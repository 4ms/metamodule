# Color Scheme Migration — Handoff

Migration to runtime-selectable GUI color schemes for accessibility (high-contrast for visually impaired users) and customization. Started in branch `color-schemes`.

## Goal

1. Centralize every color used in the GUI behind a `MetaColorId` enum.
2. Make C and C++ files reference colors by id, not by hex literal.
3. Support multiple schemes selectable at runtime via a prefs UI.
4. Preserve "Default" visual output identical to current GUI.

## Architecture (already in place)

```
src/gui/colors/
├── color_ids.h            — pure C enum + extern "C" uint32_t metacolor_rgb(MetaColorId)
├── color_scheme.hh        — C++ ColorScheme struct, mc(id) helper, Scheme:: namespace
├── color_scheme.cc        — Default scheme (matches today's hex values), Scheme::set/current/count/name
├── color_styles.h         — C accessors: metacolor_style_bg(id), _text, _border, _outline, _line, _arc, _shadow, _img_recolor
├── color_styles.hh        — C++ wrappers: mc_bg(id), mc_text(id), etc. + ColorStyles::init/reapply_scheme
└── color_styles.cc        — backing storage for ~136 atomic styles (8 props × MetaColorId count)
```

**Atomic styles** are one shared `lv_style_t` per (property, color id). Widgets attach them via `lv_obj_add_style(obj, mc_bg(METACOLOR_X), state)`. A scheme change mutates each style and calls `lv_obj_report_style_change(NULL)` so every dependent widget repaints — no per-page restyle code needed.

**Wiring:** `src/gui/ui.hh:60` calls `ColorStyles::init()` once at startup, immediately before `Gui::init_lvgl_styles()`. Both files are in `src/CMakeLists.txt` under `main.elf` and the `-Wno-deprecated-enum-enum-conversion` suppression list.

**Naming choice:** the namespace is `MetaModule::Scheme`, NOT `Colors` — there's a pre-existing global `struct Colors` in `lib/cpputil/util/colors.hh` (used by `enosc/ui.hh`, `knobset_button.hh`, `redraw_light.hh`, `rgbled.hh`). Don't reintroduce a `Colors` namespace.

## Conversion policy

For every `lv_obj_set_style_*_color()` call you encounter:

| Pattern | Action |
|---|---|
| Static color, set once at widget construction | Convert to `lv_obj_add_style(obj, mc_<prop>(METACOLOR_X), state)`. Removes local style; theme propagation is automatic via LVGL's invalidation. |
| Static color, but set inside a function called repeatedly based on runtime state (e.g., `update_knob()`, `enable()/disable()`) | Keep `lv_obj_set_style_*_color(...)`, replace value with `mc(METACOLOR_X)`. Theme propagation requires re-running the function (typically on next page transition or scheme-change-triggered reload). |
| Color computed from runtime data (`Gui::get_knob_color(id)`, `Gui::palette_main[i]`, `Gui::mapped_jack_color(...)`, `lv_palette_lighten(...)`, `el.color`) | Leave as-is for now. Becomes themable when the **palette migration step** lands (see Remaining work). |
| `lv_color_white()` / `lv_color_black()` as a value | Replace with `mc(METACOLOR_WHITE)` / `mc(METACOLOR_BLACK)`. |
| `lv_color_black().full == something.full` (literal-black comparison, not theme-aware) | KEEP as `lv_color_black()` — it's a runtime test against LVGL's literal black. There is one such case in `ui_local.cc:117` — preserve the pattern. |
| `lv_color_make_rgb565(r, g, b)` | Treat the (r,g,b) hex as a packed `0xRRGGBB`, replace with `mc(METACOLOR_X)`. |
| Hex literal with 1–2 bit difference from an existing id (e.g., `0xE91C25` vs `0xea1c25`, `0xFF8918` vs `0xfd8b18`, `0xFB8B18` vs `0xfd8b18`) | Consolidate to the existing id — visually indistinguishable in RGB565. |
| Genuinely unique hex value | Add a new `METACOLOR_*` entry at the end of the enum (before `METACOLOR_COUNT`) AND assign it in `make_default_scheme()` in `color_scheme.cc`. |

Adding a new id REQUIRES updating both files. Forgetting `make_default_scheme()` leaves the entry with garbage rgb. Always update both.

## Current `MetaColorId` catalog

