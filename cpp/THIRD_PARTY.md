# Attribution and dependency pins

Original game/media: **Oz & Kenichi / Shigemasa Ozawa**, English Windows TSW 1.2.
The EXE embeds two original ending pictures; other media comes from the local
installation. Japanese text is from their **魔法の塔 for Windows Ver1.6a**;
Chinese terminology comes from TSWH5. Original material is not relicensed under
MIT. See [project attribution](../THIRD_PARTY.md) and [catalog sources](locales/README.md).

| Dependency | Pin | Packaged license |
|---|---|---|
| raylib | 5.5, vcpkg revision 1 | `raylib-LICENSE.txt`, `licenses/` |
| miniaudio | 0.11.25 | `miniaudio-LICENSE.txt` |
| stb_image | 2024-07-29, vcpkg revision 1 | `licenses/stb.txt` |
| vcpkg catalog | `b5d1a94fb7f88fd835e360fd23a45a09ceedbf48` | Build tool only |
| TinySoundFont / TinyMidiLoader | `853a0a171759f1ddba0de1442133a75912bbeffa` | `TinySoundFont-LICENSE.txt` |
| Catch2 (tests) | 3.13.0, vcpkg revision 1 | `licenses/catch2.txt` |
| Glaze | 7.2.2 | `licenses/glaze.txt` |
| GeneralUser GS | 2.0.3; `684543d5e5efaef08d02be50dcda8d552478fa60` | `GeneralUser-GS-LICENSE.txt` |

GeneralUser GS is by **S. Christian Collins**; its complete soundfont is embedded
with its license. CMake verifies download hashes; inputs stay in
`build/dependencies/`. Packaging copies static dependency notices from vcpkg's
`share/*/copyright` and hashes packaged files.

Segoe UI, Yu Gothic/MS Gothic and Microsoft YaHei are read from installed Windows
fonts, or CJK uses `TSW_CJK_FONT`. Font files are not redistributed.

Android packages the original GeneralUser GS bank. WebAssembly packages a
Vorbis-compressed q1 `.sfo` derivative of that bank (SHA-256
`0509a47616c426f6bb160c9f3740dea4174448749c6771644c1e6c562c05d8af`),
made with TinySoundFont SFOTool and FFmpeg. Both package the extracted runtime
media as data files. Their dependency notices are staged from [licenses/](licenses/)
alongside the soundfont and game attribution. Optional builder-supplied fonts
must include their redistribution notices. Android can also read system fonts.

The web derivative was generated from the pinned GeneralUser GS download with
SFOTool from the pinned TinySoundFont source and FFmpeg 8.0.1 (`libvorbis`,
quality 1): extract the SF2 sample stream to WAV, encode that WAV to Ogg Vorbis,
then use SFOTool to replace the SF2 sample stream with the Ogg file. The original
SF2 stays the source for desktop and Android.
