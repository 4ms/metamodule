#pragma once
#include "filebrowser/ui.h"
#include "gui/ui_scale.h"
#include "lvgl.h"
#include "ui_local.h"

namespace MetaModule
{

// The SLS-exported screens were designed on a 320x240 canvas and give the
// structural panels fixed pixel sizes (312 == canvas minus padding, 232, 228,
// half-width columns, etc). Rework those to percentages/flex-grow of their
// parents so pages lay out at any display size (the MP2 "pro" screen is
// provisionally 1280x720 -- preview with the simulator's --screenw/--screenh).
// At 320x240 these resolve to (nearly) the same pixels as the exported values.
//
// Applied after ui_init() from SlsComponentInit, so SLS re-exports don't wipe
// them. Per-page findings + remaining pages: docs/MP2-GUI-Size-Audit.md
inline void apply_sls_layout_fixups() {

	// Size of something that is `mp1_px` wide or high on MP1's 320x240 screen, and that should
	// keep the same margin to the edges of the screen (rather than stay the same physical size)
	auto screen_w = [](lv_coord_t mp1_px) { return LV_HOR_RES - ui_px(320 - mp1_px); };
	auto screen_h = [](lv_coord_t mp1_px) { return LV_VER_RES - ui_px(240 - mp1_px); };

	// Jack Map page: full-size container, two equal columns, lists fill below titles
	lv_obj_set_size(ui_JackMapViewCont, lv_pct(100), lv_pct(100));
	lv_obj_set_flex_grow(ui_JackMapLeftColumn, 1);
	lv_obj_set_height(ui_JackMapLeftColumn, lv_pct(100));
	lv_obj_set_flex_grow(ui_JackMapRightColumn, 1);
	lv_obj_set_height(ui_JackMapRightColumn, lv_pct(100));
	lv_obj_set_flex_grow(ui_JackMapLeftItems, 1);
	lv_obj_set_flex_grow(ui_JackMapRightItems, 1);

	// MIDI Map page: same structure as Jack Map
	lv_obj_set_size(ui_MidiMapViewCont, lv_pct(100), lv_pct(100));
	lv_obj_set_flex_grow(ui_MidiMapLeftColumn, 1);
	lv_obj_set_height(ui_MidiMapLeftColumn, lv_pct(100));
	lv_obj_set_flex_grow(ui_MidiMapRightColumn, 1);
	lv_obj_set_height(ui_MidiMapRightColumn, lv_pct(100));
	lv_obj_set_flex_grow(ui_MidiMapLeftItems, 1);
	lv_obj_set_flex_grow(ui_MidiMapRightItems, 1);

	// Main Menu: full-width bars; the three menu buttons share the row equally
	lv_obj_set_width(ui_MainMenuLastViewedPanel, lv_pct(100));
	lv_obj_set_flex_grow(ui_MenuPanelPatches, 1);
	lv_obj_set_flex_grow(ui_MenuPanelSave, 1);
	lv_obj_set_flex_grow(ui_MenuPanelSettings, 1);

	// Patch Selector: the drives sidebar and the patch list fill the screen below the title row,
	// and the patch list takes all the width to the right of the sidebar
	// (at 320x240, both are 206px high, and the list is 206px wide)
	lv_obj_set_height(ui_DrivesPanel, screen_h(206));
	lv_obj_set_size(ui_PatchListRoller, screen_w(206), screen_h(206));

	// Patch View: slide-in menus and the save dialog are the height of the screen
	lv_obj_set_height(ui_PatchFileMenu, screen_h(240));
	lv_obj_set_height(ui_PVSettingsMenu, screen_h(240));
	lv_obj_set_size(ui_SaveDialogCont, screen_w(316), screen_h(240));
	lv_obj_set_height(ui_SaveDialogRightCont, screen_h(240));

	// Module View: the module image and the element roller are the height of the screen
	lv_obj_set_size(ui_MappingFlexZone, screen_w(320), screen_h(240));
	lv_obj_set_height(ui_ModuleImage, screen_h(240));
	lv_obj_set_height(ui_MappingParameters, screen_h(240));
	lv_obj_set_height(ui_MVSettingsMenu, screen_h(240));

	// Module List: module preview is the height of the screen, and the list fills below the title
	lv_obj_set_height(ui_ModuleListImage, screen_h(240));
	lv_obj_set_height(ui_ModuleListRoller, screen_h(208));

	// Edit Mapping page: full-size container
	lv_obj_set_size(ui_EditMappingContainer, lv_pct(100), lv_pct(100));

	// File Browser: path bar and file roller span the screen width
	lv_obj_set_width(ui_FileBrowserPathCont, lv_pct(100));
	lv_obj_set_width(ui_FileBrowserRoller, lv_pct(100));
}

} // namespace MetaModule
