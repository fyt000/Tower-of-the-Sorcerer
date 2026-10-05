use crate::{
    assets::{Art, stair_wipe_order},
    audio::Audio,
    editor::{CampaignEditor, EditorAction},
    locales::{entity_name, tr, translate_text},
    platform,
    theme::{self, BG as NAVY, GOLD, Icon, SURFACE as CARD, TEXT},
};
use eframe::egui::{self, Align2, Color32, FontId, Rect, RichText, Stroke, Vec2};
use serde_json::{Value, json};
use std::{
    collections::{BTreeMap, BTreeSet, VecDeque},
    sync::mpsc,
    time::Duration,
};
use tos_core::{Campaign, Command, Direction, Engine};

const SAVE: &str = "tos-rust:save:v1";
const CAMPAIGN: &str = "tos-rust:campaign:v1";
const CHECKPOINT: &str = "tos-rust:checkpoint:v1";
const PREFS: &str = "tos-rust:prefs:v2";

struct Active {
    effect: Value,
    start: f64,
    duration: f64,
    sounds_played: usize,
}

struct BattleProgress {
    hero_hp: i64,
    enemy_hp: i64,
    hero_turn: bool,
    completed: i64,
    strike: i64,
    phase: f32,
}

fn battle_impact(effect: &Value, progress: &BattleProgress) -> Option<bool> {
    let start = effect["overlay_phase"].as_f64().unwrap_or(1.0 / 3.0) as f32;
    let end = effect["overlay_end_phase"].as_f64().unwrap_or(2.0 / 3.0) as f32;
    // Each strike has a clean approach, a short impact, then a clean damage
    // calculation. Never carry the previous strike's image into a new beat.
    (progress.phase >= start && progress.phase < end).then_some(progress.hero_turn)
}

fn presentation_sprite(visual: &Value, tile: &Value) -> Value {
    let sprite = &visual["tile_defs"][tile.to_string()]["sprite"];
    if sprite.is_null() {
        tile.clone()
    } else {
        sprite.clone()
    }
}

struct FloorEnemyGroup {
    name: String,
    inspection: Value,
    count: usize,
}

/// Group only the already revealed encounter facts. Tile IDs and positions are
/// deliberately absent: equivalent Octopus parts collapse, but reward variants
/// and current runtime/forecast changes remain separate rows.
fn group_floor_enemies(entries: Vec<Value>, locale: &str) -> Vec<FloorEnemyGroup> {
    let mut groups: Vec<FloorEnemyGroup> = Vec::new();
    let mut keys: BTreeMap<String, usize> = BTreeMap::new();
    for inspection in entries {
        let id = inspection["id"].as_u64().unwrap_or(6).to_string();
        let name = entity_name(
            locale,
            "tiles",
            &id,
            inspection["name"].as_str().unwrap_or(""),
        );
        let key = json!([name, inspection["enemy"]]).to_string();
        if let Some(index) = keys.get(&key) {
            groups[*index].count += 1;
        } else {
            keys.insert(key, groups.len());
            groups.push(FloorEnemyGroup {
                name,
                inspection,
                count: 1,
            });
        }
    }
    groups
}

pub struct TowerApp {
    pub engine: Engine,
    snapshot: Value,
    visual: Value,
    pub editor_open: bool,
    editor: CampaignEditor,
    locale: String,
    assets: Art,
    audio: Audio,
    root: String,
    receiver: mpsc::Receiver<(String, Result<Vec<u8>, String>)>,
    sender: mpsc::Sender<(String, Result<Vec<u8>, String>)>,
    requested: BTreeSet<String>,
    context: egui::Context,
    queue: VecDeque<Value>,
    active: Option<Active>,
    route: VecDeque<Direction>,
    facing: String,
    hero_idle_at: f64,
    selected: Option<(usize, usize)>,
    settings: bool,
    journal_open: bool,
    enemy_list_open: bool,
    landscape: bool,
    classic_layout: bool,
    import_text: String,
    toast: Option<(String, f64)>,
    bounds: BTreeMap<String, Value>,
    speed: f32,
    dialogue_started: f64,
    dialogue_signature: String,
    music_pending: String,
    music_paused: bool,
    music_override: Option<String>,
    animation_history: Vec<String>,
    animation_details: Vec<Value>,
}

impl TowerApp {
    pub fn new(
        cc: &eframe::CreationContext<'_>,
        campaign: Option<String>,
        root: String,
        editor_open: bool,
    ) -> Self {
        #[cfg(not(target_arch = "wasm32"))]
        let initial_chinese =
            std::fs::read(std::path::Path::new(&root).join("fonts/NotoSansSC.ttf")).ok();
        #[cfg(target_arch = "wasm32")]
        let initial_chinese = None;
        configure(&cc.egui_ctx, initial_chinese);
        let source = campaign
            .or_else(|| platform::read(CAMPAIGN).map(upgrade_original_campaign))
            .unwrap_or_else(|| include_str!("../../../data/campaign.json").into());
        let mut recovery = None;
        let mut engine = match Engine::from_json(&source) {
            Ok(engine) => engine,
            Err(error) => {
                let backup = match platform::write("tos-rust:campaign:recovery", &source) {
                    Ok(()) => "The rejected campaign is preserved in recovery storage.".into(),
                    Err(error) => format!("The rejected campaign could not be preserved: {error}."),
                };
                let bundled = include_str!("../../../data/campaign.json");
                let storage = match platform::write(CAMPAIGN, bundled) {
                    Ok(()) => String::new(),
                    Err(error) => format!(" The bundled campaign could not be cached: {error}."),
                };
                recovery = Some(format!(
                    "Campaign could not be loaded: {error}. {backup} Loaded the bundled campaign.{storage}"
                ));
                Engine::from_json(bundled).expect("bundled campaign is validated by the test suite")
            }
        };
        if let Some(save) = platform::read(SAVE) {
            match restore_journey(&mut engine, &save) {
                Ok(Some(migrated)) => {
                    let _ = platform::write("tos-rust:save:recovery", &save);
                    let _ = platform::write(SAVE, &migrated);
                    let message = "Your saved journey was migrated to the restored original campaign. A recovery copy is preserved.";
                    match recovery.as_mut() {
                        Some(previous) => {
                            previous.push(' ');
                            previous.push_str(message);
                        }
                        None => recovery = Some(message.into()),
                    }
                }
                Ok(None) => {}
                Err(error) => {
                    let _ = platform::write("tos-rust:save:recovery", &save);
                    let message = format!(
                        "Saved journey needs migration: {error}. A recovery copy is preserved."
                    );
                    match recovery.as_mut() {
                        Some(previous) => {
                            previous.push(' ');
                            previous.push_str(&message);
                        }
                        None => recovery = Some(message),
                    }
                }
            }
        }
        let prefs: Value = platform::read(PREFS)
            .and_then(|s| serde_json::from_str(&s).ok())
            .unwrap_or_default();
        let snapshot = engine.snapshot();
        let editor = CampaignEditor::new(
            serde_json::to_value(engine.campaign()).expect("validated campaign serializes to JSON"),
        );
        let (sender, receiver) = mpsc::channel();
        let mut app = Self {
            engine,
            snapshot: snapshot.clone(),
            visual: snapshot,
            editor_open,
            editor,
            locale: prefs["locale"].as_str().unwrap_or("en").into(),
            assets: Art::default(),
            audio: Audio::default(),
            root,
            receiver,
            sender,
            requested: BTreeSet::new(),
            context: cc.egui_ctx.clone(),
            queue: VecDeque::new(),
            active: None,
            route: VecDeque::new(),
            facing: "down".into(),
            hero_idle_at: 0.0,
            selected: None,
            settings: false,
            journal_open: false,
            enemy_list_open: false,
            landscape: false,
            classic_layout: false,
            import_text: String::new(),
            toast: None,
            bounds: BTreeMap::new(),
            speed: prefs["speed"].as_f64().unwrap_or(1.0) as f32,
            dialogue_started: 0.0,
            dialogue_signature: String::new(),
            music_pending: String::new(),
            music_paused: false,
            music_override: None,
            animation_history: vec![],
            animation_details: vec![],
        };
        app.audio.enabled = prefs["audio"].as_bool().unwrap_or(true);
        app.audio.music_enabled = prefs["music"].as_bool().unwrap_or(true);
        app.audio.volume = prefs["volume"].as_f64().unwrap_or(0.55) as f32;
        app.request("assets/original-atlas.png");
        app.request("assets/original-background-atlas.png");
        for scene in ["data3-title05", "data3-open1", "data3-open2"] {
            app.request(&format!("assets/{scene}.png"));
        }
        #[cfg(target_arch = "wasm32")]
        app.request("fonts/NotoSansSC.ttf");
        for name in ["get", "open", "taisen", "kai", "kai2", "3f", "20f", "zeno"] {
            app.request(&format!("assets/wav/{name}.wav"));
        }
        if let Some(message) = recovery {
            app.notify(message);
        }
        app
    }

    fn now(&self) -> f64 {
        self.context.input(|i| i.time)
    }
    fn text(&self, key: &str) -> String {
        tr(&self.locale, key)
    }
    fn request(&mut self, path: &str) {
        if self.requested.insert(path.into()) {
            platform::load(path, &self.root, self.sender.clone(), self.context.clone());
        }
    }
    fn notify(&mut self, message: impl Into<String>) {
        self.toast = Some((message.into(), self.now() + 6.0));
    }
    fn preferences(&self) {
        let _=platform::write(PREFS,&json!({"locale":self.locale,"audio":self.audio.enabled,"music":self.audio.music_enabled,"volume":self.audio.volume,"speed":self.speed}).to_string());
    }
    pub fn set_locale(&mut self, locale: &str) {
        self.locale = if locale.starts_with("zh") {
            "zh-CN"
        } else {
            "en"
        }
        .into();
        self.preferences();
        self.context.request_repaint();
    }

    fn persist(&mut self) {
        if let Err(e) = platform::write(SAVE, &self.engine.save_json()) {
            self.notify(e);
        }
    }

    pub fn replace_campaign(&mut self, source: &str) -> Result<(), String> {
        let engine = Engine::from_json(source)?;
        let campaign =
            serde_json::to_value(engine.campaign()).expect("validated campaign serializes to JSON");
        self.engine = engine;
        self.snapshot = self.engine.snapshot();
        self.visual = self.snapshot.clone();
        self.queue.clear();
        self.active = None;
        self.hero_idle_at = 0.0;
        self.route.clear();
        self.selected = None;
        self.journal_open = false;
        self.enemy_list_open = false;
        self.music_paused = false;
        self.music_override = None;
        self.editor.replace_campaign(campaign);
        let _ = platform::write(CAMPAIGN, source);
        self.persist();
        self.context.request_repaint();
        Ok(())
    }

    pub fn load_save(&mut self, source: &str) -> Result<(), String> {
        if restore_journey(&mut self.engine, source)?.is_some() {
            let _ = platform::write("tos-rust:save:recovery", source);
        }
        self.snapshot = self.engine.snapshot();
        self.visual = self.snapshot.clone();
        self.queue.clear();
        self.active = None;
        self.hero_idle_at = 0.0;
        self.route.clear();
        self.selected = None;
        self.journal_open = false;
        self.enemy_list_open = false;
        self.music_paused = false;
        self.music_override = None;
        self.persist();
        self.context.request_repaint();
        Ok(())
    }

    /// External JSON is decoded before touching audio, movement or animation.
    pub fn submit_json(&mut self, source: &str) -> Result<(), String> {
        let command = Command::from_json(source).map_err(|error| error.to_string())?;
        self.submit(command)
    }

    pub fn submit(&mut self, command: Command) -> Result<(), String> {
        command.validate().map_err(|error| error.to_string())?;
        let direction = match &command {
            Command::Move { direction } => Some(*direction),
            _ => None,
        };
        self.engine.execute(command)?;
        self.audio.unlock();
        self.visual = self.snapshot.clone();
        if let Some(direction) = direction {
            self.facing = direction.as_str().into();
            self.hero_idle_at = self.now() + self.ambient_interval();
        }
        self.snapshot = self.engine.snapshot();
        if self.visual["last_encounter"] != self.snapshot["last_encounter"]
            || self.visual["floor"] != self.snapshot["floor"]
        {
            // A new contact or floor takes over from an older inspection.
            // Hovering or tapping a tile can select a new target immediately.
            self.selected = None;
        }
        self.queue = self.snapshot["last_action"]["presentation"]
            .as_array()
            .cloned()
            .unwrap_or_default()
            .into();
        self.active = None;
        if !self.queue.iter().any(|e| e["type"] == "move") {
            self.hero_idle_at = 0.0;
        }
        if self.queue.is_empty() {
            self.visual = self.snapshot.clone();
        }
        if !self.snapshot["last_action"]["ok"].as_bool().unwrap_or(true) {
            self.route.clear();
        }
        if self.visual["floor"] != self.snapshot["floor"] {
            self.music_paused = false;
            self.music_override = None;
        }
        if self.visual["floor"] != self.snapshot["floor"]
            || !self.snapshot["pending_interaction"].is_null()
            || self.snapshot["status"] != "playing"
        {
            self.route.clear();
        }
        if self
            .queue
            .iter()
            .any(|e| !["move", "tile", "audio"].contains(&e["type"].as_str().unwrap_or("")))
        {
            self.route.clear();
        }
        self.persist();
        self.context.request_repaint();
        Ok(())
    }

    fn apply_command(&mut self, command: Command) {
        if let Err(error) = self.submit(command) {
            self.notify(error);
        }
    }

    pub fn debug_json(&self) -> Value {
        json!({"ready":true,"landscape":self.landscape,"ui_scale":theme::scale(&self.context),"palette":{"bg":theme::colors(&self.context).bg.to_array(),"surface":theme::colors(&self.context).surface.to_array(),"accent":theme::colors(&self.context).accent.to_array(),"metal":theme::colors(&self.context).metal.to_array(),"reverse":self.visual["cycle"].as_u64().unwrap_or(1)>1},"notice":self.toast.as_ref().map(|(message,_)|message),"locale":self.locale,"visual_floor":self.visual["floor"],"visual_tiles":self.visual["tiles"],"visual_player":self.visual["player"],"visual_log":self.visual["log"],"editor_open":self.editor_open,"editor":self.editor.debug_json(),"bounds":self.bounds,"animation":self.active.as_ref().map(|a|a.effect["type"].clone()),"animation_effect":self.active.as_ref().map(|a|a.effect.clone()),"animation_progress":self.active.as_ref().map(|a|((self.now()-a.start)/a.duration).clamp(0.0,1.0)),"ambient_frame":(self.now()/self.ambient_interval()) as usize%2,"presentation_remaining":self.queue.len(),"path_remaining":self.route.len(),"animations_seen":self.animation_history,"animation_details":self.animation_details,"hero_pose":if self.active.as_ref().is_some_and(|a|a.effect["type"]=="move")||self.now()<self.hero_idle_at{"walking"}else{"idle"},"facing":self.facing,"battle":self.battle_progress(self.now()).map(|b|json!({"hero_hp":b.hero_hp,"enemy_hp":b.enemy_hp,"hero_turn":b.hero_turn,"completed":b.completed,"strike":b.strike,"phase":b.phase,"impact_visible":self.active.as_ref().and_then(|a|battle_impact(&a.effect,&b)).is_some()})),"audio":{"unlocked":self.audio.unlocked,"enabled":self.audio.enabled,"effects_played":self.audio.effects_played,"music":self.audio.music_name,"error":self.audio.error},"sprites_loaded":self.assets.atlas.is_some()})
    }

    pub fn editor_campaign_json(&self) -> String {
        self.editor.campaign().to_string()
    }

