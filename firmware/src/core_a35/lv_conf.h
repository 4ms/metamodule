#pragma once

// LVGL config for MP2: the MP1 config, so rendering matches, with overrides for MP2.
#include "../../lib/lvgl/lv_conf.h"

// FPS/CPU overlay during bring-up
#undef LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR 1
