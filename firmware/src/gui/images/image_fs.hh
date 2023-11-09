#pragma once
#include "lvgl.h"
#include <map>
#include <string_view>

// 4ms
extern const lv_img_dsc_t switch_up;
extern const lv_img_dsc_t switch_down;
extern const lv_img_dsc_t switch_center;
extern const lv_img_dsc_t switch_horiz_left;
extern const lv_img_dsc_t switch_horiz_right;
extern const lv_img_dsc_t switch_horiz_center;
extern const lv_img_dsc_t button_x;
extern const lv_img_dsc_t knob9mm_x;
extern const lv_img_dsc_t knob_x;
extern const lv_img_dsc_t knob_large_x;
extern const lv_img_dsc_t knob_unlined_x;
extern const lv_img_dsc_t slider_x;
extern const lv_img_dsc_t slider_horiz_x;
extern const lv_img_dsc_t jack_x;
extern const lv_img_dsc_t led_x;

// HetrickCV/Audible
extern const lv_img_dsc_t CKSS_rot_fg;
extern const lv_img_dsc_t CKSS_rot_bg;

// Befaco/Rack
extern const lv_img_dsc_t SwitchWideHoriz_bg;
extern const lv_img_dsc_t SwitchWideHoriz_fg;
extern const lv_img_dsc_t SwitchTallVert;
extern const lv_img_dsc_t SwitchTallVertHandle;

extern const lv_img_dsc_t SwitchNarrow_bg;
extern const lv_img_dsc_t SwitchNarrowHoriz_bg;

extern const lv_img_dsc_t BefacoSwitch_0;
extern const lv_img_dsc_t BefacoSwitch_1;
extern const lv_img_dsc_t BefacoSwitch_2;

extern const lv_img_dsc_t BefacoSlidePot;
extern const lv_img_dsc_t BefacoSlidePotHandle;
extern const lv_img_dsc_t BefacoSlidePotSmall;
extern const lv_img_dsc_t BefacoSlidePotHandleSmall;
extern const lv_img_dsc_t Crossfader;
extern const lv_img_dsc_t CrossfaderHandle;
extern const lv_img_dsc_t BananutBlack;
extern const lv_img_dsc_t BananutRed;

extern const lv_img_dsc_t TL1105;
extern const lv_img_dsc_t CKD6_0;
extern const lv_img_dsc_t BefacoPush_0;
extern const lv_img_dsc_t CKSS_0;
extern const lv_img_dsc_t CKSS_1;
extern const lv_img_dsc_t VCVBezel;

extern const lv_img_dsc_t MediumLight;
// extern const lv_img_dsc_t SmallLight;

extern const lv_img_dsc_t Trimpot;
extern const lv_img_dsc_t Rogan1PRed;
extern const lv_img_dsc_t Rogan1PSGreen;
extern const lv_img_dsc_t Rogan1PSRed;
extern const lv_img_dsc_t Rogan1PSWhite;
extern const lv_img_dsc_t Rogan2SGray;
extern const lv_img_dsc_t Rogan2PSWhite;
extern const lv_img_dsc_t Rogan2PSGreen;
extern const lv_img_dsc_t Rogan2PSRed;
extern const lv_img_dsc_t Rogan3PSRed;
extern const lv_img_dsc_t Rogan3PSGreen;
extern const lv_img_dsc_t Rogan3PSWhite;
extern const lv_img_dsc_t Davies1900hRed;
extern const lv_img_dsc_t Davies1900hWhite;
extern const lv_img_dsc_t BefacoBigKnob;
extern const lv_img_dsc_t BefacoTinyKnobWhite;
extern const lv_img_dsc_t BefacoTinyKnobBlack;
extern const lv_img_dsc_t BefacoTinyKnobRed;
extern const lv_img_dsc_t BefacoTinyKnobLightGrey;
extern const lv_img_dsc_t BefacoTinyKnobDarkGrey;
extern const lv_img_dsc_t Davies1900hLightGrey;
extern const lv_img_dsc_t Davies1900hLargeLightGrey;
extern const lv_img_dsc_t Davies1900hLargeWhite;
extern const lv_img_dsc_t Davies1900hDarkGrey;
extern const lv_img_dsc_t Davies1900hLargeGrey;