    fn advance(&mut self, now: f64) {
        while let Ok((path, result)) = self.receiver.try_recv() {
            match result {
                Ok(bytes) => {
                    if path.starts_with("drop:") {
                        let result = (|| -> Result<(), String> {
                            let source = std::str::from_utf8(&bytes).map_err(|e| e.to_string())?;
                            let value: Value =
                                serde_json::from_str(source).map_err(|e| e.to_string())?;
                            if value["tiles"].is_object() && value["floors"].is_array() {
                                self.replace_campaign(source)
                            } else {
                                self.load_save(source)
                            }
                        })();
                        match result {
                            Ok(()) => self.notify(self.text("imported")),
                            Err(e) => self.notify(e),
                        }
                    } else if path.ends_with("original-atlas.png") {
                        if let Err(e) = self.assets.install(&self.context, &bytes) {
                            self.notify(e);
                        }
                        if let Some(atlas) = &self.assets.atlas {
                            self.editor.set_atlas(
                                atlas.id(),
                                Vec2::new(self.assets.size[0] as f32, self.assets.size[1] as f32),
                            );
                        }
                    } else if path.ends_with("original-background-atlas.png") {
                        if let Err(e) = self.assets.install_background(&self.context, &bytes) {
                            self.notify(e);
                        }
                    } else if path.ends_with(".ttf") {
                        install_fonts(&self.context, Some(bytes));
                    } else if path.ends_with(".png") {
                        if let Err(e) = self.assets.install_scene(&self.context, &path, &bytes) {
                            self.notify(e);
                        }
                    } else if let Err(e) = self.audio.install(&path, &bytes) {
                        self.notify(format!("{path}: {e}"));
                    }
                }
                Err(_) => {
                    if path.ends_with("original-atlas.png") {
                        self.notify(self.text("assets_missing"));
                    }
                    if path.starts_with("drop:") {
                        self.notify("Unable to read dropped file");
                    }
                }
            }
        }
        if self.audio.unlocked
            && self.audio.enabled
            && self.audio.music_enabled
            && !self.music_paused
        {
            let floor = self.visual["floor"].as_i64().unwrap_or(1);
            let name = self.engine.campaign().rules["audio"]["floor_music"]
                .as_array()
                .and_then(|entries| {
                    entries.iter().find(|entry| {
                        floor >= entry["min_floor"].as_i64().unwrap_or(i64::MIN)
                            && floor <= entry["max_floor"].as_i64().unwrap_or(i64::MAX)
                    })
                })
                .and_then(|entry| entry["file"].as_str())
                .unwrap_or_else(|| music_for_floor(floor));
            let path = self
                .music_override
                .clone()
                .unwrap_or_else(|| format!("assets/midi/{name}.mid"));
            if self.music_pending != path {
                self.music_pending = path.clone();
                self.request(&path);
            }
            if self.audio.has(&path) {
                self.audio.play(&path, true);
            }
        }
        if let Some(effect) = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "floor" && now - a.start >= a.duration * 0.5)
            .map(|a| a.effect.clone())
            && self.visual["floor"] != effect["to"]
        {
            self.floor_visual(&effect);
        }
        if let Some(active) = &mut self.active {
            let elapsed_ms = (now - active.start) * 1000.0 * f64::from(self.speed);
            let (cue, due) =
                if active.effect["type"] == "battle" || active.effect["type"] == "damage" {
                    let total = active.effect["hero_strikes"].as_u64().unwrap_or(1)
                        + active.effect["enemy_strikes"].as_u64().unwrap_or(0);
                    let interval = active.effect["strike_ms"]
                        .as_f64()
                        .unwrap_or(450.0)
                        .max(1.0);
                    (
                        active.effect["hit_sound"]
                            .as_str()
                            .unwrap_or("taisen")
                            .to_owned(),
                        ((elapsed_ms / interval).floor() as usize + 1).min(total as usize),
                    )
                } else {
                    let due = active.effect["sound_offsets_ms"]
                        .as_array()
                        .map(|offsets| {
                            offsets
                                .iter()
                                .take_while(|v| v.as_f64().unwrap_or(0.0) <= elapsed_ms)
                                .count()
                        })
                        .unwrap_or(0);
                    (
                        active.effect["sound_cue"].as_str().unwrap_or("").to_owned(),
                        due,
                    )
                };
            while active.sounds_played < due {
                self.audio.play(&format!("assets/wav/{cue}.wav"), false);
                active.sounds_played += 1;
            }
        }
        let expired = self.active.as_ref().is_some_and(|a| {
            a.effect["type"] != "dialogue"
                && a.effect["type"] != "journal"
                && now - a.start >= a.duration
        });
        if expired {
            self.finish_effect();
        }
        if self.active.is_none() {
            while let Some(effect) = self.queue.pop_front() {
                let kind = effect["type"].as_str().unwrap_or("").to_string();
                self.animation_history.push(kind.clone());
                self.animation_details.push(json!({"type":kind,"kind":effect["kind"],"style":effect["style"],"asset":effect["asset"]}));
                if self.animation_details.len() > 120 {
                    self.animation_details.remove(0);
                }
                if self.animation_history.len() > 120 {
                    self.animation_history.remove(0);
                }
                if kind == "audio" {
                    let name = effect["name"].as_str().unwrap_or("get");
                    if name == "music-stop" {
                        self.music_paused = true;
                        self.audio.stop_music();
                        continue;
                    }
                    if name == "music-start" {
                        self.music_paused = false;
                        continue;
                    }
                    if let Some(id) = name.strip_prefix("music:") {
                        if let Some(file) =
                            self.engine.campaign().rules["audio"]["music_cues"][id].as_str()
                        {
                            let path = format!("assets/midi/{file}.mid");
                            self.music_override = Some(path.clone());
                            self.music_paused = false;
                            self.request(&path);
                        }
                        continue;
                    }
                    let path = if name.contains('/') {
                        name.to_string()
                    } else {
                        format!("assets/wav/{}.wav", name.trim_end_matches(".wav"))
                    };
                    self.audio.play(&path, false);
                    continue;
                }
                if let Some(direction) = effect["direction"].as_str() {
                    self.facing = direction.into();
                }
                if kind == "dialogue" {
                    self.append_visual_activity(effect["text"].clone(), effect["log_id"].as_u64());
                }
                if kind == "floor" {
                    let cue = effect["sound"].as_str().unwrap_or("none");
                    if cue != "none" {
                        self.audio.play(&format!("assets/wav/{cue}.wav"), false);
                    }
                }
                for field in ["asset", "target_asset", "background_asset"] {
                    if let Some(asset) = effect[field].as_str() {
                        self.request(&format!("assets/{asset}.png"));
                    }
                }
                let duration = effect["duration_ms"]
                    .as_f64()
                    .unwrap_or(if kind == "dialogue" { 0.0 } else { 100.0 })
                    / 1000.0
                    / f64::from(self.speed);
                self.active = Some(Active {
                    effect,
                    start: now,
                    duration: duration.max(0.025),
                    sounds_played: 0,
                });
                break;
            }
            if self.active.is_none() {
                self.visual = self.snapshot.clone();
                if let Some(direction) = self.route.pop_front() {
                    self.apply_command(Command::Move { direction });
                }
            }
        }
    }

    fn finish_effect(&mut self) {
        if let Some(active) = self.active.take() {
            let e = &active.effect;
            match e["type"].as_str().unwrap_or("") {
                "tile" => {
                    self.tile_visual(e);
                }
                "cinematic" if e["kind"] == "tile_reveal" || e["style"] == "dissolve" => {
                    // Commit the visual target as the transition ends. The
                    // following tile write must never flash the old door or
                    // enemy back onto the board for its final 60ms hold.
                    self.tile_visual(e);
                }
                "move" => {
                    self.hero_idle_at = self.now() + self.ambient_interval();
                    self.visual["player"]["x"] = e["to"]["x"].clone();
                    self.visual["player"]["y"] = e["to"]["y"].clone();
                }
                "battle" | "damage" => {
                    let strikes = e["enemy_strikes"]
                        .as_i64()
                        .unwrap_or_else(|| e["rounds"].as_i64().unwrap_or(0));
                    self.visual["player"]["hp"] = json!(
                        (e["hero_hp"].as_i64().unwrap_or(0)
                            - strikes * e["enemy_hit"].as_i64().unwrap_or(0))
                        .max(0)
                    );
                    if e["battle_log"].is_object() {
                        let battle = e["battle_log"].clone();
                        self.visual["player"]["hp"] = battle["hero_after_hp"].clone();
                        if let (Some(before), Some(reward)) = (
                            battle["hero_before"]["gold"].as_i64(),
                            battle["reward"].as_i64(),
                        ) {
                            self.visual["player"]["gold"] = json!(before.saturating_add(reward));
                        }
                        if self.append_visual_activity(
                            e["activity"].clone(),
                            battle["log_id"].as_u64(),
                        ) {
                            if !self.visual["battle_log"].is_array() {
                                self.visual["battle_log"] = json!([]);
                            }
                            let records = self.visual["battle_log"]
                                .as_array_mut()
                                .expect("history is an array");
                            if !records
                                .iter()
                                .any(|record| record["log_id"] == battle["log_id"])
                            {
                                records.push(battle);
                            }
                        }
                    }
                }
                "move_tile" => {
                    if e["floor"] == self.visual["floor"] {
                        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
                        let from = e["from_y"].as_u64().unwrap_or(0) as usize * width
                            + e["from_x"].as_u64().unwrap_or(0) as usize;
                        let to = e["y"].as_u64().unwrap_or(0) as usize * width
                            + e["x"].as_u64().unwrap_or(0) as usize;
                        let empty = self.engine.campaign().rules["empty_tile"]
                            .as_u64()
                            .unwrap_or(6);
                        if let Some(tiles) = self.visual["tiles"].as_array_mut()
                            && from < tiles.len()
                            && to < tiles.len()
                        {
                            tiles[from] = json!(empty);
                            tiles[to] = e["tile"].clone();
                        }
                    }
                }
                "floor" => {
                    self.floor_visual(e);
                }
                _ => {}
            }
        }
    }

    fn floor_visual(&mut self, e: &Value) {
        let floor = e["to"]
            .as_i64()
            .unwrap_or_else(|| self.snapshot["floor"].as_i64().unwrap_or(1))
            as i32;
        if self.visual["floor"] != json!(floor) {
            self.music_paused = false;
            self.music_override = None;
        }
        if e["player"].is_object() {
            self.visual["player"] = e["player"].clone();
        }
        self.visual["floor"] = json!(floor);
        self.visual["player"]["floor"] = json!(floor);
        let tiles = (0..self.engine.campaign().height)
            .flat_map(|y| (0..self.engine.campaign().width).map(move |x| (x, y)))
            .filter_map(|(x, y)| self.engine.tile_at(floor, x, y))
            .collect::<Vec<_>>();
        self.visual["tiles"] = if e["tiles"].is_array() {
            e["tiles"].clone()
        } else {
            json!(tiles)
        };
        self.visual["player"]["x"] = if e["x"].is_number() {
            e["x"].clone()
        } else {
            self.snapshot["player"]["x"].clone()
        };
        self.visual["player"]["y"] = if e["y"].is_number() {
            e["y"].clone()
        } else {
            self.snapshot["player"]["y"].clone()
        };
    }

    fn tile_visual(&mut self, effect: &Value) {
        if effect["floor"] == self.visual["floor"] {
            let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
            let index = effect["y"].as_u64().unwrap_or(0) as usize * width
                + effect["x"].as_u64().unwrap_or(0) as usize;
            if let Some(tile) = self.visual["tiles"]
                .as_array_mut()
                .and_then(|tiles| tiles.get_mut(index))
            {
                *tile = effect["tile"].clone();
            }
        }
    }

    fn busy(&self) -> bool {
        self.active.is_some() || !self.queue.is_empty()
    }

    fn ambient_interval(&self) -> f64 {
        self.engine.campaign().rules["presentation"]["ambient_frame_ms"]
            .as_f64()
            .unwrap_or(150.0)
            .clamp(60.0, 1000.0)
            / 1000.0
            / f64::from(self.speed)
    }
    fn travel_only(&self) -> bool {
        self.active.as_ref().is_none_or(|a| {
            ["move", "tile", "audio"].contains(&a.effect["type"].as_str().unwrap_or(""))
        }) && self
            .queue
            .iter()
            .all(|e| ["move", "tile", "audio"].contains(&e["type"].as_str().unwrap_or("")))
    }
    fn battle_progress(&self, now: f64) -> Option<BattleProgress> {
        let active = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "battle" || a.effect["type"] == "damage")?;
        let e = &active.effect;
        let hero_strikes = e["hero_strikes"].as_i64().unwrap_or(1);
        let enemy_strikes = e["enemy_strikes"].as_i64().unwrap_or(0);
        let total = (hero_strikes + enemy_strikes).max(1);
        let position = ((now - active.start) / active.duration).clamp(0.0, 1.0) * total as f64;
        let index = (position.floor() as i64).min(total - 1);
        let phase = (position - index as f64).clamp(0.0, 1.0) as f32;
        let completed = (index
            + i64::from(phase >= e["damage_phase"].as_f64().unwrap_or(2.0 / 3.0) as f32))
        .min(total);
        let hero_first = !e["enemy_first"].as_bool().unwrap_or(false);
        let hero_hits = (if hero_first {
            (completed + 1) / 2
        } else {
            completed / 2
        })
        .min(hero_strikes);
        let enemy_hits = (if hero_first {
            completed / 2
        } else {
            (completed + 1) / 2
        })
        .min(enemy_strikes);
        Some(BattleProgress {
            hero_hp: (e["hero_hp"].as_i64().unwrap_or(0)
                - enemy_hits * e["enemy_hit"].as_i64().unwrap_or(0))
            .max(0),
            enemy_hp: (e["enemy_hp"].as_i64().unwrap_or(0)
                - hero_hits * e["hero_hit"].as_i64().unwrap_or(0))
            .max(0),
            hero_turn: (index % 2 == 0) == hero_first,
            completed,
            strike: index,
            phase,
        })
    }
    fn record(&mut self, id: &str, response: &egui::Response) {
        self.bounds.insert(id.into(),json!({"x":response.rect.min.x,"y":response.rect.min.y,"w":response.rect.width(),"h":response.rect.height(),"enabled":response.enabled()}));
    }

    fn header(&mut self, ui: &mut egui::Ui) {
        if self.classic_layout {
            return;
        }
        ui.horizontal(|ui| self.header_controls(ui, true));
        ui.add_space(4.0);
    }

    fn header_controls(&mut self, ui: &mut egui::Ui, narrow: bool) {
        self.enemy_list_button(ui);
        let journal = ui
            .add_enabled_ui(
                !self.busy() && self.snapshot["pending_interaction"].is_null(),
                |ui| theme::action(ui, String::new(), Icon::Book, false),
            )
            .inner;
        self.record("journal_header", &journal);
        if journal.on_hover_text(self.text("journal_expand")).clicked() {
            self.open_journal_history();
        }
        let settings = theme::action(
            ui,
            if narrow {
                String::new()
            } else {
                self.text("settings")
            },
            Icon::Settings,
            false,
        );
        self.record("settings", &settings);
        if settings.on_hover_text(self.text("settings")).clicked() {
            self.settings = !self.settings;
        }
        let edit = theme::action(ui, self.text("editor_short"), Icon::Edit, false);
        self.record("editor", &edit);
        if edit.clicked() {
            self.editor_open = true;
        }
        let save = ui
            .add_enabled_ui(self.engine.save_unlocked(), |ui| {
                theme::action(ui, self.text("save_short"), Icon::Save, true)
            })
            .inner
            .on_disabled_hover_text(self.text("save_orb_required"));
        self.record("save", &save);
        if save.clicked() {
            self.checkpoint();
        }
        let restore = theme::action(
            ui,
            if narrow {
                String::new()
            } else {
                self.text("restore_short")
            },
            Icon::Restore,
            false,
        );
        self.record("restore", &restore);
        if restore.on_hover_text(self.text("restore")).clicked() {
            self.restore_checkpoint();
        }
    }

    fn checkpoint(&mut self) {
        if self.engine.ensure_player_save_allowed().is_err() {
            self.notify(self.text("save_orb_required"));
            return;
        }
        let value = json!({"campaign":self.engine.campaign(),"save":serde_json::from_str::<Value>(&self.engine.save_json()).expect("engine-generated save is valid JSON")});
        match platform::write(CHECKPOINT, &value.to_string()) {
            Ok(()) => self.notify(self.text("saved")),
            Err(e) => self.notify(e),
        }
    }
    fn restore_checkpoint(&mut self) {
        let result = (|| -> Result<(), String> {
            let source = platform::read(CHECKPOINT).ok_or_else(|| self.text("no_checkpoint"))?;
            let value: Value = serde_json::from_str(&source).map_err(|e| e.to_string())?;
            let original_campaign = match value["campaign"].as_str() {
                Some(source) => source.to_owned(),
                None => value["campaign"].to_string(),
            };
            let campaign = original_campaign_upgrade(&original_campaign)
                .unwrap_or(&original_campaign)
                .to_owned();
            let save = match value["save"].as_str() {
                Some(source) => source.to_owned(),
                None => value["save"].to_string(),
            };
            let mut engine = Engine::from_json(&campaign)?;
            restore_journey(&mut engine, &save)?;
            if campaign != original_campaign {
                let _ = platform::write("tos-rust:campaign:recovery", &original_campaign);
            }
            self.replace_campaign(&campaign)?;
            self.load_save(&save)?;
            Ok(())
        })();
        match result {
            Ok(()) => self.notify(self.text("restored")),
            Err(e) => self.notify(e),
        }
    }

    fn stats(&mut self, ui: &mut egui::Ui, compact: bool) {
        let mut player = self.visual["player"].clone();
        if let Some(battle) = self.battle_progress(self.now()) {
            player["hp"] = json!(battle.hero_hp);
        }
        let metrics = [
            ("health", "hp", theme::RED, Icon::Heart),
            (
                "attack",
                "attack",
                theme::colors(ui.ctx()).metal,
                Icon::Sword,
            ),
            ("defense", "defense", theme::BLUE, Icon::Shield),
            ("gold", "gold", theme::GREEN, Icon::Coin),
        ];
        if compact {
            let width = (ui.available_width() - 24.0) / 4.0;
            ui.horizontal_top(|ui| {
                for (label, key, color, icon) in metrics {
                    metric(
                        ui,
                        width,
                        &self.text(label),
                        &number(&player[key]),
                        color,
                        icon,
                        true,
                    );
                }
            });
            ui.add_space(4.0);
            self.keys(ui, true);
            ui.add_space(8.0);
            self.equipment(ui, true);
            return;
        }
        ui.horizontal(|ui| {
            let (portrait, _) = ui.allocate_exact_size(Vec2::splat(62.0), egui::Sense::hover());
            ui.painter()
                .rect_filled(portrait, 14.0, theme::colors(ui.ctx()).raised);
            ui.painter().rect_stroke(
                portrait,
                14.0,
                Stroke::new(1.0, theme::colors(ui.ctx()).border),
                egui::StrokeKind::Inside,
            );
            if let Some(hero) = self.assets.heroes.get("down") {
                ui.painter().image(
                    hero[2].id(),
                    portrait.shrink(9.0),
                    Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
                    Color32::WHITE,
                );
            }
            ui.add_space(5.0);
            ui.vertical(|ui| {
                ui.label(
                    RichText::new(self.text("adventurer"))
                        .size(23.0)
                        .strong()
                        .color(theme::colors(ui.ctx()).text),
                );
                ui.label(
                    RichText::new(format!("{} {}", self.text("floor"), self.visual["floor"]))
                        .size(15.0)
                        .color(theme::colors(ui.ctx()).muted),
                );
            });
        });
        ui.add_space(18.0);
        let width = (ui.available_width() - 8.0) / 2.0;
        for row in metrics.chunks(2) {
            ui.horizontal_top(|ui| {
                for (label, key, color, icon) in row {
                    metric(
                        ui,
                        width,
                        &self.text(label),
                        &number(&player[*key]),
                        *color,
                        *icon,
                        false,
                    );
                }
            });
            ui.add_space(3.0);
        }
        if self.visual["cycle"].as_u64().unwrap_or(1) > 1 {
            ui.add_space(8.0);
            ui.label(
                RichText::new(format!(
                    "{} ×{}",
                    self.text("backside"),
                    self.visual["backside_multiplier"]
                ))
                .size(15.0)
                .color(theme::colors(ui.ctx()).metal),
            );
        }
        ui.add_space(12.0);
        self.equipment(ui, false);
    }

    fn tower_stats(&mut self, ui: &mut egui::Ui) {
        let scale = theme::scale(ui.ctx());
        ui.label(
            RichText::new(format!("{} {}", self.text("floor"), self.visual["floor"]))
                .size(if self.landscape { 14.0 } else { 18.0 * scale })
                .strong(),
        );
        ui.add_space(3.0 * scale);
        let mut player = self.visual["player"].clone();
        if let Some(battle) = self.battle_progress(self.now()) {
            player["hp"] = json!(battle.hero_hp);
        }
        if self.landscape {
            let metrics = [
                ("health", "hp", Icon::Heart, theme::RED),
                (
                    "attack",
                    "attack",
                    Icon::Sword,
                    theme::colors(ui.ctx()).metal,
                ),
                ("defense", "defense", Icon::Shield, theme::BLUE),
                ("gold", "gold", Icon::Coin, theme::GREEN),
            ];
            let width = (ui.available_width() - 5.0) * 0.5;
            let stats = ui.scope(|ui| {
                for row in metrics.chunks(2) {
                    ui.horizontal(|ui| {
                        for (label, key, icon, color) in row {
                            let (rect, response) = ui
                                .allocate_exact_size(Vec2::new(width, 28.0), egui::Sense::hover());
                            ui.painter()
                                .rect_filled(rect, 5.0, theme::colors(ui.ctx()).raised);
                            theme::icon(
                                ui.painter(),
                                Rect::from_center_size(
                                    egui::pos2(rect.left() + 12.0, rect.center().y),
                                    Vec2::splat(15.0),
                                ),
                                *icon,
                                *color,
                            );
                            let value = number(&player[*key]);
                            fitted_value(
                                ui,
                                Rect::from_min_max(
                                    egui::pos2(rect.left() + 25.0, rect.top() + 2.0),
                                    rect.max - Vec2::new(5.0, 2.0),
                                ),
                                &value,
                                17.0,
                                true,
                            );
                            self.record(&format!("stat:{key}"), &response);
                            response.on_hover_text(format!("{}: {value}", self.text(label)));
                        }
                    });
                }
            });
            self.record("stats", &stats.response);
            return;
        }
        let stats = ui.scope(|ui| {
            for (label, key, icon, color) in [
                ("health", "hp", Icon::Heart, theme::RED),
                (
                    "attack",
                    "attack",
                    Icon::Sword,
                    theme::colors(ui.ctx()).metal,
                ),
                ("defense", "defense", Icon::Shield, theme::BLUE),
                ("gold", "gold", Icon::Coin, theme::GREEN),
            ] {
                let (rect, response) = ui.allocate_exact_size(
                    Vec2::new(ui.available_width(), 30.0 * scale),
                    egui::Sense::hover(),
                );
                ui.painter()
                    .rect_filled(rect, 5.0 * scale, theme::colors(ui.ctx()).raised);
                theme::icon(
                    ui.painter(),
                    Rect::from_center_size(
                        egui::pos2(rect.left() + 14.0 * scale, rect.center().y),
                        Vec2::splat(19.0 * scale),
                    ),
                    icon,
                    color,
                );
                let label_galley = ui.painter().layout_no_wrap(
                    self.text(label),
                    FontId::proportional(17.0 * scale),
                    theme::colors(ui.ctx()).text,
                );
                let label_left = rect.left() + 32.0 * scale;
                let value_left = label_left + label_galley.size().x + 12.0 * scale;
                ui.painter().galley(
                    egui::pos2(label_left, rect.center().y - label_galley.size().y * 0.5),
                    label_galley,
                    theme::colors(ui.ctx()).text,
                );
                let value = number(&player[key]);
                let value_rect = Rect::from_min_max(
                    egui::pos2(value_left, rect.top() + 2.0 * scale),
                    rect.max - Vec2::new(5.0 * scale, 2.0 * scale),
                );
                fitted_value(ui, value_rect, &value, 21.0 * scale, true);
                self.record(&format!("stat:{key}"), &response);
                response.on_hover_text(format!("{}: {value}", self.text(label)));
            }
        });
        self.record("stats", &stats.response);
    }

    fn tower_controls(&mut self, ui: &mut egui::Ui) {
        let available = !self.busy() && self.snapshot["pending_interaction"].is_null();
        let gap = 5.0 * theme::scale(ui.ctx());
        let skip_visible = self.busy() && !self.travel_only();
        let columns = if skip_visible { 4.0 } else { 3.0 };
        let width = (ui.available_width() - gap * (columns - 1.0)) / columns;
        ui.horizontal(|ui| {
            ui.spacing_mut().item_spacing.x = gap;
            self.enemy_list_button_sized(ui, Some(width));
            let journal = ui
                .add_enabled_ui(available, |ui| {
                    theme::action_sized(ui, String::new(), Icon::Book, false, Some(width))
                })
                .inner;
            self.record("journal_header", &journal);
            if journal.on_hover_text(self.text("journal_expand")).clicked() {
                self.open_journal_history();
            }
            let save = ui
                .add_enabled_ui(available && self.engine.save_unlocked(), |ui| {
                    theme::action_sized(ui, String::new(), Icon::Save, true, Some(width))
                })
                .inner;
            self.record("save", &save);
            if save.on_hover_text(self.text("save")).clicked() {
                self.checkpoint();
            }
            if skip_visible {
                let skip =
                    theme::action_sized(ui, String::new(), Icon::ArrowRight, false, Some(width));
                self.record("skip", &skip);
                if skip.on_hover_text(self.text("skip")).clicked() {
                    self.skip_presentation();
                }
            }
        });
        let width = (ui.available_width() - 2.0 * gap) / 3.0;
        ui.horizontal(|ui| {
            ui.spacing_mut().item_spacing.x = gap;
            let restore = theme::action_sized(ui, String::new(), Icon::Restore, false, Some(width));
            self.record("restore", &restore);
            if restore.on_hover_text(self.text("restore")).clicked() {
                self.restore_checkpoint();
            }
            let settings =
                theme::action_sized(ui, String::new(), Icon::Settings, false, Some(width));
            self.record("settings", &settings);
            if settings.on_hover_text(self.text("settings")).clicked() {
                self.settings = !self.settings;
            }
            let edit = theme::action_sized(ui, String::new(), Icon::Edit, false, Some(width));
            self.record("editor", &edit);
            if edit.on_hover_text(self.text("editor")).clicked() {
                self.editor_open = true;
            }
        });
    }

    fn equipment(&mut self, ui: &mut egui::Ui, compact: bool) {
        let scale = theme::scale(ui.ctx());
        let compact = compact || self.classic_layout;
        let width = if self.classic_layout {
            ui.available_width()
        } else {
            (ui.available_width() - 8.0 * scale) / 2.0
        };
        ui.with_layout(
            if self.classic_layout {
                egui::Layout::top_down(egui::Align::Min)
            } else {
                egui::Layout::left_to_right(egui::Align::TOP)
            },
            |ui| {
                for (slot, icon) in [("weapon", Icon::Sword), ("shield", Icon::Shield)] {
                    let item = visible_equipment_item(
                        &self.visual,
                        &self.snapshot,
                        self.engine.campaign(),
                        slot,
                    );
                    let (rect, response) = ui.allocate_exact_size(
                        Vec2::new(
                            width,
                            (if self.classic_layout {
                                if self.landscape { 30.0 } else { 38.0 }
                            } else if compact {
                                46.0
                            } else {
                                84.0
                            }) * scale,
                        ),
                        egui::Sense::hover(),
                    );
                    ui.painter()
                        .rect_filled(rect, 5.0 * scale, theme::colors(ui.ctx()).raised);
                    ui.painter().rect_stroke(
                        rect,
                        5.0 * scale,
                        Stroke::new(1.0, theme::colors(ui.ctx()).border),
                        egui::StrokeKind::Inside,
                    );
                    let icon_size = (if self.classic_layout {
                        if self.landscape { 22.0 } else { 30.0 }
                    } else if compact {
                        27.0
                    } else {
                        34.0
                    }) * scale;
                    let icon_rect = Rect::from_center_size(
                        if compact {
                            egui::pos2(rect.left() + icon_size / 2.0 + 8.0 * scale, rect.center().y)
                        } else {
                            egui::pos2(rect.center().x, rect.top() + 43.0 * scale)
                        },
                        Vec2::splat(icon_size),
                    );
                    let name = item
                        .as_ref()
                        .map(|item| {
                            entity_name(
                                &self.locale,
                                "items",
                                item["id"].as_str().unwrap_or(""),
                                item["name"].as_str().unwrap_or(""),
                            )
                        })
                        .unwrap_or_else(|| self.text("equipment_empty"));
                    if item.as_ref().is_none_or(|item| {
                        !self.assets.foreground(
                            ui.painter(),
                            icon_rect,
                            &item["sprite"],
                            Color32::WHITE,
                        )
                    }) {
                        theme::icon(ui.painter(), icon_rect, icon, theme::colors(ui.ctx()).muted);
                    }
                    let text_x = if compact {
                        icon_rect.right() + 7.0 * scale
                    } else {
                        rect.left() + 6.0 * scale
                    };
                    let font = FontId::proportional(13.0 * scale);
                    let mut job = egui::text::LayoutJob::simple(
                        name.clone(),
                        font,
                        if item.is_some() {
                            theme::colors(ui.ctx()).text
                        } else {
                            theme::colors(ui.ctx()).muted
                        },
                        (rect.right() - text_x - 7.0 * scale).max(0.0),
                    );
                    job.wrap.max_rows = 1;
                    let galley = ui.painter().layout_job(job);
                    let name_position = if compact {
                        egui::pos2(text_x, rect.center().y - galley.size().y * 0.5)
                    } else {
                        egui::pos2(
                            rect.center().x - galley.size().x / 2.0,
                            rect.bottom() - 21.0 * scale,
                        )
                    };
                    ui.painter()
                        .galley(name_position, galley, theme::colors(ui.ctx()).text);
                    self.record(&format!("equipment:{slot}"), &response);
                    response.on_hover_text(
                        item.as_ref()
                            .map(|item| item_tooltip(&self.locale, item, &name))
                            .unwrap_or_else(|| format!("{}: {}", self.text(slot), name)),
                    );
                }
            },
        );
        let protected = self.visual["player"]["inventory"]
            .as_array()
            .map(|items| items.iter().any(|item| item == "sacred_shield"))
            .unwrap_or_else(|| {
                self.visual["abilities"]["field_magic_protection"]
                    .as_bool()
                    .unwrap_or(false)
            });
        if protected && self.visual["player"]["shield"] != "sacred_shield" {
            ui.add_space(4.0 * scale);
            ui.label(
                RichText::new(self.text("magic_protection_active"))
                    .size(12.0 * scale)
                    .color(theme::BLUE),
            );
        }
    }

    fn keys(&mut self, ui: &mut egui::Ui, compact: bool) {
        let scale = theme::scale(ui.ctx());
        if !compact {
            section(ui, &self.text("keyring"), Icon::Key);
            ui.add_space(14.0 * scale);
        }
        let width = (ui.available_width() - 16.0 * scale) / 3.0;
        ui.horizontal(|ui| {
            for (key, color) in [
                ("yellow", theme::YELLOW),
                ("blue", theme::BLUE),
                ("red", theme::RED),
            ] {
                let (rect, response) = ui.allocate_exact_size(
                    Vec2::new(width, if compact { 22.0 } else { 38.0 } * scale),
                    egui::Sense::hover(),
                );
                if !compact {
                    ui.painter()
                        .rect_filled(rect, 8.0 * scale, theme::colors(ui.ctx()).raised);
                }
                let icon_rect = Rect::from_center_size(
                    egui::pos2(
                        rect.min.x + if compact { 12.0 } else { 20.0 } * scale,
                        rect.center().y,
                    ),
                    Vec2::splat(if compact { 22.0 } else { 28.0 } * scale),
                );
                let sprite = self
                    .engine
                    .campaign()
                    .tiles
                    .values()
                    .find(|def| def.kind == "key" && def.key.is_some_and(|color| color == key))
                    .map(|def| def.sprite.clone())
                    .unwrap_or_else(|| {
                        json!(match key {
                            "yellow" => 29,
                            "blue" => 31,
                            _ => 30,
                        })
                    });
                if !self
                    .assets
                    .foreground(ui.painter(), icon_rect, &sprite, Color32::WHITE)
                {
                    theme::icon(ui.painter(), icon_rect, Icon::Key, color);
                }
                ui.painter().text(
                    egui::pos2(
                        rect.min.x + if compact { 27.0 } else { 39.0 } * scale,
                        rect.center().y,
                    ),
                    Align2::LEFT_CENTER,
                    number(&self.visual["player"]["keys"][key]),
                    FontId::proportional(19.0 * scale),
                    theme::colors(ui.ctx()).text,
                );
                response.on_hover_text(self.text(key));
            }
        });
    }

    fn inventory(&mut self, ui: &mut egui::Ui) {
        let scale = theme::scale(ui.ctx());
        section(ui, &self.text("inventory"), Icon::Compass);
        ui.add_space(if self.landscape { 5.0 } else { 10.0 } * scale);
        let slots = inventory_slots(&self.visual, &self.snapshot, self.engine.campaign());
        if slots.is_empty() {
            ui.label(
                RichText::new(self.text("empty_inventory")).color(theme::colors(ui.ctx()).muted),
            );
        }
        let mut command = None;
        let slot_count = slots.len();
        let cell_size = if self.landscape {
            40.0
        } else if self.classic_layout {
            let columns = if ui.available_width() >= 298.0 {
                5.0
            } else {
                3.0
            };
            // egui rounds each cell and gap separately. Leave a small allowance
            // so fractional desktop scaling cannot wrap the final column.
            (ui.available_width() - (columns - 1.0) * ui.spacing().item_spacing.x) / columns - 0.25
        } else {
            54.0
        };
        let grid = ui.horizontal_wrapped(|ui| {
            for (index, item) in slots.into_iter().enumerate() {
                let occupied = item.is_some();
                let usable = item
                    .as_ref()
                    .is_some_and(|item| item["usable"] == true || item["id"] == "hero_orb");
                let enabled = usable
                    && !self.busy()
                    && !self.enemy_list_open
                    && self.snapshot["pending_interaction"].is_null();
                let (rect, response) = ui.allocate_exact_size(
                    Vec2::splat(cell_size),
                    if enabled {
                        egui::Sense::click()
                    } else {
                        egui::Sense::hover()
                    },
                );
                let slot_id = format!("inventory_slot:{index}");
                self.record(&slot_id, &response);
                self.bounds.get_mut(&slot_id).expect("slot was recorded")["occupied"] =
                    json!(occupied);
                ui.painter().rect_filled(
                    rect,
                    10.0 * scale,
                    if occupied && response.hovered() {
                        theme::colors(ui.ctx())
                            .raised
                            .lerp_to_gamma(theme::colors(ui.ctx()).accent, 0.20)
                    } else {
                        theme::colors(ui.ctx()).raised
                    },
                );
                ui.painter().rect_stroke(
                    rect,
                    10.0 * scale,
                    Stroke::new(
                        1.0,
                        if occupied && response.hovered() {
                            theme::colors(ui.ctx()).metal
                        } else {
                            theme::colors(ui.ctx()).border
                        },
                    ),
                    egui::StrokeKind::Inside,
                );
                let Some(item) = item else { continue };
                let id = item["id"].as_str().unwrap_or("");
                let name = entity_name(
                    &self.locale,
                    "items",
                    id,
                    item["name"].as_str().unwrap_or(id),
                );
                self.assets.foreground(
                    ui.painter(),
                    rect.shrink(if self.landscape { 5.0 } else { 10.0 } * scale),
                    &item["sprite"],
                    Color32::WHITE,
                );
                if let Some(n) = item["charges"].as_u64() {
                    let badge = Rect::from_min_size(
                        rect.right_bottom() - Vec2::new(24.0, 18.0) * scale,
                        Vec2::new(24.0, 18.0) * scale,
                    );
                    ui.painter()
                        .rect_filled(badge, 5.0 * scale, theme::colors(ui.ctx()).surface);
                    ui.painter().text(
                        badge.center(),
                        Align2::CENTER_CENTER,
                        n.to_string(),
                        FontId::proportional(13.0 * scale),
                        theme::colors(ui.ctx()).metal,
                    );
                }
                self.record(&format!("item:{id}"), &response);
                if response
                    .on_hover_text(item_tooltip(&self.locale, &item, &name))
                    .clicked()
                    && enabled
                {
                    if id == "hero_orb" {
                        self.open_enemy_list();
                    } else if item["usage"]["target_floor"].is_string() {
                        self.settings = true;
                        self.notify(self.text("flying_hint"));
                    } else {
                        command = Some(Command::UseItem {
                            item: id.into(),
                            floor: None,
                        });
                    }
                }
            }
        });
        let viewport = grid.response.rect.intersect(ui.clip_rect());
        self.bounds.insert(
            "inventory_grid".into(),
            json!({"x":grid.response.rect.min.x,"y":grid.response.rect.min.y,
                "w":grid.response.rect.width(),"h":grid.response.rect.height(),"slots":slot_count,
                "visible":{"x":viewport.min.x,"y":viewport.min.y,"w":viewport.width(),"h":viewport.height()}}),
        );
        if let Some(c) = command {
            self.apply_command(c);
        }
    }

    fn append_visual_activity(&mut self, text: Value, log_id: Option<u64>) -> bool {
        append_visible_activity(&mut self.visual, &self.snapshot, text, log_id)
    }

    fn activity_battle(&self, index: usize) -> Option<Value> {
        self.visual["log"].as_array()?.get(index)?;
        let id = self.visual["log_start"]
            .as_u64()
            .unwrap_or(0)
            .saturating_add(index as u64);
        self.visual["battle_log"]
            .as_array()?
            .iter()
            .find(|record| record["log_id"].as_u64() == Some(id))
            .cloned()
    }

    fn activity_expansion_id(&self, log_id: u64) -> egui::Id {
        egui::Id::new((
            "activity_battle",
            self.visual["campaign_id"].as_str().unwrap_or(""),
            log_id,
        ))
    }

    fn open_recent_activity(&mut self, index: usize) {
        if let Some(battle) = self.activity_battle(index) {
            let id = self.activity_expansion_id(battle["log_id"].as_u64().unwrap_or(0));
            self.context.data_mut(|data| data.insert_temp(id, true));
        }
        self.open_journal_history();
    }

    fn compact_activity_preview(&mut self, ui: &mut egui::Ui) {
        let scale = theme::scale(ui.ctx());
        let available = !self.busy() && self.snapshot["pending_interaction"].is_null();
        let preview = ui.scope(|ui| {
            ui.spacing_mut().item_spacing.y = 0.0;
            let (rect, header) = ui.allocate_exact_size(
                Vec2::new(ui.available_width(), 18.0 * scale),
                if available {
                    egui::Sense::click()
                } else {
                    egui::Sense::hover()
                },
            );
            theme::icon(
                ui.painter(),
                Rect::from_center_size(
                    egui::pos2(rect.left() + 7.0 * scale, rect.center().y),
                    Vec2::splat(14.0 * scale),
                ),
                Icon::Book,
                theme::colors(ui.ctx()).muted,
            );
            ui.painter().text(
                egui::pos2(rect.left() + 20.0 * scale, rect.center().y),
                Align2::LEFT_CENTER,
                self.text("journal_recent_short"),
                FontId::proportional(11.0 * scale),
                theme::colors(ui.ctx()).muted,
            );
            theme::icon(
                ui.painter(),
                Rect::from_center_size(
                    egui::pos2(rect.right() - 7.0 * scale, rect.center().y),
                    Vec2::splat(14.0 * scale),
                ),
                Icon::ArrowRight,
                theme::colors(ui.ctx()).text,
            );
            self.record("journal_preview_open", &header);
            if header.on_hover_text(self.text("journal_expand")).clicked() {
                self.open_journal_history();
            }
            ui.add_space(2.0 * scale);
            let entries = self.visual["log"].as_array().cloned().unwrap_or_default();
            for (order, (index, entry)) in entries.iter().enumerate().rev().take(2).enumerate() {
                if order > 0 {
                    ui.add_space(3.0 * scale);
                }
                let text = translate_text(&self.locale, entry.as_str().unwrap_or(""));
                let (rect, row) = ui.allocate_exact_size(
                    Vec2::new(ui.available_width(), 18.0 * scale),
                    if available {
                        egui::Sense::click()
                    } else {
                        egui::Sense::hover()
                    },
                );
                ui.painter()
                    .rect_filled(rect, 4.0 * scale, theme::colors(ui.ctx()).raised);
                let mut job = egui::text::LayoutJob::simple(
                    text.clone(),
                    FontId::proportional(13.0 * scale),
                    theme::colors(ui.ctx()).text,
                    (rect.width() - 10.0 * scale).max(1.0),
                );
                job.wrap.max_rows = 1;
                let galley = ui.painter().layout_job(job);
                ui.painter().galley(
                    egui::pos2(
                        rect.left() + 5.0 * scale,
                        rect.center().y - galley.size().y / 2.0,
                    ),
                    galley,
                    theme::colors(ui.ctx()).text,
                );
                self.record(&format!("journal_preview_entry:{index}"), &row);
                if let Some(battle) = self.activity_battle(index) {
                    self.bounds
                        .get_mut(&format!("journal_preview_entry:{index}"))
                        .expect("row was recorded")["battle_log_id"] = battle["log_id"].clone();
                }
                if row.on_hover_text(text).clicked() {
                    self.open_recent_activity(index);
                }
            }
        });
        self.record("journal_preview", &preview.response);
    }

    fn journal(&mut self, ui: &mut egui::Ui) {
        section(ui, &self.text("journal"), Icon::Book);
        ui.add_space(10.0);
        let heading = theme::caption(ui, &self.text("journal_recent_actions"));
        self.record("journal_log", &heading);
        ui.add_space(6.0);
        let entries = self.visual["log"].as_array().cloned().unwrap_or_default();
        if entries.is_empty() {
            ui.label(
                RichText::new(self.text("journal_log_empty"))
                    .size(14.0)
                    .color(theme::colors(ui.ctx()).muted),
            );
        }
        for (index, entry) in entries.iter().enumerate().rev().take(3) {
            let text = translate_text(&self.locale, entry.as_str().unwrap_or(""));
            let width = ui.available_width();
            let row = egui::Frame::new()
                .fill(theme::colors(ui.ctx()).raised)
                .corner_radius(5)
                .inner_margin(egui::Margin::symmetric(8, 3))
                .show(ui, |ui| {
                    ui.set_width((width - 16.0).max(1.0));
                    ui.add(
                        egui::Label::new(
                            RichText::new(&text)
                                .size(14.0)
                                .color(theme::colors(ui.ctx()).muted),
                        )
                        .truncate(),
                    )
                });
            self.record(&format!("journal_preview_entry:{index}"), &row.response);
            if let Some(battle) = self.activity_battle(index) {
                self.bounds
                    .get_mut(&format!("journal_preview_entry:{index}"))
                    .expect("row was recorded")["battle_log_id"] = battle["log_id"].clone();
            }
            let click = ui.interact(
                row.response.rect,
                row.response.id.with("open"),
                if !self.busy() && self.snapshot["pending_interaction"].is_null() {
                    egui::Sense::click()
                } else {
                    egui::Sense::hover()
                },
            );
            if click.on_hover_text(text).clicked() {
                self.open_recent_activity(index);
            }
            ui.add_space(3.0);
        }
        ui.add_space(10.0);
        let available = !self.busy() && self.snapshot["pending_interaction"].is_null();
        let expand = ui
            .add_enabled_ui(available, |ui| {
                theme::action(ui, self.text("journal_expand"), Icon::Book, false)
            })
            .inner;
        self.record("journal_expand", &expand);
        if expand.clicked() {
            self.open_journal_history();
        }
        if visual_has_wisdom_orb(&self.visual) {
            ui.add_space(6.0);
            let wisdom = ui
                .add_enabled_ui(available, |ui| {
                    theme::action(ui, self.text("journal_wisdom"), Icon::Compass, false)
                })
                .inner;
            self.record("journal_wisdom", &wisdom);
            self.record("journal_clues", &wisdom);
            if wisdom.clicked() {
                self.apply_command(Command::UseItem {
                    item: "wisdom_orb".into(),
                    floor: None,
                });
            }
        }
    }

    fn open_journal_history(&mut self) {
        self.route.clear();
        self.settings = false;
        self.enemy_list_open = false;
        self.journal_open = true;
    }

    fn open_enemy_list(&mut self) {
        if !visual_has_hero_orb(&self.visual)
            || self.busy()
            || !self.snapshot["pending_interaction"].is_null()
        {
            return;
        }
        self.route.clear();
        self.settings = false;
        self.journal_open = false;
        self.enemy_list_open = true;
    }

    fn enemy_list_button(&mut self, ui: &mut egui::Ui) {
        self.enemy_list_button_sized(ui, None);
    }

    fn enemy_list_button_sized(&mut self, ui: &mut egui::Ui, width: Option<f32>) {
        let owned = visual_has_hero_orb(&self.visual);
        let available = owned && !self.busy() && self.snapshot["pending_interaction"].is_null();
        let response = ui
            .add_enabled_ui(available, |ui| {
                theme::action_sized(ui, "", Icon::Compass, false, width)
            })
            .inner;
        self.record("enemy_list_open", &response);
        self.bounds
            .get_mut("enemy_list_open")
            .expect("button was recorded")["enabled"] = json!(available);
        if response
            .on_hover_text(if owned {
                self.text("enemy_list")
            } else {
                self.text("orb_required")
            })
            .clicked()
        {
            self.open_enemy_list();
        }
    }

    fn enemy_list_dialog(&mut self) {
        if !self.enemy_list_open {
            return;
        }
        if !visual_has_hero_orb(&self.visual) {
            self.enemy_list_open = false;
            return;
        }
        // Inspect only this floor using the board's player-visible boundary,
        // then group identical revealed profiles rather than listing coordinates.
        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
        let height = self.visual["height"].as_u64().unwrap_or(11) as usize;
        let mut entries = vec![];
        for y in 0..height {
            for x in 0..width {
                let inspection = self.engine.inspect_player_tile(x, y);
                if inspection["enemy"].is_object() {
                    entries.push(inspection);
                }
            }
        }
        let encounter_count = entries.len();
        let entries = group_floor_enemies(entries, &self.locale);
        let viewport = self.context.input(|i| i.viewport_rect());
        let scale = theme::scale(&self.context);
        let title = self
            .text("enemy_list_title")
            .replace("{floor}", &self.visual["floor"].to_string());
        let mut close = false;
        let response = egui::Modal::new(egui::Id::new("floor_enemy_list"))
            .backdrop_color(Color32::from_black_alpha(160))
            .frame(theme::frame(&self.context).inner_margin((12.0 * scale) as i8))
            .show(&self.context.clone(), |ui| {
                ui.set_width((viewport.width() - 56.0 * scale).clamp(240.0, 860.0 * scale));
                let heading = ui.scope(|ui| section(ui, &title, Icon::Compass));
                self.record("enemy_list_heading", &heading.response);
                ui.add_space(4.0 * scale);
                ui.label(RichText::new(self.text("enemy_list_count")
                    .replace("{count}", &encounter_count.to_string())
                    .replace("{groups}", &entries.len().to_string()))
                    .size(13.0 * scale).color(theme::colors(ui.ctx()).muted));
                ui.add_space(10.0 * scale);
                let table = ui.available_width() >= 620.0 * scale;
                let metrics = [
                    ("hp", "health_short", Icon::Heart, theme::RED),
                    ("attack", "attack_short", Icon::Sword, theme::colors(ui.ctx()).metal),
                    ("defense", "defense_short", Icon::Shield, theme::BLUE),
                    ("gold", "gold", Icon::Coin, theme::GOLD),
                    ("damage", "journal_battle_damage", Icon::Heart, theme::GREEN),
                ];
                // Shared column widths keep numeric values aligned across all
                // rows. Leave the name column the remaining table width.
                let metric_widths: Vec<f32> = metrics.iter().map(|(key, label, _, _)| {
                    let label_width = ui.painter().layout_no_wrap(self.text(label),
                        FontId::proportional(12.0 * scale), theme::colors(ui.ctx()).muted).size().x;
                    let value_width = entries.iter().map(|group| ui.painter().layout_no_wrap(
                        number(&group.inspection["enemy"][key]), FontId::proportional(18.0 * scale),
                        theme::colors(ui.ctx()).text).size().x).fold(0.0_f32, f32::max);
                    (label_width + 26.0 * scale).max(value_width + 22.0 * scale).max(66.0 * scale)
                }).collect();
                let metrics_width: f32 = metric_widths.iter().sum();
                let table = table && ui.available_width() - metrics_width >= 160.0 * scale;
                let name_width = ui.available_width() - metrics_width;
                if table {
                    let (header, response) = ui.allocate_exact_size(Vec2::new(ui.available_width(), 28.0 * scale), egui::Sense::hover());
                    self.record("enemy_list_columns", &response);
                    ui.painter().text(egui::pos2(header.left() + 10.0 * scale, header.center().y), Align2::LEFT_CENTER,
                        self.text("enemy_list_enemy"), FontId::proportional(13.0 * scale), theme::colors(ui.ctx()).muted);
                    let mut x = header.left() + name_width;
                    for ((_, label, icon, color), width) in metrics.iter().zip(&metric_widths) {
                        let column = Rect::from_min_size(egui::pos2(x, header.top()), Vec2::new(*width, header.height()));
                        enemy_overview_header(ui, column, &self.text(label), *icon, *color, scale);
                        x += width;
                    }
                    ui.add_space(3.0 * scale);
                }
                let scroll = egui::ScrollArea::vertical()
                    .id_salt("floor_enemy_list_entries")
                    .max_height((viewport.height() - 172.0 * scale - if table { 31.0 * scale } else { 0.0 }).max(70.0))
                    .show(ui, |ui| {
                        if entries.is_empty() {
                            ui.label(self.text("enemy_list_empty"));
                        }
                        for (index, group) in entries.iter().enumerate() {
                            let entry = &group.inspection;
                            let enemy = &entry["enemy"];
                            let row_height = if table { 56.0 } else { 134.0 } * scale;
                            let (rect, response) = ui.allocate_exact_size(Vec2::new(ui.available_width(), row_height), egui::Sense::hover());
                            let colors = theme::colors(ui.ctx());
                            ui.painter().rect_filled(rect, 6.0, if index % 2 == 0 { colors.raised } else { colors.surface.lerp_to_gamma(colors.raised, 0.42) });
                            let heading_rect = if table { Rect::from_min_size(rect.min, Vec2::new(name_width, row_height)) }
                                else { Rect::from_min_size(rect.min, Vec2::new(rect.width(), 42.0 * scale)) };
                            let portrait = Rect::from_center_size(egui::pos2(heading_rect.left() + 27.0 * scale, heading_rect.center().y), Vec2::splat(34.0 * scale));
                            self.assets.foreground(ui.painter(), portrait, &entry["sprite"], Color32::WHITE);
                            let quantity = format!("×{}", group.count);
                            let quantity_galley = ui.painter().layout_no_wrap(quantity, FontId::proportional(13.0 * scale), colors.muted);
                            let quantity_x = heading_rect.right() - 10.0 * scale - quantity_galley.size().x;
                            let name_x = portrait.right() + 10.0 * scale;
                            let mut job = egui::text::LayoutJob::simple(group.name.clone(), FontId::proportional(16.0 * scale), colors.text,
                                (quantity_x - name_x - 8.0 * scale).max(1.0));
                            job.wrap.max_rows = if table { 2 } else { 1 };
                            let galley = ui.painter().layout_job(job);
                            ui.painter().galley(egui::pos2(name_x, heading_rect.center().y - galley.size().y / 2.0), galley, colors.text);
                            ui.painter().galley(egui::pos2(quantity_x, heading_rect.center().y - quantity_galley.size().y / 2.0), quantity_galley, colors.muted);
                            let mut metric_rects = BTreeMap::new();
                            let mut metric_x = rect.left() + name_width;
                            for (metric_index, (key, label, icon, color)) in metrics.iter().enumerate() {
                                let metric_rect = if table {
                                    let result = Rect::from_min_size(egui::pos2(metric_x, rect.top()), Vec2::new(metric_widths[metric_index], rect.height()));
                                    metric_x += metric_widths[metric_index];
                                    result
                                } else {
                                    let column = metric_index % 3;
                                    let row = metric_index / 3;
                                    let cell_width = rect.width() / 3.0;
                                    Rect::from_min_size(egui::pos2(rect.left() + column as f32 * cell_width,
                                        rect.top() + (44.0 + row as f32 * 44.0) * scale), Vec2::new(cell_width, 42.0 * scale))
                                };
                                let color = if *key == "damage" && enemy["can_win"] != true { theme::RED } else { *color };
                                let info = enemy_overview_value(ui, metric_rect, &self.text(label), &number(&enemy[key]), *icon, color, scale, !table, *key == "damage");
                                metric_rects.insert(*key, info);
                            }
                            if !table {
                                let status = Rect::from_min_size(egui::pos2(rect.left() + 2.0 * rect.width() / 3.0, rect.top() + 88.0 * scale), Vec2::new(rect.width() / 3.0, 42.0 * scale));
                                ui.painter().text(status.center(), Align2::CENTER_CENTER, self.text(if enemy["can_win"] == true { "enemy_list_safe" } else { "enemy_list_unsafe" }),
                                    FontId::proportional(12.0 * scale), if enemy["can_win"] == true { theme::GREEN } else { theme::RED });
                            }
                            let key = format!("enemy_list_entry:{index}");
                            self.record(&key, &response);
                            let recorded = self.bounds.get_mut(&key).expect("entry was recorded");
                            for field in ["hp", "attack", "defense", "damage", "gold", "can_win"] {
                                recorded[field] = enemy[field].clone();
                            }
                            recorded["name"] = json!(group.name);
                            recorded["count"] = json!(group.count);
                            recorded["metrics"] = json!(metric_rects);
                            let reason = enemy["reason"].as_str().unwrap_or("");
                            response.on_hover_text(if reason.is_empty() { group.name.clone() } else { format!("{}\n{}", group.name, translate_text(&self.locale, reason)) });
                            ui.add_space(5.0 * scale);
                        }
                    });
                let rect = scroll.inner_rect.intersect(ui.clip_rect());
                self.bounds.insert("enemy_list_viewport".into(), json!({
                    "x":rect.min.x,"y":rect.min.y,"w":rect.width(),"h":rect.height(),
                    "offset_y":scroll.state.offset.y,"content_h":scroll.content_size.y,"entries":entries.len(),"encounters":encounter_count,"table":table
                }));
                ui.add_space(7.0 * scale);
                ui.label(RichText::new(self.text("enemy_list_damage_help")).size(12.0 * scale).color(theme::colors(ui.ctx()).muted));
                ui.add_space(5.0 * scale);
                let button = theme::action(ui, self.text("close"), Icon::ArrowLeft, true);
                self.record("enemy_list_close", &button);
                close = button.clicked();
            });
        self.record("enemy_list_dialog", &response.response);
        if close || response.should_close() {
            self.enemy_list_open = false;
        }
    }

    fn journal_history_dialog(&mut self) {
        if !self.journal_open {
            return;
        }
        let entries = self.visual["log"].as_array().cloned().unwrap_or_default();
        let viewport = self.context.input(|i| i.viewport_rect());
        let scale = theme::scale(&self.context);
        let mut close = false;
        let response = egui::Modal::new(egui::Id::new("journal_history"))
            .backdrop_color(Color32::from_black_alpha(160))
            .frame(theme::frame(&self.context).inner_margin((20.0 * scale).round() as i8))
            .show(&self.context.clone(), |ui| {
                ui.set_width((viewport.width() - 72.0 * scale).clamp(240.0 * scale, 620.0 * scale));
                let heading = ui.scope(|ui| section(ui, &self.text("journal_history"), Icon::Book));
                self.record("journal_history_heading", &heading.response);
                ui.add_space(8.0 * scale);
                ui.label(
                    RichText::new(
                        self.text("journal_history_count")
                            .replace("{count}", &entries.len().to_string()),
                    )
                    .size(14.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
                );
                ui.add_space(12.0 * scale);
                let scroll = egui::ScrollArea::vertical()
                    .id_salt("journal_history_entries")
                    .max_height((viewport.height() - 230.0 * scale).max(100.0 * scale))
                    .show(ui, |ui| {
                        if entries.is_empty() {
                            ui.label(self.text("journal_log_empty"));
                        }
                        for (index, entry) in entries.iter().enumerate().rev() {
                            let width = ui.available_width();
                            let battle = self.activity_battle(index);
                            let horizontal_padding = (10.0 * scale).round() as i8;
                            let row = egui::Frame::new()
                                .fill(theme::colors(ui.ctx()).raised)
                                .corner_radius((6.0 * scale).round() as u8)
                                .inner_margin(egui::Margin::symmetric(
                                    horizontal_padding,
                                    (7.0 * scale).round() as i8,
                                ))
                                .show(ui, |ui| {
                                    ui.set_width(
                                        (width - 2.0 * f32::from(horizontal_padding)).max(1.0),
                                    );
                                    ui.add(
                                        egui::Label::new(
                                            RichText::new(translate_text(
                                                &self.locale,
                                                entry.as_str().unwrap_or(""),
                                            ))
                                            .size(17.0 * scale)
                                            .color(theme::colors(ui.ctx()).text),
                                        )
                                        .wrap(),
                                    );
                                    if let Some(battle) = &battle {
                                        let log_id = battle["log_id"].as_u64().unwrap_or(0);
                                        let expansion_id = self.activity_expansion_id(log_id);
                                        let mut expanded = ui
                                            .ctx()
                                            .data(|data| data.get_temp::<bool>(expansion_id))
                                            .unwrap_or(false);
                                        ui.add_space(3.0 * scale);
                                        let (rect, toggle) = ui.allocate_exact_size(
                                            Vec2::new(ui.available_width(), 20.0 * scale),
                                            egui::Sense::click(),
                                        );
                                        let center =
                                            egui::pos2(rect.left() + 5.0 * scale, rect.center().y);
                                        let points = if expanded {
                                            vec![
                                                center + Vec2::new(-4.0, -2.0) * scale,
                                                center + Vec2::new(4.0, -2.0) * scale,
                                                center + Vec2::new(0.0, 3.0) * scale,
                                            ]
                                        } else {
                                            vec![
                                                center + Vec2::new(-2.0, -4.0) * scale,
                                                center + Vec2::new(-2.0, 4.0) * scale,
                                                center + Vec2::new(3.0, 0.0) * scale,
                                            ]
                                        };
                                        ui.painter().add(egui::Shape::convex_polygon(
                                            points,
                                            theme::colors(ui.ctx()).metal,
                                            Stroke::NONE,
                                        ));
                                        ui.painter().text(
                                            egui::pos2(rect.left() + 16.0 * scale, rect.center().y),
                                            Align2::LEFT_CENTER,
                                            self.text("journal_battle_details"),
                                            FontId::proportional(14.0 * scale),
                                            theme::colors(ui.ctx()).metal,
                                        );
                                        self.record(
                                            &format!("journal_battle_toggle:{log_id}"),
                                            &toggle,
                                        );
                                        if toggle.clicked() {
                                            expanded = !expanded;
                                            ui.ctx().data_mut(|data| {
                                                data.insert_temp(expansion_id, expanded)
                                            });
                                        }
                                        if expanded {
                                            ui.add_space(7.0 * scale);
                                            self.journal_battle_details(ui, battle);
                                        }
                                    }
                                });
                            self.record(&format!("journal_history_entry:{index}"), &row.response);
                            ui.add_space(6.0 * scale);
                        }
                    });
                let rect = scroll.inner_rect.intersect(ui.clip_rect());
                self.bounds.insert(
                    "journal_history_viewport".into(),
                    json!({
                        "x": rect.min.x, "y": rect.min.y, "w": rect.width(), "h": rect.height(),
                        "offset_y": scroll.state.offset.y, "content_h": scroll.content_size.y,
                        "entries": entries.len()
                    }),
                );
                ui.add_space(14.0 * scale);
                let button = theme::action(ui, self.text("close"), Icon::ArrowLeft, true);
                self.record("journal_history_close", &button);
                close = button.clicked();
            });
        self.record("journal_history", &response.response);
        if close || response.should_close() {
            self.journal_open = false;
        }
    }

    fn journal_battle_details(&mut self, ui: &mut egui::Ui, battle: &Value) {
        let scale = theme::scale(ui.ctx());
        let details = ui.scope(|ui| {
            let won = battle["outcome"] == "defeated";
            ui.label(
                RichText::new(format!(
                    "{} · {}",
                    translate_text(&self.locale, battle["enemy_name"].as_str().unwrap_or("")),
                    self.text(if won {
                        "journal_battle_defeated"
                    } else {
                        "journal_battle_lost"
                    }),
                ))
                .size(15.0 * scale)
                .strong()
                .color(if won { theme::GREEN } else { theme::RED }),
            );
            let mut location = self.text("journal_location");
            for key in ["cycle", "floor", "x", "y"] {
                location = location.replace(&format!("{{{key}}}"), &battle[key].to_string());
            }
            ui.label(
                RichText::new(location)
                    .size(12.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
            );
            ui.horizontal_wrapped(|ui| {
                for (key, label) in [
                    ("enemy_hp", "health_short"),
                    ("enemy_attack", "attack_short"),
                    ("enemy_defense", "defense_short"),
                ] {
                    ui.label(
                        RichText::new(format!("{} {}", self.text(label), number(&battle[key])))
                            .size(14.0 * scale),
                    );
                }
            });
            ui.horizontal_wrapped(|ui| {
                ui.label(
                    RichText::new(format!(
                        "{} {}",
                        self.text("journal_battle_damage"),
                        number(&battle["damage"])
                    ))
                    .size(14.0 * scale)
                    .color(theme::RED),
                );
                ui.label(
                    RichText::new(format!(
                        "{} {}",
                        self.text("journal_battle_reward"),
                        number(&battle["reward"])
                    ))
                    .size(14.0 * scale)
                    .color(theme::GOLD),
                );
            });
            ui.add_space(3.0 * scale);
            ui.label(
                RichText::new(self.text("journal_battle_hero_stats"))
                    .size(12.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
            );
            ui.horizontal_wrapped(|ui| {
                for (key, label) in [
                    ("hp", "health_short"),
                    ("attack", "attack_short"),
                    ("defense", "defense_short"),
                ] {
                    ui.label(
                        RichText::new(format!(
                            "{} {}",
                            self.text(label),
                            number(&battle["hero_before"][key])
                        ))
                        .size(14.0 * scale),
                    );
                }
            });
            ui.label(
                RichText::new(
                    self.text("journal_battle_hero_hp")
                        .replace("{before}", &number(&battle["hero_before"]["hp"]))
                        .replace("{after}", &number(&battle["hero_after_hp"])),
                )
                .size(14.0 * scale),
            );
            ui.label(
                RichText::new(
                    self.text("journal_battle_strikes")
                        .replace("{hero}", &number(&battle["hero_strikes"]))
                        .replace("{enemy}", &number(&battle["enemy_strikes"])),
                )
                .size(12.0 * scale)
                .color(theme::colors(ui.ctx()).muted),
            );
        });
        let key = format!(
            "journal_battle_details:{}",
            battle["log_id"].as_u64().unwrap_or(0)
        );
        self.record(&key, &details.response);
        let bound = self.bounds.get_mut(&key).expect("details were recorded");
        for field in [
            "log_id",
            "enemy_hp",
            "enemy_attack",
            "enemy_defense",
            "damage",
            "reward",
            "hero_after_hp",
            "hero_before",
            "outcome",
        ] {
            bound[field] = battle[field].clone();
        }
    }

    fn journal_clues(&mut self, ui: &mut egui::Ui, entries: &[Value]) {
        let scale = theme::scale(ui.ctx());
        if entries.is_empty() {
            ui.label(
                RichText::new(self.text("journal_empty"))
                    .size(15.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
            );
        }
        // The original item presents the 24 clue slots in their fixed source
        // order, rather than encounter recency.
        for (index, entry) in entries.iter().enumerate() {
            let title = translate_text(&self.locale, entry["title"].as_str().unwrap_or(""));
            if !title.is_empty() {
                ui.label(
                    RichText::new(title)
                        .size(17.0 * scale)
                        .strong()
                        .color(theme::colors(ui.ctx()).metal),
                );
            }
            let location = self
                .text("journal_location")
                .replace("{cycle}", &entry["cycle"].to_string())
                .replace("{floor}", &entry["floor"].to_string())
                .replace("{x}", &entry["x"].to_string())
                .replace("{y}", &entry["y"].to_string());
            ui.label(
                RichText::new(location)
                    .size(13.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
            );
            ui.add_space(4.0 * scale);
            let clue = ui.add(
                egui::Label::new(
                    RichText::new(translate_text(
                        &self.locale,
                        entry["text"].as_str().unwrap_or(""),
                    ))
                    .size(17.0 * scale)
                    .color(theme::colors(ui.ctx()).text),
                )
                .wrap(),
            );
            self.record(&format!("journal_clue:{index}"), &clue);
            ui.add_space(16.0 * scale);
        }
    }

    fn journal_dialog(&mut self) {
        let entries = if visual_has_wisdom_orb(&self.visual) {
            self.active
                .as_ref()
                .and_then(|active| active.effect["entries"].as_array())
                .cloned()
                .unwrap_or_default()
        } else {
            vec![]
        };
        let viewport = self.context.input(|i| i.viewport_rect());
        let scale = theme::scale(&self.context);
        let mut close = false;
        let response = egui::Modal::new(egui::Id::new("wisdom_journal"))
            .backdrop_color(Color32::from_black_alpha(160))
            .frame(theme::frame(&self.context).inner_margin((24.0 * scale).round() as i8))
            .show(&self.context.clone(), |ui| {
                ui.set_width((viewport.width() - 96.0 * scale).clamp(260.0 * scale, 580.0 * scale));
                section(ui, &self.text("journal"), Icon::Book);
                ui.add_space(8.0 * scale);
                ui.label(
                    RichText::new(self.text("journal_subtitle"))
                        .size(14.0 * scale)
                        .color(theme::colors(ui.ctx()).muted),
                );
                ui.add_space(16.0 * scale);
                let scroll = egui::ScrollArea::vertical()
                    .id_salt("wisdom_journal_entries")
                    .max_height((viewport.height() - 300.0 * scale).max(100.0 * scale))
                    .show(ui, |ui| self.journal_clues(ui, &entries));
                let rect = scroll.inner_rect.intersect(ui.clip_rect());
                self.bounds.insert(
                    "wisdom_journal_viewport".into(),
                    json!({
                        "x": rect.min.x, "y": rect.min.y, "w": rect.width(), "h": rect.height(),
                        "offset_y": scroll.state.offset.y, "content_h": scroll.content_size.y,
                        "entries": entries.len()
                    }),
                );
                ui.add_space(16.0 * scale);
                let button = theme::action(ui, self.text("close"), Icon::ArrowLeft, true);
                self.record("journal_close", &button);
                close = button.clicked();
            });
        self.record("journal_dialog", &response.response);
        if close || response.should_close() {
            self.finish_effect();
        }
    }

    fn inspection(&mut self, ui: &mut egui::Ui) {
        if self.landscape {
            self.compact_inspection(ui);
            return;
        }
        let scale = theme::scale(ui.ctx());
        section(ui, &self.text("inspect"), Icon::Compass);
        ui.add_space(16.0 * scale);
        let target = self.selected.filter(|_| !self.busy() || self.travel_only());
        let Some((x, y)) = target else {
            ui.label(
                RichText::new(self.text("inspect_hint"))
                    .size(17.0 * scale)
                    .color(theme::colors(ui.ctx()).muted),
            );
            if self.visual["forecasts_unlocked"] != true {
                ui.add_space(10.0 * scale);
                let hint = ui.label(
                    RichText::new(self.text("orb_required"))
                        .size(15.0 * scale)
                        .color(theme::colors(ui.ctx()).muted),
                );
                self.record("inspection_locked_hint", &hint);
            }
            return;
        };
        let info = self.engine.inspect(x, y);
        let id = info["id"].as_u64().unwrap_or(6).to_string();
        let name = entity_name(
            &self.locale,
            "tiles",
            &id,
            info["name"].as_str().unwrap_or(""),
        );
        let target_panel = ui.horizontal(|ui| {
            let (sprite, _) =
                ui.allocate_exact_size(Vec2::splat(54.0 * scale), egui::Sense::hover());
            ui.painter()
                .rect_filled(sprite, 10.0 * scale, theme::colors(ui.ctx()).raised);
            let portrait = &self.visual["tile_defs"][&id]["sprite"];
            if ["key", "item", "equipment", "enemy", "npc", "shop"]
                .contains(&info["kind"].as_str().unwrap_or(""))
            {
                self.assets.foreground(
                    ui.painter(),
                    sprite.shrink(7.0 * scale),
                    portrait,
                    Color32::WHITE,
                );
            } else {
                self.assets.tile(
                    ui.painter(),
                    sprite.shrink(7.0 * scale),
                    portrait,
                    Color32::WHITE,
                );
            }
            ui.vertical(|ui| {
                ui.label(RichText::new(name).size(21.0 * scale).strong());
                ui.label(
                    RichText::new(format!("{x}, {y}"))
                        .size(14.0 * scale)
                        .color(theme::colors(ui.ctx()).muted),
                );
            });
        });
        self.record("inspection_target", &target_panel.response);
        self.record("tile_inspection", &target_panel.response);
        if let Some(target) = self.bounds.get_mut("inspection_target") {
            target["tile_x"] = json!(x);
            target["tile_y"] = json!(y);
            target["kind"] = info["kind"].clone();
        }
        let enemy = &info["enemy"];
        if enemy.is_object() {
            ui.add_space(16.0 * scale);
            let width = (ui.available_width() - 8.0 * scale) / 2.0;
            for row in [
                [
                    ("hp", "health", theme::RED, Icon::Heart),
                    (
                        "attack",
                        "attack",
                        theme::colors(ui.ctx()).metal,
                        Icon::Sword,
                    ),
                ],
                [
                    ("defense", "defense", theme::BLUE, Icon::Shield),
                    ("gold", "gold", theme::GREEN, Icon::Coin),
                ],
            ] {
                ui.horizontal_top(|ui| {
                    for (key, label, color, icon) in row {
                        metric(
                            ui,
                            width,
                            &self.text(label),
                            &number(&enemy[key]),
                            color,
                            icon,
                            true,
                        );
                    }
                });
                ui.add_space(4.0 * scale);
            }
            ui.add_space(10.0 * scale);
            let forecast = theme::caption(ui, &self.text("combat_forecast"));
            self.record("inspection_forecast", &forecast);
            let survives = enemy["can_win"].as_bool().unwrap_or(false);
            let color = if survives { theme::GREEN } else { theme::RED };
            ui.horizontal(|ui| {
                ui.label(
                    RichText::new(self.text("damage"))
                        .size(16.0 * scale)
                        .color(theme::colors(ui.ctx()).muted),
                );
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    ui.label(
                        RichText::new(number(&enemy["damage"]))
                            .size(26.0 * scale)
                            .strong()
                            .color(color),
                    );
                });
            });
            ui.label(
                RichText::new(self.text(if survives {
                    "forecast_survive"
                } else {
                    "forecast_unsafe"
                }))
                .size(15.0 * scale)
                .color(color),
            );
            if let Some(reason) = enemy["reason"].as_str().filter(|s| !s.is_empty()) {
                ui.label(
                    RichText::new(translate_text(&self.locale, reason))
                        .size(15.0 * scale)
                        .color(theme::RED),
                );
            }
        } else if let Some(encounter) = info["encountered_enemy"].as_object() {
            ui.add_space(16.0 * scale);
            let contact = ui.scope(|ui| {
                let width = (ui.available_width() - 8.0 * scale) / 2.0;
                metric(
                    ui,
                    ui.available_width(),
                    &self.text("health"),
                    &number(&encounter["hp"]),
                    theme::RED,
                    Icon::Heart,
                    true,
                );
                ui.add_space(4.0 * scale);
                ui.horizontal_top(|ui| {
                    for (key, label, color, icon) in [
                        (
                            "attack",
                            "attack",
                            theme::colors(ui.ctx()).metal,
                            Icon::Sword,
                        ),
                        ("defense", "defense", theme::BLUE, Icon::Shield),
                    ] {
                        metric(
                            ui,
                            width,
                            &self.text(label),
                            &number(&encounter[key]),
                            color,
                            icon,
                            true,
                        );
                    }
                });
                ui.add_space(8.0 * scale);
                ui.label(
                    RichText::new(self.text("encounter_forecast_locked"))
                        .size(13.0 * scale)
                        .color(theme::colors(ui.ctx()).muted),
                );
            });
            self.record("inspection_contact", &contact.response);
        } else {
            ui.add_space(12.0 * scale);
            ui.label(translate_text(
                &self.locale,
                info["description"].as_str().unwrap_or(""),
            ));
            if info["details_locked"] == true {
                ui.add_space(8.0 * scale);
                ui.label(
                    RichText::new(self.text("orb_required")).color(theme::colors(ui.ctx()).muted),
                );
            }
        }
    }

    fn compact_inspection(&mut self, ui: &mut egui::Ui) {
        if let Some((x, y)) = self.selected.filter(|_| !self.busy() || self.travel_only()) {
            let info = self.engine.inspect(x, y);
            let id = info["id"].as_u64().unwrap_or(6).to_string();
            let name = entity_name(
                &self.locale,
                "tiles",
                &id,
                info["name"].as_str().unwrap_or(""),
            );
            let portrait = self.visual["tile_defs"][&id]["sprite"].clone();
            let heading = self.compact_inspection_heading(
                ui,
                &name,
                &portrait,
                ["key", "item", "equipment", "enemy", "npc", "shop"]
                    .contains(&info["kind"].as_str().unwrap_or("")),
            );
            self.record("inspection_target", &heading);
            self.record("tile_inspection", &heading);
            if let Some(target) = self.bounds.get_mut("inspection_target") {
                target["tile_x"] = json!(x);
                target["tile_y"] = json!(y);
                target["kind"] = info["kind"].clone();
            }
            ui.add_space(4.0);
            if info["enemy"].is_object() {
                self.compact_enemy_stats(ui, &info["enemy"]);
                let safe = info["enemy"]["can_win"].as_bool().unwrap_or(false);
                let forecast = ui.scope(|ui| {
                    let gold = enemy_stat_cell(
                        ui,
                        &self.text("gold"),
                        &number(&info["enemy"]["gold"]),
                        Icon::Coin,
                        theme::GOLD,
                        17.0,
                    );
                    self.record("inspection_stat:gold", &gold);
                    let damage = enemy_stat_cell(
                        ui,
                        &self.text("damage"),
                        &format!(
                            "{} {}",
                            if safe { "✓" } else { "×" },
                            number(&info["enemy"]["damage"])
                        ),
                        Icon::Heart,
                        if safe { theme::GREEN } else { theme::RED },
                        17.0,
                    );
                    self.record("inspection_stat:damage", &damage);
                });
                self.record("inspection_forecast", &forecast.response);
            } else if info["encountered_enemy"].is_object() {
                let raw = ui.scope(|ui| self.compact_enemy_stats(ui, &info["encountered_enemy"]));
                self.record("inspection_contact", &raw.response);
            } else if info["details_locked"] == true {
                ui.label(
                    RichText::new(self.text("orb_required"))
                        .size(13.0)
                        .color(theme::colors(ui.ctx()).muted),
                );
            } else {
                ui.add(
                    egui::Label::new(
                        RichText::new(translate_text(
                            &self.locale,
                            info["description"].as_str().unwrap_or(""),
                        ))
                        .size(13.0)
                        .color(theme::colors(ui.ctx()).muted),
                    )
                    .truncate(),
                );
            }
            return;
        }
        ui.label(
            RichText::new(self.text("inspect_hint"))
                .size(13.0)
                .color(theme::colors(ui.ctx()).muted),
        );
    }

    fn compact_inspection_heading(
        &mut self,
        ui: &mut egui::Ui,
        name: &str,
        sprite: &Value,
        foreground: bool,
    ) -> egui::Response {
        ui.horizontal(|ui| {
            let (portrait, _) = ui.allocate_exact_size(Vec2::splat(32.0), egui::Sense::hover());
            if foreground {
                self.assets
                    .foreground(ui.painter(), portrait, sprite, Color32::WHITE);
            } else {
                self.assets
                    .tile(ui.painter(), portrait, sprite, Color32::WHITE);
            }
            ui.add(egui::Label::new(RichText::new(name).size(16.0).strong()).truncate())
                .on_hover_text(name);
        })
        .response
    }

    fn compact_enemy_stats(&mut self, ui: &mut egui::Ui, enemy: &Value) {
        for (key, label, icon, color) in [
            ("hp", "health", Icon::Heart, theme::RED),
            (
                "attack",
                "attack",
                Icon::Sword,
                theme::colors(ui.ctx()).metal,
            ),
            ("defense", "defense", Icon::Shield, theme::BLUE),
        ] {
            let response = enemy_stat_cell(
                ui,
                &self.text(label),
                &number(&enemy[key]),
                icon,
                color,
                17.0,
            );
            self.record(&format!("inspection_stat:{key}"), &response);
        }
    }

    fn board(&mut self, ui: &mut egui::Ui, size: f32, now: f64) {
        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
        let height = self.visual["height"].as_u64().unwrap_or(11) as usize;
        let cell = (size / width.max(height) as f32).floor().max(1.0);
        let board_size = Vec2::new(cell * width as f32, cell * height as f32);
        let (rect, response) = ui.allocate_exact_size(board_size, egui::Sense::click());
        self.bounds.insert("board".into(),json!({"x":rect.min.x,"y":rect.min.y,"w":rect.width(),"h":rect.height(),"cell":cell,"width":width,"height":height}));
        let painter = ui.painter_at(rect);
        painter.rect_filled(rect, 6.0, Color32::from_rgb(36, 41, 46));
        let battle = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "battle" || a.effect["type"] == "damage");
        let mut hover = None;
        let touch_input = ui.input(|input| {
            input.any_touches()
                || input
                    .events
                    .iter()
                    .any(|event| matches!(event, egui::Event::Touch { .. }))
        });
        let pointer = if response.clicked() {
            response.interact_pointer_pos()
        } else {
            response.hover_pos()
        };
        if let Some(pos) = pointer {
            let x = ((pos.x - rect.min.x) / cell) as usize;
            let y = ((pos.y - rect.min.y) / cell) as usize;
            if x < width && y < height {
                hover = Some((x, y));
                // Touch drags scroll the workspace; only a completed tap selects.
                // Mouse hover stays selected after leaving, so its details remain readable.
                if !touch_input || response.clicked() {
                    self.selected = hover;
                }
            }
        }
        for y in 0..height {
            for x in 0..width {
                let tile = self.visual["tiles"][y * width + x].as_u64().unwrap_or(6);
                let def = &self.visual["tile_defs"][tile.to_string()];
                let min = rect.min + Vec2::new(x as f32 * cell, y as f32 * cell);
                let tile_rect = Rect::from_min_size(min, Vec2::splat(cell));
                self.assets
                    .tile(&painter, tile_rect, &json!(6), Color32::WHITE);
                if self.active.as_ref().is_some_and(|a| {
                    a.effect["type"] == "move_tile"
                        && a.effect["floor"] == self.visual["floor"]
                        && a.effect["from_x"].as_u64() == Some(x as u64)
                        && a.effect["from_y"].as_u64() == Some(y as u64)
                }) {
                    continue;
                }
                let kind = def["kind"].as_str().unwrap_or("wall");
                let frame = (now / self.ambient_interval()) as usize % 2;
                let sprite = Art::animated_sprite(&def["sprite"], frame);
                if !self
                    .assets
                    .tile(&painter, tile_rect, &sprite, Color32::WHITE)
                {
                    let color = match kind {
                        "wall" | "hidden_wall" => Color32::from_rgb(70, 76, 89),
                        "enemy" | "monster" => Color32::from_rgb(164, 65, 83),
                        "door" => Color32::from_rgb(167, 127, 60),
                        "npc" | "shop" => Color32::from_rgb(84, 133, 180),
                        "key" | "item" | "equipment" => theme::colors(ui.ctx()).metal,
                        "stairs_up" | "stairs_down" => Color32::from_rgb(90, 163, 137),
                        _ => Color32::from_rgb(44, 51, 64),
                    };
                    painter.rect_filled(tile_rect.shrink(1.0), 2.0, color);
                    if !["empty", "floor", "wall", "hidden_wall"].contains(&kind) {
                        painter.text(
                            tile_rect.center(),
                            Align2::CENTER_CENTER,
                            tile.to_string(),
                            FontId::proportional(cell * 0.35),
                            Color32::WHITE,
                        );
                    }
                }
                if hover == Some((x, y)) || (hover.is_none() && self.selected == Some((x, y))) {
                    painter.rect_stroke(
                        tile_rect.shrink(1.0),
                        1.0,
                        Stroke::new(2.0, theme::colors(ui.ctx()).metal),
                        egui::StrokeKind::Inside,
                    );
                }
            }
        }
        let mut hx = self.visual["player"]["x"].as_f64().unwrap_or(0.0) as f32;
        let mut hy = self.visual["player"]["y"].as_f64().unwrap_or(0.0) as f32;
        let mut walking = false;
        if let Some(a) = &self.active
            && a.effect["type"] == "move"
        {
            let p = ((now - a.start) / a.duration).clamp(0.0, 1.0) as f32;
            let fx = a.effect["from"]["x"].as_f64().unwrap_or(hx as f64) as f32;
            let fy = a.effect["from"]["y"].as_f64().unwrap_or(hy as f64) as f32;
            hx = fx + (a.effect["to"]["x"].as_f64().unwrap_or(fx as f64) as f32 - fx) * p;
            hy = fy + (a.effect["to"]["y"].as_f64().unwrap_or(fy as f64) as f32 - fy) * p;
            walking = true;
        }
        let hero_rect = Rect::from_min_size(
            rect.min + Vec2::new(hx * cell, hy * cell),
            Vec2::splat(cell),
        );
        let hero_tint = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "cinematic" && a.effect["kind"] == "capture")
            .map(|a| {
                Color32::from_white_alpha(
                    (255.0 * (1.0 - ((now - a.start) / a.duration).clamp(0.0, 1.0))) as u8,
                )
            })
            .unwrap_or(Color32::WHITE);
        let battle_overlay = battle.and_then(|b| {
            self.battle_progress(now)
                .and_then(|progress| battle_impact(&b.effect, &progress))
        });
        let replace_hero = battle_overlay.is_some()
            && battle.is_some_and(|b| {
                b.effect["x"] == self.visual["player"]["x"]
                    && b.effect["y"] == self.visual["player"]["y"]
            });
        if !replace_hero && let Some(frames) = self.assets.heroes.get(&self.facing) {
            painter.image(
                frames[if walking || now < self.hero_idle_at {
                    (now / self.ambient_interval()) as usize % 2
                } else {
                    2
                }]
                .id(),
                hero_rect,
                Rect::from_min_max(egui::pos2(0.0, 0.0), egui::pos2(1.0, 1.0)),
                hero_tint,
            );
        } else if !replace_hero {
            painter.circle_filled(
                hero_rect.center(),
                cell * 0.28,
                theme::colors(ui.ctx()).metal,
            );
        }
        if let Some(b) = battle
            && let Some(hero_turn) = battle_overlay
        {
            let target = Rect::from_min_size(
                rect.min
                    + Vec2::new(
                        b.effect["x"].as_f64().unwrap_or(0.0) as f32 * cell,
                        b.effect["y"].as_f64().unwrap_or(0.0) as f32 * cell,
                    ),
                Vec2::splat(cell),
            );
            let texture = if hero_turn {
                self.assets.impact.as_ref()
            } else {
                self.assets.hero_hits.get(&self.facing)
            };
            if let Some(texture) = texture {
                self.assets
                    .tile(&painter, target, &json!(6), Color32::WHITE);
                painter.image(
                    texture.id(),
                    target,
                    Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
                    Color32::WHITE,
                );
            }
        }
        if let Some(a) = &self.active
            && a.effect["type"] == "move_tile"
            && a.effect["floor"] == self.visual["floor"]
        {
            let p = ((now - a.start) / a.duration).clamp(0.0, 1.0) as f32;
            let fx = a.effect["from_x"].as_f64().unwrap_or(0.0) as f32;
            let fy = a.effect["from_y"].as_f64().unwrap_or(0.0) as f32;
            let tx = a.effect["x"].as_f64().unwrap_or(fx as f64) as f32;
            let ty = a.effect["y"].as_f64().unwrap_or(fy as f64) as f32;
            let moving = Rect::from_min_size(
                rect.min + Vec2::new((fx + (tx - fx) * p) * cell, (fy + (ty - fy) * p) * cell),
                Vec2::splat(cell),
            );
            self.assets
                .creature(&painter, moving, &a.effect["tile"], Color32::WHITE);
        }
        if let Some(a) = &self.active
            && a.effect["type"] == "cinematic"
        {
            let p = ((now - a.start) / a.duration).clamp(0.0, 1.0) as f32;
            let e = a.effect.clone();
            let kind = e["kind"].as_str().unwrap_or("");
            match kind {
                "magic" if e["floor"].is_null() || e["floor"] == self.visual["floor"] => {
                    let targets = e["targets"]
                        .as_array()
                        .filter(|v| !v.is_empty())
                        .cloned()
                        .unwrap_or_else(|| vec![e.clone()]);
                    let frames = e["frames"]
                        .as_array()
                        .filter(|v| !v.is_empty())
                        .cloned()
                        .unwrap_or_else(|| (166..=182).map(|f| json!(f)).collect());
                    let step = ((p * (frames.len() * targets.len()) as f32) as usize)
                        .min(frames.len() * targets.len() - 1);
                    let sweep = step / targets.len();
                    for (index, target) in targets.iter().enumerate() {
                        let x = target["x"]
                            .as_u64()
                            .or_else(|| e["x"].as_u64())
                            .unwrap_or(0);
                        let y = target["y"]
                            .as_u64()
                            .or_else(|| e["y"].as_u64())
                            .unwrap_or(0);
                        if x >= width as u64 || y >= height as u64 {
                            continue;
                        }
                        let at = Rect::from_min_size(
                            rect.min + Vec2::new(x as f32 * cell, y as f32 * cell),
                            Vec2::splat(cell),
                        );
                        self.assets
                            .tile(&painter, at, &e["underlying_tile"], Color32::WHITE);
                        if index > step % targets.len() && sweep == 0 {
                            continue;
                        }
                        let frame = frames[if index <= step % targets.len() {
                            sweep
                        } else {
                            sweep - 1
                        }]
                        .as_u64()
                        .unwrap_or(182) as u32;
                        self.assets.masked_tile(
                            &painter,
                            at,
                            e["color_tile"]
                                .as_u64()
                                .or_else(|| e["tile"].as_u64())
                                .unwrap_or(91) as u32,
                            frame,
                            Color32::WHITE,
                        );
                    }
                }
                "tile_reveal" if e["floor"].is_null() || e["floor"] == self.visual["floor"] => {
                    let x = e["x"].as_u64().unwrap_or(0) as f32;
                    let y = e["y"].as_u64().unwrap_or(0) as f32;
                    let at = Rect::from_min_size(
                        rect.min + Vec2::new(x * cell, y * cell),
                        Vec2::splat(cell),
                    );
                    self.assets.tile_transition(
                        &painter,
                        at,
                        &presentation_sprite(&self.visual, &e["from_tile"]),
                        &presentation_sprite(&self.visual, &e["tile"]),
                        e["style"].as_str().unwrap_or("door_open"),
                        p,
                    );
                }
                "title" | "scan" => {
                    painter.rect_filled(rect, 0.0, Color32::BLACK);
                    let asset_key = if kind == "scan" {
                        "background_asset"
                    } else {
                        "asset"
                    };
                    let asset = format!(
                        "assets/{}.png",
                        e[asset_key].as_str().unwrap_or("data3-open1")
                    );
                    let scene_rect = self
                        .assets
                        .scenes
                        .get(&asset)
                        .map(|texture| {
                            let size = texture.size_vec2();
                            Rect::from_center_size(
                                rect.center(),
                                size * (rect.width() / size.x).min(rect.height() / size.y),
                            )
                        })
                        .unwrap_or(rect);
                    if let Some(texture) = self.assets.scenes.get(&asset) {
                        painter.image(
                            texture.id(),
                            scene_rect,
                            Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
                            Color32::WHITE,
                        );
                    }
                    if kind == "title" {
                        let frames = e["frames"].as_array();
                        let mask = frames
                            .and_then(|frames| {
                                frames.get(
                                    ((p * frames.len() as f32) as usize)
                                        .min(frames.len().saturating_sub(1)),
                                )
                            })
                            .and_then(Value::as_u64)
                            .unwrap_or(182) as u32;
                        let target = format!(
                            "assets/{}.png",
                            e["target_asset"].as_str().unwrap_or("data3-open1")
                        );
                        self.assets
                            .masked_scene(&painter, scene_rect, &target, mask);
                    } else if self.locale.starts_with("zh") {
                        let text = tr(
                            &self.locale,
                            e["translation_key"]
                                .as_str()
                                .unwrap_or("capture_incantation"),
                        );
                        let lines = text.lines().collect::<Vec<_>>();
                        for (i, line) in lines.iter().enumerate() {
                            if p >= i as f32 / lines.len().max(1) as f32 {
                                painter.text(
                                    scene_rect.center()
                                        + Vec2::new(
                                            0.0,
                                            (i as f32 - (lines.len() - 1) as f32 / 2.0) * 30.0,
                                        ),
                                    Align2::CENTER_CENTER,
                                    line,
                                    FontId::proportional((cell * 0.4).clamp(16.0, 24.0)),
                                    Color32::WHITE,
                                );
                            }
                        }
                    } else if let Some(texture) = self.assets.scenes.get(&format!(
                        "assets/{}.png",
                        e["asset"].as_str().unwrap_or("data3-open2")
                    )) {
                        let clip = Rect::from_min_max(
                            scene_rect.min,
                            egui::pos2(
                                scene_rect.max.x,
                                scene_rect.min.y + scene_rect.height() * p,
                            ),
                        );
                        painter.with_clip_rect(clip).image(
                            texture.id(),
                            scene_rect,
                            Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
                            Color32::WHITE,
                        );
                    }
                }
                "transformation" => {
                    let x = e["x"].as_u64().unwrap_or(5) as usize;
                    let y = e["y"].as_u64().unwrap_or(5) as usize;
                    let w = e["width"].as_u64().unwrap_or(3) as usize;
                    let h = e["height"].as_u64().unwrap_or(3) as usize;
                    let origin_x = x.saturating_sub(w / 2);
                    let origin_y = y.saturating_sub(h / 2);
                    for dy in 0..h {
                        for dx in 0..w {
                            let at = Rect::from_min_size(
                                rect.min
                                    + Vec2::new(
                                        (origin_x + dx) as f32 * cell,
                                        (origin_y + dy) as f32 * cell,
                                    ),
                                Vec2::splat(cell),
                            );
                            self.assets.tile(&painter, at, &json!(6), Color32::WHITE);
                        }
                    }
                    let amount = (p * 32.0).floor() / 32.0;
                    for dy in 0..h {
                        for dx in 0..w {
                            if dx == w / 2 && dy == h / 2 {
                                continue;
                            }
                            let source = Vec2::new((origin_x + dx) as f32, (origin_y + dy) as f32);
                            let center = Vec2::new(x as f32, y as f32);
                            let at = Rect::from_min_size(
                                rect.min + (source + (center - source) * amount) * cell,
                                Vec2::splat(cell),
                            );
                            let sprite = Art::animated_sprite(
                                &e["from_tiles"][dy * w + dx],
                                (now / self.ambient_interval()) as usize % 2,
                            );
                            self.assets.creature(&painter, at, &sprite, Color32::WHITE);
                        }
                    }
                }
                "capture" | "fade_out" | "fade_in" | "fade" | "fairy" => {
                    let opacity = if kind == "fade_in" {
                        1.0 - p
                    } else if kind == "fade" || kind == "fairy" {
                        (p * std::f32::consts::PI).sin()
                    } else {
                        p
                    };
                    painter.rect_filled(
                        rect,
                        0.0,
                        Color32::from_black_alpha((opacity * 255.0) as u8),
                    );
                }
                "victory" | "credits" => {
                    painter.rect_filled(rect, 0.0, Color32::from_rgba_unmultiplied(6, 12, 23, 220));
                    painter.text(
                        rect.center() - Vec2::new(0.0, 20.0),
                        Align2::CENTER_CENTER,
                        self.text(if kind == "victory" {
                            "new_journey"
                        } else {
                            "game_title"
                        }),
                        FontId::proportional(28.0),
                        theme::colors(ui.ctx()).metal,
                    );
                    if kind == "credits" {
                        painter.text(
                            rect.center() + Vec2::new(0.0, 25.0),
                            Align2::CENTER_CENTER,
                            "Oz & Kenichi / Shigemasa Ozawa",
                            FontId::proportional(18.0),
                            theme::colors(ui.ctx()).text,
                        );
                    }
                }
                _ => {}
            }
        }
        if let Some(a) = &self.active
            && a.effect["type"] == "floor"
        {
            let p = ((now - a.start) / a.duration).clamp(0.0, 1.0) as f32;
            if a.effect["style"].as_str().unwrap_or("original_spiral") == "original_spiral" {
                let order = stair_wipe_order(width, height);
                let covered = if p < 0.5 {
                    (p * 2.0 * order.len() as f32).ceil() as usize
                } else {
                    order.len()
                };
                let revealed = if p < 0.5 {
                    0
                } else {
                    ((p * 2.0 - 1.0) * order.len() as f32).floor() as usize
                };
                for index in order.iter().take(covered).skip(revealed) {
                    let at = Rect::from_min_size(
                        rect.min
                            + Vec2::new(
                                (index % width) as f32 * cell,
                                (index / width) as f32 * cell,
                            ),
                        Vec2::splat(cell),
                    );
                    self.assets.tile(&painter, at, &json!(159), Color32::WHITE);
                }
            } else {
                let opacity = (1.0 - (p * 2.0 - 1.0).abs()) * 255.0;
                painter.rect_filled(rect, 0.0, Color32::from_black_alpha(opacity as u8));
            }
        }
        self.battle_overlay(&painter, rect, now);
        if response.clicked()
            && !self.journal_open
            && !self.enemy_list_open
            && self.travel_only()
            && self.snapshot["pending_interaction"].is_null()
            && let Some((x, y)) = hover
        {
            self.audio.unlock();
            match self
                .engine
                .path_to(x, y)
                .iter()
                .map(|name| name.parse())
                .collect()
            {
                Ok(route) => self.route = route,
                Err(error) => self.notify(format!("Invalid engine route: {error}")),
            }
        }
        if !self.classic_layout && self.busy() && !self.travel_only() {
            ui.add_space(10.0);
            let skip = theme::action(ui, self.text("skip"), Icon::ArrowRight, false);
            self.record("skip", &skip);
            if skip.clicked() {
                self.skip_presentation();
            }
        }
    }

    fn battle_overlay(&mut self, painter: &egui::Painter, board: Rect, now: f64) {
        let Some(effect) = self
            .active
            .as_ref()
            .filter(|active| active.effect["type"] == "battle")
            .map(|active| active.effect.clone())
        else {
            return;
        };
        let Some(progress) = self.battle_progress(now) else {
            return;
        };
        let palette = theme::colors(&self.context);
        let scale = theme::scale(&self.context);
        let size = Vec2::new(
            (board.width() - 16.0 * scale).min(248.0 * scale),
            (board.height() - 16.0 * scale).min(116.0 * scale),
        );
        let y = if effect["y"].as_u64().unwrap_or(0) * 2
            < self.visual["height"].as_u64().unwrap_or(11)
        {
            board.bottom() - size.y - 8.0 * scale
        } else {
            board.top() + 8.0 * scale
        };
        let rect = Rect::from_min_size(egui::pos2(board.right() - size.x - 8.0 * scale, y), size);
        painter.rect_filled(
            rect,
            8.0,
            Color32::from_rgba_unmultiplied(
                palette.surface.r(),
                palette.surface.g(),
                palette.surface.b(),
                155,
            ),
        );
        painter.rect_stroke(
            rect,
            8.0,
            Stroke::new(1.0, palette.metal.linear_multiply(0.45)),
            egui::StrokeKind::Inside,
        );
        let name = translate_text(&self.locale, effect["enemy_name"].as_str().unwrap_or(""));
        let mut title = egui::text::LayoutJob::simple(
            name,
            FontId::proportional(15.0 * scale),
            palette.text,
            rect.width() - 16.0 * scale,
        );
        title.wrap.max_rows = 1;
        painter.galley(
            rect.min + Vec2::new(8.0, 6.0) * scale,
            painter.layout_job(title),
            palette.text,
        );
        let encountered = visible_last_encounter(&self.visual);
        let attack = effect["enemy_attack"]
            .as_i64()
            .or_else(|| encountered.and_then(|e| e["attack"].as_i64()))
            .unwrap_or(0);
        let defense = effect["enemy_defense"]
            .as_i64()
            .or_else(|| encountered.and_then(|e| e["defense"].as_i64()))
            .unwrap_or(0);
        let values = [
            (
                Icon::Heart,
                theme::RED,
                format!(
                    "{} / {}",
                    number(&json!(progress.enemy_hp)),
                    number(&effect["enemy_hp"])
                ),
            ),
            (Icon::Sword, palette.metal, number(&json!(attack))),
            (Icon::Shield, theme::BLUE, number(&json!(defense))),
            (Icon::Coin, theme::GOLD, number(&effect["gold"])),
        ];
        let show_gold = visual_has_hero_orb(&self.visual);
        for (index, (icon, color, value)) in values.iter().enumerate() {
            if index == 3 && !show_gold {
                continue;
            }
            let x = rect.left()
                + 8.0 * scale
                + (index % 2) as f32 * (rect.width() - 16.0 * scale) * 0.5;
            let y = rect.top() + (31.0 + (index / 2) as f32 * 23.0) * scale;
            theme::icon(
                painter,
                Rect::from_center_size(
                    egui::pos2(x + 7.0 * scale, y + 10.0 * scale),
                    Vec2::splat(14.0 * scale),
                ),
                *icon,
                *color,
            );
            let width = (rect.width() - 16.0 * scale) * 0.5 - 22.0 * scale;
            let mut font_size = 15.0 * scale;
            let mut galley = painter.layout_no_wrap(
                value.clone(),
                FontId::proportional(font_size),
                palette.text,
            );
            if galley.size().x > width {
                font_size *= width / galley.size().x;
                galley = painter.layout_no_wrap(
                    value.clone(),
                    FontId::proportional(font_size),
                    palette.text,
                );
            }
            painter.galley(
                egui::pos2(x + 20.0 * scale, y + 10.0 * scale - galley.size().y * 0.5),
                galley,
                palette.text,
            );
        }
        if rect.height() >= 108.0 * scale {
            painter.text(
                egui::pos2(rect.left() + 8.0 * scale, rect.top() + 83.0 * scale),
                Align2::LEFT_TOP,
                format!(
                    "{} · {}",
                    self.text("adventurer"),
                    number(&json!(progress.hero_hp))
                ),
                FontId::proportional(12.0 * scale),
                palette.text,
            );
            let bar = Rect::from_min_size(
                egui::pos2(rect.left() + 8.0 * scale, rect.bottom() - 10.0 * scale),
                Vec2::new(rect.width() - 16.0 * scale, 3.0 * scale),
            );
            painter.rect_filled(bar, 2.0, Color32::from_black_alpha(80));
            let hp = (progress.hero_hp as f32
                / effect["hero_hp"].as_i64().unwrap_or(1).max(1) as f32)
                .clamp(0.0, 1.0);
            painter.rect_filled(
                Rect::from_min_size(bar.min, Vec2::new(bar.width() * hp, bar.height())),
                2.0,
                theme::GREEN,
            );
        }
        self.bounds.insert("battle_overlay".into(), json!({"x":rect.left(),"y":rect.top(),"w":rect.width(),"h":rect.height(),
            "enemy_hp":progress.enemy_hp,"enemy_max_hp":effect["enemy_hp"],"attack":attack,"defense":defense,
            "gold":if show_gold { effect["gold"].clone() } else { Value::Null },"hero_hp":progress.hero_hp}));
    }

    fn skip_presentation(&mut self) {
        self.queue.clear();
        self.active = None;
        self.visual = self.snapshot.clone();
        self.route.clear();
        self.hero_idle_at = 0.0;
        self.music_paused = false;
        self.music_override = None;
    }

    fn board_card(&mut self, ui: &mut egui::Ui, width: f32, now: f64, compact: bool) {
        let padding = if self.landscape {
            6
        } else if compact {
            8
        } else {
            10
        };
        let panel = theme::frame(ui.ctx()).inner_margin(padding).show(ui, |ui| {
            ui.vertical(|ui| {
                ui.set_width(width - 2.0 * f32::from(padding));
                if self.classic_layout && !self.landscape {
                    ui.set_min_height(width - 2.0 * f32::from(padding));
                }
                if !self.classic_layout {
                    ui.horizontal(|ui| {
                        let (badge, _) = ui.allocate_exact_size(
                            Vec2::splat(if self.landscape {
                                24.0
                            } else if compact {
                                28.0
                            } else {
                                36.0
                            }),
                            egui::Sense::hover(),
                        );
                        ui.painter()
                            .rect_filled(badge, 10.0, theme::colors(ui.ctx()).raised);
                        ui.painter().text(
                            badge.center(),
                            Align2::CENTER_CENTER,
                            format!("{:02}", self.visual["floor"].as_i64().unwrap_or(1)),
                            FontId::proportional(if self.landscape {
                                15.0
                            } else if compact {
                                18.0
                            } else {
                                21.0
                            }),
                            theme::colors(ui.ctx()).metal,
                        );
                        ui.add_space(4.0);
                        ui.vertical(|ui| {
                            ui.spacing_mut().item_spacing.y = 2.0;
                            if !compact {
                                theme::caption(ui, &self.text("current_floor"));
                            }
                            let title = self
                                .engine
                                .campaign()
                                .floors
                                .iter()
                                .find(|f| Some(i64::from(f.id)) == self.visual["floor"].as_i64())
                                .map(|f| f.title.as_str())
                                .unwrap_or("");
                            ui.label(
                                RichText::new(translate_text(&self.locale, title))
                                    .size(if self.landscape {
                                        14.0
                                    } else if compact {
                                        18.0
                                    } else {
                                        20.0
                                    })
                                    .strong(),
                            );
                        });
                        if !compact {
                            ui.with_layout(
                                egui::Layout::right_to_left(egui::Align::Center),
                                |ui| {
                                    ui.label(
                                        RichText::new(format!(
                                            "{} {}",
                                            number(&self.visual["steps"]),
                                            self.text("turns")
                                        ))
                                        .size(14.0)
                                        .color(theme::colors(ui.ctx()).muted),
                                    );
                                },
                            );
                        }
                    });
                    ui.add_space(8.0);
                }
                let available = ui.available_width();
                let viewport_height = self.context.input(|i| i.viewport_rect().height());
                let board_size = if self.classic_layout {
                    available.min(
                        (viewport_height - ui.cursor().min.y - f32::from(padding) - 6.0).max(96.0),
                    )
                } else {
                    available
                };
                let board_inset = (available - board_size) * 0.5;
                let board_start = ui.cursor().min + Vec2::new(board_inset, 0.0);
                let width_cells = self.visual["width"]
                    .as_u64()
                    .unwrap_or(11)
                    .max(self.visual["height"].as_u64().unwrap_or(11))
                    as f32;
                let cell = (board_size / width_cells).floor().max(1.0);
                let extent = Vec2::new(
                    self.visual["width"].as_u64().unwrap_or(11) as f32 * cell,
                    self.visual["height"].as_u64().unwrap_or(11) as f32 * cell,
                );
                let surround =
                    Rect::from_min_size(board_start - Vec2::splat(4.0), extent + Vec2::splat(8.0));
                ui.painter().rect_stroke(
                    surround,
                    4.0,
                    Stroke::new(1.0, theme::colors(ui.ctx()).border),
                    egui::StrokeKind::Outside,
                );
                for corner in [
                    surround.left_top(),
                    surround.right_top(),
                    surround.left_bottom(),
                    surround.right_bottom(),
                ] {
                    let dx = if corner.x < surround.center().x {
                        1.0
                    } else {
                        -1.0
                    };
                    let dy = if corner.y < surround.center().y {
                        1.0
                    } else {
                        -1.0
                    };
                    ui.painter().line_segment(
                        [corner, corner + Vec2::new(dx * 14.0, 0.0)],
                        Stroke::new(2.0, theme::colors(ui.ctx()).metal),
                    );
                    ui.painter().line_segment(
                        [corner, corner + Vec2::new(0.0, dy * 14.0)],
                        Stroke::new(2.0, theme::colors(ui.ctx()).metal),
                    );
                }
                ui.horizontal_top(|ui| {
                    ui.spacing_mut().item_spacing.x = 0.0;
                    ui.add_space(board_inset);
                    ui.vertical(|ui| {
                        ui.set_width(board_size);
                        self.board(ui, board_size, now);
                    });
                });
                if !self.classic_layout {
                    ui.add_space(4.0);
                    if !compact {
                        ui.label(
                            RichText::new(self.text("keyboard_hint"))
                                .size(14.0)
                                .color(theme::colors(ui.ctx()).muted),
                        );
                    }
                    ui.add_space(4.0);
                    ui.label(
                        RichText::new(self.text("controls_hint"))
                            .size(if compact { 14.0 } else { 15.0 })
                            .color(theme::colors(ui.ctx()).muted),
                    );
                }
            });
        });
        self.record("floor_panel", &panel.response);
    }

    fn dialogs(&mut self, now: f64) {
        if self
            .active
            .as_ref()
            .is_some_and(|active| active.effect["type"] == "journal")
        {
            self.journal_dialog();
            return;
        }
        let scripted = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "dialogue")
            .map(|a| (a.effect["text"].as_str().unwrap_or("").to_string(), a.start));
        let pending = if self.busy() {
            Value::Null
        } else {
            self.snapshot["pending_interaction"].clone()
        };
        if scripted.is_none() && pending.is_null() {
            return;
        }
        let signature = scripted
            .as_ref()
            .map(|(t, _)| t.clone())
            .unwrap_or_else(|| pending.to_string());
        if self.dialogue_signature != signature {
            self.dialogue_signature = signature;
            self.dialogue_started = now;
        }
        let (raw, start) = scripted.clone().unwrap_or_else(|| {
            (
                pending["text"]
                    .as_str()
                    .or_else(|| pending["message"].as_str())
                    .unwrap_or("")
                    .into(),
                self.dialogue_started,
            )
        });
        let text = translate_text(&self.locale, &raw);
        let count = ((now - start) * 48.0 * f64::from(self.speed)) as usize;
        let visible: String = text.chars().take(count).collect();
        let mut action = None;
        let mut next = false;
        let mut skip_scene = false;
        let viewport = self.context.input(|i| i.viewport_rect());
        let bounds = &self.bounds["board"];
        let board = Rect::from_min_size(
            egui::pos2(
                bounds["x"].as_f64().unwrap_or(0.0) as f32,
                bounds["y"].as_f64().unwrap_or(0.0) as f32,
            ),
            Vec2::new(
                bounds["w"].as_f64().unwrap_or(360.0) as f32,
                bounds["h"].as_f64().unwrap_or(360.0) as f32,
            ),
        );
        let inset = if board.width() < 380.0 { 16 } else { 24 };
        let dialog_width = (board.width() - 28.0 - inset as f32 * 2.0).min(480.0);
        self.context
            .layer_painter(egui::LayerId::new(
                egui::Order::Middle,
                egui::Id::new("conversation_shade"),
            ))
            .with_clip_rect(board)
            .rect_filled(board, 6.0, Color32::from_black_alpha(140));
        let modal_id = egui::Id::new("conversation");
        let response = egui::Modal::new(modal_id)
            .area(
                egui::Modal::default_area(modal_id)
                    .anchor(Align2::CENTER_CENTER, board.center() - viewport.center()),
            )
            .backdrop_color(Color32::TRANSPARENT)
            .frame(theme::frame(&self.context).inner_margin(inset))
            .show(&self.context.clone(), |ui| {
                ui.set_width(dialog_width);
                theme::caption(ui, &self.text("dialogue"));
                ui.add_space(8.0);
                if let Some(name) = pending["title"].as_str() {
                    ui.label(
                        RichText::new(translate_text(&self.locale, name))
                            .size(if board.width() < 380.0 { 24.0 } else { 27.0 })
                            .color(theme::colors(ui.ctx()).text),
                    );
                    ui.add_space(10.0);
                }
                let offers = pending["offers"]
                    .as_array()
                    .or_else(|| pending["choices"].as_array())
                    .cloned()
                    .unwrap_or_default();
                let needs_close = scripted.is_none()
                    && !offers
                        .iter()
                        .any(|o| o["id"] == "leave" || o["id"] == "cancel");
                let action_height = if scripted.is_some() {
                    38.0
                } else {
                    (offers.len() as f32 * 50.0 + if needs_close { 44.0 } else { 0.0 })
                        .min(board.height() * 0.42)
                };
                let body_height = (board.height()
                    - inset as f32 * 2.0
                    - 74.0
                    - action_height
                    - if pending["title"].is_string() {
                        42.0
                    } else {
                        0.0
                    })
                .max(45.0);
                egui::ScrollArea::vertical()
                    .id_salt("conversation_text")
                    .max_height(body_height)
                    .auto_shrink([false, true])
                    .show(ui, |ui| {
                        let font_size = if board.width() < 380.0 { 19.0 } else { 21.0 };
                        let full = ui.painter().layout(
                            text.clone(),
                            FontId::proportional(font_size),
                            theme::colors(ui.ctx()).text,
                            ui.available_width(),
                        );
                        // Reserve the complete speech so typing cannot move the choice buttons.
                        ui.set_min_height(full.size().y.min(body_height));
                        ui.label(RichText::new(visible).size(font_size));
                    });
                ui.add_space(14.0);
                if scripted.is_some() {
                    ui.horizontal(|ui| {
                        let button =
                            theme::action(ui, self.text("continue"), Icon::ArrowRight, true);
                        self.record("dialogue_continue", &button);
                        if button.clicked() {
                            next = true;
                        }
                        let skip = theme::action(ui, self.text("skip_scene"), Icon::Close, false);
                        self.record("skip", &skip);
                        if skip.clicked() {
                            skip_scene = true;
                        }
                    });
                } else {
                    egui::ScrollArea::vertical()
                        .id_salt("conversation_choices")
                        .max_height(action_height)
                        // A prior shorter conversation must not constrain this
                        // area's cached viewport and clip newly added choices.
                        .min_scrolled_height(action_height)
                        .auto_shrink([false, true])
                        .show(ui, |ui| {
                            ui.spacing_mut().item_spacing.y = 6.0;
                            for offer in offers {
                                let label = offer["label"]
                                    .as_str()
                                    .or_else(|| offer["text"].as_str())
                                    .or_else(|| offer["name"].as_str())
                                    .unwrap_or("Accept");
                                let button = ui.add(
                                    egui::Button::new(
                                        RichText::new(translate_text(&self.locale, label))
                                            .size(17.0),
                                    )
                                    .fill(theme::colors(ui.ctx()).raised)
                                    .stroke(Stroke::new(1.0, theme::colors(ui.ctx()).border))
                                    .corner_radius(9)
                                    .min_size(Vec2::new(ui.available_width(), 44.0)),
                                );
                                let id = offer["id"].as_str().unwrap_or("accept");
                                self.record(&format!("choice:{id}"), &button);
                                if button.clicked() {
                                    action = Some(Command::Choose { choice: id.into() });
                                }
                            }
                            if needs_close {
                                let close =
                                    theme::action(ui, self.text("close"), Icon::Close, false);
                                self.record("dialogue_close", &close);
                                if close.clicked() {
                                    action = Some(Command::Cancel);
                                }
                            }
                        });
                }
            });
        self.record("dialogue", &response.response);
        if self
            .context
            .input(|i| i.key_pressed(egui::Key::Enter) || i.key_pressed(egui::Key::Space))
        {
            if scripted.is_some() {
                next = true;
            } else if pending["choices"]
                .as_array()
                .is_some_and(|choices| choices.len() == 1 && choices[0]["id"] == "leave")
            {
                action = Some(Command::Choose {
                    choice: "leave".into(),
                });
            }
        }
        if skip_scene {
            self.skip_presentation();
        } else if next {
            self.finish_effect();
        }
        if let Some(command) = action {
            self.apply_command(command);
        }
    }

    fn settings_window(&mut self) {
        if !self.settings {
            return;
        }
        let mut opened = self.settings;
        let viewport = self.context.input(|i| i.viewport_rect());
        let scale = theme::scale(&self.context);
        let width = (viewport.width() - 96.0 * scale).clamp(260.0, 490.0 * scale);
        let mut new_game = false;
        let mut import = false;
        let mut export = false;
        let mut language = self.locale.clone();
        let mut changed = false;
        let mut flying = None;
        let flying_record =
            visible_inventory_items(&self.visual, &self.snapshot, self.engine.campaign())
                .into_iter()
                .find(|item| item["usage"]["target_floor"].is_string());
        let flying_item = flying_record
            .as_ref()
            .and_then(|item| item["id"].as_str().map(str::to_owned));
        let flying_floors = flying_record
            .as_ref()
            .and_then(|item| item["usage"]["allowed_floors"].as_array())
            .or_else(|| self.visual["visited_floors"].as_array())
            .cloned()
            .unwrap_or_default();
        let response = egui::Modal::new(egui::Id::new("settings_modal"))
            .backdrop_color(Color32::from_black_alpha(150))
            .frame(theme::frame(&self.context).inner_margin((24.0 * scale) as i8))
            .show(&self.context.clone(), |ui| {
                ui.set_width(width);
                ui.set_max_height((viewport.height() - 140.0 * scale).min(780.0 * scale));
                egui::ScrollArea::vertical()
                    .id_salt("settings_content")
                    .max_height(viewport.height() - 100.0 * scale)
                    .show(ui, |ui| {
                        ui.horizontal(|ui| {
                            ui.label(
                                RichText::new(self.text("settings"))
                                    .size(28.0 * scale)
                                    .strong(),
                            );
                            ui.with_layout(
                                egui::Layout::right_to_left(egui::Align::Center),
                                |ui| {
                                    if theme::action(ui, String::new(), Icon::Close, false)
                                        .on_hover_text(self.text("close"))
                                        .clicked()
                                    {
                                        opened = false;
                                    }
                                },
                            );
                        });
                        ui.add_space(14.0);
                        theme::caption(ui, &self.text("language"));
                        ui.horizontal_wrapped(|ui| {
                            if ui
                                .selectable_value(&mut language, "en".into(), "English")
                                .clicked()
                            {
                                changed = true;
                            }
                            if ui
                                .selectable_value(&mut language, "zh-CN".into(), "简体中文")
                                .clicked()
                            {
                                changed = true;
                            }
                        });
                        ui.add_space(14.0);
                        ui.separator();
                        ui.add_space(10.0);
                        changed |= ui
                            .checkbox(&mut self.audio.enabled, tr(&language, "audio"))
                            .changed();
                        changed |= ui
                            .checkbox(&mut self.audio.music_enabled, tr(&language, "music"))
                            .changed();
                        changed |= ui
                            .add(
                                egui::Slider::new(&mut self.audio.volume, 0.0..=1.0)
                                    .text(tr(&language, "volume")),
                            )
                            .changed();
                        changed |= ui
                            .add(
                                egui::Slider::new(&mut self.speed, 0.5..=4.0)
                                    .text(tr(&language, "animation_speed")),
                            )
                            .changed();
                        if let Some(error) = &self.audio.error {
                            ui.label(RichText::new(error).color(theme::colors(ui.ctx()).muted));
                        }
                        ui.separator();
                        ui.add_space(12.0);
                        let new = theme::action(ui, self.text("new_game"), Icon::Tower, false);
                        self.record("new_game", &new);
                        if new.clicked() {
                            new_game = true;
                        }
                        let save = ui
                            .add_enabled_ui(self.engine.save_unlocked(), |ui| {
                                theme::action(ui, self.text("export_save"), Icon::Save, false)
                            })
                            .inner
                            .on_disabled_hover_text(self.text("save_orb_required"));
                        if save.clicked() {
                            export = true;
                        }
                        ui.add_space(12.0);
                        ui.label(self.text("import_hint"));
                        ui.add(
                            egui::TextEdit::multiline(&mut self.import_text)
                                .desired_rows(4)
                                .desired_width(f32::INFINITY)
                                .hint_text("{…}"),
                        );
                        if ui.button(self.text("import")).clicked() {
                            import = true;
                        }
                        if flying_item.is_some() {
                            ui.separator();
                            ui.label(self.text("flying_hint"));
                            ui.horizontal_wrapped(|ui| {
                                for f in &flying_floors {
                                    if let Some(floor) = f.as_i64()
                                        && ui.button(floor.to_string()).clicked()
                                    {
                                        flying = Some(floor);
                                    }
                                }
                            });
                        }
                    });
            });
        self.settings = opened && !response.should_close();
        if changed {
            self.locale = language;
            self.audio.unlock();
            self.audio.refresh_volume();
            self.preferences();
        }
        if new_game {
            self.apply_command(Command::NewGame);
            self.settings = false;
        }
        if export {
            if self.engine.ensure_player_save_allowed().is_err() {
                self.notify(self.text("save_orb_required"));
            } else {
                match platform::export("tower.save.json", &self.engine.save_json()) {
                    Ok(path) => self.notify(path),
                    Err(e) => self.notify(e),
                }
            }
        }
        if import {
            let source = self.import_text.clone();
            let result = if serde_json::from_str::<Value>(&source)
                .ok()
                .is_some_and(|v| v["floors"].is_array() && v["tiles"].is_object())
            {
                self.replace_campaign(&source)
            } else {
                self.load_save(&source)
            };
            match result {
                Ok(()) => {
                    self.import_text.clear();
                    self.notify(self.text("imported"));
                }
                Err(e) => self.notify(e),
            }
        }
        if let Some(floor) = flying {
            self.settings = false;
            self.apply_command(Command::UseItem {
                item: flying_item.expect("a destination is selectable only with a flying item"),
                floor: Some(i32::try_from(floor).expect("floor ID came from a validated campaign")),
            });
        }
    }

    fn keyboard(&mut self) {
        if self.settings
            || self.journal_open
            || self.enemy_list_open
            || self.editor_open
            || !self.travel_only()
            || !self.snapshot["pending_interaction"].is_null()
        {
            return;
        }
        let direction = self.context.input(|i| {
            [
                (egui::Key::ArrowUp, egui::Key::W, Direction::Up),
                (egui::Key::ArrowDown, egui::Key::S, Direction::Down),
                (egui::Key::ArrowLeft, egui::Key::A, Direction::Left),
                (egui::Key::ArrowRight, egui::Key::D, Direction::Right),
            ]
            .iter()
            .find_map(|(a, b, d)| (i.key_pressed(*a) || i.key_pressed(*b)).then_some(*d))
        });
        if let Some(direction) = direction {
            self.route.clear();
            if self.busy() {
                self.route.push_back(direction);
            } else {
                self.apply_command(Command::Move { direction });
            }
        }
    }
}

