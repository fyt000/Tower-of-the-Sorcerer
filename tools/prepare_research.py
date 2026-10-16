"""Prepare ignored research data; optionally run the Ghidra export pipeline.

Ordinary C++ builds/tests do not require this cache. Existing editable campaign
and interaction data are preserved. Ghidra runs are explicit and use a new local
project, so they never mutate an existing analyst project.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

from recovery_evidence import ROOT, ORIGINAL_HASH, digest

DATA_FILES = (
    "data/original-map-bytes.bin", "data/original-dialogue.json",
    "data/original-enemies.json", "data/events.json", "data/interactions.json",
    "data/campaign.json", "build/research/decompilation/presentation/ui-manifest.json",
)
EXPORT_FILES = (
    "build/research/decompilation/decompiled/00442c38_FUN_00442c38.c",
    "build/research/decompilation/decompiled/00449e18_FUN_00449e18.c",
    "build/research/decompilation/presentation/decompiled/0043416c_TAboutBox_formactivate.c",
    "build/research/decompilation/whole-program/decompiled/00455cb8.c",
    "build/research/decompilation/whole-program/decompiled/00484f48.c",
    "build/research/decompilation/whole-program/decompiled/0047d4a4.c",
    "build/research/decompilation/whole-program/decompiled/00454de8.c",
    "build/research/decompilation/whole-program/decompiled/export-manifest.json",
    "build/research/decompilation/whole-program/discovery-snapshot.json",
    "build/research/decompilation/whole-program/analysis-snapshot.json",
    "build/research/decompilation/whole-program/structural-inventory.json",
    "build/research/decompilation/whole-program/ledger.json",
    "build/research/decompilation/presentation/effect-inventory.json",
)


def require_cache(*, decompile=False, root=ROOT):
    required = ("build/research/TSW.exe",) + DATA_FILES + (EXPORT_FILES if decompile else ())
    missing = [name for name in required if not (root / name).is_file()]
    if missing:
        command = "python tools/prepare_research.py --source ORIGINAL_GAME_DIRECTORY"
        if decompile:
            command += " --decompile --ghidra GHIDRA_DIRECTORY"
        raise ValueError("Local research cache is incomplete:\n  " + "\n  ".join(missing) +
                         "\nPrepare it with: " + command)
    if digest(root / "build/research/TSW.exe") != ORIGINAL_HASH:
        raise ValueError("Local TSW.exe is not the supported English 1.2 executable")


def run(*command):
    print("Running " + " ".join(map(str, command)), flush=True)
    environment = os.environ.copy()
    # Every legacy probe must use the executable selected by --source, including
    # on hosts with a different installation path or an inherited override.
    environment["TOS_ORIGINAL_EXE"] = str(ROOT / "build/research/TSW.exe")
    subprocess.run([str(part) for part in command], cwd=ROOT, env=environment, check=True)


def python(script, *arguments):
    run(sys.executable, ROOT / script, *arguments)


def prepare_data(source):
    original = source / "TSW.exe"
    if not original.is_file() or digest(original) != ORIGINAL_HASH:
        raise ValueError("--source must contain the supported English TSW.exe and game assets")
    local = ROOT / "build/research/TSW.exe"
    local.parent.mkdir(parents=True, exist_ok=True)
    if local.resolve() != original.resolve():
        shutil.copy2(original, local)
    had_campaign = (ROOT / "data/campaign.json").exists()
    python("tools/extract_original.py", "--source", source)
    python("tools/extract_original_events.py")
    # First extraction has no event file on a clean checkout. Assemble the final
    # campaign only after event recovery; preserve any existing editable fixture.
    if not had_campaign:
        python("tools/extract_original.py", "--source", source, "--regenerate-campaign")
    python("tools/extract_original_ui.py", "--exe", local)
    python("cpp/tools/extract_ui.py", "--exe", local)


def decompile(ghidra):
    launcher = ghidra / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    if not launcher.is_file():
        raise ValueError("--ghidra must name a Ghidra installation with support/analyzeHeadless")
    original = ROOT / "build/research/TSW.exe"
    gameplay = ROOT / "build/research/decompilation/decompiled"
    presentation = ROOT / "build/research/decompilation/presentation"
    whole = ROOT / "build/research/decompilation/whole-program"
    for folder in (gameplay, presentation / "decompiled", whole):
        folder.mkdir(parents=True, exist_ok=True)
    python("tools/fetch_idr_recognition.py")
    # A unique persistent directory preserves failed runs for inspection.
    project = Path(tempfile.mkdtemp(prefix="ghidra-", dir=ROOT / "build/research"))
    common = (launcher, project, "recovery", "-scriptPath", ROOT / "tools/ghidra")
    run(*common, "-import", original,
        "-postScript", "ExportOriginal.java", gameplay,
        "-postScript", "RecoverArrival.java", gameplay / "0046cb1c_arrival_recovered.c",
        "-postScript", "RecoverCallbacks.java", gameplay,
        "-postScript", "RecoverSaves.java", gameplay,
        "-postScript", "RecoverPresentation.java", presentation / "published-methods.tsv",
        presentation / "decompiled", original,
        "-postScript", "RecoverUiRuntime.java", presentation / "decompiled",
        "-postScript", "InventoryWholeProgram.java", whole / "discovery-snapshot.json")
    python("tools/review_original_presentation.py")
    # Structural discovery and recovered functions can expose further roots.
    # Repeat until the root list stabilizes; never declare an incomplete run good.
    previous_roots = None
    for attempt in range(6):
        python("tools/account_original_program.py")
        roots = (whole / "roots.tsv").read_bytes()
        run(*common, "-process", "TSW.exe", "-noanalysis",
            "-postScript", "RecoverWholeProgram.java", whole / "roots.tsv",
            whole / "metadata.tsv", whole / "decompiled", "reuse-unchanged",
            "-postScript", "InventoryWholeProgram.java", whole / "analysis-snapshot.json")
        manifest = json.loads((whole / "decompiled/export-manifest.json").read_text())
        if roots == previous_roots and manifest["root_closure_complete"]:
            break
        if attempt == 5:
            raise ValueError("Ghidra roots did not stabilize; inspect the local project: " + str(project))
        shutil.copy2(whole / "analysis-snapshot.json", whole / "discovery-snapshot.json")
        previous_roots = roots
    python("tools/review_whole_program.py")
    print("Ghidra project retained at " + str(project))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path(os.environ.get(
        "TOS_ORIGINAL_EXE", r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe")).parent)
    parser.add_argument("--check", action="store_true", help="Check prerequisites without generating files")
    parser.add_argument("--decompile", action="store_true", help="Also prepare/check Ghidra exports and inventories")
    parser.add_argument("--ghidra", type=Path, default=ROOT / "build/research/ghidra_11.0.3_PUBLIC")
    args = parser.parse_args()
    try:
        if not args.check:
            prepare_data(args.source.resolve())
            if args.decompile:
                decompile(args.ghidra.resolve())
        require_cache(decompile=args.decompile)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, str(error) + "\n")
    print("Local research cache is ready" + (" (including decompilation)" if args.decompile else ""))


if __name__ == "__main__":
    main()
