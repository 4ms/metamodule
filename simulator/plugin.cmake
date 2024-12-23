# TODO: Get cmake to copy the source file that contains init() and rename that function to init_BRAND()
# Also see if Cmake can generate the calls to init (currently manually written into simulator/src/ext_plugin_builtin.hh)

# file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/replace.cmake"
# [=[
# file(READ "${SOURCE}" TEXT)
# string(REPLACE "foo" "bar" TEXT "${TEXT}")
# file(WRITE "${TARGET}" "${TEXT}")
# ]=])

# add_custom_command(
#     OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/plugin.cpp"
#     COMMAND "${CMAKE_COMMAND}"
#         "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/plugin.cpp"
#         "-DTARGET=${CMAKE_CURRENT_BINARY_DIR}/plugin.cpp"
#         -P "${CMAKE_CURRENT_BINARY_DIR}/replace.cmake"
#     DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/plugin.cpp" "${CMAKE_CURRENT_BINARY_DIR}/replace.cmake"
# )


function(create_plugin)
	message("Building ${brand} as built-in plugin (create_plugin)")

	# target_sources(${PLUGIN_OPTIONS_SOURCE_LIB} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/plugin.cpp)

    set(oneValueArgs SOURCE_LIB SOURCE_ASSETS DESTINATION PLUGIN_NAME PLUGIN_JSON)
    cmake_parse_arguments(PLUGIN_OPTIONS "" "${oneValueArgs}" "" ${ARGN} )

	add_custom_command(
		OUTPUT "${ASSET_DIR}/${PLUGIN_OPTIONS_PLUGIN_NAME}" 
		COMMAND ${CMAKE_COMMAND} -E copy_directory "${PLUGIN_OPTIONS_SOURCE_ASSETS}" "${ASSET_DIR}/${PLUGIN_OPTIONS_PLUGIN_NAME}"
		COMMENT "Copying ${PLUGIN_OPTIONS_SOURCE_ASSETS} to ${ASSET_DIR}/${PLUGIN_OPTIONS_PLUGIN_NAME}"
		VERBATIM
	)

	add_custom_target(${PLUGIN_OPTIONS_SOURCE_LIB}-assets
		DEPENDS "${ASSET_DIR}/${PLUGIN_OPTIONS_PLUGIN_NAME}" 
	)


endfunction()
