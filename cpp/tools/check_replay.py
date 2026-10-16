"""Check selected values from a C++ replay without a shared engine state schema."""
import argparse
import json
from pathlib import Path
import subprocess
import sys


def differences(actual, expected, path=""):
    if isinstance(expected, dict):
        for key, value in expected.items():
            name = f"{path}.{key}" if path else key
            if isinstance(actual, dict) and key in actual:
                yield from differences(actual[key], value, name)
            elif isinstance(actual, list) and key.isdecimal() and int(key) < len(actual):
                yield from differences(actual[int(key)], value, name)
            else:
                yield f"{name}: missing; expected {value!r}"
    elif actual != expected:
        yield f"{path}: expected {expected!r}, C++ {actual!r}"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("recording", type=Path)
    parser.add_argument("expected", type=Path, help="JSON with just the values this case checks")
    parser.add_argument("--cli", type=Path, required=True)
    parser.add_argument("--limit", type=int, help="inspect the first N commands")
    parser.add_argument("--map-floor", type=int, help="inspect a particular floor's tiles")
    args = parser.parse_args()
    command = [str(args.cli.resolve()), "replay", str(args.recording.resolve())]
    if args.limit is not None:
        command += ["--limit", str(args.limit)]
    if args.map_floor is not None:
        command += ["--map-floor", str(args.map_floor)]
    result = subprocess.run(command, capture_output=True, text=True, encoding="utf-8", timeout=60)
    if result.returncode:
        print(result.stderr.strip(), file=sys.stderr)
        return result.returncode
    actual = json.loads(result.stdout)
    expected = json.loads(args.expected.read_text(encoding="utf-8"))
    failures = list(differences(actual, expected))
    if failures:
        location = f" after {args.limit} commands" if args.limit is not None else " at the end"
        print(f"{args.recording.name}{location}:", file=sys.stderr)
        for failure in failures:
            print(f"  {failure}", file=sys.stderr)
        return 1
    print(f"{args.recording.name}: selected values match")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
