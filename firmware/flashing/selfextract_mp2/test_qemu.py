#!/usr/bin/env python3
"""Load main.uimg as TF-A's loader does (same checks of its header), run it in QEMU, started as
TF-A starts it (EL3, MMU off), and check that the A35 image is unpacked to where it's linked, and
entered with the MMU and caches off.
Then check that the stub hangs, without starting the image, if the payload is corrupted.

Usage: test_qemu.py [build dir]   (default: build-mp2)
Needs qemu-system-aarch64 and aarch64-none-elf-gdb.

QEMU doesn't model the caches, so this doesn't test that the stub writes them out before it jumps.
"""

import struct
import subprocess
import sys
import tempfile
import time
import zlib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from elftools.elf.elffile import ELFFile

GDB_PORT = 1234


def load_segments(elf_path):
    with open(elf_path, "rb") as f:
        elf = ELFFile(f)
        segs = [(s["p_paddr"], s.data()) for s in elf.iter_segments() if s["p_type"] == "PT_LOAD" and s["p_filesz"] > 0]
        hang = elf.get_section_by_name(".symtab").get_symbol_by_name("hang")
        return elf.header.e_entry, segs, hang[0]["st_value"] if hang else None


def load_uimg(path, base, max_size):
    """The checks in TF-A's stm32mp_load_baremetal_app(). Returns load address, entry, payload"""
    img = path.read_bytes()
    hdr = img[:64]
    magic, hcrc, _, size, load, ep, dcrc = struct.unpack(">7I", hdr[:28])
    if magic != 0x27051956:
        sys.exit("FAIL: uimg magic")
    if zlib.crc32(hdr[:4] + bytes(4) + hdr[8:]) != hcrc:
        sys.exit("FAIL: uimg header CRC")
    if size == 0 or size > max_size or load < base or load + size > base + max_size or not load <= ep < load + size:
        sys.exit(f"FAIL: TF-A would reject size {size:#x} load {load:#x} entry {ep:#x}")
    if len(img) != 64 + size:
        sys.exit(f"FAIL: uimg size field is {size}, but the file has {len(img) - 64} bytes after the header")
    if zlib.crc32(img[64:]) != dcrc:
        sys.exit("FAIL: uimg payload CRC")
    print(f"ok: main.uimg header: {size} bytes, load {load:#x}, entry {ep:#x}")
    return load, ep, img[64:]


def run(stub_bin, load, start, gdb_commands, tmp):
    qemu = subprocess.Popen(
        ["qemu-system-aarch64", "-machine", "virt,secure=on", "-cpu", "cortex-a35", "-m", "3G"]
        + ["-nographic", "-monitor", "none", "-serial", "none", "-S", "-gdb", f"tcp::{GDB_PORT}"]
        + ["-device", f"loader,file={stub_bin},addr={load:#x},force-raw=on"]
        + ["-device", f"loader,addr={start:#x},cpu-num=0"],
        stderr=subprocess.DEVNULL,
    )
    try:
        time.sleep(1)
        script = Path(tmp) / "test.gdb"
        script.write_text("\n".join(["set pagination off", f"target remote :{GDB_PORT}"] + gdb_commands + ["kill"]))
        res = subprocess.run(["aarch64-none-elf-gdb", "-batch", "-x", str(script)], capture_output=True, text=True, timeout=120)
        return res.stdout
    finally:
        qemu.kill()
        qemu.wait()


def main():
    build = Path(sys.argv[1] if len(sys.argv) > 1 else "build-mp2")
    entry, app_segs, _ = load_segments(build / "main_a35.elf")
    _, _, hang = load_segments(build / "selfextract" / "selfextract_stub.elf")
    # TF-A's limits: image_base and image_max_size in its plat_bl2_mem_params_desc.c
    load, start, stub = load_uimg(build / "main.uimg", 0x88000000, 0x1000000)
    ok = True

    with tempfile.TemporaryDirectory() as tmp:
        stub_bin = Path(tmp) / "stub.bin"

        # 1: a good image
        stub_bin.write_bytes(stub)
        cmds = [f"hbreak *{entry:#x}", "continue", "printf \"PC=%lx SCTLR=%lx\\n\", $pc, $SCTLR_EL3"]
        for i, (addr, data) in enumerate(app_segs):
            cmds.append(f"dump binary memory {tmp}/seg{i}.bin {addr:#x} {addr + len(data):#x}")
        out = run(stub_bin, load, start, cmds, tmp)

        line = next((l for l in out.splitlines() if l.startswith("PC=")), "PC=0 SCTLR=0")
        pc, sctlr = (int(v.split("=")[1], 16) for v in line.split())
        if pc != entry:
            print(f"FAIL: didn't reach the entry point {entry:#x}")
            ok = False
        if sctlr & 0x1005:
            print(f"FAIL: the MMU or caches are on at the entry point (SCTLR_EL3 = {sctlr:#x})")
            ok = False
        for i, (addr, data) in enumerate(app_segs):
            got = Path(tmp, f"seg{i}.bin")
            if not got.exists() or got.read_bytes() != data:
                print(f"FAIL: segment at {addr:#x} ({len(data)} bytes) doesn't match the ELF")
                ok = False
            else:
                print(f"ok: segment at {addr:#x} ({len(data)} bytes) matches the ELF")
        if ok:
            print(f"ok: entered the image at {entry:#x} with the MMU and caches off")

        # 2: a corrupted payload must not be started
        bad = bytearray(stub)
        bad[len(bad) // 2] ^= 0x01
        stub_bin.write_bytes(bad)
        out = run(stub_bin, load, start, [f"hbreak *{entry:#x}", f"hbreak *{hang:#x}", "continue", "printf \"PC=%lx\\n\", $pc"], tmp)
        line = next((l for l in out.splitlines() if l.startswith("PC=")), "PC=0")
        pc = int(line.split("=")[1], 16)
        if pc == hang:
            print("ok: corrupted payload: the stub hangs")
        else:
            print(f"FAIL: corrupted payload: pc = {pc:#x}, expected the stub's hang loop at {hang:#x}")
            ok = False

    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
