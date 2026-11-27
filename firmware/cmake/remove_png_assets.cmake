# Removes the PNG images from a copy of the assets dir.
# MP2 draws module faceplates and components from the SVGs in assets-svg/ only (see
# src/gui/elements/svg_file.hh), so its assets image doesn't carry the PNGs that MP1 draws.
#
# Usage: cmake -DDIR=<assets dir> -P remove_png_assets.cmake

if(NOT IS_DIRECTORY "${DIR}")
  message(FATAL_ERROR "Not a directory: '${DIR}'")
endif()

file(GLOB_RECURSE PNG_FILES "${DIR}/*.png")
if(PNG_FILES)
  file(REMOVE ${PNG_FILES})
endif()
