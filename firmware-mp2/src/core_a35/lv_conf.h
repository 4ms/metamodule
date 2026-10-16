#pragma once

// LVGL config for MP2: the MP1 config, so rendering matches, with overrides for
// what the MP2 build doesn't have yet.
#include "../../../firmware/lib/lvgl/lv_conf.h"

// No filesystem yet (MP1's LVGL fs driver needs the FatFS/disk layer)
#undef LV_USE_FS_FATFS
#define LV_USE_FS_FATFS 0
#undef LV_FS_FATFS_LETTER

// FPS/CPU overlay during bring-up
#undef LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR 1
