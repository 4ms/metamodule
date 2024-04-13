#!/usr/bin/env python3
import sys
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

createInfo [input svg file name] {{optional output path for ModuleInfo file}}
    Creates a ModuleInfo struct and saves it to a file in the given path. The
    file will be named "slug_info.hh", where "slug" is the string of the text
    element with name/id "slug" found in the components layer/group of the SVG
    file. File will be overwritten if it exists.

createVcvSvg [input SVG file name] [output artwork SVG file name]
    Saves a new VCV artwork SVG file with the components layer removed.

createPngFaceplate [input faceplate SVG file name] [output PNG file name] {{optional layer to extract, default=all}}
    Converts the SVG to a 47 dpi PNG file (240px/5.059in = 47.44dpi):
    If you want just one layer of the SVG to be extracted, pass that layer name as the optional 3rd argument.
    (e.g. for 4ms SVG info files, the layer to extract is called `faceplate`).
    Requires inkscape v1.2.2 and for the command to be present on PATH, or found at the env var INKSCAPE_BIN_PATH

convertSvgToPng [input SVG file name] [path for generated file]
    Converts the SVG to a 47dpi PNG format into the specified dir. The filename
    will be the same as the .svg base filename, with the .png extensions.
    Requires inkscape v1.2.2 to be on PATH or at INKSCAPE_BIN_PATH.

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

#TODO: allow to scan an entire directory for :
# -createLvglFaceplate (scan Befaco/res/modules/*.svg) + appendimglist 
# -convertSvgToLvgl (scan Befaco/res/components/*.svg) + edit elements/befaco_images.hh
# -createInfo (scan all 4ms info svg files and re-generate the info files)

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

    elif cmd == 'createpngfaceplate':
        layer = args.pop(0) if len(args) > 0 else "all"
        lvgl.faceplateSvgToPng(inputfile, output, layer)
        return

    elif cmd == 'convertsvgtopng':
        lvgl.componentSvgToPng(inputfile, output)
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
