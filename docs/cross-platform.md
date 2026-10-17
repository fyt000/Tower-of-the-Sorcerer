# Android and WebAssembly

Both builds contain the C++ game without CLI, MCP, planner or test executables.
Android 9+ and mobile browsers share a D-pad: tap to step, hold to repeat, OK to
continue dialogue or travel in Flight. Options → Touch controls overrides automatic
device detection. Tap-to-walk remains available. Landscape gives larger controls.

## Build and run

Install Python, CMake, Ninja and vcpkg. Web needs an activated Emscripten SDK
(tested: 5.0.1). Android needs JDK 17, SDK 35, NDK 30.0.14904198 and CMake 4.1.2.
Browser checks need Node.js/npm.
Set `VCPKG_ROOT`, `EMSDK` for web, and `JAVA_HOME`/`ANDROID_HOME` for Android;
the script also accepts paths as arguments. Run from the repository root:

```sh
python cpp/tools/cross.py assets --source "C:/path/to/original/game" --install
python cpp/tools/cross.py web
python cpp/tools/cross.py serve
python cpp/tools/cross.py android
python cpp/tools/cross.py android --abi x86_64
python cpp/tools/cross.py check-web --install
```

Open <http://127.0.0.1:8000> after `serve`. Use `serve --host 0.0.0.0` to test
from a phone on your network. Each subcommand has `--help`, including SDK paths,
custom assets, unsigned release APKs and the Windows JDK socket workaround.

Outputs: `build/cpp/web/site/`, `build/cpp/web/tower-of-the-sorcerer-web.zip`,
and `build/android/artifacts/`. Debug APKs are signed for local testing.

## Saves and media

- Web restores IndexedDB before starting and automatically persists saves. Wait
  for **Saved in this browser**. **Export file** downloads saves and companion
  files. Storage belongs to the browser/site address; clearing site data removes it.
  If persistence fails, export temporary saves; **Retry storage** retries writes.
- Android keeps saves in private `files/Savedat/`, surviving restarts and updates.
  Uninstalling or clearing app data removes them. Back closes panels or opens the menu.
- Media comes from your original installation; see [attribution](../THIRD_PARTY.md).
  Optional `build/assets/fonts/body.ttf` and `cjk.ttf` need redistribution notices.
  CJK text in web needs the latter; Android also uses system fonts.
