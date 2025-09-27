#include "lvgl.h"

namespace MetaModule
{

extern lv_obj_t *ui_SystemPrefsPatchSuggestTitle;
extern lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCont;
extern lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateLabel;
extern lv_obj_t *ui_SystemPrefsPatchSuggestSampleRateCheck;

extern lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCont;
extern lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeLabel;
extern lv_obj_t *ui_SystemPrefsPatchSuggestBlocksizeCheck;

void init_SystemPrefsPatchSuggestedAudioPane(lv_obj_t *parentTab);

} // namespace MetaModule

