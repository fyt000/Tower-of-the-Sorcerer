//! Shared native/WebAssembly campaign editor. Every export uses core validation.
use eframe::egui;
use egui::{Color32, FontId, Pos2, Rect, RichText, Sense, Stroke, TextureId, Ui, Vec2};
use serde_json::{Value, json};
use std::collections::{BTreeMap, VecDeque};

use crate::locales::{entity_name, tr};
use crate::theme::{
    ACCENT as EDITOR_ACCENT, BORDER as EDITOR_BORDER, GOLD as EDITOR_GOLD, MUTED as EDITOR_MUTED,
    SURFACE as EDITOR_SURFACE, SURFACE_RAISED as EDITOR_RAISED, TEXT as EDITOR_TEXT,
};

fn editor_surface() -> egui::Frame {
    crate::theme::frame().inner_margin(18)
}

fn editor_card<R>(ui: &mut Ui, contents: impl FnOnce(&mut Ui) -> R) -> egui::InnerResponse<R> {
    editor_surface().show(ui, |ui| {
        ui.with_layout(egui::Layout::top_down(egui::Align::Min), contents)
            .inner
    })
}

fn editor_eyebrow(ui: &mut Ui, text: impl Into<String>) {
    ui.label(RichText::new(text).size(13.0).strong().color(EDITOR_MUTED));
}

fn editor_button(text: impl Into<String>, primary: bool) -> egui::Button<'static> {
    egui::Button::new(RichText::new(text).size(14.0).strong().color(if primary {
        EDITOR_SURFACE
    } else {
        EDITOR_TEXT
    }))
    .fill(if primary {
        EDITOR_ACCENT
    } else {
        EDITOR_RAISED
    })
    .stroke(Stroke::new(
        1.0,
        if primary {
            EDITOR_ACCENT
        } else {
            EDITOR_BORDER
        },
    ))
    .corner_radius(9)
    .min_size(egui::vec2(0.0, 34.0))
}

#[derive(Debug, Default)]
pub enum EditorAction {
    #[default]
    None,
    Play(Value),
    Export(Value),
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Section {
    Floors,
    Enemies,
    Tiles,
    Rules,
    Npcs,
    Events,
    Advanced,
}

pub struct CampaignEditor {
    campaign: Value,
    exported: Value,
    undo: VecDeque<Value>,
    redo: Vec<Value>,
    section: Section,
    floor: usize,
    brush: u16,
    paint_mode: bool,
    selected_cell: (usize, usize),
    selected_enemy: String,
    selected_tile: String,
    selected_npc: usize,
    selected_event: usize,
    search: String,
    new_id: String,
    advanced: String,
    advanced_error: Option<String>,
    advanced_dirty: bool,
    validation: Option<Result<(), String>>,
    stroke_active: bool,
    discard_pending: bool,
    atlas: Option<(TextureId, Vec2)>,
    bounds: BTreeMap<String, Rect>,
}

impl CampaignEditor {
    pub fn new(campaign: Value) -> Self {
        let brush = campaign["rules"]["empty_tile"].as_u64().unwrap_or(6) as u16;
        let advanced = serde_json::to_string_pretty(&campaign).unwrap_or_default();
        Self {
            exported: campaign.clone(),
            campaign,
            undo: VecDeque::new(),
            redo: Vec::new(),
            section: Section::Floors,
            floor: 0,
            brush,
            paint_mode: true,
            selected_cell: (0, 0),
            selected_enemy: String::new(),
            selected_tile: String::new(),
            selected_npc: 0,
            selected_event: 0,
            search: String::new(),
            new_id: String::new(),
            advanced,
            advanced_error: None,
            advanced_dirty: false,
            validation: None,
            stroke_active: false,
            discard_pending: false,
            atlas: None,
            bounds: BTreeMap::new(),
        }
    }

    pub fn campaign(&self) -> &Value {
        &self.campaign
    }
    pub fn is_dirty(&self) -> bool {
        self.campaign != self.exported || self.advanced_dirty
    }
    pub fn mark_exported(&mut self) {
        self.exported = self.campaign.clone();
    }
    pub fn replace_campaign(&mut self, campaign: Value) {
        let atlas = self.atlas;
        *self = Self::new(campaign);
        self.atlas = atlas;
    }
    pub fn set_atlas(&mut self, texture: TextureId, dimensions: Vec2) {
        self.atlas = Some((texture, dimensions));
    }
    pub fn debug_json(&self) -> Value {
        let bounds: BTreeMap<String,Value> = self.bounds.iter().map(|(key,rect)|
            (key.clone(),json!({"x":rect.min.x,"y":rect.min.y,"width":rect.width(),"height":rect.height(),"cx":rect.center().x,"cy":rect.center().y}))).collect();
        json!({"bounds":bounds,"section":format!("{:?}",self.section),"selected_enemy":self.selected_enemy,
            "selected_tile":self.selected_tile,"floor_index":self.floor,"brush":self.brush,
            "width":self.campaign["width"],"height":self.campaign["height"],"floor_id":self.campaign["floors"][self.floor]["id"],
            "selected_cell":self.selected_cell,"dirty":self.is_dirty(),"valid":self.validation.as_ref().map(Result::is_ok),
            "undo_count":self.undo.len(),"redo_count":self.redo.len()})
    }
    pub fn validate(&self) -> Result<(), String> {
        tos_core::Engine::from_json(&self.campaign.to_string()).map(|_| ())
    }
    fn remember(&mut self, before: Value) {
        if before == self.campaign {
            return;
        }
        self.undo.push_back(before);
        if self.undo.len() > 40 {
            self.undo.pop_front();
        }
        self.redo.clear();
        self.validation = None;
    }
    pub fn undo(&mut self) -> bool {
        let Some(previous) = self.undo.pop_back() else {
            return false;
        };
        self.redo
            .push(std::mem::replace(&mut self.campaign, previous));
        self.sync_draft();
        true
    }
    pub fn redo(&mut self) -> bool {
        let Some(next) = self.redo.pop() else {
            return false;
        };
        self.undo
            .push_back(std::mem::replace(&mut self.campaign, next));
        self.sync_draft();
        true
    }
    fn sync_draft(&mut self) {
        self.advanced = serde_json::to_string_pretty(&self.campaign).unwrap_or_default();
        self.advanced_error = None;
        self.advanced_dirty = false;
        self.validation = None;
        self.stroke_active = false;
    }
    pub fn paint_cell(&mut self, floor: usize, x: usize, y: usize, tile: u16) -> bool {
        let width = self.campaign["width"].as_u64().unwrap_or(0) as usize;
        let height = self.campaign["height"].as_u64().unwrap_or(0) as usize;
        if x >= width || y >= height || self.campaign["tiles"][tile.to_string()].is_null() {
            return false;
        }
        let before = self.campaign.clone();
        let Some(tiles) = self.campaign["floors"][floor]["tiles"].as_array_mut() else {
            return false;
        };
        if let Some(cell) = tiles.get_mut(y * width + x) {
            *cell = json!(tile);
        }
        let changed = before != self.campaign;
        self.remember(before);
        changed
    }
    pub fn resize_dimensions(&mut self, width: usize, height: usize) {
        let before = self.campaign.clone();
        let width = width.clamp(1, 64);
        let height = height.clamp(1, 64);
        resize_campaign(&mut self.campaign, width, height);
        self.selected_cell.0 = self.selected_cell.0.min(width - 1);
        self.selected_cell.1 = self.selected_cell.1.min(height - 1);
        self.remember(before);
    }

