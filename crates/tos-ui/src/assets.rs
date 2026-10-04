use eframe::egui::{self, ColorImage, TextureHandle, TextureOptions};
use std::collections::BTreeMap;

#[derive(Default)]
pub struct Art {
    pub atlas: Option<TextureHandle>,
    pub heroes: BTreeMap<String, [TextureHandle; 2]>,
    pub size: [usize; 2],
}

impl Art {
    pub fn install(&mut self, ctx: &egui::Context, bytes: &[u8]) -> Result<(), String> {
        let image = image::load_from_memory(bytes)
            .map_err(|e| e.to_string())?
            .to_rgba8();
        self.size = [image.width() as usize, image.height() as usize];
        self.atlas = Some(ctx.load_texture(
            "original sprites",
            ColorImage::from_rgba_unmultiplied(self.size, image.as_raw()),
            TextureOptions::NEAREST,
        ));
        if image.width() < 440 || image.height() < 800 {
            return Ok(());
        }
        for (direction, first) in [("down", 185), ("left", 193), ("right", 201), ("up", 209)] {
            let frames = [first, first + 2].map(|tile| {
                let index = tile - 1;
                let mut pixels = Vec::with_capacity(40 * 40 * 4);
                for y in 0..40 {
                    for x in 0..40 {
                        let mut color = image.get_pixel(index % 11 * 40 + x, index / 11 * 40 + y).0;
                        let mask = image
                            .get_pixel((index + 1) % 11 * 40 + x, (index + 1) / 11 * 40 + y)
                            .0;
                        color[3] = 255 - mask[0];
                        pixels.extend_from_slice(&color);
                    }
                }
                ctx.load_texture(
                    format!("hero {direction} {tile}"),
                    ColorImage::from_rgba_unmultiplied([40, 40], &pixels),
                    TextureOptions::NEAREST,
                )
            });
            self.heroes.insert(direction.into(), frames);
        }
        Ok(())
    }

    pub fn tile(
        &self,
        painter: &egui::Painter,
        rect: egui::Rect,
        sprite: &serde_json::Value,
        tint: egui::Color32,
    ) -> bool {
        let Some(atlas) = &self.atlas else {
            return false;
        };
        let (x, y, w, h) = if sprite.is_object() {
            (
                sprite["x"].as_f64().unwrap_or(200.0) as f32,
                sprite["y"].as_f64().unwrap_or(0.0) as f32,
                sprite["w"].as_f64().unwrap_or(40.0) as f32,
                sprite["h"].as_f64().unwrap_or(40.0) as f32,
            )
        } else {
            let id = sprite.as_u64().unwrap_or(6).saturating_sub(1) as usize;
            ((id % 11 * 40) as f32, (id / 11 * 40) as f32, 40.0, 40.0)
        };
        let uv = egui::Rect::from_min_max(
            egui::pos2(x / self.size[0] as f32, y / self.size[1] as f32),
            egui::pos2((x + w) / self.size[0] as f32, (y + h) / self.size[1] as f32),
        );
        painter.image(atlas.id(), rect, uv, tint);
        true
    }
}
