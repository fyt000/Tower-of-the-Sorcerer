//! Shared visual primitives for the native and WebAssembly interfaces.

use eframe::egui::{
    self, Color32, Context, FontId, InnerResponse, Layout, Painter, Rect, Response, RichText,
    Sense, Shape, Stroke, StrokeKind, Ui, WidgetInfo, WidgetText, WidgetType, pos2, vec2,
};

pub const BG: Color32 = Color32::from_rgb(19, 23, 40);
pub const SURFACE: Color32 = Color32::from_rgb(31, 37, 59);
pub const SURFACE_RAISED: Color32 = Color32::from_rgb(43, 48, 73);
pub const TEXT: Color32 = Color32::from_rgb(237, 238, 249);
pub const MUTED: Color32 = Color32::from_rgb(173, 184, 210);
pub const BORDER: Color32 = Color32::from_rgb(77, 86, 117);
pub const GOLD: Color32 = Color32::from_rgb(216, 184, 124);
pub const YELLOW: Color32 = GOLD;
pub const ACCENT: Color32 = Color32::from_rgb(120, 136, 209);
pub const GREEN: Color32 = Color32::from_rgb(128, 189, 155);
pub const RED: Color32 = Color32::from_rgb(213, 121, 121);
pub const BLUE: Color32 = Color32::from_rgb(132, 184, 215);

/// Modern indigo tower surfaces become warm crimson on the reverse side.
/// Semantic health, reward and key colors remain independent of the tower palette.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Palette {
    pub bg: Color32,
    pub surface: Color32,
    pub raised: Color32,
    pub text: Color32,
    pub muted: Color32,
    pub border: Color32,
    pub metal: Color32,
    pub accent: Color32,
}

