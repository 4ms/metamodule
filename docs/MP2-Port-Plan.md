# MetaModule MP2 (STM32MP25x) Port — Project Plan

*Status: draft for team review — July 2026*

## Context

MetaModule is moving to a new hardware revision based on the STM32MP25x (2×Cortex-A35 AArch64 + Cortex-M33; M0+ unused) replacing the STM32MP153 (2×Cortex-A7 AArch32 + M4). The new unit uses LTDC (possibly MIPI DSI) with a larger screen instead of the SPI display. Sales move to MP2; MP1 ("medium") becomes maintenance-only (bug fixes + SDK updates), with a real transition period where both are maintained. Plugins must run on both platforms long-term. Hardware isn't finalized (no final pin list yet) — this plan sequences what can start now vs. what waits for hardware. The MP2 unit's codename is "pro".

### Where things stand

- **mdrivlib** selects targets via defines (`-DSTM32MP1 -DCORE_CA7`), `drivers/stm32xx.h` + `drivers/arch.hh`, and include-path resolution of well-known header names (`drivers/rcc.hh`, `cache.hh`, `interrupt_control.hh`, …) into `target/<family>/` and `target/<family>_<core>/` dirs. The `stm32mp2` branch was one commit (stm32xx.h cases); it has been rebased onto main and the `target/stm32mp2*` skeleton started.
- **stm32mp2-baremetal** has verified A35 EL3-secure examples: boot/C-runtime, GIC nested interrupts, AArch64 MMU, HPDMA m2m + cache maintenance, SAI audio via HPDMA linked-list circular + I2C **PCM3168** (MetaModule's exact codec), USB device (DWC3 CDC-ACM), dual-A35 SMP — and on the `usb-xhci` branch, verified XHCI USB **host** + dual-role switching + USB MIDI (targets both the ST EV1 and the 4ms devboard v0.1). Its `shared/` code is already near-mdrivlib style (same `register_access.hh` pattern, InterruptManager, FPin).
- **metamodule** firmware selects its single board ("medium") purely by include path: `firmware/src/medium/conf/*.hh`, no `#ifdef MEDIUM`. `firmware/` is a single-toolchain (arm-none-eabi) CMake project building `main.elf` (A7) + `main_m4.elf` (M4); the simulator is a sibling CMake project consuming `../firmware` sources via curated source lists + stubs. The M4 owns controls, ALL filesystem, and wifi; IPC is HSEM + shared-memory structs (`src/core_intercom/`). Plugin loading is a hand-written ELF relocator handling 32-bit ARM relocs only (`src/dynload/elf_process/elf_relocator.hh`).

## Decisions (confirmed)

1. **Repo layout: sibling `firmware-mp2/` project in this repo** (hybrid of "new build target" and "new dir like simulator"). A single CMake project for both platforms is mechanically impossible: MP2 needs two toolchains (aarch64-none-elf for A35, arm-none-eabi for M33) while today's firmware project is single-toolchain for A7+M4. A separate repo would force double-committing every shared fix (~40 GUI pages, patch engine, params, plugin adaptors) for the whole transition. So: a new sibling CMake project consuming `firmware/src/` the way `simulator/` already does — include paths + a new canonical `firmware/src/shared_sources.cmake` used by firmware, firmware-mp2, and simulator. New board-conf dir `src/pro/conf/` mirroring `medium/conf/`. Defer any physical `shared/` dir hoist until MP1 is maintenance-only (keeps the MP1 tree stable for backports, preserves blame/bisect).

   ```
   metamodule/
     firmware/                      # MP1, unchanged; maintenance target
       src/medium/conf/             # existing MP1 board conf
       src/shared_sources.cmake     # NEW: canonical portable source lists
     firmware-mp2/                  # NEW: "pro" target; superbuild of A35 + M33 ELFs
       CMakeLists.txt               # set(FWDIR ../firmware) — simulator precedent
       cmake/arch_mp25xa35.cmake    # aarch64-none-elf (model on stm32mp2-baremetal makefile-common.mk)
       cmake/arch_mp25xm33.cmake    # arm-none-eabi -mcpu=cortex-m33
       src/pro/conf/                # pin_conf.hh, screen_conf.hh, ... mirrors medium/conf
       src/core_a35/                # boot, static_buffers, aux-core player analog
       src/core_m33/                # M33-side main
       lib/cmsis-device-mp2/        # patched CMSIS pack (from stm32mp2-baremetal/shared/cmsis-device)
     simulator/                     # unchanged; migrates onto shared_sources.cmake
   ```

2. **M33 role: abstract now, mirror-the-M4 as the default** (confirmed). Refactor `src/core_intercom/` so the transport and the A35/M33 responsibility split are movable; start with the MP1 split (controls + FS + wifi on the M-core — the M4 code is Cortex-M 32-bit and ports mostly mechanically) and revisit after eval-board numbers. The alternative (M33 = real-time controls only; FS/USB on the A35s, which are far faster than the A7s were) stays open until bring-up data exists.

3. **Exception level: EL3 secure** (confirmed), as all verified baremetal examples run. Matches MP1's own-the-whole-chip model: no BL31/OP-TEE runtime, manual core-1 start via `CA35SYSCFG->VBAR_CR` + RCC reset, full RIF/RISAB control. The `el1-ns` branch remains the fallback if a need for secure services appears.

---

## Part A — mdrivlib MP2 target (started; can proceed without new hardware)

Layout mirrors MP1 (`target/stm32mp1`, `_ca7`, `_cm4`; `target/stm32mp13` = new-family precedent):

```
target/stm32mp2/drivers/        # family-shared (both cores)
  periph.hh, rcc_common.hh (from baremetal shared/drivers/rcc.hh),
  rcc_pll.hh, rcc_pll1.hh, rcc_xbar.hh (flexgen kernel clocks),
  hpdma_registers.hh + hpdma_transfer.hh (NEW IP; linked-list circular pattern from hal-audio/dma.hh),
  hsem.hh, ipcc.hh/ipcc_regs.hh (MP2 register maps, same class APIs),
  i2c_target.hh, i2c_timing_config.hh, uart_target.hh, spi.hh/spi_registers.hh,
  sai_tdm.{hh,cc} (from hal-audio, verified), adc_builtin.hh + sdcard_target.hh (gated on examples),
  risab.{hh,cc} / rif config, pwr_vdd.hh, watchdog.hh
target/stm32mp2_ca35/
  boot/     vectors.S + macros_el.S (from shared/aarch64/), startup, system init,
            irq_init.c (GIC init), mmu (from shared/mmu/)
  drivers/  cache.hh (AArch64 DC CVAC/CIVAC — SAME mdrivlib::SystemCache API),
            interrupt_control.hh + interrupt_handler.cc (SAME API as MP1 CA7),
            rcc.hh, system_clocks.hh, smp.hh (VBAR_CR+RCC reset / PSCI, from multicore_smp),
            copro_control.hh (M33 load/start — new; MP1 version is the API template),
            system_reg.hh, smc.hh, cycle_counter.hh (generic timer)
  templates/ linker script, MMU region config
target/stm32mp2_cm33/
  boot/ CMSIS startup; drivers/ NVIC interrupt_control.hh, cache.hh stubs, rcc.hh (M33 view)
```

Key points:

- CMSIS device headers stay app-provided (as with MP1). The **patched** pack (ST's `POSITION_VAL` is broken on 64-bit; the A35 headers came from ST's DDR-FW-UTIL, absent from Cube) lives in `stm32mp2-baremetal/shared/cmsis-device/` — consuming projects must use it, documented in `target/stm32mp2/README.md`.
- Reconcile `register_access.hh`: the baremetal copy is a 64-bit-safe mirror of mdrivlib's shared one; merge fixes into the single mdrivlib copy and compile-sweep the existing 32-bit targets.
- **Test bed = the baremetal repo**: convert `minimal_boot`, `ctest`, `interrupts`, `hal-dma`, `hal-audio` to build against the mdrivlib target dirs instead of local `shared/` — each conversion verifies a ported layer on real hardware. Milestone: `hal-audio` runs on mdrivlib's `sai_tdm` + HPDMA + `i2c` with the shared `codec_PCM3168.cc` unchanged.

Porting order: ① rebase + `arch.hh` targets → ② ca35 boot (vectors/mmu/startup/linker) → ③ rcc family drivers → ④ interrupt stack → ⑤ cache.hh → ⑥ hpdma + sai_tdm + i2c → ⑦ hsem/ipcc + copro_control + cm33 target (needs the copro-m33 example) → ⑧ sdcard, adc, LTDC, xspi (each gated on its example); USB dwc3/xhci port (or kept app-side, as MP1 does) once `usb-xhci` merges to main.

## Part B — driver gaps → new stm32mp2-baremetal examples (ordered by risk × lead time)

| # | Gap | Example project | Notes |
|---|-----|-----------------|-------|
| 1 | **LTDC display (± DSI/LVDS)** | `ltdc/` — RGB565 layer to eval panel, then LVGL blit | Longest pole; informs the panel-interface hardware decision (RGB vs DSI vs LVDS — each PHY is its own bring-up). Start now |
| 2 | **M33 AMP + inter-core** | `copro-m33/` — A35 loads M33 image to SRAM, RIF grants, start core, HSEM-signaled shared-struct exchange (MetaModule's actual IPC pattern) | Longest pole #2; determines whether the `core_intercom` port is mechanical. Start now |
| 3 | **SDMMC** | `sdmmc/` — IDMA multi-block + FatFs mount | IP close to MP1; blocks all filesystem work |
| 4 | **ADC + HPDMA circular** | `adc/` | New ADC IP; knobs/CV |
| 5 | **XSPI NOR flash** | `xspi-flash/` | mdrivlib has qspi/xspi precedents (MP13) |
| 6 | **USB MSC host class** | extend `usb-drd/` on the `usb-xhci` branch | Not a stack gap: XHCI host + dual-role + USB MIDI already verified on `usb-xhci`. Remaining: MSC host class + merge to main |
| 7 | TIM/PWM | fold into `adc/` or tiny example | gate outs / LED PWM |
| 8 | IPCC (if chosen over raw HSEM) | fold into `copro-m33/` | decide HSEM-vs-IPCC there |

UART/wifi + I2C expanders need no new examples (UART trivial; `i2c/` verified; expanders are portable mdrivlib chip drivers). Examples 1 and 2 are independent — run in parallel.

## Part C — metamodule firmware port phases

**Phase 0 — now, before MetaModule-specific hardware (eval board / devboard v0.1):**

- Extract `firmware/src/shared_sources.cmake`; migrate `simulator/` onto it (pure refactor, testable today via the simulator build).
- Scaffold `firmware-mp2/` (toolchain files per Decision 1; superbuild of A35 + M33 ELFs) and stub `src/pro/conf/` (copy of `medium/conf/` with TBD pins) so shared code compiles for aarch64 early.
- **AArch64 dynloader**: extend `src/dynload/elf_process/` to Elf64 + `R_AARCH64_RELATIVE/GLOB_DAT/JUMP_SLOT/ABS64` (currently `uint32_t*` + `R_ARM_*` only). Host-testable now under qemu/aarch64 with a real `.so` and a synthetic symbol table.
- **64-bit audit** of the non-simulated remainder (the simulator already proves gui/patch_play/params on 64-bit hosts): `src/core_intercom/` shared structs must become fixed-width, pointer-free, `static_assert`-ed layouts (A35=64-bit, M33=32-bit — any pointer or `size_t`/`long` in shared memory is a bug); `static_buffers`, memory maps, fatfs/littlefs config.
- **Intercom abstraction** per Decision 2 — also benefits MP1 (the struct hygiene is backportable).
- **GUI size flexibility**: audit `src/gui/` pages for hardcoded 320×240 vs `screen_buffer_conf.hh`-derived values; add a simulator display-size option so the larger-screen "pro" pages can be designed and previewed before hardware exists.
- **mp2-boot**: productize the 4ms TF-A BL2 fork as the mp1-boot analog; define the FIP/uimg-successor packaging for combined A35+M33 images (`flashing/elf_to_uimg.py` successor).
- SDK dual-arch (sketch only; full SDK work deferred): aarch64 toolchain file in `metamodule-plugin-sdk`, dual-arch `.mmplugin` packaging decision, canary plugin compiles in CI.

**Phase 1 — eval board / devboard bring-up of `firmware-mp2/`:**
console/clocks/MMU/SMP → **audio milestone** (PCM3168 + SAI + HPDMA into StaticBuffers; patch_play headless = "a MetaModule that makes sound, no UI") → SD + filesystem on A35 → dynloader on target with generated symbol table → M33 AMP + ported intercom → LTDC + LVGL at provisional resolution + aux-core player → USB host MSC+MIDI (XHCI already verified).

**Phase 2 — final hardware:** real `pro/conf/pin_conf.hh` + all conf headers from the pin list, panel init, jack sense/calibration, wifi UART, expanders, LEDs, production flashing + fw_update path, boot-time parity with mp1-boot.

**Phase 3 — transition:** MP1 maintenance-branch policy, SDK dual-arch releases by default, optional physical `shared/` hoist, simulator "pro" flavor (screen size + conf).

## Phase 0 status (July 2026)

Done (this branch):
- mdrivlib `target/stm32mp2{,_ca35,_cm33}` with all verified baremetal code ported
  (boot, MMU, GIC, cache, RCC/PLL/XBAR, SMP/SMC, RISAB, HPDMA circular, SAI TDM,
  I2C); baremetal `interrupts` example converted as the first test-bed proof
- Build split: `firmware/src/shared_sources.cmake` + simulator migrated (full sim
  builds unchanged); `firmware-mp2/` scaffold building `main_a35.elf` on the
  mdrivlib boot path; `src/pro/conf/` started (provisional 720x480 screen conf)
- AArch64 plugin loader: ELF64/RELA support (`METAMODULE_ELF64`), R_AARCH64
  relocations, init_array fixes; tested against a real aarch64 .so in the suite
- Simulator `--screenw/--screenh` for pro-size GUI previews (first findings in
  the commit log); `docs/MP2-Intercom-Audit.md` for the A35/M33 struct work

Next: intercom abstraction + fixed-width structs, GUI layout constants, LTDC and
copro-m33 baremetal examples (hardware), mp2-boot/FIP packaging.

## Open questions / risks

1. EL3 vs EL1-NS (proceeding EL3 — Decision 3).
2. M33 role (proceeding abstract-now / mirror-default — Decision 2).
3. Panel interface + resolution — hardware decision; the biggest firmware↔hardware schedule coupling.
4. HSEM vs IPCC, shared-memory region choice, RIF grants, A35-side cacheability of shared regions.
5. Render pipeline: larger framebuffer in DDR; MP25 has a GPU but **no DMA2D** — software render on a 1.5 GHz A35 is likely fine, GPU drivers would be a large effort. LVGL 8.3-fork upgrade is an opportunity/risk to weigh during the port.
6. Plugin ABI: compiler/libstdc++ pinning for aarch64, distribution format (fat `.mmplugin` vs per-arch), how long MP1 builds stay mandatory for plugin publishers.
7. `register_access.hh` 64-bit reconciliation touches all mdrivlib targets — needs a compile sweep.
8. The baremetal SMP shared-ISR-table limitation (same IRQ can't have per-core handlers) must be fixed before A35 core2 runs the aux player with its own interrupt set.
9. ST MP2 header/tooling maturity (`POSITION_VAL`-class surprises) — budget slack in the example phase.
