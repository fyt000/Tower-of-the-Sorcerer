use crate::{
    assets::{Art, stair_wipe_order},
    audio::Audio,
    editor::{CampaignEditor, EditorAction},
    locales::{entity_name, tr, translate_text},
    platform,
    theme::{self, BG as NAVY, GOLD, Icon, MUTED, SURFACE as CARD, TEXT},
};
use eframe::egui::{self, Align2, Color32, FontId, Rect, RichText, Stroke, Vec2};
use serde_json::{Value, json};
use std::{
    collections::{BTreeMap, BTreeSet, VecDeque},
    sync::mpsc,
    time::Duration,
};
use tos_core::Engine;

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
    route: VecDeque<String>,
    facing: String,
    hero_idle_at: f64,
    selected: Option<(usize, usize)>,
    settings: bool,
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
        let mut engine = Engine::from_json(&source).unwrap_or_else(|_| {
            Engine::from_json(include_str!("../../../data/campaign.json"))
                .expect("bundled campaign")
        });
        let mut recovery = None;
        if let Some(save) = platform::read(SAVE) {
            match restore_journey(&mut engine, &save) {
                Ok(Some(migrated)) => {
                    let _ = platform::write("tos-rust:save:recovery", &save);
                    let _ = platform::write(SAVE, &migrated);
                    recovery=Some("Your saved journey was migrated to the restored original campaign. A recovery copy is preserved.".into());
                }
                Ok(None) => {}
                Err(error) => {
                    let _ = platform::write("tos-rust:save:recovery", &save);
                    recovery = Some(format!(
                        "Saved journey needs migration: {error}. A recovery copy is preserved."
                    ));
                }
            }
        }
        let prefs: Value = platform::read(PREFS)
            .and_then(|s| serde_json::from_str(&s).ok())
            .unwrap_or_default();
        let snapshot = engine.snapshot();
        let editor = CampaignEditor::new(serde_json::to_value(&engine.campaign).unwrap());
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
        let campaign = serde_json::to_value(&engine.campaign).unwrap();
        self.engine = engine;
        self.snapshot = self.engine.snapshot();
        self.visual = self.snapshot.clone();
        self.queue.clear();
        self.active = None;
        self.hero_idle_at = 0.0;
        self.route.clear();
        self.selected = None;
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
        self.music_paused = false;
        self.music_override = None;
        self.persist();
        self.context.request_repaint();
        Ok(())
    }

    pub fn submit(&mut self, command: Value) {
        self.audio.unlock();
        self.visual = self.snapshot.clone();
        if let Some(direction) = command["direction"].as_str() {
            self.facing = direction.into();
            self.hero_idle_at = self.now() + self.ambient_interval();
        }
        match self.engine.command(command) {
            Ok(()) => {}
            Err(e) => {
                self.notify(e);
                return;
            }
        }
        self.snapshot = self.engine.snapshot();
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
    }

    pub fn debug_json(&self) -> Value {
        json!({"ready":true,"locale":self.locale,"visual_floor":self.visual["floor"],"visual_player":self.visual["player"],"visual_log":self.visual["log"],"editor_open":self.editor_open,"editor":self.editor.debug_json(),"bounds":self.bounds,"animation":self.active.as_ref().map(|a|a.effect["type"].clone()),"presentation_remaining":self.queue.len(),"path_remaining":self.route.len(),"animations_seen":self.animation_history,"animation_details":self.animation_details,"hero_pose":if self.active.as_ref().is_some_and(|a|a.effect["type"]=="move")||self.now()<self.hero_idle_at{"walking"}else{"idle"},"facing":self.facing,"battle":self.battle_progress(self.now()).map(|b|json!({"hero_hp":b.hero_hp,"enemy_hp":b.enemy_hp,"hero_turn":b.hero_turn,"completed":b.completed,"phase":b.phase})),"audio":{"unlocked":self.audio.unlocked,"enabled":self.audio.enabled,"effects_played":self.audio.effects_played,"music":self.audio.music_name,"error":self.audio.error},"sprites_loaded":self.assets.atlas.is_some()})
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
            let name = self.engine.campaign.rules["audio"]["floor_music"]
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
            let (cue, due) = if active.effect["type"] == "battle" {
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
        let expired = self
            .active
            .as_ref()
            .is_some_and(|a| a.effect["type"] != "dialogue" && now - a.start >= a.duration);
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
                            self.engine.campaign.rules["audio"]["music_cues"][id].as_str()
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
                    if !self.visual["log"].is_array() {
                        self.visual["log"] = json!([]);
                    }
                    if let Some(log) = self.visual["log"].as_array_mut() {
                        log.push(effect["text"].clone());
                        if log.len() > 100 {
                            log.remove(0);
                        }
                    }
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
                    self.submit(json!({"type":"move","direction":direction}));
                }
            }
        }
    }

    fn finish_effect(&mut self) {
        if let Some(active) = self.active.take() {
            let e = &active.effect;
            match e["type"].as_str().unwrap_or("") {
                "tile" => {
                    if e["floor"] == self.visual["floor"] {
                        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
                        let index = e["y"].as_u64().unwrap_or(0) as usize * width
                            + e["x"].as_u64().unwrap_or(0) as usize;
                        if let Some(tile) = self.visual["tiles"]
                            .as_array_mut()
                            .and_then(|v| v.get_mut(index))
                        {
                            *tile = e["tile"].clone();
                        }
                    }
                }
                "move" => {
                    self.hero_idle_at = self.now() + self.ambient_interval();
                    self.visual["player"]["x"] = e["to"]["x"].clone();
                    self.visual["player"]["y"] = e["to"]["y"].clone();
                }
                "battle" => {
                    let strikes = e["enemy_strikes"]
                        .as_i64()
                        .unwrap_or_else(|| e["rounds"].as_i64().unwrap_or(0));
                    self.visual["player"]["hp"] = json!(
                        (e["hero_hp"].as_i64().unwrap_or(0)
                            - strikes * e["enemy_hit"].as_i64().unwrap_or(0))
                        .max(0)
                    );
                }
                "move_tile" => {
                    if e["floor"] == self.visual["floor"] {
                        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
                        let from = e["from_y"].as_u64().unwrap_or(0) as usize * width
                            + e["from_x"].as_u64().unwrap_or(0) as usize;
                        let to = e["y"].as_u64().unwrap_or(0) as usize * width
                            + e["x"].as_u64().unwrap_or(0) as usize;
                        let empty = self.engine.campaign.rules["empty_tile"]
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
        let tiles = (0..self.engine.campaign.height)
            .flat_map(|y| (0..self.engine.campaign.width).map(move |x| (x, y)))
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

    fn busy(&self) -> bool {
        self.active.is_some() || !self.queue.is_empty()
    }

    fn ambient_interval(&self) -> f64 {
        self.engine.campaign.rules["presentation"]["ambient_frame_ms"]
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
            .filter(|a| a.effect["type"] == "battle")?;
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
        self.bounds.insert(id.into(),json!({"x":response.rect.min.x,"y":response.rect.min.y,"w":response.rect.width(),"h":response.rect.height()}));
    }

    fn header(&mut self, ui: &mut egui::Ui) {
        let narrow = ui.available_width() < 1060.0;
        ui.horizontal(|ui| {
            let (mark, _) = ui.allocate_exact_size(
                Vec2::splat(if narrow { 36.0 } else { 48.0 }),
                egui::Sense::hover(),
            );
            theme::icon(ui.painter(), mark.shrink(5.0), Icon::Tower, GOLD);
            ui.add_space(if narrow { 2.0 } else { 8.0 });
            ui.vertical(|ui| {
                if !narrow {
                    theme::caption(ui, &self.text("classic_adventure"));
                }
                ui.label(
                    RichText::new(translate_text(&self.locale, &self.engine.campaign.title))
                        .font(FontId::new(
                            if narrow { 29.0 } else { 40.0 },
                            egui::FontFamily::Name("serif".into()),
                        ))
                        .color(TEXT),
                );
            });
            if !narrow {
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    self.header_controls(ui, false)
                });
            }
        });
        if narrow {
            ui.add_space(8.0);
            ui.horizontal(|ui| self.header_controls(ui, true));
        }
        ui.add_space(if narrow { 6.0 } else { 24.0 });
    }

    fn header_controls(&mut self, ui: &mut egui::Ui, narrow: bool) {
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
        let save = theme::action(ui, self.text("save_short"), Icon::Save, true);
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
        let value = json!({"campaign":self.engine.campaign,"save":serde_json::from_str::<Value>(&self.engine.save_json()).unwrap()});
        match platform::write(CHECKPOINT, &value.to_string()) {
            Ok(()) => self.notify(self.text("saved")),
            Err(e) => self.notify(e),
        }
    }
    fn restore_checkpoint(&mut self) {
        let result = (|| -> Result<(), String> {
            let source = platform::read(CHECKPOINT).ok_or_else(|| self.text("no_checkpoint"))?;
            let value: Value = serde_json::from_str(&source).map_err(|e| e.to_string())?;
            let original_campaign = if value["campaign"].is_string() {
                value["campaign"].as_str().unwrap().into()
            } else {
                value["campaign"].to_string()
            };
            let campaign = original_campaign_upgrade(&original_campaign)
                .unwrap_or(&original_campaign)
                .to_owned();
            let save = if value["save"].is_string() {
                value["save"].as_str().unwrap().into()
            } else {
                value["save"].to_string()
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
            ("attack", "attack", GOLD, Icon::Sword),
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
            return;
        }
        ui.horizontal(|ui| {
            let (portrait, _) = ui.allocate_exact_size(Vec2::splat(62.0), egui::Sense::hover());
            ui.painter()
                .rect_filled(portrait, 14.0, theme::SURFACE_RAISED);
            ui.painter().rect_stroke(
                portrait,
                14.0,
                Stroke::new(1.0, theme::BORDER),
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
                        .color(TEXT),
                );
                ui.label(
                    RichText::new(format!("{} {}", self.text("floor"), self.visual["floor"]))
                        .size(15.0)
                        .color(MUTED),
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
                .color(GOLD),
            );
        }
    }

    fn keys(&self, ui: &mut egui::Ui, compact: bool) {
        if !compact {
            section(ui, &self.text("keyring"), Icon::Key);
            ui.add_space(14.0);
        }
        let width = (ui.available_width() - 16.0) / 3.0;
        ui.horizontal(|ui| {
            for (key, color) in [("yellow", GOLD), ("blue", theme::BLUE), ("red", theme::RED)] {
                let (rect, response) = ui.allocate_exact_size(
                    Vec2::new(width, if compact { 22.0 } else { 38.0 }),
                    egui::Sense::hover(),
                );
                if !compact {
                    ui.painter().rect_filled(rect, 8.0, theme::SURFACE_RAISED);
                }
                let icon_rect = Rect::from_center_size(
                    egui::pos2(rect.min.x + 20.0, rect.center().y),
                    Vec2::splat(if compact { 22.0 } else { 28.0 }),
                );
                let sprite = self
                    .engine
                    .campaign
                    .tiles
                    .values()
                    .find(|def| def.kind == "key" && def.key.as_deref() == Some(key))
                    .map(|def| serde_json::to_value(&def.sprite).unwrap_or_default())
                    .unwrap_or_else(|| {
                        json!(match key {
                            "yellow" => 29,
                            "blue" => 31,
                            _ => 30,
                        })
                    });
                if !self
                    .assets
                    .tile(ui.painter(), icon_rect, &sprite, Color32::WHITE)
                {
                    theme::icon(ui.painter(), icon_rect, Icon::Key, color);
                }
                ui.painter().text(
                    egui::pos2(rect.min.x + 39.0, rect.center().y),
                    Align2::LEFT_CENTER,
                    number(&self.visual["player"]["keys"][key]),
                    FontId::proportional(19.0),
                    TEXT,
                );
                response.on_hover_text(self.text(key));
            }
        });
    }

    fn inventory(&mut self, ui: &mut egui::Ui) {
        section(ui, &self.text("inventory"), Icon::Compass);
        ui.add_space(14.0);
        let items = self.visual["player"]["inventory"]
            .as_array()
            .into_iter()
            .flatten()
            .filter_map(Value::as_str)
            .map(|item| {
                let definition = self
                    .engine
                    .campaign
                    .tiles
                    .values()
                    .find(|def| def.item.as_deref() == Some(item));
                let usable = definition.is_none_or(|def| def.kind != "equipment")
                    && ![
                        "hero_orb",
                        "wisdom_orb",
                        "monster_book",
                        "cross",
                        "dragon_slayer",
                        "lucky_gold",
                        "sacred_shield",
                    ]
                    .contains(&item);
                json!({
                    "id": item,
                    "name": definition.map(|def| def.name.as_str()).unwrap_or(item),
                    "sprite": definition.map(|def| &def.sprite),
                    "usable": usable,
                    "charges": self.visual["player"]["item_charges"][item],
                })
            })
            .collect::<Vec<_>>();
        if items.is_empty() {
            ui.label(RichText::new(self.text("empty_inventory")).color(MUTED));
        }
        let mut command = None;
        egui::ScrollArea::vertical()
            .id_salt("inventory")
            .max_height(250.0)
            .show(ui, |ui| {
                ui.horizontal_wrapped(|ui| {
                    for item in items {
                        let id = item["id"].as_str().unwrap_or("");
                        let name = entity_name(
                            &self.locale,
                            "items",
                            id,
                            item["name"].as_str().unwrap_or(id),
                        );
                        let usable = item["usable"].as_bool().unwrap_or(false);
                        let enabled = usable
                            && !self.busy()
                            && self.snapshot["pending_interaction"].is_null();
                        let (rect, response) = ui.allocate_exact_size(
                            Vec2::splat(54.0),
                            if enabled {
                                egui::Sense::click()
                            } else {
                                egui::Sense::hover()
                            },
                        );
                        ui.painter().rect_filled(
                            rect,
                            10.0,
                            if response.hovered() {
                                Color32::from_rgb(34, 45, 61)
                            } else {
                                theme::SURFACE_RAISED
                            },
                        );
                        ui.painter().rect_stroke(
                            rect,
                            10.0,
                            Stroke::new(
                                1.0,
                                if response.hovered() {
                                    GOLD
                                } else {
                                    theme::BORDER
                                },
                            ),
                            egui::StrokeKind::Inside,
                        );
                        self.assets.tile(
                            ui.painter(),
                            rect.shrink(10.0),
                            &item["sprite"],
                            Color32::WHITE,
                        );
                        if let Some(n) = item["charges"].as_u64() {
                            let badge = Rect::from_min_size(
                                rect.right_bottom() - Vec2::new(24.0, 18.0),
                                Vec2::new(24.0, 18.0),
                            );
                            ui.painter().rect_filled(badge, 5.0, CARD);
                            ui.painter().text(
                                badge.center(),
                                Align2::CENTER_CENTER,
                                n.to_string(),
                                FontId::proportional(13.0),
                                GOLD,
                            );
                        }
                        self.record(&format!("item:{id}"), &response);
                        if response.on_hover_text(name).clicked() && enabled {
                            if id == "flying_orb" {
                                self.settings = true;
                                self.notify(self.text("flying_hint"));
                            } else {
                                command = Some(json!({"type":"use_item","item":id}));
                            }
                        }
                    }
                });
            });
        if let Some(c) = command {
            self.submit(c);
        }
    }

    fn journal(&self, ui: &mut egui::Ui, max_height: f32) {
        section(ui, &self.text("journal"), Icon::Book);
        ui.add_space(6.0);
        ui.label(
            RichText::new(self.text("journal_subtitle"))
                .size(14.0)
                .color(MUTED),
        );
        ui.add_space(16.0);
        egui::ScrollArea::vertical()
            .id_salt("journal")
            .max_height(max_height)
            .show(ui, |ui| {
                for (i, entry) in self.visual["log"]
                    .as_array()
                    .into_iter()
                    .flatten()
                    .rev()
                    .take(50)
                    .enumerate()
                {
                    ui.horizontal_top(|ui| {
                        let (dot, _) =
                            ui.allocate_exact_size(Vec2::new(14.0, 24.0), egui::Sense::hover());
                        ui.painter().circle_filled(
                            dot.center(),
                            if i == 0 { 3.5 } else { 2.5 },
                            if i == 0 { GOLD } else { theme::BORDER },
                        );
                        ui.add(
                            egui::Label::new(
                                RichText::new(translate_text(
                                    &self.locale,
                                    entry.as_str().unwrap_or(""),
                                ))
                                .size(17.0)
                                .color(if i == 0 {
                                    TEXT
                                } else {
                                    MUTED
                                }),
                            )
                            .wrap(),
                        );
                    });
                    ui.add_space(11.0);
                }
            });
    }

    fn inspection(&self, ui: &mut egui::Ui) {
        section(ui, &self.text("inspect"), Icon::Compass);
        ui.add_space(16.0);
        if let Some(active) = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "battle")
            && let Some(progress) = self.battle_progress(self.now())
        {
            let e = &active.effect;
            let name = translate_text(&self.locale, e["enemy_name"].as_str().unwrap_or(""));
            ui.label(RichText::new(name).size(22.0).strong());
            ui.add_space(6.0);
            ui.label(
                RichText::new(self.text(if progress.hero_turn {
                    "hero_turn"
                } else {
                    "enemy_turn"
                }))
                .size(17.0)
                .color(GOLD),
            );
            ui.add_space(10.0);
            for (label, hp, maximum, color) in [
                (
                    self.text("adventurer"),
                    progress.hero_hp,
                    e["hero_hp"].as_i64().unwrap_or(1),
                    theme::GREEN,
                ),
                (
                    self.text("combat_enemy"),
                    progress.enemy_hp,
                    e["enemy_hp"].as_i64().unwrap_or(1),
                    theme::RED,
                ),
            ] {
                ui.horizontal(|ui| {
                    ui.label(RichText::new(label).size(15.0).color(MUTED));
                    ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                        ui.label(RichText::new(number(&json!(hp))).size(18.0).strong());
                    });
                });
                ui.add(
                    egui::ProgressBar::new(hp as f32 / maximum.max(1) as f32)
                        .fill(color)
                        .desired_height(5.0),
                );
                ui.add_space(10.0);
            }
            ui.separator();
            ui.add_space(6.0);
            for (key, label) in [("hero_hit", "hero_hit"), ("enemy_hit", "enemy_hit")] {
                ui.horizontal(|ui| {
                    ui.label(RichText::new(self.text(label)).size(15.0).color(MUTED));
                    ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                        ui.label(
                            RichText::new(format!("−{}", number(&e[key])))
                                .size(18.0)
                                .color(TEXT),
                        );
                    });
                });
            }
            let strikes =
                e["hero_strikes"].as_i64().unwrap_or(0) + e["enemy_strikes"].as_i64().unwrap_or(0);
            ui.add_space(8.0);
            ui.label(
                RichText::new(format!(
                    "{} {}/{}",
                    self.text("strikes_resolved"),
                    progress.completed,
                    strikes
                ))
                .size(14.0)
                .color(MUTED),
            );
            return;
        }
        let Some((x, y)) = self.selected.filter(|_| !self.busy() || self.travel_only()) else {
            ui.label(
                RichText::new(self.text("inspect_hint"))
                    .size(17.0)
                    .color(MUTED),
            );
            ui.add_space(10.0);
            ui.label(
                RichText::new(self.text("orb_required"))
                    .size(15.0)
                    .color(MUTED),
            );
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
        ui.horizontal(|ui| {
            let (sprite, _) = ui.allocate_exact_size(Vec2::splat(54.0), egui::Sense::hover());
            ui.painter()
                .rect_filled(sprite, 10.0, theme::SURFACE_RAISED);
            self.assets.tile(
                ui.painter(),
                sprite.shrink(7.0),
                &self.visual["tile_defs"][&id]["sprite"],
                Color32::WHITE,
            );
            ui.vertical(|ui| {
                ui.label(RichText::new(name).size(21.0).strong());
                ui.label(RichText::new(format!("{x}, {y}")).size(14.0).color(MUTED));
            });
        });
        let enemy = &info["enemy"];
        if enemy.is_object() {
            ui.add_space(16.0);
            let width = (ui.available_width() - 8.0) / 2.0;
            for row in [
                [
                    ("hp", "health", theme::RED, Icon::Heart),
                    ("attack", "attack", GOLD, Icon::Sword),
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
                ui.add_space(4.0);
            }
            ui.add_space(10.0);
            theme::caption(ui, &self.text("combat_forecast"));
            let survives = enemy["can_win"].as_bool().unwrap_or(false);
            let color = if survives { theme::GREEN } else { theme::RED };
            ui.horizontal(|ui| {
                ui.label(RichText::new(self.text("damage")).size(16.0).color(MUTED));
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    ui.label(
                        RichText::new(number(&enemy["damage"]))
                            .size(26.0)
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
                .size(15.0)
                .color(color),
            );
            if let Some(reason) = enemy["reason"].as_str().filter(|s| !s.is_empty()) {
                ui.label(
                    RichText::new(translate_text(&self.locale, reason))
                        .size(15.0)
                        .color(theme::RED),
                );
            }
        } else {
            ui.add_space(12.0);
            ui.label(translate_text(
                &self.locale,
                info["description"].as_str().unwrap_or(""),
            ));
            if info["details_locked"] == true {
                ui.add_space(8.0);
                ui.label(RichText::new(self.text("orb_required")).color(MUTED));
            }
        }
    }

    fn board(&mut self, ui: &mut egui::Ui, size: f32, now: f64) {
        let width = self.visual["width"].as_u64().unwrap_or(11) as usize;
        let height = self.visual["height"].as_u64().unwrap_or(11) as usize;
        let cell = (size / width.max(height) as f32).floor().max(20.0);
        let board_size = Vec2::new(cell * width as f32, cell * height as f32);
        let (rect, response) = ui.allocate_exact_size(board_size, egui::Sense::click());
        self.bounds.insert("board".into(),json!({"x":rect.min.x,"y":rect.min.y,"w":rect.width(),"h":rect.height(),"cell":cell,"width":width,"height":height}));
        let painter = ui.painter_at(rect);
        painter.rect_filled(rect, 6.0, Color32::from_rgb(36, 41, 46));
        let battle = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "battle");
        let mut hover = None;
        if let Some(pos) = response.hover_pos() {
            let x = ((pos.x - rect.min.x) / cell) as usize;
            let y = ((pos.y - rect.min.y) / cell) as usize;
            if x < width && y < height {
                hover = Some((x, y));
                self.selected = hover;
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
                        "key" | "item" | "equipment" => GOLD,
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
                if hover == Some((x, y)) {
                    painter.rect_stroke(
                        tile_rect.shrink(1.0),
                        1.0,
                        Stroke::new(2.0, GOLD),
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
            self.battle_progress(now).and_then(|progress| {
                let overlay = b.effect["overlay_phase"].as_f64().unwrap_or(1.0 / 3.0) as f32;
                let strike = progress.strike - i64::from(progress.phase < overlay);
                (strike >= 0).then_some(
                    (strike % 2 == 0) != b.effect["enemy_first"].as_bool().unwrap_or(false),
                )
            })
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
            painter.circle_filled(hero_rect.center(), cell * 0.28, GOLD);
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
                "magic" => {
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
                "tile_reveal" => {
                    let x = e["x"].as_u64().unwrap_or(0) as f32;
                    let y = e["y"].as_u64().unwrap_or(0) as f32;
                    let at = Rect::from_min_size(
                        rect.min + Vec2::new(x * cell, y * cell),
                        Vec2::splat(cell),
                    );
                    self.assets.tile(&painter, at, &e["tile"], Color32::WHITE);
                    let amount = (p * 16.0).floor() / 16.0;
                    // Original door-open helper retracts the two sides in 16 steps.
                    for left in [true, false] {
                        let clip = if left {
                            Rect::from_min_max(
                                at.min,
                                egui::pos2(at.center().x - cell * amount * 0.5, at.max.y),
                            )
                        } else {
                            Rect::from_min_max(
                                egui::pos2(at.center().x + cell * amount * 0.5, at.min.y),
                                at.max,
                            )
                        };
                        let shifted = at.translate(Vec2::new(
                            if left {
                                -cell * amount * 0.5
                            } else {
                                cell * amount * 0.5
                            },
                            0.0,
                        ));
                        self.assets.tile(
                            &painter.with_clip_rect(clip),
                            shifted,
                            &e["from_tile"],
                            Color32::WHITE,
                        );
                    }
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
                        GOLD,
                    );
                    if kind == "credits" {
                        painter.text(
                            rect.center() + Vec2::new(0.0, 25.0),
                            Align2::CENTER_CENTER,
                            "Oz & Kenichi / Shigemasa Ozawa",
                            FontId::proportional(18.0),
                            TEXT,
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
        if response.clicked()
            && self.travel_only()
            && self.snapshot["pending_interaction"].is_null()
            && let Some((x, y)) = hover
        {
            self.audio.unlock();
            self.route = self.engine.path_to(x, y).into();
        }
        if self.busy() && !self.travel_only() {
            ui.add_space(10.0);
            let skip = theme::action(ui, self.text("skip"), Icon::ArrowRight, false);
            self.record("skip", &skip);
            if skip.clicked() {
                self.skip_presentation();
            }
        }
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
        theme::frame()
            .inner_margin(if compact { 10 } else { 16 })
            .show(ui, |ui| {
                ui.vertical(|ui| {
                    ui.set_width(width - if compact { 20.0 } else { 32.0 });
                    ui.horizontal(|ui| {
                        let (badge, _) = ui.allocate_exact_size(
                            Vec2::splat(if compact { 32.0 } else { 42.0 }),
                            egui::Sense::hover(),
                        );
                        ui.painter()
                            .rect_filled(badge, 10.0, Color32::from_rgb(43, 40, 35));
                        ui.painter().text(
                            badge.center(),
                            Align2::CENTER_CENTER,
                            format!("{:02}", self.visual["floor"].as_i64().unwrap_or(1)),
                            FontId::proportional(if compact { 19.0 } else { 23.0 }),
                            GOLD,
                        );
                        ui.add_space(4.0);
                        ui.vertical(|ui| {
                            ui.spacing_mut().item_spacing.y = 2.0;
                            if !compact {
                                theme::caption(ui, &self.text("current_floor"));
                            }
                            let title = self
                                .engine
                                .campaign
                                .floors
                                .iter()
                                .find(|f| Some(i64::from(f.id)) == self.visual["floor"].as_i64())
                                .map(|f| f.title.as_str())
                                .unwrap_or("");
                            ui.label(
                                RichText::new(translate_text(&self.locale, title))
                                    .size(if compact { 18.0 } else { 22.0 })
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
                                        .color(MUTED),
                                    );
                                },
                            );
                        }
                    });
                    ui.add_space(if compact { 8.0 } else { 16.0 });
                    let available = ui.available_width();
                    let board_size = if compact {
                        available
                    } else {
                        // Keep the footer visible in the default native window and
                        // on smaller desktop viewports, including high-DPI displays.
                        let viewport_height = self.context.input(|i| i.viewport_rect().height());
                        available.min((viewport_height - ui.cursor().min.y - 140.0).max(240.0))
                    };
                    let board_inset = (available - board_size) * 0.5;
                    let board_start = ui.cursor().min + Vec2::new(board_inset, 0.0);
                    let width_cells = self.visual["width"]
                        .as_u64()
                        .unwrap_or(11)
                        .max(self.visual["height"].as_u64().unwrap_or(11))
                        as f32;
                    let cell = (board_size / width_cells).floor().max(20.0);
                    let extent = Vec2::new(
                        self.visual["width"].as_u64().unwrap_or(11) as f32 * cell,
                        self.visual["height"].as_u64().unwrap_or(11) as f32 * cell,
                    );
                    let surround = Rect::from_min_size(
                        board_start - Vec2::splat(4.0),
                        extent + Vec2::splat(8.0),
                    );
                    ui.painter().rect_stroke(
                        surround,
                        4.0,
                        Stroke::new(1.0, theme::BORDER),
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
                            Stroke::new(2.0, GOLD),
                        );
                        ui.painter().line_segment(
                            [corner, corner + Vec2::new(0.0, dy * 14.0)],
                            Stroke::new(2.0, GOLD),
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
                    ui.add_space(4.0);
                    if !compact {
                        ui.label(
                            RichText::new(self.text("keyboard_hint"))
                                .size(14.0)
                                .color(MUTED),
                        );
                    }
                    ui.add_space(4.0);
                    ui.label(
                        RichText::new(self.text("controls_hint"))
                            .size(if compact { 14.0 } else { 15.0 })
                            .color(MUTED),
                    );
                });
            });
    }

    fn dialogs(&mut self, now: f64) {
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
            .frame(theme::frame().inner_margin(inset))
            .show(&self.context.clone(), |ui| {
                ui.set_width(dialog_width);
                theme::caption(ui, &self.text("dialogue"));
                ui.add_space(8.0);
                if let Some(name) = pending["title"].as_str() {
                    ui.label(
                        RichText::new(translate_text(&self.locale, name))
                            .size(if board.width() < 380.0 { 24.0 } else { 27.0 })
                            .color(TEXT),
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
                            TEXT,
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
                                    .fill(theme::SURFACE_RAISED)
                                    .stroke(Stroke::new(1.0, theme::BORDER))
                                    .corner_radius(9)
                                    .min_size(Vec2::new(ui.available_width(), 44.0)),
                                );
                                let id = offer["id"].as_str().unwrap_or("accept");
                                self.record(&format!("choice:{id}"), &button);
                                if button.clicked() {
                                    action = Some(json!({"type":"choose","choice":id}));
                                }
                            }
                            if needs_close {
                                let close =
                                    theme::action(ui, self.text("close"), Icon::Close, false);
                                self.record("dialogue_close", &close);
                                if close.clicked() {
                                    action = Some(json!({"type":"cancel"}));
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
                action = Some(json!({"type":"choose","choice":"leave"}));
            }
        }
        if skip_scene {
            self.skip_presentation();
        } else if next {
            self.finish_effect();
        }
        if let Some(command) = action {
            self.submit(command);
        }
    }

    fn settings_window(&mut self) {
        if !self.settings {
            return;
        }
        let mut opened = self.settings;
        let viewport = self.context.input(|i| i.viewport_rect());
        let width = (viewport.width() - 96.0).clamp(260.0, 490.0);
        let mut new_game = false;
        let mut import = false;
        let mut export = false;
        let mut language = self.locale.clone();
        let mut changed = false;
        let mut flying = None;
        let response = egui::Modal::new(egui::Id::new("settings_modal"))
            .backdrop_color(Color32::from_black_alpha(150))
            .frame(theme::frame().inner_margin(24))
            .show(&self.context.clone(), |ui| {
                ui.set_width(width);
                ui.set_max_height((viewport.height() - 140.0).min(780.0));
                egui::ScrollArea::vertical()
                    .id_salt("settings_content")
                    .max_height(viewport.height() - 100.0)
                    .show(ui, |ui| {
                        ui.horizontal(|ui| {
                            ui.label(RichText::new(self.text("settings")).size(28.0).strong());
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
                            ui.label(RichText::new(error).color(MUTED));
                        }
                        ui.separator();
                        ui.add_space(12.0);
                        let new = theme::action(ui, self.text("new_game"), Icon::Tower, false);
                        self.record("new_game", &new);
                        if new.clicked() {
                            new_game = true;
                        }
                        let save = theme::action(ui, self.text("export_save"), Icon::Save, false);
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
                        if self
                            .engine
                            .player()
                            .inventory
                            .iter()
                            .any(|i| i == "flying_orb")
                        {
                            ui.separator();
                            ui.label(self.text("flying_hint"));
                            ui.horizontal_wrapped(|ui| {
                                for f in self.snapshot["visited_floors"]
                                    .as_array()
                                    .into_iter()
                                    .flatten()
                                {
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
            self.submit(json!({"type":"new_game"}));
            self.settings = false;
        }
        if export {
            match platform::export("tower.save.json", &self.engine.save_json()) {
                Ok(path) => self.notify(path),
                Err(e) => self.notify(e),
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
            self.submit(json!({"type":"use_item","item":"flying_orb","floor":floor}));
        }
    }

    fn keyboard(&mut self) {
        if self.settings
            || self.editor_open
            || !self.travel_only()
            || !self.snapshot["pending_interaction"].is_null()
        {
            return;
        }
        let direction = self.context.input(|i| {
            [
                (egui::Key::ArrowUp, egui::Key::W, "up"),
                (egui::Key::ArrowDown, egui::Key::S, "down"),
                (egui::Key::ArrowLeft, egui::Key::A, "left"),
                (egui::Key::ArrowRight, egui::Key::D, "right"),
            ]
            .iter()
            .find_map(|(a, b, d)| (i.key_pressed(*a) || i.key_pressed(*b)).then_some(*d))
        });
        if let Some(direction) = direction {
            self.route.clear();
            if self.busy() {
                self.route.push_back(direction.into());
            } else {
                self.submit(json!({"type":"move","direction":direction}));
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
                        &serde_json::to_string_pretty(&value).unwrap(),
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
            let mut mesh = egui::Mesh::default();
            mesh.colored_vertex(bg.left_top(), Color32::from_rgb(18, 25, 39));
            mesh.colored_vertex(bg.right_top(), Color32::from_rgb(14, 20, 32));
            mesh.colored_vertex(bg.right_bottom(), NAVY);
            mesh.colored_vertex(bg.left_bottom(), NAVY);
            mesh.add_triangle(0, 1, 2);
            mesh.add_triangle(0, 2, 3);
            ui.painter().add(mesh);
            egui::Frame::new()
                .inner_margin(if narrow { 12 } else { 28 })
                .show(ui, |ui| {
                    let shell_width = ui.available_width().min(1232.0);
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
                                    if !narrow {
                                        let left = (shell_width * 0.198).clamp(216.0, 244.0);
                                        let right = (shell_width * 0.25).clamp(252.0, 308.0);
                                        let center = shell_width - left - right - 48.0;
                                        ui.horizontal_top(|ui| {
                                            ui.vertical(|ui| {
                                                ui.set_width(left);
                                                theme::card(ui, left, |ui| self.stats(ui, false));
                                                ui.add_space(12.0);
                                                theme::card(ui, left, |ui| self.keys(ui, false));
                                                ui.add_space(12.0);
                                                theme::card(ui, left, |ui| self.inventory(ui));
                                                ui.add_space(14.0);
                                                ui.label(
                                                    RichText::new(self.text("checkpoint_hint"))
                                                        .size(14.0)
                                                        .color(MUTED),
                                                );
                                            });
                                            ui.add_space(16.0);
                                            ui.vertical(|ui| {
                                                ui.set_width(center);
                                                self.board_card(ui, center, now, false);
                                            });
                                            ui.add_space(16.0);
                                            ui.vertical(|ui| {
                                                ui.set_width(right);
                                                theme::card(ui, right, |ui| self.inspection(ui));
                                                ui.add_space(12.0);
                                                theme::card(ui, right, |ui| {
                                                    self.journal(ui, 420.0)
                                                });
                                            });
                                        });
                                    } else {
                                        theme::frame().inner_margin(8).show(ui, |ui| {
                                            ui.vertical(|ui| {
                                                ui.set_width(shell_width - 16.0);
                                                self.stats(ui, true);
                                            });
                                        });
                                        ui.add_space(10.0);
                                        self.board_card(ui, shell_width, now, true);
                                        ui.add_space(12.0);
                                        theme::card(ui, shell_width, |ui| self.inventory(ui));
                                        ui.add_space(12.0);
                                        theme::card(ui, shell_width, |ui| self.inspection(ui));
                                        ui.add_space(12.0);
                                        theme::card(ui, shell_width, |ui| self.journal(ui, 300.0));
                                    }
                                });
                            });
                        });
                });
            self.keyboard();
            self.dialogs(now);
            self.settings_window();
        }
        if let Some((message, until)) = &self.toast
            && now < *until
        {
            egui::Area::new(egui::Id::new("toast"))
                .anchor(Align2::CENTER_BOTTOM, Vec2::new(0.0, -22.0))
                .show(&self.context, |ui| {
                    egui::Frame::new()
                        .fill(CARD)
                        .stroke(Stroke::new(1.0, GOLD))
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
        NAVY.to_normalized_gamma_f32()
    }
}

/// Only the known first-release original campaign is eligible for migration.
/// Custom campaigns and unknown revisions keep the core's strict fingerprint check.
fn original_campaign_upgrade(source: &str) -> Option<&'static str> {
    if let Ok(engine) = Engine::from_json(source) {
        let saved: Value = serde_json::from_str(&engine.save_json()).unwrap_or_default();
        if ["56277325ec91e254", "800993184d7842ca"]
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
    if !["56277325ec91e254", "800993184d7842ca"]
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
    ui.horizontal(|ui| {
        let (rect, _) = ui.allocate_exact_size(Vec2::splat(19.0), egui::Sense::hover());
        theme::icon(ui.painter(), rect, icon, GOLD);
        ui.label(RichText::new(title).size(20.0).strong().color(TEXT));
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
    let (rect, response) = ui.allocate_exact_size(
        Vec2::new(width, if compact { 54.0 } else { 85.0 }),
        egui::Sense::hover(),
    );
    ui.painter().rect_filled(rect, 10.0, theme::SURFACE_RAISED);
    let inset = if compact { 9.0 } else { 12.0 };
    let icon_rect = Rect::from_min_size(rect.min + Vec2::new(inset, 12.0), Vec2::splat(15.0));
    theme::icon(ui.painter(), icon_rect, icon, color);
    ui.painter().text(
        rect.min + Vec2::new(inset + 22.0, 19.5),
        Align2::LEFT_CENTER,
        label,
        FontId::proportional(if compact { 12.0 } else { 14.0 }),
        MUTED,
    );
    let size = if value.chars().count() > 7 {
        21.0
    } else if compact {
        24.0
    } else {
        28.0
    };
    ui.painter().text(
        rect.min + Vec2::new(inset, if compact { 37.0 } else { 54.0 }),
        Align2::LEFT_CENTER,
        value,
        FontId::proportional(size),
        TEXT,
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
        .get_mut(&egui::FontFamily::Proportional)
        .unwrap()
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
