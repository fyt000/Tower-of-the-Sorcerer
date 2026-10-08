# Replay verification plan

Status: proposal. Rust already supports JSONL replay and headless commands. The
C++ gameplay CLI, desktop recorder and comparison script are not implemented.

Play the faithful C++ baseline, record player actions and replay them in both
engines to check later Rust changes. Keep Rust's architecture independent. Use
the original executable and decompiled evidence to resolve disagreements with
C++, rather than assuming every C++ result is correct.

## Share inputs; check a few explicit results

Reuse Rust's existing player command format where the operations correspond:

```jsonl
{"type":"move","direction":"up"}
{"type":"choose","choice":"leave"}
{"type":"use_item","item":"bomb"}
```

A small C++ CLI maps these inputs to the real `Game` actions. Rust uses its
existing `Engine::execute` and CLI. These adapters translate directions, item
names and choices; they do not implement game rules. `tsw_probe` remains a
research tool with raw setters and internal handler calls, separate from replay.

Each CLI prints readable values from its own engine. Reuse Rust's native JSON
output and give C++ a small read-only output suitable for inspection. Neither
engine needs to export a universal state representation, mirror the other's
structures or use the same save format.

A separate test script reads those outputs and compares a few explicit facts:
hero floor/position, HP, attack, defense, gold and keys. A scenario adds item
ownership, a charge count or particular map tiles when those facts matter to
that test. Map a value in the test helper only when a test needs it. For example,
a remote map change requires a read-only query in the CLI if its usual output
does not include that floor.

There are no state hashes, whole-world serialization contract, normalized
outcome vocabulary or mandatory field coverage report. Some correspondence
between observable values is unavoidable for a comparison; keep it small and
explicit in tests. Rust's internal flags and enemy representation remain its own.

## Keep recording and playback straightforward

Begin every initial replay with a fresh game. Keep one JSON command per gameplay
input, using the existing Rust format. This records the route without requiring a
new path encoding or pathfinding. Check final results or selected milestones;
there is no need to capture state after every square. Grouping ordinary walking
can wait until recording size actually becomes a problem.

The optional desktop recorder writes inputs where the application dispatches
them to gameplay. It does not record frames, animation timing, repeated keyboard
polls, window changes or audio. Keep actual refused attempts: an unchanged hero
position can still accompany an original script side effect. Deciding which
inputs are redundant would add filtering logic without helping the first version.

The headless C++ runner executes the resulting command queue without animation
delays. It acknowledges dialogue with no decision through its real continuation
and pauses for shop choices. It stops on death or completion and bounds automatic
work so a stuck queue produces a useful error. Corresponding Rust dialogue
handling belongs in the CLI adapter. Unsupported inputs or interactions are
reported rather than approximated silently.

Gameplay legality comes from calling each engine's normal actions. Tests for
refused moves check concrete effects, such as the hero staying put, the key count
remaining unchanged and the door staying closed, plus any expected script effects.
C++'s movement boolean and Rust's action status have different meanings; comparing
them directly would require an unnecessary outcome abstraction.

Flight selection needs a separate decision later. In C++, browsing through 35F
can change a 2F tile before confirming travel, and direction reversals or cancel
can matter. Rust's current direct flight command does not expose that full input
sequence. Initially mark those cases unsupported. Add actual selection commands
only when testing that behavior, without inventing world writes in an adapter.

## Diagnose differences with values and replay prefixes

A failure should name the replay, command number and actual values, for example:

```text
door-without-key.jsonl, after command 38 (move right)
hero.hp: C++ 400, Rust 420
```

That command is the observation point, not necessarily the first divergent
action. Rerun a shorter prefix or add a check around the suspected interaction,
then inspect the native outputs. Ordinary field differences already explain
more than a hash mismatch. We do not need automatic trace reduction to begin.

Passing a replay proves its selected checks on that path. It does not establish
that every internal field matches. Add a focused assertion when investigating
a bug; longer replays can also reveal differences in hidden state through their
later gameplay effects.

## First implementation

1. Add the small C++ headless CLI and a comparison script. Reuse Rust's existing
   replay/headless modes; add read-only queries only where a test needs them.
2. Write a handful of short cases for walking, pickups, doors, combat and shops,
   including refused attempts. Compare readable final values. Keep cases under
   `tests/replays/` and generated output under ignored `build/verification/`.
3. Add optional recording to C++ action dispatch. Confirm that a recorded session
   reproduces its checked results in the C++ headless runner before using it to
   check Rust. Keep assertions and comparison code outside production gameplay.
4. Grow the cases around actual discrepancies and important branches, including
   Zeno, backside behavior and meaningful original quirks.

Legacy-save starts, save/load actions and exact Flight-selector recording can be
separate later additions. Do not use save/reload at comparison points: the
original format reconstructs some state, including Zeno, and can change the live
result. The first version needs no save compatibility layer, shared progression
model or changes to either engine's architecture.