impl TowerApp {
    fn import_drops(&mut self) {
        let files = self.context.input(|input| input.raw.dropped_files.clone());
        for file in files {
            platform::read_drop(file, self.sender.clone(), self.context.clone());
        }
    }
}

impl eframe::App for TowerApp {
    #[cfg(target_arch = "wasm32")]
    fn as_any_mut(&mut self) -> Option<&mut dyn std::any::Any> {
        Some(self)
    }
    fn ui(&mut self, ui: &mut egui::Ui, _frame: &mut eframe::Frame) {
        let now = ui.input(|i| i.time);
        self.import_drops();
        self.advance(now);
        let viewport = self.context.input(|i| i.viewport_rect());
        self.landscape = !self.editor_open
            && viewport.width() >= 700.0
            && viewport.height() <= 720.0
            && viewport.width() > viewport.height() * 1.25;
        self.classic_layout = !self.editor_open && (self.landscape || viewport.width() >= 1060.0);
        let desktop_scale = if self.classic_layout && !self.landscape {
            let shell = viewport.width() - 24.0;
            let center = (shell - 464.0).min(viewport.height() - 24.0);
            let sidebar = (shell - center - 16.0) * 0.5;
            (sidebar / 224.0).sqrt().clamp(1.0, 2.0)
        } else {
            1.0
        };
        theme::apply(
            &self.context,
            self.visual["cycle"].as_u64().unwrap_or(1) > 1,
            self.landscape || viewport.width() < 700.0,
            desktop_scale,
        );
        self.bounds.clear();
        if self.editor_open {
            let margin = if ui.available_width() < 700.0 { 14 } else { 24 };
            egui::Frame::new().inner_margin(margin).show(ui, |ui| {
                let action = self.editor.show(ui, &self.locale);
                match action {
                    EditorAction::Play(value) => match self.replace_campaign(&value.to_string()) {
                        Ok(()) => self.editor_open = false,
                        Err(e) => self.notify(e),
                    },
                    EditorAction::Export(value) => match platform::export(
                        "campaign.json",
                        &serde_json::to_string_pretty(&value)
                            .expect("JSON editor document serializes to JSON"),
                    ) {
                        Ok(path) => {
                            self.editor.mark_exported();
                            self.notify(path);
                        }
                        Err(e) => self.notify(e),
                    },
                    EditorAction::None => {}
                }
                ui.add_space(8.0);
                let back = theme::action(ui, self.text("back_to_game"), Icon::ArrowLeft, false);
                self.record("back_to_game", &back);
                if back.clicked() {
                    self.editor_open = false;
                }
            });
        } else {
            let narrow = ui.available_width() < 1060.0;
            let bg = ui.max_rect();
            theme::paint_tower_backdrop(ui, bg);
            egui::Frame::new()
                .inner_margin(if self.landscape {
                    6
                } else if narrow {
                    10
                } else {
                    12
                })
                .show(ui, |ui| {
                    let shell_width = ui.available_width();
                    let inset = ((ui.available_width() - shell_width) * 0.5).max(0.0);
                    egui::ScrollArea::vertical()
                        .id_salt("game_workspace")
                        .auto_shrink([false, false])
                        .show(ui, |ui| {
                            ui.horizontal_top(|ui| {
                                ui.add_space(inset);
                                ui.vertical(|ui| {
                                    ui.set_width(shell_width);
                                    if narrow {
                                        ui.spacing_mut().item_spacing.y = 4.0;
                                    }
                                    self.header(ui);
                                    if self.classic_layout {
                                        let scale = theme::scale(ui.ctx());
                                        let minimum_side =
                                            if self.landscape { 196.0 } else { 224.0 };
                                        let center = (shell_width - 2.0 * minimum_side - 16.0).min(
                                            viewport.height()
                                                - if self.landscape { 12.0 } else { 24.0 },
                                        );
                                        let side = (shell_width - center - 16.0) * 0.5;
                                        ui.horizontal_top(|ui| {
                                            ui.spacing_mut().item_spacing.x = 0.0;
                                            ui.vertical(|ui| {
                                                ui.set_width(side);
                                                ui.spacing_mut().item_spacing.x =
                                                    if self.landscape { 5.0 } else { 7.0 * scale };
                                                let sidebar = theme::card(ui, side, |ui| {
                                                    let bottom = ui.cursor().min.y + center
                                                        - 2.0 * theme::card_padding(ui.ctx());
                                                    if !self.landscape {
                                                        ui.set_min_height(
                                                            center
                                                                - 2.0
                                                                    * theme::card_padding(ui.ctx()),
                                                        );
                                                    }
                                                    self.tower_stats(ui);
                                                    if !self.landscape {
                                                        ui.add_space(14.0 * scale);
                                                    }
                                                    self.inventory(ui);
                                                    if !self.landscape {
                                                        ui.add_space(
                                                            (bottom
                                                                - ui.cursor().min.y
                                                                - 77.0 * scale)
                                                                .max(0.0),
                                                        );
                                                    }
                                                    ui.add_space(if self.landscape {
                                                        2.0
                                                    } else {
                                                        12.0 * scale
                                                    });
                                                    self.compact_activity_preview(ui);
                                                });
                                                self.record("left_sidebar", &sidebar.response);
                                            });
                                            ui.add_space(8.0);
                                            ui.vertical(|ui| {
                                                ui.set_width(center);
                                                self.board_card(ui, center, now, self.landscape);
                                            });
                                            ui.add_space(8.0);
                                            let right = ui.vertical(|ui| {
                                                ui.set_width(side);
                                                ui.spacing_mut().item_spacing.x =
                                                    if self.landscape { 5.0 } else { 7.0 * scale };
                                                if self.landscape {
                                                    theme::card(ui, side, |ui| {
                                                        self.equipment(ui, true);
                                                        ui.add_space(4.0 * scale);
                                                        let keys =
                                                            ui.scope(|ui| self.keys(ui, true));
                                                        self.record("keyring", &keys.response);
                                                    });
                                                    let inspector = theme::card(ui, side, |ui| {
                                                        ui.set_min_height(168.0);
                                                        self.inspection(ui);
                                                    });
                                                    self.record(
                                                        "inspection_panel",
                                                        &inspector.response,
                                                    );
                                                    let toolbar = theme::card(ui, side, |ui| {
                                                        self.tower_controls(ui)
                                                    });
                                                    self.record("tower_toolbar", &toolbar.response);
                                                } else {
                                                    theme::card(ui, side, |ui| {
                                                        let bottom = ui.cursor().min.y + center
                                                            - 2.0 * theme::card_padding(ui.ctx());
                                                        ui.set_min_height(
                                                            center
                                                                - 2.0
                                                                    * theme::card_padding(ui.ctx()),
                                                        );
                                                        self.equipment(ui, true);
                                                        ui.add_space(4.0 * scale);
                                                        let keys =
                                                            ui.scope(|ui| self.keys(ui, true));
                                                        self.record("keyring", &keys.response);
                                                        ui.add_space(10.0 * scale);
                                                        ui.separator();
                                                        ui.add_space(6.0 * scale);
                                                        let inspector =
                                                            ui.scope(|ui| self.inspection(ui));
                                                        self.record(
                                                            "inspection_panel",
                                                            &inspector.response,
                                                        );
                                                        ui.add_space(
                                                            (bottom
                                                                - ui.cursor().min.y
                                                                - 82.0 * scale)
                                                                .max(0.0),
                                                        );
                                                        let toolbar =
                                                            ui.scope(|ui| self.tower_controls(ui));
                                                        self.record(
                                                            "tower_toolbar",
                                                            &toolbar.response,
                                                        );
                                                    });
                                                }
                                            });
                                            self.record("right_sidebar", &right.response);
                                        });
                                    } else {
                                        let stats =
                                            theme::frame(ui.ctx()).inner_margin(8).show(ui, |ui| {
                                                ui.vertical(|ui| {
                                                    ui.set_width(shell_width - 16.0);
                                                    self.stats(ui, true);
                                                });
                                            });
                                        self.record("stats", &stats.response);
                                        self.record("keyring", &stats.response);
                                        ui.add_space(10.0);
                                        theme::card(ui, shell_width, |ui| self.inventory(ui));
                                        ui.add_space(12.0);
                                        self.board_card(ui, shell_width, now, true);
                                        ui.add_space(12.0);
                                        theme::card(ui, shell_width, |ui| self.inspection(ui));
                                        ui.add_space(12.0);
                                        theme::card(ui, shell_width, |ui| self.journal(ui));
                                    }
                                });
                            });
                        });
                });
            self.keyboard();
            self.dialogs(now);
            self.settings_window();
            self.journal_history_dialog();
            self.enemy_list_dialog();
        }
        if let Some((message, until)) = &self.toast
            && now < *until
        {
            egui::Area::new(egui::Id::new("toast"))
                .anchor(Align2::CENTER_BOTTOM, Vec2::new(0.0, -22.0))
                .show(&self.context, |ui| {
                    egui::Frame::new()
                        .fill(theme::colors(ui.ctx()).surface)
                        .stroke(Stroke::new(1.0, theme::colors(ui.ctx()).metal))
                        .corner_radius(8)
                        .inner_margin(16)
                        .show(ui, |ui| {
                            ui.label(
                                RichText::new(translate_text(&self.locale, message)).size(18.0),
                            );
                        });
                });
        }
        self.context.request_repaint_after(Duration::from_millis(
            if self.busy() || !self.route.is_empty() {
                16
            } else {
                100
            },
        ));
    }
    fn clear_color(&self, _visuals: &egui::Visuals) -> [f32; 4] {
        theme::colors(&self.context).bg.to_normalized_gamma_f32()
    }
}

