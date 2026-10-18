# Quality of life

**Settings → QOL**. All options default off and persist between launches.

| Option | Effect |
|---|---|
| Mouse walking | Click floor to walk, or an event to interact. |
| Blink mode | Instant movement across clear floor; overrides Mouse walking. |
| Item collection | **Zuck all** or **Zuck all except potion**; hero stays in place. |
| Hero Orb actual damage | Includes Cross and Dragon Slayer bonuses. |
| Realtime Hero Orb | Monster stats and HP cost on the map; requires Hero Orb. Uses the damage setting above. |
| Skip attack animation | First strike, then instant resolution; same damage and rewards. |
| Skip staircase animation | Immediate arrival without the spiral wipe. |

## Reachability

- **Mouse walking:** uses apparent floor; stops at unexpected events/hazards or other input.
- **Blink:** crosses connected safe floor. Doors, monsters, pickups, stairs, hidden passages and hazards block transit. Can contact the selected event once from beside it. Adjacent clicks or unavailable safe routes use ordinary walking.
- **Collection:** uses blink's transit restrictions and requires safe ordinary floor under the hero plus a safe round trip. Collects nearest first; removed pickups open paths, skipped potions block them. Never opens doors, fights, reveals passages or changes floors.

## Replay

Blink records ordinary walking; collection records walks to each pickup and back. Playback reproduces the same gameplay and original save bytes. No special replay events or visual metadata are stored. Animation skips apply to live play and playback.
