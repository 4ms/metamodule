#include "lvgl.h"

namespace MetaModule
{

extern lv_obj_t *ui_SystemPrefsFSTitle;

extern lv_obj_t *ui_SystemPrefsFSMaxPatchesCont;
extern lv_obj_t *ui_SystemPrefsFSMaxPatchesLabel;
extern lv_obj_t *ui_SystemPrefsFSMaxPatchesDropdown;

extern lv_obj_t *ui_SystemPrefsFSStartupPatchCont;
extern lv_obj_t *ui_SystemPrefsFSStartupPatchLabel;
extern lv_obj_t *ui_SystemPrefsFSStartupPatchCheck;
extern lv_obj_t *ui_SystemPrefsFSStartupPatchName;

void init_SystemPrefsFSPane(lv_obj_t *parentTab);

} // namespace MetaModule
