#pragma once
#include "lvgl.h"
#include "printf.h"
#include <string_view>

struct LVGLMemory {
	static void print_mem_usage(std::string_view tag) {
		lv_mem_monitor_t mon;
		lv_mem_monitor(&mon);
		printf_("%s: used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n\r",
				tag.data(),
				(int)mon.total_size - (int)mon.free_size,
				mon.used_pct,
				mon.frag_pct,
				(int)mon.free_biggest_size);
	}
};
