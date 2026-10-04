//! One Rust presentation implementation for desktop and browser.
mod app;
mod assets;
mod audio;
pub mod editor;
pub mod locales;
mod platform;
pub use app::TowerApp;

#[cfg(target_arch = "wasm32")]
mod web {
    use super::TowerApp;
    use wasm_bindgen::prelude::*;

    #[wasm_bindgen]
    pub struct WebHandle {
        runner: eframe::WebRunner,
    }

    #[wasm_bindgen]
    impl WebHandle {
        #[wasm_bindgen(constructor)]
        pub fn new() -> Self {
            console_error_panic_hook::set_once();
            Self {
                runner: eframe::WebRunner::new(),
            }
        }
        pub async fn start(&self, canvas: web_sys::HtmlCanvasElement) -> Result<(), JsValue> {
            self.runner
                .start(
                    canvas,
                    eframe::WebOptions::default(),
                    Box::new(|cc| Ok(Box::new(TowerApp::new(cc, None, String::new(), false)))),
                )
                .await
        }
        pub fn state_json(&self) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| a.engine.snapshot().to_string())
                .unwrap_or_default()
        }
        pub fn ui_json(&self) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| a.debug_json().to_string())
                .unwrap_or_default()
        }
        pub fn command_json(&self, source: &str) -> Result<String, JsValue> {
            let command =
                serde_json::from_str(source).map_err(|e| JsValue::from_str(&e.to_string()))?;
            let mut app = self
                .runner
                .app_mut::<TowerApp>()
                .ok_or_else(|| JsValue::from_str("Application not ready"))?;
            app.submit(command);
            Ok(app.engine.snapshot().to_string())
        }
        pub fn import_campaign(&self, source: &str) -> Result<(), JsValue> {
            self.runner
                .app_mut::<TowerApp>()
                .ok_or_else(|| JsValue::from_str("Application not ready"))?
                .replace_campaign(source)
                .map_err(|e| JsValue::from_str(&e))
        }
        pub fn load_save(&self, source: &str) -> Result<(), JsValue> {
            let mut app = self
                .runner
                .app_mut::<TowerApp>()
                .ok_or_else(|| JsValue::from_str("Application not ready"))?;
            app.load_save(source).map_err(|e| JsValue::from_str(&e))
        }
        pub fn set_language(&self, locale: &str) {
            if let Some(mut app) = self.runner.app_mut::<TowerApp>() {
                app.set_locale(locale);
            }
        }
        pub fn open_editor(&self) {
            if let Some(mut app) = self.runner.app_mut::<TowerApp>() {
                app.editor_open = true;
            }
        }
        pub fn inspect_json(&self, x: usize, y: usize) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| a.engine.inspect(x, y).to_string())
                .unwrap_or_default()
        }
        pub fn save_json(&self) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| a.engine.save_json())
                .unwrap_or_default()
        }
        pub fn path_json(&self, x: usize, y: usize) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| serde_json::to_string(&a.engine.path_to(x, y)).unwrap())
                .unwrap_or_default()
        }
        pub fn editor_campaign_json(&self) -> String {
            self.runner
                .app_mut::<TowerApp>()
                .map(|a| a.editor_campaign_json())
                .unwrap_or_default()
        }
    }
}
