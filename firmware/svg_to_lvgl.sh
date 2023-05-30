#!/usr/bin/env bash
#Usage: ./svg_to_lvgl.sh InputFileName.svg OutputDir/ resize_string
#
#Where resize string is like 28x (for 28px wide, any height), or x120 (for 120px height)
#or 120x240 for 120px by 240px

OUTPATH=$(realpath $2)
SVG=$(basename $1)
IMGNAME=${SVG%%.svg}
PNG=$OUTPATH/$IMGNAME.png
C=$OUTPATH/$IMGNAME.c
inkscape --export-type="png" --export-filename=- $1  | convert -resize $3 - $PNG
cd ../shared/svgextract/lv_img_conv
./lv_img_conv.js -c CF_TRUE_COLOR --force -t c $PNG -o $C
cd ../../../firmware
ls -l $C
