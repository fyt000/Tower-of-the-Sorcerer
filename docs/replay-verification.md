# Replay verification plan

Status: design proposal. The replay contract, C++ gameplay CLI and desktop recorder
described below are not implemented yet.

## Goal and existing pieces

Play the C++ baseline, record meaningful player actions, and replay those actions
in both engines. Check the action outcomes and resulting gameplay state, including
changes to floors the player is not currently visiting. Keep the existing Rust
architecture and the explicit C++ game branches. The original executable remains
the evidence for resolving disagreements with the C++ baseline.

- `tsw_core` is already independent of graphics and audio. Its public actions are
  `move`, `use`, `choose` and `continue_dialogue`; `run_one` executes automatic work.
- `DesktopSession` owns the actual desktop action dispatch and command scheduling.
  It is the recording integration point, alongside held-key movement dispatch.
- `tsw_probe` is an original-machine research adapter. Its raw state setters and
  internal handler calls stay separate from the proposed player CLI.
- Rust already has typed `Command`, `Engine::execute`, `headless` and JSONL `replay`
  modes. Its current replay parses commands and prints a final snapshot; it does
  not compare C++ outcomes or a common state schema.
- Rust's UI snapshot contains the current map and floor metadata, while `save_json`
  contains all mutated maps and more progression state. Neither native save format
  is the comparison contract.

## Record actions, omit rendering and input noise

Record movement intents that reach gameplay, item activations, shop decisions and
gameplay-relevant Flight selection. Do not record frames, elapsed time, animation
commands, repeated input polls, mouse coordinates, music samples or window changes.
Direction names, stable item IDs and stable choice IDs are the shared vocabulary;
each adapter maps them to its own enums and APIs.

Consecutive ordinary walking actions can occupy one record such as
`{"type":"walk","path":"UUURRDL"}`. The runner expands the exact direction
sequence and invokes the real movement API for every direction. Split the record
at a pickup, door interaction, combat, shop, floor transition, script side effect,
rejection or another player decision. There is no need to save a full snapshot for
each road square. Do not replace the captured path with independently calculated
pathfinding: the traversed squares and approach direction can matter.

Omit a repeated attempt only if it changes neither comparable state nor decision
context and is redundant with the preceding attempt. Keep the first genuine
rejection, such as a door without a key, so its legality and side effects can be
verified. Do not use an unchanged position or a false return value as a test for
irrelevance:

- `Game::move` changes facing before checking the map boundary. Contact can return
  true without entering a square. Doors and battles also differ from ordinary walking.
- A refused door attempt can still run original floor/door checks and alter tiles.
- `Game::flight_preview` can change the 2F map while browsing upward through 35F.
  Confirmation is not required for that write. Opening Flight also resets its
  direction. Preserve the actual selection sequence, direction reversals and
  cancellation; recording only the final destination loses behavior.
- Rust's current direct Flight action models a monotonic selection path. Exact
  selection/cancellation replay will require corresponding engine operations,
  rather than an adapter that invents world writes or substitutes a final flight.

The recorder should be an optional application component. It reads action results
and stable state outside rendering/audio callbacks. No verification counters,
golden-state assertions or test-only hooks belong in `Game` or the audio callback.

## Define when an action is complete

A gameplay transaction contains one player decision and the automatic work it
causes. The C++ headless driver executes `run_one` without waiting for animation
timers. It follows ordinary, non-choice dialogue continuations and the ending card
acknowledgment, and stops when movement is available, a shop decision is required,
or a terminal state has been reached. Automatic acknowledgment must execute the
original continuation; it must not clear a dialogue or skip its callbacks.

On the desktop, the player still sees scenes and acknowledges speech normally.
The recorder finalizes the transaction after that work completes. A shop purchase,
declined trade or Flight selector action remains an explicit decision. A visual
pause with one acknowledgment need not add a replay entry. Decide and test the
mapping of each C++ continuation to Rust's immediate effects or `choose("leave")`;
never silently dismiss a Rust interaction that has alternative outcomes.

The headless driver needs a command budget and explicit ready/prompt/terminal
results. It must not wait for `busy()` to become false forever: death or a stopped
engine can remain busy. Report an exhausted budget or unsupported boundary as a
failure, rather than silently discarding commands. A recording interrupted midway
through a transaction is marked incomplete and retains its last completed boundary.

## Compare semantics, not native structs or save bytes

Define a small, versioned canonical gameplay projection with named integer fields,
original floor/tile numbering and deterministic ordering. Both engines export it
independently. Compare fields and use a SHA-256 of their canonical encoding for
compact checkpoints. The projection includes:

| State | Required comparison |
|---|---|
| Hero | Floor, position, HP, attack, defense, gold, key counts and facing |
| Inventory and equipment | Ownership, consumable/charge counts, displayed equipment and collected equipment flags |
| World | Every floor's tiles and stair landing metadata, including unvisited floors |
| Progression | Dialogue/hint state, merchant usage, altar purchases, reward flags, Fairy visits/scoring and other flags affecting later behavior |
| Travel | Original highest-floor/stair bounds and Flight direction/selection state |
| Monsters | All 33 effective shared rows; tile variants must resolve consistently to the shared row |
| Cycles | Frontside/backside scaling, later-cycle carry state and Zeno seal state |
| Decision boundary | Ready, pending shop/Flight decision, death or other terminal state, with semantic choices and costs where relevant |

Normalize documented equivalents, such as equipment IDs and C++ cycle fields
versus Rust's cycle number and effective multiplier. Read current monster state
without invoking another encounter or its bump effects. Do not compare Rust's
unscaled enemy overrides directly with C++'s already-scaled rows, and do not hide
different Zeno variant values by picking one arbitrarily.

