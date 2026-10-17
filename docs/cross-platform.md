# Android and WebAssembly

Both builds contain the C++ game without CLI, MCP, planner or test executables.
Android 9+ and mobile browsers share a lower-right D-pad: tap to step and hold to
repeat. Its targets stay at 48 CSS pixels / Android dp independently of the game
artwork. Landscape reserves room beside the game so the pad covers neither the map
nor the stats and inventory. Tap a conversation panel to continue; drag long text
to scroll without advancing. Shops require their explicit choice buttons. Flight
has floor arrows, a checkmark to travel and an X to cancel. Settings → Controls → Touch controls
overrides automatic device detection. Tap-to-walk remains available.

## Build and run

Install Python, CMake, Ninja and vcpkg. Web needs an activated Emscripten SDK
(tested: 5.0.1). Android needs JDK 17, SDK 35, NDK 30.0.14904198 and CMake 4.1.2.
Browser checks need Node.js/npm.
Web font subsetting also needs the pinned fontTools build dependency:

```sh
python -m pip install -r cpp/tools/web-fonts-requirements.txt
```
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

The web player fits the browser viewport without page scrolling. **Menu** at the
upper left opens help, save status, exports and **Full screen**. On wide landscape
screens it becomes a single hamburger button in the left margin. Narrower screens
use a compact top bar. Fullscreen keeps Menu and exports accessible where the
browser supports it. Android renders at native display resolution for consistent
text and touch target sizing.

Outputs: `build/cpp/web/site/`, `build/cpp/web/tower-of-the-sorcerer-web.zip`,
and `build/android/artifacts/`. Debug APKs are signed for local testing.

## Publish on Cloudflare Pages

Build locally first, then upload the **contents** of `build/cpp/web/site/` as a
Pages Direct Upload project. Every build uses the q1 compressed GeneralUser GS
soundfont and shows download progress while its assets load. The web `.data`
file is below Cloudflare Pages' 25 MiB per-file limit.

```sh
python cpp/tools/cross.py web
npx wrangler login
npx wrangler pages project list
npx wrangler pages deploy build/cpp/web/site --project-name YOUR_PROJECT_NAME
```

If you do not already have a Direct Upload project, run
`npx wrangler pages project create` before deploying; it prompts for the name and
production branch. Use your existing or newly created project name in the deploy
command. For later releases, rebuild and run the last command again. Cloudflare
Pages also accepts the generated web zip through the dashboard's drag-and-drop
uploader. See [Cloudflare's Direct Upload guide](https://developers.cloudflare.com/pages/get-started/direct-upload/).

## Saves and media

- Web restores IndexedDB before starting and automatically persists saves.
  **Menu** shows save status; **Export file** downloads saves and companion
  files. Storage belongs to the browser/site address; clearing site data removes it.
  A warning on **Menu** signals persistence trouble. Export temporary
  saves; **Retry storage** in the panel retries writes.
- Android keeps saves in private `files/Savedat/`, surviving restarts and updates.
  Uninstalling or clearing app data removes them. Back closes panels or opens the menu.
- Media comes from your original installation; see [attribution](../THIRD_PARTY.md).
  Optional `build/assets/fonts/body.ttf` and `cjk.ttf` need redistribution notices.
  Android also uses system fonts.

## Browser fonts and settings

Settings has **Game**, **Controls**, **Replay**, and **Language** tabs. Touch controls
and mouse walking live together under Controls. Recording and playback speed live
under Replay; music, game speed and Hero Orb display options live under Game.

The web build supplies Noto Sans CJK automatically. At build time,
`cpp/tools/web_fonts.py` downloads checksum-pinned Japanese and Simplified Chinese
OpenType sources and their SIL Open Font License into `build/dependencies/noto-cjk/`.
It keeps only characters used by the checked-in catalogs, plus ASCII and language
names. Rebuilding after catalog changes regenerates the subsets. An existing
`cjk.ttf` is excluded from the web startup package; Android can still use it.

A roughly 8 KiB subset for native language names loads with the game. The full
Japanese or Chinese subset (roughly 440 KiB each) is a separate file fetched only
when that language is selected, including a saved selection on startup. Both
Chinese catalogs share one face. The game displays English until the font arrives;
failed or timed-out downloads show a Retry button while the game remains usable.
Font bytes and atlases are created on demand and reused for subsequent switches.

Fonts are served from the same site, with content hashes in their filenames.
The generated site includes `_headers` for long-lived font caching on Pages;
other hosts should apply `Cache-Control: public, max-age=31536000, immutable` to
`fonts/*.otf`. Deploy the complete site directory, including `fonts/` and its
license. The generated zip includes them. Runtime font loading does not need a CDN
or an external font service, and font files remain outside `index.data`.
