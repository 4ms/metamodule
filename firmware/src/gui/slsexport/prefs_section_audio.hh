#include "lvgl.h"

namespace MetaModule
{

struct PrefsSectionAudio {
	lv_obj_t *samplerate_dropdown;
	lv_obj_t *samplerate_label;

	lv_obj_t *sr_override_cont;
	lv_obj_t *sr_override_label;
	lv_obj_t *sr_override_check;

	lv_obj_t *blocksize_dropdown;
	lv_obj_t *blocksize_label;

	lv_obj_t *bs_override_cont;
	lv_obj_t *bs_override_label;
	lv_obj_t *bs_override_check;

	lv_obj_t *overrun_retries;

	void create(lv_obj_t *parent);
};

} // namespace MetaModule
