add_library(ui_lvgl STATIC)

# MP2's screen has 4x the pixels of MP1's across, but is only about twice the size:
# scale the GUI (fonts and sizes) so it's the same physical size. See gui/ui_scale.h
# To change the scale, also regenerate the fonts: gui/fonts/generate_scaled_fonts.py
if(METAMODULE_PLATFORM STREQUAL "mp2")
  set(METAMODULE_UI_SCALE 200 CACHE STRING "GUI scale, in percent of MP1 pixel sizes")
  # lv_conf.h (default font, dpi) and all GUI code need these, and all of it uses lvgl
  target_compile_definitions(lvgl PUBLIC METAMODULE_UI_SCALE=${METAMODULE_UI_SCALE} METAMODULE_UI_SCALED_FONTS)
endif()

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
          prefs_section_button_exp_knobset.cc
          prefs_section_notifications.cc
          prefs_section_usb.cc
          filebrowser/ui.c
          filebrowser/screens/ui_FileBrowserPage.c
)

target_include_directories(ui_lvgl PRIVATE ${FWDIR}/src)
target_compile_features(ui_lvgl PRIVATE cxx_std_20)

set_source_files_properties(
  prefs_section_audio.cc
  prefs_section_screensaver.cc
  prefs_section_catchup.cc
  prefs_section_fs.cc
  prefs_section_midi.cc
  prefs_section_missing_plugins.cc
  prefs_section_button_exp_knobset.cc
  prefs_section_notifications.cc
  prefs_section_usb.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)
