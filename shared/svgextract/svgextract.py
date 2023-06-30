#!/usr/bin/env python3

import sys

from helpers import *
import vcv
import infofile
import coreModule
import lvgl
import imageList

# Version check
f"Python 3.6+ is required"


def processSvg(svgFilename):
    slug = infofile.createInfoFile(svgFilename)

    if slug is None:
        Log("No slug found, aborting")
        return

    vcv.extractForVcv(svgFilename, None, slug)
    

def usage(script):
    print(f"""MetaModule SVG Helper Utility

Usage: {script} <command> [args] 

Commands:

processSvg [input svg file name]
    Runs createinfo and extractforvcv on the given file.
    Uses environmant variables METAMODULE_INFO_DIR, METAMODULE_ARTWORK_DIR if 
    found, otherwise prompts user for the values

createInfo [input svg file name] {{optional output path for ModuleInfo file}}
    Creates a ModuleInfo struct and saves it to a file in the given path. The
    file will be named "slug_info.hh", where "slug" is the string of the text
    element with name/id "slug" found in the components layer/group of the SVG
    file. File will be overwritten if it exists.

createVcvSvg [input SVG file name] [output artwork SVG file name]
    Saves a new VCV artwork SVG file with the components layer removed.
    Also makes sure the Slug (found in the SVG file) exists as a model in the 
    VCV plugin, and adds it if not.

createCoreModule [slug] {{optional output path for CoreModule file}}
    Creates a stub CoreModule C++ class for the slug passed into the first
    parameter. If the second parameter is a valid path, the file will be saved 
    there, otherwise it will be saved to the directory pointed to by the 
    METAMODULE_COREMODULE_DIR environmant variable. File will *not* be 
    overwritten.

createLvImg [input artwork SVG file name] [output C file name]
    Converts the artwork SVG to a PNG, scales it to 240px high, and then 
    converts it to a .c file using the LVGL image converter.
    Requires these commands to be present on $PATH, or found at the env var:
        inkscape            (INKSCAPE_BIN_PATH)
        convert             (IMAGEMAGICK_BIN_PATH)

appendimglist [C array name] [path/to/image_list.hh]
    C array name is the prefix for an image array in c format, created by 
    lv_img_conv, without the _### size suffix. Example: EnOsc_artwork 
    (If the array name contains a size suffix, it will be removed and ignored.)
    The second argument is the path to the image_list.hh file that should be 
    updated with this new array. Does not update the image_list.hh file if the
    exact string to be inserted is already found. Note that the slug is the 
    first part of the C array name, up to the first underscore 
    (EnOsc_artwork => EnOsc)
""")


def parse_args(args):
    script = args.pop(0)
    if len(args) < 2:
        usage(script)
        return

    cmd = args.pop(0).lower()
    inputfile = args.pop(0)

    if cmd == 'processsvg':
        processSvg(inputfile)
        return

    if cmd == 'createinfo':
        output = args.pop(0) if len(args) > 0 else None
        infofile.createInfoFile(inputfile, output)
        return

    if cmd == 'createcoremodule':
        output = args.pop(0) if len(args) > 0 else None
        slug = inputfile
        coreModule.createCoreModule(slug, output) 
        return

    # Two args required for all other cmds:

    if len(args) == 0:
        usage(script)
        return

    output = args.pop(0)

    if cmd == 'createvcvsvg':
        vcv.extractForVcv(inputfile, output)
        return

    if cmd == 'createlvimg':
        lvgl.faceplateSvgToLVGL(inputfile, output)
        return

    if cmd == 'appendimglist':
        imageList.appendImageList(inputfile, output)

if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
