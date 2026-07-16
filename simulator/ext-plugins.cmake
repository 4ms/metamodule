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
# Don't forget to change init() => init_BrandSlug(), and add `extern` to the pluginInstance!
# 
# See docs/simulator-ext-plugins.md for instructions

list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/CVfunk/metamodule")
list(APPEND ext_builtin_brand_libname "CVfunk")
# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/Bogaudio")
# list(APPEND ext_builtin_brand_libname "BogaudioModules")

#
# Asset dir
#

cmake_path(SET ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")
set(ASSET_IMG_FILENAME assets.uimg)
cmake_path(APPEND ASSET_IMG_PATH "${CMAKE_CURRENT_BINARY_DIR}" "${ASSET_IMG_FILENAME}")

message("set ASSET_DIR to ${ASSET_DIR}")
message("set ASSET_IMG_PATH to ${ASSET_IMG_PATH}")

add_custom_command(
  OUTPUT ${ASSET_DIR}
  COMMAND ${CMAKE_COMMAND} -E echo Copying "${FWDIR}/assets" to "${ASSET_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${FWDIR}/assets" "${ASSET_DIR}"
  COMMENT "Copying assets/ dir from ${FWDIR}/assets to ${ASSET_DIR}"
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT ${ASSET_IMG_PATH}
  COMMAND cd ${ASSET_DIR} && ${CMAKE_COMMAND} -E tar -cf ${ASSET_IMG_PATH}.tar .
  COMMAND ${FWDIR}/flashing/uimg_header.py --name Assets ${ASSET_IMG_PATH}.tar ${ASSET_IMG_PATH}
  COMMENT "Creating assets uimg file at ${ASSET_IMG_PATH}"
  DEPENDS ${ASSET_DIR}
  VERBATIM USES_TERMINAL
)

 add_custom_target(asset-image ALL 
	DEPENDS ${ASSET_IMG_PATH}
 )

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

	# Prelink the brand's static lib into a single relocatable object and localize all
	# symbols except its entry point (init_${brand}). This keeps each plugin's internal
	# symbols private, the same as when it's dynamically loaded on hardware. Otherwise,
	# same-named classes in two statically-linked plugins (e.g. a global-namespace
	# `DigitalDisplay` in both Valley and CVfunk) get merged by the linker, and one
	# plugin's vtable/methods silently operate on the other's incompatible object layout.
	set(brand_localized_obj ${CMAKE_CURRENT_BINARY_DIR}/builtins/${brand}_localized.o)

	if (APPLE)
		set(brand_exports_file ${CMAKE_CURRENT_BINARY_DIR}/builtins/${brand}_exports.txt)
		file(WRITE ${brand_exports_file} "*init_${brand}*\n")
		# -mmacosx-version-min: stamp a floor version so the final link never sees the
		# prelinked object as "newer" than its target. -Wl,-w: silence the resulting
		# version-mismatch warnings within this (purely mechanical) prelink step.
		add_custom_command(
			OUTPUT ${brand_localized_obj}
			COMMAND ${CMAKE_CXX_COMPILER} -r -nostdlib -mmacosx-version-min=11.0 -Wl,-w
					-Wl,-force_load,$<TARGET_FILE:${brand}>
					-Wl,-exported_symbols_list,${brand_exports_file}
					-o ${brand_localized_obj}
			DEPENDS ${brand} ${brand_exports_file}
			COMMENT "Prelinking ${brand} and localizing all symbols except init_${brand}"
			VERBATIM
		)
	else()
		add_custom_command(
			OUTPUT ${brand_localized_obj}
			COMMAND ${CMAKE_LINKER} -r --whole-archive $<TARGET_FILE:${brand}> --no-whole-archive -o ${brand_localized_obj}.partial.o
			COMMAND ${CMAKE_OBJCOPY} -w --keep-global-symbol=*init_${brand}* ${brand_localized_obj}.partial.o ${brand_localized_obj}
			DEPENDS ${brand}
			COMMENT "Prelinking ${brand} and localizing all symbols except init_${brand}"
			VERBATIM
		)
	endif()

	add_custom_target(${brand}-localized DEPENDS ${brand_localized_obj})
	add_dependencies(_vcv_ports_internal ${brand}-localized)

	target_link_libraries(_vcv_ports_internal PUBLIC ${brand_localized_obj})
	add_dependencies(asset-image ${brand}-assets)

	string(APPEND EXT_PLUGIN_INIT_CALLS "\textern void init_${brand}(rack::plugin::Plugin *);\n\tinit_${brand}(&internal_plugins.emplace_back(\"${slug}\"));")
endforeach()

configure_file(src/ext_plugin_builtin.hh.in ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin/ext_plugin_builtin.hh)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin)

