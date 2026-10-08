# Attribution and dependency pins

Original game and artwork: **Oz & Kenichi / Shigemasa Ozawa**, English Windows
Tower of the Sorcerer 1.2. Maps, dialogue, sprite/scene images, WAV effects and
MIDI tracks are read from the local installation. The replacement embeds the
original form's two ending pictures; external BMP/OZ/MIDI/WAV files keep their
original formats. Original media and generated local distributions are excluded
from Git.

The C++ implementation is separate from the original author's Delphi source.
Its readable translation and probe scripts are in this repository; generated
Ghidra files are marked as decompiler inspection output.

| Dependency | Pin | License shipped in package |
|---|---|---|
| raylib | 5.5, vcpkg port revision 1 | `raylib-LICENSE.txt`; dependency notices under `licenses/` |
| miniaudio | 0.11.25, direct device and WAV decoding | `miniaudio-LICENSE.txt` |
| stb_image | 2024-07-29, vcpkg port revision 1 | `licenses/stb.txt` |
| vcpkg catalog | `b5d1a94fb7f88fd835e360fd23a45a09ceedbf48` | Build tool, not distributed with game |
| TinySoundFont / TinyMidiLoader | `853a0a171759f1ddba0de1442133a75912bbeffa` | `TinySoundFont-LICENSE.txt` |
| Catch2 (test runner only) | 3.13.0, vcpkg port revision 1 | `licenses/catch2.txt` |
| nlohmann/json (replay input/output) | 3.12.0, vcpkg port revision 2 | `licenses/nlohmann-json.txt` |
| GeneralUser GS | 2.0.3; `684543d5e5efaef08d02be50dcda8d552478fa60` | `GeneralUser-GS-LICENSE.txt` |

GeneralUser GS is by **S. Christian Collins**. The package includes the complete
soundfont embedded in the executable and its license. It supplies the GM programs
and drums needed by all 17 original tracks. Dependency source/downloads live under
ignored `build/dependencies/`, and CMake verifies their pinned download hashes.

The raylib fallback archive has SHA-256
`aea98ecf5bc5c5e0b789a76de0083a21a70457050ea4cc2aec7566935f5e258e`.
The TinySoundFont source archive has SHA-256
`76c356df524f71f2a34f67fa0cb2cb946036fe7a65d2930a849569c5e742fa57`.
The nlohmann/json fallback archive has SHA-256
`4b92eb0c06d10683f7447ce9406cb97cd4b453be18d7279320f7b2f025c10187`.
The GeneralUser SF2 has SHA-256
`9575028c7a1f589f5770fccc8cff2734566af40cd26ed836944e9a5152688cfe`.

The packaging script also copies notices for installed static raylib dependencies
from vcpkg's `share/*/copyright` files and records SHA-256 for each packaged file.

The desktop can read Segoe UI Semibold and Bold from the user's installed
Windows fonts through raylib. These font files are not redistributed. If they
are unavailable, the application uses raylib's bundled default font.
