#!/usr/bin/env python3
"""
Generate the scaled GUI fonts used on high-density screens (MP2/pro).

Each font in ROLES is regenerated from the lv_font_conv options recorded in the
header of the MP1 font it replaces (same glyph ranges, same FontAwesome and
DejaVu merges), at `scale` times the size, into scaled/ui_font_<role>.c

    ./generate_scaled_fonts.py --scale 2 --museo-dir "<dir with MuseoSansRounded-*.ttf>"

Requires lv_font_conv (npm i -g lv_font_conv).
See ui_fonts.hh for how the roles map to fonts on each platform.
"""

import argparse
import re
import shlex
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
MP1_FONTS = HERE.parent / "slsexport" / "meta5" / "fonts"
LVGL_FONTS = HERE.parents[2] / "lib" / "lvgl" / "lvgl" / "scripts" / "built_in_font"
OUT_DIR = HERE / "scaled"

# role -> MP1 font it stands in for
ROLES = {
    "tiny": "ui_font_MuseoSansRounded50010",
    "small": "ui_font_MuseoSansRounded50012",
    "medium": "ui_font_MuseoSansRounded50014",
    "medium_bold": "ui_font_MuseoSansRounded70014",
    "med_large": "ui_font_MuseoSansRounded50016",
    "med_large_bold": "ui_font_MuseoSansRounded70016",
    "large": "ui_font_MuseoSansRounded90018",
    "huge": "ui_font_MuseoSansRounded90040",
}


def recorded_opts(mp1_font: str) -> list[str]:
    text = (MP1_FONTS / f"{mp1_font}.c").read_text()
    m = re.search(r"^ \* Opts: (.*)$", text, re.MULTILINE)
    if not m:
        sys.exit(f"No 'Opts:' line found in {mp1_font}.c")
    # Font paths contain spaces ("Museo Sans Rounded/..."): split on the option flags instead
    return re.split(r"\s+(?=--?[a-z])", m.group(1).strip())


def find_font(filename: str, search_dirs: list[Path]) -> Path:
    for d in search_dirs:
        if (d / filename).exists():
            return d / filename
    sys.exit(f"Could not find {filename} in: {', '.join(str(d) for d in search_dirs)}")


def build_command(role: str, mp1_font: str, scale: float, search_dirs: list[Path]) -> tuple[list[str], int]:
    cmd = ["lv_font_conv"]
    size = 0
    for opt in recorded_opts(mp1_font):
        flag, _, value = opt.partition(" ")
        if flag == "--size":
            size = round(int(value) * scale)
            cmd += ["--size", str(size)]
        elif flag == "--font":
            cmd += ["--font", str(find_font(Path(value).name, search_dirs))]
        elif flag == "-o":
            cmd += ["-o", str(OUT_DIR / f"ui_font_{role}.c")]
        elif value:
            cmd += [flag, value]
        else:
            cmd += [flag]
    if not size:
        sys.exit(f"No --size in the options recorded in {mp1_font}.c")
    return cmd, size


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--scale", type=float, default=2.0, help="Size multiplier vs. the MP1 fonts (default 2)")
    parser.add_argument("--museo-dir", type=Path, required=True, help="Dir containing MuseoSansRounded-{500,700,900}.ttf")
    parser.add_argument("--only", nargs="*", choices=ROLES.keys(), help="Only generate these roles")
    args = parser.parse_args()

    search_dirs = [args.museo_dir, LVGL_FONTS, args.museo_dir.parent]
    OUT_DIR.mkdir(exist_ok=True)

    for role, mp1_font in ROLES.items():
        if args.only and role not in args.only:
            continue
        cmd, size = build_command(role, mp1_font, args.scale, search_dirs)
        print(f"ui_font_{role}: {mp1_font} x{args.scale:g} -> {size}px")
        subprocess.run(cmd, check=True)

        # lv_font_conv writes absolute paths into the Opts comment, and an lvgl include
        # that assumes LV_LVGL_H_INCLUDE_SIMPLE.
        out = OUT_DIR / f"ui_font_{role}.c"
        text = out.read_text()
        text = re.sub(r"^ \* Opts: .*$", " * Opts: " + shlex.join(_relative(cmd)), text, count=1, flags=re.MULTILINE)
        out.write_text(text)


def _relative(cmd: list[str]) -> list[str]:
    return [Path(c).name if c.startswith("/") else c for c in cmd]


if __name__ == "__main__":
    main()
