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
    images/ui_img_1x_play1_png.c
    images/ui_img_1x_add1_png.c
    images/ui_img_1x_settings1_png.c
    images/ui_img_1x_info1_png.c
    images/ui_img_1x_knob1_png.c
    images/ui_img_1x_knob1pressed_png.c
    images/ui_img_1x_infosmall2_png.c
)

file(GLOB FONTS fonts/*.c)

# Builds for high-density screens (METAMODULE_UI_SCALE, see gui/ui_scale.h) use scaled-up GUI fonts,
# and scale the pixel sizes in the exported sources: see ../sls_hidpi.h
# (Not for the MP1 font files themselves: module displays still use them.)
if(METAMODULE_UI_SCALE)
  file(GLOB SCALED_FONTS ${CMAKE_CURRENT_LIST_DIR}/../../fonts/scaled/*.c)
  list(APPEND FONTS ${SCALED_FONTS})
  set_source_files_properties(
    ${SOURCES} PROPERTIES COMPILE_OPTIONS "-include;${CMAKE_CURRENT_LIST_DIR}/../sls_hidpi.h"
  )
endif()

add_library(ui ${SOURCES} ${FONTS} ../sls_hidpi_img.c)
