# Optional offline tooling. No game, CLI or MCP target links this library.
add_library(tsw_planner src/planner_engine.cpp src/planner_search.cpp
    src/planner_routes.cpp src/planner_economy.cpp src/planner_verify.cpp)
target_include_directories(tsw_planner PUBLIC include)
target_link_libraries(tsw_planner PUBLIC tsw_replay)
add_executable(tsw_route src/route_cli.cpp)
target_link_libraries(tsw_route PRIVATE tsw_planner)
foreach(target IN ITEMS tsw_planner tsw_route)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /utf-8)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()

if(BUILD_TESTING)
    add_executable(tsw_planner_tests tests/planner_tests.cpp)
    target_include_directories(tsw_planner_tests PRIVATE src)
    target_link_libraries(tsw_planner_tests PRIVATE tsw_planner Catch2::Catch2WithMain)
    set(replays "${CMAKE_CURRENT_SOURCE_DIR}/../../tests/replays")
    target_compile_definitions(tsw_planner_tests PRIVATE
        TSW_PLANNER_FIXTURE="${replays}/first-cycle-seal.jsonl"
        TSW_PLANNER_ECONOMY_FIXTURE="${replays}/first-cycle-seal-economy.jsonl"
        TSW_PLANNER_CASHFLOW_FIXTURE="${replays}/first-cycle-seal-cashflow.jsonl")
    catch_discover_tests(tsw_planner_tests TEST_PREFIX "planner: " PROPERTIES LABELS "planner")
endif()
