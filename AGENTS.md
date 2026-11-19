# Repository Guidelines

Paths are relative to the repo root. `make` commands say which directory to run them from.

## Project Structure & Module Organization
- `firmware/src/` contains runtime firmware (e.g., `patch_play/`, `fs/`, `gui/`) built for the A7 and M4 cores (`core_a7/`, `core_m4/`, shared messaging in `core_intercom/`); keep platform-specific code isolated per subdir.
- `firmware/system/` holds startup, fault handling and syscalls; `firmware/bootloader/` and `firmware/flashing/` hold boot images and the flashing/debug scripts; `firmware/assets/` stores UI resources and each bundled brand's `plugin.json` / `plugin-mm.json`.
- `firmware/tests/` hosts doctest suites; fixtures live under `tests/shared/`, sample patches under `tests/patches/`, and stubs for hardware headers under `tests/stubs/`.
- `simulator/` builds the same `firmware/src/gui` and patch-playing code for the host. Most GUI and patch logic can be verified there without hardware.
- `firmware/src/gui/slsexport/` was originally exported from SquareLine Studio but is now maintained by hand. Edit those files directly like any other source.
- Submodules: most of `firmware/lib/` (CoreModules, mdrivlib, cpputil, patch-serial, lvgl, thorvg...), `firmware/metamodule-plugin-sdk/`, and each brand in `firmware/vcv_ports/` are separate repos (see `.gitmodules`). A change there is a commit in that repo plus a pointer bump here, never a file edit committed to this repo. Say so before editing inside one.

## Build, Test, and Development Commands
Run these from `firmware/`.
- `make configure` once (it runs `cmake --fresh`), then `make` for every rebuild. Only re-run `configure` to change preset or options. `PRESET=min-brands` omits the bundled brands; other presets are in `firmware/CMakePresets.json`.
- `make all` already runs the unit tests (`tests` is part of `ALL`), so a separate `make tests` after it is redundant.
- `make tests` runs the firmware, patch-serial, CoreModules and SDK core-interface suites. `make dep_tests` runs cpputil and mdrivlib.
- `make -f tests/Makefile` builds and runs only the firmware suite with the host compiler: no arm toolchain or cmake configure needed. It is the fastest check for logic changes. Output is hidden unless a test fails.
- There are no per-suite make targets. All suites link into `tests/build/runtests`; filter with doctest flags, e.g. `tests/build/runtests -sf='*patch_player_tests*'` (source file) or `-tc='<test case name>'`.
- `make bootloader` and `make bootloader-dfu` build bootloader images; `make flash-app-sd` or `make flash-dfu` deploy firmware over SD or DFU.

## Simulator
Run these from `simulator/`.
- `make config-sim` once, then `make`, and `make run` to launch. `make headless` builds the no-GUI variant into `build-headless/`.
- Verify GUI changes with a screenshot instead of driving the SDL window: `./build/simulator -p patches/ --patch /<file>.yml --page <name> --screenshot /path/s.bmp --screenshot-frames 20`. Pages, `--module`, and `--input "cw:3 click back"` encoder sequences are documented in `simulator/README-screenshots.md`. Output is BMP; convert with `sips -s format png` before viewing.
- Screenshot mode skips audio, so patch modifications that go through the player (new cables, expanders) are not applied in the capture.
- If back-to-back simulator runs die with an RtMidi CoreMIDI client error, sleep 1s between runs.
- After adding or removing a module in a bundled brand, run `cmake --build build-headless --target check-plugin-jsons`. It checks that `firmware/assets/<brand>/plugin.json` and `plugin-mm.json` list every registered module, and CI fails on `main` if they don't.

## Hardware
Run these from `firmware/`.
- Flashing and attaching need the dev board connected, powered, and the Freeze jumper installed; ask before assuming it is. Setup is in `docs/firmware-loading.md` and `docs/firmware-debugging.md`.
- `make flash-openocd` resets, loads and boots over ST-LINK with no power cycle (it starts openocd if one isn't running). `make flash-t32` does the same through TRACE32. `make attach` attaches gdb without flashing.
- When scripting your own debugger loads after a soft reset: the first bulk write through the ST-LINK AXI access port silently drops words. `firmware/flashing/flash-openocd.py` primes and verifies for this reason; do the same.
- If the app boots and then silently resets after 10-30s with only `VCORERSTF` set, check the bench supply current limit before debugging firmware.

## Debugging Notes
- A crashing plugin logs `[abort] <kind>: pc ... addr ... fsr ...` and fails to load instead of hanging (`firmware/system/abort_rescue.cc`). Per-core fault breadcrumbs are in `mm_abort_fault_info`.
- Plugins load at a different address each boot. Recompute the load base from the logged pc before running `arm-none-eabi-addr2line` on a plugin's debug `.so`; a stale base gives a plausible but fictional backtrace.
- Plugin widget constructors can run with `module == nullptr`. Ported code that dereferences `getParamQuantity()` and similar without a null check crashes at plugin load.
- Any DMA stream serving a UART on the MP15 needs the undocumented `TRBUFF` bit (`DMA_SxCR` bit 20) or it can lock up under concurrent DMA traffic. See `firmware/src/console/uart_console_drain.hh`.
- Functions that plugins call must be in the plugin API symbol list, `firmware/metamodule-plugin-sdk/api-symbols.txt` (inside the SDK submodule). `make new-api-sym-list` regenerates it by scanning the export libraries; symbols the scan can't find go in `firmware/flashing/api-keep-list.txt`.

## Coding Style & Naming Conventions
- Firmware is C++23 (`-std=gnu++2b`); headers use `.hh` (C++) and `.h` (C), and all files include via quotes for local paths.
- Place code inside the `MetaModule` namespace; avoid `using namespace` in headers and prefer explicit `MetaModule::` qualifiers.
- Use snake_case for functions/variables, PascalCase for classes/structs, and tabs for indentation as in existing sources.
- Format with the `.clang-format` at the repo root. Don't reformat or refactor code outside the change.
- Favor STL containers, RAII, and `std::unique_ptr` ownership; return status flags or result structs instead of throwing exceptions.

## Testing Guidelines
- Add doctest cases in `firmware/tests/<feature>_tests.cc`. The Makefile picks up `*_tests.cc`, `*_test.cc` and `test_*.cc` by wildcard, so new test files need no registration.
- Non-test sources that a test links against (anything not header-only) must be added to `TEST_SOURCES` in `firmware/tests/Makefile`, or the link fails.
- When adding fixtures, keep them in `firmware/tests/shared/` or `firmware/tests/patches/` and clean up temporary assets after the run.
- Run the tests before submitting PRs; document any platform-specific limitations (e.g., hardware-only timing) in the PR description.

## Commit & Pull Request Guidelines
- Follow the existing history: concise, sentence-cased imperative subjects (e.g., `Fix crash if opening Jack page ...`) under ~72 characters. Submodule bumps say why: `Update sdk (docs for createDirectories)`.
- Group related changes per commit, describing firmware, tests, and tooling updates separately.
- CI does not run on pull requests, only on pushes to `main`. Local build and test results are the only verification a PR has, so list what was run (`make all`, simulator, hardware) in the description.
- Include a simulator screenshot when the GUI changes, and flag any bootloader impact for review.
- Never attribute commits or PRs to an AI tool or agent: no `Co-Authored-By:` trailers naming one, no AI tool as commit author or committer, and no "Generated with ..." lines in commit messages or PR descriptions. The human submitting the work is its author. See `CONTRIBUTING.md`.
