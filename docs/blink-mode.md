# Blink mode and TSWH5

The reference was inspected before implementation in the same local `D:/Downloads/tswh5.zip`
archive used for Chinese item terminology. SHA-256:
`d2fd5ae5b45a1d4f0da57e85801d4e3445e828cf3df992106437d4e4df0c0f70`.

Relevant reference functions:

- `TSWH5/libs/control.js:503`, `setAutomaticRoute`: tries single-click instant movement
  before falling back to ordinary automatic walking.
- `TSWH5/libs/control.js:792`, `tryMoveDirectly`: ignores adjacent clicks, then tries
  the destination followed by its left, upper, lower and right neighbors. An adjacent
  approach ends with one ordinary movement input toward the selected event.
- `TSWH5/libs/maps.js:764-881`, `canMoveDirectlyArray` and its helpers: checks reachability
  with BFS; excludes blocking events, scripts, damage, repulsion and ambushes. It also
  refuses a hazardous starting position. Ignorable floor transitions are an explicit
  HTML5 exception; the C++ port conservatively excludes intermediate stairs, which
  always change floors under its native rules.
- `TSWH5/project/functions.js:1587`, `moveDirectly`: updates position and records a
  special replay input. `project/data.js:554` enables instant movement.
- `TSWH5/libs/maps.js:884-953`, `automaticRoute`: weighted ordinary walking, with
  penalties for damage, ambushes and some optional pickups. It does not provide the
  initially proposed action-aware door/monster optimization.

The requested scope was narrowed to TSWH5-style blink, without planning through doors
or other events. C++ therefore adds an input helper, not a new core movement rule:

- Search only connected, event-free floor. Disposable native movement probes detect
  magic, pincer damage and 47F magician movement without mutating the running game.
- Prefer the destination itself, otherwise use TSWH5's adjacent approach order and
  contact the destination once. Opening a door or secret tunnel leaves the hero beside it.
- Resolve the clear stretch in one frame through ordinary native movement inputs.
  Preserve normal event commands, dialogue, combat, floor transitions and saves.
- Fall back to the existing mouse walker if no safe blink is available, including
  adjacent clicks. This fallback retains the C++ walker's conservative event stopping.
- Record those native inputs with the existing replay format. Replay playback presents
  them as ordinary steps, while reproducing the same gameplay and original save bytes.

No combat, contact, map, save or replay schema changes are needed. `blink_mode` is an
independent, persisted Controls preference, off by default, with an experienced-player
note and an entry in the enabled-QOL tooltip. It takes precedence over mouse walking.
