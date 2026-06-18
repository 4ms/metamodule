# Simulator screenshots & headless initial state

The simulator can boot directly into a chosen page with a patch already loaded,
render a few frames, dump the screen to an image file, and exit — all without
manually driving the GUI. This is intended for visual verification of GUI
changes (by a human or by automation/CI) without needing to navigate menus or
worry about the SDL window being obscured by other windows.

## Quick start

Run from the `simulator/` directory (paths below are relative to it):

```sh
# Build the simulator (assets are produced by the firmware build)
ninja -C build simulator

# Load a patch, jump to the Jacks page, capture, and exit
./build/simulator -p patches/ \
    --patch /test-cable-disp.yml \
    --page jackmap \
    --screenshot /tmp/shot.bmp \
    --screenshot-frames 20

# Capture is written as BMP. Convert to PNG to view (macOS):
sips -s format png /tmp/shot.bmp --out /tmp/shot.png
# ...or cross-platform with ImageMagick:
# convert /tmp/shot.bmp /tmp/shot.png
```

The screen is 320x240. The capture is taken from the last fully-rendered LVGL
framebuffer, so it is unaffected by the SDL window being hidden, minimized, or
covered by other windows.

## Options

These options are added on top of the simulator's normal options
(`-z/--zoom`, `-p/--sdcarddir`, `-f/--flashdir`, `-s/--assets`, etc.):

| Option | Description | Default |
| --- | --- | --- |
| `--patch <file>` | Patch file on the SD-card volume to load on startup, e.g. `/test-cable-disp.yml`. Path is relative to the SD-card root (`-p/--sdcarddir`, default `patches/`). | (none) |
| `--page <name>` | Page to jump to on startup (see table below). | (none) |
| `--screenshot <file>` | Capture the screen to this **BMP** file after rendering, then exit. If omitted, the simulator runs normally. | (none) |
| `--screenshot-frames <N>` | Number of UI update cycles (~`N`×10 ms) to run before capturing. | `120` |

`--patch` and `--page` also work without `--screenshot`: the simulator will load
the patch / jump to the page and then run interactively as usual. This is handy
for jumping straight to the screen you're working on.

### Page names

| `--page` value | Page |
| --- | --- |
| `mainmenu` | Main menu |
| `patchsel` | Patch selector |
| `patchview` | Patch view |
| `moduleview` | Module view |
| `modulelist` | Module list |
| `jackmap` | Jack map (panel in/out mappings) |
| `midimap` | MIDI map |

(Unknown names print a warning and are ignored. All pages use the same jump
mechanism, but some — e.g. `moduleview` and `knobmap` — need page arguments
(a target module/param) to render anything useful when entered directly, which
this tool does not currently supply. `jackmap` renders from just a loaded patch
and is the verified target; `midimap`/`patchview` should behave similarly.)

## Notes & caveats

- **Choosing `--screenshot-frames`.** Labels that are too wide for their column
  use `LV_LABEL_LONG_SCROLL` and start scrolling shortly after the page appears.
  Use a small value (e.g. `20`) to capture text near its start; the default
  `120` lets animations/notifications settle but long names will have scrolled.
- **Output format.** Capture writes BMP (no extra image-library dependency).
  Convert with `sips` (macOS) or ImageMagick `convert` as shown above. The
  agent reading the image needs PNG/JPG, not BMP.
- **Audio is skipped** in screenshot mode, so no audio device is required for a
  capture.
- The capture is the LVGL framebuffer, not the SDL window contents, so other
  windows covering the simulator do not affect the result.

## How it works (for maintainers)

- `lv_port_disp_capture(const char *path)` in `lvgl_drv/lv_sdl_disp.c` saves the
  most recently flushed framebuffer (the driver uses `full_refresh = 1`, so each
  flush holds the whole screen) to a BMP via SDL. Declared in
  `lvgl_drv/lv_port_disp.h`.
- `Ui::load_patch()` and `Ui::goto_page()` (`src/ui.{hh,cc}`) load a patch
  synchronously (the simulator's file storage services requests inline) and jump
  to a page via `PageManager::request_page()` (a thin public wrapper added in the
  firmware's `src/gui/pages/page_manager.hh`).
- The startup/screenshot flow is wired in `src/main.cc`; option parsing is in
  `src/settings.hh`.
