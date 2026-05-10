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
	METACOLOR_BLACK,
	METACOLOR_WHITE,

	METACOLOR_PRIMARY_HIGHLIGHT, // Primary highlight color. WHITE text sometimes appears over it
	METACOLOR_MODULE_SELECTED_BORDER,

	METACOLOR_BUTTON_CONFIRM, // Button bg for "Confirm" buttons. White text goes over.
	METACOLOR_BUTTON_CAUTION, // Button bg for Delete or other cautionary action button. White text goes over.
	METACOLOR_CONTROL_BG,	  // Default bg for button, slider, checkbox
	METACOLOR_CONTROL_TEXT,	  // Default text color over control_bg
	METACOLOR_DISABLED_BG,
	METACOLOR_DISABLED_TEXT,
	METACOLOR_CHECKBOX,
	METACOLOR_NOTIFICATION_BG,

	METACOLOR_GREY_BRIGHT,
	METACOLOR_GREY_DARKEST,
	METACOLOR_GREY_DARKER,
	METACOLOR_GREY_DARK,
	METACOLOR_GREY_MEDDARK,
	METACOLOR_GREY_MEDIUM,
	METACOLOR_GREY_MED_LIGHT,
	METACOLOR_GREY_BRIGHTER,
	METACOLOR_GREY_BRIGHTEST,

	METACOLOR_KNOB_BODY,
	METACOLOR_KNOB_DOT,
	METACOLOR_KNOB_DISABLED,

	METACOLOR_TEXT_DARK, // Grayed-out text

	METACOLOR_YELLOW_TEXT,
	METACOLOR_GREEN_TEXT,

	METACOLOR_ORANGE_DARK,		/* 0xF19300 — HwTestPage data text */
	METACOLOR_GREEN_DARK,		/* 0x23973C — PatchView play-button green */
	METACOLOR_BLUE_DEEP,		/* 0x4040FF — mapping menu control arc */
	METACOLOR_SCROLLBAR_ORANGE, /* 0xDF7D1A — scrollbar accent */

	/* Substitutes for lv_palette_main()/lighten() calls in firmware code. */
	METACOLOR_LV_GREY,		  /* 0x9E9E9E — lv_palette_main(LV_PALETTE_GREY) */
	METACOLOR_LV_ORANGE,	  /* 0xFF9800 — lv_palette_main(LV_PALETTE_ORANGE) */
	METACOLOR_LV_GREEN_LIGHT, /* 0x66BB6A — lv_palette_lighten(LV_PALETTE_GREEN, 1) */
	METACOLOR_LV_RED_LIGHT,	  /* 0xEF5350 — lv_palette_lighten(LV_PALETTE_RED, 1) */

	METACOLOR_DEBUG_BORDER,

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