/// Append only activities completed by presentation, preserving stable log IDs.
/// Intermediate snapshot text may be copied only before the current effect;
/// battle records are committed by their own completed animation.
fn append_visible_activity(
    visual: &mut Value,
    snapshot: &Value,
    text: Value,
    log_id: Option<u64>,
) -> bool {
    if !text.is_string() {
        return false;
    }
    if !visual["log"].is_array() {
        visual["log"] = json!([]);
    }
    let start = visual["log_start"].as_u64().unwrap_or(0);
    let next = start.saturating_add(visual["log"].as_array().map_or(0, |log| log.len()) as u64);
    let snapshot_start = snapshot["log_start"].as_u64().unwrap_or(0);
    let id = log_id
        .or_else(|| {
            snapshot["log"].as_array().and_then(|log| {
                log.iter().enumerate().find_map(|(index, candidate)| {
                    let id = snapshot_start.saturating_add(index as u64);
                    (id >= next && candidate == &text).then_some(id)
                })
            })
        })
        .unwrap_or(next);
    if id < next {
        return id >= start && visual["log"][(id - start) as usize] == text;
    }
    let mut prefix = vec![];
    for candidate_id in next..id {
        // Intermediate completed activity may have no animation. A battle
        // record is copied only by finish_effect, never from future state.
        if snapshot["battle_log"].as_array().is_some_and(|records| {
            records
                .iter()
                .any(|record| record["log_id"].as_u64() == Some(candidate_id))
        }) {
            return false;
        }
        let Some(candidate) = candidate_id
            .checked_sub(snapshot_start)
            .and_then(|offset| snapshot["log"].get(offset as usize))
            .filter(|entry| entry.is_string())
        else {
            return false;
        };
        prefix.push(candidate.clone());
    }
    let log = visual["log"].as_array_mut().expect("log is an array");
    log.extend(prefix);
    log.push(text);
    let dropped = log.len().saturating_sub(100);
    log.drain(..dropped);
    let start = start.saturating_add(dropped as u64);
    let end = start.saturating_add(log.len() as u64);
    visual["log_start"] = json!(start);
    if let Some(records) = visual["battle_log"].as_array_mut() {
        records.retain(|record| {
            record["log_id"]
                .as_u64()
                .is_some_and(|id| id >= start && id < end)
        });
    }
    true
}

