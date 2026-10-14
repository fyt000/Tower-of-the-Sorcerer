# Offline route planner

This optional component builds `tsw_route`, separate from `tsw_game` and `tsw_cli`.
It owns its public headers, implementation, tests and CMake targets. It shares
the native game and replay libraries so planning uses the real game rules.
Neither the game nor MCP depends on this component; `TSW_PLANNER` defaults OFF.

From the repository root with the existing Windows build:

```powershell
cmake -S cpp -B build/cpp/vs -DTSW_PLANNER=ON
cmake --build build/cpp/vs --config Release --target tsw_route tsw_planner_tests
ctest --test-dir build/cpp/vs -C Release -L planner -LE audio --output-on-failure
build/cpp/vs/planner/Release/tsw_route.exe --help
```

To avoid desktop dependencies in a separate build directory, configure the
parent CMake project with `-DTSW_GUI=OFF -DTSW_PLANNER=ON`. This directory is a
component of that project, not a second copy of the game's dependency setup.

After a successful build, format the parent `src`, `include`, `tests` trees
as required by AGENTS.md, plus this component's C++ files. The formatter finds
`cpp/.clang-format` in the parent directory.

See [the guide](../../docs/route-planner.md) for algorithms and commands.
The final run is in `artifacts/final-run/`; regression recordings are in
`tests/replays/`. Planner scripts can make heuristic gameplay decisions and
are deliberately not accepted by the live MCP interface. MCP `run_steps`
only batches explicit native actions and ordinary destination navigation.