The full enum is in `src/gui/colors/color_ids.h`. As of handoff, ~35 entries. Default values in `src/gui/colors/color_scheme.cc::make_default_scheme()`.

Reference table (values in 0xRRGGBB):

```
METACOLOR_RED_HIGHLIGHT       0xea1c25  (also covers 0xE91C25)
METACOLOR_ORANGE_HIGHLIGHT    0xfd8b18  (also covers 0xFB8B18, 0xFF8918)
METACOLOR_ORANGE_BRIGHT       0xfdb818
METACOLOR_YELLOW_HIGHLIGHT    0x8bfd18
METACOLOR_GREEN_HIGHLIGHT     0x00a551
METACOLOR_BLUE_HIGHLIGHT      0x188bfd
METACOLOR_BLUE_INFO           0x2095f6
METACOLOR_GREY_HIGHLIGHT      0xaaaaaa
METACOLOR_GREY_DARKEST        0x222222
METACOLOR_GREY_DARKER         0x333333
METACOLOR_GREY_DARK           0x555555
METACOLOR_GREY_44             0x444444
METACOLOR_GREY_MEDIUM         0x777777
METACOLOR_GREY_88             0x888888  (also covers 0x999999)
METACOLOR_GREY_BB             0xbbbbbb
METACOLOR_GREY_BRIGHT         0xeeeeee
METACOLOR_BROWN_HIGHLIGHT     0xa26e3e
METACOLOR_RED_TEXT            0xea1c25
METACOLOR_ORANGE_TEXT         0xfd9b18  (HTML rich-text variant)
METACOLOR_YELLOW_TEXT         0xd7ff6a  (HTML rich-text variant)
METACOLOR_GREEN_TEXT          0x00a551
METACOLOR_BLUE_TEXT           0x188bfd
METACOLOR_GREY_TEXT           0xaaaaaa
METACOLOR_LT_GREY_TEXT        0xcccccc
METACOLOR_BLACK               0x000000
METACOLOR_WHITE               0xffffff
METACOLOR_DEBUG_BORDER        0xff0000
METACOLOR_KNOB_BODY           0x666666
METACOLOR_KNOB_DOT            0xdddddd
METACOLOR_KNOB_DISABLED       0xb4b2b4
METACOLOR_INPUT_BG            0x202020
METACOLOR_INPUT_ACCENT        0x202328
METACOLOR_INPUT_DISABLED_BG   0x404040
METACOLOR_BLUE_CHECKED        0x4067d3  (also covers 0x4165D5)
METACOLOR_TEXT_DARK           0x111111
METACOLOR_DEBUG_GREEN         0x00ff00
METACOLOR_POPUP_WARNING_BG    0xe1e878
```

## What's done

### Step 1: infrastructure
- Created the 6 files under `src/gui/colors/`.
- Wired `ColorStyles::init()` into `src/gui/ui.hh:60`.
- Added new `.cc` files to `src/CMakeLists.txt` (line ~133) and to its `set_source_files_properties(... -Wno-deprecated-enum-enum-conversion ...)` block.

### Step 2: styles.hh internals
- `Gui::red_highlight`, `orange_highlight`, `yellow_highlight`, `green_highlight`, `grey_highlight` are now inline-initialized via `mc(METACOLOR_*)` (safe — `Scheme::active` and `schemes` are constant-initialized in `color_scheme.cc`, no SIOF).
- These are also reassigned at the top of `Gui::init_lvgl_styles()` so a runtime scheme change refreshes them.
- `Gui::*_text()` HTML formatters now build escape strings from `html_code(METACOLOR_*_TEXT)`.
- `Gui::grey_color_html`, `brown_highlight_html`, `orange_highlight_html` switched from `string_view` to `std::string`, populated via `html_code(...)`. External `.data()` users still work.
- All `lv_color_hex(0x...)` literals inside `init_lvgl_styles()` replaced with `mc(METACOLOR_*)`.
- **Deferred to a later step:** `lv_color_white()`/`lv_color_black()` calls in `init_lvgl_styles()`, the constexpr palette arrays (`palette_main`, `jack_palette`, etc.), and `LV_STYLE_CONST_*` slider props.

### Step 3 (partial — atomic-style sweep): files completed

