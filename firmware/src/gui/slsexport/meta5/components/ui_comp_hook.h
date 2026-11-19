#ifndef _MAIN_UI_COMP_HOOK_H
#define _MAIN_UI_COMP_HOOK_H

#ifdef __cplusplus
extern "C" {
#endif

void ui_comp_KnobContainer_create_hook( lv_obj_t *comp );
void ui_comp_KnobContainerBig_create_hook( lv_obj_t *comp );
void ui_comp_MappedKnobsetitem_create_hook( lv_obj_t *comp );
void ui_comp_UnmappedSetItem_create_hook( lv_obj_t *comp );

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
