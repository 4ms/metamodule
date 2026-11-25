set(SOURCES
    components/ui_comp_knobcontainer.c
    components/ui_comp_knobcontainerbig.c
    components/ui_comp_mappedknobsetitem.c
    components/ui_comp_unmappedsetitem.c
    screens/ui_MainMenu.c
    screens/ui_PatchSelectorPage.c
    screens/ui_PatchViewPage.c
    screens/ui_MappingMenu.c
    screens/ui_KnobSetViewPage.c
    screens/ui_EditMappingPage.c
    screens/ui_DeleteMappingPopUp.c
    screens/ui_ModuleListPage.c
    screens/ui_SystemMenu.c
    screens/ui_JackMapViewPage.c
    screens/ui_MidiMapViewPage.c
    screens/ui_HwTestPage.c
    ui.c
    ui_helpers.c
    ui_events.c
)

file(GLOB FONTS fonts/*.c)

# Builds for high-density screens (METAMODULE_UI_SCALE, see gui/ui_scale.h) use scaled-up GUI fonts
# as well as the MP1 fonts above (which module displays still use). See gui/fonts/ui_font_names.h
if(METAMODULE_UI_SCALE)
  file(GLOB SCALED_FONTS ${CMAKE_CURRENT_LIST_DIR}/../../fonts/scaled/*.c)
  list(APPEND FONTS ${SCALED_FONTS})
endif()

# Icon images: made at the GUI scale, like the fonts (images/generate_scaled_images.py)
if(METAMODULE_UI_SCALE)
  file(GLOB IMAGES images/scaled/*.c)
else()
  set(IMAGES images/ui_img_knob.c images/ui_img_knob_pressed.c)
endif()

add_library(ui ${SOURCES} ${FONTS} ${IMAGES})