pub const fn palette(reverse: bool) -> Palette {
    if reverse {
        Palette {
            bg: Color32::from_rgb(37, 15, 15),
            surface: Color32::from_rgb(57, 26, 25),
            raised: Color32::from_rgb(78, 35, 33),
            text: Color32::from_rgb(252, 239, 233),
            muted: Color32::from_rgb(220, 177, 167),
            border: Color32::from_rgb(145, 74, 68),
            metal: Color32::from_rgb(240, 165, 151),
            accent: Color32::from_rgb(221, 86, 74),
        }
    } else {
        Palette {
            bg: BG,
            surface: SURFACE,
            raised: SURFACE_RAISED,
            text: TEXT,
            muted: MUTED,
            border: BORDER,
            metal: Color32::from_rgb(170, 185, 227),
            accent: ACCENT,
        }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
struct ThemeState {
    reverse: bool,
    compact: bool,
    scale_milli: u16,
}

fn state(ctx: &Context) -> ThemeState {
    ctx.data(|data| {
        data.get_temp::<ThemeState>(egui::Id::new("tower_theme"))
            .unwrap_or_default()
    })
}

pub fn colors(ctx: &Context) -> Palette {
    palette(state(ctx).reverse)
}

pub fn scale(ctx: &Context) -> f32 {
    f32::from(state(ctx).scale_milli.max(1000)) / 1000.0
}

pub fn font_size(ctx: &Context, base: f32) -> f32 {
    base * scale(ctx)
}

/// Call with the currently presented world, so animated travel cannot reveal a future cycle.
pub fn apply(ctx: &Context, reverse: bool, compact: bool, desktop_scale: f32) {
    let next = ThemeState {
        reverse,
        compact,
        scale_milli: (desktop_scale.clamp(1.0, 2.0) * 1000.0).round() as u16,
    };
    let changed = ctx.data_mut(|data| {
        let id = egui::Id::new("tower_theme");
        if data.get_temp::<ThemeState>(id) == Some(next) {
            false
        } else {
            data.insert_temp(id, next);
            true
        }
    });
    if !changed {
        return;
    }
    let c = palette(reverse);
    let scale = scale(ctx);
    ctx.global_style_mut(|style| {
        for (text_style, size) in [
            (egui::TextStyle::Body, 17.0),
            (egui::TextStyle::Button, 17.0),
            (egui::TextStyle::Small, 15.0),
            (egui::TextStyle::Heading, 28.0),
        ] {
            style
                .text_styles
                .insert(text_style, FontId::proportional(size * scale));
        }
        style
            .text_styles
            .insert(egui::TextStyle::Monospace, FontId::monospace(16.0 * scale));
        style.spacing.icon_width = 18.0 * scale;
        style.spacing.icon_spacing = 8.0 * scale;
        style.visuals.override_text_color = Some(c.text);
        style.visuals.panel_fill = c.bg;
        style.visuals.window_fill = c.surface;
        style.visuals.extreme_bg_color = c.bg;
        style.visuals.faint_bg_color = c.raised;
        style.visuals.code_bg_color = c.raised;
        style.visuals.hyperlink_color = c.metal;
        style.visuals.selection.bg_fill = c.accent.linear_multiply(0.45);
        style.visuals.selection.stroke = Stroke::new(1.0, c.metal);
        style.visuals.window_corner_radius = egui::CornerRadius::same(10);
        style.visuals.window_stroke = Stroke::new(1.0, c.border);
        style.visuals.widgets.noninteractive.bg_fill = c.surface;
        style.visuals.widgets.noninteractive.weak_bg_fill = c.surface;
        style.visuals.widgets.noninteractive.bg_stroke = Stroke::new(1.0, c.border);
        style.visuals.widgets.noninteractive.fg_stroke = Stroke::new(1.0, c.text);
        for widget in [
            &mut style.visuals.widgets.inactive,
            &mut style.visuals.widgets.hovered,
            &mut style.visuals.widgets.active,
            &mut style.visuals.widgets.open,
        ] {
            widget.corner_radius = egui::CornerRadius::same(6);
            widget.bg_fill = c.raised;
            widget.weak_bg_fill = c.raised;
            widget.bg_stroke = Stroke::new(1.0, c.border);
            widget.fg_stroke = Stroke::new(1.0, c.text);
        }
        style.visuals.widgets.hovered.bg_fill = c.raised.lerp_to_gamma(c.accent, 0.22);
        style.visuals.widgets.hovered.weak_bg_fill = style.visuals.widgets.hovered.bg_fill;
        style.visuals.widgets.hovered.bg_stroke = Stroke::new(1.0, c.metal);
        style.visuals.widgets.active.bg_fill = c.raised.lerp_to_gamma(c.accent, 0.35);
        style.visuals.widgets.active.weak_bg_fill = style.visuals.widgets.active.bg_fill;
        style.visuals.widgets.active.bg_stroke = Stroke::new(1.0, c.metal);
        style.spacing.item_spacing = if compact {
            vec2(5.0, 4.0)
        } else {
            vec2(7.0, 6.0) * scale
        };
        style.spacing.button_padding = if compact {
            vec2(8.0, 4.0)
        } else {
            vec2(10.0, 6.0) * scale
        };
        style.spacing.window_margin =
            egui::Margin::same(if compact { 10 } else { (16.0 * scale) as i8 });
    });
}

pub fn card_padding(ctx: &Context) -> f32 {
    if state(ctx).compact {
        8.0
    } else {
        (12.0 * scale(ctx)).round()
    }
}

pub fn frame(ctx: &Context) -> egui::Frame {
    let c = colors(ctx);
    egui::Frame::new()
        .fill(c.surface)
        .stroke(Stroke::new(1.0, c.border))
        .corner_radius(8)
        .inner_margin(card_padding(ctx) as i8)
        .shadow(egui::epaint::Shadow {
            offset: [0, 2],
            blur: 8,
            spread: 0,
            color: Color32::from_black_alpha(34),
        })
}

/// `outer_width` includes the card's horizontal padding.
/// Force a vertical layout even when the caller is arranging cards in a row.
pub fn card<R>(
    ui: &mut Ui,
    outer_width: f32,
    contents: impl FnOnce(&mut Ui) -> R,
) -> InnerResponse<R> {
    let inset = card_padding(ui.ctx());
    let c = colors(ui.ctx());
    let response = frame(ui.ctx()).show(ui, |ui| {
        ui.with_layout(Layout::top_down(egui::Align::Min), |ui| {
            ui.set_width((outer_width - 2.0 * inset).max(1.0));
            contents(ui)
        })
        .inner
    });
    tower_edge(ui.painter(), response.response.rect, c);
    response
}

pub fn caption(ui: &mut Ui, label: &str) -> Response {
    ui.label(
        RichText::new(label)
            .size(font_size(ui.ctx(), 12.0))
            .strong()
            .color(colors(ui.ctx()).muted),
    )
}

/// Subtle code-drawn stone courses add depth without original UI bitmaps.
pub fn paint_tower_backdrop(ui: &Ui, rect: Rect) {
    let c = colors(ui.ctx());
    let painter = ui.painter();
    painter.rect_filled(rect, 0.0, c.bg);
    let mortar = c.bg.lerp_to_gamma(Color32::BLACK, 0.18);
    let stone_highlight = c.bg.lerp_to_gamma(c.border, 0.24);
    let course = 24.0;
    let block = 64.0;
    let rows = (rect.height() / course).ceil() as i32;
    let columns = (rect.width() / block).ceil() as i32 + 1;
    for row in 0..rows {
        let y = rect.top() + row as f32 * course;
        painter.line_segment(
            [pos2(rect.left(), y), pos2(rect.right(), y)],
            Stroke::new(1.0, mortar),
        );
        let offset = if row % 2 == 0 { 0.0 } else { block * 0.5 };
        for column in 0..columns {
            let x = rect.left() + column as f32 * block + offset;
            if x < rect.right() {
                painter.line_segment(
                    [pos2(x, y), pos2(x, (y + course).min(rect.bottom()))],
                    Stroke::new(1.0, mortar),
                );
                let tile = Rect::from_min_max(
                    pos2((x + 2.0).min(rect.right()), (y + 2.0).min(rect.bottom())),
                    pos2(
                        (x + block - 2.0).min(rect.right()),
                        (y + course - 2.0).min(rect.bottom()),
                    ),
                );
                painter.line_segment(
                    [tile.left_top(), tile.right_top()],
                    Stroke::new(1.0, stone_highlight),
                );
            }
        }
    }
}

/// A restrained inner highlight keeps modern panels distinct from the stone surround.
pub fn tower_edge(painter: &Painter, rect: Rect, c: Palette) {
    let rect = rect.shrink(2.0);
    painter.rect_stroke(
        rect,
        6,
        Stroke::new(1.0, c.border.linear_multiply(0.18)),
        StrokeKind::Inside,
    );
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Icon {
    Tower,
    Heart,
    Sword,
    Shield,
    Coin,
    Key,
    Save,
    Restore,
    Edit,
    Settings,
    Book,
    Compass,
    ArrowLeft,
    ArrowRight,
    Close,
}

/// Draw crisp, resolution-independent line icons on a normalized 24-point grid.
pub fn icon(painter: &Painter, rect: Rect, kind: Icon, color: Color32) {
    let size = rect.width().min(rect.height());
    let origin = rect.center() - vec2(size, size) * 0.5;
    let point = |x: f32, y: f32| origin + vec2(x, y) * (size / 24.0);
    let stroke = Stroke::new((size / 24.0 * 1.6).max(1.0), color);
    let line = |a: [f32; 2], b: [f32; 2]| {
        painter.line_segment([point(a[0], a[1]), point(b[0], b[1])], stroke);
    };
    let path = |points: &[[f32; 2]], closed: bool| {
        let points = points.iter().map(|p| point(p[0], p[1])).collect();
        painter.add(if closed {
            Shape::closed_line(points, stroke)
        } else {
            Shape::line(points, stroke)
        });
    };
    let circle = |x: f32, y: f32, radius: f32| {
        painter.circle_stroke(point(x, y), radius * size / 24.0, stroke);
    };
    match kind {
        Icon::Tower => {
            path(
                &[[6., 21.], [6., 7.], [12., 3.], [18., 7.], [18., 21.]],
                false,
            );
            line([3., 21.], [21., 21.]);
            line([9., 9.], [15., 9.]);
            line([10., 13.], [14., 13.]);
            path(&[[10., 21.], [10., 17.], [14., 17.], [14., 21.]], false);
        }
        Icon::Heart => {
            path(
                &[
                    [12., 21.],
                    [5., 15.],
                    [2.9, 12.2],
                    [2., 9.5],
                    [2.2, 7.],
                    [3.6, 4.8],
                    [5.7, 3.8],
                    [8., 3.9],
                    [10.4, 5.1],
                    [12., 7.2],
                    [13.6, 5.1],
                    [16., 3.9],
                    [18.3, 3.8],
                    [20.4, 4.8],
                    [21.8, 7.],
                    [22., 9.5],
                    [21.1, 12.2],
                    [19., 15.],
                ],
                true,
            );
        }
        Icon::Sword => {
            path(
                &[[8., 15.], [18., 5.], [21., 3.], [20., 8.], [10., 18.]],
                false,
            );
            line([6., 13.], [12., 19.]);
            line([9., 16.], [4., 21.]);
            line([3., 19.], [5., 21.]);
        }
        Icon::Shield => {
            path(
                &[
                    [12., 3.],
                    [20., 6.],
                    [19.5, 13.],
                    [17.5, 17.],
                    [12., 21.],
                    [6.5, 17.],
                    [4.5, 13.],
                    [4., 6.],
                ],
                true,
            );
            line([12., 7.], [12., 16.]);
        }
        Icon::Coin => {
            circle(12., 12., 9.);
            circle(12., 12., 6.);
            line([12., 7.], [12., 17.]);
            path(
                &[
                    [15., 9.],
                    [10., 9.],
                    [9., 10.],
                    [10., 12.],
                    [14., 12.],
                    [15., 14.],
                    [14., 15.],
                    [9., 15.],
                ],
                false,
            );
        }
        Icon::Key => {
            circle(7.5, 7.5, 4.5);
            line([10.7, 10.7], [21., 21.]);
            line([16., 16.], [19., 13.]);
            line([19., 19.], [22., 16.]);
        }
        Icon::Save => {
            path(
                &[
                    [4., 3.],
                    [17., 3.],
                    [21., 7.],
                    [21., 21.],
                    [3., 21.],
                    [3., 3.],
                ],
                true,
            );
            path(&[[7., 3.], [7., 9.], [16., 9.], [16., 3.]], false);
            path(&[[7., 21.], [7., 14.], [17., 14.], [17., 21.]], false);
            line([13., 5.], [13., 7.]);
        }
        Icon::Restore => {
            path(
                &[
                    [4., 10.],
                    [6., 6.],
                    [9., 4.],
                    [13., 3.5],
                    [17., 5.],
                    [20., 8.],
                    [21., 12.],
                    [20., 16.],
                    [17., 19.],
                    [13., 20.],
                    [9., 19.],
                ],
                false,
            );
            path(&[[4., 4.], [4., 10.], [10., 10.]], false);
            path(&[[13., 7.], [13., 12.], [16., 14.]], false);
        }
        Icon::Edit => {
            path(
                &[
                    [4., 15.],
                    [15., 4.],
                    [17., 3.],
                    [21., 7.],
                    [20., 9.],
                    [9., 20.],
                    [3., 21.],
                ],
                true,
            );
            line([13., 6.], [18., 11.]);
            line([4., 15.], [9., 20.]);
        }
        Icon::Settings => {
            line([3., 6.], [21., 6.]);
            line([3., 12.], [21., 12.]);
            line([3., 18.], [21., 18.]);
            for (x, y) in [(8., 6.), (16., 12.), (9., 18.)] {
                painter.circle_filled(point(x, y), size / 24.0 * 2.3, colors(painter.ctx()).raised);
                circle(x, y, 2.3);
            }
        }
        Icon::Book => {
            path(
                &[
                    [12., 6.],
                    [9., 4.5],
                    [3., 4.],
                    [3., 19.],
                    [9., 19.5],
                    [12., 21.],
                    [15., 19.5],
                    [21., 19.],
                    [21., 4.],
                    [15., 4.5],
                ],
                true,
            );
            line([12., 6.], [12., 21.]);
            line([6., 8.], [9., 8.5]);
            line([6., 12.], [9., 12.5]);
            line([15., 8.5], [18., 8.]);
            line([15., 12.5], [18., 12.]);
        }
        Icon::Compass => {
            circle(12., 12., 9.);
            path(
                &[[15.5, 8.5], [13.8, 13.8], [8.5, 15.5], [10.2, 10.2]],
                true,
            );
            line([10.2, 10.2], [13.8, 13.8]);
        }
        Icon::ArrowLeft => {
            line([20., 12.], [4., 12.]);
            path(&[[10., 6.], [4., 12.], [10., 18.]], false);
        }
        Icon::ArrowRight => {
            line([4., 12.], [20., 12.]);
            path(&[[14., 6.], [20., 12.], [14., 18.]], false);
        }
        Icon::Close => {
            line([6., 6.], [18., 18.]);
            line([18., 6.], [6., 18.]);
        }
    }
}

/// Consistent compact actions without depending on font-provided icon glyphs.
/// An empty label produces a square icon button.
pub fn action(ui: &mut Ui, label: impl Into<String>, kind: Icon, primary: bool) -> Response {
    action_sized(ui, label, kind, primary, None)
}

pub fn action_sized(
    ui: &mut Ui,
    label: impl Into<String>,
    kind: Icon,
    primary: bool,
    width: Option<f32>,
) -> Response {
    let label = label.into();
    let compact = state(ui.ctx()).compact;
    let c = colors(ui.ctx());
    let scale = scale(ui.ctx());
    let size = if compact { 13.0 } else { 14.0 * scale };
    let height = if compact { 28.0 } else { 34.0 * scale };
    let galley = WidgetText::from(RichText::new(label.as_str()).size(size).strong()).into_galley(
        ui,
        Some(egui::TextWrapMode::Extend),
        f32::INFINITY,
        FontId::proportional(size),
    );
    let width = width.unwrap_or_else(|| {
        if label.is_empty() {
            height
        } else {
            galley.size().x + if compact { 42.0 } else { 48.0 * scale }
        }
    });
    let (rect, response) = ui.allocate_exact_size(vec2(width, height), Sense::click());
    response
        .widget_info(|| WidgetInfo::labeled(WidgetType::Button, ui.is_enabled(), label.as_str()));
    let response = response.on_hover_cursor(egui::CursorIcon::PointingHand);
    if ui.is_rect_visible(rect) {
        let hovered =
            ui.ctx()
                .animate_bool_with_time(response.id.with("hover"), response.hovered(), 0.13);
        let pressed = response.is_pointer_button_down_on();
        let fill = if primary {
            c.metal.lerp_to_gamma(c.text, hovered * 0.35)
        } else {
            c.raised.lerp_to_gamma(c.accent, hovered * 0.25)
        };
        let fill = if pressed {
            fill.lerp_to_gamma(c.bg, 0.15)
        } else {
            fill
        };
        let border = if primary {
            c.metal
        } else {
            c.border.lerp_to_gamma(c.metal, hovered)
        };
        let foreground = if primary {
            Color32::from_gray(38)
        } else {
            c.text
        };
        let foreground = if ui.is_enabled() {
            foreground
        } else {
            foreground.lerp_to_gamma(fill, 0.55)
        };
        let painter = ui.painter();
        painter.rect_filled(rect, 6, fill);
        painter.rect_stroke(rect, 6, Stroke::new(1.0, border), StrokeKind::Inside);
        if response.has_focus() {
            painter.rect_stroke(
                rect.expand(2.0),
                8,
                Stroke::new(1.5, c.metal),
                StrokeKind::Outside,
            );
        }
        let icon_size = if compact { 15.0 } else { 17.0 * scale };
        let icon_left = if label.is_empty() {
            rect.center().x - icon_size * 0.5
        } else {
            rect.left() + if compact { 9.0 } else { 10.0 * scale }
        };
        icon(
            painter,
            Rect::from_min_size(
                pos2(icon_left, rect.center().y - icon_size * 0.5),
                vec2(icon_size, icon_size),
            ),
            kind,
            foreground,
        );
        if !label.is_empty() {
            painter.galley_with_override_text_color(
                pos2(
                    rect.left() + if compact { 32.0 } else { 36.0 * scale },
                    rect.center().y - galley.size().y * 0.5,
                ),
                galley,
                foreground,
            );
        }
    }
    response
}
