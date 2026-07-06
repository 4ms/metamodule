# GUI size audit for the MP2 "pro" screen (provisional 1280x720)

Preview any page at the pro size with the simulator:

```
simulator --screenw=1280 --screenh=720 --patch /BraidsLFOs.yml --page jackmap \
          --screenshot out.bmp    # optional headless capture
```

`firmware-mp2/src/pro/conf/screen_buffer_conf.hh` is set to 1280x720 (TBD until
the panel is chosen).

## How the GUI sizes itself

- LVGL screens (`lv_obj_create(NULL)`) auto-size to the display, and the
  SLS-exported screens use `lv_pct`/`LV_SIZE_CONTENT`/flex for most content.
- The *structural* panels, however, were designed on the 320x240 canvas with
  fixed pixel sizes (312 = canvas minus padding, 232, 228, 150-wide half
  columns, ...), plus some hand-written pages add fixed widths/offsets.
- Fix pattern: re-size those structural panels to `lv_pct`/`lv_obj_set_flex_grow`
  **after** `ui_init()`, from `gui/slsexport/sls_layout_fixups.hh` (called by
  `SlsComponentInit`) — hand-written code, so SquareLine re-exports don't wipe
  it. At 320x240 the fixups resolve to (nearly) the same pixels as the exported
  values, so the medium build is unaffected (verified by 320x240 screenshot
  comparison; a quick MP1 hardware eyeball of the touched pages is advised).

## Converted (in sls_layout_fixups.hh) — verified at 320x240 and 1280x720

| Page | What changed |
|---|---|
| Jack Map | container fills screen; two equal flex columns; lists fill below titles |
| MIDI Map | same as Jack Map |
| Main Menu | full-width bars; the three buttons share the row equally |
| Patch Selector | drives sidebar fills below the title row |
| Edit Mapping | container fills screen |
| File Browser | path bar + roller span the width |

## Remaining per-page work (needs design decisions, not just resizing)

- **Patch Selector**: the patch-list panel is a *floating* `roller_hover`
  overlay, width 210, aligned to the screen's RIGHT_MID
  (`pages/patch_selector.hh`) — at 320 it happens to cover the roller; at
  larger sizes it detaches (stray "now playing" chip at the right edge).
  Align it to the roller instead of the screen, and let the roller grow.
- **Patch View / Module View**: the module canvas draws faceplates at the
  240px-tall design scale (`draw_module.cc`, `ui_ModuleImage` 180x240,
  `ui_MappingFlexZone` 320x240). At 1280x720 modules could render ~3x — this
  is *the* headline visual decision for pro (see also `ui_ModulesSizeSlider`).
- **Slide-in menus** position by 320-based x offsets: `ui_PVSettingsMenu`
  (x=240, w=218), `ui_MVSettingsMenu` (x=220), `ui_PatchFileMenu` (x=140/200),
  `action_menu` (x=160) — convert to LV_ALIGN_RIGHT + width, and check their
  slide animations (`lv_anim` to -240 in `meta5/ui.c`).
- **Keyboards** are placed at fixed y (`description_panel.hh` y=128,
  `file_save_dialog.hh` y=108, `mapping_pane.hh` y=144, `knobset_view.hh`
  y=40) — align to bottom instead.
- **Popups/dialogs** with fixed widths (choice_popup 220/180, confirm_popup
  180, midi_pc_assign 300x185, plugin_tab load_all_popup 320, ...) — cap by
  pct, or keep fixed and center (they look fine small; decide per popup).
- **Knobset view**: absolute-positioned knob grid (52x71 panels) — regenerate
  or re-layout for larger canvas.
- **Module List**: roller panel fixed 164 wide (`module_list.hh`), image
  180x240 (canvas question again).
- **System Menu / prefs tabs**: mostly content-sized; calibration grid has
  fixed labels — check per tab.

## Global design questions for the pro GUI

1. **Scale/density**: at 1280x720 everything renders at MP1 pixel sizes (tiny
   text, 20px rows). The screen is physically larger but much denser. Options:
   a global 2x-ish theme (fonts, paddings, row heights) or an SLS re-export at
   the new canvas. The per-panel fixups above are orthogonal (they handle
   *structure*; density needs bigger fonts/styles).
2. **Module canvas scale**: how large to draw faceplates, and whether the
   modules-size slider range changes.
3. Fonts: current set is bitmap fonts at 320x240 sizes (`src/gui/fonts/`);
   larger sizes need generating.

## Screenshot-based regression flow

Before/after captures for every converted page, at both sizes:

```
for page in mainmenu patchsel patchview moduleview modulelist jackmap midimap; do
  for size in "320 240" "1280 720"; do set -- $size
    simulator --screenw=$1 --screenh=$2 --patch /BraidsLFOs.yml --page $page \
              --screenshot ${page}_$1.bmp --screenshot-frames 90
  done
done
```

The 320x240 captures must stay pixel-identical (or near) to the pre-fixup
baseline; that is the "don't break medium" check.