| File | Notes |
|---|---|
| `src/gui/pages/confirm_popup.hh` | All 27 hardcodes → atomic styles. |
| `src/gui/pages/missing_plugin_scan.hh` | 1 hex + 2 `Gui::orange_highlight` value uses → atomic. |
| `src/gui/pages/prefs_tab.hh` | 2 `Gui::orange_highlight` value uses → atomic. |
| `src/calibrate/calibration_routine.hh` | 2 `Gui::orange_highlight` value uses → atomic. |
| `src/gui/elements/draw.hh` | 4 static hex → atomic; 2 dynamic (el.color) kept. |
| `src/gui/elements/screensaver.hh` | 2 hex → atomic. |
| `src/gui/pages/base.hh` | 1 `lv_color_black()` → atomic. |
| `src/gui/helpers/roller_hover_text.hh` | 2 hex → atomic. |
| `src/gui/pages/knobset_view.hh` | 3 hex (dynamic-context) → `mc()`-parameterized. |
| `src/gui/pages/knobmap.hh` | 1 atomic + 4 `mc()`-parameterized. |
| `src/gui/pages/fullscreen_graphic.hh` | 2 → atomic. |
| `src/gui/pages/plugin_tab.hh` | 2 → atomic; new id `POPUP_WARNING_BG`. |
| `src/gui/pages/system_tab.hh` | 1 → atomic. |
| `src/gui/module_menu/plugin_module_menu.hh` | 1 → atomic. |
| `src/gui/pages/module_view/action_menu.hh` | 1 → atomic. |
| `src/gui/pages/module_view/mapping_pane.hh` | 4 → mixed. |
| `src/gui/pages/module_view/mapping_pane_list.hh` | 8 → mixed. |
| `src/gui/slsexport/comp_init.hh` | 5 (theme primary + slider EDITED state) → `mc()`-parameterized. |
| `src/gui/slsexport/ui_local.cc` | ~140 conversions. All hex literals + `lv_color_make_rgb565` + `lv_color_white()/black()` (except one literal-black comparison) → `mc()`. Kept `lv_obj_set_style_*_color()` calls — these helpers run once per widget at construction; theme propagation will require triggering a re-run on scheme change (page reload). |

### Step 3 (continued): SLS C-file sweep — DONE

`MC(METACOLOR_X)` C-callable shortcut added to `src/gui/colors/color_ids.h` (now also includes `lvgl.h`). `target_include_directories(ui PUBLIC ${CMAKE_SOURCE_DIR}/src)` added to `src/gui/slsexport/CMakeLists.txt` so SLS .c files can `#include "gui/colors/color_ids.h"`.

| File | MC() calls |
|---|---:|
| `meta5/screens/ui_DeleteMappingPopUp.c` | 2 |
| `meta5/components/ui_comp_unmappedsetitem.c` | 5 |
| `meta5/screens/ui_JackMapViewPage.c` | 6 (active; 5 commented-out hex literals left as-is) |
| `meta5/screens/ui_MidiMapViewPage.c` | 8 |
| `meta5/components/ui_comp_mappedknobsetitem.c` | 9 |
| `meta5/components/ui_comp_knobcontainer.c` | 14 |
| `meta5/components/ui_comp_knobcontainerbig.c` | 14 |
| `meta5/screens/ui_ModuleListPage.c` | 15 |
| `meta5/screens/ui_MainMenu.c` | 22 |
| `filebrowser/screens/ui_FileBrowserPage.c` | 25 |
| `meta5/screens/ui_HwTestPage.c` | 38 |
| `meta5/screens/ui_PatchSelectorPage.c` | 51 |
| `meta5/screens/ui_KnobSetViewPage.c` | 78 |
| `meta5/screens/ui_SystemMenu.c` | 97 |
| `meta5/screens/ui_EditMappingPage.c` | 144 |
| `meta5/screens/ui_PatchViewPage.c` | 326 |
| `meta5/screens/ui_MappingMenu.c` | 424 |

Total ~1278 SLS conversions across 17 files. New ids added to the catalog (color_ids.h + color_scheme.cc):
`METACOLOR_ORANGE_DARK` (0xf19300), `METACOLOR_GREEN_DARK` (0x23973c), `METACOLOR_BLUE_DEEP` (0x4040ff), `METACOLOR_GREY_80` (0x808080), `METACOLOR_SCROLLBAR_ORANGE` (0xdf7d1a), `METACOLOR_KNOBSET_B` (0xfff200), `METACOLOR_KNOBSET_C` (0x00aeee), `METACOLOR_KNOBSET_D` (0xf66194), `METACOLOR_KNOBSET_E` (0xffa529).

