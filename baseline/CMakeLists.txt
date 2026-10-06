cmake_minimum_required(VERSION 3.25)
project(tos_original_baseline VERSION 0.6 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
option(BASELINE_GUI "Build the raylib desktop game" ON)
option(BASELINE_SANITIZERS "Enable address and undefined behavior checks" OFF)
add_library(baseline_core src/game.cpp src/combat.cpp src/items.cpp src/contact.cpp
    src/floor_checks.cpp src/scenes.cpp src/npcs.cpp src/save.cpp src/original_save.cpp src/save_slots.cpp)
target_include_directories(baseline_core PUBLIC include PRIVATE src)
if(MSVC)
    target_compile_options(baseline_core PRIVATE /W4 /utf-8)
    if(BASELINE_SANITIZERS)
        string(REGEX REPLACE "/RTC[1su]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        target_compile_options(baseline_core PUBLIC /fsanitize=address /Zi)
        target_link_options(baseline_core PUBLIC /INCREMENTAL:NO /DEBUG)
    endif()
else()
    target_compile_options(baseline_core PRIVATE -Wall -Wextra -Wpedantic)
    if(BASELINE_SANITIZERS)
        target_compile_options(baseline_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(baseline_core PUBLIC -fsanitize=address,undefined)
    endif()
endif()
add_executable(tos_baseline_probe src/probe.cpp)
target_link_libraries(tos_baseline_probe PRIVATE baseline_core)
include(FetchContent)
include(CTest)
if(BUILD_TESTING)
    # MSVC's instrumented STL must agree across the test runner and our objects.
    # Build Catch2 with ASan instead of mixing it with the ordinary vcpkg library.
    if(NOT (MSVC AND BASELINE_SANITIZERS))
        find_package(Catch2 3 CONFIG QUIET)
    endif()
    if(NOT Catch2_FOUND)
        FetchContent_Declare(Catch2 URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.13.0.tar.gz
            URL_HASH SHA512=7eea385d79d88a5690cde131fe7ccda97d5c54ea09d6f515000d7bf07c828809d61c1ac99912c1ee507cf933f61c1c47ecdcc45df7850ffa82714034b0fccf35
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
        FetchContent_MakeAvailable(Catch2)
        list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
        if(MSVC AND BASELINE_SANITIZERS)
            foreach(catch_target IN ITEMS Catch2 Catch2WithMain)
                target_compile_options(${catch_target} PRIVATE /fsanitize=address /Zi)
            endforeach()
        endif()
    endif()
    add_executable(baseline_tests tests/core_tests.cpp)
    target_link_libraries(baseline_tests PRIVATE baseline_core Catch2::Catch2WithMain)
    include(Catch)
    catch_discover_tests(baseline_tests TEST_PREFIX "core: " PROPERTIES LABELS "core")
endif()
if(BASELINE_GUI)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(raylib_USE_STATIC_LIBS ON)
    find_package(raylib 5.5 CONFIG QUIET)
    if(NOT raylib_FOUND)
      FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        URL_HASH SHA256=aea98ecf5bc5c5e0b789a76de0083a21a70457050ea4cc2aec7566935f5e258e
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
      FetchContent_MakeAvailable(raylib)
      set(RAYLIB_LICENSE "${raylib_SOURCE_DIR}/LICENSE")
    else()
      find_package(glfw3 CONFIG REQUIRED)
      if(VCPKG_TARGET_TRIPLET MATCHES "windows-static$")
        # raylib 5.5's package has one unqualified path and repeats it in its
        # link interface. Select the matching CRT library for each VS config.
        set(raylib_root "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
        find_library(BASELINE_RAYLIB_RELEASE NAMES raylib PATHS "${raylib_root}/lib" NO_DEFAULT_PATH REQUIRED)
        find_library(BASELINE_RAYLIB_DEBUG NAMES raylib PATHS "${raylib_root}/debug/lib" NO_DEFAULT_PATH REQUIRED)
        set_target_properties(raylib PROPERTIES
          IMPORTED_CONFIGURATIONS "DEBUG;RELEASE"
          IMPORTED_LOCATION_DEBUG "${BASELINE_RAYLIB_DEBUG}"
          IMPORTED_IMPLIB_DEBUG "${BASELINE_RAYLIB_DEBUG}"
          IMPORTED_LOCATION_RELEASE "${BASELINE_RAYLIB_RELEASE}"
          IMPORTED_IMPLIB_RELEASE "${BASELINE_RAYLIB_RELEASE}"
          MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE
          MAP_IMPORTED_CONFIG_MINSIZEREL RELEASE
          INTERFACE_LINK_LIBRARIES "")
      endif()
      find_file(RAYLIB_LICENSE NAMES copyright
        PATHS "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/raylib" REQUIRED NO_DEFAULT_PATH)
    endif()
    FetchContent_Declare(tinysoundfont URL https://github.com/schellingb/TinySoundFont/archive/853a0a171759f1ddba0de1442133a75912bbeffa.tar.gz
        URL_HASH SHA256=76c356df524f71f2a34f67fa0cb2cb946036fe7a65d2930a849569c5e742fa57
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(tinysoundfont)
    include(cmake/Soundfont.cmake)
    add_executable(tos_baseline src/desktop.cpp src/presentation.cpp src/presentation_checks.cpp src/audio.cpp
        src/assets.cpp src/embedded_media.cpp src/asset_checks.cpp)
    include(cmake/EmbeddedMedia.cmake)
    if(raylib_FOUND)
        find_path(BASELINE_STB_INCLUDE_DIR NAMES stb_image.h REQUIRED)
    else()
        set(BASELINE_STB_INCLUDE_DIR "${raylib_SOURCE_DIR}/src/external")
    endif()
    target_include_directories(tos_baseline SYSTEM PRIVATE "${BASELINE_STB_INCLUDE_DIR}")
    if(WIN32)
        set(presentation_assets "${original_directory}")
    else()
        set(presentation_assets "${CMAKE_CURRENT_SOURCE_DIR}/../web/assets")
    endif()
    add_test(NAME original_presentation COMMAND tos_baseline --assets "${presentation_assets}"
        --presentation-test "${CMAKE_CURRENT_BINARY_DIR}/presentation-checks")
    set_tests_properties(original_presentation PROPERTIES TIMEOUT 60)
    add_test(NAME original_audio COMMAND tos_baseline --assets "${presentation_assets}"
        --audio-test --screenshot "${CMAKE_CURRENT_BINARY_DIR}/midi-test.wav")
    set_tests_properties(original_audio PROPERTIES TIMEOUT 180)
    if(WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../web/assets/original-atlas.png")
        add_test(NAME original_assets COMMAND tos_baseline --assets "${original_directory}"
            --compare-assets "${CMAKE_CURRENT_SOURCE_DIR}/../web/assets"
            --asset-test "${CMAKE_CURRENT_BINARY_DIR}/asset-checks")
        add_test(NAME extracted_presentation COMMAND tos_baseline --assets "${CMAKE_CURRENT_SOURCE_DIR}/../web/assets"
            --presentation-test "${CMAKE_CURRENT_BINARY_DIR}/extracted-presentation-checks")
        set_tests_properties(original_assets extracted_presentation PROPERTIES TIMEOUT 60)
    endif()
    target_include_directories(tos_baseline SYSTEM PRIVATE ${tinysoundfont_SOURCE_DIR})
    target_link_libraries(tos_baseline PRIVATE baseline_core raylib)
    if(raylib_FOUND)
        target_link_libraries(tos_baseline PRIVATE glfw)
        if(WIN32)
            target_link_libraries(tos_baseline PRIVATE winmm)
        endif()
    endif()
    target_compile_definitions(tos_baseline PRIVATE BASELINE_ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/../web/assets")
    if(MSVC)
        target_compile_options(tos_baseline PRIVATE /W4 /utf-8)
        target_compile_definitions(tos_baseline PRIVATE _CRT_SECURE_NO_WARNINGS)
    else()
        target_compile_options(tos_baseline PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_custom_command(TARGET tos_baseline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOUNDFONT_ROOT}/LICENSE.txt $<TARGET_FILE_DIR:tos_baseline>/GeneralUser-GS-LICENSE.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${tinysoundfont_SOURCE_DIR}/LICENSE $<TARGET_FILE_DIR:tos_baseline>/TinySoundFont-LICENSE.txt
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RAYLIB_LICENSE} $<TARGET_FILE_DIR:tos_baseline>/raylib-LICENSE.txt)
    if(NOT WIN32)
        add_custom_command(TARGET tos_baseline POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SOUNDFONT_ROOT}/music.sf2 $<TARGET_FILE_DIR:tos_baseline>/music.sf2)
    endif()
    if(MINGW)
        target_link_options(tos_baseline PRIVATE -static-libgcc -static-libstdc++)
        target_link_options(tos_baseline_probe PRIVATE -static-libgcc -static-libstdc++)
        target_link_options(baseline_tests PRIVATE -static-libgcc -static-libstdc++)
    endif()
endif()
