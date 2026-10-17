set(TSW_PORTABLE_ASSETS "${TSW_BUILD_ROOT}/assets" CACHE PATH "Extracted PNG, MIDI and WAV asset directory")
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(web_assets "${CMAKE_CURRENT_BINARY_DIR}/web-assets")
add_custom_target(tsw_web_assets
    BYPRODUCTS "${web_assets}/asset-version.txt"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/portable_assets.py"
        --source "${TSW_PORTABLE_ASSETS}" --soundfont "${CMAKE_CURRENT_SOURCE_DIR}/web/GeneralUser-q1.sfo"
        --soundfont-license "${SOUNDFONT_ROOT}/LICENSE.txt"
        --output "${web_assets}"
    VERBATIM)
add_dependencies(tsw_game tsw_web_assets)
target_include_directories(tsw_audio SYSTEM PRIVATE "${TSW_STB_INCLUDE_DIR}")
set_target_properties(tsw_game PROPERTIES
    SUFFIX ".html" OUTPUT_NAME "index"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/site"
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html;${CMAKE_CURRENT_SOURCE_DIR}/web/storage.js;${CMAKE_CURRENT_SOURCE_DIR}/web/input.js")
# The asset target refreshes its output on every build. Relink to refresh the .data package too.
set_property(TARGET tsw_game APPEND PROPERTY LINK_DEPENDS "${web_assets}/asset-version.txt")
target_link_options(tsw_game PRIVATE
    "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html"
    "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/storage.js"
    "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/input.js"
    "--preload-file=${web_assets}@/assets"
    -lidbfs.js -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=1
    -sINITIAL_MEMORY=134217728 -sSTACK_SIZE=8388608
    -sDISABLE_EXCEPTION_CATCHING=0 -sEXPORTED_RUNTIME_METHODS=FS
    -sUSE_GLFW=3 -sENVIRONMENT=web -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2)
