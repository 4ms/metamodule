import os
from shutil import which
import subprocess

from helpers import *

def createlvimg(artworkSvgFilename, outputBaseName, export_faceplate_layer = True):
    png240Filename = outputBaseName +"_artwork_240.png"
    png120Filename = outputBaseName +"_artwork_120.png"
    # Find programs needed
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
    Log(f"converting {artworkSvgFilename} to {png240Filename} and {png120Filename} with inkscape and convert.")
    export_layer = "--export-id=\"faceplate\" --export-id-only" if export_faceplate_layer else ""
    try:
        subprocess.run(f'{inkscapeBin} --export-type="png" {export_layer} --export-filename=- {artworkSvgFilename} | {convertBin} -resize x240 - {png240Filename}', shell=True, check=True)
        subprocess.run(f'{inkscapeBin} --export-type="png" {export_layer} --export-filename=- {artworkSvgFilename} | {convertBin} -resize x120 - {png120Filename}', shell=True, check=True)
    except:
        Log(f"Failed running {inkscapeBin} and {convertBin}. Aborting")
        return

    # PNG ==> LVGL image (C file with array)
    lv_img_conv = os.path.dirname(os.path.realpath(__file__)) + "/lv_img_conv/lv_img_conv.js"
    try:
        c240Filename = os.path.realpath(os.path.splitext(png240Filename)[0]+".c")
        subprocess.run([lv_img_conv, '-c', 'CF_TRUE_COLOR', '-t', 'c', '--force', png240Filename, '-o', c240Filename], check=True)
        Log(f"Created {png240Filename.strip('.png')}.c file from {png240Filename} with:\n"
            f"    {lv_img_conv} -c CF_TRUE_COLOR -t c --force {png240Filename} -o {c240Filename}")

        c120Filename = os.path.realpath(os.path.splitext(png120Filename)[0]+".c")
        subprocess.run([lv_img_conv, '-c', 'CF_TRUE_COLOR', '-t', 'c', '--force', png120Filename, '-o', c120Filename], check=True)
        Log(f"Created {png120Filename.strip('.png')}.c file from {png120Filename}")
    except subprocess.CalledProcessError:
        Log("lv_img_conv.js failed. Try "
        " 1) `git submodule update --init` and/or "
        " 2) `cd ../shared/svgextract/lv_img_conv && npm install`"
        " 3) `cd ../shared/svgextract/lv_img_conv && docker build -t lv_img_conv` and then use the docker container (or not -- docker container is broken???)"
        " 4) `sudo n 16` to use node v16 (required) and then `cd ../shared/svgextract/lv_img_conv && npm install`. Might have to install n with `npm i -g n`, and do `brew unlink node` first")
        return


