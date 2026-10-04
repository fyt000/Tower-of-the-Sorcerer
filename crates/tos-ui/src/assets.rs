use eframe::egui::{self, ColorImage, TextureHandle, TextureOptions};
use std::collections::BTreeMap;

#[derive(Default)]
pub struct Art {
    pub atlas: Option<TextureHandle>,
    /// The original two walking poses followed by the distinct standing pose.
    pub heroes: BTreeMap<String, [TextureHandle; 3]>,
    /// Directional hero poses with the original impact burst already painted in.
    pub hero_hits: BTreeMap<String, TextureHandle>,
    /// Enemy impact color cell 184, with alpha recovered from mask cell 183.
    pub impact: Option<TextureHandle>,
    pub size: [usize; 2],
    pub scenes: BTreeMap<String, TextureHandle>,
    scene_sources: BTreeMap<String, image::RgbaImage>,
    scene_masks: BTreeMap<(String, u32), TextureHandle>,
    original_image: Option<image::RgbaImage>,
    masked: BTreeMap<(u32, u32), TextureHandle>,
    foreground_masks: Option<image::RgbaImage>,
    foregrounds: BTreeMap<(u32, u32, u32, u32), TextureHandle>,
}

impl Art {
    pub fn install_scene(
        &mut self,
        ctx: &egui::Context,
        name: &str,
        bytes: &[u8],
    ) -> Result<(), String> {
        let source = image::load_from_memory(bytes)
            .map_err(|e| e.to_string())?
            .to_rgba8();
        let texture = ctx.load_texture(
            name,
            ColorImage::from_rgba_unmultiplied(
                [source.width() as usize, source.height() as usize],
                source.as_raw(),
            ),
            TextureOptions::NEAREST,
        );
        self.scenes.insert(name.into(), texture);
        self.scene_sources.insert(name.into(), source);
        self.scene_masks.retain(|(path, _), _| path != name);
        Ok(())
    }

    /// Original title-to-vortex dissolve: repeat the executable's 40px mask
    /// across the original scene image, rather than drawing a replacement effect.
    pub fn masked_scene(
        &mut self,
        painter: &egui::Painter,
        rect: egui::Rect,
        name: &str,
        mask_tile: u32,
    ) -> bool {
        let Some(source) = self.scene_sources.get(name) else {
            return false;
        };
        let Some(atlas) = self.original_image.as_ref() else {
            return false;
        };
        if mask_tile == 0 || mask_tile > 11 * (atlas.height() / 40) {
            return false;
        }
        let key = (name.to_owned(), mask_tile);
        let texture = self.scene_masks.entry(key).or_insert_with(|| {
            let mut pixels = source.clone();
            let mask = mask_tile - 1;
            for (x, y, pixel) in pixels.enumerate_pixels_mut() {
                pixel.0[3] = 255
                    - atlas
                        .get_pixel(mask % 11 * 40 + x % 40, mask / 11 * 40 + y % 40)
                        .0[0];
            }
            painter.ctx().load_texture(
                format!("scene {name}:{mask_tile}"),
                ColorImage::from_rgba_unmultiplied(
                    [pixels.width() as usize, pixels.height() as usize],
                    pixels.as_raw(),
                ),
                TextureOptions::NEAREST,
            )
        });
        painter.image(
            texture.id(),
            rect,
            egui::Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
            egui::Color32::WHITE,
        );
        true
    }

    pub fn install(&mut self, ctx: &egui::Context, bytes: &[u8]) -> Result<(), String> {
        let image = image::load_from_memory(bytes)
            .map_err(|e| e.to_string())?
            .to_rgba8();
        self.size = [image.width() as usize, image.height() as usize];
        self.original_image = Some(image.clone());
        self.masked.clear();
        self.foregrounds.clear();
        self.heroes.clear();
        self.hero_hits.clear();
        self.impact = None;
        self.atlas = Some(ctx.load_texture(
            "original sprites",
            ColorImage::from_rgba_unmultiplied(self.size, image.as_raw()),
            TextureOptions::NEAREST,
        ));
        if image.width() < 440 || image.height() < 800 {
            return Ok(());
        }
        for (direction, first) in [("down", 185), ("left", 193), ("right", 201), ("up", 209)] {
            let frames = [first, first + 2, first + 4]
                .map(|tile| masked_texture(ctx, &image, tile, tile + 1));
            self.heroes.insert(direction.into(), frames);
            self.hero_hits.insert(
                direction.into(),
                masked_texture(ctx, &image, first + 6, first + 7),
            );
        }
        // This pair is reversed compared with the hero pairs: mask, then color.
        self.impact = Some(masked_texture(ctx, &image, 184, 183));
        Ok(())
    }

