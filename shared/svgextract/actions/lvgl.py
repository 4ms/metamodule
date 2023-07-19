import os
from shutil import which
import subprocess
import re

from helpers.util import *

def faceplateSvgToLVGL(artworkSvgFilename, outputBaseName, exportLayer="all"):
    if exportLayer=="all":
        exportLayer = None
    png240Filename = outputBaseName +"_artwork_240"
    svgToLVGL(artworkSvgFilename, png240Filename, 240, False, exportLayer)


def componentSvgToLVGL(svgFilename, outputBaseName, scale):
    scale = float(scale)
    png240Filename = outputBaseName.rstrip(".c")
    svgToLVGL(svgFilename, png240Filename)


def svgToLVGL(svgFilename, outputBaseName, resize=0, alpha=True, exportLayer=None):
    inkscapeBin = which('inkscape') or os.getenv('INKSCAPE_BIN_PATH')
    if inkscapeBin is None:
        Log("inkscape is not found. Please put it in your shell PATH, or set INKSCAPE_BIN_PATH to the path to the binary")
        Log("Aborting")
        return

    # SVG ==> PNG
    pngFilename = outputBaseName + ".png"
    exportLayer = f"--export-id=\"{exportLayer}\" --export-id-only" if exportLayer else ""


    if resize == 0:
        dpi = determine_dpi(svgFilename)
        export_size = f"--export-dpi={dpi}"
    else:
        dpi = f"x{resize}"
        export_size = f"--export-height={resize}"

    inkscape_cmd = f'{inkscapeBin} --export-type="png" {exportLayer} --export-png-use-dithering=false {export_size} --export-filename={pngFilename} {svgFilename}'

    try:
        subprocess.run(f'{inkscape_cmd}', shell=True, check=True)
        Log(f"Converted {svgFilename} to {os.path.basename(pngFilename)} at {dpi} dpi.")
    except:
        Log(f"Failed running {inkscape_cmd}. Aborting")
        return

    # PNG ==> LVGL image (C file with array)
    lv_img_conv = os.path.dirname(os.path.realpath(__file__)) + "/../lv_img_conv/lv_img_conv.js"
    colorFormat = "CF_RAW_ALPHA"
    # colorFormat = "CF_TRUE_COLOR_ALPHA" if alpha else "CF_TRUE_COLOR"
    try:
        cFilename = os.path.realpath(os.path.splitext(pngFilename)[0]+".c")
        subprocess.run([lv_img_conv, '-c', colorFormat, '-t', 'c', '--force', pngFilename, '-o', cFilename], check=True)
        #Log(f"Converted {pngFilename} to {cFilename}")

    except subprocess.CalledProcessError:
        Log("lv_img_conv.js failed. Try \n"
        " 1) `git submodule update --init` and/or \n"
        " 2) `cd ../shared/svgextract/lv_img_conv && npm install` and/or\n"
        " 3) `cd ../shared/svgextract/lv_img_conv && docker build -t lv_img_conv` \n"
        "     and then use the docker container (or not -- docker container is broken???)\n"
        " 4) `sudo n 16` to use node v16 (required) and then `cd ../shared/svgextract/lv_img_conv && npm install`.\n"
        "     Might have to install n with `npm i -g n`, and do `brew unlink node` first\n")
        return

def determine_dpi(filename):
    # Workaround for different SVGs;
    # Some need to be exported at 47.44 DPI (which makes sense since 240px screen = 5.059" module)
    # But it seems some are scaled by a factor of 96/75, so they need to be exported at 60.72 DPI
    # I don't know the reason, but the common factor seems to be width="*mm" in the file
    if "4ms" in filename:
        return 60.72

    with open(filename, 'r') as fp:
        contents = fp.read()
        m = re.search('width=".+mm"',contents)
        if m is None:
            return 60.72
        if m.group(0) is None:
            return 60.72
        else:
            return 47.44