    pub fn show(&mut self, ui: &mut Ui, locale: &str) -> EditorAction {
        self.bounds.clear();
        let mut action = EditorAction::None;
        ui.spacing_mut().item_spacing = egui::vec2(10.0, 10.0);
        ui.spacing_mut().button_padding = egui::vec2(12.0, 7.0);
        editor_card(ui, |ui| {
            ui.set_width(ui.available_width());
            ui.horizontal_wrapped(|ui| {
                ui.vertical(|ui| {
                    editor_eyebrow(
                        ui,
                        crate::locales::translate_text(
                            locale,
                            self.campaign["title"].as_str().unwrap_or_default(),
                        ),
                    );
                    ui.label(
                        RichText::new(tr(locale, "editor.title"))
                            .size(27.0)
                            .strong()
                            .color(EDITOR_TEXT),
                    );
                });
                ui.add_space(12.0);
                let dirty = self.is_dirty();
                let status = format!(
                    "●  {}",
                    tr(
                        locale,
                        if dirty {
                            "editor.unsaved"
                        } else {
                            "editor.saved"
                        }
                    )
                );
                let status_color = if dirty {
                    EDITOR_GOLD
                } else {
                    Color32::from_rgb(120, 214, 178)
                };
                let galley =
                    ui.painter()
                        .layout_no_wrap(status, FontId::proportional(13.0), status_color);
                let (rect, _) = ui
                    .allocate_exact_size(egui::vec2(galley.size().x + 24.0, 28.0), Sense::hover());
                ui.painter().rect_filled(
                    rect,
                    14,
                    if dirty {
                        Color32::from_rgb(63, 49, 35)
                    } else {
                        Color32::from_rgb(27, 54, 48)
                    },
                );
                ui.painter()
                    .galley(rect.center() - galley.size() * 0.5, galley, status_color);
            });
            ui.label(
                RichText::new(tr(locale, "editor.intro"))
                    .size(14.0)
                    .color(EDITOR_MUTED),
            );
        });
        ui.add_space(3.0);
        ui.horizontal_wrapped(|ui| {
            let dirty = self.is_dirty();
            let undo = ui.add_enabled(
                !self.undo.is_empty(),
                editor_button(tr(locale, "editor.undo"), false),
            );
            self.bounds.insert("undo".into(), undo.rect);
            if undo.clicked() {
                self.undo();
            }
            let redo = ui.add_enabled(
                !self.redo.is_empty(),
                editor_button(tr(locale, "editor.redo"), false),
            );
            self.bounds.insert("redo".into(), redo.rect);
            if redo.clicked() {
                self.redo();
            }
            ui.add_space(6.0);
            let validate = ui.add(editor_button(tr(locale, "editor.validate"), false));
            self.bounds.insert("validate".into(), validate.rect);
            if validate.clicked() {
                self.validation = Some(self.validate());
            }
            for (key, play) in [("editor.play", true), ("editor.export", false)] {
                let response = ui.add(editor_button(tr(locale, key), !play));
                self.bounds
                    .insert(if play { "play" } else { "export" }.into(), response.rect);
                if response.clicked() {
                    if self.advanced_dirty {
                        self.validation = Some(Err(tr(locale, "editor.apply_draft_first")));
                        continue;
                    }
                    let result = self.validate();
                    if result.is_ok() {
                        action = if play {
                            EditorAction::Play(self.campaign.clone())
                        } else {
                            EditorAction::Export(self.campaign.clone())
                        };
                    }
                    self.validation = Some(result);
                }
            }
            if ui
                .add_enabled(dirty, editor_button(tr(locale, "editor.discard"), false))
                .clicked()
            {
                self.discard_pending = true;
            }
        });
        if self.discard_pending {
            ui.horizontal_wrapped(|ui| {
                ui.label(tr(locale, "editor.discard_confirm"));
                if ui.button(tr(locale, "editor.discard")).clicked() {
                    let before = self.campaign.clone();
                    self.campaign = self.exported.clone();
                    self.remember(before);
                    self.sync_draft();
                    self.discard_pending = false;
                }
                if ui.button(tr(locale, "editor.keep_editing")).clicked() {
                    self.discard_pending = false;
                }
            });
        }
        if let Some(result) = &self.validation {
            match result {
                Ok(()) => {
                    ui.colored_label(Color32::from_rgb(99, 200, 164), tr(locale, "editor.valid"));
                }
                Err(error) => {
                    ui.colored_label(
                        Color32::from_rgb(245, 128, 127),
                        format!("{}: {error}", tr(locale, "editor.invalid")),
                    );
                }
            }
        }
        ui.add_space(4.0);
        ui.horizontal_wrapped(|ui| {
            for (section, key) in [
                (Section::Floors, "editor.floors"),
                (Section::Enemies, "editor.enemies"),
                (Section::Tiles, "editor.tiles"),
                (Section::Rules, "editor.rules"),
                (Section::Npcs, "editor.npcs"),
                (Section::Events, "editor.events"),
                (Section::Advanced, "editor.advanced"),
            ] {
                let selected = self.section == section;
                let response = ui.add(
                    egui::Button::new(
                        RichText::new(tr(locale, key))
                            .size(15.0)
                            .strong()
                            .color(if selected { EDITOR_TEXT } else { EDITOR_MUTED }),
                    )
                    .fill(if selected {
                        EDITOR_RAISED
                    } else {
                        Color32::TRANSPARENT
                    })
                    .stroke(Stroke::new(
                        1.0,
                        if selected {
                            EDITOR_BORDER
                        } else {
                            Color32::TRANSPARENT
                        },
                    ))
                    .corner_radius(10)
                    .min_size(egui::vec2(0.0, 38.0)),
                );
                self.bounds
                    .insert(format!("tab.{section:?}"), response.rect);
                if response.clicked() {
                    self.section = section;
                    if section == Section::Advanced && !self.advanced_dirty {
                        self.sync_draft();
                    }
                }
            }
        });
        ui.add_space(5.0);
        let before = self.campaign.clone();
        let was_stroke = self.stroke_active;
        // eframe's root UI can grow with its contents. Bound the editor body
        // against the actual viewport and reserve the caller's Back button.
        let editor_bottom = ui.max_rect().bottom().min(ui.ctx().content_rect().bottom());
        let body_height = (editor_bottom - ui.next_widget_position().y - 64.0).max(40.0);
        let content = egui::ScrollArea::both()
            .id_salt("campaign_editor_content")
            .max_height(body_height)
            .auto_shrink([false, false])
            .scroll_bar_visibility(egui::scroll_area::ScrollBarVisibility::AlwaysVisible)
            .show(ui, |ui| {
                // Validation notices and toolbar controls appear/disappear
                // before this body. Their automatic IDs must not change a
                // focused text or number field's identity between keystrokes.
                ui.scope_builder(
                    egui::UiBuilder::new().id(egui::Id::new((
                        "campaign-editor-section",
                        format!("{:?}", self.section),
                    ))),
                    |ui| match self.section {
                        Section::Floors => self.floors_ui(ui, locale),
                        Section::Enemies => self.enemies_ui(ui, locale),
                        Section::Tiles => {
                            editor_card(ui, |ui| {
                                ui.set_width(ui.available_width());
                                self.tiles_ui(ui, locale);
                            });
                        }
                        Section::Rules => {
                            editor_card(ui, |ui| {
                                ui.set_width(ui.available_width());
                                self.rules_ui(ui, locale);
                            });
                        }
                        Section::Npcs => {
                            editor_card(ui, |ui| {
                                ui.set_width(ui.available_width());
                                self.npcs_ui(ui, locale);
                            });
                        }
                        Section::Events => {
                            editor_card(ui, |ui| {
                                ui.set_width(ui.available_width());
                                self.events_ui(ui, locale);
                            });
                        }
                        Section::Advanced => {
                            editor_card(ui, |ui| {
                                ui.set_width(ui.available_width());
                                self.advanced_ui(ui, locale);
                            });
                        }
                    },
                );
            });
        self.bounds.insert("content".into(), content.inner_rect);
        if self.section != Section::Advanced {
            remove_untouched_additions(&mut self.campaign, &before);
        }
        if before != self.campaign && !was_stroke {
            self.remember(before);
        }
        if !ui.input(|input| input.pointer.primary_down()) {
            self.stroke_active = false;
        }
        action
    }

    fn floors_ui(&mut self, ui: &mut Ui, locale: &str) {
        let count = self.campaign["floors"].as_array().map_or(0, Vec::len);
        if count == 0 {
            ui.label(tr(locale, "editor.no_floors"));
            return;
        }
        self.floor = self.floor.min(count - 1);
        ui.horizontal_wrapped(|ui| {
            egui::ComboBox::from_id_salt("editor_floor").selected_text(format!("{} {}",tr(locale,"floor"),self.campaign["floors"][self.floor]["id"]))
                .show_ui(ui, |ui| { for index in 0..count { let floor = &self.campaign["floors"][index];
                    ui.selectable_value(&mut self.floor,index,format!("{} · {}",floor["id"],crate::locales::translate_text(locale,floor["title"].as_str().unwrap_or_default()))); } });
            if ui.add(editor_button(tr(locale,"editor.add_floor"), false)).clicked() {
                let id = self.campaign["floors"].as_array().unwrap().iter().filter_map(|floor|floor["id"].as_i64()).max().unwrap_or(0) + 1;
                let width = self.campaign["width"].as_u64().unwrap_or(11) as usize;
                let height = self.campaign["height"].as_u64().unwrap_or(11) as usize;
                let empty = self.campaign["rules"]["empty_tile"].as_u64().unwrap_or(6);
                self.campaign["floors"].as_array_mut().unwrap().push(json!({"id":id,"title":format!("Floor {id}"),"tiles":vec![empty;width*height],"arrival_up":{"x":0,"y":0},"arrival_down":{"x":0,"y":0}}));
                self.floor = count;
            }
            if ui.add(editor_button(tr(locale,"editor.duplicate_floor"), false)).clicked() {
                let mut copy = self.campaign["floors"][self.floor].clone();
                let id = self.campaign["floors"].as_array().unwrap().iter().filter_map(|floor|floor["id"].as_i64()).max().unwrap_or(0) + 1;
                copy["id"] = json!(id); copy["title"] = json!(format!("Floor {id}"));
                self.campaign["floors"].as_array_mut().unwrap().push(copy); self.floor = count;
            }
        });
        let old_id = self.campaign["floors"][self.floor]["id"]
            .as_i64()
            .unwrap_or(0);
        ui.collapsing(tr(locale, "editor.floor_metadata"), |ui| {
            let floor = &mut self.campaign["floors"][self.floor];
            number(ui, locale, "id", &mut floor["id"], 0);
            text(ui, locale, "title", &mut floor["title"], false);
            for key in ["arrival_up", "arrival_down"] {
                ui.horizontal(|ui| {
                    let mut enabled = floor[key].is_object();
                    if ui.checkbox(&mut enabled, tr(locale, key)).changed() {
                        floor[key] = if enabled {
                            json!({"x":0,"y":0})
                        } else {
                            Value::Null
                        };
                    }
                    if enabled {
                        number(ui, locale, "x", &mut floor[key]["x"], 0);
                        number(ui, locale, "y", &mut floor[key]["y"], 0);
                    }
                });
            }
        });
        let new_id = self.campaign["floors"][self.floor]["id"]
            .as_i64()
            .unwrap_or(old_id);
        if old_id != new_id {
            remap_floor_references(&mut self.campaign, old_id, new_id);
        }
        ui.horizontal_wrapped(|ui| {
            for (paint, key) in [(true, "editor.paint"), (false, "editor.select")] {
                let active = self.paint_mode == paint;
                if ui
                    .add(
                        egui::Button::new(
                            RichText::new(tr(locale, key)).size(14.0).color(if active {
                                EDITOR_TEXT
                            } else {
                                EDITOR_MUTED
                            }),
                        )
                        .fill(if active {
                            EDITOR_RAISED
                        } else {
                            Color32::TRANSPARENT
                        })
                        .corner_radius(8)
                        .min_size(egui::vec2(0.0, 32.0)),
                    )
                    .clicked()
                {
                    self.paint_mode = paint;
                }
            }
            ui.label(
                RichText::new(format!("{}: {}", tr(locale, "editor.brush"), self.brush))
                    .size(13.0)
                    .color(EDITOR_GOLD),
            );
            if ui
                .add(editor_button(tr(locale, "editor.fill_floor"), false))
                .clicked()
                && let Some(tiles) = self.campaign["floors"][self.floor]["tiles"].as_array_mut()
            {
                tiles.fill(json!(self.brush));
            }
        });
        let width = self.campaign["width"].as_u64().unwrap_or(11) as usize;
        let height = self.campaign["height"].as_u64().unwrap_or(11) as usize;
        if width == 0 || height == 0 || width > 64 || height > 64 {
            return;
        }
        self.selected_cell.0 = self.selected_cell.0.min(width - 1);
        self.selected_cell.1 = self.selected_cell.1.min(height - 1);
        if ui.available_width() > 820.0 {
            let available = ui.available_width();
            // Remaining layout height is independent of the scroll offset,
            // so the grid does not resize while the user scrolls metadata.
            let board_height = (ui.available_height() - 132.0).clamp(180.0, 600.0);
            let board_width = (board_height + 42.0)
                .clamp(340.0, 660.0)
                .min(available * 0.58);
            let palette_width = (available - board_width - 18.0).max(240.0);
            ui.horizontal_top(|ui| {
                editor_card(ui, |ui| {
                    ui.set_width(board_width - 38.0);
                    editor_eyebrow(
                        ui,
                        format!("{}  ·  {width} × {height}", tr(locale, "editor.floors")),
                    );
                    ui.add_space(4.0);
                    self.floor_canvas_ui(ui, locale, width, height, board_height);
                });
                ui.add_space(6.0);
                editor_card(ui, |ui| {
                    ui.set_width(palette_width - 38.0);
                    self.palette_ui(ui, locale, board_height);
                });
            });
        } else {
            editor_card(ui, |ui| {
                ui.set_width(ui.available_width());
                editor_eyebrow(
                    ui,
                    format!("{}  ·  {width} × {height}", tr(locale, "editor.floors")),
                );
                self.floor_canvas_ui(ui, locale, width, height, 540.0);
            });
            ui.add_space(6.0);
            editor_card(ui, |ui| {
                ui.set_width(ui.available_width());
                self.palette_ui(ui, locale, 250.0);
            });
        }
    }

