# Standalone help and source evidence

The help is a separate static document, like the original Windows help window.
Open [English](../web/help.html) or [Simplified Chinese](../web/help.zh-CN.html)
directly in a browser. With `npm start` running, the corresponding URLs are
`http://127.0.0.1:8080/help.html` and
`http://127.0.0.1:8080/help.zh-CN.html`. The existing Rust static server serves
these files without a new route or a WebAssembly rebuild.

Each page has a contents list and a language link. Walkthrough, acquisition
hints and later-area descriptions use closed HTML `details` disclosures.
The original hero, enemy and item sprites come from the existing local asset
atlas. Click a character portrait to expand its introduction; native HTML
`details` also supports keyboard operation without JavaScript. The background
uses the original opening tower artwork with the remake's dark blue and gold
palette. Combat uses separate formula cards, a stacked fraction for retaliation
count, a symbol legend, and a worked example.

There are no remote assets, game/storage calls or JavaScript dependencies. The
page loads the original images and bundled fonts from adjacent `assets/` and
`fonts/` folders. Deploy or copy the complete `web/` directory for offline art;
the text and CSS remain readable without the optional images/fonts. A fresh
clone obtains the ignored original media through the existing asset setup tool.
The optional “Open the game” link opens `index.html` in a separate tab. The help
does not change game UI, dictionaries or campaign data. The native packaging
helper does not yet copy this help.

## Content and provenance

The source is the user's English **Tower of the Sorcerer for Windows 1.2**
installation at `D:\Program Files (x86)\Tower of the Sorcerer`:

| File | Bytes | SHA-256 |
| --- | ---: | --- |
| `TSW.txt` | 10547 | `53bf64bc269815ce051cb26f9a5737b978167ce79cd3361017931dc884a9b31e` |
| `Tsw.hlp` | 222052 | `1daecbe601c76b7db4e280ec161adfe2874e680bcc6344f57c2ddaea431270f0` |
| `Tsw.cnt` | 463 | `9f5448c43b4daf3583e3ba737bd5589558facd98a41865f71623d71569c98055` |

`data/help/original.json` preserves the text manual, help contents, file
checksums and **33 nonempty help topics**, including the character hotspots.
Original spelling and wording are retained in that evidence file.
Images, screen hotspots, formatting and executable WinHelp macros are omitted.

`data/help/manual.json` is the editable, paired English/Simplified Chinese
adaptation. It covers the introduction, current controls, status,
ordinary combat, strategy, seven special items, fairies, the first-area route,
five regions and character introductions. Both originals introduce only seven
of the fifteen special items; this page keeps that scope. It is an adaptation
of selected help material, rather than a complete replica of WinHelp.
Its sprite coordinates were checked against `web/assets/manifest.json` and the
current campaign definitions. Portraits use the original 40-pixel atlas cells;
item/status icons reuse the same artwork. No original media is newly committed.

The player-facing handbook describes the current game directly. Adaptation
credits and the remake's additions are mentioned only in the footer; chapter
source references remain in the authored data and this evidence documentation.
Obsolete Windows setup, the old save gate and fairy score/rank descriptions are
retained in `original.json`, rather than presented as current instructions.
The Warp Staff uses the deterministic mirror rule established in
[mechanics.md](mechanics.md); its charge is spent even if the destination is
blocked. The middle key color is normalized to blue from the help's “purple”,
matching `TSW.txt` and the game dictionary. Chinese entity names match the
existing Simplified Chinese game labels.

Original help remains the work of **Oz & Kenichi**, outside the remake's MIT
license. The page includes this attribution. The original contact/distribution
topic remains in the source evidence; the adapted player handbook does not
promote the old contact addresses as current support channels.

## Regeneration

To edit the handbook, change the paired strings in `data/help/manual.json`, then:

```powershell
python tools/build_help.py
python tools/build_help.py --check
```

This uses Python's standard library and writes only `web/help.html` and
`web/help.zh-CN.html`. `web/help.css` is handwritten. Generated HTML is tracked
so normal deployment of `web/` includes help without requiring this generator.

To reproduce the raw help extraction, use a working
[helpdeco](https://github.com/joncampbell123/helpdeco) executable to export the
installed `Tsw.hlp` in lookalike RTF mode (`-r`); run it in a separate output
directory so it writes no files into the installation. Then:

```powershell
python tools/extract_help.py --source "D:\Program Files (x86)\Tower of the Sorcerer" --hlp-rtf "PATH\TO\Tsw.rtf"
# Alternatively, let the extractor use an isolated temporary directory:
python tools/extract_help.py --source "D:\Program Files (x86)\Tower of the Sorcerer" --helpdeco "PATH\TO\helpdeco.exe"
```

The local extraction used the `joncampbell123/helpdeco` 2.1.3 fork, with small
Windows build adaptations in ignored scratch files. Its RTF export completed
with exit code 0. No decompiler binary or source is included in the remake.
The RTF reader is scoped to the visible-text subset of this English help,
skips nontext destinations, rejects unbalanced/incomplete input and checks for
the final contact topic. Extraction does not overwrite the authored translation
or alter the source installation, campaign, engine or game locales.
