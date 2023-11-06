#pragma once
#include "lvgl.h"
#include <map>
#include <string_view>

// struct lv_img_dsc_t;
extern const lv_img_dsc_t CKSS_rot_fg;
extern const lv_img_dsc_t CKSS_rot_bg;
extern const lv_img_dsc_t SwitchWideHoriz_bg;
extern const lv_img_dsc_t SwitchWideHoriz_fg;
extern const lv_img_dsc_t SwitchTallVert;
extern const lv_img_dsc_t SwitchTallVertHandle;

extern const lv_img_dsc_t SwitchNarrow_bg;
extern const lv_img_dsc_t SwitchNarrowHoriz_bg;

// Mock filesystem -- TODO replace with littlefs or SD Card FATFS
struct PNGFileSystem {

	static lv_img_dsc_t const *read(std::string_view filename) {
		if (mock_fs.contains(filename))
			return mock_fs[filename];
		else
			return nullptr;
	}

	static inline std::map<std::string_view, lv_img_dsc_t const *> mock_fs{
		{"CKSS_rot_bg.png", &CKSS_rot_bg},
		{"CKSS_rot_fg.png", &CKSS_rot_fg},
		{"SwitchWideHoriz_bg.png", &SwitchWideHoriz_bg},
		{"SwitchWideHoriz_fg.png", &SwitchWideHoriz_fg},
		{"SwitchTallVert.png", &SwitchTallVert},
		{"SwitchTallVertHandle.png", &SwitchTallVertHandle},
		{"SwitchNarrow.png", &SwitchNarrow_bg},
		{"SwitchNarrowHoriz_bg.png", &SwitchNarrowHoriz_bg},
	};
};