    /// Composite a scripted color cell using the original separate alpha mask.
    ///
    /// Magic apparition cells 166..182 are dither masks, not artwork to display
    /// directly. This cache also supports later transformations without a fixed
    /// list of creature/mask combinations or additional extracted PNG assets.
    pub fn masked_tile(
        &mut self,
        painter: &egui::Painter,
        rect: egui::Rect,
        color_tile: u32,
        mask_tile: u32,
        tint: egui::Color32,
    ) -> bool {
        let Some(image) = &self.original_image else {
            return false;
        };
        let cells = 11 * (image.height() / 40);
        if image.width() < 440
            || color_tile == 0
            || mask_tile == 0
            || color_tile > cells
            || mask_tile > cells
        {
            return false;
        }
        let texture = self
            .masked
            .entry((color_tile, mask_tile))
            .or_insert_with(|| masked_texture(painter.ctx(), image, color_tile, mask_tile));
        painter.image(
            texture.id(),
            rect,
            egui::Rect::from_min_max(egui::pos2(0.0, 0.0), egui::pos2(1.0, 1.0)),
            tint,
        );
        true
    }

    /// Install Chtableb's foreground silhouettes, including items, equipment,
    /// keys, NPCs and enemies. Both atlases use the same cell coordinates.
    pub fn install_background(&mut self, _ctx: &egui::Context, bytes: &[u8]) -> Result<(), String> {
        let masks = image::load_from_memory(bytes)
            .map_err(|error| error.to_string())?
            .to_rgba8();
        if masks.width() < 440 || masks.height() < 40 {
            return Err(
                "Original foreground mask atlas must contain 11 columns of 40px cells".into(),
            );
        }
        self.foreground_masks = Some(masks);
        self.foregrounds.clear();
        Ok(())
    }

    /// Paint the original foreground using its exact Chtableb silhouette. This
    /// removes the atlas's composited floor without treating any artwork color
    /// as transparent. Custom rectangles or unavailable masks use normal tiles.
    pub fn foreground(
        &mut self,
        painter: &egui::Painter,
        rect: egui::Rect,
        sprite: &serde_json::Value,
        tint: egui::Color32,
    ) -> bool {
        let source = if sprite.is_object() {
            sprite["x"]
                .as_u64()
                .zip(sprite["y"].as_u64())
                .zip(sprite["w"].as_u64().zip(sprite["h"].as_u64()))
                .and_then(|((x, y), (w, h))| {
                    Some((
                        u32::try_from(x).ok()?,
                        u32::try_from(y).ok()?,
                        u32::try_from(w).ok()?,
                        u32::try_from(h).ok()?,
                    ))
                })
        } else {
            sprite.as_u64().filter(|tile| *tile > 0).and_then(|tile| {
                let index = u32::try_from(tile - 1).ok()?;
                Some((index % 11 * 40, (index / 11).checked_mul(40)?, 40, 40))
            })
        };
        let Some((x, y, w, h)) = source else {
            return self.tile(painter, rect, sprite, tint);
        };
        let (Some(colors), Some(masks)) = (&self.original_image, &self.foreground_masks) else {
            return self.tile(painter, rect, sprite, tint);
        };
        let valid = w > 0
            && h > 0
            && [x, y, w, h].iter().all(|value| value.is_multiple_of(40))
            && x.checked_add(w).is_some_and(|right| {
                right <= 440 && right <= colors.width() && right <= masks.width()
            })
            && y.checked_add(h)
                .is_some_and(|bottom| bottom <= colors.height() && bottom <= masks.height());
        if !valid {
            return self.tile(painter, rect, sprite, tint);
        }
        let texture = self.foregrounds.entry((x, y, w, h)).or_insert_with(|| {
            let pixels = foreground_pixels(colors, masks, (x, y, w, h))
                .expect("foreground atlas bounds were checked");
            painter.ctx().load_texture(
                format!("original foreground {x}:{y}:{w}:{h}"),
                ColorImage::from_rgba_unmultiplied([w as usize, h as usize], &pixels),
                TextureOptions::NEAREST,
            )
        });
        painter.image(
            texture.id(),
            rect,
            egui::Rect::from_min_max(egui::Pos2::ZERO, egui::pos2(1.0, 1.0)),
            tint,
        );
        true
    }

