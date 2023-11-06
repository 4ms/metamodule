#pragma once
#include "lvgl.h"
#include <cstdio>
#include <map>
#include <string_view>

extern const lv_img_dsc_t switch_up;
extern const lv_img_dsc_t switch_down;
extern const lv_img_dsc_t switch_center;
extern const lv_img_dsc_t switch_horiz_left;
extern const lv_img_dsc_t switch_horiz_right;
extern const lv_img_dsc_t switch_horiz_center;
extern const lv_img_dsc_t button_x;

extern const lv_img_dsc_t CKSS_rot_fg;
extern const lv_img_dsc_t CKSS_rot_bg;
extern const lv_img_dsc_t SwitchWideHoriz_bg;
extern const lv_img_dsc_t SwitchWideHoriz_fg;
extern const lv_img_dsc_t SwitchTallVert;
extern const lv_img_dsc_t SwitchTallVertHandle;

extern const lv_img_dsc_t SwitchNarrow_bg;
extern const lv_img_dsc_t SwitchNarrowHoriz_bg;

extern const lv_img_dsc_t BefacoSwitch_0;
extern const lv_img_dsc_t BefacoSwitch_1;
extern const lv_img_dsc_t BefacoSwitch_2;

// These are only used in Muxslicer
// extern const lv_img_dsc_t BefacoSwitchHoriz_0;
// extern const lv_img_dsc_t BefacoSwitchHoriz_1;
// extern const lv_img_dsc_t BefacoSwitchHoriz_2;

// Mock filesystem -- TODO replace with littlefs or SD Card FATFS
struct PNGFileSystem {

	static lv_img_dsc_t const *read(std::string_view filename) {
		if (mock_fs.contains(filename))
			return mock_fs[filename];
		else
			return nullptr;
	}

	static inline std::map<std::string_view, lv_img_dsc_t const *> mock_fs{
		// 4ms/
		{"switch_down.png", &switch_down},
		{"switch_up.png", &switch_up},
		{"switch_center.png", &switch_center},
		{"switch_horiz_left.png", &switch_horiz_left},
		{"switch_horiz_right.png", &switch_horiz_right},
		{"switch_horiz_center.png", &switch_horiz_center},
		{"button_x.png", &button_x},

		// Befaco/
		{"SwitchWideHoriz_bg.png", &SwitchWideHoriz_bg},
		{"SwitchWideHoriz_fg.png", &SwitchWideHoriz_fg},
		{"SwitchTallVert.png", &SwitchTallVert},
		{"SwitchTallVertHandle.png", &SwitchTallVertHandle},
		{"SwitchNarrow.png", &SwitchNarrow_bg},
		{"SwitchNarrowHoriz_bg.png", &SwitchNarrowHoriz_bg},

		// Rack/
		{"BefacoSwitch_0.png", &BefacoSwitch_0},
		{"BefacoSwitch_1.png", &BefacoSwitch_1},
		{"BefacoSwitch_2.png", &BefacoSwitch_2},

		// HetrickCV/ and AudibleInstruments/ ???
		{"CKSS_rot_bg.png", &CKSS_rot_bg},
		{"CKSS_rot_fg.png", &CKSS_rot_fg},
	};
};
