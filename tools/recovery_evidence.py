"""Shared file hashes and reference identity for source-recovery tools."""
import hashlib
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ORIGINAL_HASH = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779"


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def original_exe():
    return Path(os.environ.get("TOS_ORIGINAL_EXE") or ROOT / "build/research/TSW.exe")


def original_assets():
    return Path(os.environ.get("TOS_ASSETS") or original_exe().parent)