fn visual_has_wisdom_orb(visual: &Value) -> bool {
    visual["player"]["inventory"]
        .as_array()
        .is_some_and(|items| items.iter().any(|item| item == "wisdom_orb"))
}

fn visual_has_hero_orb(visual: &Value) -> bool {
    visual["player"]["inventory"]
        .as_array()
        .is_some_and(|items| items.iter().any(|item| item == "hero_orb"))
}

fn enemy_overview_header(
    ui: &egui::Ui,
    rect: Rect,
    label: &str,
    icon: Icon,
    color: Color32,
    scale: f32,
) {
    let galley = ui.painter().layout_no_wrap(
        label.into(),
        FontId::proportional(12.0 * scale),
        theme::colors(ui.ctx()).muted,
    );
    let text_x = rect.right() - 10.0 * scale - galley.size().x;
    theme::icon(
        ui.painter(),
        Rect::from_center_size(
            egui::pos2(text_x - 12.0 * scale, rect.center().y),
            Vec2::splat(13.0 * scale),
        ),
        icon,
        color,
    );
    ui.painter().galley(
        egui::pos2(text_x, rect.center().y - galley.size().y / 2.0),
        galley,
        theme::colors(ui.ctx()).muted,
    );
}

#[allow(clippy::too_many_arguments)]
fn enemy_overview_value(
    ui: &egui::Ui,
    rect: Rect,
    label: &str,
    value: &str,
    icon: Icon,
    color: Color32,
    scale: f32,
    label_visible: bool,
    damage: bool,
) -> Value {
    let value_rect = if label_visible {
        let header = Rect::from_min_size(rect.min, Vec2::new(rect.width(), 17.0 * scale));
        enemy_overview_header(ui, header, label, icon, color, scale);
        Rect::from_min_max(
            egui::pos2(rect.left() + 10.0 * scale, header.bottom()),
            egui::pos2(rect.right() - 10.0 * scale, rect.bottom()),
        )
    } else {
        rect.shrink2(Vec2::new(10.0 * scale, 4.0 * scale))
    };
    let font_size = 18.0 * scale;
    let value_color = if damage {
        color
    } else {
        theme::colors(ui.ctx()).text
    };
    let mut galley =
        ui.painter()
            .layout_no_wrap(value.into(), FontId::proportional(font_size), value_color);
    let fit = (value_rect.width() / galley.size().x.max(1.0)).min(1.0);
    let font_size = font_size * fit;
    if fit < 1.0 {
        galley =
            ui.painter()
                .layout_no_wrap(value.into(), FontId::proportional(font_size), value_color);
    }
    ui.painter().galley(
        egui::pos2(
            value_rect.right() - galley.size().x,
            value_rect.center().y - galley.size().y / 2.0,
        ),
        galley.clone(),
        value_color,
    );
    json!({"x":value_rect.left(),"y":value_rect.top(),"w":value_rect.width(),"h":value_rect.height(),
        "font_size":font_size,"text":value,"text_w":galley.size().x})
}