Exclude animation frames, renderer caches, translated prose, audio timing, modern
activity logs and opaque original save words. Extra state that affects gameplay
needs a documented equivalent; it cannot simply be excluded because only one
engine stores it. In particular, Rust's current `Player` has no facing field and
the existing Flight API does not expose preview/cancel. Record these as explicit
coverage gaps. A partial comparison can aid development but must be labeled
partial; a strict full-fidelity result fails on missing required state/operations.

The field/ID/flag mapping needs small reviewed fixtures. It must not copy expected
C++ values into the Rust projection or infer missing state from the expected file.
The adapters compare state without imposing C++'s queue or Rust's event architecture
on the other engine.

## Outcomes and legality

Distinguish malformed input from a well-formed action refused by gameplay. After
calling the actual engine action, report semantic outcomes such as walked,
opened-door, fought, died, opened-choice, used-item or blocked. A blocked action can
have state changes, so compare its resulting state as well. Do not equate C++'s
`move()` boolean with Rust's `last_action.ok`: they describe different things.

Check the preceding decision context, target/approach and availability for every
recorded action. Use the engine's own action dispatch to determine legality, not
a second implementation of its movement, inventory or combat rules. Fatal combat
is a valid original action, not an invalid move just because the hero cannot win.
Keep explicit negative cases for insufficient keys/gold, unavailable items,
ineligible Flight destinations, wrong dialogue context and input after death.

## Recording and CLI contract

Use a fixed JSONL action format plus a final canonical state file. This is an
adapter/replay format, not runtime campaign configuration. The recording header
identifies the schema, original-game profile, content fingerprints, baseline
revision and starting state. Each completed transaction stores its input,
normalized outcome and state digest. Ordinary walk paths can be grouped as above.
The sidecar stores readable initial/final state and selected milestone snapshots.

Start version 1 from a fresh game in both engines and compare their initial state
before any actions. Small, hand-authored traces exercise the contract before the
desktop recorder is added. Proposed interfaces:

```text
tsw_cli replay run.jsonl --emit cpp-states.jsonl
tos replay run.jsonl --verify --emit rust-states.jsonl
python tools/compare_replay.py run.jsonl
```

`tsw_cli` links only gameplay and adapter code; it needs no window, media or audio
device. Extend Rust's existing CLI instead of introducing another engine wrapper.
Machine-readable output goes to stdout, diagnostics to stderr; mismatches produce
a nonzero exit code. Keep the existing simple Rust replay input available.

The comparison tool checks every emitted transaction outcome/digest and the full
final state. On a mismatch, replay the failing prefix through both headless engines
with detailed state output. Expand a compressed walk to find its first divergent
direction. Report the action, pre-state, legality/outcome and field differences,
for example a changed tile at `(floor, x, y)` or a different shared monster row.
This gets useful diagnostics without recording every animation or full step state.

## Save/loading and starting later in the game

Add original `.dat` starts and save/restore branches after fresh-game playback
works. Bundle the actual save bytes and their hash; obtain the C++ initial state
through its real loader. Rust needs an explicit equivalent import/initialization
path. If a field or load rule is unsupported, report that limitation.

Do not take a new legacy save at every comparison boundary and reload it as the
state snapshot. Original saves omit mutable monster rows and reconstruct Zeno
with the legacy scaling quirk, so live state and restored state can differ. A
read-only canonical snapshot is separate from exercising real save/load behavior.
Keep original slot and raw Fairy formats unchanged.

When recording loads or restarting, preserve the branch's source and provenance.
Never inject C++ checkpoint values into Rust midway through a replay to get past
a divergence. Test legacy load reconstruction, raw Fairy checkpoints and
save/restore branching explicitly. Prepared research fixtures are useful for rare
states, but label them separately from naturally reached playthrough segments.

## Implementation order and acceptance

1. **State contract and headless runners.** Audit field/ID mappings, add the C++
   gameplay CLI and a Rust verification mode, and compare initial state plus short
   movement/contact traces. Add negative-action checks and self-replay determinism.
   Emit a coverage report for fields/operations that do not yet map.
2. **C++ desktop recording.** Record at actual action dispatch and completed
   transaction boundaries. Cover item/choice/Flight input as well as held walking.
   A recorded C++ session must reproduce its own outcomes and final state headlessly,
   independently of animation speed, window size or elapsed time.
3. **Strict cross-engine regression corpus.** Check in compact, reviewed recordings
   and expectations under `tests/replays/`; put generated reports under
   `build/verification/`. Cover pickups, doors, ordinary/fatal/forced battles,
   shops, capture, stairs versus wings, item edge cases, remote floor writes,
   Flight previews/reversal/cancel, all 50F Zeno branches and backside carry rules.
   Include the documented meaningful original quirks. Preserve baseline provenance.
4. **Loaded starts and save branches.** Add `.dat` fixtures, Fairy snapshots and
   the shared-Zeno load quirk, followed by longer natural tower recordings through
   the ending and later cycles. Keep rare-state fixtures and natural runs distinct.
5. **Bounded exploration and reduction.** Generate valid and refused action
   sequences from C++ decision states, run them through both engines and retain
   failures. Find the shortest failing prefix first; further reduction must replay
   and revalidate dependencies rather than teleporting or editing live state.

Gate later Rust gameplay changes on reviewed replay cases plus its unit tests.
Keep C++/original-machine differential checks as the independent reference layer;
passing replay cases establishes covered paths, not all possible game states.
When a discrepancy is found, resolve it against the C++ logic and original evidence
before changing or regenerating a golden result. Track deliberately modern Rust
behavior separately from the strict original-game profile.
