#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * MetaColorId — symbolic names for every themable color in the GUI.
 * Pure C so .c files (e.g. SLS-generated ui.c) can use it.
 *
 * To add a color: append before METACOLOR_COUNT, then add a value for
 * every scheme in color_scheme.cc.
 */
typedef enum MetaColorId {
	METACOLOR_RED_HIGHLIGHT = 0,
	METACOLOR_ORANGE_HIGHLIGHT,
	METACOLOR_ORANGE_BRIGHT,
	METACOLOR_YELLOW_HIGHLIGHT,
	METACOLOR_GREEN_HIGHLIGHT,
	METACOLOR_BLUE_HIGHLIGHT,
	METACOLOR_BLUE_INFO,
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
	METACOLOR_BROWN_HIGHLIGHT,

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

	METACOLOR_COUNT
} MetaColorId;

/* Returns 0xRRGGBB for the given color id under the active scheme. */
uint32_t metacolor_rgb(MetaColorId id);

#ifdef __cplusplus
}
#endif
