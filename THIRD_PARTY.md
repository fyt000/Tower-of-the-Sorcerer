# Attribution

The C++ game uses raylib, miniaudio, stb_image, TinySoundFont/TinyMidiLoader,
nlohmann/json for replay files and GeneralUser GS. [Its dependency notes](cpp/THIRD_PARTY.md) record versions,
hashes and packaged licenses. The original-media loader and embedded ending
pictures use the same original-game attribution below.

**Tower of the Sorcerer for Windows 1.2**, freeware by Oz & Kenichi, published by Shigemasa Ozawa. Original sprites, sounds, music, maps, monster constants, and dialogue were extracted from the installation supplied by the user. The original `Readme.txt` names the copyright holders and includes original distribution conditions. Extracted media are retained for this local remake and are not relicensed under MIT.

**tswKai**, by Z-H-Sun and contributors, [GitHub](https://github.com/Z-H-Sun/tswKai), MIT licensed. Its reverse-engineering research was used to locate tables and interpret original executable behavior. The Rust engine is a new implementation. Original executable evidence and source links are recorded in the project documentation.

**DM Sans** and **Cormorant Garamond** fonts are bundled for offline presentation under the SIL Open Font License. See the font license files in `rust/web/fonts/`.

**Noto Sans SC**, from Google's official fonts repository, supplies Simplified Chinese glyphs under the SIL Open Font License. `tools/setup_assets.py` downloads it once to the ignored local `rust/web/fonts/NotoSansSC.ttf`; its license is retained in `rust/web/fonts/Noto-Sans-SC-LICENSE.txt`. Extracted image and audio files are also ignored and reproduced from the user's original installation.

Rust and Node dependencies are resolved by `rust/Cargo.lock` and `rust/package-lock.json` and retain their upstream licenses. `wasm-bindgen` is MIT/Apache-2.0; Playwright is Apache-2.0. The binding generator and test browser are development tools.
