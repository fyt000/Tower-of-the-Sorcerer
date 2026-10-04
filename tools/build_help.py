"""Render the bilingual manual as standalone static HTML; no game build needed."""

import argparse
import html
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PAGES = {"en": "help.html", "zh-CN": "help.zh-CN.html"}


def render(manual: dict, language: str) -> str:
    labels = manual["labels"][language]

    def t(value):
        return html.escape(value[language] if isinstance(value, dict) else value, quote=True)

    def sprite(name):
        art = manual["sprites"][name]
        x, y = art.get("x", 0), art.get("y", 0)
        width, height = art["width"], art["height"]
        return (f'<span class="sprite" aria-hidden="true" style="--sprite-x: {-x}px; '
                f'--sprite-y: {-y}px; --sheet-width: {width}px; --sheet-height: {height}px">'
                f'<img src="{t(art["source"])}" width="{width}" height="{height}" alt=""></span>')

    def cell(value):
        if isinstance(value, dict) and "text" in value:
            return f'<span class="icon-label">{sprite(value["sprite"])}<span>{t(value["text"])}</span></span>'
        return t(value)

    def expression(tokens):
        parts = []
        for token in tokens:
            if "term" in token:
                parts.append(f'<span class="term {t(token.get("side", "neutral"))}">{t(token["term"])}</span>')
            elif "op" in token:
                parts.append(f'<span class="operator">{t(token["op"])}</span>')
            elif "fraction" in token:
                fraction = token["fraction"]
                parts.append(f'<span class="fraction"><span class="numerator">{expression(fraction["top"])}</span>'
                             f'<span class="denominator">{expression(fraction["bottom"])}</span></span>')
            elif "floor" in token:
                parts.append(f'<span class="floor-expression"><span class="floor-bracket">⌊</span>'
                             f'{expression(token["floor"])}<span class="floor-bracket">⌋</span></span>')
            else:
                raise ValueError(f"Unknown formula token: {token}")
        return "".join(parts)

    def blocks(entries):
        result = []
        for entry in entries:
            kind = entry["type"]
            if kind == "p":
                result.append(f'<p>{t(entry["text"])}</p>')
            elif kind == "note":
                result.append(f'<aside class="note"><strong>{t(entry["title"])}</strong><p>{t(entry["text"])}</p></aside>')
            elif kind in {"ul", "ol"}:
                items = "".join(f"<li>{t(item)}</li>" for item in entry["items"])
                result.append(f"<{kind}>{items}</{kind}>")
            elif kind == "table":
                headers = "".join(f'<th scope="col">{t(cell)}</th>' for cell in entry["headers"])
                rows = "".join("<tr>" + "".join(f'<th scope="row">{cell(value)}</th>' if i == 0
                              else f"<td>{cell(value)}</td>" for i, value in enumerate(row)) + "</tr>"
                              for row in entry["rows"])
                result.append(f'<div class="table-scroll" role="region" aria-label="{t(entry["caption"])}" tabindex="0"><table><caption>{t(entry["caption"])}</caption><thead><tr>{headers}</tr></thead><tbody>{rows}</tbody></table></div>')
            elif kind == "details":
                result.append(f'<details><summary>{t(entry["summary"])}</summary><div class="disclosure">{blocks(entry["blocks"])}</div></details>')
            elif kind == "item":
                result.append(f'<article class="item" id="{t(entry["id"])}"><h3 class="icon-label">'
                              f'{sprite(entry["sprite"])}<span>{t(entry["title"])}</span></h3>{blocks(entry["blocks"])}</article>')
            elif kind == "formulas":
                cards = "".join(f'<article class="formula-card"><h3>{t(card["title"])}</h3>'
                                f'<div class="equation" role="math" aria-label="{t(card["accessible"])}">'
                                f'{expression(card["expression"])}</div><p class="formula-caption">{t(card["caption"])}</p></article>'
                                for card in entry["cards"])
                result.append(f'<div class="formula-set"><p class="formula-legend">{t(entry["legend"])}</p>{cards}</div>')
            elif kind == "example":
                stats = "".join(f'<div class="example-stats"><h4 class="icon-label">{sprite(side["sprite"])}'
                                f'<span>{t(side["title"])}</span></h4><p>{t(side["stats"])}</p></div>' for side in entry["sides"])
                steps = "".join(f'<li><span>{t(step["label"])}</span><strong>{t(step["calculation"])}</strong></li>'
                                for step in entry["steps"])
                result.append(f'<aside class="worked-example"><h3>{t(entry["title"])}</h3>'
                              f'<div class="example-sides">{stats}</div><ol class="example-steps">{steps}</ol>'
                              f'<p class="example-result">{t(entry["result"])}</p></aside>')
            elif kind == "characters":
                characters = "".join(f'<details class="character" name="character-introductions" id="character-{t(character["id"])}">'
                                     f'<summary><span class="portrait">{sprite(character["sprite"])}</span>'
                                     f'<span class="character-name">{t(character["name"])}</span>'
                                     f'<span class="character-action">{t(entry["action"])}</span></summary>'
                                     f'<blockquote>{t(character["text"])}</blockquote></details>'
                                     for character in entry["entries"])
                result.append(f'<div class="character-gallery">{characters}</div>')
            else:
                raise ValueError(f"Unknown manual block: {kind}")
        return "\n".join(result)

    sections = manual["sections"]
    navigation = "\n".join(f'<li><a href="#{t(section["id"])}"><span>{i:02}</span>{t(section["title"])}</a></li>'
                           for i, section in enumerate(sections, 1))
    chapters = "\n".join(f'<section id="{t(section["id"])}" aria-labelledby="{t(section["id"])}-title">'
                         f'<p class="chapter">{t(labels["chapter"])} {i:02}</p>'
                         f'<h2 id="{t(section["id"])}-title">{t(section["title"])}</h2>'
                         f'{blocks(section["blocks"])}</section>'
                         for i, section in enumerate(sections, 1))
    language_links = "\n".join(f'<a href="{filename}" lang="{code}" hreflang="{code}"'
                               + (' aria-current="page"' if code == language else '')
                               + f'>{t(manual["labels"][code]["language"])}</a>'
                               for code, filename in PAGES.items())
    return f'''<!doctype html>
<!-- Generated by tools/build_help.py from data/help/manual.json. -->
<html lang="{language}">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="description" content="{t(labels['description'])}">
  <meta name="theme-color" content="#0b101a">
  <title>{t(labels['title'])} · {t(labels['manual'])}</title>
  <link rel="stylesheet" href="help.css">
  <link rel="alternate" hreflang="en" href="help.html">
  <link rel="alternate" hreflang="zh-CN" href="help.zh-CN.html">
</head>
<body>
  <a class="skip-link" href="#manual">{t(labels['skip'])}</a>
  <header class="masthead">
    <a class="wordmark" href="#top">{sprite('hero')}<span>TOWER OF THE SORCERER<small>{t(labels['manual'])}</small></span></a>
    <nav class="languages" aria-label="{t(labels['language_nav'])}">{language_links}</nav>
  </header>
  <div class="layout" id="top">
    <nav class="contents" aria-label="{t(labels['contents'])}">
      <p class="eyebrow">{t(labels['contents'])}</p>
      <ol>{navigation}</ol>
      <a class="game-link" href="index.html" target="_blank" rel="noopener">{t(labels['game'])} ↗</a>
    </nav>
    <main id="manual">
      <div class="cover">
        <p class="eyebrow">{t(labels['edition'])}</p>
        <h1>{t(labels['title'])}</h1>
        <p class="subtitle">{t(labels['manual'])}</p>
        <p class="lead">{t(labels['intro'])}</p>
        <div class="cover-art" aria-hidden="true">{sprite('hero-orb')}{sprite('wisdom-orb')}{sprite('flight-orb')}</div>
        <div class="cover-rule"><span>01 — 50</span><span>{t(labels['tagline'])}</span></div>
      </div>
      {chapters}
      <footer>
        <p>{t(labels['attribution'])}</p>
        <p>{t(labels['footer'])}</p>
        <a href="#top">{t(labels['top'])} ↑</a>
      </footer>
    </main>
  </div>
</body>
</html>
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="Verify tracked HTML matches its source without writing")
    args = parser.parse_args()
    manual = json.loads((ROOT / "data/help/manual.json").read_text(encoding="utf-8"))
    for language, filename in PAGES.items():
        output = ROOT / "web" / filename
        rendered = render(manual, language)
        if args.check:
            if not output.exists() or output.read_text(encoding="utf-8") != rendered:
                raise SystemExit(f"Stale static help: {output}; run python tools/build_help.py")
        else:
            output.write_text(rendered, encoding="utf-8", newline="\n")
        print(f"{'Verified' if args.check else 'Generated'} {output}")


if __name__ == "__main__":
    main()
