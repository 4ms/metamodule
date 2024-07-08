
add_library(vcv_plugin INTERFACE)

add_subdirectory(export ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin_export)

add_subdirectory(internal ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin_internal)

target_link_libraries(vcv_plugin INTERFACE vcv_plugin_internal)
target_link_libraries(vcv_plugin INTERFACE "$<LINK_LIBRARY:WHOLE_ARCHIVE,vcv_plugin_export>")

