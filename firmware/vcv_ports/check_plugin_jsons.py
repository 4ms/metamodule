#!/usr/bin/env python3
"""
Checks that assets/BRAND/plugin.json and assets/BRAND/plugin-mm.json match
the modules registered in firmware. 

It actually just checks the json files against the list of modules the headless 
simualator reports it registered, but this should be the same as what shows up in firmware.

For each brand in the assets dir, this checks:

  - plugin.json and plugin-mm.json are valid (strict) JSON
  - plugin.json matches the copy in the vcv_ports/BRAND submodule (if any)
  - every registered module is listed in plugin-mm.json
  - every module in plugin-mm.json is registered
  - every module in plugin-mm.json is in plugin.json

Brands that are registered but have no assets dir are also reported.
Brands in the assets dir with no registered modules are skipped (e.g. built
with OMIT_BRAND_x).

Usage:
  check_plugin_jsons.py --simulator path/to/headless/simulator
  check_plugin_jsons.py --registered modules.txt   (output of --list-modules)

Exits with 1 if any errors were found.
"""

import argparse
import json
import subprocess
import sys
from pathlib import Path

FW_DIR = Path(__file__).resolve().parent.parent
ASSET_DIR = FW_DIR / "assets"
VCV_PORTS_DIR = FW_DIR / "vcv_ports"

# Registered modules that are intentionally not listed in plugin-mm.json
IGNORED_MODULES = {
    "4msCompany:HubMedium",
}

errors = []


def error(msg):
    errors.append(msg)
    print(f"ERROR: {msg}")


def load_json(path):
    try:
        with open(path) as f:
            return json.load(f)
    except json.JSONDecodeError as e:
        error(f"{path.relative_to(FW_DIR)}: invalid JSON: {e}")
    return None


def parse_registered(lines):
    registered = {}
    for line in lines:
        parts = line.rstrip("\n").split("\t")
        if len(parts) == 3 and parts[0] == "module":
            registered.setdefault(parts[1], set()).add(parts[2])
    return registered


def check_brand(brand_dir, registered):
    plugin_json_path = brand_dir / "plugin.json"
    mm_json_path = brand_dir / "plugin-mm.json"

    plugin_json = load_json(plugin_json_path)
    mm_json = load_json(mm_json_path) if mm_json_path.exists() else None

    if not mm_json_path.exists():
        error(f"{mm_json_path.relative_to(FW_DIR)} is missing")

    submodule_json = VCV_PORTS_DIR / brand_dir.name / "plugin.json"
    if submodule_json.exists() and submodule_json.read_bytes() != plugin_json_path.read_bytes():
        error(f"{plugin_json_path.relative_to(FW_DIR)} differs from {submodule_json.relative_to(FW_DIR)}. "
              f"Building the firmware or simulator will update it, or copy it manually.")

    if plugin_json is None or mm_json is None:
        return None

    brand_slug = mm_json.get("MetaModuleBrandSlug", plugin_json.get("slug", brand_dir.name))
    reg_slugs = registered.get(brand_slug)
    if not reg_slugs:
        print(f"Note: {brand_dir.name}: no modules registered for brand '{brand_slug}', skipping module checks")
        return brand_slug

    mm_slugs = {m.get("slug") for m in mm_json.get("MetaModuleIncludedModules", [])}
    vcv_slugs = {m.get("slug") for m in plugin_json.get("modules", [])}

    mm_name = mm_json_path.relative_to(FW_DIR)
    for slug in sorted(reg_slugs - mm_slugs):
        if f"{brand_slug}:{slug}" in IGNORED_MODULES:
            continue
        error(f"{mm_name}: missing registered module {brand_slug}:{slug}")
    for slug in sorted(mm_slugs - reg_slugs):
        error(f"{mm_name}: lists {slug}, which is not a registered module")
    for slug in sorted(mm_slugs - vcv_slugs):
        error(f"{mm_name}: lists {slug}, which is not in {plugin_json_path.relative_to(FW_DIR)}")

    return brand_slug


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    src = parser.add_mutually_exclusive_group(required=True)
    src.add_argument("--simulator", help="Path to headless simulator binary")
    src.add_argument("--registered", help="File with output of `simulator --list-modules`")
    args = parser.parse_args()

    if args.simulator:
        result = subprocess.run([args.simulator, "--list-modules"], capture_output=True, text=True, check=True)
        registered = parse_registered(result.stdout.splitlines())
    else:
        with open(args.registered) as f:
            registered = parse_registered(f)

    if not registered:
        print("ERROR: no registered modules found. Is this the headless simulator?")
        return 1

    checked_brands = set()
    for brand_dir in sorted(ASSET_DIR.iterdir()):
        if (brand_dir / "plugin.json").exists():
            checked_brands.add(check_brand(brand_dir, registered))

    for brand in sorted(set(registered) - checked_brands):
        error(f"brand '{brand}' is registered but has no assets/BRAND/plugin.json with that slug")

    if errors:
        print(f"\n{len(errors)} error(s) found")
        return 1

    print(f"plugin.json and plugin-mm.json OK for {len(checked_brands)} brands")
    return 0


if __name__ == "__main__":
    sys.exit(main())
