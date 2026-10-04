use crate::{
    assets::Art,
    audio::Audio,
    editor::{CampaignEditor, EditorAction},
    locales::{entity_name, tr, translate_text},
    platform,
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
const NAVY: Color32 = Color32::from_rgb(12, 19, 31);
const CARD: Color32 = Color32::from_rgb(20, 30, 45);
const GOLD: Color32 = Color32::from_rgb(220, 184, 108);
const MUTED: Color32 = Color32::from_rgb(145, 161, 183);
const TEXT: Color32 = Color32::from_rgb(226, 230, 238);

struct Active {
    effect: Value,
    start: f64,
    duration: f64,
}

struct BattleProgress {
    hero_hp: i64,
    enemy_hp: i64,
    hero_turn: bool,
    completed: i64,
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
            .or_else(|| platform::read(CAMPAIGN))
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
        };
        app.audio.enabled = prefs["audio"].as_bool().unwrap_or(true);
        app.audio.music_enabled = prefs["music"].as_bool().unwrap_or(true);
        app.audio.volume = prefs["volume"].as_f64().unwrap_or(0.55) as f32;
        app.request("assets/original-atlas.png");
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
        self.route.clear();
        self.selected = None;
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
        self.route.clear();
        self.persist();
        self.context.request_repaint();
        Ok(())
    }

    pub fn submit(&mut self, command: Value) {
        self.audio.unlock();
        self.visual = self.snapshot.clone();
        if let Some(direction) = command["direction"].as_str() {
            self.facing = direction.into();
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
        json!({"ready":true,"locale":self.locale,"visual_floor":self.visual["floor"],"visual_player":self.visual["player"],"editor_open":self.editor_open,"editor":self.editor.debug_json(),"bounds":self.bounds,"animation":self.active.as_ref().map(|a|a.effect["type"].clone()),"presentation_remaining":self.queue.len(),"path_remaining":self.route.len(),"animations_seen":self.animation_history,"audio":{"unlocked":self.audio.unlocked,"enabled":self.audio.enabled,"effects_played":self.audio.effects_played,"music":self.audio.music_name,"error":self.audio.error},"sprites_loaded":self.assets.atlas.is_some()})
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
                    } else if path.ends_with(".ttf") {
                        install_fonts(&self.context, Some(bytes));
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
                let duration = effect["duration_ms"]
                    .as_f64()
                    .unwrap_or(if kind == "dialogue" { 0.0 } else { 100.0 })
                    / 1000.0
                    / f64::from(self.speed);
                self.active = Some(Active {
                    effect,
                    start: now,
                    duration: duration.max(0.025),
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

    fn battle_progress(&self, now: f64) -> Option<BattleProgress> {
        let active = self
            .active
            .as_ref()
            .filter(|a| a.effect["type"] == "battle")?;
        let effect = &active.effect;
        let rounds = effect["rounds"].as_i64().unwrap_or(0);
        let hero_strikes = effect["hero_strikes"].as_i64().unwrap_or(rounds + 1);
        let enemy_strikes = effect["enemy_strikes"].as_i64().unwrap_or(rounds);
        let total = (hero_strikes + enemy_strikes).max(1);
        let completed = (((now - active.start) / active.duration).clamp(0.0, 1.0) * total as f64)
            .floor() as i64;
        let hero_first = !effect["enemy_first"].as_bool().unwrap_or(false);
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
            hero_hp: (effect["hero_hp"].as_i64().unwrap_or(0)
                - enemy_hits * effect["enemy_hit"].as_i64().unwrap_or(0))
            .max(0),
            enemy_hp: (effect["enemy_hp"].as_i64().unwrap_or(0)
                - hero_hits * effect["hero_hit"].as_i64().unwrap_or(0))
            .max(0),
            hero_turn: (completed % 2 == 0) == hero_first,
            completed,
        })
    }
    fn record(&mut self, id: &str, response: &egui::Response) {
        self.bounds.insert(id.into(),json!({"x":response.rect.min.x,"y":response.rect.min.y,"w":response.rect.width(),"h":response.rect.height()}));
    }

    fn header(&mut self, ui: &mut egui::Ui) {
        let narrow = ui.available_width() < 1060.0;
        ui.horizontal_wrapped(|ui| {
            ui.label(
                RichText::new(translate_text(&self.locale, &self.engine.campaign.title))
                    .font(FontId::new(34.0, egui::FontFamily::Name("serif".into())))
                    .color(GOLD),
            );
            ui.add_space(12.0);
            ui.label(
                RichText::new(format!("{} {}", self.text("floor"), self.visual["floor"]))
                    .size(18.0)
                    .color(MUTED),
            );
            if self.snapshot["cycle"].as_u64().unwrap_or(0) > 1 {
                ui.label(
                    RichText::new(format!(
                        "{} ×{}",
                        self.text("backside"),
                        self.snapshot["backside_multiplier"]
                    ))
                    .color(GOLD),
                );
            }
            if !narrow {
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    self.header_controls(ui)
                });
            }
        });
        if narrow {
            ui.horizontal_wrapped(|ui| self.header_controls(ui));
        }
        ui.add_space(8.0);
        ui.separator();
        ui.add_space(14.0);
    }

    fn header_controls(&mut self, ui: &mut egui::Ui) {
        let settings = ui.button(self.text("settings"));
        self.record("settings", &settings);
        if settings.clicked() {
            self.settings = !self.settings;
        }
        let edit = ui.button(self.text("editor"));
        self.record("editor", &edit);
        if edit.clicked() {
            self.editor_open = true;
        }
        let save = ui.button(self.text("save"));
        self.record("save", &save);
        if save.clicked() {
            self.checkpoint();
        }
        let restore = ui.button(self.text("restore"));
        self.record("restore", &restore);
        if restore.clicked() {
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
            let campaign = if value["campaign"].is_string() {
                value["campaign"].as_str().unwrap().into()
            } else {
                value["campaign"].to_string()
            };
            let save = if value["save"].is_string() {
                value["save"].as_str().unwrap().into()
            } else {
                value["save"].to_string()
            };
            let mut engine = Engine::from_json(&campaign)?;
            engine.load_json(&save)?;
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
        if !compact {
            ui.label(
                RichText::new(self.text("adventurer"))
                    .size(25.0)
                    .color(GOLD),
            );
            ui.add_space(14.0);
        }
        let metrics = [
            ("health", "hp", Color32::from_rgb(232, 113, 123)),
            ("attack", "attack", GOLD),
            ("defense", "defense", Color32::from_rgb(131, 175, 223)),
            ("gold", "gold", GOLD),
        ];
        if compact {
            ui.horizontal_wrapped(|ui| {
                for (label, key, color) in metrics {
                    ui.vertical(|ui| {
                        ui.label(RichText::new(self.text(label)).color(MUTED));
                        ui.label(RichText::new(number(&player[key])).size(25.0).color(color));
                    });
                    ui.add_space(14.0);
                }
            });
        } else {
            for (label, key, color) in metrics {
                ui.horizontal(|ui| {
                    ui.label(RichText::new(self.text(label)).color(MUTED));
                    ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                        ui.label(RichText::new(number(&player[key])).size(29.0).color(color));
                    });
                });
                ui.add_space(8.0);
            }
        }
        ui.add_space(12.0);
        ui.horizontal(|ui| {
            for (key, color) in [
                ("yellow", GOLD),
                ("blue", Color32::from_rgb(112, 168, 232)),
                ("red", Color32::from_rgb(231, 118, 126)),
            ] {
                ui.label(
                    RichText::new(format!("◇ {}", number(&player["keys"][key])))
                        .size(22.0)
                        .color(color),
                )
                .on_hover_text(self.text(key));
                ui.add_space(9.0);
            }
        });
    }

    fn inventory(&mut self, ui: &mut egui::Ui) {
        ui.add_space(15.0);
        ui.separator();
        ui.add_space(14.0);
        ui.label(RichText::new(self.text("inventory")).size(23.0).color(GOLD));
        ui.add_space(10.0);
        let items = self.snapshot["inventory_items"]
            .as_array()
            .cloned()
            .unwrap_or_default();
        if items.is_empty() {
            ui.label(RichText::new(self.text("empty_inventory")).color(MUTED));
        }
        let mut command = None;
        egui::ScrollArea::vertical()
            .id_salt("inventory")
            .max_height(280.0)
            .show(ui, |ui| {
                for item in items {
                    let id = item["id"].as_str().unwrap_or("");
                    let name = entity_name(
                        &self.locale,
                        "items",
                        id,
                        item["name"].as_str().unwrap_or(id),
                    );
                    ui.horizontal(|ui| {
                        let (rect, _) =
                            ui.allocate_exact_size(Vec2::splat(30.0), egui::Sense::hover());
                        self.assets
                            .tile(ui.painter(), rect, &item["sprite"], Color32::WHITE);
                        let mut text = name;
                        if let Some(n) = item["charges"].as_u64() {
                            text = format!("{text} · {n}");
                        }
                        if item["usable"].as_bool().unwrap_or(false) {
                            let button = ui.add_enabled(
                                !self.busy() && self.snapshot["pending_interaction"].is_null(),
                                egui::Button::new(text),
                            );
                            self.record(&format!("item:{id}"), &button);
                            if button.clicked() {
                                if id == "flying_orb" {
                                    self.settings = true;
                                    self.notify(self.text("flying_hint"));
                                } else {
                                    command = Some(json!({"type":"use_item","item":id}));
                                }
                            }
                        } else {
                            ui.label(text);
                        }
                    });
                    ui.add_space(8.0);
                }
            });
        if let Some(c) = command {
            self.submit(c);
        }
    }

    fn journal(&self, ui: &mut egui::Ui, max_height: f32) {
        ui.label(RichText::new(self.text("journal")).size(24.0).color(GOLD));
        ui.add_space(12.0);
        egui::ScrollArea::vertical()
            .id_salt("journal")
            .max_height(max_height)
            .show(ui, |ui| {
                for (i, entry) in self.snapshot["log"]
                    .as_array()
                    .into_iter()
                    .flatten()
                    .rev()
                    .take(50)
                    .enumerate()
                {
                    let text = entry.as_str().unwrap_or("");
                    ui.label(
                        RichText::new(translate_text(&self.locale, text))
                            .size(18.0)
                            .color(if i == 0 { TEXT } else { MUTED }),
                    );
                    ui.add_space(9.0);
                    ui.separator();
                    ui.add_space(9.0);
                }
            });
    }

    fn inspection(&self, ui: &mut egui::Ui) {
        ui.label(RichText::new(self.text("inspect")).size(23.0).color(GOLD));
        ui.add_space(10.0);
        let Some((x, y)) = self.selected else {
            ui.label(RichText::new(self.text("inspect_hint")).color(MUTED));
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
        ui.label(RichText::new(name).size(23.0));
        ui.label(RichText::new(format!("({x}, {y})")).color(MUTED));
        let enemy = &info["enemy"];
        if enemy.is_object() {
            ui.add_space(8.0);
            for (key, label) in [
                ("hp", "health"),
                ("attack", "attack"),
                ("defense", "defense"),
                ("gold", "gold"),
                ("damage", "damage"),
            ] {
                ui.horizontal(|ui| {
                    ui.label(self.text(label));
                    ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                        ui.label(RichText::new(number(&enemy[key])).color(
                            if key == "damage" && !enemy["can_win"].as_bool().unwrap_or(false) {
                                Color32::LIGHT_RED
                            } else {
                                GOLD
                            },
                        ));
                    });
                });
            }
            if let Some(reason) = enemy["reason"].as_str().filter(|s| !s.is_empty()) {
                ui.label(
                    RichText::new(translate_text(&self.locale, reason)).color(Color32::LIGHT_RED),
                );
            }
        } else {
            ui.label(translate_text(
                &self.locale,
                info["description"].as_str().unwrap_or(""),
            ));
            if info["kind"] == "enemy" || info["kind"] == "monster" {
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
                let animated = (97..=132).contains(&tile)
                    || (kind == "enemy" || kind == "monster" || kind == "npc")
                        && ((61..=96).contains(&tile)
                            || (133..=158).contains(&tile)
                            || (19..=28).contains(&tile));
                let frame = if animated && (now * 2.8) as u64 % 2 == 1 {
                    1
                } else {
                    0
                };
                let sprite = if frame > 0
                    && ((97..=105).contains(&tile) || (115..=123).contains(&tile))
                {
                    json!(tile + 9)
                } else if frame > 0 && ((106..=114).contains(&tile) || (124..=132).contains(&tile))
                {
                    json!(tile - 9)
                } else if frame > 0 && tile % 2 == 1 {
                    json!(tile + 1)
                } else {
                    def["sprite"].clone()
                };
                let wiggle = if animated {
                    ((now * 4.0 + (x + y) as f64).sin() * 0.65) as f32
                } else {
                    0.0
                };
                let tint = if battle.is_some_and(|b| {
                    b.effect["x"].as_u64() == Some(x as u64)
                        && b.effect["y"].as_u64() == Some(y as u64)
                        && (((now - b.start) * 12.0) as u64).is_multiple_of(2)
                }) {
                    Color32::from_rgb(255, 150, 150)
                } else {
                    Color32::WHITE
                };
                if !self.assets.tile(
                    &painter,
                    tile_rect.translate(Vec2::new(wiggle, 0.0)),
                    &sprite,
                    tint,
                ) {
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
        if let Some(frames) = self.assets.heroes.get(&self.facing) {
            painter.image(
                frames[if walking && (now * 15.0) as u64 % 2 == 1 {
                    1
                } else {
                    0
                }]
                .id(),
                hero_rect,
                Rect::from_min_max(egui::pos2(0.0, 0.0), egui::pos2(1.0, 1.0)),
                hero_tint,
            );
        } else {
            painter.circle_filled(hero_rect.center(), cell * 0.28, GOLD);
        }
        if let Some(b) = battle {
            let target = rect.min
                + Vec2::new(
                    (b.effect["x"].as_f64().unwrap_or(0.0) as f32 + 0.5) * cell,
                    (b.effect["y"].as_f64().unwrap_or(0.0) as f32 + 0.5) * cell,
                );
            let pulse = ((now - b.start) * 7.0).sin().abs() as f32;
            painter.line_segment(
                [hero_rect.center(), target],
                Stroke::new(
                    2.0 + 3.0 * pulse,
                    Color32::from_rgba_unmultiplied(248, 190, 109, (180.0 * pulse) as u8),
                ),
            );
            painter.circle_stroke(target, cell * (0.25 + 0.15 * pulse), Stroke::new(2.0, GOLD));
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
                .tile(&painter, moving, &a.effect["tile"], Color32::WHITE);
        }
        if let Some(a) = &self.active
            && a.effect["type"] == "cinematic"
        {
            let p = ((now - a.start) / a.duration).clamp(0.0, 1.0) as f32;
            let kind = a.effect["kind"].as_str().unwrap_or("magic");
            match kind {
                "magic" | "capture" | "fairy" => {
                    let color = if kind == "fairy" {
                        Color32::from_rgb(118, 217, 194)
                    } else {
                        Color32::from_rgb(201, 137, 242)
                    };
                    let radius = cell * (0.5 + p * 3.0);
                    let center = hero_rect.center();
                    painter.circle_stroke(
                        center,
                        radius,
                        Stroke::new(2.5, color.gamma_multiply(1.0 - p * 0.7)),
                    );
                    for ray in 0..10 {
                        let angle = (ray as f32 / 10.0 + p) * std::f32::consts::TAU;
                        let at = center + Vec2::angled(angle) * radius;
                        painter.circle_filled(at, cell * 0.08, color);
                    }
                    self.assets.tile(
                        &painter,
                        hero_rect.expand(cell * 0.15),
                        &json!(166 + (p * 16.0) as u64),
                        Color32::from_white_alpha(200),
                    );
                }
                "fade_out" | "fade_in" | "fade" => {
                    let opacity = if kind == "fade_out" {
                        p
                    } else if kind == "fade_in" {
                        1.0 - p
                    } else {
                        (p * std::f32::consts::PI).sin()
                    };
                    painter.rect_filled(
                        rect,
                        0.0,
                        Color32::from_rgba_unmultiplied(5, 10, 20, (opacity * 245.0) as u8),
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
                            "Oz & Kenichi · Shigemasa Ozawa",
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
            let opacity = (1.0 - (p * 2.0 - 1.0).abs()) * 235.0;
            painter.rect_filled(
                rect,
                0.0,
                Color32::from_rgba_unmultiplied(8, 15, 26, opacity as u8),
            );
            painter.text(
                rect.center(),
                Align2::CENTER_CENTER,
                format!("{} {}", self.text("floor"), a.effect["to"]),
                FontId::proportional(32.0),
                GOLD,
            );
        }
        if response.clicked()
            && !self.busy()
            && self.snapshot["pending_interaction"].is_null()
            && let Some((x, y)) = hover
        {
            self.audio.unlock();
            self.route = self.engine.path_to(x, y).into();
        }
        ui.add_space(12.0);
        ui.horizontal_wrapped(|ui| {
            ui.label(
                RichText::new(self.text("movement_hint"))
                    .size(17.0)
                    .color(MUTED),
            );
            if self.busy() {
                let skip = ui.button(self.text("skip"));
                self.record("skip", &skip);
                if skip.clicked() {
                    self.queue.clear();
                    self.active = None;
                    self.visual = self.snapshot.clone();
                    self.route.clear();
                }
            }
        });
        if let Some(a) = &self.active
            && a.effect["type"] == "battle"
        {
            let e = &a.effect;
            let battle = self.battle_progress(now).expect("active battle");
            let ehp = battle.enemy_hp;
            let hhp = battle.hero_hp;
            ui.label(
                RichText::new(format!(
                    "{} · {} {}  |  {} {}",
                    translate_text(&self.locale, e["enemy_name"].as_str().unwrap_or("")),
                    self.text("health"),
                    ehp,
                    self.text("adventurer"),
                    hhp
                ))
                .size(19.0)
                .color(GOLD),
            );
            ui.label(format!(
                "{}: {}    {}: {}    {} {}",
                self.text("hero_hit"),
                e["hero_hit"],
                self.text("enemy_hit"),
                e["enemy_hit"],
                self.text(if battle.hero_turn {
                    "hero_turn"
                } else {
                    "enemy_turn"
                }),
                battle.completed / 2 + 1
            ));
        }
    }

    fn directional_controls(&mut self, ui: &mut egui::Ui) {
        ui.horizontal(|ui| {
            ui.add_space(12.0);
            for (direction, label) in [("left", "←"), ("up", "↑"), ("down", "↓"), ("right", "→")]
            {
                let r = ui.add_enabled(
                    !self.busy() && self.snapshot["pending_interaction"].is_null(),
                    egui::Button::new(RichText::new(label).size(25.0))
                        .min_size(Vec2::new(45.0, 44.0)),
                );
                self.record(direction, &r);
                if r.clicked() {
                    self.route.clear();
                    self.submit(json!({"type":"move","direction":direction}));
                }
            }
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
        egui::Window::new(self.text("dialogue"))
            .id(egui::Id::new("conversation"))
            .anchor(Align2::CENTER_CENTER, Vec2::ZERO)
            .collapsible(false)
            .resizable(false)
            .max_width(560.0)
            .show(&self.context.clone(), |ui| {
                if let Some(name) = pending["title"].as_str() {
                    ui.label(
                        RichText::new(translate_text(&self.locale, name))
                            .size(27.0)
                            .color(GOLD),
                    );
                    ui.add_space(12.0);
                }
                ui.set_min_width(280.0);
                ui.label(RichText::new(visible).size(21.0));
                ui.add_space(18.0);
                if scripted.is_some() {
                    let button = ui.button(self.text("continue"));
                    self.record("dialogue_continue", &button);
                    if button.clicked() {
                        next = true;
                    }
                } else {
                    let offers = pending["offers"]
                        .as_array()
                        .or_else(|| pending["choices"].as_array())
                        .cloned()
                        .unwrap_or_default();
                    for offer in offers {
                        let label = offer["label"]
                            .as_str()
                            .or_else(|| offer["text"].as_str())
                            .or_else(|| offer["name"].as_str())
                            .unwrap_or("Accept");
                        let button = ui.add(
                            egui::Button::new(translate_text(&self.locale, label))
                                .min_size(Vec2::new(240.0, 40.0)),
                        );
                        let id = offer["id"].as_str().unwrap_or("accept");
                        self.record(&format!("choice:{id}"), &button);
                        if button.clicked() {
                            action = Some(json!({"type":"choose","choice":id}));
                        }
                        ui.add_space(6.0);
                    }
                    let close = ui.button(self.text("close"));
                    self.record("dialogue_close", &close);
                    if close.clicked() {
                        action = Some(json!({"type":"cancel"}));
                    }
                }
            });
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
        if next {
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
        let mut new_game = false;
        let mut import = false;
        let mut export = false;
        let mut language = self.locale.clone();
        let mut changed = false;
        let mut flying = None;
        egui::Window::new(self.text("settings"))
            .id(egui::Id::new("settings"))
            .open(&mut opened)
            .default_width(490.0)
            .show(&self.context.clone(), |ui| {
                ui.horizontal(|ui| {
                    ui.label(self.text("language"));
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
                ui.add_space(12.0);
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
                let new = ui.button(self.text("new_game"));
                self.record("new_game", &new);
                if new.clicked() {
                    new_game = true;
                }
                let save = ui.button(self.text("export_save"));
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
        self.settings = opened;
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
            || self.busy()
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
            self.submit(json!({"type":"move","direction":direction}));
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
            let back = ui.button(self.text("back_to_game"));
            self.record("back_to_game", &back);
            if back.clicked() {
                self.editor_open = false;
            }
        } else {
            egui::Frame::new()
                .fill(NAVY)
                .inner_margin(egui::Margin::same(22))
                .show(ui, |ui| {
                    self.header(ui);
                    let wide = ui.available_width() > 1060.0;
                    if wide {
                        let available = ui.available_width();
                        let center = (available - 600.0).clamp(400.0, 620.0);
                        ui.horizontal_top(|ui| {
                            card(ui, 235.0, |ui| {
                                self.stats(ui, false);
                                self.inventory(ui);
                                ui.add_space(20.0);
                                self.directional_controls(ui);
                            });
                            ui.add_space(18.0);
                            ui.vertical(|ui| {
                                ui.set_width(center);
                                ui.label(
                                    RichText::new(translate_text(
                                        &self.locale,
                                        self.engine
                                            .campaign
                                            .floors
                                            .iter()
                                            .find(|f| {
                                                Some(i64::from(f.id))
                                                    == self.visual["floor"].as_i64()
                                            })
                                            .map(|f| f.title.as_str())
                                            .unwrap_or(""),
                                    ))
                                    .size(22.0)
                                    .color(MUTED),
                                );
                                ui.add_space(12.0);
                                self.board(
                                    ui,
                                    center.min(ui.available_height() - 80.0).max(360.0),
                                    now,
                                );
                            });
                            ui.add_space(18.0);
                            card(ui, (available - center - 343.0).max(260.0), |ui| {
                                self.inspection(ui);
                                ui.add_space(20.0);
                                ui.separator();
                                ui.add_space(20.0);
                                self.journal(ui, (ui.available_height() - 20.0).max(220.0));
                            });
                        });
                    } else {
                        egui::ScrollArea::vertical()
                            .id_salt("mobile")
                            .show(ui, |ui| {
                                self.stats(ui, true);
                                ui.add_space(12.0);
                                let size = ui.available_width().min(560.0);
                                self.board(ui, size, now);
                                self.directional_controls(ui);
                                ui.add_space(20.0);
                                ui.collapsing(self.text("inventory"), |ui| self.inventory(ui));
                                ui.add_space(10.0);
                                self.inspection(ui);
                                ui.add_space(25.0);
                                self.journal(ui, 300.0);
                            });
                    }
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
fn restore_journey(engine: &mut Engine, source: &str) -> Result<Option<String>, String> {
    let original_error = match engine.load_json(source) {
        Ok(()) => return Ok(None),
        Err(error) => error,
    };
    let mut saved: Value = serde_json::from_str(source).map_err(|_| original_error.clone())?;
    if saved["campaign_fingerprint"] != "56277325ec91e254" {
        return Err(original_error);
    }
    let bundled = Engine::from_json(include_str!("../../../data/campaign.json"))?;
    let current: Value = serde_json::from_str(&engine.save_json()).expect("core save");
    let expected: Value = serde_json::from_str(&bundled.save_json()).expect("bundled core save");
    if current["campaign_fingerprint"] != expected["campaign_fingerprint"] {
        return Err(original_error);
    }
    saved["campaign_fingerprint"] = expected["campaign_fingerprint"].clone();
    saved["cycle"] = json!(1);
    if saved["status"] == "won" && saved["player"]["floor"] == 50 {
        saved["status"] = json!("playing");
    }
    let migrated = saved.to_string();
    engine.load_json(&migrated)?;
    Ok(Some(migrated))
}

fn card(ui: &mut egui::Ui, width: f32, contents: impl FnOnce(&mut egui::Ui)) {
    egui::Frame::new()
        .fill(CARD)
        .stroke(Stroke::new(1.0, Color32::from_rgb(39, 53, 72)))
        .corner_radius(12)
        .inner_margin(18)
        .show(ui, |ui| {
            ui.vertical(|ui| {
                ui.set_width(width);
                contents(ui);
            });
        });
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
    style.visuals.widgets.inactive.bg_fill = Color32::from_rgb(35, 48, 66);
    style.visuals.widgets.inactive.weak_bg_fill = Color32::from_rgb(35, 48, 66);
    style.visuals.widgets.hovered.bg_fill = Color32::from_rgb(59, 68, 81);
    style.visuals.widgets.hovered.weak_bg_fill = Color32::from_rgb(59, 68, 81);
    style.visuals.selection.bg_fill = Color32::from_rgb(93, 77, 47);
    style.visuals.selection.stroke = Stroke::new(1.0, GOLD);
    style.spacing.item_spacing = Vec2::new(9.0, 9.0);
    style.spacing.button_padding = Vec2::new(13.0, 9.0);
    style
        .text_styles
        .insert(egui::TextStyle::Body, FontId::proportional(18.0));
    style
        .text_styles
        .insert(egui::TextStyle::Button, FontId::proportional(18.0));
    style
        .text_styles
        .insert(egui::TextStyle::Small, FontId::proportional(16.0));
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
        Arc::new(egui::FontData::from_static(include_bytes!(
            "../../../web/fonts/DM-Sans.ttf"
        ))),
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
            Arc::new(egui::FontData::from_owned(bytes)),
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
