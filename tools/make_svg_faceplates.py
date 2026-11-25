#!/usr/bin/env python3
"""
Collect SVG faceplates for platforms that draw module artwork from SVGs (MP2).

On those platforms, a module's faceplate is drawn from an .svg file with the same path as its
.png faceplate, if there is one (the .png is the fallback). This script fills the overlay dir
firmware/assets-svg/ with those SVGs, which the build adds to the assets image:

  - 4ms modules: the `faceplate` layer of firmware/lib/CoreModules/4ms/svg/<Slug>_info.svg
  - Other built-in brands: the panel SVG in firmware/vcv_ports/<Brand>/res with the same name
    as the faceplate PNG in firmware/assets/<Brand>/

The firmware's SVG renderer (ThorVG) is built without fonts or image loaders, so:
  - SVGs with <text> are run through Inkscape to convert the text to paths. This needs
    Inkscape (in PATH, or set INKSCAPE_BIN_PATH), and the fonts the SVG uses to be installed:
    if they aren't, the SVG is skipped rather than drawn in a substitute font.
  - SVGs with <image> are skipped.
  - SVGs that are not the same shape as the PNG they'd replace are skipped.
Everything skipped is listed, and keeps using its PNG faceplate.

Usage: tools/make_svg_faceplates.py [--out firmware/assets-svg]
"""

import argparse
import os
import re
import shutil
import subprocess
import tempfile
import struct
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
FW = REPO / "firmware"
SVG_NS = "http://www.w3.org/2000/svg"
ET.register_namespace("", SVG_NS)
ET.register_namespace("xlink", "http://www.w3.org/1999/xlink")

# Faceplate PNGs are exported at this height
FACEPLATE_PNG_HEIGHT = 240

# Height of a 3U Eurorack panel
PANEL_HEIGHT_MM = 128.5


def png_size(path: Path) -> tuple[int, int]:
    with open(path, "rb") as f:
        header = f.read(24)
    if header[:8] != b"\x89PNG\r\n\x1a\n":
        return 0, 0
    return struct.unpack(">II", header[16:24])


def has_text(svg_text: str) -> bool:
    return re.search(r"<(svg:)?text[\s>]", svg_text) is not None


def has_image(svg_text: str) -> bool:
    return re.search(r"<(svg:)?image[\s>]", svg_text) is not None


def find_inkscape() -> str | None:
    mac_app = "/Applications/Inkscape.app/Contents/MacOS/inkscape"
    return shutil.which("inkscape") or os.getenv("INKSCAPE_BIN_PATH") or (mac_app if os.path.exists(mac_app) else None)


