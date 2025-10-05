add_library(ui_lvgl STATIC)

add_subdirectory(meta5)
target_link_libraries(ui PUBLIC lvgl)
target_link_libraries(ui_lvgl PUBLIC ui)

target_sources(
  ui_lvgl
  PRIVATE prefs_section_audio.cc
          prefs_section_screensaver.cc
          prefs_section_catchup.cc
          prefs_section_fs.cc
          prefs_section_midi.cc
          prefs_section_missing_plugins.cc
          filebrowser/ui.c
          filebrowser/screens/ui_FileBrowserPage.c
)

set_source_files_properties(
  prefs_section_audio.cc
  prefs_section_screensaver.cc
  prefs_section_catchup.cc
  prefs_section_fs.cc
  prefs_section_midi.cc
  prefs_section_missing_plugins.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)
