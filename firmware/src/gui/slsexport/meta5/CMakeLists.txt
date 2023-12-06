SET(SOURCES components/ui_comp_knobcontainer.c
    components/ui_comp_knobcontainerbig.c
    components/ui_comp_knobsetgroup.c
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
    screens/ui_CableMapPage.c
    screens/ui_SystemMenu.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_1x_play1_png.c
    images/ui_img_1x_add1_png.c
    images/ui_img_1x_settings1_png.c
    images/ui_img_1x_info1_png.c
    images/ui_img_1x_knob1_png.c
    images/ui_img_1x_knob1pressed_png.c
    images/ui_img_1x_infosmall2_png.c
    fonts/ui_font_MuseoSansRounded50010.c
    fonts/ui_font_MuseoSansRounded50012.c
    fonts/ui_font_MuseoSansRounded70014.c
    fonts/ui_font_MuseoSansRounded70016.c
    fonts/ui_font_MuseoSansRounded90018.c
    fonts/ui_font_MuseoSansRounded90032.c
    fonts/ui_font_MuseoSansRounded90040.c)

add_library(ui ${SOURCES})
