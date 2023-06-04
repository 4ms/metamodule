#!/usr/bin/env bash
#Usage: ./svg_to_lvgl.sh path/to/inputfile.svg path/to/output/image_name resize_string
#
# path/to/output/ is where the .c and .png files will be created
#
# image_name is the name of the C structure, like "LFO_artwork_120"
# it's also the prefix for the output file names "LFO_artwork_120.c"
# 
# resize_string is a imagemagick resize string, examples:
#   28x (for 28px wide, any height), 
#   x120 (for 120px height)
# 	120x240 (for 120px by 240px)

OUTPATH=$(realpath $(dirname $2))
IMGNAME=$(basename $2)
PNG=$OUTPATH/$IMGNAME.png
C=$OUTPATH/$IMGNAME.c
mkdir -p $OUTPATH
inkscape --export-type="png" --export-filename=- $1  | convert -resize $3 - $PNG
cd ../shared/svgextract/lv_img_conv
./lv_img_conv.js -c CF_TRUE_COLOR --force -t c $PNG -o $C
cd ../../../firmware
ls -l $C
