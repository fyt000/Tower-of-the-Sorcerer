#[cfg(not(target_arch = "wasm32"))]
fn main() -> eframe::Result {
    let args: Vec<String> = std::env::args().collect();
    let option = |name: &str| {
        args.iter()
            .position(|a| a == name)
            .and_then(|i| args.get(i + 1))
            .cloned()
    };
    let campaign = option("--campaign").and_then(|p| std::fs::read_to_string(p).ok());
    let root = option("--assets-root").unwrap_or_else(|| {
        let cwd = std::env::current_dir().unwrap_or_default();
        let executable = std::env::current_exe()
            .ok()
            .and_then(|p| p.parent().map(std::path::Path::to_path_buf));
        if let Some(parent) = executable.filter(|p| p.join("assets").exists()) {
            parent.display().to_string()
        } else if cwd.join("web/assets").exists() {
            cwd.join("web").display().to_string()
        } else {
            std::path::Path::new(env!("CARGO_MANIFEST_DIR"))
                .join("../../web")
                .display()
                .to_string()
        }
    });
    let editor = args.iter().any(|a| a == "--editor");
    let save = option("--save").and_then(|p| std::fs::read_to_string(p).ok());
    let language = option("--language");
    let options = eframe::NativeOptions {
        viewport: eframe::egui::ViewportBuilder::default()
            .with_inner_size([1360.0, 920.0])
            .with_min_inner_size([360.0, 650.0])
            .with_app_id("tos-rust"),
        renderer: eframe::Renderer::Glow,
        ..Default::default()
    };
    eframe::run_native(
        "Tower of the Sorcerer",
        options,
        Box::new(move |cc| {
            let mut app = tos_ui::TowerApp::new(cc, campaign, root, editor);
            if let Some(language) = language {
                app.set_locale(&language);
            }
            if let Some(save) = save {
                app.load_save(&save).map_err(std::io::Error::other)?;
            }
            Ok(Box::new(app))
        }),
    )
}

#[cfg(target_arch = "wasm32")]
fn main() {}
