# Collection buttons

**Item collection** is an opt-in QOL under Settings → Game → Quality of life and
defaults off. Its preference is saved between launches and listed in the QOL status.
When off, both collection buttons and their toolbar background are absent, and
collection actions are disabled.

When enabled, **Zuck all** and **Zuck all except potion** sit beneath the inventory.
They use the original key, gem and potion sprites with a small pixel collection
arrow and the UI's gray beveled buttons. The second icon crosses out the potion.
Hovering shows each action's translated name and explanation. Each is a one-shot
action, independent of Mouse walking and Blink mode. Pickups are collected in
deterministic nearest-first order, repeatedly exposing any pickups behind them.
The second action leaves both red and blue potions untouched. A skipped potion
remains a barrier; pickups beyond it need another safe route.

Reachability uses the same disposable native movement probes as blink. Doors,
monsters, stairs, hidden walls, hidden objects, scripted floor cells and movement
hazards are barriers. Pickups on hazardous cells are also excluded. Collection
requires ordinary safe floor under the hero, since a return to stairs or a trigger
would cause an event. Normal stair landings are ordinary floor.

The native pickup code remains the source of truth for keys, potion scaling, gems,
inventory, weapons and shields. Internally the collector validates and expands each
pickup into a safe native movement round trip. All trips complete during activation,
so the hero's position stays fixed on screen. The presentation then animates the
collected icons toward the hero over roughly 0.6 seconds of real time, independent
of the animation-speed setting. Buttons are disabled during the animation, busy
events, overlays, Flight and replay playback. Loading, changing floors or starting
a new game clears the effects. No sprites or timers are stored in save files.

## Replay presentation

Replay deliberately retains ordinary walking, as requested. No replay schema or
input-kind changes are needed for collection. Its native inputs enter the existing
recorder, as blink's inputs already do. Replay playback shows ordinary movement:
blink becomes walking, and collection becomes
walking to each pickup and back. The resulting original-format saves are identical.
The live collection summary message and flying icons are presentation only.

Neither QOL adds replay events or presentation metadata. Playback and verification
both execute the same recorded native inputs.
