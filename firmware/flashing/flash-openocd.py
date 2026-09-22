#!/usr/bin/env python3
"""
Reflash the MetaModule app over JTAG/SWD without a power cycle.

Requires:
  - Freeze jumper installed, so mp1-boot waits for an image after reset
  - openocd: an already-running instance (make start-openocd) is used if present;
    otherwise one is launched for the duration of the script and killed afterwards

Flow:
  1. Clear the TAMP_BKP6R mailbox (it survives resets), then trigger a system
     reset by setting MPSYSRST in RCC_MP_GRSTCSETR. The board reboots into
     mp1-boot, which (with the freeze jumper) writes 0xFFFFFFFF to TAMP_BKP6R
     and spins until that register is changed.
  2. Poll TAMP_BKP6R until it reads 0xFFFFFFFF (bootloader ready, DDR initialized).
  3. Write a sacrificial 16kB block to DDR. The first bulk write after a system
     reset loses one word per 512-byte burst within its first 16kB (stale AP
     CSW state in the ST-LINK/openocd after the debug-domain reset); this
     throwaway transfer absorbs that corruption.
  4. Bulk-load main.uimg to DDR at 0xC0000000 via the AXI debug port (the CPU
     keeps spinning; no halt needed).
  5. Verify: read back the first 32kB and compare, plus scattered spot words.
     Retry the load once on mismatch.
  6. Write the image address to TAMP_BKP6R -- mp1-boot jumps to the app
     immediately.

Typical cycle time: ~25 seconds for a 6MB image.

Usage: flash-openocd.py path/to/main.uimg [--port 4444] [--verify] [--no-reset] [--no-boot]
"""

import argparse
import os
import socket
import struct
import subprocess
import sys
import tempfile
import time

LOAD_ADDR = 0xC0000000
RCC_MP_GRSTCSETR = 0x50000404  # bit 0 = MPSYSRST: software system reset
TAMP_BKP6R = 0x5C00A118  # mp1-boot's "DDR image address" mailbox register
BOOTLOADER_READY = 0xFFFFFFFF  # mp1-boot writes this when waiting for an image
AXI = "stm32mp15x.axi"
PRIME_SIZE = 16 * 1024


OPENOCD_CMD = ["openocd", "-f", "board/stm32mp15x_dk2.cfg"]


class OpenOcd:
    def __init__(self, port):
        # Raises OSError if nothing is listening; the caller decides whether
        # to launch an openocd instance of its own.
        self.sock = socket.create_connection(("localhost", port), timeout=5)
        self.sock.settimeout(120)
        self._read_to_prompt()  # banner

    def cmd(self, command):
        self.sock.sendall(command.encode() + b"\n")
        resp = self._read_to_prompt().decode(errors="replace")
        # Strip the echoed command line and the trailing prompt
        lines = resp.replace("\r", "").split("\n")
        return "\n".join(lines[1:]).removesuffix("> ").strip()

    def read_word(self, addr):
        out = self.cmd(f"{AXI} mdw 0x{addr:08X}")
        # e.g. "0xc0000000: 12345678"
        try:
            return int(out.split(":")[1].split()[0], 16)
        except (IndexError, ValueError):
            raise RuntimeError(f"Unexpected response reading 0x{addr:08X}: {out!r}")

    def write_word(self, addr, value):
        self.cmd(f"{AXI} mww 0x{addr:08X} 0x{value:08X}")

    def load_image(self, path, addr):
        self.cmd(f"targets {AXI}")
        out = self.cmd(f"load_image {path} 0x{addr:08X} bin")
        self.cmd("targets stm32mp15x.cpu0")
        if "downloaded" not in out:
            raise RuntimeError(f"load_image failed:\n{out}")
        return out.splitlines()[-1].strip()

    def dump_image(self, path, addr, size):
        self.cmd(f"targets {AXI}")
        out = self.cmd(f"dump_image {path} 0x{addr:08X} {size}")
        self.cmd("targets stm32mp15x.cpu0")
        if "dumped" not in out:
            raise RuntimeError(f"dump_image failed:\n{out}")

    def _read_to_prompt(self):
        buf = b""
        while not buf.endswith(b"> "):
            chunk = self.sock.recv(4096)
            if not chunk:
                raise RuntimeError("openocd closed the telnet connection")
            buf += chunk
        return buf

    def close(self):
        try:
            self.sock.sendall(b"exit\n")
            self.sock.close()
        except OSError:
            pass


def connect_or_launch(port):
    """Connect to a running openocd, or launch one ourselves.

    Returns (ocd, proc) where proc is the Popen handle of the openocd we
    launched, or None if one was already running (and must be left alone).
    """
    try:
        return OpenOcd(port), None
    except OSError:
        pass

    print("openocd is not running, launching it...")
    cmd = OPENOCD_CMD + (["-c", f"telnet_port {port}"] if port != 4444 else [])
    logfile = tempfile.NamedTemporaryFile(prefix="openocd-", suffix=".log", delete=False)
    try:
        proc = subprocess.Popen(cmd, stdout=logfile, stderr=subprocess.STDOUT)
    except FileNotFoundError:
        sys.exit("openocd not found on PATH. Install it, or start it yourself: make start-openocd")

    deadline = time.time() + 15
    while True:
        try:
            ocd = OpenOcd(port)
            return ocd, proc
        except OSError:
            pass
        if proc.poll() is not None or time.time() > deadline:
            proc.terminate()
            logfile.close()
            with open(logfile.name) as f:
                sys.exit("********************************************************\n"
                         " Failed to start openocd. Its output was:\n"
                         "********************************************************\n"
                         + f.read())
        time.sleep(0.3)


