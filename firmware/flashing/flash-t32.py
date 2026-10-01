#!/usr/bin/env python3
"""
Flash the MetaModule app via TRACE32 without a power cycle.

Requires:
  - TRACE32 PowerView running with the RCL API enabled
  - Freeze jumper installed, so mp1-boot waits for an image after reset

Flow (mirrors flash-openocd.py):
  1. Attach if not already attached (never resets or halts the target).
  2. Clear the TAMP_BKP6R mailbox (it survives resets), then trigger a system
     reset by setting MPSYSRST in RCC_MP_GRSTCSETR. The board reboots into
     mp1-boot, which (with the freeze jumper) writes 0xFFFFFFFF to TAMP_BKP6R
     and spins until that register is changed.
  3. Poll TAMP_BKP6R until it reads 0xFFFFFFFF (bootloader ready, DDR up).
  4. Load main.uimg to DDR at 0xC0000000 with a run-time (/DUALPORT) transfer
     -- the CPU keeps spinning, no halt needed -- and verify with /ComPare.
  5. Load ELF symbols, write the image address to TAMP_BKP6R (mp1-boot jumps
     to the app immediately), and re-arm the ETM trace.

With --assets <assets.uimg>, step 4 also loads the assets image to DDR and writes its
address to TAMP_BKP8R. The app uses it instead of the assets in NOR flash, for that boot
only (see AssetFS::read_ram_image() in src/fs/asset_drive/asset_fs.hh).

Typical cycle time: ~10 seconds for a 6MB image.
"""

import argparse
import sys
import time
from pathlib import Path

import lauterbach.trace32.rcl as t32

do_verify = False

LOAD_ADDR = 0xC0000000
RCC_MP_GRSTCSETR = 0x50000404  # bit 0 = MPSYSRST: software system reset
TAMP_BKP6R = 0x5C00A118  # mp1-boot's "DDR image address" mailbox register
TAMP_BKP8R = 0x5C00A120  # app's "assets image in RAM" mailbox register (0 = use flash)
ASSETS_LOAD_ADDR = 0xCCC00000  # in FWBUFFER, see system/linker/memory.ld
BOOTLOADER_READY = 0xFFFFFFFF  # mp1-boot writes this when waiting for an image
SYSTEM_MODE_UP = 11

basepath = Path(__file__).parent.parent
binpath = basepath / "build" / "main.uimg"
elfpath = basepath / "build" / "mp1corea7" / "medium" / "main.elf"


def read_long(dbg, addr):
    return dbg.fnc(f"Data.Long(EAZSD:{addr:#x})")


def write_long(dbg, addr, value):
    dbg.cmd(f"Data.Set EAZSD:{addr:#x} %Long {value:#x}")


def attach_if_needed(dbg):
    if dbg.fnc("SYStem.Mode()") == SYSTEM_MODE_UP:
        return
    dbg.cmd("SYStem.CPU STM32MP153D-CA7")
    dbg.cmd("SYStem.config DEBUGPORTTYPE SWD")
    dbg.cmd("SYStem.JtagClock 50MHz")
    dbg.cmd("CORE.ASSIGN 1. 2.")
    dbg.cmd("Trace.DISable")
    dbg.cmd("SYStem.MemAccess DAP")
    dbg.cmd("SYStem.attach")


def load_binary(dbg, path, addr):
    for attempt in (1, 2):
        print(f"Loading {path.name} to {addr:#x} (run-time access, no halt)...")
        dbg.cmd(f"Data.LOAD.Binary {path} {addr:#x} /DUALPORT")
        if do_verify:
            try:
                dbg.cmd(f"Data.LOAD.Binary {path} {addr:#x} /DUALPORT /ComPare")
                break
            except Exception as e:
                if attempt == 2:
                    sys.exit(f"Verify FAILED after retry: {e}")
                print("  Verify failed, retrying load...")


def main():
    parser = argparse.ArgumentParser(description="Flash the MetaModule app via TRACE32")
    parser.add_argument("--assets", type=Path,
                        help="Also load this assets.uimg into RAM, to use instead of the assets in flash")
    args = parser.parse_args()

    if args.assets and not args.assets.is_file():
        sys.exit(f"Assets image not found: {args.assets}")

    try:
        dbg = t32.connect()
    except Exception as e:
        sys.exit(f"Cannot connect to TRACE32 ({e}).\n"
                 "Is PowerView running with the RCL API enabled?")

    t_start = time.time()
    dbg.print(f"Flashing via python rcl {binpath}...")
    attach_if_needed(dbg)

    # TAMP backup registers survive a system reset: clear the ready flag first
    # so the poll below can't see a stale value from the last boot.
    write_long(dbg, TAMP_BKP6R, 0)
    print("Resetting board (MPSYSRST)...")
    try:
        write_long(dbg, RCC_MP_GRSTCSETR, 1)
    except Exception:
        # TRACE32 often reports "target reset detected" on this write -- that
        # IS the reset we asked for, so carry on to polling for the bootloader
        pass

    print("Waiting for mp1-boot to be ready for an image...")
    deadline = time.time() + 20
    while True:
        try:
            if read_long(dbg, TAMP_BKP6R) == BOOTLOADER_READY:
                break
        except Exception:
            pass  # bus error while the SoC is still mid-reset; keep polling
        if time.time() > deadline:
            sys.exit("Timed out waiting for mp1-boot ready flag (TAMP_BKP6R == 0xFFFFFFFF).\n"
                     "Is the Freeze jumper installed?")
        time.sleep(0.2)

    load_binary(dbg, binpath, LOAD_ADDR)

    # The app reads (and clears) this when it starts. Clear it when not loading assets, in
    # case an earlier run left an address there.
    if args.assets:
        load_binary(dbg, args.assets, ASSETS_LOAD_ADDR)
        write_long(dbg, TAMP_BKP8R, ASSETS_LOAD_ADDR)
    else:
        write_long(dbg, TAMP_BKP8R, 0)

    print(f"  Loaded in {time.time() - t_start:.1f}s")

    dbg.cmd(f"Data.LOAD.Elf {elfpath} /CPP /NoCode")

    print("Booting image (writing address to TAMP_BKP6R)...")
    write_long(dbg, TAMP_BKP6R, LOAD_ADDR)

    dbg.cmd("Trace.METHOD ONCHIP")
    dbg.cmd("ETM.Trace ON")
    dbg.cmd("ETM.ON")
    dbg.cmd("Trace.arm")
    print(f"Done in {time.time() - t_start:.1f}s. App is booting; watch the console log.")


if __name__ == "__main__":
    main()