    fn floor_canvas_ui(
        &mut self,
        ui: &mut Ui,
        locale: &str,
        width: usize,
        height: usize,
        maximum_height: f32,
    ) {
        let size = ((ui.available_width() - 12.0) / width as f32)
            .min(maximum_height / height as f32)
            .clamp(8.0, 52.0);
        let board_size = Vec2::new(width as f32 * size, height as f32 * size);
        let (rect, response) = ui
            .horizontal(|ui| {
                ui.add_space(((ui.available_width() - board_size.x) * 0.5).max(0.0));
                ui.allocate_exact_size(board_size, Sense::click_and_drag())
            })
            .inner;
        let response = response.on_hover_text(tr(locale, "editor.paint_hint"));
        self.bounds.insert("board".into(), rect);
        let tiles = self.campaign["floors"][self.floor]["tiles"]
            .as_array()
            .cloned()
            .unwrap_or_default();
        for y in 0..height {
            for x in 0..width {
                let id = tiles
                    .get(y * width + x)
                    .and_then(Value::as_u64)
                    .unwrap_or(0) as u16;
                let cell = Rect::from_min_size(
                    rect.min + egui::vec2(x as f32 * size, y as f32 * size),
                    Vec2::splat(size),
                );
                draw_tile(
                    ui,
                    cell,
                    id,
                    &self.campaign["tiles"][id.to_string()],
                    self.atlas,
                );
                if self.selected_cell == (x, y) {
                    ui.painter().rect_stroke(
                        cell.shrink(1.0),
                        2.0,
                        Stroke::new(2.5, EDITOR_ACCENT),
                        egui::StrokeKind::Inside,
                    );
                }
                for (key, label, color) in [
                    ("arrival_up", "↑", Color32::from_rgb(80, 225, 195)),
                    ("arrival_down", "↓", Color32::from_rgb(130, 160, 255)),
                ] {
                    let position = &self.campaign["floors"][self.floor][key];
                    if position["x"].as_u64() == Some(x as u64)
                        && position["y"].as_u64() == Some(y as u64)
                    {
                        ui.painter().text(
                            cell.left_top() + egui::vec2(3.0, 2.0),
                            egui::Align2::LEFT_TOP,
                            label,
                            FontId::proportional(size * 0.42),
                            color,
                        );
                    }
                }
            }
        }
        if let Some(pointer) = response
            .interact_pointer_pos()
            .or_else(|| ui.input(|input| input.pointer.hover_pos()))
            && rect.contains(pointer)
            && (response.hovered() || response.dragged())
        {
            let x = ((pointer.x - rect.min.x) / size) as usize;
            let y = ((pointer.y - rect.min.y) / size) as usize;
            if response.secondary_clicked() {
                self.brush = tiles
                    .get(y * width + x)
                    .and_then(Value::as_u64)
                    .unwrap_or(6) as u16;
            }
            if response.clicked()
                || response.dragged()
                || ui.input(|input| input.pointer.primary_down())
            {
                self.selected_cell = (x.min(width - 1), y.min(height - 1));
                if self.paint_mode
                    && (response.clicked() || ui.input(|input| input.pointer.primary_down()))
                    && let Some(tile) = self.campaign["floors"][self.floor]["tiles"]
                        .as_array_mut()
                        .and_then(|tiles| tiles.get_mut(y * width + x))
                    && *tile != json!(self.brush)
                {
                    *tile = json!(self.brush);
                    self.stroke_active = true;
                }
            }
        }
        let (x, y) = self.selected_cell;
        ui.add_space(6.0);
        ui.label(
            RichText::new(format!(
                "{}: ({x}, {y})",
                tr(locale, "editor.selected_cell")
            ))
            .size(13.0)
            .color(EDITOR_MUTED),
        );
        ui.horizontal_wrapped(|ui| {
            if ui.add(editor_button(tr(locale,"editor.npc_here"), false)).clicked() {
                let index=y*width+x;
                let tile=self.campaign["floors"][self.floor]["tiles"][index].as_u64().unwrap_or(0).to_string();
                if !["npc","merchant","fairy","altar"].contains(&self.campaign["tiles"][&tile]["kind"].as_str().unwrap_or(""))
                    && let Some(id)=self.campaign["tiles"].as_object().and_then(|tiles|tiles.iter().find(|(_,definition)|definition["kind"]=="npc").and_then(|(id,_)|id.parse::<u16>().ok())) {
                    self.campaign["floors"][self.floor]["tiles"][index]=json!(id);
                }
                ensure_array(&mut self.campaign["interactions"]);
                let floor_id = self.campaign["floors"][self.floor]["id"].clone();
                let interactions = self.campaign["interactions"].as_array_mut().unwrap();
                self.selected_npc = interactions.len(); interactions.push(json!({"floor":floor_id,"x":x,"y":y,"name":"NPC","text":"","offers":[],"effects":[],"disappear":false}));
                self.section = Section::Npcs;
            }
            if ui.add(editor_button(tr(locale,"editor.event_here"), false)).clicked() {
                ensure_array(&mut self.campaign["events"]);
                let floor_id = self.campaign["floors"][self.floor]["id"].clone();
                let events = self.campaign["events"].as_array_mut().unwrap(); self.selected_event = events.len();
                events.push(json!({"id":format!("custom_event_{}",events.len()),"once":true,"trigger":{"type":"step","floor":floor_id,"x":x,"y":y},"conditions":[],"effects":[]}));
                self.section = Section::Events;
            }
        });
    }

    fn palette_ui(&mut self, ui: &mut Ui, locale: &str, maximum_height: f32) {
        editor_eyebrow(ui, tr(locale, "editor.palette"));
        let search = ui.add(
            egui::TextEdit::singleline(&mut self.search)
                .hint_text(tr(locale, "editor.search"))
                .desired_width(f32::INFINITY)
                .margin(egui::vec2(10.0, 9.0)),
        );
        self.bounds.insert("search".into(), search.rect);
        let mut entries: Vec<(u16, Value)> = self.campaign["tiles"]
            .as_object()
            .into_iter()
            .flat_map(|tiles| tiles.iter())
            .filter_map(|(id, value)| Some((id.parse().ok()?, value.clone())))
            .collect();
        entries.sort_by_key(|(id, _)| *id);
        let query = self.search.to_lowercase();
        egui::ScrollArea::vertical()
            .id_salt("editor_palette")
            .max_height(maximum_height)
            .auto_shrink([false, false])
            .scroll_bar_visibility(egui::scroll_area::ScrollBarVisibility::AlwaysVisible)
            .show(ui, |ui| {
                ui.horizontal_wrapped(|ui| {
                    for (id, definition) in entries {
                        let name = entity_name(
                            locale,
                            "tile",
                            &id.to_string(),
                            definition["name"].as_str().unwrap_or(""),
                        );
                        if !query.is_empty()
                            && !format!("{id} {name} {}", definition["name"].as_str().unwrap_or(""))
                                .to_lowercase()
                                .contains(&query)
                        {
                            continue;
                        }
                        let (rect, response) =
                            ui.allocate_exact_size(Vec2::splat(48.0), Sense::click());
                        self.bounds.insert(format!("palette.{id}"), rect);
                        ui.painter().rect_filled(
                            rect,
                            9,
                            if self.brush == id {
                                EDITOR_ACCENT.gamma_multiply(0.28)
                            } else if response.hovered() {
                                EDITOR_RAISED
                            } else {
                                Color32::from_rgb(19, 24, 35)
                            },
                        );
                        draw_tile(ui, rect.shrink(4.0), id, &definition, self.atlas);
                        if self.brush == id {
                            ui.painter().rect_stroke(
                                rect,
                                9.0,
                                Stroke::new(2.0, EDITOR_ACCENT),
                                egui::StrokeKind::Inside,
                            );
                        }
                        if response.clicked() {
                            self.brush = id;
                        }
                        response.on_hover_text(format!(
                            "{id} · {name}\n{}",
                            definition["kind"].as_str().unwrap_or("")
                        ));
                    }
                });
            });
    }

