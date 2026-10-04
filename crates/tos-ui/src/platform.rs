//! The small platform boundary: bytes, persistence, and file export.
use std::sync::mpsc::Sender;

pub fn load(
    path: &str,
    root: &str,
    sender: Sender<(String, Result<Vec<u8>, String>)>,
    ctx: eframe::egui::Context,
) {
    #[cfg(not(target_arch = "wasm32"))]
    {
        let result =
            std::fs::read(std::path::Path::new(root).join(path)).map_err(|e| e.to_string());
        let _ = sender.send((path.into(), result));
        ctx.request_repaint();
    }
    #[cfg(target_arch = "wasm32")]
    {
        let _ = root;
        let name = path.to_string();
        ehttp::fetch(ehttp::Request::get(path), move |result| {
            let result = result.and_then(|r| {
                if r.ok {
                    Ok(r.bytes)
                } else {
                    Err(format!("HTTP {}", r.status))
                }
            });
            let _ = sender.send((name, result));
            ctx.request_repaint();
        });
    }
}

pub fn read_drop(
    file: eframe::egui::DroppedFileHandle,
    sender: Sender<(String, Result<Vec<u8>, String>)>,
    ctx: eframe::egui::Context,
) {
    let name = format!("drop:{}", file.path().display());
    #[cfg(not(target_arch = "wasm32"))]
    {
        let result = file.bytes();
        let _ = sender.send((name, result));
        ctx.request_repaint();
    }
    #[cfg(target_arch = "wasm32")]
    wasm_bindgen_futures::spawn_local(async move {
        let result = file.bytes_async().await;
        let _ = sender.send((name, result));
        ctx.request_repaint();
    });
}

#[cfg(not(target_arch = "wasm32"))]
fn storage_dir() -> std::path::PathBuf {
    std::env::var_os("TOS_STORAGE_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| {
            std::env::var_os("APPDATA")
                .or_else(|| std::env::var_os("XDG_DATA_HOME"))
                .or_else(|| std::env::var_os("HOME"))
                .map(std::path::PathBuf::from)
                .unwrap_or_else(|| ".".into())
                .join("tos-rust")
        })
}

pub fn read(key: &str) -> Option<String> {
    #[cfg(target_arch = "wasm32")]
    {
        web_sys::window()?
            .local_storage()
            .ok()??
            .get_item(key)
            .ok()?
    }
    #[cfg(not(target_arch = "wasm32"))]
    {
        std::fs::read_to_string(storage_dir().join(format!("{}.json", key.replace(':', "_")))).ok()
    }
}

pub fn write(key: &str, value: &str) -> Result<(), String> {
    #[cfg(target_arch = "wasm32")]
    {
        let storage = web_sys::window()
            .and_then(|w| w.local_storage().ok().flatten())
            .ok_or("Browser storage unavailable")?;
        storage
            .set_item(key, value)
            .map_err(|e| format!("Storage: {e:?}"))
    }
    #[cfg(not(target_arch = "wasm32"))]
    {
        let folder = storage_dir();
        std::fs::create_dir_all(&folder).map_err(|e| e.to_string())?;
        let path = folder.join(format!("{}.json", key.replace(':', "_")));
        let temporary = path.with_extension("tmp");
        std::fs::write(&temporary, value).map_err(|e| e.to_string())?;
        std::fs::rename(temporary, path).map_err(|e| e.to_string())
    }
}

pub fn export(name: &str, data: &str) -> Result<String, String> {
    #[cfg(not(target_arch = "wasm32"))]
    {
        let path = std::env::current_dir()
            .map_err(|e| e.to_string())?
            .join(name);
        std::fs::write(&path, data).map_err(|e| e.to_string())?;
        Ok(path.display().to_string())
    }
    #[cfg(target_arch = "wasm32")]
    {
        use wasm_bindgen::JsCast;
        let document = web_sys::window()
            .and_then(|w| w.document())
            .ok_or("No document")?;
        let parts = js_sys::Array::new();
        parts.push(&wasm_bindgen::JsValue::from_str(data));
        let properties = web_sys::BlobPropertyBag::new();
        properties.set_type("application/json");
        let blob = web_sys::Blob::new_with_str_sequence_and_options(&parts, &properties)
            .map_err(|e| format!("{e:?}"))?;
        let url = web_sys::Url::create_object_url_with_blob(&blob).map_err(|e| format!("{e:?}"))?;
        let anchor = document
            .create_element("a")
            .map_err(|e| format!("{e:?}"))?
            .dyn_into::<web_sys::HtmlAnchorElement>()
            .map_err(|e| format!("{e:?}"))?;
        anchor.set_href(&url);
        anchor.set_download(name);
        anchor.click();
        let _ = web_sys::Url::revoke_object_url(&url);
        Ok(name.into())
    }
}