`0x00A552` consolidated to `METACOLOR_GREEN_HIGHLIGHT` (1-bit diff from 0x00a551, identical in RGB565). `0xFB8B19` consolidated to `METACOLOR_ORANGE_HIGHLIGHT`. `0x999999` consolidated to `METACOLOR_GREY_88`.

Cumulative: ~1488 conversions across 36 files. All five external `Gui::*_highlight` value uses converted.

## What remains

### Remaining .hh files — DONE (palette migration unblocked these)

- `src/gui/pages/knobset_view_buttonexp.hh` — converted: 4 hex literals + `lv_color_white()` → `mc()`-parameterized.
- `src/gui/pages/hardware_test_popup.hh` — converted: `lv_color_white()` → `mc(METACOLOR_WHITE)`. `Gui::palette_main[i]` accesses left as-is (already themable through palette migration).
- `src/gui/pages/firmware_update_tab.hh` — converted: 6 `lv_palette_lighten(...)` → `mc(METACOLOR_LV_*_LIGHT)`.
- `src/gui/elements/map_ring_drawer.hh` — no changes needed; all 3 setters use a runtime `color` parameter sourced from `Gui::get_knob_color()` / `mapped_jack_color()`, which now reads from the themable palette.
- `src/gui/elements/redraw_light.hh` — skipped (fundamentally dynamic img_recolor).
- `src/gui/dyn_display_drawer.hh` — skipped (only commented-out usage).

### SLS-generated C files

DONE — see "Step 3 (continued): SLS C-file sweep" above.

### LVGL palette migration — DONE

`ColorScheme` now carries `uint32_t palette_main[19]` and `uint32_t jack_palette[8]`. `Gui::palette_main` and `Gui::jack_palette` are no longer `constexpr` — they're zero-initialized arrays of `lv_color_t` repopulated from the active scheme at the top of `Gui::init_lvgl_styles()`. The derived `cable_palette`, `knob_palette`, and `knob_disabled_palette` are also rebuilt from `palette_main` in the same call (this also fixes a latent bug: re-running `init_lvgl_styles` previously kept darkening `knob_disabled_palette` because the HSV transform compounded).

`Scheme::active_scheme()` was added to `color_scheme.hh`/`.cc` as the access point.

5 new metacolors substitute LVGL palette function calls in firmware code:
- `METACOLOR_LV_GREY` (0x9E9E9E) replaces `lv_palette_main(LV_PALETTE_GREY)` (1 use in styles.hh).
- `METACOLOR_LV_ORANGE` (0xFF9800) replaces `lv_palette_main(LV_PALETTE_ORANGE)` (2 uses in styles.hh).
- `METACOLOR_LV_ORANGE_LIGHT` (0xFFB74D) replaces `lv_palette_lighten(LV_PALETTE_ORANGE, 1)` (1 use in styles.hh).
- `METACOLOR_LV_GREEN_LIGHT` (0x66BB6A) replaces `lv_palette_lighten(LV_PALETTE_GREEN, 1)` (3 uses in firmware_update_tab.hh).
- `METACOLOR_LV_RED_LIGHT` (0xEF5350) replaces `lv_palette_lighten(LV_PALETTE_RED, 1)` (3 uses in firmware_update_tab.hh).

Remaining `lv_palette_main()` calls in `comp_init.hh` and `meta5/ui.c` are LVGL theme-init parameters; intentionally left because they pre-cache theme primary colors. Updating these on scheme change would require re-running `lv_theme_default_init()`, which is currently startup-only (acceptable per "Known limitations" below).

### Step 4: Prefs UI for scheme selection

- Add `ColorSchemeSettings { uint8_t scheme_id; }` to `src/user_settings/settings.hh` (existing pattern: `audio_settings.hh`, `screensaver_settings.hh`, etc.).
- Wire serialization in `src/user_settings/settings_serialize.cc` and `settings_parse.cc` (search for any existing setting like `screensaver` and follow that pattern).
- Add UI to `src/gui/pages/prefs_tab.hh` — a roller listing `Scheme::name(i)` for `i < Scheme::count()`, with change callback that calls `Scheme::set(idx)` then `Gui::init_lvgl_styles()` and (optionally) reloads the current page so widgets that use `lv_obj_set_style_*_color()` (rather than atomic styles) pick up the new scheme.
- On boot, after `Settings::read_settings(...)` succeeds in `Ui::Ui()` (around `src/gui/ui.hh:62`), call `Scheme::set(settings.color_scheme.scheme_id); Gui::init_lvgl_styles();` to apply the persisted scheme.

