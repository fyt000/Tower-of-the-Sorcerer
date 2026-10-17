set(TSW_PORTABLE_ASSETS "${TSW_BUILD_ROOT}/assets" CACHE PATH "Extracted PNG, MIDI and WAV asset directory")
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(web_assets "${CMAKE_CURRENT_BINARY_DIR}/web-assets")
add_custom_target(tsw_web_assets
    BYPRODUCTS "${web_assets}/asset-version.txt"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/portable_assets.py"
        --source "${TSW_PORTABLE_ASSETS}" --soundfont "${SOUNDFONT_FILE}"
        --output "${web_assets}" --exclude-cjk-font
    VERBATIM)
set(font_manifest "${CMAKE_CURRENT_BINARY_DIR}/web-fonts.js")
set(font_preload "${CMAKE_CURRENT_BINARY_DIR}/web-font-labels")
configure_file(web/_headers "${CMAKE_CURRENT_BINARY_DIR}/site/_headers" COPYONLY)
add_custom_target(tsw_web_fonts
    BYPRODUCTS "${font_manifest}" "${font_preload}/labels.otf"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/web_fonts.py"
        --cache "${TSW_BUILD_ROOT}/dependencies/noto-cjk"
        --output "${CMAKE_CURRENT_BINARY_DIR}/site/fonts"
        --preload "${font_preload}" --manifest "${font_manifest}"
    VERBATIM)
add_dependencies(tsw_game tsw_web_assets tsw_web_fonts)
set_target_properties(tsw_game PROPERTIES
    SUFFIX ".html" OUTPUT_NAME "index"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/site"
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html;${CMAKE_CURRENT_SOURCE_DIR}/web/storage.js;${CMAKE_CURRENT_SOURCE_DIR}/web/input.js;${CMAKE_CURRENT_SOURCE_DIR}/web/fonts.js;${font_manifest};${font_preload}/labels.otf")
# The asset target refreshes its output on every build. Relink to refresh the .data package too.
set_property(TARGET tsw_game APPEND PROPERTY LINK_DEPENDS "${web_assets}/asset-version.txt")
target_link_options(tsw_game PRIVATE
    "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html"
    "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/storage.js"
    "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/input.js"
    "--pre-js=${font_manifest}"
    "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/fonts.js"
    "--preload-file=${web_assets}@/assets"
    "--preload-file=${font_preload}/labels.otf@/assets/fonts/labels.otf"
    -lidbfs.js -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=1
    -sINITIAL_MEMORY=134217728 -sSTACK_SIZE=8388608
    -sDISABLE_EXCEPTION_CATCHING=0 -sEXPORTED_RUNTIME_METHODS=FS
    -sUSE_GLFW=3 -sENVIRONMENT=web -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2)