    /// Paint a transparent original creature while it moves between cells.
    pub fn creature(
        &mut self,
        painter: &egui::Painter,
        rect: egui::Rect,
        sprite: &serde_json::Value,
        tint: egui::Color32,
    ) -> bool {
        self.foreground(painter, rect, sprite, tint)
    }

    /// Select an original stationary animation frame without moving its cell.
    ///
    /// Only 40px, grid-aligned rectangles in the original 11-column atlas are
    /// interpreted. Custom rectangles are left intact so an edited campaign's
    /// artwork cannot accidentally be replaced by an original monster sprite.
    pub fn animated_sprite(sprite: &serde_json::Value, frame: usize) -> serde_json::Value {
        let object = sprite.is_object();
        let tile = if object {
            let Some((x, y, w, h)) = sprite["x"]
                .as_u64()
                .zip(sprite["y"].as_u64())
                .zip(sprite["w"].as_u64().zip(sprite["h"].as_u64()))
                .map(|((x, y), (w, h))| (x, y, w, h))
            else {
                return sprite.clone();
            };
            if w != 40 || h != 40 || !x.is_multiple_of(40) || !y.is_multiple_of(40) || x >= 440 {
                return sprite.clone();
            }
            y / 40 * 11 + x / 40 + 1
        } else if let Some(tile) = sprite.as_u64() {
            tile
        } else {
            return sprite.clone();
        };
        let phase = (frame % 2) as u64;
        let selected = match tile {
            13 | 160 => {
                if phase == 0 {
                    13
                } else {
                    160
                }
            }
            14 | 161 => {
                if phase == 0 {
                    14
                } else {
                    161
                }
            }
            19..=28 | 61..=96 | 133..=158 => ((tile - 1) / 2 * 2 + 1) + phase,
            97..=114 => 97 + (tile - 97) % 9 + phase * 9,
            115..=132 => 115 + (tile - 115) % 9 + phase * 9,
            _ => return sprite.clone(),
        };
        if object {
            let mut result = sprite.clone();
            result["x"] = ((selected - 1) % 11 * 40).into();
            result["y"] = ((selected - 1) / 11 * 40).into();
            result
        } else {
            selected.into()
        }
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

/// The original stair transition's order, generalized to edited floor sizes.
///
/// On an 11x11 floor this matches all 121 bytes at TSW.exe VA 0x489b20: down
/// the left edge, across the bottom, up the right edge, back along the top,
/// then repeat on the inset rectangle until the center is reached.
pub fn stair_wipe_order(width: usize, height: usize) -> Vec<usize> {
    let mut order = Vec::with_capacity(width.saturating_mul(height));
    if width == 0 || height == 0 {
        return order;
    }
    let (mut left, mut top, mut right, mut bottom) = (0, 0, width - 1, height - 1);
    while left <= right && top <= bottom {
        for y in top..=bottom {
            order.push(y * width + left);
        }
        if left == right {
            break;
        }
        for x in left + 1..=right {
            order.push(bottom * width + x);
        }
        if top == bottom {
            break;
        }
        for y in (top..bottom).rev() {
            order.push(y * width + right);
        }
        for x in (left + 1..right).rev() {
            order.push(top * width + x);
        }
        left += 1;
        top += 1;
        right -= 1;
        bottom -= 1;
    }
    order
}

fn masked_texture(
    ctx: &egui::Context,
    image: &image::RgbaImage,
    color_tile: u32,
    mask_tile: u32,
) -> TextureHandle {
    let (color, mask) = (color_tile - 1, mask_tile - 1);
    let mut pixels = Vec::with_capacity(40 * 40 * 4);
    for y in 0..40 {
        for x in 0..40 {
            let mut rgba = image.get_pixel(color % 11 * 40 + x, color / 11 * 40 + y).0;
            rgba[3] = 255 - image.get_pixel(mask % 11 * 40 + x, mask / 11 * 40 + y).0[0];
            pixels.extend_from_slice(&rgba);
        }
    }
    ctx.load_texture(
        format!("original masked sprite {color_tile}:{mask_tile}"),
        ColorImage::from_rgba_unmultiplied([40, 40], &pixels),
        TextureOptions::NEAREST,
    )
}

fn foreground_pixels(
    colors: &image::RgbaImage,
    masks: &image::RgbaImage,
    (x, y, w, h): (u32, u32, u32, u32),
) -> Option<Vec<u8>> {
    if w == 0
        || h == 0
        || x.checked_add(w)
            .is_none_or(|right| right > colors.width() || right > masks.width())
        || y.checked_add(h)
            .is_none_or(|bottom| bottom > colors.height() || bottom > masks.height())
    {
        return None;
    }
    let mut pixels = Vec::with_capacity(w as usize * h as usize * 4);
    for dy in 0..h {
        for dx in 0..w {
            let mut rgba = colors.get_pixel(x + dx, y + dy).0;
            let alpha = 255 - masks.get_pixel(x + dx, y + dy).0[0];
            rgba[3] = (u16::from(rgba[3]) * u16::from(alpha) / 255) as u8;
            pixels.extend_from_slice(&rgba);
        }
    }
    Some(pixels)
}

#[cfg(test)]
mod tests {
    use super::{Art, foreground_pixels, stair_wipe_order};
    use serde_json::json;

    #[test]
    fn foreground_mask_removes_floor_without_removing_matching_artwork_colors() {
        let colors = image::RgbaImage::from_raw(
            2,
            2,
            vec![
                70, 70, 70, 255, 255, 255, 255, 255, 0, 0, 0, 200, 201, 11, 12, 255,
            ],
        )
        .unwrap();
        let masks = image::RgbaImage::from_raw(
            2,
            2,
            vec![
                255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 128, 128, 128, 255,
            ],
        )
        .unwrap();
        assert_eq!(
            foreground_pixels(&colors, &masks, (0, 0, 2, 2)).unwrap(),
            vec![
                70, 70, 70, 0, 255, 255, 255, 255, 0, 0, 0, 200, 201, 11, 12, 127,
            ]
        );
        assert!(foreground_pixels(&colors, &masks, (0, 0, 3, 2)).is_none());
    }

    #[test]
    fn stair_spiral_matches_original_executable_table() {
        // Read-only extraction of VA 0x489b20..0x489b98, rather than an
        // expected value generated by the helper under test.
        let original = [
            0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 111, 112, 113, 114, 115, 116, 117, 118,
            119, 120, 109, 98, 87, 76, 65, 54, 43, 32, 21, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 12, 23,
            34, 45, 56, 67, 78, 89, 100, 101, 102, 103, 104, 105, 106, 107, 108, 97, 86, 75, 64,
            53, 42, 31, 20, 19, 18, 17, 16, 15, 14, 13, 24, 35, 46, 57, 68, 79, 90, 91, 92, 93, 94,
            95, 96, 85, 74, 63, 52, 41, 30, 29, 28, 27, 26, 25, 36, 47, 58, 69, 80, 81, 82, 83, 84,
            73, 62, 51, 40, 39, 38, 37, 48, 59, 70, 71, 72, 61, 50, 49, 60,
        ];
        assert_eq!(stair_wipe_order(11, 11), original);
    }

    #[test]
    fn original_animation_selects_frames_without_replacing_custom_artwork() {
        for (first, second) in [(19, 20), (61, 62), (97, 106), (122, 131), (157, 158)] {
            assert_eq!(Art::animated_sprite(&json!(first), 1), json!(second));
            assert_eq!(Art::animated_sprite(&json!(second), 0), json!(first));
        }
        let dragon = json!({"x":0,"y":440,"w":40,"h":40,"artist":"original"});
        assert_eq!(
            Art::animated_sprite(&dragon, 1),
            json!({"x":360,"y":440,"w":40,"h":40,"artist":"original"})
        );
        let custom = json!({"x":12,"y":12,"w":48,"h":48});
        assert_eq!(Art::animated_sprite(&custom, 1), custom);
    }
}
