"""Validate local compiler inputs recorded by prepare_delphi2_reference.py."""
import json
from pathlib import Path

from recovery_evidence import digest


def describe(path):
    return dict(path=str(path.resolve()), bytes=path.stat().st_size, sha256=digest(path))


def validate_media(path):
    manifest = json.loads((path / "media-manifest.json").read_text())
    for record in manifest["files"] + manifest["updates"]:
        name = record.get("extracted_path")
        if not name and record in manifest["updates"]:
            name = record["path"]
        if name and digest(path / name) != record["sha256"]:
            raise ValueError(f"Altered baseline input: {name}")
    payload = Path(manifest["media_path"]) / "DATA.Z"
    if digest(payload) != manifest["payload_sha256"]:
        raise ValueError("Altered baseline archive payload")
    archive = manifest.get("archive")
    if archive and digest(Path(archive["path"])) != archive["sha256"]:
        raise ValueError("Altered supplied archive")
    return manifest
