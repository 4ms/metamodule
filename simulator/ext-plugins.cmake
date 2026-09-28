# External plugins as "built-ins" for the Simulator
#
# Example with `Venom`:
# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/Venom")
# list(APPEND ext_builtin_brand_libname "Venom")
#
# Optionally, if the brand slug is different than the Cmake library name,
# then you can specify the brand slug like this:
# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../mm-plugins/squinky")
# list(APPEND ext_builtin_brand_libname "SquinkyLabs")
# list(APPEND ext_builtin_brand_slug "squinkylabs-plug1")
#
# If you have more than one external plugin, then you have to specify the slug for ALL of them or NONE of them.
#
# No source changes are needed in the plugin: its init() is automatically renamed to
# init_BrandName and all its other symbols (including pluginInstance) are kept private.
# (Legacy plugins that #ifdef'd init() => init_BrandName() and made pluginInstance
# `extern` for the simulator still work, too.)
#
# See docs/simulator-ext-plugins.md for instructions

# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/CVfunk/metamodule")
# list(APPEND ext_builtin_brand_libname "CVfunk")
# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/Bogaudio")
# list(APPEND ext_builtin_brand_libname "BogaudioModules")

# Ext plugins can also be given on the cmake command line, which replaces any listed above.
# (The SDK's scripts/check_element_layout.py uses this):
#   -DEXT_BUILTIN_BRAND_PATHS="path1;path2" -DEXT_BUILTIN_BRAND_LIBNAMES="Lib1;Lib2"
#   -DEXT_BUILTIN_BRAND_SLUGS="slug1;slug2" (optional)
if (DEFINED EXT_BUILTIN_BRAND_PATHS)
  set(ext_builtin_brand_paths ${EXT_BUILTIN_BRAND_PATHS})
  set(ext_builtin_brand_libname ${EXT_BUILTIN_BRAND_LIBNAMES})
  set(ext_builtin_brand_slug ${EXT_BUILTIN_BRAND_SLUGS})
endif()

#
# Asset dir
#

