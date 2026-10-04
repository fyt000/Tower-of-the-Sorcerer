#!/usr/bin/env python3
"""Extract the user's installed Tower of the Sorcerer v1.2 without running it.

Requires Python 3 and Pillow (`python -m pip install pillow`). Source files are
only read. Numeric map IDs and executable bytes are retained for reproducibility.
Campaign JSON is created once; --regenerate-campaign explicitly replaces it.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import struct
from pathlib import Path

from PIL import Image, ImageOps

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SOURCE = Path(r"D:\Program Files (x86)\Tower of the Sorcerer")
MAP_CODE_START = 0x550B8
MAP_CODE_END = 0x5FFD8
MONSTER_OFFSET = 0x88D10
MAP_RECORD_SIZE = 123
MAP_COUNT = 51


def write_json(path: Path, data: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def extract_maps(executable: bytes) -> tuple[bytes, list[dict]]:
    """Recognize the three x86 MOV-byte encodings used in syokidata1.

    The original Delphi initializer keeps EAX = 0x4B8934 throughout this
    routine. Its byte assignments cover [0,6272] exactly once, in order.
    This is extraction of constants, rather than execution of foreign code.
    """
    writes: dict[int, int] = {}
    evidence = []
    cursor = MAP_CODE_START
    while cursor < MAP_CODE_END:
        if executable[cursor] != 0xC6:
            cursor += 1
            continue
        encoding = executable[cursor + 1]
        if encoding == 0x00:
            displacement, value, size = 0, executable[cursor + 2], 3
        elif encoding == 0x40:
            displacement = struct.unpack_from("<b", executable, cursor + 2)[0]
            value, size = executable[cursor + 3], 4
        elif encoding == 0x80:
            displacement = struct.unpack_from("<i", executable, cursor + 2)[0]
            value, size = executable[cursor + 6], 7
        else:
            cursor += 1
            continue
        if 0 <= displacement < MAP_COUNT * MAP_RECORD_SIZE:
            if displacement in writes:
                raise ValueError(f"Repeated map displacement {displacement}")
            writes[displacement] = value
            evidence.append({"file_offset": f"0x{cursor:06x}", "map_byte_offset": displacement, "value": value})
        cursor += size
    expected = set(range(MAP_COUNT * MAP_RECORD_SIZE))
    if set(writes) != expected:
        raise ValueError(f"Incomplete initializer: {len(writes)} of {len(expected)} map bytes")
    return bytes(writes[index] for index in range(len(expected))), evidence


def extract_dialogue(executable: bytes) -> list[dict]:
    marker = executable.index(b"Items.Strings", 0x122B20)
    cursor = marker + len(b"Items.Strings")
    if executable[cursor] != 1:
        raise ValueError("Expected a Delphi vaList for original dialogue")
    cursor += 1
    strings = []
    while executable[cursor] in (6, 12):
        offset = cursor
        tag = executable[cursor]
        cursor += 1
        if tag == 6:  # vaString
            length = executable[cursor]
            cursor += 1
        else:  # vaLString
            length = struct.unpack_from("<I", executable, cursor)[0]
            cursor += 4
        value = executable[cursor:cursor + length].decode("cp1252")
        cursor += length
        strings.append({"id": len(strings), "text": value, "file_offset": f"0x{offset:06x}"})
    if len(strings) != 268 or executable[cursor] != 0:
        raise ValueError(f"Unexpected original dialogue list ({len(strings)} entries)")
    return strings


def sprite(tile: int) -> dict:
    return {"x": ((tile - 1) % 11) * 40, "y": ((tile - 1) // 11) * 40, "w": 40, "h": 40}


MONSTERS = [
    ("green_slime", "Green Slime", ""),
    ("red_slime", "Red Slime", ""),
    ("big_slime", "Big Slime", ""),
    ("bat", "Bat", ""),
    ("priest", "Priest", ""),
    ("superion_priest", "Superion Priest", ""),
    ("gate_keeper_c", "Gate-Keeper C", ""),
    ("gate_keeper_b", "Gate-Keeper B", ""),
    ("skeleton_c", "Skeleton C", ""),
    ("skeleton_b", "Skeleton B", ""),
    ("skeleton_a", "Skeleton A", ""),
    ("big_bat", "Big Bat", ""),
    ("zombie", "Zombie", "undead"),
    ("zombie_knight", "Zombie Knight", "undead"),
    ("rock", "Rock", ""),
    ("zeno", "The Magic Sergeant, Zeno", "boss"),
    ("magic_sergeant", "The Magic Sergeant", "sorcerer"),
    ("vampire", "Vampire", "undead"),
    ("giant_octopus", "Giant Octopus", "boss"),
    ("dragon", "Dragon", "dragon"),
    ("golden_knight", "Golden Knight", ""),
    ("knight", "Knight", ""),
    ("swordsman", "Swordsman", ""),
    ("soldier", "Soldier", ""),
    ("ghost_soldier", "Ghost Soldier", ""),
    ("slime_man", "Slime Man", ""),
    ("great_magic_master", "Great Magic Master", "boss"),
    ("vampire_bat", "Vampire Bat", ""),
    ("slime_lord", "SlimeLord", ""),
    ("magician_a", "Magician A", "magician_a"),
    ("magician_b", "Magician B", "magician_b"),
    ("dark_knight", "Dark Knight", ""),
    ("gate_keeper_a", "Gate-Keeper A", ""),
]


def enemy_index(tile: int) -> int | None:
    if 61 <= tile <= 96:
        return (tile - 61) // 2
    if 97 <= tile <= 105:
        return 18
    if tile == 122:
        return 19
    if 133 <= tile <= 158:
        return (tile - 93) // 2
    return None


def tile_definitions() -> dict:
    tiles = {str(tile): {"name": f"Original tile {tile}", "kind": "trigger", "sprite": sprite(tile)} for tile in range(1, 166)}
    tiles["0"] = {"name": "Void", "kind": "wall", "sprite": sprite(6)}

    def put(tile: int, name: str, kind: str, **fields: object) -> None:
        tiles[str(tile)].update(name=name, kind=kind, **fields)

    for tile, color in [(1, "yellow"), (2, "blue"), (3, "red")]:
        put(tile, f"{color.title()} door", "door", key=color)
    put(4, "Sealed gate", "special_door")
    put(5, "Prison gate", "special_door")
    put(6, "Stone passage", "floor")
    put(7, "Scripted stone passage", "floor")
    put(8, "Brick wall", "wall")
    put(9, "Secret wall", "hidden_wall")
    put(10, "Scripted wall", "wall")
    put(11, "Stairs up", "stairs_up")
    put(12, "Stairs down", "stairs_down")
    put(13, "Lava", "lava")
    put(14, "Star void", "wall")
    for tile in range(15, 19):
        put(tile, "Altar", "altar")
    for tile in (19, 20):
        put(tile, "Merchant", "merchant")
    for tile in (21, 22):
        put(tile, "Thief", "npc")
    for tile in (23, 24):
        put(tile, "Fairy", "fairy")
    for tile in (25, 26):
        put(tile, "Old man", "npc")
    for tile in (27, 28):
        put(tile, "Princess", "npc")
    for tile, color in [(29, "yellow"), (30, "red"), (31, "blue")]:
        put(tile, f"{color.title()} key", "key", key=color, amount=1)
    put(32, "Red potion", "potion", stat="hp", amount=50, scaled=True)
    put(33, "Blue potion", "potion", stat="hp", amount=200, scaled=True)
    put(34, "Red crystal", "gem", stat="attack", amount=1, scaled=True)
    put(35, "Blue crystal", "gem", stat="defense", amount=1, scaled=True)
    items = {
        36: ("Orb of the hero", "hero_orb"), 37: ("Orb of wisdom", "wisdom_orb"),
        38: ("Orb of flying", "flying_orb"), 39: ("Cross", "cross"),
        40: ("Magic elixir", "elixir"), 41: ("Magic mattock", "mattock"),
        42: ("Destructible ball", "bomb"), 43: ("Warp staff", "warp_staff"),
        44: ("Wing to fly up", "up_wing"), 45: ("Wing to fly down", "down_wing"),
        46: ("Dragon slayer", "dragon_slayer"), 47: ("Snow crystal", "snow_crystal"),
        48: ("Magic key", "magic_key"), 49: ("Super magic mattock", "super_mattock"),
        50: ("Lucky gold", "lucky_gold"),
    }
    for tile, (name, item) in items.items():
        put(tile, name, "item", item=item, amount=1)
    for level, (name, amount) in enumerate(zip(["Iron", "Silver", "Knight", "Holy", "Sacred"], [10, 20, 40, 50, 100])):
        put(51 + level, f"{name} sword", "equipment", stat="attack", amount=amount, item=f"sword_{level + 1}")
        put(56 + level, f"{name} shield", "equipment", stat="defense", amount=amount, item="sacred_shield" if level == 4 else f"shield_{level + 1}")
    for tile in range(61, 159):
        index = enemy_index(tile)
        if index is not None:
            put(tile, MONSTERS[index][1], "enemy", enemy=MONSTERS[index][0])
        else:
            put(tile, "Giant monster decoration", "wall")
    for tile in range(97, 106):
        tiles[str(tile)]["footprint"] = {"width": 3, "height": 3,
                                         "offset_x": (tile - 97) % 3, "offset_y": (tile - 97) // 3,
                                         "tiles": list(range(97, 115))}
    tiles["122"]["footprint"] = {"width": 3, "height": 3, "offset_x": 1, "offset_y": 2,
                                  "tiles": list(range(115, 133))}
    put(159, "Combat icon", "floor")
    put(160, "Cooled lava", "floor")
    put(161, "Star passage", "floor")
    put(164, "Blue wall", "wall")
    return tiles


def original_interactions(map_bytes: bytes, dialogue: list[dict]) -> list[dict]:
    """Position-specific original NPC messages and merchant offers.

    Message mappings come from roujin (0x449708; dialogue[62+code]) and
    syounin (0x449014; dialogue[246+case]). Prices are its literal globals.
    Reusable, JSON effects replace the original GUI callback instructions.
    """
    text = {entry["id"]: entry["text"] for entry in dialogue}
    old_man_ids = {2: 87, 3: 88, 4: 62, 6: 63, 16: 68, 18: 69, 21: 70,
                   23: 61, 27: 71, 31: 72, 33: 74, 36: 75, 37: 76,
                   39: 78, 42: 80, 45: 81, 46: 83, 48: 85}
    shop_data = {
        # floor: (original message, cost, stat quantities, granted item, later clue)
        2: (246, 0, {"gold": 1000}, None, 91),
        6: (247, 50, {"blue": 1}, None, 64),
        7: (248, 50, {"yellow": 5}, None, 65),
        12: (249, 800, {"red": 1}, None, 66),
        15: (251, 200, {"blue": 1}, None, 67),
        28: (252, 0, {"yellow": -1, "gold": 100}, None, None),
        31: (253, 1000, {"yellow": 4, "blue": 1}, None, 73),
        38: (254, 200, {"yellow": 3}, None, 77),
        39: (255, 2000, {"blue": 3}, None, 79),
        45: (256, 1000, {"hp": 2000}, None, 82),
        47: (257, 4000, {}, "super_mattock", 84),
    }
    interactions = []
    for floor in range(MAP_COUNT):
        for index, tile in enumerate(map_bytes[floor * 123 + 2:(floor + 1) * 123]):
            if tile not in (19, 21, 25, 27):
                continue
            x, y = index % 11, index // 11
            record = {"floor": floor, "x": x, "y": y, "name": tile_definitions()[str(tile)]["name"],
                      "text": "", "offers": [], "effects": [], "disappear": False}
            if tile == 25:
                message = old_man_ids.get(floor, 90)
                record.update(text=text[message], dialogue_ids=[message], source="Original TTSW10.roujin 0x449708 / 0x449E18")
                if floor in (2, 3):
                    flag = f"npc_{floor}_{x}_{y}_gift"
                    effects = [{"type": "flag", "flag": flag}]
                    if floor == 2:
                        effects += [{"type": "multiply_stat", "stat": stat, "numerator": 103, "denominator": 100} for stat in ("attack", "defense")]
                    else:
                        effects.append({"type": "give_item", "item": "hero_orb"})
                    record["offers"] = [{"id": "accept", "label": "Accept the gift", "cost": 0, "once": True,
                                         "conditions": [{"type": "flag", "flag": flag, "value": False}], "effects": effects}]
            elif tile == 19:
                message, cost, quantities, item, clue = shop_data[floor]
                flag = f"merchant_{floor}_{x}_{y}_bought"
                effects = [{"type": "add_stat", "stat": stat, "amount": amount} for stat, amount in quantities.items()]
                if item:
                    effects.append({"type": "give_item", "item": item})
                if clue is not None:
                    effects += [{"type": "flag", "flag": flag}, {"type": "message", "text": text[clue], "dialogue_id": clue}]
                conditions = [{"type": "stat_at_least", "stat": "yellow", "amount": 1}] if floor == 28 else [{"type": "flag", "flag": flag, "value": False}]
                label = "Accept 1000 gold" if floor == 2 else "Sell one yellow key for 100 gold" if floor == 28 else text[message]
                record.update(text=text[message], dialogue_ids=[message] + ([clue] if clue is not None else []),
                              source="Original TTSW10.syounin 0x449014; literal prices and original offer dialogue",
                              offers=[{"id": "trade", "label": label, "cost": cost, "once": floor != 28,
                                       "conditions": conditions, "effects": effects}])
                if clue is not None:
                    record["after_text"] = {"flag": flag, "text": text[clue]}
            elif tile == 21:
                ids = {2: [3, 4, 57], 15: [17], 29: [26, 27, 28]}.get(floor, [31])
                record.update(text="Talk to the thief to continue.", dialogue_ids=ids,
                              source="Original TTSW10.touzoku 0x465900; map effects live in events.json")
            else:
                record.update(text="Speak to the princess.", dialogue_ids=[25], source="Original princess case TTSW10.handan 0x445397; dialogue/map effects live in events.json")
            interactions.append(record)
    # These NPCs are absent in the initializer and revealed by original events.
    # handan's tile-10 branch at 0x4448CE hides a repeatable key merchant and
    # the old man who grants the Elixir. Fairy callback 0x478F0C removes the
    # fairy and stores the original score/checkpoint; it grants no combat stats.
    interactions.append({"floor": 12, "x": 10, "y": 0, "name": "Key merchant",
                         "text": text[250], "dialogue_ids": [250], "effects": [], "disappear": False,
                         "offers": [{"id": "trade", "label": "Buy one yellow key", "cost": 1000, "once": False,
                                     "effects": [{"type": "add_stat", "stat": "yellow", "amount": 1}]}],
                         "source": "Original handan 0x4448F8 reveals merchant; syounin 0x449014 floor-12 right branch"})
    flag = "npc_16_10_10_gift"
    interactions.append({"floor": 16, "x": 10, "y": 10, "name": "Hidden old man",
                         "text": text[89], "dialogue_ids": [89], "effects": [], "disappear": False,
                         "offers": [{"id": "accept", "label": "Accept the Elixir", "cost": 0, "once": True,
                                     "conditions": [{"type": "flag", "flag": flag, "value": False}],
                                     "effects": [{"type": "give_item", "item": "elixir"}, {"type": "flag", "flag": flag}]}],
                         "source": "Original handan 0x4449F0 reveals old man; roujin floor-16 right branch gives Elixir"})
    for floor, x, y in [(10, 5, 2), (20, 5, 4), (25, 5, 6), (40, 5, 5), (49, 5, 1)]:
        interactions.append({"floor": floor, "x": x, "y": y, "name": "Fairy",
                             "text": text[227], "dialogue_ids": [227], "offers": [], "effects": [], "disappear": True,
                             "source": "Original fairy 0x478F0C clears fairy on continue; score/rank overlay replaced by modern acknowledgement"})
    interactions.append({"floor": 50, "x": 4, "y": 8, "name": "Thief", "text": "Talk to the thief to continue.",
                         "dialogue_ids": [263], "offers": [], "effects": [], "disappear": False,
                         "source": "Original touzoku floor-50 branch; dialogue/map effects live in events.json"})
    return interactions


def build_campaign(map_bytes: bytes, monsters: list[dict], source_hash: str) -> dict:
    floors = []
    for floor_id in range(MAP_COUNT):
        raw = map_bytes[floor_id * MAP_RECORD_SIZE:(floor_id + 1) * MAP_RECORD_SIZE]
        floors.append({"id": floor_id, "title": "Secret floor" if floor_id == 0 else f"Floor {floor_id}",
                       "arrival_up": {"x": raw[0] % 11, "y": raw[0] // 11},
                       "arrival_down": {"x": raw[1] % 11, "y": raw[1] // 11},
                       "tiles": list(raw[2:])})
    events_path = ROOT / "data" / "events.json"
    events = json.loads(events_path.read_text(encoding="utf-8")) if events_path.exists() else []
    if isinstance(events, dict):
        events = events.get("events", [])
    return {
        "id": "tower-of-the-sorcerer-1.2", "title": "Tower of the Sorcerer", "width": 11, "height": 11,
        "start": {"floor": 1, "x": 5, "y": 10, "hp": 1000, "attack": 100, "defense": 100,
                  "gold": 0, "keys": {"yellow": 0, "blue": 0, "red": 0}, "inventory": ["sword_5", "sacred_shield"]},
        "rules": {"empty_tile": 6, "hero_attacks_first": True,
                  "area_scaling": [{"max_floor": n * 10, "multiplier": n} for n in range(1, 6)],
                  "altar_base_cost": 10, "altar_attack_gain": 2, "altar_defense_gain": 4,
                  "altar_hp_gain": 100, "lava_damage": 0, "cross_multiplier": 2, "dragon_slayer_multiplier": 2,
                  "flying_requires_stairs": True, "save_requires_hero_orb": True,
                  "stair_links": {"43:up": 45, "45:down": 43}},
        "floors": floors, "tiles": tile_definitions(), "enemies": {row["id"]: {k: v for k, v in row.items() if k != "id"} for row in monsters},
        "events": events,
        "interactions": json.loads((ROOT / "data" / "interactions.json").read_text(encoding="utf-8")) if (ROOT / "data" / "interactions.json").exists() else [],
        "provenance": {"source": "Installed Tower of the Sorcerer v1.2 by Oz & Kenichi", "executable_sha256": source_hash,
                       "maps": "All 51 original initializer records extracted from TSW.exe; row-major and original tile IDs retained",
                       "enemy_stats": "All 33 original little-endian DWORD rows from TSW.exe offset 0x88D10",
                       "status": "Scripted events are configured separately; see docs/original-data.md for fidelity coverage"},
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=DEFAULT_SOURCE)
    parser.add_argument("--regenerate-campaign", "--write-campaign", action="store_true", help="Replace editable campaign.json with extracted defaults, preserving separate events.json and interactions.json")
    args = parser.parse_args()
    source = args.source.resolve()
    executable = (source / "TSW.exe").read_bytes()
    executable_hash = hashlib.sha256(executable).hexdigest()
    data_dir, asset_dir = ROOT / "data", ROOT / "web" / "assets"
    data_dir.mkdir(parents=True, exist_ok=True)
    asset_dir.mkdir(parents=True, exist_ok=True)

    map_bytes, map_evidence = extract_maps(executable)
    (data_dir / "original-map-bytes.bin").write_bytes(map_bytes)
    write_json(data_dir / "original-maps.json", [{"id": i, "stair_landings": list(map_bytes[i * 123:i * 123 + 2]), "tiles": list(map_bytes[i * 123 + 2:(i + 1) * 123])} for i in range(51)])
    write_json(data_dir / "original-map-evidence.json", {"initializer_file_range": [hex(MAP_CODE_START), hex(MAP_CODE_END)], "map_base_virtual_address": "0x4b8934", "writes": map_evidence})
    dialogue = extract_dialogue(executable)
    write_json(data_dir / "original-dialogue.json", dialogue)
    if not (data_dir / "interactions.json").exists():
        write_json(data_dir / "interactions.json", original_interactions(map_bytes, dialogue))
    monsters = []
    for index, (identifier, name, special) in enumerate(MONSTERS):
        hp, attack, defense, gold = struct.unpack_from("<4I", executable, MONSTER_OFFSET + index * 16)
        row = {"id": identifier, "name": name, "hp": hp, "attack": attack, "defense": defense, "gold": gold}
        if special:
            row["special"] = special
        monsters.append(row)
    write_json(data_dir / "original-enemies.json", monsters)

    extraction = []
    for subfolder in ("Data3", "Data2"):
        for path in sorted((source / subfolder).glob("*")):
            if path.suffix.lower() not in (".bmp", ".oz"):
                continue
            target_name = "original-atlas.png" if path.name.lower() == "chtable.oz" else "original-background-atlas.png" if path.name.lower() == "chtableb.oz" else f"{subfolder.lower()}-{path.stem.lower()}.png"
            target = asset_dir / target_name
            with Image.open(path) as bitmap:
                bitmap.convert("RGB").save(target, optimize=True)
                size = list(bitmap.size)
            extraction.append({"source": f"{subfolder}/{path.name}", "output": f"web/assets/{target_name}", "size": size, "source_sha256": hashlib.sha256(path.read_bytes()).hexdigest()})
    for folder in ("Wav", "Midi"):
        target_dir = asset_dir / folder.lower()
        target_dir.mkdir(exist_ok=True)
        for path in sorted((source / folder).glob("*")):
            if path.is_file():
                shutil.copyfile(path, target_dir / path.name.lower())
                extraction.append({"source": f"{folder}/{path.name}", "output": f"web/assets/{folder.lower()}/{path.name.lower()}", "source_sha256": hashlib.sha256(path.read_bytes()).hexdigest()})
    hero_directions = {}
    with Image.open(asset_dir / "original-atlas.png") as atlas:
        for direction, tile in {"down": 185, "left": 193, "right": 201, "up": 209}.items():
            rect, mask_rect = sprite(tile), sprite(tile + 1)
            hero = atlas.crop((rect["x"], rect["y"], rect["x"] + 40, rect["y"] + 40)).convert("RGBA")
            mask = atlas.crop((mask_rect["x"], mask_rect["y"], mask_rect["x"] + 40, mask_rect["y"] + 40)).convert("L")
            hero.putalpha(ImageOps.invert(mask))
            hero.save(asset_dir / f"hero-{direction}.png")
            hero_directions[direction] = {"source": f"assets/hero-{direction}.png", "x": 0, "y": 0, "w": 40, "h": 40}
            extraction.append({"source": "Data3/Chtable.oz", "output": f"web/assets/hero-{direction}.png", "color_tile": tile, "mask_tile": tile + 1, "size": [40, 40]})
    write_json(asset_dir / "manifest.json", {"atlas": "assets/original-atlas.png", "tile_size": 40, "columns": 11, "hero": hero_directions["down"], "hero_directions": hero_directions, "hero_frames": {"down": [sprite(185), sprite(187)], "left": [sprite(193), sprite(195)], "right": [sprite(201), sprite(203)], "up": [sprite(209), sprite(211)]}, "floor": sprite(6), "tiles": {str(n): sprite(n) for n in range(1, 221)}, "credits": "Original artwork: Oz & Kenichi / Shigemasa Ozawa"})
    write_json(data_dir / "extraction-manifest.json", {"source_directory": str(source), "executable_sha256": executable_hash, "map_count": 51, "map_record_bytes": 123, "monster_count": 33, "dialogue_count": 268, "assets": extraction})
    campaign_path = data_dir / "campaign.json"
    if args.regenerate_campaign or not campaign_path.exists():
        write_json(campaign_path, build_campaign(map_bytes, monsters, executable_hash))
    print(f"Extracted 51 original maps, 33 enemy stat rows, 268 dialogue entries, and {len(extraction)} assets.")
    print(f"Executable SHA-256: {executable_hash}")
    print(f"Editable campaign: {campaign_path}")


if __name__ == "__main__":
    main()
