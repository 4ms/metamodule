#!/usr/bin/env python3
import sys
from pathlib import Path
from helpers.util import *
import actions.vcv as vcv
import actions.infofile as infofile
import actions.coreModule as coreModule
import actions.lvgl as lvgl

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

Commands (case-insensitive):

createInfo [input SVG file name] {{optional output path for ModuleInfo file}}
    Creates a ModuleInfo struct and saves it to a file in the given path. The
    file will be named "slug_info.hh", where "slug" is the string of the text
    element with name/id "slug" found in the components layer/group of the SVG
    file. File will be overwritten if it exists.

createVcvSvg [input SVG file name] [output SVG file name]
    Saves a new SVG file with the 'components' layer removed.

convertSvgToPng [input SVG file name or directory] [directory for generated PNG file]
    Converts the SVG to a 47 dpi PNG file (240px/5.059in = 47.44dpi), and puts it 
    in the given directory. The filename will be the same as the .svg base
    filename, with the .png extensions.
    If a directory is given instead of a filename, then all *.svg files will be converted.
    Requires inkscape v1.2.2 and for the command to be present on PATH, or found at the env var INKSCAPE_BIN_PATH

convertFaceplateToPng [input faceplate SVG file name or directory] [directory for generated file PNG file] {{optional layer to extract, default=all}}
    Same as convertSvgToPng but ensures the PNG pixel height will be exactly 240px. 
    You also can specify a layer of the SVG to be extracted, by passing the
    layer name as the optional 3rd argument (e.g. for 4ms SVG info files, the layer to extract is called `faceplate`).
    If a directory is given instead of a filename, then all *.svg files will be converted.


""")

    extended_help = f"""
##### Not actively used: #####

processSvg [input svg file name]
    Runs createinfo and extractforvcv on the given file.
    Uses environmant variables METAMODULE_INFO_DIR, METAMODULE_ARTWORK_DIR if 
    found, otherwise prompts user for the values

addToVcvPlugin [slug] [brand name]
    Makes sure the Slug exists as a model in the VCV plugin, and adds it if not.
    Potentially modifies vcv/plugin.json, vcv/src/plugin.cc, vcv/src/plugin.hh

createCoreModule [slug] {{optional output path for CoreModule file}}
    Creates a stub CoreModule C++ class for the slug passed into the first
    parameter. If the second parameter is a valid path, the file will be saved 
    there, otherwise it will be saved to the directory pointed to by the 
    METAMODULE_COREMODULE_DIR environmant variable. File will *not* be 
    overwritten.
    """

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

    elif cmd == 'addtovcvplugin':
        slug = inputfile
        brand = output
        vcv.appendPluginFiles(slug, brand)
        return

    elif cmd == 'convertfaceplatetopng':
        layer = args.pop(0) if len(args) > 0 else "all"
        if Path(inputfile).is_file():
            lvgl.convertSvgToPng(inputfile, output, 240, layer)

        elif Path(inputfile).is_dir():
            svg_files = Path(inputfile).glob("*.svg")
            for svg_file in svg_files:
                lvgl.convertSvgToPng(str(svg_file), output)

        
        return

    elif cmd == 'convertsvgtopng':
        if Path(inputfile).is_file():
            lvgl.convertSvgToPng(inputfile, output)

        elif Path(inputfile).is_dir():
            svg_files = Path(inputfile).glob("*.svg")
            for svg_file in svg_files:
                lvgl.convertSvgToPng(str(svg_file), output)

        return

    else:
        print(f"Invalid command '{cmd}'")


if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