def file_word(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def verify(ocd, image, tmpdir, full):
    """Return None if the loaded image matches, else a description of the first mismatch."""
    check_size = len(image) if full else min(32 * 1024, len(image))
    readback_path = os.path.join(tmpdir, "readback.bin")
    ocd.dump_image(readback_path, LOAD_ADDR, check_size)
    with open(readback_path, "rb") as f:
        readback = f.read()
    if readback != image[:check_size]:
        diff = next(i for i in range(check_size) if readback[i] != image[i])
        return f"mismatch at offset 0x{diff:X}"
    if full:
        return None

    # Spot-check words spread across the rest of the image, plus the last word
    step = max(4, (len(image) // 16) & ~3)
    offsets = list(range(check_size, len(image) - 4, step)) + [(len(image) - 4) & ~3]
    for offset in offsets:
        if ocd.read_word(LOAD_ADDR + offset) != file_word(image, offset):
            return f"mismatch at offset 0x{offset:X}"
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("uimg", help="path to main.uimg")
    parser.add_argument("--port", type=int, default=4444, help="openocd telnet port")
    parser.add_argument("--verify", action="store_true",
                        help="verify the entire image after loading (adds ~20s)")
    parser.add_argument("--no-reset", action="store_true",
                        help="skip the reset (board is already waiting in mp1-boot)")
    parser.add_argument("--no-boot", action="store_true",
                        help="load and verify only; do not write the boot mailbox")
    args = parser.parse_args()

    with open(args.uimg, "rb") as f:
        image = f.read()

    t_start = time.time()
    ocd, launched_proc = connect_or_launch(args.port)
    try:
        run(ocd, image, args, t_start, external_openocd=launched_proc is None)
    finally:
        ocd.close()
        if launched_proc:
            launched_proc.terminate()
            launched_proc.wait()
            print("Stopped the openocd instance this script launched.")


def run(ocd, image, args, t_start, external_openocd):
    if not args.no_reset:
        # TAMP backup registers survive a system reset: clear the ready flag
        # first so the poll below can't see a stale value from the last boot.
        ocd.write_word(TAMP_BKP6R, 0)
        print("Resetting board (MPSYSRST)...")
        ocd.write_word(RCC_MP_GRSTCSETR, 1)

    print("Waiting for mp1-boot to be ready for an image...")
    deadline = time.time() + 20
    while True:
        try:
            if ocd.read_word(TAMP_BKP6R) == BOOTLOADER_READY:
                break
        except RuntimeError:
            pass
        if time.time() > deadline:
            sys.exit("Timed out waiting for mp1-boot ready flag (TAMP_BKP6R == 0xFFFFFFFF).\n"
                     "Is the Freeze jumper installed?")
        time.sleep(0.2)

    with tempfile.TemporaryDirectory() as tmpdir:
        prime_path = os.path.join(tmpdir, "prime.bin")
        with open(prime_path, "wb") as f:
            f.write(image[:PRIME_SIZE])

        for attempt in (1, 2):
            # Sacrificial write to absorb post-reset first-transfer corruption
            ocd.load_image(prime_path, LOAD_ADDR)

            print(f"Loading {len(image)} bytes to 0x{LOAD_ADDR:08X} via AXI debug port...")
            print("  " + ocd.load_image(args.uimg, LOAD_ADDR))

            error = verify(ocd, image, tmpdir, args.verify)
            if error is None:
                break
            if attempt == 2:
                sys.exit(f"Verify FAILED after retry: {error}")
            print(f"  Verify failed ({error}), retrying load...")
        print(f"  Loaded and verified in {time.time() - t_start:.1f}s")

    if args.no_boot:
        print("Skipping boot (--no-boot). Board is waiting in mp1-boot.")
        return

    print("Booting image (writing address to TAMP_BKP6R)...")
    if not external_openocd:
        # Our own openocd gets killed right after this write, so the app boots
        # with no debugger traffic at all.
        ocd.write_word(TAMP_BKP6R, LOAD_ADDR)
    else:
        # The app's early boot briefly breaks debug access (clock/debug-domain
        # reconfig, M4 reset). If openocd's background poller hits that window,
        # its poll failure triggers a re-examine that pokes DBGMCU/RCC and the
        # M4 core mid-boot, and the app dies to a watchdog reset ~40s later.
        # Suspend polling until the app is past its init.
        ocd.cmd("poll off")
        ocd.write_word(TAMP_BKP6R, LOAD_ADDR)
        print("App is booting; openocd polling suspended for 8s to keep out of its way...")
        time.sleep(8)
        ocd.cmd("poll on")
    print(f"Done in {time.time() - t_start:.1f}s. App is booting; watch the console log.")


if __name__ == "__main__":
    main()
