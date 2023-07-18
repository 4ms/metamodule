import os
from shutil import which
import subprocess

from helpers.util import *

def faceplateSvgToLVGL(artworkSvgFilename, outputBaseName, exportLayer="all"):
    if exportLayer=="all":
        exportLayer = None

    png240Filename = outputBaseName +"_artwork_240"
    svgToLVGL(artworkSvgFilename, png240Filename, "x240", False, exportLayer)

    png120Filename = outputBaseName +"_artwork_120"
    svgToLVGL(artworkSvgFilename, png120Filename, "x120", False, exportLayer)


def componentSvgToLVGL(svgFilename, outputBaseName, scale):
    scale = float(scale)

    png240Filename = outputBaseName +"_240"
    svgToLVGL(svgFilename, png240Filename, f"{scale}%", True, None)

    png120Filename = outputBaseName +"_120"
    svgToLVGL(svgFilename, png120Filename, f"{scale/2}%", True, None)


def svgToLVGL(svgFilename, outputBaseName, resize, alpha=True, exportLayer=None):
    inkscapeBin = which('inkscape') or os.getenv('INKSCAPE_BIN_PATH')
    if inkscapeBin is None:
        Log("inkscape is not found. Please put it in your shell PATH, or set INKSCAPE_BIN_PATH to the path to the binary")
        Log("Aborting")
        return

    convertBin = which('convert') or which('magick') or os.getenv('IMAGEMAGICK_BIN_PATH')
    if convertBin is None:
        Log("convert or magick is not found. Please put it in your shell PATH, or set IMAGEMAGICK_BIN_PATH to the path to the binary")
        Log("Aborting")
        return

    # SVG ==> PNG
    pngFilename = outputBaseName + ".png"
    exportLayer = f"--export-id=\"{exportLayer}\" --export-id-only" if exportLayer else ""
    inkscape_cmd = f'{inkscapeBin} --export-type="png" {exportLayer} --export-filename=- {svgFilename}'
    convert_cmd = f'{convertBin} -resize {resize} - {pngFilename}'

    try:
        subprocess.run(f'{inkscape_cmd} | {convert_cmd}', shell=True, check=True)
        Log(f"Converted {svgFilename} to {pngFilename}, resizing to {resize}.")
    except:
        Log(f"Failed running {inkscape_cmd} | {convert_cmd}. Aborting")
        return

    # PNG ==> LVGL image (C file with array)
    lv_img_conv = os.path.dirname(os.path.realpath(__file__)) + "/../lv_img_conv/lv_img_conv.js"
    colorFormat = "CF_RAW_ALPHA"
    # colorFormat = "CF_TRUE_COLOR_ALPHA" if alpha else "CF_TRUE_COLOR"
    try:
        cFilename = os.path.realpath(os.path.splitext(pngFilename)[0]+".c")
        subprocess.run([lv_img_conv, '-c', colorFormat, '-t', 'c', '--force', pngFilename, '-o', cFilename], check=True)
        Log(f"Converted {pngFilename} to {cFilename}")

    except subprocess.CalledProcessError:
        Log("lv_img_conv.js failed. Try \n"
        " 1) `git submodule update --init` and/or \n"
        " 2) `cd ../shared/svgextract/lv_img_conv && npm install` and/or\n"
        " 3) `cd ../shared/svgextract/lv_img_conv && docker build -t lv_img_conv` \n"
        "     and then use the docker container (or not -- docker container is broken???)\n"
        " 4) `sudo n 16` to use node v16 (required) and then `cd ../shared/svgextract/lv_img_conv && npm install`.\n"
        "     Might have to install n with `npm i -g n`, and do `brew unlink node` first\n")
        return
