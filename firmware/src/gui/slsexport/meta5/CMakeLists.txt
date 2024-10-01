SET(SOURCES components/ui_comp_knobcontainer.c
    components/ui_comp_knobcontainerbig.c
    components/ui_comp_mappedknobsetitem.c
    components/ui_comp_unmappedsetitem.c
    components/ui_comp.c
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
    screens/ui_HwTestPage.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_1x_play1_png.c
    images/ui_img_1x_add1_png.c
    images/ui_img_1x_settings1_png.c
    images/ui_img_1x_info1_png.c
    images/ui_img_1x_knob1_png.c
    images/ui_img_1x_knob1pressed_png.c
    images/ui_img_1x_infosmall2_png.c)

file(GLOB FONTS fonts/*.c)

add_library(ui ${SOURCES} ${FONTS})