fn enemy_stat_cell(
    ui: &mut egui::Ui,
    label: &str,
    value: &str,
    icon: Icon,
    color: Color32,
    size: f32,
) -> egui::Response {
    let (rect, response) =
        ui.allocate_exact_size(Vec2::new(ui.available_width(), 22.0), egui::Sense::hover());
    let colors = theme::colors(ui.ctx());
    ui.painter()
        .rect_filled(rect, 4.0, colors.raised.linear_multiply(0.45));
    ui.painter().hline(
        rect.left() + 6.0..=rect.right() - 6.0,
        rect.bottom(),
        egui::Stroke::new(0.5, colors.border.linear_multiply(0.24)),
    );
    theme::icon(
        ui.painter(),
        Rect::from_center_size(
            egui::pos2(rect.left() + 12.0, rect.center().y),
            Vec2::splat(16.0),
        ),
        icon,
        color,
    );
    let value_rect = Rect::from_min_max(
        egui::pos2(rect.left() + 30.0, rect.top() + 1.0),
        rect.max - Vec2::new(8.0, 1.0),
    );
    fitted_value(ui, value_rect, value, size, true);
    response.on_hover_text(format!("{label}: {value}"))
}

fn fitted_value(ui: &egui::Ui, rect: Rect, value: &str, size: f32, right: bool) {
    let mut size = size;
    let mut galley = ui.painter().layout_no_wrap(
        value.into(),
        FontId::proportional(size),
        theme::colors(ui.ctx()).text,
    );
    for _ in 0..4 {
        let scale = (rect.width() / galley.size().x.max(1.0))
            .min(rect.height() / galley.size().y.max(1.0))
            .min(1.0);
        if scale >= 1.0 {
            break;
        }
        size = (size * scale - 0.1).max(1.0);
        galley = ui.painter().layout_no_wrap(
            value.into(),
            FontId::proportional(size),
            theme::colors(ui.ctx()).text,
        );
    }
    let x = if right {
        rect.right() - galley.size().x
    } else {
        rect.left()
    };
    ui.painter().galley(
        egui::pos2(x, rect.center().y - galley.size().y / 2.0),
        galley,
        theme::colors(ui.ctx()).text,
    );
}

