"""One-time local media extraction and open-source Chinese font setup.

No original media is downloaded or redistributed. The licensed font is fetched
from Google's official font repository; original art/music come from your copy.
"""
import argparse
import pathlib
import subprocess
import sys
import urllib.request

ROOT = pathlib.Path(__file__).resolve().parent.parent
FONT_BASE = "https://raw.githubusercontent.com/google/fonts/main/ofl/notosanssc/"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", default=r"D:\Program Files (x86)\Tower of the Sorcerer")
    parser.add_argument("--font-only", action="store_true")
    parser.add_argument("--skip-font", action="store_true")
    args = parser.parse_args()
    if not args.font_only:
        subprocess.run([sys.executable, str(ROOT / "tools/extract_original.py"), "--source", args.source], check=True)
    if not args.skip_font:
        fonts = ROOT / "rust/web/fonts"
        fonts.mkdir(parents=True, exist_ok=True)
        for name, remote in [("NotoSansSC.ttf", "NotoSansSC%5Bwght%5D.ttf"), ("Noto-Sans-SC-LICENSE.txt", "OFL.txt")]:
            target = fonts / name
            if not target.exists():
                print(f"Downloading licensed Chinese font resource: {name}")
                with urllib.request.urlopen(FONT_BASE + remote, timeout=60) as response:
                    target.write_bytes(response.read())
    print("Local assets ready. Extracted images/audio and the downloaded font stay outside Git.")


if __name__ == "__main__":
    main()
