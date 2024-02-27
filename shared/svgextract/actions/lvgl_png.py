import os
import re

def generate_lvgl_png_img(filename, imgname=None):
    if imgname == None:
        imgname = os.path.splitext(os.path.basename(filename))[0]

    # Remove chars that aren't a digit, letter, or underscore:
    imgname = re.sub(r"([^0-9A-Za-z_])", '', imgname)
    # prefix with "img_" if it begins with a number
    imgname = re.sub(r"(^[0-9])", r"img_\1", imgname)

    NAMECAPS = imgname.upper()

    res = f"""#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_{NAMECAPS}
#define LV_ATTRIBUTE_IMG_{NAMECAPS}
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_{NAMECAPS} uint8_t {imgname}_map[] = {{"""

    with open(filename,  "rb") as f:
        pngdata = f.read()

    byteIdx = 0
    width = 0
    height = 0

    for byte in pngdata:

        if byteIdx >= 16 and byteIdx <= 19:
            width = width * 256 + int(byte)

        if byteIdx >= 20 and byteIdx <= 23:
            height = height * 256 + int(byte)

        if byteIdx % 13 == 0:
            res += "\n    "

        res += format(byte, "#04x")


        if byteIdx < len(pngdata) - 1:
          res += ", "

        byteIdx += 1


    res += f"""
}};

const lv_img_dsc_t {imgname} = {{
  .header.cf = LV_IMG_CF_RAW_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = {width},
  .header.h = {height},
  .data_size = {byteIdx},
  .data = {imgname}_map,
}};
"""
    return res
