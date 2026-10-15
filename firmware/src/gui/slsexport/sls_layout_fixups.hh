#pragma once
#include "filebrowser/ui.h"
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

	// Patch Selector: drives sidebar fills below the title row (206/234 at 320x240)
	lv_obj_set_height(ui_DrivesPanel, lv_pct(88));

	// Edit Mapping page: full-size container
	lv_obj_set_size(ui_EditMappingContainer, lv_pct(100), lv_pct(100));

	// File Browser: path bar and file roller span the screen width
	lv_obj_set_width(ui_FileBrowserPathCont, lv_pct(100));
	lv_obj_set_width(ui_FileBrowserRoller, lv_pct(100));
}

} // namespace MetaModule
