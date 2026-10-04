//! Shared visual primitives for the native and WebAssembly interfaces.

use egui::{
    Color32, FontId, InnerResponse, Layout, Painter, Rect, Response, RichText, Sense, Shape,
    Stroke, StrokeKind, Ui, WidgetInfo, WidgetText, WidgetType, pos2, vec2,
};

pub const BG: Color32 = Color32::from_rgb(11, 16, 26);
pub const SURFACE: Color32 = Color32::from_rgb(17, 26, 40);
pub const SURFACE_RAISED: Color32 = Color32::from_rgb(21, 31, 46);
pub const TEXT: Color32 = Color32::from_rgb(231, 233, 238);
pub const MUTED: Color32 = Color32::from_rgb(151, 164, 182);
pub const BORDER: Color32 = Color32::from_rgb(37, 48, 66);
pub const GOLD: Color32 = Color32::from_rgb(216, 184, 124);
pub const ACCENT: Color32 = Color32::from_rgb(163, 151, 230);
pub const GREEN: Color32 = Color32::from_rgb(128, 189, 155);
pub const RED: Color32 = Color32::from_rgb(213, 121, 121);
pub const BLUE: Color32 = Color32::from_rgb(132, 184, 215);

pub fn frame() -> egui::Frame {
    egui::Frame::new()
        .fill(SURFACE)
        .stroke(Stroke::new(1.0, BORDER))
        .corner_radius(14)
        .inner_margin(18)
        .shadow(egui::epaint::Shadow {
            offset: [0, 5],
            blur: 20,
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
    frame().show(ui, |ui| {
        ui.with_layout(Layout::top_down(egui::Align::Min), |ui| {
            ui.set_width((outer_width - 36.0).max(1.0));
            contents(ui)
        })
        .inner
    })
}

pub fn caption(ui: &mut Ui, label: &str) -> Response {
    ui.label(RichText::new(label).size(13.0).strong().color(MUTED))
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
    ArrowUp,
    ArrowDown,
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
                painter.circle_filled(point(x, y), size / 24.0 * 2.3, SURFACE_RAISED);
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
        Icon::ArrowUp => {
            line([12., 20.], [12., 4.]);
            path(&[[6., 10.], [12., 4.], [18., 10.]], false);
        }
        Icon::ArrowDown => {
            line([12., 4.], [12., 20.]);
            path(&[[6., 14.], [12., 20.], [18., 14.]], false);
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
    let label = label.into();
    let galley = WidgetText::from(RichText::new(label.as_str()).size(15.0).strong()).into_galley(
        ui,
        Some(egui::TextWrapMode::Extend),
        f32::INFINITY,
        FontId::proportional(15.0),
    );
    let width = if label.is_empty() {
        38.0
    } else {
        galley.size().x + 54.0
    };
    let (rect, response) = ui.allocate_exact_size(vec2(width, 38.0), Sense::click());
    response
        .widget_info(|| WidgetInfo::labeled(WidgetType::Button, ui.is_enabled(), label.as_str()));
    let response = response.on_hover_cursor(egui::CursorIcon::PointingHand);
    if ui.is_rect_visible(rect) {
        let hovered =
            ui.ctx()
                .animate_bool_with_time(response.id.with("hover"), response.hovered(), 0.13);
        let pressed = response.is_pointer_button_down_on();
        let fill = if primary {
            GOLD.lerp_to_gamma(Color32::from_rgb(236, 205, 148), hovered)
        } else {
            SURFACE_RAISED.lerp_to_gamma(Color32::from_rgb(29, 43, 61), hovered)
        };
        let fill = if pressed {
            fill.lerp_to_gamma(BG, 0.15)
        } else {
            fill
        };
        let border = if primary {
            GOLD
        } else {
            BORDER.lerp_to_gamma(Color32::from_rgb(74, 91, 114), hovered)
        };
        let foreground = if primary { BG } else { TEXT };
        let foreground = if ui.is_enabled() {
            foreground
        } else {
            foreground.lerp_to_gamma(fill, 0.55)
        };
        let painter = ui.painter();
        painter.rect_filled(rect, 8, fill);
        painter.rect_stroke(rect, 8, Stroke::new(1.0, border), StrokeKind::Inside);
        if response.has_focus() {
            painter.rect_stroke(
                rect.expand(2.0),
                10,
                Stroke::new(1.5, GOLD),
                StrokeKind::Outside,
            );
        }
        let icon_left = if label.is_empty() {
            rect.center().x - 9.0
        } else {
            rect.left() + 12.0
        };
        icon(
            painter,
            Rect::from_min_size(pos2(icon_left, rect.center().y - 9.0), vec2(18.0, 18.0)),
            kind,
            foreground,
        );
        if !label.is_empty() {
            painter.galley_with_override_text_color(
                pos2(rect.left() + 38.0, rect.center().y - galley.size().y * 0.5),
                galley,
                foreground,
            );
        }
    }
    response
}