    fn enemies_ui(&mut self, ui: &mut Ui, locale: &str) {
        editor_card(ui, |ui| {
            ui.set_width(ui.available_width());
            editor_eyebrow(ui, tr(locale, "editor.enemies"));
            ui.horizontal_wrapped(|ui| {
                choose_object(
                    ui,
                    locale,
                    "editor.enemy",
                    "enemies",
                    &self.campaign,
                    &mut self.selected_enemy,
                );
                ui.add_space(8.0);
                ui.add(
                    egui::TextEdit::singleline(&mut self.new_id).hint_text(tr(locale, "editor.new_id")).desired_width(180.0).margin(egui::vec2(10.0, 8.0)),
            );
                if ui.add(editor_button(tr(locale, "editor.add_enemy"), false)).clicked() && !self.new_id.trim().is_empty()
                {
                    let id = self.new_id.trim().to_owned();
                    if self.campaign["enemies"][&id].is_null() {
                        self.campaign["enemies"][&id] =
                            json!({"name":id,"hp":100,"attack":10,"defense":0,"gold":1,"special":""});
                        self.selected_enemy = id;
                        self.new_id.clear();
                    }
                }
            });
        });
        if self.selected_enemy.is_empty() {
            return;
        }
        ui.add_space(6.0);
        let enemy_snapshot = self.campaign["enemies"][&self.selected_enemy].clone();
        let sprite = self.campaign["tiles"].as_object().and_then(|tiles| {
            tiles.iter().find_map(|(id, tile)| {
                (tile["enemy"].as_str() == Some(&self.selected_enemy))
                    .then(|| (id.parse::<u16>().unwrap_or(0), tile.clone()))
            })
        });
        let name = entity_name(
            locale,
            "enemy",
            &self.selected_enemy,
            enemy_snapshot["name"].as_str().unwrap_or(""),
        );
        let available = ui.available_width();
        let atlas = self.atlas;
        let id = self.selected_enemy.clone();
        let enemy = &mut self.campaign["enemies"][&self.selected_enemy];
        if available > 720.0 {
            let summary_width = (available * 0.31).clamp(230.0, 310.0);
            let form_width = available - summary_width - 18.0;
            ui.horizontal_top(|ui| {
                editor_card(ui, |ui| {
                    ui.set_width(summary_width - 38.0);
                    enemy_summary(
                        ui,
                        locale,
                        &id,
                        &name,
                        &enemy_snapshot,
                        sprite.as_ref(),
                        atlas,
                    );
                });
                ui.add_space(6.0);
                editor_card(ui, |ui| {
                    ui.set_width(form_width - 38.0);
                    enemy_fields(ui, locale, enemy, &mut self.bounds);
                });
            });
        } else {
            editor_card(ui, |ui| {
                ui.set_width(ui.available_width());
                enemy_summary(
                    ui,
                    locale,
                    &id,
                    &name,
                    &enemy_snapshot,
                    sprite.as_ref(),
                    atlas,
                );
                ui.add_space(8.0);
                enemy_fields(ui, locale, enemy, &mut self.bounds);
            });
        }
    }

    fn tiles_ui(&mut self, ui: &mut Ui, locale: &str) {
        editor_eyebrow(ui, tr(locale, "editor.tiles"));
        choose_object(
            ui,
            locale,
            "editor.tile",
            "tiles",
            &self.campaign,
            &mut self.selected_tile,
        );
        ui.horizontal(|ui| {
            ui.add(
                egui::TextEdit::singleline(&mut self.new_id)
                    .hint_text(tr(locale, "editor.numeric_id")),
            );
            if ui
                .add(editor_button(tr(locale, "editor.add_tile"), false))
                .clicked()
                && let Ok(id) = self.new_id.trim().parse::<u16>()
            {
                let id = id.to_string();
                if self.campaign["tiles"][&id].is_null() {
                    self.campaign["tiles"][&id] = json!({"name":"New tile","kind":"floor"});
                    self.selected_tile = id;
                    self.new_id.clear();
                }
            }
        });
        if self.selected_tile.is_empty() {
            return;
        }
        let definition = &self.campaign["tiles"][&self.selected_tile];
        ui.add_space(6.0);
        ui.horizontal(|ui| {
            let (rect, _) = ui.allocate_exact_size(egui::vec2(76.0, 76.0), Sense::hover());
            ui.painter()
                .rect_filled(rect, 12, Color32::from_rgb(18, 23, 34));
            draw_tile(
                ui,
                rect.shrink(7.0),
                self.selected_tile.parse().unwrap_or(0),
                definition,
                self.atlas,
            );
            ui.vertical(|ui| {
                ui.label(
                    RichText::new(entity_name(
                        locale,
                        "tile",
                        &self.selected_tile,
                        definition["name"].as_str().unwrap_or_default(),
                    ))
                    .size(23.0)
                    .strong()
                    .color(EDITOR_TEXT),
                );
                ui.label(
                    RichText::new(format!(
                        "{}  ·  {}",
                        self.selected_tile,
                        tr(locale, definition["kind"].as_str().unwrap_or_default())
                    ))
                    .size(13.0)
                    .color(EDITOR_MUTED),
                );
            });
        });
        ui.add_space(10.0);
        let tile = &mut self.campaign["tiles"][&self.selected_tile];
        text(ui, locale, "name", &mut tile["name"], false);
        text(ui, locale, "description", &mut tile["description"], true);
        choice(
            ui,
            locale,
            "kind",
            &mut tile["kind"],
            &[
                "floor",
                "wall",
                "hidden_wall",
                "door",
                "special_door",
                "lava",
                "decoration",
                "enemy",
                "key",
                "potion",
                "gem",
                "gold",
                "stat",
                "equipment",
                "item",
                "stairs_up",
                "stairs_down",
                "npc",
                "merchant",
                "altar",
                "fairy",
                "trigger",
                "win",
            ],
        );
        boolean(ui, locale, "passable", &mut tile["passable"], false);
        let kind = tile["kind"].as_str().unwrap_or("").to_owned();
        if ["enemy", "monster"].contains(&kind.as_str()) {
            text(ui, locale, "enemy", &mut tile["enemy"], false);
        }
        if ["door", "key"].contains(&kind.as_str()) {
            choice(
                ui,
                locale,
                "key",
                &mut tile["key"],
                &["yellow", "blue", "red"],
            );
        }
        if ["potion", "gem", "stat", "equipment", "gold", "key"].contains(&kind.as_str()) {
            choice(
                ui,
                locale,
                "stat",
                &mut tile["stat"],
                &["hp", "attack", "defense", "gold", "yellow", "blue", "red"],
            );
            number(ui, locale, "amount", &mut tile["amount"], 1);
            boolean(ui, locale, "scaled", &mut tile["scaled"], false);
        }
        if ["item", "equipment"].contains(&kind.as_str()) {
            text(ui, locale, "item", &mut tile["item"], false);
        }
        if kind.starts_with("stairs") {
            optional_number(ui, locale, "target_floor", &mut tile["target_floor"]);
        }
        if ["npc", "merchant", "altar", "fairy"].contains(&kind.as_str()) {
            text(ui, locale, "text", &mut tile["text"], true);
            boolean(ui, locale, "disappear", &mut tile["disappear"], false);
            offers_ui(ui, locale, &mut tile["offers"]);
        }
        effects_ui(ui, locale, &mut tile["effects"]);
        ui.collapsing(tr(locale, "editor.sprite"), |ui| {
            let mut enabled = tile["sprite"].is_object();
            if ui.checkbox(&mut enabled, tr(locale, "enabled")).changed() {
                tile["sprite"] = if enabled {
                    json!({"x":0,"y":0,"w":40,"h":40})
                } else {
                    Value::Null
                };
            }
            if enabled {
                for key in ["x", "y", "w", "h"] {
                    number(ui, locale, key, &mut tile["sprite"][key], 0);
                }
            }
        });
        ui.collapsing(tr(locale, "editor.footprint"), |ui| {
            let mut enabled = tile["footprint"].is_object();
            if ui.checkbox(&mut enabled, tr(locale, "enabled")).changed() {
                tile["footprint"] = if enabled {
                    json!({"width":3,"height":3,"offset_x":1,"offset_y":2,"tiles":[]})
                } else {
                    Value::Null
                };
            }
            if enabled {
                for key in ["width", "height", "offset_x", "offset_y"] {
                    number(ui, locale, key, &mut tile["footprint"][key], 0);
                }
                scalar_array(ui, locale, "tiles", &mut tile["footprint"]["tiles"]);
            }
        });
    }

    fn rules_ui(&mut self, ui: &mut Ui, locale: &str) {
        ui.label(
            RichText::new(tr(locale, "editor.campaign"))
                .size(23.0)
                .strong()
                .color(EDITOR_TEXT),
        );
        text(ui, locale, "id", &mut self.campaign["id"], false);
        text(ui, locale, "title", &mut self.campaign["title"], false);
        let mut width = self.campaign["width"].as_u64().unwrap_or(11) as usize;
        let mut height = self.campaign["height"].as_u64().unwrap_or(11) as usize;
        let old = (width, height);
        ui.horizontal(|ui| {
            ui.label(tr(locale, "width"));
            ui.add(egui::DragValue::new(&mut width).range(1..=64));
            ui.label(tr(locale, "height"));
            ui.add(egui::DragValue::new(&mut height).range(1..=64));
        });
        if old != (width, height) {
            resize_campaign(&mut self.campaign, width, height);
        }
        ui.label(
            RichText::new(tr(locale, "editor.resize_hint"))
                .size(13.0)
                .color(EDITOR_MUTED),
        );
        ui.collapsing(tr(locale, "editor.start"), |ui| {
            for field in ["floor", "x", "y", "hp", "attack", "defense", "gold"] {
                number(ui, locale, field, &mut self.campaign["start"][field], 0);
            }
            for color in ["yellow", "blue", "red"] {
                number(
                    ui,
                    locale,
                    color,
                    &mut self.campaign["start"]["keys"][color],
                    0,
                );
            }
            scalar_array(
                ui,
                locale,
                "inventory",
                &mut self.campaign["start"]["inventory"],
            );
        });
        ui.add_space(12.0);
        ui.label(
            RichText::new(tr(locale, "editor.rules"))
                .size(23.0)
                .strong()
                .color(EDITOR_TEXT),
        );
        for key in [
            "empty_tile",
            "altar_base_cost",
            "altar_hp_gain",
            "altar_attack_gain",
            "altar_defense_gain",
            "cross_multiplier",
            "dragon_slayer_multiplier",
            "magician_a_damage",
            "magician_b_damage",
        ] {
            number(
                ui,
                locale,
                key,
                &mut self.campaign["rules"][key],
                match key {
                    "empty_tile" => 6,
                    "cross_multiplier" | "dragon_slayer_multiplier" => 2,
                    "altar_base_cost" => 10,
                    "altar_hp_gain" | "magician_b_damage" => 100,
                    "magician_a_damage" => 200,
                    "altar_attack_gain" => 2,
                    "altar_defense_gain" => 4,
                    _ => 0,
                },
            );
        }
        for key in [
            "hero_attacks_first",
            "base_attack_guard",
            "flying_requires_stairs",
            "save_requires_hero_orb",
        ] {
            boolean(ui, locale, key, &mut self.campaign["rules"][key], true);
        }
        ui.collapsing(tr(locale, "area_scaling"), |ui| {
            ensure_array(&mut self.campaign["rules"]["area_scaling"]);
            let list = self.campaign["rules"]["area_scaling"]
                .as_array_mut()
                .unwrap();
            let mut remove = None;
            for (index, row) in list.iter_mut().enumerate() {
                ui.push_id(index, |ui| {
                    ui.horizontal(|ui| {
                        number(ui, locale, "max_floor", &mut row["max_floor"], 10);
                        number(ui, locale, "multiplier", &mut row["multiplier"], 1);
                        if ui.button("×").clicked() {
                            remove = Some(index);
                        }
                    });
                });
            }
            if let Some(index) = remove {
                list.remove(index);
            }
            if ui.button(tr(locale, "add")).clicked() {
                list.push(json!({"max_floor":50,"multiplier":5}));
            }
        });
        ui.collapsing(tr(locale, "stair_links"), |ui| {
            ensure_object(&mut self.campaign["rules"]["stair_links"]);
            let links = self.campaign["rules"]["stair_links"]
                .as_object_mut()
                .unwrap();
            let keys: Vec<String> = links.keys().cloned().collect();
            let mut remove = None;
            for key in keys {
                ui.push_id(&key, |ui| {
                    ui.horizontal(|ui| {
                        ui.label(&key);
                        number(ui, locale, "target_floor", links.get_mut(&key).unwrap(), 0);
                        if ui.button("×").clicked() {
                            remove = Some(key.clone());
                        }
                    });
                });
            }
            if let Some(key) = remove {
                links.remove(&key);
            }
            ui.horizontal(|ui| {
                ui.add(egui::TextEdit::singleline(&mut self.new_id).hint_text("43:up"));
                if ui.button(tr(locale, "add")).clicked() && self.new_id.contains(':') {
                    links.insert(self.new_id.trim().to_owned(), json!(0));
                    self.new_id.clear();
                }
            });
        });
    }

