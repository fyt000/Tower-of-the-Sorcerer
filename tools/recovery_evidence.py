"""Shared file hashes and reference identity for source-recovery tools."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ORIGINAL_HASH = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779"


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()
