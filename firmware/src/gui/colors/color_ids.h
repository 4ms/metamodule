#pragma once

#include "lvgl.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SchemeColorId — symbolic names for every themable color in the GUI.
 * To add a color: append before METACOLOR_COUNT, then add a value for
 * every scheme in color_scheme.cc.
 */
typedef enum SchemeColorId {
	METACOLOR_RED_HIGHLIGHT = 0,
	METACOLOR_ORANGE_HIGHLIGHT,
	METACOLOR_ORANGE_BRIGHT,
	METACOLOR_YELLOW_HIGHLIGHT,
	// METACOLOR_GREEN_HIGHLIGHT,
	// METACOLOR_BLUE_HIGHLIGHT,
	METACOLOR_BLUE_INFO, // Button color for "Confirm" buttons
	METACOLOR_GREY_HIGHLIGHT,
	METACOLOR_GREY_DARKEST,
	METACOLOR_GREY_DARKER,
	METACOLOR_GREY_DARK,
	METACOLOR_GREY_44,
	METACOLOR_GREY_MEDIUM,
	METACOLOR_GREY_88,
	METACOLOR_GREY_BB,
	METACOLOR_GREY_BRIGHT,
	METACOLOR_POPUP_WARNING_BG,
	METACOLOR_KNOB_BODY,
	METACOLOR_KNOB_DOT,
	METACOLOR_KNOB_DISABLED,
	METACOLOR_INPUT_BG,
	METACOLOR_INPUT_ACCENT,
	METACOLOR_INPUT_DISABLED_BG,
	METACOLOR_BLUE_CHECKED,
	METACOLOR_TEXT_DARK,
	METACOLOR_DEBUG_GREEN,
	// METACOLOR_BROWN_HIGHLIGHT,

	/* HTML rich-text variants (used by Gui::*_text() formatters).
	   Some differ slightly from the *_HIGHLIGHT values — preserved
	   exactly to avoid visual changes during the migration. */
	METACOLOR_RED_TEXT,
	METACOLOR_ORANGE_TEXT,
	METACOLOR_YELLOW_TEXT,
	METACOLOR_GREEN_TEXT,
	METACOLOR_BLUE_TEXT,
	METACOLOR_GREY_TEXT,
	METACOLOR_LT_GREY_TEXT,

	METACOLOR_BLACK,
	METACOLOR_WHITE,
	METACOLOR_DEBUG_BORDER,

	/* Additional ids discovered during SLS C-file sweep. */
	METACOLOR_ORANGE_DARK,		/* 0xF19300 — HwTestPage data text */
	METACOLOR_GREEN_DARK,		/* 0x23973C — PatchView play-button green */
	METACOLOR_BLUE_DEEP,		/* 0x4040FF — mapping menu control arc */
	METACOLOR_GREY_80,			/* 0x808080 — disabled state text */
	METACOLOR_SCROLLBAR_ORANGE, /* 0xDF7D1A — scrollbar accent */

	/* Substitutes for lv_palette_main()/lighten() calls in firmware code. */
	METACOLOR_LV_GREY,		   /* 0x9E9E9E — lv_palette_main(LV_PALETTE_GREY) */
	METACOLOR_LV_ORANGE,	   /* 0xFF9800 — lv_palette_main(LV_PALETTE_ORANGE) */
	METACOLOR_LV_ORANGE_LIGHT, /* 0xFFB74D — lv_palette_lighten(LV_PALETTE_ORANGE, 1) */
	METACOLOR_LV_GREEN_LIGHT,  /* 0x66BB6A — lv_palette_lighten(LV_PALETTE_GREEN, 1) */
	METACOLOR_LV_RED_LIGHT,	   /* 0xEF5350 — lv_palette_lighten(LV_PALETTE_RED, 1) */

	METACOLOR_COUNT
} MetaColorId;

/* Returns 0xRRGGBB for the given color id under the active scheme. */
uint32_t scheme_color_rgb(MetaColorId id);

/* C-callable shortcut: returns lv_color_t for the given id under the active scheme.
   Used by SLS-generated .c files in place of lv_color_hex(0xXXXXXX) literals. */
static inline lv_color_t MC(MetaColorId id) {
	return lv_color_hex(scheme_color_rgb(id));
}

#ifdef __cplusplus
}
#endif
