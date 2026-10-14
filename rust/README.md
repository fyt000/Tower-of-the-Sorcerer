# Tower of the Sorcerer — Rust

## Build and run

Install Rust, Node.js and Python, then run from the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/setup_assets.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
Set-Location rust
npm ci
rustup target add wasm32-unknown-unknown
npm run build
npm run start:native
```

From `rust/`, use `npm start` for the browser at `http://127.0.0.1:8080/`, or
`npm run editor` for the campaign editor. `npm run check` runs tests and Clippy;
`npm run test:browser`, `npm run test:native` and `npm run test:mcp` run
integration checks.

Build output is in `build/rust/`, extracted media in `rust/web/assets/`, and
Node dependencies in `rust/node_modules/` (paths relative to the repository root).