/// Presentation may expose a floor-effect player before the final snapshot.
/// Match metadata only after filtering to that visually owned inventory.
fn visible_inventory_items(visual: &Value, snapshot: &Value, campaign: &Campaign) -> Vec<Value> {
    visual["player"]["inventory"]
        .as_array()
        .into_iter()
        .flatten()
        .filter_map(Value::as_str)
        .filter(|item| !campaign.is_equipment(item))
        .map(|item| {
            let metadata = visual["inventory_items"]
                .as_array()
                .into_iter()
                .flatten()
                .chain(snapshot["inventory_items"].as_array().into_iter().flatten())
                .find(|entry| entry["id"] == item);
            let mut entry = metadata.cloned().unwrap_or_else(|| {
                let definition = campaign
                    .tiles
                    .values()
                    .find(|def| def.item.as_deref() == Some(item));
                json!({
                    "id": item,
                    "name": definition.map(|def| def.name.as_str()).unwrap_or(item),
                    "sprite": definition.map(|def| &def.sprite),
                    "usable": false,
                })
            });
            // A cached record can predate a visible floor-effect player update.
            if let Some(charges) = visual["player"]["item_charges"][item].as_u64() {
                entry["charges"] = json!(charges);
            }
            entry
        })
        .collect()
}

const ORIGINAL_SPECIAL_ITEMS: [&str; 15] = [
    "hero_orb",
    "wisdom_orb",
    "flying_orb",
    "cross",
    "elixir",
    "mattock",
    "bomb",
    "warp_staff",
    "up_wing",
    "down_wing",
    "dragon_slayer",
    "snow_crystal",
    "magic_key",
    "super_mattock",
    "lucky_gold",
];

/// Reserve the original inventory positions without exposing any unowned item.
/// A partial/custom campaign keeps only its actual items instead of gaining
/// empty original slots merely because it uses the original Flight rule.
fn inventory_slots(visual: &Value, snapshot: &Value, campaign: &Campaign) -> Vec<Option<Value>> {
    let items = visible_inventory_items(visual, snapshot, campaign);
    let original_slots = campaign.rules["flying_original_selection"] == true
        && ORIGINAL_SPECIAL_ITEMS.iter().all(|id| {
            campaign.tiles.values().any(|tile| {
                tile.kind == tos_core::TileKind::Item && tile.item.as_deref() == Some(*id)
            })
        });
    if !original_slots {
        return items.into_iter().map(Some).collect();
    }
    let mut slots: Vec<_> = ORIGINAL_SPECIAL_ITEMS
        .iter()
        .map(|id| items.iter().find(|item| item["id"] == *id).cloned())
        .collect();
    slots.extend(
        items
            .into_iter()
            .filter(|item| !ORIGINAL_SPECIAL_ITEMS.contains(&item["id"].as_str().unwrap_or("")))
            .map(Some),
    );
    slots
}

/// Render the slot in the visible presentation state, never a later pickup.
fn visible_equipment_item(
    visual: &Value,
    snapshot: &Value,
    campaign: &Campaign,
    slot: &str,
) -> Option<Value> {
    let id = visual["player"][slot].as_str()?;
    visual["equipment"][slot]
        .as_object()
        .filter(|item| item.get("id").is_some_and(|value| value == id))
        .or_else(|| {
            snapshot["equipment"][slot]
                .as_object()
                .filter(|item| item.get("id").is_some_and(|value| value == id))
        })
        .map(|item| json!(item))
        .or_else(|| {
            let definition = campaign
                .tiles
                .values()
                .find(|tile| tile.item.as_deref() == Some(id));
            Some(json!({
                "id": id,
                "name": definition.map(|tile| tile.name.as_str()).unwrap_or(id),
                "sprite": definition.map(|tile| &tile.sprite),
                "usable": false,
            }))
        })
}

/// Only the engine's persisted actual contact enters the unforecasted panel.
fn visible_last_encounter(visual: &Value) -> Option<&Value> {
    visual["last_encounter"].as_object()?;
    Some(&visual["last_encounter"])
}

fn item_tooltip(locale: &str, item: &Value, name: &str) -> String {
    let mut lines = vec![name.to_owned()];
    if item["id"] == "hero_orb" {
        lines.push(tr(locale, "item_hero_open"));
    }
    let usage = &item["usage"];
    if let Some(description) = usage["description"].as_str() {
        lines.push(translate_text(locale, description));
    }
    if let Some(charges) = item["charges"].as_u64() {
        lines.push(tr(locale, "item_charges").replace("{charges}", &charges.to_string()));
    }
    let status = match usage["activation"].as_str() {
        Some("passive") => Some("item_passive"),
        Some("none") => Some("item_no_action"),
        Some("use_item") if usage["consumable"] == true => {
            Some(if usage["remaining_charges"].is_number() {
                "item_charged_consumption"
            } else {
                "item_consumable"
            })
        }
        Some("use_item") => Some("item_reusable"),
        _ => None,
    };
    if let Some(status) = status {
        lines.push(tr(locale, status));
    }
    lines.extend(
        usage["restrictions"]
            .as_array()
            .into_iter()
            .flatten()
            .filter_map(Value::as_str)
            .map(|text| translate_text(locale, text)),
    );
    lines.join("\n\n")
}

fn original_campaign_upgrade(source: &str) -> Option<&'static str> {
    if let Ok(engine) = Engine::from_json(source) {
        let saved: Value = serde_json::from_str(&engine.save_json()).unwrap_or_default();
        if [
            "56277325ec91e254",
            "800993184d7842ca",
            "70293e17a4e914ca",
            "0ababefe999bbdfb",
            "ad358ec82db8b9ef",
            "c3e406503a26e7f9",
            "abd9d284f2e9b303",
            "689db6b6a00a3400",
        ]
        .contains(&saved["campaign_fingerprint"].as_str().unwrap_or(""))
        {
            return Some(include_str!("../../../data/campaign.json"));
        }
    }
    None
}

fn upgrade_original_campaign(source: String) -> String {
    if let Some(updated) = original_campaign_upgrade(&source) {
        let _ = platform::write("tos-rust:campaign:recovery", &source);
        let _ = platform::write(CAMPAIGN, updated);
        return updated.to_owned();
    }
    source
}

fn restore_journey(engine: &mut Engine, source: &str) -> Result<Option<String>, String> {
    let original_error = match engine.load_json(source) {
        Ok(()) => return Ok(None),
        Err(error) => error,
    };
    let mut saved: Value = serde_json::from_str(source).map_err(|_| original_error.clone())?;
    if ![
        "56277325ec91e254",
        "800993184d7842ca",
        "70293e17a4e914ca",
        "0ababefe999bbdfb",
        "ad358ec82db8b9ef",
        "c3e406503a26e7f9",
        "abd9d284f2e9b303",
        "689db6b6a00a3400",
    ]
    .contains(&saved["campaign_fingerprint"].as_str().unwrap_or(""))
    {
        return Err(original_error);
    }
    let bundled = Engine::from_json(include_str!("../../../data/campaign.json"))?;
    let current: Value = serde_json::from_str(&engine.save_json()).expect("core save");
    let expected: Value = serde_json::from_str(&bundled.save_json()).expect("bundled core save");
    if current["campaign_fingerprint"] != expected["campaign_fingerprint"] {
        return Err(original_error);
    }
    saved["campaign_fingerprint"] = expected["campaign_fingerprint"].clone();
    // A newly restored arrival scene must not ambush an existing journey
    // again on a floor it already reached through stairs.
    let highest = saved["highest_stair_floor"].as_i64().unwrap_or_else(|| {
        saved["visited_floors"]
            .as_array()
            .into_iter()
            .flatten()
            .filter_map(Value::as_i64)
            .max()
            .unwrap_or(1)
    });
    for (floor, events) in [
        (
            32,
            &[
                "floor_32_golden_knight_arrival",
                "floor_32_golden_knight_retreat",
            ][..],
        ),
        (42, &["floor_42_zeno_and_golden_knight_arrival"][..]),
    ] {
        if highest >= floor {
            for event in events {
                if saved["event_counts"][*event].is_null() {
                    saved["event_counts"][*event] = json!(1);
                }
            }
        }
    }
    if saved["cycle"].is_null() {
        saved["cycle"] = json!(1);
    }
    if saved["status"] == "won" && saved["player"]["floor"] == 50 {
        saved["status"] = json!("playing");
    }
    let migrated = saved.to_string();
    engine.load_json(&migrated)?;
    Ok(Some(migrated))
}

fn section(ui: &mut egui::Ui, title: &str, icon: Icon) {
    let scale = theme::scale(ui.ctx());
    ui.horizontal(|ui| {
        let (rect, _) = ui.allocate_exact_size(Vec2::splat(19.0 * scale), egui::Sense::hover());
        theme::icon(ui.painter(), rect, icon, theme::colors(ui.ctx()).metal);
        ui.label(
            RichText::new(title)
                .size(
                    if theme::card_padding(ui.ctx()) < 10.0 {
                        16.0
                    } else {
                        18.0
                    } * scale,
                )
                .strong()
                .color(theme::colors(ui.ctx()).text),
        );
    });
}