    fn npcs_ui(&mut self, ui: &mut Ui, locale: &str) {
        editor_eyebrow(ui, tr(locale, "editor.npcs"));
        ensure_array(&mut self.campaign["interactions"]);
        let list = self.campaign["interactions"].as_array_mut().unwrap();
        select_record(ui, locale, "editor.npc", list, &mut self.selected_npc);
        if ui
            .add(editor_button(tr(locale, "editor.add_npc"), false))
            .clicked()
        {
            self.selected_npc = list.len();
            list.push(json!({"floor":1,"x":0,"y":0,"name":"NPC","text":"","offers":[],"effects":[],"disappear":false}));
        }
        if list.is_empty() {
            return;
        }
        self.selected_npc = self.selected_npc.min(list.len() - 1);
        let npc = &mut list[self.selected_npc];
        for field in ["floor", "x", "y"] {
            number(ui, locale, field, &mut npc[field], 0);
        }
        text(ui, locale, "name", &mut npc["name"], false);
        text(ui, locale, "text", &mut npc["text"], true);
        boolean(ui, locale, "disappear", &mut npc["disappear"], false);
        offers_ui(ui, locale, &mut npc["offers"]);
        effects_ui(ui, locale, &mut npc["effects"]);
        ui.collapsing(tr(locale, "after_text"), |ui| {
            text(ui, locale, "flag", &mut npc["after_text"]["flag"], false);
            text(ui, locale, "text", &mut npc["after_text"]["text"], true);
        });
        if ui.button(tr(locale, "editor.remove_record")).clicked() {
            list.remove(self.selected_npc);
        }
    }

    fn events_ui(&mut self, ui: &mut Ui, locale: &str) {
        editor_eyebrow(ui, tr(locale, "editor.events"));
        ensure_array(&mut self.campaign["events"]);
        let list = self.campaign["events"].as_array_mut().unwrap();
        select_record(ui, locale, "editor.event", list, &mut self.selected_event);
        if ui
            .add(editor_button(tr(locale, "editor.add_event"), false))
            .clicked()
        {
            self.selected_event = list.len();
            list.push(json!({"id":format!("custom_event_{}",list.len()),"once":true,"trigger":{"type":"step","floor":1},"conditions":[],"effects":[]}));
        }
        if list.is_empty() {
            return;
        }
        self.selected_event = self.selected_event.min(list.len() - 1);
        let event = &mut list[self.selected_event];
        text(ui, locale, "id", &mut event["id"], false);
        boolean(ui, locale, "once", &mut event["once"], true);
        editor_surface()
            .fill(EDITOR_RAISED)
            .inner_margin(14)
            .corner_radius(12)
            .show(ui, |ui| {
                editor_eyebrow(ui, tr(locale, "trigger"));
                choice(
                    ui,
                    locale,
                    "type",
                    &mut event["trigger"]["type"],
                    &[
                        "step",
                        "bump",
                        "door_opened",
                        "enter_floor",
                        "enemy_defeated",
                        "interact",
                    ],
                );
                for key in ["floor", "x", "y", "tile"] {
                    optional_number(ui, locale, key, &mut event["trigger"][key]);
                }
            });
        conditions_ui(ui, locale, &mut event["conditions"], 0);
        effects_ui(ui, locale, &mut event["effects"]);
        text(ui, locale, "source", &mut event["source"], false);
        if ui.button(tr(locale, "editor.remove_record")).clicked() {
            list.remove(self.selected_event);
        }
    }

