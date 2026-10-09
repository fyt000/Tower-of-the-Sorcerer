"""Format Delphi sources and include fragments with pinned pasfmt 0.7.0."""
from pathlib import Path
import argparse
import hashlib
import os
import shutil
import subprocess
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]
VERSION = "0.7.0"
ARCHIVE_NAME = f"pasfmt-{VERSION}-x86_64-pc-windows-msvc"
ARCHIVE_SHA256 = "58703093b194e50d87a997bdf26743a0e12127a70c4b5420d46b32c0c7fc098c"
CONFIG = ROOT / "delphi/pasfmt.toml"
STATEMENT_INCLUDES = {
    "InitializeCycle.inc", "GraphicsLayout.inc", "GraphicsHints.inc", "FormChecks.inc",
    "AboutLayout.inc", "DataHolderLayout.inc", "FontLayout.inc", "StartupHidden.inc",
    "RankingLayout.inc",
}


def formatter():
    installed = shutil.which("pasfmt")
    if installed:
        version = subprocess.check_output([installed, "--version"], text=True).strip()
        if version != f"pasfmt {VERSION}":
            raise ValueError(f"Expected pasfmt {VERSION}; found {version}")
        return Path(installed)
    if os.name != "nt":
        raise FileNotFoundError(f"Install pasfmt {VERSION} and add it to PATH")
    directory = ROOT / "build/tools/pasfmt"
    executable = directory / ARCHIVE_NAME / "pasfmt.exe"
    if not executable.exists():
        directory.mkdir(parents=True, exist_ok=True)
        archive = directory / f"pasfmt-{VERSION}.zip"
        if not archive.exists():
            url = ("https://github.com/integrated-application-development/pasfmt/"
                   f"releases/download/v{VERSION}/{ARCHIVE_NAME}.zip")
            urllib.request.urlretrieve(url, archive)
        if hashlib.sha256(archive.read_bytes()).hexdigest() != ARCHIVE_SHA256:
            raise ValueError("pasfmt archive checksum differs from the pinned release")
        with zipfile.ZipFile(archive) as package:
            for entry in package.infolist():
                if not (directory / entry.filename).resolve().is_relative_to(directory.resolve()):
                    raise ValueError("pasfmt archive contains a path outside its install directory")
            package.extractall(directory)
    return executable


def format_source(name, text, executable=None):
    if not text.strip():
        return text
    if name.endswith(".inc"):
        # Includes contain fields, statements, or routines rather than complete units.
        # Supply their enclosing syntax so indentation matches the inclusion site.
        start, stop = "{FORMAT_BODY_BEGIN}", "{FORMAT_BODY_END}"
        if name == "HeroFields.inc":
            prefix, suffix = "unit Fragment; interface type THero = record\n", "\nend; implementation end."
        elif name == "FormDeclarations.inc":
            prefix, suffix = "unit Fragment; interface type\n", "\nimplementation end."
        elif name in STATEMENT_INCLUDES:
            prefix, suffix = "procedure Fragment; begin\n", "\nend;"
        else:
            prefix, suffix = "unit Fragment; interface implementation\n", "\nend."
        source = prefix + start + "\n" + text + "\n" + stop + suffix
    else:
        source = text
    result = subprocess.run(
        [str(executable or formatter()), "--config-file", str(CONFIG), "--mode", "stdout"],
        input=source.encode("utf-8"), capture_output=True, check=True,
    ).stdout.decode("utf-8")
    if name.endswith(".inc"):
        result = result.split(start, 1)[1].split(stop, 1)[0]
        # Remove the marker lines, retaining the fragment's indentation.
        result = result.split("\n", 1)[1].rstrip() + "\n"
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    executable = formatter()
    files = sorted(path for path in (ROOT / "delphi").rglob("*")
                   if path.suffix.lower() in (".pas", ".dpr", ".inc"))
    changed = []
    for path in files:
        source = path.read_text(encoding="utf-8")
        formatted = format_source(path.name, source, executable)
        if source != formatted:
            changed.append(str(path.relative_to(ROOT)))
            if not args.check:
                path.write_text(formatted, encoding="utf-8", newline="\n")
    if args.check and changed:
        raise SystemExit("Pascal formatting differs: " + ", ".join(changed))
    print(f"pasfmt {VERSION}: {len(files)} Pascal files checked; {len(changed)} changed")


if __name__ == "__main__":
    main()
