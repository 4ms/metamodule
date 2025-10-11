#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionFilesystem {
	lv_obj_t *max_patches_dropdown;

	lv_obj_t *startup_patch_check;
	lv_obj_t *startup_patch_label;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