    fn advanced_ui(&mut self, ui: &mut Ui, locale: &str) {
        editor_eyebrow(ui, tr(locale, "editor.advanced"));
        ui.label(
            RichText::new(tr(locale, "editor.advanced_hint"))
                .size(14.0)
                .color(EDITOR_MUTED),
        );
        let response = ui.add(
            egui::TextEdit::multiline(&mut self.advanced)
                .code_editor()
                .desired_rows(28)
                .desired_width(f32::INFINITY)
                .margin(egui::vec2(14.0, 12.0)),
        );
        if response.changed() {
            self.advanced_dirty = true;
        }
        if ui
            .add(editor_button(tr(locale, "editor.apply_json"), true))
            .clicked()
        {
            match serde_json::from_str::<Value>(&self.advanced) {
                Ok(value) => match tos_core::Engine::from_json(&value.to_string()) {
                    Ok(_) => {
                        self.campaign = value;
                        self.advanced_error = None;
                        self.advanced_dirty = false;
                        self.validation = Some(Ok(()));
                    }
                    Err(error) => self.advanced_error = Some(error),
                },
                Err(error) => self.advanced_error = Some(error.to_string()),
            }
        }
        if let Some(error) = &self.advanced_error {
            ui.colored_label(Color32::from_rgb(245, 128, 127), error);
        }
    }
}

fn enemy_summary(
    ui: &mut Ui,
    locale: &str,
    id: &str,
    name: &str,
    enemy: &Value,
    sprite: Option<&(u16, Value)>,
    atlas: Option<(TextureId, Vec2)>,
) {
    editor_eyebrow(ui, tr(locale, "editor.enemy"));
    ui.add_space(10.0);
    if let Some((tile_id, tile)) = sprite {
        let (rect, _) = ui.allocate_exact_size(egui::vec2(112.0, 112.0), Sense::hover());
        ui.painter()
            .rect_filled(rect, 16, Color32::from_rgb(18, 23, 34));
        draw_tile(ui, rect.shrink(12.0), *tile_id, tile, atlas);
        ui.add_space(8.0);
    }
    ui.label(RichText::new(name).size(23.0).strong().color(EDITOR_TEXT));
    ui.label(RichText::new(id).monospace().size(12.0).color(EDITOR_MUTED));
    ui.add_space(14.0);
    let stat_width = ((ui.available_width() - 18.0) * 0.5).max(72.0);
    egui::Grid::new("enemy-summary-stats")
        .num_columns(2)
        .spacing(egui::vec2(18.0, 16.0))
        .show(ui, |ui| {
            for (index, field) in ["hp", "attack", "defense", "gold"].iter().enumerate() {
                ui.vertical(|ui| {
                    ui.set_width(stat_width);
                    editor_eyebrow(ui, tr(locale, field));
                    ui.label(
                        RichText::new(enemy[*field].as_i64().unwrap_or_default().to_string())
                            .size(22.0)
                            .strong()
                            .color(if *field == "gold" {
                                EDITOR_GOLD
                            } else {
                                EDITOR_TEXT
                            }),
                    );
                });
                if index % 2 == 1 {
                    ui.end_row();
                }
            }
        });
    if let Some(special) = enemy["special"].as_str().filter(|value| !value.is_empty()) {
        ui.add_space(10.0);
        ui.label(
            RichText::new(tr(locale, special))
                .size(13.0)
                .color(EDITOR_ACCENT),
        );
    }
}

fn enemy_fields(ui: &mut Ui, locale: &str, enemy: &mut Value, bounds: &mut BTreeMap<String, Rect>) {
    editor_eyebrow(ui, tr(locale, "editor.enemies"));
    ui.add_space(5.0);
    text(ui, locale, "name", &mut enemy["name"], false);
    ui.add_space(8.0);
    for field in ["hp", "attack", "defense", "gold"] {
        let rect = number_control(ui, locale, field, &mut enemy[field], 0);
        bounds.insert(format!("enemy.{field}"), rect);
    }
    ui.add_space(9.0);
    choice(
        ui,
        locale,
        "special",
        &mut enemy["special"],
        &[
            "",
            "undead",
            "dragon",
            "magician_a",
            "magician_b",
            "sorcerer",
            "boss",
        ],
    );
}

fn ensure_array(value: &mut Value) {
    if !value.is_array() {
        *value = json!([]);
    }
}
fn ensure_object(value: &mut Value) {
    if !value.is_object() {
        *value = json!({});
    }
}
/// serde_json's mutable indexing materializes absent fields as null. Showing
/// an optional form must not turn an otherwise valid campaign into null-valued
/// strings/booleans, or mark it dirty merely because a panel was opened.
fn remove_untouched_additions(value: &mut Value, before: &Value) {
    match value {
        Value::Object(object) => {
            let keys: Vec<String> = object.keys().cloned().collect();
            for key in keys {
                let previous = before.get(&key).unwrap_or(&Value::Null);
                if let Some(child) = object.get_mut(&key) {
                    remove_untouched_additions(child, previous);
                }
                let empty = object.get(&key).is_some_and(|child| {
                    child.is_null()
                        || child.as_object().is_some_and(|object| object.is_empty())
                        || child.as_array().is_some_and(|array| array.is_empty())
                });
                if before.get(&key).is_none() && empty {
                    object.remove(&key);
                }
            }
        }
        Value::Array(array) => {
            for (index, child) in array.iter_mut().enumerate() {
                remove_untouched_additions(child, before.get(index).unwrap_or(&Value::Null));
            }
        }
        _ => {}
    }
}
fn text(ui: &mut Ui, locale: &str, key: &str, value: &mut Value, multiline: bool) {
    let mut content = value.as_str().unwrap_or("").to_owned();
    editor_eyebrow(ui, tr(locale, key));
    let desired_width = ui.available_width().clamp(120.0, 620.0);
    let response = if multiline {
        ui.add(
            egui::TextEdit::multiline(&mut content)
                .desired_rows(3)
                .desired_width(desired_width)
                .margin(egui::vec2(10.0, 9.0)),
        )
    } else {
        ui.add(
            egui::TextEdit::singleline(&mut content)
                .desired_width(desired_width)
                .margin(egui::vec2(10.0, 9.0)),
        )
    };
    if response.changed() {
        *value = json!(content);
    }
}
fn number(ui: &mut Ui, locale: &str, key: &str, value: &mut Value, default: i64) {
    number_control(ui, locale, key, value, default);
}
fn number_control(ui: &mut Ui, locale: &str, key: &str, value: &mut Value, default: i64) -> Rect {
    let mut content = value.as_i64().unwrap_or(default);
    ui.horizontal(|ui| {
        ui.add_sized(
            egui::vec2(138.0_f32.min(ui.available_width() * 0.52), 32.0),
            egui::Label::new(
                RichText::new(tr(locale, key))
                    .size(14.0)
                    .color(EDITOR_MUTED),
            ),
        );
        let response = ui.add_sized(
            egui::vec2(112.0, 34.0),
            egui::DragValue::new(&mut content).speed(1),
        );
        if response.changed() {
            *value = json!(content);
        }
        response.rect
    })
    .inner
}
fn optional_number(ui: &mut Ui, locale: &str, key: &str, value: &mut Value) {
    let mut enabled = value.is_number();
    ui.horizontal(|ui| {
        if ui.checkbox(&mut enabled, tr(locale, key)).changed() {
            *value = if enabled { json!(0) } else { Value::Null };
        }
        if enabled {
            number(ui, locale, "value", value, 0);
        }
    });
}
fn boolean(ui: &mut Ui, locale: &str, key: &str, value: &mut Value, default: bool) {
    let mut enabled = value.as_bool().unwrap_or(default);
    if ui.checkbox(&mut enabled, tr(locale, key)).changed() {
        *value = json!(enabled);
    }
}
fn choice(ui: &mut Ui, locale: &str, key: &str, value: &mut Value, choices: &[&str]) {
    let mut selected = value
        .as_str()
        .unwrap_or(choices.first().copied().unwrap_or(""))
        .to_owned();
    let original = selected.clone();
    egui::ComboBox::from_label(tr(locale, key))
        .width(220.0_f32.min(ui.available_width() * 0.68))
        .selected_text(tr(locale, &selected))
        .show_ui(ui, |ui| {
            for option in choices {
                ui.selectable_value(&mut selected, (*option).to_owned(), tr(locale, option));
            }
        });
    if original != selected {
        *value = json!(selected);
    }
}
fn scalar_array(ui: &mut Ui, locale: &str, key: &str, value: &mut Value) {
    let mut content = value
        .as_array()
        .map(|list| {
            list.iter()
                .map(|entry| {
                    entry
                        .as_str()
                        .map(str::to_owned)
                        .unwrap_or_else(|| entry.to_string())
                })
                .collect::<Vec<_>>()
                .join(", ")
        })
        .unwrap_or_default();
    ui.label(format!(
        "{} · {}",
        tr(locale, key),
        tr(locale, "editor.comma_separated")
    ));
    if ui.text_edit_singleline(&mut content).changed() {
        *value = Value::Array(
            content
                .replace('，', ",")
                .split(',')
                .map(str::trim)
                .filter(|entry| !entry.is_empty())
                .map(|entry| {
                    if key == "inventory" {
                        return json!(entry);
                    }
                    entry
                        .parse::<i64>()
                        .map(|n| json!(n))
                        .unwrap_or_else(|_| json!(entry))
                })
                .collect(),
        );
    }
}

fn initialize_record(record: &mut Value, effect: bool) {
    let kind = record["type"].as_str().unwrap_or("");
    let defaults = match kind {
        "flag" => json!({"flag":"custom_flag","value":true}),
        "message" => json!({"text":""}),
        "tile" | "set_tile" => json!({"floor":0,"x":0,"y":0,"tile":6}),
        "teleport" | "battle_at" => json!({"floor":0,"x":0,"y":0,"first_strike":false}),
        "stat_at_least" | "stat_at_most" | "add_stat" | "set_stat" => {
            json!({"stat":"hp","amount":1})
        }
        "multiply_stat" => json!({"stat":"hp","numerator":1,"denominator":1}),
        "has_item" | "give_item" | "remove_item" => json!({"item":"hero_orb"}),
        "set_charges" => json!({"item":"warp_staff","charges":3}),
        "set_visited" => json!({"floors":[1]}),
        "set_enemy" => json!({"enemy":"green_slime"}),
        "wait" => json!({"ms":120}),
        "sound" => json!({"cue":"open"}),
        "cinematic" => json!({"kind":"magic","duration_ms":650}),
        "move_tile" => json!({"floor":0,"from_x":0,"from_y":0,"x":1,"y":0,"duration_ms":120}),
        "no_enemies" => json!({"floor":0}),
        "cycle_at_least" | "cycle_at_most" => json!({"amount":1}),
        "any" if !effect => json!({"conditions":[]}),
        _ => json!({}),
    };
    if let (Some(object), Some(defaults)) = (record.as_object_mut(), defaults.as_object()) {
        for (key, value) in defaults {
            if object.get(key).is_none_or(Value::is_null) {
                object.insert(key.clone(), value.clone());
            }
        }
    }
}
fn choose_object(
    ui: &mut Ui,
    locale: &str,
    label: &str,
    category: &str,
    campaign: &Value,
    selected: &mut String,
) {
    let entries = campaign[category].as_object();
    if selected.is_empty() || campaign[category][selected.as_str()].is_null() {
        *selected = entries
            .and_then(|entries| entries.keys().next())
            .cloned()
            .unwrap_or_default();
    }
    egui::ComboBox::from_label(tr(locale, label))
        .width(250.0_f32.min(ui.available_width() * 0.76))
        .selected_text(format!(
            "{} · {}",
            entity_name(
                locale,
                if category == "enemies" {
                    "enemy"
                } else {
                    "tile"
                },
                selected,
                campaign[category][selected.as_str()]["name"]
                    .as_str()
                    .unwrap_or_default()
            ),
            selected
        ))
        .show_ui(ui, |ui| {
            if let Some(entries) = entries {
                for (id, value) in entries {
                    ui.selectable_value(
                        selected,
                        id.clone(),
                        format!(
                            "{id} · {}",
                            entity_name(
                                locale,
                                if category == "enemies" {
                                    "enemy"
                                } else {
                                    "tile"
                                },
                                id,
                                value["name"].as_str().unwrap_or("")
                            )
                        ),
                    );
                }
            }
        });
}
fn select_record(ui: &mut Ui, locale: &str, label: &str, list: &[Value], selected: &mut usize) {
    egui::ComboBox::from_label(tr(locale, label))
        .width(300.0_f32.min(ui.available_width() * 0.76))
        .selected_text(format!("{} / {}", selected.saturating_add(1), list.len()))
        .show_ui(ui, |ui| {
            for (index, record) in list.iter().enumerate() {
                let name = record["id"]
                    .as_str()
                    .or_else(|| record["name"].as_str())
                    .unwrap_or("");
                ui.selectable_value(
                    selected,
                    index,
                    format!(
                        "{} · {name} · F{} ({},{})",
                        index + 1,
                        record["floor"],
                        record["x"],
                        record["y"]
                    ),
                );
            }
        });
}

fn conditions_ui(ui: &mut Ui, locale: &str, value: &mut Value, depth: usize) {
    ensure_array(value);
    let list = value.as_array_mut().unwrap();
    let mut remove = None;
    ui.collapsing(
        format!("{} ({})", tr(locale, "conditions"), list.len()),
        |ui| {
            for (index, condition) in list.iter_mut().enumerate() {
                ui.push_id(("condition", depth, index), |ui| {
                    editor_surface()
                        .fill(EDITOR_RAISED)
                        .inner_margin(14)
                        .corner_radius(12)
                        .show(ui, |ui| {
                            let previous_type = condition["type"].as_str().unwrap_or("").to_owned();
                            choice(
                                ui,
                                locale,
                                "type",
                                &mut condition["type"],
                                &[
                                    "flag",
                                    "has_item",
                                    "tile",
                                    "no_enemies",
                                    "stat_at_least",
                                    "stat_at_most",
                                    "cycle_at_least",
                                    "cycle_at_most",
                                    "any",
                                ],
                            );
                            if condition["type"].as_str().unwrap_or("") != previous_type {
                                initialize_record(condition, false);
                            }
                            match condition["type"].as_str().unwrap_or("flag") {
                                "flag" => {
                                    text(ui, locale, "flag", &mut condition["flag"], false);
                                    boolean(ui, locale, "value", &mut condition["value"], true);
                                }
                                "has_item" => {
                                    text(ui, locale, "item", &mut condition["item"], false)
                                }
                                "tile" => {
                                    for key in ["floor", "x", "y", "tile"] {
                                        number(ui, locale, key, &mut condition[key], 0);
                                    }
                                }
                                "no_enemies" => {
                                    number(ui, locale, "floor", &mut condition["floor"], 1)
                                }
                                "stat_at_least" | "stat_at_most" => {
                                    choice(
                                        ui,
                                        locale,
                                        "stat",
                                        &mut condition["stat"],
                                        &[
                                            "hp", "attack", "defense", "gold", "yellow", "blue",
                                            "red",
                                        ],
                                    );
                                    number(ui, locale, "amount", &mut condition["amount"], 1);
                                }
                                "cycle_at_least" | "cycle_at_most" => {
                                    let key = if condition["cycle"].is_number() {
                                        "cycle"
                                    } else {
                                        "amount"
                                    };
                                    number(ui, locale, "cycle", &mut condition[key], 1);
                                }
                                "any" if depth < 4 => conditions_ui(
                                    ui,
                                    locale,
                                    &mut condition["conditions"],
                                    depth + 1,
                                ),
                                _ => {}
                            }
                            if ui.button(tr(locale, "remove")).clicked() {
                                remove = Some(index);
                            }
                        });
                });
            }
            if let Some(index) = remove {
                list.remove(index);
            }
            if ui.button(tr(locale, "editor.add_condition")).clicked() {
                list.push(json!({"type":"flag","flag":"custom_flag","value":true}));
            }
        },
    );
}

fn effects_ui(ui: &mut Ui, locale: &str, value: &mut Value) {
    ensure_array(value);
    let list = value.as_array_mut().unwrap();
    let mut remove = None;
    let mut reorder = None;
    ui.collapsing(
        format!("{} ({})", tr(locale, "effects"), list.len()),
        |ui| {
            let count = list.len();
            for (index, effect) in list.iter_mut().enumerate() {
                ui.push_id(("effect", index), |ui| {
                    editor_surface()
                        .fill(EDITOR_RAISED)
                        .inner_margin(14)
                        .corner_radius(12)
                        .show(ui, |ui| {
                            let previous_type = effect["type"].as_str().unwrap_or("").to_owned();
                            choice(
                                ui,
                                locale,
                                "type",
                                &mut effect["type"],
                                &[
                                    "message",
                                    "flag",
                                    "set_tile",
                                    "add_stat",
                                    "set_stat",
                                    "multiply_stat",
                                    "give_item",
                                    "remove_item",
                                    "clear_inventory",
                                    "set_charges",
                                    "set_visited",
                                    "teleport",
                                    "set_enemy",
                                    "battle_at",
                                    "wait",
                                    "sound",
                                    "cinematic",
                                    "move_tile",
                                    "next_cycle",
                                    "win",
                                ],
                            );
                            if effect["type"].as_str().unwrap_or("") != previous_type {
                                initialize_record(effect, true);
                            }
                            match effect["type"].as_str().unwrap_or("message") {
                                "message" => {
                                    text(ui, locale, "text", &mut effect["text"], true);
                                    optional_number(
                                        ui,
                                        locale,
                                        "dialogue_id",
                                        &mut effect["dialogue_id"],
                                    );
                                    optional_number(
                                        ui,
                                        locale,
                                        "duration_ms",
                                        &mut effect["duration_ms"],
                                    );
                                }
                                "wait" => number(ui, locale, "ms", &mut effect["ms"], 120),
                                "sound" => text(ui, locale, "cue", &mut effect["cue"], false),
                                "cinematic" => {
                                    choice(
                                        ui,
                                        locale,
                                        "kind",
                                        &mut effect["kind"],
                                        &[
                                            "magic", "capture", "fade_out", "fade_in", "fade",
                                            "fairy", "victory", "credits",
                                        ],
                                    );
                                    number(
                                        ui,
                                        locale,
                                        "duration_ms",
                                        &mut effect["duration_ms"],
                                        650,
                                    );
                                }
                                "move_tile" => {
                                    for key in ["floor", "from_x", "from_y", "x", "y"] {
                                        number(ui, locale, key, &mut effect[key], 0);
                                    }
                                    number(
                                        ui,
                                        locale,
                                        "duration_ms",
                                        &mut effect["duration_ms"],
                                        120,
                                    );
                                }
                                "flag" => {
                                    text(ui, locale, "flag", &mut effect["flag"], false);
                                    boolean(ui, locale, "value", &mut effect["value"], true);
                                }
                                "set_tile" | "teleport" | "battle_at" => {
                                    for key in ["floor", "x", "y"] {
                                        number(ui, locale, key, &mut effect[key], 0);
                                    }
                                    if effect["type"] == "set_tile" {
                                        number(ui, locale, "tile", &mut effect["tile"], 6);
                                    }
                                    if effect["type"] == "battle_at" {
                                        boolean(
                                            ui,
                                            locale,
                                            "first_strike",
                                            &mut effect["first_strike"],
                                            false,
                                        );
                                    }
                                }
                                "add_stat" | "set_stat" | "multiply_stat" => {
                                    choice(
                                        ui,
                                        locale,
                                        "stat",
                                        &mut effect["stat"],
                                        &[
                                            "hp", "attack", "defense", "gold", "yellow", "blue",
                                            "red",
                                        ],
                                    );
                                    if effect["type"] == "multiply_stat" {
                                        number(
                                            ui,
                                            locale,
                                            "numerator",
                                            &mut effect["numerator"],
                                            1,
                                        );
                                        number(
                                            ui,
                                            locale,
                                            "denominator",
                                            &mut effect["denominator"],
                                            1,
                                        );
                                    } else {
                                        number(ui, locale, "amount", &mut effect["amount"], 1);
                                    }
                                }
                                "give_item" | "remove_item" | "set_charges" => {
                                    text(ui, locale, "item", &mut effect["item"], false);
                                    if effect["type"] == "set_charges" {
                                        number(ui, locale, "charges", &mut effect["charges"], 1);
                                    }
                                }
                                "set_visited" => {
                                    scalar_array(ui, locale, "floors", &mut effect["floors"])
                                }
                                "set_enemy" => {
                                    text(ui, locale, "enemy", &mut effect["enemy"], false);
                                    for key in ["hp", "attack", "defense", "gold"] {
                                        optional_number(ui, locale, key, &mut effect[key]);
                                    }
                                }
                                _ => {}
                            }
                            conditions_ui(ui, locale, &mut effect["conditions"], 0);
                            ui.horizontal(|ui| {
                                if ui.add_enabled(index > 0, egui::Button::new("↑")).clicked() {
                                    reorder = Some((index, index - 1));
                                }
                                if ui
                                    .add_enabled(index + 1 < count, egui::Button::new("↓"))
                                    .clicked()
                                {
                                    reorder = Some((index, index + 1));
                                }
                                if ui.button(tr(locale, "remove")).clicked() {
                                    remove = Some(index);
                                }
                            });
                        });
                });
            }
            if let Some(index) = remove {
                list.remove(index);
            } else if let Some((a, b)) = reorder {
                list.swap(a, b);
            }
            if ui.button(tr(locale, "editor.add_effect")).clicked() {
                list.push(json!({"type":"message","text":""}));
            }
        },
    );
}

fn offers_ui(ui: &mut Ui, locale: &str, value: &mut Value) {
    ensure_array(value);
    let list = value.as_array_mut().unwrap();
    let mut remove = None;
    ui.collapsing(format!("{} ({})",tr(locale,"offers"),list.len()),|ui|{
        for(index,offer)in list.iter_mut().enumerate(){ui.push_id(("offer",index),|ui|{editor_surface().fill(EDITOR_RAISED).inner_margin(14).corner_radius(12).show(ui, |ui|{
            text(ui,locale,"id",&mut offer["id"],false);text(ui,locale,"label",&mut offer["label"],false);
            number(ui,locale,"cost",&mut offer["cost"],0);number(ui,locale,"cost_increment",&mut offer["cost_increment"],0);boolean(ui,locale,"once",&mut offer["once"],false);
            conditions_ui(ui,locale,&mut offer["conditions"],0);effects_ui(ui,locale,&mut offer["effects"]);
            if ui.button(tr(locale,"remove")).clicked(){remove=Some(index);}
        });});}
        if let Some(index)=remove{list.remove(index);}
        if ui.button(tr(locale,"editor.add_offer")).clicked(){list.push(json!({"id":format!("offer_{}",list.len()),"label":"New offer","cost":0,"once":false,"conditions":[],"effects":[]}));}
    });
}

fn draw_tile(ui: &Ui, rect: Rect, id: u16, definition: &Value, atlas: Option<(TextureId, Vec2)>) {
    let kind = definition["kind"].as_str().unwrap_or("floor");
    let color = match kind {
        "wall" | "hidden_wall" => Color32::from_rgb(62, 70, 83),
        "enemy" => Color32::from_rgb(106, 54, 71),
        "door" | "special_door" => Color32::from_rgb(133, 102, 52),
        "item" | "equipment" => Color32::from_rgb(64, 99, 129),
        "npc" | "merchant" | "fairy" => Color32::from_rgb(71, 112, 107),
        "lava" => Color32::from_rgb(140, 66, 44),
        _ => Color32::from_rgb(38, 46, 61),
    };
    ui.painter().rect_filled(rect.shrink(0.5), 2.0, color);
    if let Some((texture, size)) = atlas {
        let sprite = &definition["sprite"];
        if let (Some(x), Some(y), Some(w), Some(h)) = (
            sprite["x"].as_f64(),
            sprite["y"].as_f64(),
            sprite["w"].as_f64(),
            sprite["h"].as_f64(),
        ) {
            let uv = Rect::from_min_max(
                Pos2::new(x as f32 / size.x, y as f32 / size.y),
                Pos2::new((x + w) as f32 / size.x, (y + h) as f32 / size.y),
            );
            ui.painter()
                .image(texture, rect.shrink(1.0), uv, Color32::WHITE);
            ui.painter().text(
                rect.right_bottom() - egui::vec2(2.0, 1.0),
                egui::Align2::RIGHT_BOTTOM,
                id.to_string(),
                FontId::monospace(11.0),
                Color32::WHITE,
            );
            return;
        }
    }
    ui.painter().text(
        rect.center(),
        egui::Align2::CENTER_CENTER,
        id.to_string(),
        FontId::monospace((rect.width() * 0.35).clamp(9.0, 16.0)),
        Color32::from_rgb(230, 230, 235),
    );
}

fn resize_campaign(campaign: &mut Value, width: usize, height: usize) {
    let old_width = campaign["width"].as_u64().unwrap_or(11) as usize;
    let old_height = campaign["height"].as_u64().unwrap_or(11) as usize;
    let empty = campaign["rules"]["empty_tile"].as_u64().unwrap_or(6);
    if let Some(floors) = campaign["floors"].as_array_mut() {
        for floor in floors {
            let old = floor["tiles"].as_array().cloned().unwrap_or_default();
            let mut tiles = vec![json!(empty); width * height];
            for y in 0..height.min(old_height) {
                for x in 0..width.min(old_width) {
                    if let Some(value) = old.get(y * old_width + x) {
                        tiles[y * width + x] = value.clone();
                    }
                }
            }
            floor["tiles"] = json!(tiles);
            for key in ["arrival_up", "arrival_down"] {
                if floor[key].is_object() {
                    floor[key]["x"] = json!(
                        floor[key]["x"]
                            .as_u64()
                            .unwrap_or(0)
                            .min((width - 1) as u64)
                    );
                    floor[key]["y"] = json!(
                        floor[key]["y"]
                            .as_u64()
                            .unwrap_or(0)
                            .min((height - 1) as u64)
                    );
                }
            }
        }
    }
    campaign["width"] = json!(width);
    campaign["height"] = json!(height);
    campaign["start"]["x"] = json!(
        campaign["start"]["x"]
            .as_u64()
            .unwrap_or(0)
            .min((width - 1) as u64)
    );
    campaign["start"]["y"] = json!(
        campaign["start"]["y"]
            .as_u64()
            .unwrap_or(0)
            .min((height - 1) as u64)
    );
}
fn remap_floor_references(value: &mut Value, old: i64, new: i64) {
    match value {
        Value::Object(object) => {
            for (key, value) in object {
                if (key == "floor" || key == "target_floor") && value.as_i64() == Some(old) {
                    *value = json!(new);
                } else if key == "floors"
                    && value
                        .as_array()
                        .is_some_and(|values| values.iter().all(Value::is_i64))
                {
                    for floor in value.as_array_mut().unwrap() {
                        if floor.as_i64() == Some(old) {
                            *floor = json!(new);
                        }
                    }
                } else if key == "stair_links" {
                    if let Some(links) = value.as_object_mut() {
                        let previous = std::mem::take(links);
                        for (key, mut target) in previous {
                            let key = if let Some((floor, direction)) = key.split_once(':') {
                                if floor.parse::<i64>().ok() == Some(old) {
                                    format!("{new}:{direction}")
                                } else {
                                    key
                                }
                            } else {
                                key
                            };
                            if target.as_i64() == Some(old) {
                                target = json!(new);
                            }
                            links.insert(key, target);
                        }
                    }
                } else {
                    remap_floor_references(value, old, new);
                }
            }
        }
        Value::Array(array) => {
            for child in array {
                remap_floor_references(child, old, new)
            }
        }
        _ => {}
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    fn campaign() -> Value {
        serde_json::from_str(include_str!("../../../data/campaign.json")).unwrap()
    }
    #[test]
    fn painted_cells_undo_and_redo_without_losing_metadata() {
        let original = campaign();
        let mut editor = CampaignEditor::new(original.clone());
        assert!(editor.paint_cell(1, 5, 10, 8));
        assert!(editor.is_dirty());
        assert!(editor.undo());
        assert_eq!(editor.campaign(), &original);
        assert!(editor.redo());
        assert_eq!(editor.campaign()["floors"][1]["tiles"][115], 8);
        assert!(editor.validate().is_ok());
    }
    #[test]
    fn resizing_preserves_grid_coordinates_and_undo_restores_exact_source() {
        let original = campaign();
        let mut editor = CampaignEditor::new(original.clone());
        editor.resize_dimensions(12, 12);
        assert_eq!(
            editor.campaign()["floors"][1]["tiles"][10 * 12 + 5],
            original["floors"][1]["tiles"][10 * 11 + 5]
        );
        assert_eq!(editor.campaign()["floors"][1]["tiles"][11 * 12 + 11], 6);
        assert!(editor.validate().is_ok());
        editor.undo();
        assert_eq!(editor.campaign(), &original);
    }
    #[test]
    fn core_validation_blocks_undefined_tile_export() {
        let mut original = campaign();
        original["floors"][0]["tiles"][0] = json!(65535);
        assert!(CampaignEditor::new(original).validate().is_err());
    }
    #[test]
    fn viewing_every_editor_section_preserves_campaign_and_validity() {
        let original = campaign();
        let mut editor = CampaignEditor::new(original.clone());
        let context = egui::Context::default();
        for section in [
            Section::Floors,
            Section::Enemies,
            Section::Tiles,
            Section::Rules,
            Section::Npcs,
            Section::Events,
            Section::Advanced,
        ] {
            editor.section = section;
            // Open optional forms too: rendering must not introduce null schema fields.
            context.memory_mut(|memory| memory.set_everything_is_visible(true));
            context
                .run_ui(
                    egui::RawInput {
                        screen_rect: Some(Rect::from_min_size(
                            Pos2::ZERO,
                            Vec2::new(1400.0, 1000.0),
                        )),
                        ..Default::default()
                    },
                    |ui| {
                        editor.show(ui, "en");
                    },
                )
                .drop_without_applying_deltas();
            assert_eq!(
                editor.campaign(),
                &original,
                "Viewing {section:?} changed campaign"
            );
            assert!(
                !editor.is_dirty(),
                "Viewing {section:?} marked campaign dirty"
            );
            assert!(
                editor.validate().is_ok(),
                "Viewing {section:?} invalidated campaign"
            );
        }
    }
    #[test]
    fn editor_layout_reserves_footer_and_shows_desktop_palette_beside_board() {
        for width in [1360.0, 390.0] {
            let mut editor = CampaignEditor::new(campaign());
            let context = egui::Context::default();
            context.all_styles_mut(|style| {
                for font in style.text_styles.values_mut() {
                    font.size = 20.0;
                }
            });
            let viewport = Rect::from_min_size(Pos2::ZERO, Vec2::new(width, 920.0));
            let mut footer = Rect::NOTHING;
            for _ in 0..2 {
                context
                    .run_ui(
                        egui::RawInput {
                            screen_rect: Some(viewport),
                            ..Default::default()
                        },
                        |ui| {
                            editor.show(ui, "en");
                            footer = ui.button("Back to game").rect;
                        },
                    )
                    .drop_without_applying_deltas();
            }
            assert!(
                footer.bottom() <= viewport.bottom(),
                "Footer inaccessible at width {width}: {footer:?}"
            );
            assert!(editor.bounds["content"].bottom() <= viewport.bottom() - 40.0);
            if width > 820.0 {
                assert!(editor.bounds["board"].right() < editor.bounds["search"].left());
                assert!(editor.bounds["board"].bottom() <= editor.bounds["content"].bottom());
                assert!(editor.bounds["search"].bottom() <= editor.bounds["content"].bottom());
            }
            assert!(!editor.is_dirty());
        }
    }
    #[test]
    fn floor_renaming_updates_nested_events_and_stair_links() {
        let mut value = json!({"floors":[{"id":1,"tiles":[]}],"start":{"floor":1},
            "events":[{"trigger":{"floor":1},"effects":[{"type":"set_visited","floors":[1,2]},{"type":"set_tile","floor":1,"x":0,"y":0,"tile":6}]}],
            "rules":{"stair_links":{"1:up":2,"2:down":1}},"tiles":{"8":{"target_floor":1}}});
        remap_floor_references(&mut value, 1, 3);
        assert_eq!(value["start"]["floor"], 3);
        assert_eq!(value["events"][0]["trigger"]["floor"], 3);
        assert_eq!(value["events"][0]["effects"][0]["floors"], json!([3, 2]));
        assert_eq!(value["events"][0]["effects"][1]["floor"], 3);
        assert_eq!(value["tiles"]["8"]["target_floor"], 3);
        assert_eq!(value["rules"]["stair_links"], json!({"3:up":2,"2:down":3}));
        assert_eq!(value["floors"][0]["tiles"], json!([]));
    }
    #[test]
    fn numeric_typing_keeps_focus_when_validation_notice_disappears() {
        let context = egui::Context::default();
        let mut editor = CampaignEditor::new(campaign());
        editor.section = Section::Enemies;
        editor.validation = Some(Ok(()));
        let render = |editor: &mut CampaignEditor, events| {
            context
                .run_ui(
                    egui::RawInput {
                        screen_rect: Some(Rect::from_min_size(
                            Pos2::ZERO,
                            Vec2::new(1360.0, 920.0),
                        )),
                        events,
                        ..Default::default()
                    },
                    |ui| {
                        editor.show(ui, "en");
                    },
                )
                .drop_without_applying_deltas();
        };
        render(&mut editor, vec![]);
        render(&mut editor, vec![]);
        let point = editor.bounds["enemy.hp"].center();
        render(
            &mut editor,
            vec![
                egui::Event::PointerMoved(point),
                egui::Event::PointerButton {
                    pos: point,
                    button: egui::PointerButton::Primary,
                    pressed: true,
                    modifiers: egui::Modifiers::NONE,
                },
            ],
        );
        render(
            &mut editor,
            vec![egui::Event::PointerButton {
                pos: point,
                button: egui::PointerButton::Primary,
                pressed: false,
                modifiers: egui::Modifiers::NONE,
            }],
        );
        render(&mut editor, vec![]);
        for digit in ["1", "3", "7"] {
            render(&mut editor, vec![egui::Event::Text(digit.into())]);
        }
        render(
            &mut editor,
            vec![egui::Event::Key {
                key: egui::Key::Enter,
                physical_key: None,
                pressed: true,
                repeat: false,
                modifiers: egui::Modifiers::NONE,
            }],
        );
        assert_eq!(
            editor.campaign["enemies"][&editor.selected_enemy]["hp"],
            137
        );
        assert!(editor.validation.is_none());
        assert!(editor.is_dirty());
    }
}