### Step 5: Add a second scheme

Once the prefs UI works, add a `make_high_contrast_scheme()` to `color_scheme.cc` and append it to `schemes[]`. Black bg, pure white text, saturated accents. This is the user-facing accessibility win.

### Step 6: Lint / regression guard

Add a CI check (or pre-commit grep) to catch reintroduced hardcodes:
```bash
grep -rEn 'lv_color_hex\(0x' src/gui/ src/calibrate/
grep -rEn 'lv_obj_set_style_[a-z_]*_color\b' src/gui/ src/calibrate/
```
Allow-list legitimate dynamic uses (palette lookups, `update_light_style`, the literal-black comparison in `ui_local.cc:117`, the `get_buttonexp_color()` / `get_buttonexp_textcolor()` helpers in `styles.hh`).

## Concrete next-session priority order

1. **SLS C-file sweep** — DONE (see "Step 3 (continued)" above).

2. **Palette migration** — DONE.

3. **Sweep deferred .hh files** — DONE.

4. **Prefs UI + persistence** (Step 4 above).

5. **Add high-contrast scheme** (Step 5 above).

6. **Lint guard** (Step 6 above).

## Build & verify

```sh
cd /Users/dann/4ms/stm32/metamodule/firmware/build
ninja main.elf
```

Fast incremental builds. Configure runs automatically via ninja deps. After every batch of conversions, build clean before moving on. The build directory is not checked in — if missing, run `cmake -B build -GNinja` first.

## Known limitations / TODOs

- **Theme propagation for `lv_obj_set_style_*_color()` callsites:** widgets styled via local-style setters (rather than atomic styles) won't update on a runtime scheme change until the function that styles them re-runs. The ui_local.cc helpers fall in this category. Mitigation in step 4: trigger a page reload on scheme change. The infrastructure already calls `lv_obj_report_style_change(NULL)` on scheme change (in `Scheme::set()` via `ColorStyles::reapply_scheme()`) — that handles the atomic-style widgets cleanly.
- **`LV_STYLE_CONST_CPP` slider props in `styles.hh`:** can't be re-themed because they're constexpr. Convert to runtime-init style if/when needed.
- **`lv_theme_default_init()` in `comp_init.hh`:** runs once at startup. The theme primary color will not update on scheme change unless this function re-runs. Acceptable for now (page reload handles it).
- **Static init order:** `Gui::*_highlight` data members in `styles.hh` are inline-initialized via `mc(METACOLOR_*)` at static init time. This is safe ONLY because `Scheme::active` and `schemes[]` are constant-initialized in `color_scheme.cc` (constant init runs before dynamic init per `[basic.start.static]`). Don't change `active` or `schemes[]` to require dynamic initialization without re-thinking this.

## Resuming on another machine

1. Clone the repo and check out branch `color-schemes`. Pull latest. Verify `git status` matches `M lib/mdrivlib` plus the new files under `src/gui/colors/` and the converted files listed above.
2. Build to confirm everything is green: `cd build && ninja main.elf`. If `build/` is missing, run `cmake -B build -GNinja` from the firmware root first.
3. Open this file (`COLOR_SCHEME_MIGRATION.md`) and use it as the starting context for a new Claude session. Suggested kickoff prompt:

> Read `COLOR_SCHEME_MIGRATION.md` at the project root, then continue from "Concrete next-session priority order" — specifically item 1 (SLS C-file sweep). Start by adding the `MC()` C-callable shortcut to `color_ids.h`, verifying include paths in `slsexport` CMakeLists, and converting one small SLS file end-to-end (`src/gui/slsexport/meta5/screens/ui_DeleteMappingPopUp.c` is a good first target). Build clean before moving to the next file. After every ~5 files, build and report.

4. The conversion is mechanical but mind the conversion-policy table in this doc — most setters in SLS files are static (one-shot widget construction), so the `lv_color_hex(0xXX)` → `MC(METACOLOR_X)` substitution is straightforward. Watch for `lv_color_make(...)` / `LV_COLOR_MAKE(...)` variants too — same treatment.
