# Two steps to build an external plugin into the simulator:
#
# 1. Copy/paste the two `list APPEND commands` below, puttting in the path to the
#    plugin (where the CMakeLists.txt lives), and the plugin cmake library name
#
# 2. In the plugin, find the file where init(rack::Plugin*) is defined, and rename it to init_Brand
#    You can use #if defined(METAMODULE_BUILTIN) so that it's still called init() when building as a plugin for Rack or MM.
#    `Brand` in init_Brand must match the plugin cmake library name you used in step 1.

# Example with Venom:
# list(APPEND ext_builtin_brand_paths "${CMAKE_CURRENT_LIST_DIR}/../../metamodule-plugin-examples/Venom")
# list(APPEND ext_builtin_brand_libname "Venom")


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
  COMMAND cd ${FWDIR} && flashing/uimg_header.py --name Assets ${ASSET_IMG_PATH}.tar ${ASSET_IMG_PATH}
  COMMENT "Creating assets uimg file at ${ASSET_IMG_PATH}"
  DEPENDS ${ASSET_DIR}
  VERBATIM USES_TERMINAL
)

 add_custom_target(asset-image ALL 
	DEPENDS ${ASSET_IMG_PATH}
 )

 set(EXT_PLUGIN_INIT_CALLS "")

foreach(branddir brand IN ZIP_LISTS ext_builtin_brand_paths ext_builtin_brand_libname)
	set(METAMODULE_SDK_DIR ${CMAKE_CURRENT_LIST_DIR})
	add_subdirectory(${branddir} ${CMAKE_CURRENT_BINARY_DIR}/builtins/${brand})

	target_link_libraries(${brand} PRIVATE metamodule::vcv-plugin-interface)
	target_link_libraries(${brand} PRIVATE cpputil::cpputil)
	target_compile_definitions(${brand} PRIVATE METAMODULE METAMODULE_BUILTIN)

	target_link_libraries(_vcv_ports_internal PUBLIC ${brand})
	add_dependencies(asset-image ${brand}-assets)

	string(APPEND EXT_PLUGIN_INIT_CALLS "\textern void init_${brand}(rack::plugin::Plugin *);\n\tinit_${brand}(&internal_plugins.emplace_back(\"${brand}\"));")
endforeach()

configure_file(src/ext_plugin_builtin.hh.in ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin/ext_plugin_builtin.hh)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/ext_plugin)

