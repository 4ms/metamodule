import os
from shutil import which
import subprocess
import re

from helpers.util import *

def convertSvgToPng(svgFilename, outputDir, resize=0, exportLayer="all"):
    outputDir = outputDir.rstrip("/") + "/"
    png240Filename = outputDir + os.path.splitext(os.path.basename(svgFilename))[0] + ".png"
    svgToPng(svgFilename, png240Filename, resize, exportLayer)


def svgToPng(svgFilename, pngFilename, resize=0, exportLayer="all"):
    inkscapeBin = which('inkscape') or os.getenv('INKSCAPE_BIN_PATH')
    if inkscapeBin is None:
        Log("inkscape is not found. Please put it in your shell PATH, or set INKSCAPE_BIN_PATH to the path to the binary")
        Log("Aborting")
        return

    exportLayer = f"--export-id=\"{exportLayer}\" --export-id-only" if exportLayer != "all" else ""

    if resize == 0:
        dpi = determine_dpi(svgFilename)
        export_size = f"--export-dpi={dpi}"
    else:
        dpi = f"x{resize}"
        export_size = f"--export-height={resize}"

    inkscape_cmd = f'{inkscapeBin} --export-type="png" {exportLayer} --export-png-use-dithering=false {export_size} --export-filename=\"{pngFilename}\" {svgFilename}'

    try:
        subprocess.run(f'{inkscape_cmd}', shell=True, check=True)
        Log(f"Converted {svgFilename} to {os.path.basename(pngFilename)} at {dpi} dpi.")
    except:
        Log(f"Failed running {inkscape_cmd}. Aborting")
        return


def determine_dpi(filename):
    # Workaround for different SVGs;
    # Some need to be exported at 47.44 DPI (which makes sense since 240px screen = 5.059" module)
    # But it seems some are scaled by a factor of 96/75, so they need to be exported at 60.72 DPI
    # I don't know the reason, but the common factor seems to be width="*mm" in the file
    if "4ms/components/" in filename:
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

