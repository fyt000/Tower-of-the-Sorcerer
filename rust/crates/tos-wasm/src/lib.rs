use tos_core::Engine;
use wasm_bindgen::prelude::*;

/// The browser uses exactly the same deterministic engine as the native CLI.
#[wasm_bindgen]
pub struct Game {
    engine: Engine,
}

fn js_error(error: impl ToString) -> JsValue {
    JsValue::from_str(&error.to_string())
}

#[wasm_bindgen]
impl Game {
    #[wasm_bindgen(constructor)]
    pub fn new(campaign_json: &str, save_json: Option<String>) -> Result<Game, JsValue> {
        let mut engine = Engine::from_json(campaign_json).map_err(js_error)?;
        if let Some(save) = save_json {
            engine.load_json(&save).map_err(js_error)?;
        }
        Ok(Self { engine })
    }

    pub fn state_json(&self) -> String {
        self.engine.snapshot().to_string()
    }

    pub fn command_json(&mut self, command: &str) -> Result<String, JsValue> {
        self.engine.command_json(command).map_err(js_error)?;
        Ok(self.state_json())
    }

    pub fn inspect_json(&self, x: usize, y: usize) -> String {
        self.engine.inspect(x, y).to_string()
    }

    pub fn path_json(&self, x: usize, y: usize) -> String {
        serde_json::to_string(&self.engine.path_to(x, y)).expect("route serialization")
    }

    pub fn save_json(&self) -> String {
        self.engine.save_json()
    }

    pub fn load_json(&mut self, save: &str) -> Result<String, JsValue> {
        self.engine.load_json(save).map_err(js_error)?;
        Ok(self.state_json())
    }
}
