# Original form pictures must survive replacement of TSW.exe; MIDI synthesis needs its bank too.
if(WIN32)
    enable_language(RC)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(original_exe "$ENV{TOS_ORIGINAL_EXE}")
    if(NOT original_exe)
        set(original_exe "D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe")
    endif()
    set(TSW_ORIGINAL_EXE "${original_exe}" CACHE FILEPATH "Original English Tower of the Sorcerer 1.2 EXE")
    if(NOT EXISTS "${TSW_ORIGINAL_EXE}")
        message(FATAL_ERROR "Set TSW_ORIGINAL_EXE to the original TSW.exe to embed its ending pictures")
    endif()
    set(EMBEDDED_ROOT "${CMAKE_CURRENT_BINARY_DIR}/embedded")
    file(MAKE_DIRECTORY "${EMBEDDED_ROOT}")
    add_custom_command(OUTPUT "${EMBEDDED_ROOT}/ending-story.bmp" "${EMBEDDED_ROOT}/ending-card.bmp"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_ui.py"
            --exe "${TSW_ORIGINAL_EXE}" --binary-output "${EMBEDDED_ROOT}"
        DEPENDS "${TSW_ORIGINAL_EXE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_ui.py"
        VERBATIM)
    add_custom_target(tsw_embedded_media DEPENDS
        "${EMBEDDED_ROOT}/ending-story.bmp" "${EMBEDDED_ROOT}/ending-card.bmp")
    configure_file(cmake/media.rc.in "${EMBEDDED_ROOT}/media.rc" @ONLY)
    set_source_files_properties("${EMBEDDED_ROOT}/media.rc" PROPERTIES OBJECT_DEPENDS
        "${EMBEDDED_ROOT}/ending-story.bmp;${EMBEDDED_ROOT}/ending-card.bmp;${SOUNDFONT_ROOT}/music.sf2")
    get_filename_component(original_directory "${TSW_ORIGINAL_EXE}" DIRECTORY)
endif()

function(tsw_embed_media target)
    if(WIN32)
        target_sources(${target} PRIVATE "${EMBEDDED_ROOT}/media.rc")
        add_dependencies(${target} tsw_embedded_media)
        target_compile_definitions(${target} PRIVATE TSW_ORIGINAL_ASSETS="${original_directory}")
    else()
        target_compile_definitions(${target} PRIVATE TSW_ORIGINAL_ASSETS="")
        add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SOUNDFONT_ROOT}/music.sf2" $<TARGET_FILE_DIR:${target}>/music.sf2)
    endif()
    target_compile_definitions(${target} PRIVATE TSW_ASSETS="${TSW_BUILD_ROOT}/assets")
endfunction()
