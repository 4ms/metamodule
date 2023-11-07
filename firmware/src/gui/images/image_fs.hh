#pragma once
#include "gui/images/Rack/images.hh"
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
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(knob_large_x);

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

extern const lv_img_dsc_t TL1105;
extern const lv_img_dsc_t CKD6_0;
extern const lv_img_dsc_t BefacoPush_0;
extern const lv_img_dsc_t CKSS_0;
extern const lv_img_dsc_t CKSS_1;

LV_IMG_DECLARE(Trimpot);
LV_IMG_DECLARE(Rogan1PRed);
LV_IMG_DECLARE(Rogan1PSGreen);
LV_IMG_DECLARE(Rogan1PSRed);
LV_IMG_DECLARE(Rogan1PSWhite);
LV_IMG_DECLARE(Rogan2SGray);
LV_IMG_DECLARE(Rogan2PSWhite);
LV_IMG_DECLARE(Rogan2PSGreen);
LV_IMG_DECLARE(Rogan2PSRed);
LV_IMG_DECLARE(Rogan3PSRed);
LV_IMG_DECLARE(Rogan3PSGreen);
LV_IMG_DECLARE(Rogan3PSWhite);
LV_IMG_DECLARE(Davies1900hRed);
LV_IMG_DECLARE(Davies1900hWhite);
LV_IMG_DECLARE(BefacoBigKnob);
LV_IMG_DECLARE(BefacoTinyKnobWhite);
LV_IMG_DECLARE(BefacoTinyKnobBlack);
LV_IMG_DECLARE(BefacoTinyKnobRed);
LV_IMG_DECLARE(BefacoTinyKnobLightGrey);
LV_IMG_DECLARE(BefacoTinyKnobDarkGrey);
LV_IMG_DECLARE(Davies1900hLightGrey);
LV_IMG_DECLARE(Davies1900hLargeLightGrey);
LV_IMG_DECLARE(Davies1900hLargeWhite);
LV_IMG_DECLARE(Davies1900hDarkGrey);
LV_IMG_DECLARE(Davies1900hLargeGrey);

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
		{"knob_x.png", &knob_x},
		{"knob9mm_x.png", &knob9mm_x},
		{"knob_large_x.png", &knob_large_x},

		// Befaco/
		{"SwitchWideHoriz_bg.png", &SwitchWideHoriz_bg},
		{"SwitchWideHoriz_fg.png", &SwitchWideHoriz_fg},
		{"SwitchTallVert.png", &SwitchTallVert},
		{"SwitchTallVertHandle.png", &SwitchTallVertHandle},
		{"SwitchNarrow.png", &SwitchNarrow_bg},
		{"SwitchNarrowHoriz_bg.png", &SwitchNarrowHoriz_bg},
		{"BefacoTinyKnobWhite.png", &BefacoTinyKnobWhite},
		{"BefacoTinyKnobRed.png", &BefacoTinyKnobRed},
		{"BefacoTinyKnobDarkGrey.png", &BefacoTinyKnobDarkGrey},
		{"BefacoTinyKnobLightGrey.png", &BefacoTinyKnobLightGrey},
		{"BefacoTinyKnobBlack.png", &BefacoTinyKnobBlack},
		{"BefacoBigKnob.png", &BefacoBigKnob},
		{"Davies1900hDarkGreyKnob.png", &Davies1900hDarkGrey},
		{"Davies1900hLightGreyKnob.png", &Davies1900hLightGrey},
		{"Davies1900hLargeGreyKnob.png", &Davies1900hLargeGrey},
		{"Davies1900hLargeLightGreyKnob.png", &Davies1900hLargeLightGrey},

		// Rack/
		{"BefacoSwitch_0.png", &BefacoSwitch_0},
		{"BefacoSwitch_1.png", &BefacoSwitch_1},
		{"BefacoSwitch_2.png", &BefacoSwitch_2},
		{"TL1105.png", &TL1105},
		{"CKD6_0.png", &CKD6_0},
		{"BefacoPush_0.png", &BefacoPush_0},
		{"CKSS_0.png", &CKSS_0},
		{"CKSS_1.png", &CKSS_1},
		{"Trimpot.png", &Trimpot},
		{"Rogan1PRed.png", &Rogan1PRed},
		{"Rogan1PSGreen.png", &Rogan1PSGreen},
		{"Rogan1PSRed.png", &Rogan1PSRed},
		{"Rogan1PSWhite.png", &Rogan1PSWhite},
		{"Rogan2SGray.png", &Rogan2SGray},
		{"Rogan2PSWhite.png", &Rogan2PSWhite},
		{"Rogan2PSGreen.png", &Rogan2PSGreen},
		{"Rogan2PSRed.png", &Rogan2PSRed},
		{"Rogan3PSRed.png", &Rogan3PSRed},
		{"Rogan3PSGreen.png", &Rogan3PSGreen},
		{"Rogan3PSWhite.png", &Rogan3PSWhite},
		{"Davies1900hRedKnob.png", &Davies1900hRed},
		{"Davies1900hWhiteKnob.png", &Davies1900hWhite},
		{"Davies1900hBlackKnob.png", &knob_x}, //??
		{"Davies1900hLargeWhiteKnob.png", &Davies1900hLargeWhite},

		// HetrickCV/ and AudibleInstruments/ ???
		{"CKSS_rot_bg.png", &CKSS_rot_bg},
		{"CKSS_rot_fg.png", &CKSS_rot_fg},
	};
};