cmake_path(SET ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")
set(ASSET_IMG_FILENAME assets.uimg)
cmake_path(APPEND ASSET_IMG_PATH "${CMAKE_CURRENT_BINARY_DIR}" "${ASSET_IMG_FILENAME}")

message("set ASSET_DIR to ${ASSET_DIR}")
message("set ASSET_IMG_PATH to ${ASSET_IMG_PATH}")

# CONFIGURE_DEPENDS re-globs at build time, so added or deleted files trigger a
# reconfigure and modified ones rebuild the asset image.
file(GLOB_RECURSE FW_ASSET_FILES CONFIGURE_DEPENDS ${FWDIR}/assets/*)

 set(EXT_PLUGIN_INIT_CALLS "")

foreach(branddir brand slug IN ZIP_LISTS ext_builtin_brand_paths ext_builtin_brand_libname ext_builtin_brand_slug)
	if ("${slug}" STREQUAL "")
		set(slug ${brand})
	endif()
	set(METAMODULE_SDK_DIR ${CMAKE_CURRENT_LIST_DIR})
	add_subdirectory(${branddir} ${CMAKE_CURRENT_BINARY_DIR}/builtins/${brand})

	target_link_libraries(${brand} PRIVATE metamodule::vcv-plugin-interface)
	target_link_libraries(${brand} PRIVATE cpputil::cpputil)
	target_compile_definitions(${brand} PRIVATE METAMODULE METAMODULE_BUILTIN)

	# Prelink the brand's static lib into a single relocatable object, rename its
	# init() entry point to init_${brand}, and localize all other symbols. This keeps
	# each plugin's internal symbols (including its `pluginInstance`) private, the same
	# as when it's dynamically loaded on hardware. Otherwise, same-named symbols in two
    # statically-linked plugins get merged by the linker, and one plugin's code
    # silently operates on another plugin's incompatible objects. See
    # localize-ext-plugin.cmake for details.
	set(brand_localized_obj ${CMAKE_CURRENT_BINARY_DIR}/builtins/${brand}_localized.o)

	# Collect the brand's own static-library dependencies (transitively), so
	# multi-library plugins (e.g. Airwindows' airwin-registry) get prelinked and
	# localized completely. Host-provided targets are excluded: references to them
	# stay undefined in the prelinked object and resolve against the host at the
	# final link (same as when the plugin is dynamically loaded on hardware).
	set(host_provided_targets
		metamodule::vcv-plugin-interface vcv-plugin-interface
		cpputil::cpputil cpputil
		metamodule::CMSISDSP CMSISDSP
	)
	set(brand_dep_archives "")
	set(brand_dep_targets "")
	set(_pending ${brand})
	set(_visited "")
	while(_pending)
		list(POP_FRONT _pending _dep)
		if (_dep IN_LIST _visited)
			continue()
		endif()
		list(APPEND _visited ${_dep})
		if (_dep IN_LIST host_provided_targets)
			continue()
		endif()
		if (NOT TARGET ${_dep})
			# A raw path to a prebuilt static lib is prelinked in, too
			if (EXISTS ${_dep} AND _dep MATCHES "\\.a$")
				list(APPEND brand_dep_archives ${_dep})
			endif()
			continue()
		endif()
		get_target_property(_dep_type ${_dep} TYPE)
		if (NOT _dep STREQUAL brand AND _dep_type STREQUAL "STATIC_LIBRARY")
			list(APPEND brand_dep_archives $<TARGET_FILE:${_dep}>)
			list(APPEND brand_dep_targets ${_dep})
		endif()
		if (_dep_type STREQUAL "INTERFACE_LIBRARY")
			get_target_property(_dep_deps ${_dep} INTERFACE_LINK_LIBRARIES)
		else()
			get_target_property(_dep_deps ${_dep} LINK_LIBRARIES)
		endif()
		if (_dep_deps)
			list(APPEND _pending ${_dep_deps})
		endif()
	endwhile()
	list(JOIN brand_dep_archives "|" brand_dep_archives_joined)

	add_custom_command(
		OUTPUT ${brand_localized_obj}
		COMMAND ${CMAKE_COMMAND}
				-DARCHIVE=$<TARGET_FILE:${brand}>
				"-DDEP_ARCHIVES=${brand_dep_archives_joined}"
				-DBRAND=${brand}
				-DOUTPUT=${brand_localized_obj}
				-DHOST_APPLE=${APPLE}
				-DCXX=${CMAKE_CXX_COMPILER}
				-DLINKER=${CMAKE_LINKER}
				-DOBJCOPY=${CMAKE_OBJCOPY}
				-P ${CMAKE_CURRENT_LIST_DIR}/localize-ext-plugin.cmake
		DEPENDS ${brand} ${brand_dep_targets} ${CMAKE_CURRENT_LIST_DIR}/localize-ext-plugin.cmake
		COMMENT "Prelinking ${brand}: renaming init() => init_${brand} and localizing internal symbols"
		VERBATIM
	)

	add_custom_target(${brand}-localized DEPENDS ${brand_localized_obj})
	add_dependencies(_vcv_ports_internal ${brand}-localized)

	target_link_libraries(_vcv_ports_internal PUBLIC ${brand_localized_obj})
	# No add_dependencies(asset-image ...) needed: the image depends on this plugin's
	# asset files and manifests, which create_plugin() records (see plugin.cmake)

	string(APPEND EXT_PLUGIN_INIT_CALLS "\textern void init_${brand}(rack::plugin::Plugin *);\n\tpluginInstance = &internal_plugins.emplace_back(\"${slug}\");\n\tinit_${brand}(pluginInstance);\n")
endforeach()

# The asset dir is rebuilt from scratch every time the image is: the firmware's assets,
# then each built-in plugin's assets and manifests. Nothing else writes to it, so it
# can't get out of step with the image (e.g. if build/assets is deleted).
#
# Defined after the loop so it can use each built-in plugin's assets, which
# create_plugin() records as it runs (see plugin.cmake)
get_property(PLUGIN_ASSET_NAMES GLOBAL PROPERTY MM_PLUGIN_ASSET_NAMES)
get_property(PLUGIN_ASSET_SOURCE_DIRS GLOBAL PROPERTY MM_PLUGIN_ASSET_SOURCE_DIRS)
get_property(PLUGIN_ASSET_MANIFESTS GLOBAL PROPERTY MM_PLUGIN_ASSET_MANIFESTS)
get_property(PLUGIN_ASSET_DEPENDS GLOBAL PROPERTY MM_PLUGIN_ASSET_DEPENDS)

set(PLUGIN_ASSET_COPY_COMMANDS "")
foreach(name source_dir manifests IN ZIP_LISTS PLUGIN_ASSET_NAMES PLUGIN_ASSET_SOURCE_DIRS PLUGIN_ASSET_MANIFESTS)
  if (IS_DIRECTORY "${source_dir}")
    list(APPEND PLUGIN_ASSET_COPY_COMMANDS
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${source_dir} ${ASSET_DIR}/${name})
  endif()
  if (manifests)
    string(REPLACE "|" ";" manifests "${manifests}")
    list(APPEND PLUGIN_ASSET_COPY_COMMANDS
      COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_DIR}/${name}
      COMMAND ${CMAKE_COMMAND} -E copy ${manifests} ${ASSET_DIR}/${name}/)
  endif()
endforeach()

add_custom_command(
  OUTPUT ${ASSET_IMG_PATH}
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${ASSET_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${FWDIR}/assets ${ASSET_DIR}
  ${PLUGIN_ASSET_COPY_COMMANDS}
  COMMAND cd ${ASSET_DIR} && ${CMAKE_COMMAND} -E tar -cf ${ASSET_IMG_PATH}.tar .
  COMMAND ${FWDIR}/flashing/uimg_header.py --name Assets ${ASSET_IMG_PATH}.tar ${ASSET_IMG_PATH}
  COMMENT "Creating assets uimg file at ${ASSET_IMG_PATH}"
  DEPENDS ${FW_ASSET_FILES} ${PLUGIN_ASSET_DEPENDS}
  VERBATIM USES_TERMINAL
)

add_custom_target(asset-image ALL
  DEPENDS ${ASSET_IMG_PATH}
)

configure_file(src/ext_plugin_builtin.hh.in ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin/ext_plugin_builtin.hh)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin)