// Mock read-only filesystem: given a file name, return the file contents
// TODO: replace with real filesystem (LittleFS for NORFlash)
// TODO: use /plugin/BRAND/res/components/ directories
// TODO: integrate this with module faceplates (/plugin/BRAND/res/modules/)
struct PNGFileSystem {

	static lv_img_dsc_t const *read(std::string_view filename) {
		if (mock_fs.contains(filename))
			return mock_fs[filename];
		else
			return nullptr;
	}

	static inline std::map<std::string_view, lv_img_dsc_t const *> mock_fs{
		// /plugin/4ms/res/components/
		{"switch_down.png", &switch_down},
		{"switch_up.png", &switch_up},
		{"switch_center.png", &switch_center},
		{"switch_horiz_left.png", &switch_horiz_left},
		{"switch_horiz_right.png", &switch_horiz_right},
		{"switch_horiz_center.png", &switch_horiz_center},
		{"button_x.png", &button_x},
		{"knob_x.png", &knob_x},
		{"knob_unlined_x.png", &knob_unlined_x},
		{"knob9mm_x.png", &knob9mm_x},
		{"knob_large_x.png", &knob_large_x},
		{"slider_x.png", &slider_x},
		{"slider_horiz_x.png", &slider_horiz_x},
		{"jack_x.png", &jack_x},
		{"led_x.png", &led_x},

		// /plugin/Befaco/res/components/
		{"BananutBlack.png", &BananutBlack},
		{"BananutRed.png", &BananutRed},
		//BefacoButton_0/1
		{"BefacoSlidePotHandleSmall.png", &BefacoSlidePotHandleSmall},
		{"BefacoSlidePotSmall.png", &BefacoSlidePotSmall},
		//BefacoSwitchHoriz_0/1/2: only used in Muxlicer
		{"BefacoTinyKnobBlack.png", &BefacoTinyKnobBlack},
		{"BefacoTinyKnobDarkGrey.png", &BefacoTinyKnobDarkGrey},
		{"BefacoTinyKnobLightGrey.png", &BefacoTinyKnobLightGrey},
		{"BefacoTinyKnobRed.png", &BefacoTinyKnobRed},
		{"BefacoTinyKnobWhite.png", &BefacoTinyKnobWhite},
		//CKSSThree_bg/fg
		{"Crossfader.png", &Crossfader},
		{"CrossfaderHandle.png", &CrossfaderHandle},
		{"Davies1900hBlackKnob.png", &knob_x}, //??
		{"Davies1900hDarkGreyKnob.png", &Davies1900hDarkGrey},
		{"Davies1900hLargeGreyKnob.png", &Davies1900hLargeGrey},
		{"Davies1900hLargeLightGreyKnob.png", &Davies1900hLargeLightGrey},
		{"Davies1900hLightGreyKnob.png", &Davies1900hLightGrey},
		{"SwitchNarrow.png", &SwitchNarrow_bg},
		{"SwitchNarrowHoriz_bg.png", &SwitchNarrowHoriz_bg},
		{"SwitchTallVert.png", &SwitchTallVert},
		{"SwitchTallVertHandle.png", &SwitchTallVertHandle},
		{"SwitchWideHoriz_bg.png", &SwitchWideHoriz_bg},
		{"SwitchWideHoriz_fg.png", &SwitchWideHoriz_fg},

		// {system}/ -> /plugin/Rack/ComponentLibrary
		{"BefacoSlidePot.png", &BefacoSlidePot},
		{"BefacoSlidePotHandle.png", &BefacoSlidePotHandle},
		{"BefacoBigKnob.png", &BefacoBigKnob},
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
		{"Davies1900hLargeWhiteKnob.png", &Davies1900hLargeWhite},
		{"VCVBezel.png", &VCVBezel},
		{"MediumLight.png", &MediumLight},
		{"SmallLight.png", &MediumLight}, //TODO: SmallLight image

		// hetrickcv/res/ (and/or AudibleInstruments/res?)
		{"CKSS_rot_bg.png", &CKSS_rot_bg},
		{"CKSS_rot_fg.png", &CKSS_rot_fg},
	};
};
