#include "lvgl.h"

namespace MetaModule
{

extern lv_obj_t *ui_SystemPrefsCatchupTitle;
extern lv_obj_t *ui_SystemPrefsCatchupModeCont;
extern lv_obj_t *ui_SystemPrefsCatchupModeLabel;
extern lv_obj_t *ui_SystemPrefsCatchupModeDropdown;
extern lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsCont;
extern lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsLabel;
extern lv_obj_t *ui_SystemPrefsCatchupExcludeButtonsCheck;

void init_SystemPrefsCatchupPane(lv_obj_t *parentTab);

} // namespace MetaModule
