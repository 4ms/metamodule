# Keeps assets/BRAND/plugin.json in sync with the plugin.json in the vcv_ports/BRAND submodule.
# If they differ, the submodule's copy is copied to assets and a warning is printed.
#
# include() this file to get:
#   SYNC_PLUGIN_JSONS_COMMAND: command that does the sync (runs this file in script mode)
#   SYNC_PLUGIN_JSONS_SOURCES: the submodule plugin.json files (use as DEPENDS)

if(CMAKE_SCRIPT_MODE_FILE)
  string(REPLACE "," ";" BRANDS "${BRANDS}")
  foreach(brand ${BRANDS})
    set(src ${VCV_PORTS_DIR}/${brand}/plugin.json)
    set(dst ${ASSET_DIR}/${brand}/plugin.json)
    if(EXISTS ${src})
      execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files ${src} ${dst} RESULT_VARIABLE differs OUTPUT_QUIET ERROR_QUIET)
      if(differs)
        message(WARNING "assets/${brand}/plugin.json was out of date with vcv_ports/${brand}/plugin.json: updating it. "
                        "Check that assets/${brand}/plugin-mm.json lists any new modules.")
        file(COPY_FILE ${src} ${dst})
      endif()
    endif()
  endforeach()
  return()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/brands.cmake)

set(SYNC_PLUGIN_JSONS_SOURCES)
foreach(brand ${brands})
  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${brand}/plugin.json)
    list(APPEND SYNC_PLUGIN_JSONS_SOURCES ${CMAKE_CURRENT_LIST_DIR}/${brand}/plugin.json)
  endif()
endforeach()

# Brands are passed comma-separated because a ; would split the command
string(REPLACE ";" "," _comma_brands "${brands}")
set(SYNC_PLUGIN_JSONS_COMMAND
    ${CMAKE_COMMAND} -DBRANDS=${_comma_brands} -DVCV_PORTS_DIR=${CMAKE_CURRENT_LIST_DIR}
    -DASSET_DIR=${CMAKE_CURRENT_LIST_DIR}/../assets -P ${CMAKE_CURRENT_LIST_FILE}
)