def text_to_paths(svg_text: str, inkscape: str) -> str | None:
    with tempfile.TemporaryDirectory() as tmp:
        src = Path(tmp) / "in.svg"
        dst = Path(tmp) / "out.svg"
        src.write_text(svg_text)
        cmd = [inkscape, "--export-text-to-path", "--export-plain-svg", f"--export-filename={dst}", str(src)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0 or not dst.exists():
            return None
        return dst.read_text()


def text_fonts(svg_text: str) -> set[str]:
    """Font families used by the <text> elements that actually have text in them"""
    fonts = set()
    try:
        root = ET.fromstring(svg_text)
    except ET.ParseError:
        return fonts
    for text in root.iter(f"{{{SVG_NS}}}text"):
        if not "".join(text.itertext()).strip():
            continue
        for el in text.iter():
            family = el.get("font-family") or ""
            if m := re.search(r"font-family:\s*([^;]+)", el.get("style", "")):
                family = m.group(1)
            # "GillSans-Bold, 'Gill Sans'" -> Gill Sans
            for name in family.split(","):
                name = name.strip().strip("'\"")
                if name and "-" not in name:
                    fonts.add(name)
    return fonts


def installed_fonts() -> set[str] | None:
    """Lower-case names of the installed font families, or None if they can't be listed"""
    if not shutil.which("fc-list"):
        return None
    result = subprocess.run(["fc-list", ":", "family"], capture_output=True, text=True)
    if result.returncode != 0:
        return None
    return {name.strip().lower() for line in result.stdout.splitlines() for name in line.split(",")}


def svg_aspect(svg_text: str) -> float | None:
    try:
        root = ET.fromstring(svg_text)
    except ET.ParseError:
        return None
    viewbox = root.get("viewBox", "").replace(",", " ").split()
    if len(viewbox) == 4 and float(viewbox[3]) > 0:
        return float(viewbox[2]) / float(viewbox[3])
    w = re.match(r"\s*([\d.]+)", root.get("width", ""))
    h = re.match(r"\s*([\d.]+)", root.get("height", ""))
    if w and h and float(h.group(1)) > 0:
        return float(w.group(1)) / float(h.group(1))
    return None


def prepare(svg_text: str, png: Path, inkscape: str | None, fonts: set[str] | None) -> tuple[str | None, str]:
    """Returns the SVG ready for the firmware's renderer, or None and the reason it can't be used"""
    if has_image(svg_text):
        return None, "has <image>"

    # The SVG replaces the PNG, so it must be the same shape (within a pixel of the PNG's width)
    png_w, png_h = png_size(png)
    aspect = svg_aspect(svg_text)
    if aspect is None or abs(aspect * png_h - png_w) > 1.5:
        return None, f"is not the same shape as the PNG ({png_w}x{png_h})"

    if has_text(svg_text):
        if not inkscape:
            return None, "has <text>, and Inkscape was not found to convert it to paths"
        if fonts is not None:
            if missing := sorted(f for f in text_fonts(svg_text) if f.lower() not in fonts):
                return None, f"has <text> in fonts that are not installed: {', '.join(missing)}"
        svg_text = text_to_paths(svg_text, inkscape)
        if svg_text is None:
            return None, "has <text>, and Inkscape failed to convert it to paths"
    return svg_text, ""


def crop_to_panel_height(root: ET.Element):
    """
    Some info SVGs have a page that is taller than the 3U panel (which is at the top of the
    page). The PNG faceplates are exported from the faceplate layer's bounds, not the page,
    so crop the page to the panel height to match.
    """
    m = re.fullmatch(r"\s*([\d.]+)\s*mm\s*", root.get("height", ""))
    viewbox = root.get("viewBox", "").replace(",", " ").split()
    if not m or len(viewbox) != 4:
        return
    height_mm = float(m.group(1))
    if height_mm <= PANEL_HEIGHT_MM:
        return
    x, y, w, h = (float(v) for v in viewbox)
    h = h * PANEL_HEIGHT_MM / height_mm
    root.set("height", f"{PANEL_HEIGHT_MM}mm")
    root.set("viewBox", f"{x:g} {y:g} {w:g} {h:.4f}")


def extract_4ms_faceplate(info_svg: Path) -> str | None:
    """Keep only <defs>, <style> and the `faceplate` layer of a 4ms info SVG"""
    tree = ET.parse(info_svg)
    root = tree.getroot()
    found = False
    for child in list(root):
        tag = child.tag.split("}")[-1]
        if tag == "g" and child.get("id") == "faceplate":
            found = True
        elif tag not in ("defs", "style"):
            root.remove(child)
    if not found:
        return None
    crop_to_panel_height(root)
    # Drop editor metadata
    for el in root.iter():
        for attr in list(el.attrib):
            if attr.startswith("{http://www.inkscape.org") or attr.startswith("{http://sodipodi."):
                del el.attrib[attr]
    return ET.tostring(root, encoding="unicode")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--out", type=Path, default=FW / "assets-svg")
    args = parser.parse_args()

    inkscape = find_inkscape()
    fonts = installed_fonts()

    # Start clean, so an SVG that can no longer be used doesn't linger
    if args.out.is_dir():
        for old in args.out.rglob("*.svg"):
            old.unlink()
    written = 0
    skipped = []
    missing = []

    # 4ms: info SVGs
    fp_dir = FW / "assets" / "4ms" / "fp"
    svg_dir = FW / "lib" / "CoreModules" / "4ms" / "svg"
    for png in sorted(fp_dir.glob("*.png")):
        candidates = [svg_dir / f"{png.stem}_info.svg", svg_dir / f"{png.stem}.svg"]
        src = next((c for c in candidates if c.exists()), None)
        if not src:
            missing.append(f"4ms/fp/{png.name}")
            continue
        svg = extract_4ms_faceplate(src)
        if svg is None:
            skipped.append(f"{src.relative_to(REPO)}: no `faceplate` layer")
            continue
        svg, reason = prepare(svg, png, inkscape, fonts)
        if svg is None:
            skipped.append(f"{src.relative_to(REPO)}: faceplate layer {reason}")
            continue
        dest = args.out / "4ms" / "fp" / f"{png.stem}.svg"
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(svg)
        written += 1

    # Other brands: same-named SVG in the VCV plugin's res/ dir
    for brand_dir in sorted((FW / "assets").iterdir()):
        brand = brand_dir.name
        res = FW / "vcv_ports" / brand / "res"
        if brand == "4ms" or not res.is_dir():
            continue
        svgs = {}
        for svg in res.rglob("*.svg"):
            svgs.setdefault(svg.relative_to(res).with_suffix(""), svg)
        for png in sorted(brand_dir.rglob("*.png")):
            if png_size(png)[1] != FACEPLATE_PNG_HEIGHT:
                continue  # a component, not a faceplate
            rel = png.relative_to(brand_dir).with_suffix("")
            src = svgs.get(rel)
            if not src:
                missing.append(f"{brand}/{rel}.png")
                continue
            text, reason = prepare(src.read_text(errors="replace"), png, inkscape, fonts)
            if text is None:
                skipped.append(f"{src.relative_to(REPO)}: {reason}")
                continue
            dest = args.out / brand / rel.with_suffix(".svg")
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_text(text)
            written += 1

    print(f"Wrote {written} SVG faceplates to {args.out}")
    if skipped:
        print(f"\nSkipped {len(skipped)} (the PNG faceplate will be used):")
        print("\n".join(f"  {s}" for s in skipped))
    if missing:
        print(f"\nNo SVG found for {len(missing)} faceplate PNGs:")
        print("\n".join(f"  {m}" for m in missing))


if __name__ == "__main__":
    main()