fn metric(
    ui: &mut egui::Ui,
    width: f32,
    label: &str,
    value: &str,
    color: Color32,
    icon: Icon,
    compact: bool,
) {
    let scale = theme::scale(ui.ctx());
    let (rect, response) = ui.allocate_exact_size(
        Vec2::new(width, if compact { 54.0 } else { 85.0 } * scale),
        egui::Sense::hover(),
    );
    ui.painter()
        .rect_filled(rect, 10.0 * scale, theme::colors(ui.ctx()).raised);
    let inset = if compact { 9.0 } else { 12.0 } * scale;
    let icon_rect = Rect::from_min_size(
        rect.min + Vec2::new(inset, 12.0 * scale),
        Vec2::splat(15.0 * scale),
    );
    theme::icon(ui.painter(), icon_rect, icon, color);
    let mut label_job = egui::text::LayoutJob::simple(
        label.into(),
        FontId::proportional(if compact { 12.0 } else { 14.0 } * scale),
        theme::colors(ui.ctx()).muted,
        (rect.width() - inset * 2.0 - 22.0 * scale).max(1.0),
    );
    label_job.wrap.max_rows = 1;
    ui.painter().galley(
        rect.min
            + Vec2::new(
                inset + 22.0 * scale,
                if compact { 9.0 } else { 12.0 } * scale,
            ),
        ui.painter().layout_job(label_job),
        theme::colors(ui.ctx()).muted,
    );
    let value_rect = Rect::from_min_max(
        rect.min + Vec2::new(inset, if compact { 25.0 } else { 32.0 } * scale),
        rect.max - Vec2::new(inset, if compact { 3.0 } else { 9.0 } * scale),
    );
    let mut font_size = if compact { 24.0 } else { 28.0 } * scale;
    let mut galley = ui.painter().layout_no_wrap(
        value.into(),
        FontId::proportional(font_size),
        theme::colors(ui.ctx()).text,
    );
    // Measure the actual glyphs, including grouping commas, rather than
    // estimating from character count. Never abbreviate or drop stat digits.
    for _ in 0..4 {
        let scale = (value_rect.width() / galley.size().x.max(1.0))
            .min(value_rect.height() / galley.size().y.max(1.0))
            .min(1.0);
        if scale >= 1.0 {
            break;
        }
        font_size = (font_size * scale - 0.1).max(1.0);
        galley = ui.painter().layout_no_wrap(
            value.into(),
            FontId::proportional(font_size),
            theme::colors(ui.ctx()).text,
        );
    }
    ui.painter().galley(
        egui::pos2(
            value_rect.left(),
            value_rect.center().y - galley.size().y / 2.0,
        ),
        galley,
        theme::colors(ui.ctx()).text,
    );
    response.on_hover_text(format!("{label}: {value}"));
}
fn number(value: &Value) -> String {
    value
        .as_i64()
        .map(|n| {
            let source = n.to_string();
            let mut result = String::new();
            for (i, c) in source.chars().rev().enumerate() {
                if i > 0 && i % 3 == 0 && c != '-' {
                    result.push(',');
                }
                result.push(c);
            }
            result.chars().rev().collect()
        })
        .unwrap_or_else(|| "—".into())
}
fn music_for_floor(floor: i64) -> &'static str {
    match floor {
        0 => "a_027xgw",
        1..=10 => "b_067xgw",
        11..=20 => "b_058xgw",
        21..=30 => "b_110xgw",
        31..=40 => "a_118xgw",
        41..=49 => "a_019xgw",
        _ => "b_018xgw",
    }
}
fn configure(ctx: &egui::Context, chinese: Option<Vec<u8>>) {
    install_fonts(ctx, chinese);
    let configured = ctx.data_mut(|data| {
        let id = egui::Id::new("tower_style_configured");
        let configured = data.get_temp::<bool>(id).unwrap_or(false);
        data.insert_temp(id, true);
        configured
    });
    if configured {
        return;
    }
    let mut style = (*ctx.style_of(egui::Theme::Dark)).clone();
    style.visuals = egui::Visuals::dark();
    style.visuals.override_text_color = Some(TEXT);
    style.visuals.panel_fill = NAVY;
    style.visuals.window_fill = CARD;
    style.visuals.widgets.noninteractive.bg_fill = CARD;
    style.visuals.widgets.inactive.bg_fill = theme::SURFACE_RAISED;
    style.visuals.widgets.inactive.weak_bg_fill = theme::SURFACE_RAISED;
    style.visuals.widgets.hovered.bg_fill = Color32::from_rgb(59, 68, 81);
    style.visuals.widgets.hovered.weak_bg_fill = Color32::from_rgb(59, 68, 81);
    style.visuals.selection.bg_fill = Color32::from_rgb(93, 77, 47);
    style.visuals.selection.stroke = Stroke::new(1.0, GOLD);
    style.visuals.window_corner_radius = egui::CornerRadius::same(16);
    style.visuals.window_stroke = Stroke::new(1.0, theme::BORDER);
    style.visuals.widgets.inactive.bg_stroke = Stroke::new(1.0, theme::BORDER);
    style.visuals.widgets.hovered.bg_stroke = Stroke::new(1.0, GOLD);
    style.visuals.widgets.active.bg_stroke = Stroke::new(1.0, GOLD);
    style.spacing.item_spacing = Vec2::new(8.0, 8.0);
    style.spacing.icon_width = 18.0;
    style.spacing.icon_spacing = 8.0;
    style.visuals.widgets.inactive.corner_radius = egui::CornerRadius::same(8);
    style.visuals.widgets.hovered.corner_radius = egui::CornerRadius::same(8);
    style.visuals.widgets.active.corner_radius = egui::CornerRadius::same(8);
    style.spacing.button_padding = Vec2::new(12.0, 8.0);
    style.spacing.window_margin = egui::Margin::same(22);
    style
        .text_styles
        .insert(egui::TextStyle::Body, FontId::proportional(17.0));
    style
        .text_styles
        .insert(egui::TextStyle::Button, FontId::proportional(17.0));
    style
        .text_styles
        .insert(egui::TextStyle::Small, FontId::proportional(15.0));
    style
        .text_styles
        .insert(egui::TextStyle::Heading, FontId::proportional(28.0));
    style
        .text_styles
        .insert(egui::TextStyle::Monospace, FontId::monospace(16.0));
    ctx.set_style_of(egui::Theme::Dark, style);
    ctx.set_theme(egui::Theme::Dark);
}
fn install_fonts(ctx: &egui::Context, chinese: Option<Vec<u8>>) {
    use std::sync::Arc;
    let mut fonts = egui::FontDefinitions::default();
    fonts.font_data.insert(
        "sans".into(),
        Arc::new(
            egui::FontData::from_static(include_bytes!("../../../web/fonts/DM-Sans.ttf")).tweak(
                egui::FontTweak {
                    coords: egui::epaint::text::VariationCoords::new([(b"wght", 400.0)]),
                    ..Default::default()
                },
            ),
        ),
    );
    fonts.font_data.insert(
        "serif".into(),
        Arc::new(egui::FontData::from_static(include_bytes!(
            "../../../web/fonts/Cormorant-Garamond.ttf"
        ))),
    );
    fonts
        .families
        .entry(egui::FontFamily::Proportional)
        .or_default()
        .insert(0, "sans".into());
    fonts.families.insert(
        egui::FontFamily::Name("serif".into()),
        vec!["serif".into(), "sans".into()],
    );
    if let Some(bytes) = chinese {
        fonts.font_data.insert(
            "chinese".into(),
            // Google's variable Noto Sans SC defaults to weight 100 (Thin).
            // Resolve a readable Regular face consistently on both renderers.
            Arc::new(egui::FontData::from_owned(bytes).tweak(egui::FontTweak {
                coords: egui::epaint::text::VariationCoords::new([(b"wght", 400.0)]),
                ..Default::default()
            })),
        );
        for family in fonts.families.values_mut() {
            family.push("chinese".into());
        }
    }
    ctx.set_fonts(fonts);
}

#[cfg(test)]
mod migration_tests {
    use super::*;
    #[test]
    fn floor_enemy_groups_merge_positions_and_sprites_but_preserve_visible_variants() {
        let enemy = json!({"name":"Octopus","hp":1200,"attack":180,"defense":20,"gold":50,"damage":160,"can_win":true,"reason":"","rounds":2});
        let part = json!({"id":97,"name":"Custom octopus","sprite":97,"x":2,"y":3,"enemy":enemy});
        let mut second = part.clone();
        second["id"] = json!(98);
        second["sprite"] = json!(98);
        second["x"] = json!(4);
        let mut body = part.clone();
        body["enemy"]["gold"] = json!(100);
        let mut override_stats = part.clone();
        override_stats["enemy"]["hp"] = json!(1500);
        let mut forecast = part.clone();
        forecast["enemy"]["damage"] = json!(240);
        let mut reason = part.clone();
        reason["enemy"]["reason"] = json!("A revealed restriction");
        let groups = group_floor_enemies(
            vec![part, second, body, override_stats, forecast, reason],
            "en",
        );
        assert_eq!(groups.len(), 5);
        assert_eq!(groups[0].count, 2);
        assert_eq!(groups[1].inspection["enemy"]["gold"], 100);
        assert!(groups.iter().skip(1).all(|group| group.count == 1));
    }

    #[test]
    fn activity_presentation_keeps_retained_ids_and_defers_future_battle_facts() {
        let mut visual = json!({"log_start":400,"log":(0..100).map(|i|format!("old {i}")).collect::<Vec<_>>(),"battle_log":[{"log_id":400},{"log_id":450}]});
        let snapshot = json!({"log_start":403,"log":(403..500).map(|i|format!("old {}",i-400)).chain(["before battle".into(),"battle".into(),"after battle".into()]).collect::<Vec<_>>(),"battle_log":[{"log_id":501}]});
        assert!(append_visible_activity(
            &mut visual,
            &snapshot,
            json!("battle"),
            Some(501)
        ));
        assert_eq!(visual["log_start"], 402);
        assert_eq!(visual["log"].as_array().unwrap().len(), 100);
        assert_eq!(visual["log"][98], "before battle");
        assert_eq!(visual["log"][99], "battle");
        assert_eq!(visual["battle_log"], json!([{"log_id":450}]));
        assert!(
            !visual["log"]
                .as_array()
                .unwrap()
                .contains(&json!("after battle"))
        );
        let unchanged = visual.clone();
        assert!(append_visible_activity(
            &mut visual,
            &snapshot,
            json!("battle"),
            Some(501)
        ));
        assert_eq!(
            visual, unchanged,
            "repeated effects do not append duplicate activity"
        );
    }

    #[test]
    fn activity_gaps_never_copy_a_future_battle_and_repeated_dialogue_uses_exact_ids() {
        let mut visual = json!({"log_start":10,"log":["old"],"battle_log":[]});
        let snapshot = json!({"log_start":10,"log":["old","repeat","battle","repeat"],"battle_log":[{"log_id":12}]});
        assert!(append_visible_activity(
            &mut visual,
            &snapshot,
            json!("repeat"),
            Some(11)
        ));
        let unchanged = visual.clone();
        assert!(!append_visible_activity(
            &mut visual,
            &snapshot,
            json!("repeat"),
            Some(13)
        ));
        assert_eq!(
            visual, unchanged,
            "an unresolved intermediate battle stays hidden"
        );
        assert!(append_visible_activity(
            &mut visual,
            &snapshot,
            json!("battle"),
            Some(12)
        ));
        assert!(append_visible_activity(
            &mut visual,
            &snapshot,
            json!("repeat"),
            Some(13)
        ));
        assert_eq!(visual["log"], snapshot["log"]);
    }

    #[test]
    fn activity_gap_outside_the_retained_snapshot_waits_for_final_sync() {
        let mut visual = json!({"log_start":10,"log":["old"],"battle_log":[]});
        let unchanged = visual.clone();
        let snapshot = json!({"log_start":100,"log":["retained","battle","future"],"battle_log":[{"log_id":101}]});
        assert!(!append_visible_activity(
            &mut visual,
            &snapshot,
            json!("battle"),
            Some(101)
        ));
        assert_eq!(
            visual, unchanged,
            "missing prefix facts cannot attach a future record to older strings"
        );
    }

    #[test]
    fn compact_metrics_keep_large_values_complete_inside_their_cells() {
        for value in ["396,000", "1,000,000,000"] {
            let context = egui::Context::default();
            configure(&context, None);
            let mut frame = context.run_ui(egui::RawInput::default(), |ui| {
                metric(ui, 78.0, "Health", value, theme::RED, Icon::Heart, true);
            });
            frame.textures_delta.clear();
            let cell = frame
                .shapes
                .iter()
                .find_map(|shape| match &shape.shape {
                    egui::Shape::Rect(shape) if shape.rect.size() == Vec2::new(78.0, 54.0) => {
                        Some(shape.rect)
                    }
                    _ => None,
                })
                .expect("metric cell was painted");
            let number = frame
                .shapes
                .iter()
                .find_map(|shape| match &shape.shape {
                    egui::Shape::Text(shape) if shape.galley.job.text == value => Some(shape),
                    _ => None,
                })
                .expect("all numeric characters remain in the rendered galley");
            let bounds = number.galley.rect.translate(number.pos.to_vec2());
            assert!(
                cell.shrink(2.0).contains_rect(bounds),
                "{value}: {bounds:?} outside {cell:?}"
            );
            assert_eq!(number.galley.rows.len(), 1);
        }
    }

    #[test]
    fn original_inventory_reserves_neutral_slots_without_snapshot_ownership_leaks() {
        let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let visual = json!({"player":{"inventory":[]}});
        let snapshot = json!({"player":{"inventory":["bomb"]},
            "inventory_items":[{"id":"bomb","name":"Hidden name","sprite":42,"usable":true}]});
        let slots = inventory_slots(&visual, &snapshot, engine.campaign());
        assert_eq!(slots.len(), 15);
        assert!(slots.iter().all(Option::is_none));
    }

    #[test]
    fn original_inventory_positions_stay_fixed_after_consumption_and_append_custom_items() {
        let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut visual = json!({"player":{"inventory":["super_mattock","wisdom_orb","custom_trinket"]},
            "inventory_items":[{"id":"super_mattock","usable":true},{"id":"wisdom_orb","usable":true},
                {"id":"custom_trinket","usable":false}]});
        let slots = inventory_slots(&visual, &Value::Null, engine.campaign());
        assert_eq!(slots.len(), 16);
        assert_eq!(slots[1].as_ref().unwrap()["id"], "wisdom_orb");
        assert_eq!(slots[13].as_ref().unwrap()["id"], "super_mattock");
        assert_eq!(slots[15].as_ref().unwrap()["id"], "custom_trinket");
        visual["player"]["inventory"] = json!(["wisdom_orb", "custom_trinket"]);
        let after = inventory_slots(&visual, &Value::Null, engine.campaign());
        assert_eq!(after.len(), 16);
        assert!(after[13].is_none());
        assert_eq!(after[1], slots[1]);
        assert_eq!(after[15], slots[15]);
    }

    #[test]
    fn partial_custom_campaign_does_not_gain_unconfigured_original_slots() {
        let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut campaign = engine.campaign().clone();
        let visual = json!({"player":{"inventory":["wisdom_orb"]}});
        campaign.tiles.remove("36");
        let slots = inventory_slots(&visual, &Value::Null, &campaign);
        assert_eq!(slots.len(), 1);
        assert_eq!(slots[0].as_ref().unwrap()["id"], "wisdom_orb");
    }

    #[test]
    fn equipment_slots_follow_visible_presentation_and_stay_out_of_special_inventory() {
        let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let visual = json!({
            "player":{"weapon":"sword_1","shield":null,"inventory":["sword_5","sword_1","sacred_shield","wisdom_orb"]},
            "equipment":{"weapon":{"id":"sword_1","name":"Iron Sword","usage":{"description":"Visible pickup"}}},
        });
        let snapshot = json!({
            "player":{"weapon":"sword_5","shield":"sacred_shield"},
            "equipment":{"weapon":{"id":"sword_5","name":"Sacred Sword"},"shield":{"id":"sacred_shield","name":"Sacred Shield"}},
            "inventory_items":[{"id":"wisdom_orb","usable":true}],
        });
        let weapon =
            visible_equipment_item(&visual, &snapshot, engine.campaign(), "weapon").unwrap();
        assert_eq!(weapon["id"], "sword_1");
        assert_eq!(weapon["usage"]["description"], "Visible pickup");
        assert!(visible_equipment_item(&visual, &snapshot, engine.campaign(), "shield").is_none());
        let items = visible_inventory_items(&visual, &snapshot, engine.campaign());
        assert_eq!(items.len(), 1);
        assert_eq!(items[0]["id"], "wisdom_orb");
        assert_eq!(tr("zh-CN", "weapon"), "武器");
        assert_eq!(tr("zh-CN", "shield"), "盾牌");
    }
    #[test]
    fn encountered_stats_panel_uses_actual_contact_instead_of_hovered_enemy() {
        let mut visual = json!({
            "last_encounter":null,
            "enemies":[{"hp":999,"attack":999,"defense":999}],
        });
        assert!(visible_last_encounter(&visual).is_none());
        visual["last_encounter"] =
            json!({"floor":1,"x":2,"y":1,"enemy_name":"Slime","hp":20,"attack":8,"defense":1});
        let encounter = visible_last_encounter(&visual).unwrap();
        assert_eq!(encounter["hp"], 20);
        assert!(encounter.get("damage").is_none());
        assert!(encounter.get("gold").is_none());
        assert_eq!(tr("zh-CN", "last_encounter"), "最近遭遇");
    }
    #[test]
    fn inventory_help_follows_visible_ownership_and_charge_updates() {
        let engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let visual = json!({
            "player":{"inventory":["warp_staff","mattock"],"item_charges":{"warp_staff":2}},
            "inventory_items":[{"id":"warp_staff","charges":3,"usable":true,
                "usage":{"description":"Visible staff","remaining_charges":3}}],
        });
        let snapshot = json!({"inventory_items":[
            {"id":"warp_staff","charges":1,"usage":{"description":"Future staff"}},
            {"id":"mattock","usable":true,"usage":{"description":"Newly visible mattock"}},
            {"id":"bomb","usable":true,"usage":{"description":"Not yet acquired"}},
        ]});
        let items = visible_inventory_items(&visual, &snapshot, engine.campaign());
        assert_eq!(items.len(), 2);
        assert_eq!(items[0]["id"], "warp_staff");
        assert_eq!(items[0]["charges"], 2);
        assert_eq!(items[0]["usage"]["description"], "Visible staff");
        assert_eq!(items[1]["id"], "mattock");
        assert_eq!(items[1]["usage"]["description"], "Newly visible mattock");
    }
    #[test]
    fn item_help_distinguishes_charge_consumption_and_keeps_custom_prose() {
        let item = json!({"charges":3,"usage":{
            "activation":"use_item","consumable":true,"remaining_charges":3,
            "description":"Warp to the point mirrored through the center of the current floor.",
            "restrictions":["Close any open conversation before use."]
        }});
        let tooltip = item_tooltip("zh-CN", &item, "传送法杖");
        assert!(tooltip.contains("本层以中心点"));
        assert!(tooltip.contains("剩余使用次数：3"));
        assert!(tooltip.contains("最后一次使用次数耗尽后消耗"));
        assert!(tooltip.contains("使用前请先关闭对话"));
        let custom = json!({"usage":{
            "activation":"use_item","consumable":false,
            "description":"Custom author's unlisted item instruction.","restrictions":[]
        }});
        let tooltip = item_tooltip("zh-CN", &custom, "Custom item");
        assert!(tooltip.contains("Custom author's unlisted item instruction."));
        assert!(tooltip.contains("可重复使用，不会消耗"));
    }
    #[test]
    fn known_original_save_migrates_with_player_progress() {
        let mut engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["campaign_fingerprint"] = json!("56277325ec91e254");
        saved["player"]["hp"] = json!(725);
        saved.as_object_mut().unwrap().remove("cycle");
        assert!(
            restore_journey(&mut engine, &saved.to_string())
                .unwrap()
                .is_some()
        );
        assert_eq!(engine.player().hp, 725);
        assert_eq!(engine.snapshot()["cycle"], 1);
    }
    #[test]
    fn previous_ui_save_preserves_backside_cycle_and_progress() {
        let mut engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["campaign_fingerprint"] = json!("800993184d7842ca");
        saved["cycle"] = json!(2);
        saved["player"]["hp"] = json!(7500);
        saved["player"]["gold"] = json!(128);
        saved["steps"] = json!(42);
        let floors = saved["floors"].clone();
        assert!(
            restore_journey(&mut engine, &saved.to_string())
                .unwrap()
                .is_some()
        );
        let restored: Value = serde_json::from_str(&engine.save_json()).unwrap();
        assert_eq!(restored["cycle"], 2);
        assert_eq!(restored["steps"], 42);
        assert_eq!(restored["floors"], floors);
        assert_eq!(engine.player().hp, 7500);
        assert_eq!(engine.player().gold, 128);
    }
    #[test]
    fn last_published_save_migrates_all_progress_without_inventing_clues() {
        let mut engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        let new_fingerprint = saved["campaign_fingerprint"].clone();
        saved["campaign_fingerprint"] = json!("70293e17a4e914ca");
        saved["cycle"] = json!(2);
        saved["player"]["hp"] = json!(1500);
        saved["player"]["gold"] = json!(314);
        saved["player"]["inventory"] = json!(["hero_orb", "wisdom_orb", "warp_staff"]);
        saved["player"]["item_charges"] = json!({"warp_staff":2});
        saved["steps"] = json!(314);
        saved["flags"] = json!(["backside", "npc_16_10_10_gift"]);
        saved["shop_visits"] = json!({"altar":2});
        saved["event_counts"] = json!({"opening_capture":1});
        saved["floors"]["1"][0] = json!(6);
        saved.as_object_mut().unwrap().remove("journal");
        assert!(
            restore_journey(&mut engine, &saved.to_string())
                .unwrap()
                .is_some()
        );
        saved["campaign_fingerprint"] = new_fingerprint;
        saved["journal"] = json!([]);
        let restored: Value = serde_json::from_str(&engine.save_json()).unwrap();
        assert_eq!(
            restored, saved,
            "every old progress field survives migration"
        );
        assert_eq!(engine.snapshot()["journal"], json!([]));
    }
    #[test]
    fn mechanics_revision_migrates_the_previous_campaign_and_complete_save() {
        let mut engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        let fingerprint = saved["campaign_fingerprint"].clone();
        saved["campaign_fingerprint"] = json!("abd9d284f2e9b303");
        saved["cycle"] = json!(2);
        saved["player"]["hp"] = json!(8123);
        saved["player"]["inventory"] = json!(["mattock", "hero_orb"]);
        saved["flags"] = json!(["captured"]);
        saved["event_counts"] = json!({"capture_on_floor_3":1});
        saved["floors"]["1"][0] = json!(6);
        saved["steps"] = json!(932);
        assert!(
            restore_journey(&mut engine, &saved.to_string())
                .unwrap()
                .is_some()
        );
        saved["campaign_fingerprint"] = fingerprint;
        assert_eq!(
            serde_json::from_str::<Value>(&engine.save_json()).unwrap(),
            saved
        );
    }
    #[test]
    fn stair_scene_revision_preserves_advanced_progress_without_replaying_arrivals() {
        let mut engine = Engine::from_json(include_str!("../../../data/campaign.json")).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["campaign_fingerprint"] = json!("689db6b6a00a3400");
        saved["highest_stair_floor"] = json!(42);
        saved["visited_floors"] = json!([1, 32, 42]);
        saved["player"]["hp"] = json!(8123);
        assert!(
            restore_journey(&mut engine, &saved.to_string())
                .unwrap()
                .is_some()
        );
        let restored: Value = serde_json::from_str(&engine.save_json()).unwrap();
        assert_eq!(restored["player"]["hp"], 8123);
        for event in [
            "floor_32_golden_knight_arrival",
            "floor_32_golden_knight_retreat",
            "floor_42_zeno_and_golden_knight_arrival",
        ] {
            assert_eq!(restored["event_counts"][event], 1);
        }
    }
    #[test]
    fn custom_campaign_and_unknown_save_are_not_migrated() {
        let mut campaign: Value =
            serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap();
        campaign["title"] = json!("Custom adventure");
        let mut engine = Engine::from_json(&campaign.to_string()).unwrap();
        let mut saved: Value = serde_json::from_str(&engine.save_json()).unwrap();
        saved["campaign_fingerprint"] = json!("56277325ec91e254");
        assert!(restore_journey(&mut engine, &saved.to_string()).is_err());
        saved["campaign_fingerprint"] = json!("unknown");
        assert!(restore_journey(&mut engine, &saved.to_string()).is_err());
        assert_eq!(engine.player().hp, 1000);
    }
}
