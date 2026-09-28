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

	# The real SDK's create_plugin() packages plugin.json and plugin-mm.json into the
	# .mmplugin next to the assets. Built-in brands have them in their asset dir instead,
	# where InternalPluginManager::parse_jsons() reads them -- so copy them there, or the
	# plugin's metadata (display names, element groups) is silently missing in the simulator.
	set(PLUGIN_MANIFESTS "")
	if (EXISTS "${PLUGIN_OPTIONS_PLUGIN_JSON}")
		list(APPEND PLUGIN_MANIFESTS "${PLUGIN_OPTIONS_PLUGIN_JSON}")
	endif()

	# Validate plugin-mm.json the same way the SDK's create_plugin() does: JSON syntax,
	# the shape of groups/order/names, and that each module slug is in plugin.json.
	# Like the SDK, this runs on every build. A JSON syntax error fails the build;
	# anything else is a warning.
	set(PLUGIN_VALIDATE_TARGET "")
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/plugin-mm.json")
		add_custom_target(${PLUGIN_OPTIONS_SOURCE_LIB}-validate-plugin-mm-json ALL
			COMMAND ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../firmware/metamodule-plugin-sdk/scripts/check_plugin_mm_json.py
				--plugin-mm-json "${CMAKE_CURRENT_SOURCE_DIR}/plugin-mm.json"
				--plugin-json "${PLUGIN_OPTIONS_PLUGIN_JSON}"
			VERBATIM
			USES_TERMINAL
			COMMENT "Validating ${PLUGIN_OPTIONS_PLUGIN_NAME}'s plugin-mm.json"
		)
		set(PLUGIN_VALIDATE_TARGET ${PLUGIN_OPTIONS_SOURCE_LIB}-validate-plugin-mm-json)
	endif()

	# The SDK's create_plugin() rewrites element-group members written as enumerator
	# names into typed indices, reading the plugin's DWARF. Built-in plugins here are
	# compiled natively, so there may be no ELF to read: --best-effort leaves those
	# members as written, and the firmware falls back to matching them by name.
	set(PLUGIN_MM_JSON_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/plugin-mm.json")
	if (EXISTS "${PLUGIN_MM_JSON_SOURCE}")
		set(PLUGIN_MM_JSON_RESOLVED "${CMAKE_CURRENT_BINARY_DIR}/plugin-mm.json")
		add_custom_command(
			OUTPUT "${PLUGIN_MM_JSON_RESOLVED}"
			COMMAND ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../firmware/metamodule-plugin-sdk/scripts/resolve_element_groups.py
				--in "${PLUGIN_MM_JSON_SOURCE}"
				--out "${PLUGIN_MM_JSON_RESOLVED}"
				--elf $<TARGET_FILE:${PLUGIN_OPTIONS_SOURCE_LIB}>
				--best-effort
			DEPENDS "${PLUGIN_MM_JSON_SOURCE}" ${PLUGIN_OPTIONS_SOURCE_LIB}
				${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../firmware/metamodule-plugin-sdk/scripts/resolve_element_groups.py
			COMMENT "Resolving element groups in ${PLUGIN_OPTIONS_PLUGIN_NAME}'s plugin-mm.json"
			VERBATIM
		)
		list(APPEND PLUGIN_MANIFESTS "${PLUGIN_MM_JSON_RESOLVED}")
	endif()

	# The asset image (see ext-plugins.cmake) copies this plugin's assets and manifests
	# into the asset dir itself, rebuilding the whole dir each time. So nothing here
	# copies into the asset dir: a separate copy step, tracked by a stamp file, goes
	# stale when the asset dir is deleted but the stamp isn't.
	#
	# CONFIGURE_DEPENDS re-globs at build time, so added or deleted asset files trigger
	# a reconfigure and modified ones rebuild the image.
	set(PLUGIN_ASSET_FILES "")
	if (IS_DIRECTORY "${PLUGIN_OPTIONS_SOURCE_ASSETS}")
		file(GLOB_RECURSE PLUGIN_ASSET_FILES CONFIGURE_DEPENDS "${PLUGIN_OPTIONS_SOURCE_ASSETS}/*")
	endif()

	# A custom command's rule is only generated if a target in the same directory uses
	# it, so without this the resolved plugin-mm.json would never be (re)built
	add_custom_target(${PLUGIN_OPTIONS_SOURCE_LIB}-assets ALL
		DEPENDS ${PLUGIN_MANIFESTS}
	)
	if (PLUGIN_VALIDATE_TARGET)
		add_dependencies(${PLUGIN_OPTIONS_SOURCE_LIB}-assets ${PLUGIN_VALIDATE_TARGET})
	endif()

	# One entry per plugin in each list: ext-plugins.cmake zips them together.
	# The manifests are joined with | since a global property can't hold nested lists.
	list(JOIN PLUGIN_MANIFESTS "|" PLUGIN_MANIFESTS_JOINED)
	set_property(GLOBAL APPEND PROPERTY MM_PLUGIN_ASSET_NAMES "${PLUGIN_OPTIONS_PLUGIN_NAME}")
	set_property(GLOBAL APPEND PROPERTY MM_PLUGIN_ASSET_SOURCE_DIRS "${PLUGIN_OPTIONS_SOURCE_ASSETS}")
	set_property(GLOBAL APPEND PROPERTY MM_PLUGIN_ASSET_MANIFESTS "${PLUGIN_MANIFESTS_JOINED}")
	set_property(GLOBAL APPEND PROPERTY MM_PLUGIN_ASSET_DEPENDS ${PLUGIN_MANIFESTS} ${PLUGIN_ASSET_FILES})

    # The real SDK's create_plugin() defines a `plugin` target, and so we need to define
    # the same target here so that plugin CMakeLists can reference this target (e.g. to call
    # add_custom_command(TARGET plugin ...). 
    # Target names are global, so only the first built-in plugin gets it:
    # add_custom_command(TARGET plugin ...) only works in the directory that
    # created the target.
	if (NOT TARGET plugin)
		add_custom_target(plugin ALL)
	else()
		message(STATUS "Target `plugin` already exists, so `add_custom_command(TARGET plugin ...)` in ${CMAKE_CURRENT_SOURCE_DIR} will fail to configure -- register that plugin first")
	endif()

endfunction()
