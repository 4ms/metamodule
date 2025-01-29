add_library(ui_lvgl STATIC)

add_subdirectory(meta5)
target_link_libraries(ui PUBLIC lvgl)
target_link_libraries(ui_lvgl PUBLIC ui)

target_sources(ui_lvgl PRIVATE
  prefs_menu.cc

  filebrowser/ui.c
  filebrowser/screens/ui_FileBrowserPage.c
)

set_source_files_properties(
  prefs_menu.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)
