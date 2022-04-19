# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=320,h=240)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(320*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 320
disp_drv.ver_res = 240
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.add_flag(lv.obj.FLAG.HIDDEN)


patch_selection = lv.obj()
# create style style_patch_selection_main_main_default
style_patch_selection_main_main_default = lv.style_t()
style_patch_selection_main_main_default.init()
style_patch_selection_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_patch_selection_main_main_default.set_bg_opa(255)

# add style for patch_selection
patch_selection.add_style(style_patch_selection_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_back = lv.btn(patch_selection)
patch_selection_back.set_pos(4,4)
patch_selection_back.set_size(50,25)
patch_selection_back_label = lv.label(patch_selection_back)
patch_selection_back_label.set_text("BACK")
patch_selection_back.set_style_pad_all(0, lv.STATE.DEFAULT)
patch_selection_back_label.align(lv.ALIGN.CENTER,0,0)
patch_selection_back_label.set_style_text_color(lv.color_make(0x32,0x32,0x32), lv.STATE.DEFAULT)
try:
    patch_selection_back_label.set_style_text_font(lv.font_MuseoSansCondensed_700_12, lv.STATE.DEFAULT)
except AttributeError:
    try:
        patch_selection_back_label.set_style_text_font(lv.font_montserrat_12, lv.STATE.DEFAULT)
    except AttributeError:
        patch_selection_back_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_patch_selection_back_main_main_default
style_patch_selection_back_main_main_default = lv.style_t()
style_patch_selection_back_main_main_default.init()
style_patch_selection_back_main_main_default.set_radius(4)
style_patch_selection_back_main_main_default.set_bg_color(lv.color_make(0xfe,0xe4,0x63))
style_patch_selection_back_main_main_default.set_bg_grad_color(lv.color_make(0xfe,0xe4,0x63))
style_patch_selection_back_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_back_main_main_default.set_bg_opa(255)
style_patch_selection_back_main_main_default.set_shadow_color(lv.color_make(0x32,0x32,0x32))
style_patch_selection_back_main_main_default.set_shadow_opa(255)
style_patch_selection_back_main_main_default.set_border_color(lv.color_make(0xc8,0xc8,0xc8))
style_patch_selection_back_main_main_default.set_border_width(2)
style_patch_selection_back_main_main_default.set_border_opa(255)

# add style for patch_selection_back
patch_selection_back.add_style(style_patch_selection_back_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_next = lv.btn(patch_selection)
patch_selection_next.set_pos(266,4)
patch_selection_next.set_size(50,25)
patch_selection_next_label = lv.label(patch_selection_next)
patch_selection_next_label.set_text("NEXT")
patch_selection_next.set_style_pad_all(0, lv.STATE.DEFAULT)
patch_selection_next_label.align(lv.ALIGN.CENTER,0,0)
patch_selection_next_label.set_style_text_color(lv.color_make(0x32,0x32,0x32), lv.STATE.DEFAULT)
try:
    patch_selection_next_label.set_style_text_font(lv.font_MuseoSansCondensed_700_12, lv.STATE.DEFAULT)
except AttributeError:
    try:
        patch_selection_next_label.set_style_text_font(lv.font_montserrat_12, lv.STATE.DEFAULT)
    except AttributeError:
        patch_selection_next_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_patch_selection_next_main_main_default
style_patch_selection_next_main_main_default = lv.style_t()
style_patch_selection_next_main_main_default.init()
style_patch_selection_next_main_main_default.set_radius(4)
style_patch_selection_next_main_main_default.set_bg_color(lv.color_make(0xfe,0xe4,0x63))
style_patch_selection_next_main_main_default.set_bg_grad_color(lv.color_make(0xfe,0xe4,0x63))
style_patch_selection_next_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_next_main_main_default.set_bg_opa(255)
style_patch_selection_next_main_main_default.set_shadow_color(lv.color_make(0x32,0x32,0x32))
style_patch_selection_next_main_main_default.set_shadow_opa(255)
style_patch_selection_next_main_main_default.set_border_color(lv.color_make(0xc8,0xc8,0xc8))
style_patch_selection_next_main_main_default.set_border_width(2)
style_patch_selection_next_main_main_default.set_border_opa(255)

# add style for patch_selection_next
patch_selection_next.add_style(style_patch_selection_next_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_play = lv.btn(patch_selection)
patch_selection_play.set_pos(265,211)
patch_selection_play.set_size(50,25)
patch_selection_play_label = lv.label(patch_selection_play)
patch_selection_play_label.set_text("PLAY")
patch_selection_play.set_style_pad_all(0, lv.STATE.DEFAULT)
patch_selection_play_label.align(lv.ALIGN.CENTER,0,0)
patch_selection_play_label.set_style_text_color(lv.color_make(0x32,0x32,0x32), lv.STATE.DEFAULT)
try:
    patch_selection_play_label.set_style_text_font(lv.font_MuseoSansCondensed_700_12, lv.STATE.DEFAULT)
except AttributeError:
    try:
        patch_selection_play_label.set_style_text_font(lv.font_montserrat_12, lv.STATE.DEFAULT)
    except AttributeError:
        patch_selection_play_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_patch_selection_play_main_main_default
style_patch_selection_play_main_main_default = lv.style_t()
style_patch_selection_play_main_main_default.init()
style_patch_selection_play_main_main_default.set_radius(4)
style_patch_selection_play_main_main_default.set_bg_color(lv.color_make(0xba,0xdd,0xa4))
style_patch_selection_play_main_main_default.set_bg_grad_color(lv.color_make(0xba,0xdd,0xa4))
style_patch_selection_play_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_play_main_main_default.set_bg_opa(255)
style_patch_selection_play_main_main_default.set_shadow_color(lv.color_make(0x32,0x32,0x32))
style_patch_selection_play_main_main_default.set_shadow_opa(255)
style_patch_selection_play_main_main_default.set_border_color(lv.color_make(0xc8,0xc8,0xc8))
style_patch_selection_play_main_main_default.set_border_width(2)
style_patch_selection_play_main_main_default.set_border_opa(255)

# add style for patch_selection_play
patch_selection_play.add_style(style_patch_selection_play_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_description = lv.label(patch_selection)
patch_selection_description.set_pos(5,34)
patch_selection_description.set_size(310,73)
patch_selection_description.set_text("Patch Description Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam")
patch_selection_description.set_long_mode(lv.label.LONG.WRAP)
patch_selection_description.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_patch_selection_description_main_main_default
style_patch_selection_description_main_main_default = lv.style_t()
style_patch_selection_description_main_main_default.init()
style_patch_selection_description_main_main_default.set_radius(4)
style_patch_selection_description_main_main_default.set_bg_color(lv.color_make(0xcc,0xcc,0xcc))
style_patch_selection_description_main_main_default.set_bg_grad_color(lv.color_make(0x91,0x91,0x91))
style_patch_selection_description_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_description_main_main_default.set_bg_opa(0)
style_patch_selection_description_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_patch_selection_description_main_main_default.set_text_font(lv.font_MuseoSansCondensed_500Italic_13)
except AttributeError:
    try:
        style_patch_selection_description_main_main_default.set_text_font(lv.font_montserrat_13)
    except AttributeError:
        style_patch_selection_description_main_main_default.set_text_font(lv.font_montserrat_16)
style_patch_selection_description_main_main_default.set_text_letter_space(2)
style_patch_selection_description_main_main_default.set_pad_left(0)
style_patch_selection_description_main_main_default.set_pad_right(0)
style_patch_selection_description_main_main_default.set_pad_top(0)
style_patch_selection_description_main_main_default.set_pad_bottom(0)

# add style for patch_selection_description
patch_selection_description.add_style(style_patch_selection_description_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_modules = lv.obj(patch_selection)
patch_selection_modules.set_pos(0,115)
patch_selection_modules.set_size(320,125)
# create style style_patch_selection_modules_main_main_default
style_patch_selection_modules_main_main_default = lv.style_t()
style_patch_selection_modules_main_main_default.init()
style_patch_selection_modules_main_main_default.set_radius(0)
style_patch_selection_modules_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_patch_selection_modules_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_patch_selection_modules_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_modules_main_main_default.set_bg_opa(0)
style_patch_selection_modules_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_patch_selection_modules_main_main_default.set_border_width(0)
style_patch_selection_modules_main_main_default.set_border_opa(255)
style_patch_selection_modules_main_main_default.set_pad_left(0)
style_patch_selection_modules_main_main_default.set_pad_right(0)
style_patch_selection_modules_main_main_default.set_pad_top(0)
style_patch_selection_modules_main_main_default.set_pad_bottom(0)

# add style for patch_selection_modules
patch_selection_modules.add_style(style_patch_selection_modules_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_selection = lv.dropdown(patch_selection)
patch_selection_selection.set_pos(60,4)
patch_selection_selection.set_width(200)
patch_selection_selection.set_options("PATCH NAME\nDJEMBE\nSTEREO DELAY")
patch_selection_selection.set_symbol(lv.SYMBOL.UP)
# create style style_patch_selection_selection_extra_list_selected_default
style_patch_selection_selection_extra_list_selected_default = lv.style_t()
style_patch_selection_selection_extra_list_selected_default.init()
style_patch_selection_selection_extra_list_selected_default.set_radius(4)
style_patch_selection_selection_extra_list_selected_default.set_bg_color(lv.color_make(0xff,0xc3,0x70))
style_patch_selection_selection_extra_list_selected_default.set_bg_grad_color(lv.color_make(0xff,0xc3,0x70))
style_patch_selection_selection_extra_list_selected_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_selection_extra_list_selected_default.set_bg_opa(255)
style_patch_selection_selection_extra_list_selected_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_patch_selection_selection_extra_list_selected_default.set_border_width(1)
style_patch_selection_selection_extra_list_selected_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_patch_selection_selection_extra_list_selected_default.set_text_font(lv.font_MuseoSansCondensed_300_12)
except AttributeError:
    try:
        style_patch_selection_selection_extra_list_selected_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_patch_selection_selection_extra_list_selected_default.set_text_font(lv.font_montserrat_16)

def patch_selection_selection_event_cb(e):
    patch_selection_selection.get_list().add_style(style_patch_selection_selection_extra_list_selected_default, lv.PART.SELECTED|lv.STATE.DEFAULT)

patch_selection_selection.add_event_cb(patch_selection_selection_event_cb, lv.EVENT.READY, None)

# create style style_patch_selection_selection_extra_list_main_default
style_patch_selection_selection_extra_list_main_default = lv.style_t()
style_patch_selection_selection_extra_list_main_default.init()
style_patch_selection_selection_extra_list_main_default.set_radius(4)
style_patch_selection_selection_extra_list_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_patch_selection_selection_extra_list_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_patch_selection_selection_extra_list_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_selection_extra_list_main_default.set_bg_opa(255)
style_patch_selection_selection_extra_list_main_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_patch_selection_selection_extra_list_main_default.set_border_width(2)
style_patch_selection_selection_extra_list_main_default.set_text_color(lv.color_make(0x32,0x32,0x32))
try:
    style_patch_selection_selection_extra_list_main_default.set_text_font(lv.font_MuseoSansCondensed_300_12)
except AttributeError:
    try:
        style_patch_selection_selection_extra_list_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_patch_selection_selection_extra_list_main_default.set_text_font(lv.font_montserrat_16)
style_patch_selection_selection_extra_list_main_default.set_max_height(90)

def patch_selection_selection_event_cb(e):
    patch_selection_selection.get_list().add_style(style_patch_selection_selection_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

patch_selection_selection.add_event_cb(patch_selection_selection_event_cb, lv.EVENT.READY, None)

# create style style_patch_selection_selection_extra_list_scrollbar_default
style_patch_selection_selection_extra_list_scrollbar_default = lv.style_t()
style_patch_selection_selection_extra_list_scrollbar_default.init()
style_patch_selection_selection_extra_list_scrollbar_default.set_radius(3)
style_patch_selection_selection_extra_list_scrollbar_default.set_bg_color(lv.color_make(0x00,0xff,0x00))
style_patch_selection_selection_extra_list_scrollbar_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_patch_selection_selection_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_selection_extra_list_scrollbar_default.set_bg_opa(255)

def patch_selection_selection_event_cb(e):
    patch_selection_selection.get_list().add_style(style_patch_selection_selection_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

patch_selection_selection.add_event_cb(patch_selection_selection_event_cb, lv.EVENT.READY, None)

# create style style_patch_selection_selection_main_main_default
style_patch_selection_selection_main_main_default = lv.style_t()
style_patch_selection_selection_main_main_default.init()
style_patch_selection_selection_main_main_default.set_radius(4)
style_patch_selection_selection_main_main_default.set_bg_color(lv.color_make(0xf5,0xf5,0xf5))
style_patch_selection_selection_main_main_default.set_bg_grad_color(lv.color_make(0xf5,0xf5,0xf5))
style_patch_selection_selection_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_patch_selection_selection_main_main_default.set_bg_opa(255)
style_patch_selection_selection_main_main_default.set_border_color(lv.color_make(0xc8,0xc8,0xc8))
style_patch_selection_selection_main_main_default.set_border_width(2)
style_patch_selection_selection_main_main_default.set_text_color(lv.color_make(0x1c,0x1c,0x1c))
try:
    style_patch_selection_selection_main_main_default.set_text_font(lv.font_MuseoSansRounded_700_14)
except AttributeError:
    try:
        style_patch_selection_selection_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_patch_selection_selection_main_main_default.set_text_font(lv.font_montserrat_16)
style_patch_selection_selection_main_main_default.set_text_line_space(20)

# add style for patch_selection_selection
patch_selection_selection.add_style(style_patch_selection_selection_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view = lv.obj()
# create style style_knob_button_view_main_main_default
style_knob_button_view_main_main_default = lv.style_t()
style_knob_button_view_main_main_default.init()
style_knob_button_view_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_knob_button_view_main_main_default.set_bg_opa(255)

# add style for knob_button_view
knob_button_view.add_style(style_knob_button_view_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_arc_1 = lv.arc(knob_button_view)
knob_button_view_arc_1.set_pos(30,10)
knob_button_view_arc_1.set_size(60,60)
knob_button_view_arc_1.set_bg_angles(120, 60)
knob_button_view_arc_1.set_angles(120, 220)
knob_button_view_arc_1.set_rotation(0)
knob_button_view_arc_1.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_1.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_1.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_1.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_1_main_main_default
style_knob_button_view_arc_1_main_main_default = lv.style_t()
style_knob_button_view_arc_1_main_main_default.init()
style_knob_button_view_arc_1_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_1_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_1_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_1_main_main_default.set_border_width(0)
style_knob_button_view_arc_1_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_1_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_1
knob_button_view_arc_1.add_style(style_knob_button_view_arc_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_1_main_indicator_default
style_knob_button_view_arc_1_main_indicator_default = lv.style_t()
style_knob_button_view_arc_1_main_indicator_default.init()
style_knob_button_view_arc_1_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_button_view_arc_1_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_1
knob_button_view_arc_1.add_style(style_knob_button_view_arc_1_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_1_main_knob_default
style_knob_button_view_arc_1_main_knob_default = lv.style_t()
style_knob_button_view_arc_1_main_knob_default.init()
style_knob_button_view_arc_1_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_1_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_1_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_1_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_1_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_1
knob_button_view_arc_1.add_style(style_knob_button_view_arc_1_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_2 = lv.arc(knob_button_view)
knob_button_view_arc_2.set_pos(130,10)
knob_button_view_arc_2.set_size(60,60)
knob_button_view_arc_2.set_bg_angles(120, 60)
knob_button_view_arc_2.set_angles(120, 220)
knob_button_view_arc_2.set_rotation(0)
knob_button_view_arc_2.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_2.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_2.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_2.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_2_main_main_default
style_knob_button_view_arc_2_main_main_default = lv.style_t()
style_knob_button_view_arc_2_main_main_default.init()
style_knob_button_view_arc_2_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_2_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_2_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_2_main_main_default.set_border_width(0)
style_knob_button_view_arc_2_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_2_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_2
knob_button_view_arc_2.add_style(style_knob_button_view_arc_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_2_main_indicator_default
style_knob_button_view_arc_2_main_indicator_default = lv.style_t()
style_knob_button_view_arc_2_main_indicator_default.init()
style_knob_button_view_arc_2_main_indicator_default.set_arc_color(lv.color_make(0xfe,0xe4,0x63))
style_knob_button_view_arc_2_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_2
knob_button_view_arc_2.add_style(style_knob_button_view_arc_2_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_2_main_knob_default
style_knob_button_view_arc_2_main_knob_default = lv.style_t()
style_knob_button_view_arc_2_main_knob_default.init()
style_knob_button_view_arc_2_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_2_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_2_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_2_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_2_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_2
knob_button_view_arc_2.add_style(style_knob_button_view_arc_2_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_3 = lv.arc(knob_button_view)
knob_button_view_arc_3.set_pos(230,10)
knob_button_view_arc_3.set_size(60,60)
knob_button_view_arc_3.set_bg_angles(120, 60)
knob_button_view_arc_3.set_angles(120, 220)
knob_button_view_arc_3.set_rotation(0)
knob_button_view_arc_3.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_3.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_3.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_3.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_3_main_main_default
style_knob_button_view_arc_3_main_main_default = lv.style_t()
style_knob_button_view_arc_3_main_main_default.init()
style_knob_button_view_arc_3_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_3_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_3_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_3_main_main_default.set_border_width(0)
style_knob_button_view_arc_3_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_3_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_3
knob_button_view_arc_3.add_style(style_knob_button_view_arc_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_3_main_indicator_default
style_knob_button_view_arc_3_main_indicator_default = lv.style_t()
style_knob_button_view_arc_3_main_indicator_default.init()
style_knob_button_view_arc_3_main_indicator_default.set_arc_color(lv.color_make(0xaa,0xa7,0xd7))
style_knob_button_view_arc_3_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_3
knob_button_view_arc_3.add_style(style_knob_button_view_arc_3_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_3_main_knob_default
style_knob_button_view_arc_3_main_knob_default = lv.style_t()
style_knob_button_view_arc_3_main_knob_default.init()
style_knob_button_view_arc_3_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_3_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_3_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_3_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_3_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_3
knob_button_view_arc_3.add_style(style_knob_button_view_arc_3_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_4 = lv.arc(knob_button_view)
knob_button_view_arc_4.set_pos(30,90)
knob_button_view_arc_4.set_size(60,60)
knob_button_view_arc_4.set_bg_angles(120, 60)
knob_button_view_arc_4.set_angles(120, 220)
knob_button_view_arc_4.set_rotation(0)
knob_button_view_arc_4.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_4.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_4.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_4.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_4_main_main_default
style_knob_button_view_arc_4_main_main_default = lv.style_t()
style_knob_button_view_arc_4_main_main_default.init()
style_knob_button_view_arc_4_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_4_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_4_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_4_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_4_main_main_default.set_border_width(0)
style_knob_button_view_arc_4_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_4_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_4
knob_button_view_arc_4.add_style(style_knob_button_view_arc_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_4_main_indicator_default
style_knob_button_view_arc_4_main_indicator_default = lv.style_t()
style_knob_button_view_arc_4_main_indicator_default.init()
style_knob_button_view_arc_4_main_indicator_default.set_arc_color(lv.color_make(0x4b,0xaf,0xfa))
style_knob_button_view_arc_4_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_4
knob_button_view_arc_4.add_style(style_knob_button_view_arc_4_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_4_main_knob_default
style_knob_button_view_arc_4_main_knob_default = lv.style_t()
style_knob_button_view_arc_4_main_knob_default.init()
style_knob_button_view_arc_4_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_4_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_4_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_4_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_4_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_4
knob_button_view_arc_4.add_style(style_knob_button_view_arc_4_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_5 = lv.arc(knob_button_view)
knob_button_view_arc_5.set_pos(130,90)
knob_button_view_arc_5.set_size(60,60)
knob_button_view_arc_5.set_bg_angles(120, 60)
knob_button_view_arc_5.set_angles(120, 220)
knob_button_view_arc_5.set_rotation(0)
knob_button_view_arc_5.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_5.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_5.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_5.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_5_main_main_default
style_knob_button_view_arc_5_main_main_default = lv.style_t()
style_knob_button_view_arc_5_main_main_default.init()
style_knob_button_view_arc_5_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_5_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_5_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_5_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_5_main_main_default.set_border_width(0)
style_knob_button_view_arc_5_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_5_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_5
knob_button_view_arc_5.add_style(style_knob_button_view_arc_5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_5_main_indicator_default
style_knob_button_view_arc_5_main_indicator_default = lv.style_t()
style_knob_button_view_arc_5_main_indicator_default.init()
style_knob_button_view_arc_5_main_indicator_default.set_arc_color(lv.color_make(0x87,0xd7,0xc8))
style_knob_button_view_arc_5_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_5
knob_button_view_arc_5.add_style(style_knob_button_view_arc_5_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_5_main_knob_default
style_knob_button_view_arc_5_main_knob_default = lv.style_t()
style_knob_button_view_arc_5_main_knob_default.init()
style_knob_button_view_arc_5_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_5_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_5_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_5_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_5_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_5
knob_button_view_arc_5.add_style(style_knob_button_view_arc_5_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_6 = lv.arc(knob_button_view)
knob_button_view_arc_6.set_pos(230,90)
knob_button_view_arc_6.set_size(60,60)
knob_button_view_arc_6.set_bg_angles(120, 60)
knob_button_view_arc_6.set_angles(120, 220)
knob_button_view_arc_6.set_rotation(0)
knob_button_view_arc_6.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_6.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_6.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_6.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_6_main_main_default
style_knob_button_view_arc_6_main_main_default = lv.style_t()
style_knob_button_view_arc_6_main_main_default.init()
style_knob_button_view_arc_6_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_6_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_6_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_6_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_6_main_main_default.set_border_width(0)
style_knob_button_view_arc_6_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_button_view_arc_6_main_main_default.set_arc_width(16)

# add style for knob_button_view_arc_6
knob_button_view_arc_6.add_style(style_knob_button_view_arc_6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_6_main_indicator_default
style_knob_button_view_arc_6_main_indicator_default = lv.style_t()
style_knob_button_view_arc_6_main_indicator_default.init()
style_knob_button_view_arc_6_main_indicator_default.set_arc_color(lv.color_make(0xff,0xc3,0x70))
style_knob_button_view_arc_6_main_indicator_default.set_arc_width(16)

# add style for knob_button_view_arc_6
knob_button_view_arc_6.add_style(style_knob_button_view_arc_6_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_6_main_knob_default
style_knob_button_view_arc_6_main_knob_default = lv.style_t()
style_knob_button_view_arc_6_main_knob_default.init()
style_knob_button_view_arc_6_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_6_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_6_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_6_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_6_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_6
knob_button_view_arc_6.add_style(style_knob_button_view_arc_6_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_7 = lv.arc(knob_button_view)
knob_button_view_arc_7.set_pos(26,6)
knob_button_view_arc_7.set_size(68,68)
knob_button_view_arc_7.set_bg_angles(120, 60)
knob_button_view_arc_7.set_angles(120, 220)
knob_button_view_arc_7.set_rotation(0)
knob_button_view_arc_7.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_7.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_7.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_7.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_7_main_main_default
style_knob_button_view_arc_7_main_main_default = lv.style_t()
style_knob_button_view_arc_7_main_main_default.init()
style_knob_button_view_arc_7_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_7_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_7_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_7_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_7_main_main_default.set_border_width(0)
style_knob_button_view_arc_7_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_7_main_main_default.set_arc_width(4)

# add style for knob_button_view_arc_7
knob_button_view_arc_7.add_style(style_knob_button_view_arc_7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_7_main_indicator_default
style_knob_button_view_arc_7_main_indicator_default = lv.style_t()
style_knob_button_view_arc_7_main_indicator_default.init()
style_knob_button_view_arc_7_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_7_main_indicator_default.set_arc_width(1)

# add style for knob_button_view_arc_7
knob_button_view_arc_7.add_style(style_knob_button_view_arc_7_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_7_main_knob_default
style_knob_button_view_arc_7_main_knob_default = lv.style_t()
style_knob_button_view_arc_7_main_knob_default.init()
style_knob_button_view_arc_7_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_7_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_7_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_7_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_7_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_7
knob_button_view_arc_7.add_style(style_knob_button_view_arc_7_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_8 = lv.arc(knob_button_view)
knob_button_view_arc_8.set_pos(126,6)
knob_button_view_arc_8.set_size(68,68)
knob_button_view_arc_8.set_bg_angles(120, 60)
knob_button_view_arc_8.set_angles(120, 220)
knob_button_view_arc_8.set_rotation(0)
knob_button_view_arc_8.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_8.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_8.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_8.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_8_main_main_default
style_knob_button_view_arc_8_main_main_default = lv.style_t()
style_knob_button_view_arc_8_main_main_default.init()
style_knob_button_view_arc_8_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_8_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_8_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_8_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_8_main_main_default.set_border_width(0)
style_knob_button_view_arc_8_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_8_main_main_default.set_arc_width(3)

# add style for knob_button_view_arc_8
knob_button_view_arc_8.add_style(style_knob_button_view_arc_8_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_8_main_indicator_default
style_knob_button_view_arc_8_main_indicator_default = lv.style_t()
style_knob_button_view_arc_8_main_indicator_default.init()
style_knob_button_view_arc_8_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_8_main_indicator_default.set_arc_width(1)

# add style for knob_button_view_arc_8
knob_button_view_arc_8.add_style(style_knob_button_view_arc_8_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_8_main_knob_default
style_knob_button_view_arc_8_main_knob_default = lv.style_t()
style_knob_button_view_arc_8_main_knob_default.init()
style_knob_button_view_arc_8_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_8_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_8_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_8_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_8_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_8
knob_button_view_arc_8.add_style(style_knob_button_view_arc_8_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_9 = lv.arc(knob_button_view)
knob_button_view_arc_9.set_pos(225,5)
knob_button_view_arc_9.set_size(70,70)
knob_button_view_arc_9.set_bg_angles(120, 60)
knob_button_view_arc_9.set_angles(120, 220)
knob_button_view_arc_9.set_rotation(0)
knob_button_view_arc_9.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_9.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_9.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_9.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_9_main_main_default
style_knob_button_view_arc_9_main_main_default = lv.style_t()
style_knob_button_view_arc_9_main_main_default.init()
style_knob_button_view_arc_9_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_9_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_9_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_9_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_9_main_main_default.set_border_width(0)
style_knob_button_view_arc_9_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_9_main_main_default.set_arc_width(3)

# add style for knob_button_view_arc_9
knob_button_view_arc_9.add_style(style_knob_button_view_arc_9_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_9_main_indicator_default
style_knob_button_view_arc_9_main_indicator_default = lv.style_t()
style_knob_button_view_arc_9_main_indicator_default.init()
style_knob_button_view_arc_9_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_9_main_indicator_default.set_arc_width(1)

# add style for knob_button_view_arc_9
knob_button_view_arc_9.add_style(style_knob_button_view_arc_9_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_9_main_knob_default
style_knob_button_view_arc_9_main_knob_default = lv.style_t()
style_knob_button_view_arc_9_main_knob_default.init()
style_knob_button_view_arc_9_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_9_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_9_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_9_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_9_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_9
knob_button_view_arc_9.add_style(style_knob_button_view_arc_9_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_10 = lv.arc(knob_button_view)
knob_button_view_arc_10.set_pos(26,86)
knob_button_view_arc_10.set_size(68,68)
knob_button_view_arc_10.set_bg_angles(120, 60)
knob_button_view_arc_10.set_angles(120, 220)
knob_button_view_arc_10.set_rotation(0)
knob_button_view_arc_10.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_10.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_10.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_10.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_10_main_main_default
style_knob_button_view_arc_10_main_main_default = lv.style_t()
style_knob_button_view_arc_10_main_main_default.init()
style_knob_button_view_arc_10_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_10_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_10_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_10_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_10_main_main_default.set_border_width(0)
style_knob_button_view_arc_10_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_10_main_main_default.set_arc_width(2)

# add style for knob_button_view_arc_10
knob_button_view_arc_10.add_style(style_knob_button_view_arc_10_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_10_main_indicator_default
style_knob_button_view_arc_10_main_indicator_default = lv.style_t()
style_knob_button_view_arc_10_main_indicator_default.init()
style_knob_button_view_arc_10_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_10_main_indicator_default.set_arc_width(1)

# add style for knob_button_view_arc_10
knob_button_view_arc_10.add_style(style_knob_button_view_arc_10_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_10_main_knob_default
style_knob_button_view_arc_10_main_knob_default = lv.style_t()
style_knob_button_view_arc_10_main_knob_default.init()
style_knob_button_view_arc_10_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_10_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_10_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_10_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_10_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_10
knob_button_view_arc_10.add_style(style_knob_button_view_arc_10_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_12 = lv.arc(knob_button_view)
knob_button_view_arc_12.set_pos(125,85)
knob_button_view_arc_12.set_size(70,70)
knob_button_view_arc_12.set_bg_angles(170, 10)
knob_button_view_arc_12.set_angles(170, 10)
knob_button_view_arc_12.set_rotation(0)
knob_button_view_arc_12.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_12.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_12.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_12.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_12_main_main_default
style_knob_button_view_arc_12_main_main_default = lv.style_t()
style_knob_button_view_arc_12_main_main_default.init()
style_knob_button_view_arc_12_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_12_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_12_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_12_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_12_main_main_default.set_border_width(0)
style_knob_button_view_arc_12_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_12_main_main_default.set_arc_width(3)

# add style for knob_button_view_arc_12
knob_button_view_arc_12.add_style(style_knob_button_view_arc_12_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_12_main_indicator_default
style_knob_button_view_arc_12_main_indicator_default = lv.style_t()
style_knob_button_view_arc_12_main_indicator_default.init()
style_knob_button_view_arc_12_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_12_main_indicator_default.set_arc_width(1)

# add style for knob_button_view_arc_12
knob_button_view_arc_12.add_style(style_knob_button_view_arc_12_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_12_main_knob_default
style_knob_button_view_arc_12_main_knob_default = lv.style_t()
style_knob_button_view_arc_12_main_knob_default.init()
style_knob_button_view_arc_12_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_12_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_arc_12_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_12_main_knob_default.set_bg_opa(0)
style_knob_button_view_arc_12_main_knob_default.set_pad_all(5)

# add style for knob_button_view_arc_12
knob_button_view_arc_12.add_style(style_knob_button_view_arc_12_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_arc_13 = lv.arc(knob_button_view)
knob_button_view_arc_13.set_pos(219,80)
knob_button_view_arc_13.set_size(82,82)
knob_button_view_arc_13.set_bg_angles(180, 2)
knob_button_view_arc_13.set_angles(269, 270)
knob_button_view_arc_13.set_rotation(0)
knob_button_view_arc_13.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_13.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_13.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_button_view_arc_13.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_button_view_arc_13_main_main_default
style_knob_button_view_arc_13_main_main_default = lv.style_t()
style_knob_button_view_arc_13_main_main_default.init()
style_knob_button_view_arc_13_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_13_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_button_view_arc_13_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_13_main_main_default.set_bg_opa(0)
style_knob_button_view_arc_13_main_main_default.set_border_width(0)
style_knob_button_view_arc_13_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_13_main_main_default.set_arc_width(7)

# add style for knob_button_view_arc_13
knob_button_view_arc_13.add_style(style_knob_button_view_arc_13_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_13_main_indicator_default
style_knob_button_view_arc_13_main_indicator_default = lv.style_t()
style_knob_button_view_arc_13_main_indicator_default.init()
style_knob_button_view_arc_13_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_button_view_arc_13_main_indicator_default.set_arc_width(0)

# add style for knob_button_view_arc_13
knob_button_view_arc_13.add_style(style_knob_button_view_arc_13_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_button_view_arc_13_main_knob_default
style_knob_button_view_arc_13_main_knob_default = lv.style_t()
style_knob_button_view_arc_13_main_knob_default.init()
style_knob_button_view_arc_13_main_knob_default.set_bg_color(lv.color_make(0xd0,0xa0,0x5d))
style_knob_button_view_arc_13_main_knob_default.set_bg_grad_color(lv.color_make(0xd0,0xa0,0x5d))
style_knob_button_view_arc_13_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_arc_13_main_knob_default.set_bg_opa(255)
style_knob_button_view_arc_13_main_knob_default.set_pad_all(0)

# add style for knob_button_view_arc_13
knob_button_view_arc_13.add_style(style_knob_button_view_arc_13_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_button_view_btn_1 = lv.btn(knob_button_view)
knob_button_view_btn_1.set_pos(20,200)
knob_button_view_btn_1.set_size(80,30)
knob_button_view_btn_1_label = lv.label(knob_button_view_btn_1)
knob_button_view_btn_1_label.set_text("PARAM")
knob_button_view_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_1_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_1_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_1_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_1_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_1_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_1_main_main_default
style_knob_button_view_btn_1_main_main_default = lv.style_t()
style_knob_button_view_btn_1_main_main_default.init()
style_knob_button_view_btn_1_main_main_default.set_radius(15)
style_knob_button_view_btn_1_main_main_default.set_bg_color(lv.color_make(0x4b,0xaf,0xfa))
style_knob_button_view_btn_1_main_main_default.set_bg_grad_color(lv.color_make(0x4b,0xaf,0xfa))
style_knob_button_view_btn_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_1_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_1_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_1_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_1_main_main_default.set_border_width(1)
style_knob_button_view_btn_1_main_main_default.set_border_opa(255)

# add style for knob_button_view_btn_1
knob_button_view_btn_1.add_style(style_knob_button_view_btn_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_btn_2 = lv.btn(knob_button_view)
knob_button_view_btn_2.set_pos(120,200)
knob_button_view_btn_2.set_size(80,30)
knob_button_view_btn_2_label = lv.label(knob_button_view_btn_2)
knob_button_view_btn_2_label.set_text("PARAM")
knob_button_view_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_2_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_2_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_2_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_2_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_2_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_2_main_main_default
style_knob_button_view_btn_2_main_main_default = lv.style_t()
style_knob_button_view_btn_2_main_main_default.init()
style_knob_button_view_btn_2_main_main_default.set_radius(15)
style_knob_button_view_btn_2_main_main_default.set_bg_color(lv.color_make(0x87,0xd7,0xc8))
style_knob_button_view_btn_2_main_main_default.set_bg_grad_color(lv.color_make(0x87,0xd7,0xc8))
style_knob_button_view_btn_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_2_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_2_main_main_default.set_shadow_color(lv.color_make(0x73,0xb5,0xaa))
style_knob_button_view_btn_2_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_2_main_main_default.set_border_width(2)
style_knob_button_view_btn_2_main_main_default.set_border_opa(0)

# add style for knob_button_view_btn_2
knob_button_view_btn_2.add_style(style_knob_button_view_btn_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_btn_3 = lv.btn(knob_button_view)
knob_button_view_btn_3.set_pos(20,160)
knob_button_view_btn_3.set_size(80,30)
knob_button_view_btn_3_label = lv.label(knob_button_view_btn_3)
knob_button_view_btn_3_label.set_text("PARAM")
knob_button_view_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_3_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_3_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_3_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_3_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_3_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_3_main_main_default
style_knob_button_view_btn_3_main_main_default = lv.style_t()
style_knob_button_view_btn_3_main_main_default.init()
style_knob_button_view_btn_3_main_main_default.set_radius(15)
style_knob_button_view_btn_3_main_main_default.set_bg_color(lv.color_make(0xf9,0x53,0xab))
style_knob_button_view_btn_3_main_main_default.set_bg_grad_color(lv.color_make(0xf9,0x53,0xab))
style_knob_button_view_btn_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_3_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_3_main_main_default.set_shadow_color(lv.color_make(0xc1,0x3e,0x84))
style_knob_button_view_btn_3_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_3_main_main_default.set_border_color(lv.color_make(0xc1,0x3e,0x84))
style_knob_button_view_btn_3_main_main_default.set_border_width(2)
style_knob_button_view_btn_3_main_main_default.set_border_opa(255)

# add style for knob_button_view_btn_3
knob_button_view_btn_3.add_style(style_knob_button_view_btn_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_btn_4 = lv.btn(knob_button_view)
knob_button_view_btn_4.set_pos(120,160)
knob_button_view_btn_4.set_size(80,30)
knob_button_view_btn_4_label = lv.label(knob_button_view_btn_4)
knob_button_view_btn_4_label.set_text("PARAM")
knob_button_view_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_4_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_4_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_4_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_4_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_4_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_4_main_main_default
style_knob_button_view_btn_4_main_main_default = lv.style_t()
style_knob_button_view_btn_4_main_main_default.init()
style_knob_button_view_btn_4_main_main_default.set_radius(15)
style_knob_button_view_btn_4_main_main_default.set_bg_color(lv.color_make(0xfe,0xe4,0x63))
style_knob_button_view_btn_4_main_main_default.set_bg_grad_color(lv.color_make(0xfe,0xe4,0x63))
style_knob_button_view_btn_4_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_4_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_4_main_main_default.set_shadow_color(lv.color_make(0xd3,0xc0,0x5f))
style_knob_button_view_btn_4_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_4_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_4_main_main_default.set_border_width(2)
style_knob_button_view_btn_4_main_main_default.set_border_opa(0)

# add style for knob_button_view_btn_4
knob_button_view_btn_4.add_style(style_knob_button_view_btn_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_btn_5 = lv.btn(knob_button_view)
knob_button_view_btn_5.set_pos(220,200)
knob_button_view_btn_5.set_size(80,30)
knob_button_view_btn_5_label = lv.label(knob_button_view_btn_5)
knob_button_view_btn_5_label.set_text("PARAM")
knob_button_view_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_5_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_5_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_5_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_5_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_5_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_5_main_main_default
style_knob_button_view_btn_5_main_main_default = lv.style_t()
style_knob_button_view_btn_5_main_main_default.init()
style_knob_button_view_btn_5_main_main_default.set_radius(15)
style_knob_button_view_btn_5_main_main_default.set_bg_color(lv.color_make(0xff,0xc3,0x70))
style_knob_button_view_btn_5_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xc3,0x70))
style_knob_button_view_btn_5_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_5_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_5_main_main_default.set_shadow_color(lv.color_make(0xd0,0xa0,0x5d))
style_knob_button_view_btn_5_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_5_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_5_main_main_default.set_border_width(2)
style_knob_button_view_btn_5_main_main_default.set_border_opa(0)

# add style for knob_button_view_btn_5
knob_button_view_btn_5.add_style(style_knob_button_view_btn_5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_button_view_btn_6 = lv.btn(knob_button_view)
knob_button_view_btn_6.set_pos(220,160)
knob_button_view_btn_6.set_size(80,30)
knob_button_view_btn_6_label = lv.label(knob_button_view_btn_6)
knob_button_view_btn_6_label.set_text("PARAM")
knob_button_view_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
knob_button_view_btn_6_label.align(lv.ALIGN.CENTER,0,0)
knob_button_view_btn_6_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    knob_button_view_btn_6_label.set_style_text_font(lv.font_MuseoSansCondensed_700_14, lv.STATE.DEFAULT)
except AttributeError:
    try:
        knob_button_view_btn_6_label.set_style_text_font(lv.font_montserrat_14, lv.STATE.DEFAULT)
    except AttributeError:
        knob_button_view_btn_6_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_knob_button_view_btn_6_main_main_default
style_knob_button_view_btn_6_main_main_default = lv.style_t()
style_knob_button_view_btn_6_main_main_default.init()
style_knob_button_view_btn_6_main_main_default.set_radius(15)
style_knob_button_view_btn_6_main_main_default.set_bg_color(lv.color_make(0xaa,0xa7,0xd7))
style_knob_button_view_btn_6_main_main_default.set_bg_grad_color(lv.color_make(0xaa,0xa7,0xd7))
style_knob_button_view_btn_6_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_button_view_btn_6_main_main_default.set_bg_opa(255)
style_knob_button_view_btn_6_main_main_default.set_shadow_color(lv.color_make(0x8a,0x88,0xaf))
style_knob_button_view_btn_6_main_main_default.set_shadow_opa(255)
style_knob_button_view_btn_6_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_knob_button_view_btn_6_main_main_default.set_border_width(2)
style_knob_button_view_btn_6_main_main_default.set_border_opa(0)

# add style for knob_button_view_btn_6
knob_button_view_btn_6.add_style(style_knob_button_view_btn_6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view = lv.obj()
# create style style_knob_view_main_main_default
style_knob_view_main_main_default = lv.style_t()
style_knob_view_main_main_default.init()
style_knob_view_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_knob_view_main_main_default.set_bg_opa(255)

# add style for knob_view
knob_view.add_style(style_knob_view_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_x_knob = lv.arc(knob_view)
knob_view_x_knob.set_pos(19,18)
knob_view_x_knob.set_size(45,45)
knob_view_x_knob.set_bg_angles(120, 60)
knob_view_x_knob.set_angles(120, 220)
knob_view_x_knob.set_rotation(0)
knob_view_x_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_x_knob_main_main_default
style_knob_view_x_knob_main_main_default = lv.style_t()
style_knob_view_x_knob_main_main_default.init()
style_knob_view_x_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_x_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_x_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_x_knob_main_main_default.set_bg_opa(0)
style_knob_view_x_knob_main_main_default.set_border_width(0)
style_knob_view_x_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_x_knob_main_main_default.set_arc_width(12)

# add style for knob_view_x_knob
knob_view_x_knob.add_style(style_knob_view_x_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_x_knob_main_indicator_default
style_knob_view_x_knob_main_indicator_default = lv.style_t()
style_knob_view_x_knob_main_indicator_default.init()
style_knob_view_x_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view_x_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_x_knob
knob_view_x_knob.add_style(style_knob_view_x_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_x_knob_main_knob_default
style_knob_view_x_knob_main_knob_default = lv.style_t()
style_knob_view_x_knob_main_knob_default.init()
style_knob_view_x_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_x_knob_main_knob_default.set_bg_opa(0)
style_knob_view_x_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_x_knob
knob_view_x_knob.add_style(style_knob_view_x_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_x_outline = lv.arc(knob_view)
knob_view_x_outline.set_pos(8,8)
knob_view_x_outline.set_size(65,65)
knob_view_x_outline.set_bg_angles(120, 60)
knob_view_x_outline.set_angles(120, 220)
knob_view_x_outline.set_rotation(0)
knob_view_x_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_x_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_x_outline_main_main_default
style_knob_view_x_outline_main_main_default = lv.style_t()
style_knob_view_x_outline_main_main_default.init()
style_knob_view_x_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_x_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_x_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_x_outline_main_main_default.set_bg_opa(0)
style_knob_view_x_outline_main_main_default.set_border_width(0)
style_knob_view_x_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_x_outline_main_main_default.set_arc_width(3)

# add style for knob_view_x_outline
knob_view_x_outline.add_style(style_knob_view_x_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_x_outline_main_indicator_default
style_knob_view_x_outline_main_indicator_default = lv.style_t()
style_knob_view_x_outline_main_indicator_default.init()
style_knob_view_x_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_x_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_x_outline
knob_view_x_outline.add_style(style_knob_view_x_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_x_outline_main_knob_default
style_knob_view_x_outline_main_knob_default = lv.style_t()
style_knob_view_x_outline_main_knob_default.init()
style_knob_view_x_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_x_outline_main_knob_default.set_bg_opa(0)
style_knob_view_x_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_x_outline
knob_view_x_outline.add_style(style_knob_view_x_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_x_label = lv.label(knob_view)
knob_view_x_label.set_pos(30,66)
knob_view_x_label.set_size(25,16)
knob_view_x_label.set_text("X")
knob_view_x_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_x_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_x_label_main_main_default
style_knob_view_x_label_main_main_default = lv.style_t()
style_knob_view_x_label_main_main_default.init()
style_knob_view_x_label_main_main_default.set_radius(0)
style_knob_view_x_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_x_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_x_label_main_main_default.set_bg_opa(0)
style_knob_view_x_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_x_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view_x_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view_x_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_x_label_main_main_default.set_text_letter_space(2)
style_knob_view_x_label_main_main_default.set_pad_left(0)
style_knob_view_x_label_main_main_default.set_pad_right(0)
style_knob_view_x_label_main_main_default.set_pad_top(0)
style_knob_view_x_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_x_label
knob_view_x_label.add_style(style_knob_view_x_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_a_knob = lv.arc(knob_view)
knob_view_a_knob.set_pos(88,7)
knob_view_a_knob.set_size(60,60)
knob_view_a_knob.set_bg_angles(120, 60)
knob_view_a_knob.set_angles(120, 220)
knob_view_a_knob.set_rotation(0)
knob_view_a_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_a_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_a_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_a_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_a_knob_main_main_default
style_knob_view_a_knob_main_main_default = lv.style_t()
style_knob_view_a_knob_main_main_default.init()
style_knob_view_a_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_a_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_a_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_a_knob_main_main_default.set_bg_opa(0)
style_knob_view_a_knob_main_main_default.set_border_width(0)
style_knob_view_a_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_a_knob_main_main_default.set_arc_width(16)

# add style for knob_view_a_knob
knob_view_a_knob.add_style(style_knob_view_a_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_a_knob_main_indicator_default
style_knob_view_a_knob_main_indicator_default = lv.style_t()
style_knob_view_a_knob_main_indicator_default.init()
style_knob_view_a_knob_main_indicator_default.set_arc_color(lv.color_make(0xe1,0x49,0xe4))
style_knob_view_a_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_a_knob
knob_view_a_knob.add_style(style_knob_view_a_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_a_knob_main_knob_default
style_knob_view_a_knob_main_knob_default = lv.style_t()
style_knob_view_a_knob_main_knob_default.init()
style_knob_view_a_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_a_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_a_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_a_knob_main_knob_default.set_bg_opa(0)
style_knob_view_a_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_a_knob
knob_view_a_knob.add_style(style_knob_view_a_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_a_label = lv.label(knob_view)
knob_view_a_label.set_pos(87,69)
knob_view_a_label.set_size(61,13)
knob_view_a_label.set_text("PARAM")
knob_view_a_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_a_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_a_label_main_main_default
style_knob_view_a_label_main_main_default = lv.style_t()
style_knob_view_a_label_main_main_default.init()
style_knob_view_a_label_main_main_default.set_radius(0)
style_knob_view_a_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_a_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_a_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_a_label_main_main_default.set_bg_opa(0)
style_knob_view_a_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_a_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_a_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_a_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_a_label_main_main_default.set_text_letter_space(2)
style_knob_view_a_label_main_main_default.set_pad_left(0)
style_knob_view_a_label_main_main_default.set_pad_right(0)
style_knob_view_a_label_main_main_default.set_pad_top(0)
style_knob_view_a_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_a_label
knob_view_a_label.add_style(style_knob_view_a_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_b_knob = lv.arc(knob_view)
knob_view_b_knob.set_pos(172,7)
knob_view_b_knob.set_size(60,60)
knob_view_b_knob.set_bg_angles(120, 60)
knob_view_b_knob.set_angles(120, 220)
knob_view_b_knob.set_rotation(0)
knob_view_b_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_b_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_b_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_b_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_b_knob_main_main_default
style_knob_view_b_knob_main_main_default = lv.style_t()
style_knob_view_b_knob_main_main_default.init()
style_knob_view_b_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_b_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_b_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_b_knob_main_main_default.set_bg_opa(0)
style_knob_view_b_knob_main_main_default.set_border_width(0)
style_knob_view_b_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_b_knob_main_main_default.set_arc_width(16)

# add style for knob_view_b_knob
knob_view_b_knob.add_style(style_knob_view_b_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_b_knob_main_indicator_default
style_knob_view_b_knob_main_indicator_default = lv.style_t()
style_knob_view_b_knob_main_indicator_default.init()
style_knob_view_b_knob_main_indicator_default.set_arc_color(lv.color_make(0xfe,0xe4,0x63))
style_knob_view_b_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_b_knob
knob_view_b_knob.add_style(style_knob_view_b_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_b_knob_main_knob_default
style_knob_view_b_knob_main_knob_default = lv.style_t()
style_knob_view_b_knob_main_knob_default.init()
style_knob_view_b_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_b_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_b_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_b_knob_main_knob_default.set_bg_opa(0)
style_knob_view_b_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_b_knob
knob_view_b_knob.add_style(style_knob_view_b_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_b_label = lv.label(knob_view)
knob_view_b_label.set_pos(174,69)
knob_view_b_label.set_size(61,13)
knob_view_b_label.set_text("PARAM")
knob_view_b_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_b_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_b_label_main_main_default
style_knob_view_b_label_main_main_default = lv.style_t()
style_knob_view_b_label_main_main_default.init()
style_knob_view_b_label_main_main_default.set_radius(0)
style_knob_view_b_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_b_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_b_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_b_label_main_main_default.set_bg_opa(0)
style_knob_view_b_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_b_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_b_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_b_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_b_label_main_main_default.set_text_letter_space(2)
style_knob_view_b_label_main_main_default.set_pad_left(0)
style_knob_view_b_label_main_main_default.set_pad_right(0)
style_knob_view_b_label_main_main_default.set_pad_top(0)
style_knob_view_b_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_b_label
knob_view_b_label.add_style(style_knob_view_b_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_q_knob = lv.arc(knob_view)
knob_view_q_knob.set_pos(258,18)
knob_view_q_knob.set_size(45,45)
knob_view_q_knob.set_bg_angles(120, 60)
knob_view_q_knob.set_angles(120, 220)
knob_view_q_knob.set_rotation(0)
knob_view_q_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_q_knob_main_main_default
style_knob_view_q_knob_main_main_default = lv.style_t()
style_knob_view_q_knob_main_main_default.init()
style_knob_view_q_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_q_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_q_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_q_knob_main_main_default.set_bg_opa(0)
style_knob_view_q_knob_main_main_default.set_border_width(0)
style_knob_view_q_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_q_knob_main_main_default.set_arc_width(12)

# add style for knob_view_q_knob
knob_view_q_knob.add_style(style_knob_view_q_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_q_knob_main_indicator_default
style_knob_view_q_knob_main_indicator_default = lv.style_t()
style_knob_view_q_knob_main_indicator_default.init()
style_knob_view_q_knob_main_indicator_default.set_arc_color(lv.color_make(0x3a,0x45,0xdf))
style_knob_view_q_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_q_knob
knob_view_q_knob.add_style(style_knob_view_q_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_q_knob_main_knob_default
style_knob_view_q_knob_main_knob_default = lv.style_t()
style_knob_view_q_knob_main_knob_default.init()
style_knob_view_q_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_q_knob_main_knob_default.set_bg_opa(0)
style_knob_view_q_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_q_knob
knob_view_q_knob.add_style(style_knob_view_q_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_q_outline = lv.arc(knob_view)
knob_view_q_outline.set_pos(247,8)
knob_view_q_outline.set_size(65,65)
knob_view_q_outline.set_bg_angles(120, 60)
knob_view_q_outline.set_angles(120, 220)
knob_view_q_outline.set_rotation(0)
knob_view_q_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_q_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_q_outline_main_main_default
style_knob_view_q_outline_main_main_default = lv.style_t()
style_knob_view_q_outline_main_main_default.init()
style_knob_view_q_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_q_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_q_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_q_outline_main_main_default.set_bg_opa(0)
style_knob_view_q_outline_main_main_default.set_border_width(0)
style_knob_view_q_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_q_outline_main_main_default.set_arc_width(3)

# add style for knob_view_q_outline
knob_view_q_outline.add_style(style_knob_view_q_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_q_outline_main_indicator_default
style_knob_view_q_outline_main_indicator_default = lv.style_t()
style_knob_view_q_outline_main_indicator_default.init()
style_knob_view_q_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_q_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_q_outline
knob_view_q_outline.add_style(style_knob_view_q_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_q_outline_main_knob_default
style_knob_view_q_outline_main_knob_default = lv.style_t()
style_knob_view_q_outline_main_knob_default.init()
style_knob_view_q_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_q_outline_main_knob_default.set_bg_opa(0)
style_knob_view_q_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_q_outline
knob_view_q_outline.add_style(style_knob_view_q_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_q_label = lv.label(knob_view)
knob_view_q_label.set_pos(269,66)
knob_view_q_label.set_size(25,16)
knob_view_q_label.set_text("Q")
knob_view_q_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_q_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_q_label_main_main_default
style_knob_view_q_label_main_main_default = lv.style_t()
style_knob_view_q_label_main_main_default.init()
style_knob_view_q_label_main_main_default.set_radius(0)
style_knob_view_q_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_q_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_q_label_main_main_default.set_bg_opa(0)
style_knob_view_q_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_q_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view_q_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view_q_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_q_label_main_main_default.set_text_letter_space(2)
style_knob_view_q_label_main_main_default.set_pad_left(0)
style_knob_view_q_label_main_main_default.set_pad_right(0)
style_knob_view_q_label_main_main_default.set_pad_top(0)
style_knob_view_q_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_q_label
knob_view_q_label.add_style(style_knob_view_q_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_y_knob = lv.arc(knob_view)
knob_view_y_knob.set_pos(19,98)
knob_view_y_knob.set_size(45,45)
knob_view_y_knob.set_bg_angles(120, 60)
knob_view_y_knob.set_angles(120, 220)
knob_view_y_knob.set_rotation(0)
knob_view_y_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_y_knob_main_main_default
style_knob_view_y_knob_main_main_default = lv.style_t()
style_knob_view_y_knob_main_main_default.init()
style_knob_view_y_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_y_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_y_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_y_knob_main_main_default.set_bg_opa(0)
style_knob_view_y_knob_main_main_default.set_border_width(0)
style_knob_view_y_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_y_knob_main_main_default.set_arc_width(12)

# add style for knob_view_y_knob
knob_view_y_knob.add_style(style_knob_view_y_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_y_knob_main_indicator_default
style_knob_view_y_knob_main_indicator_default = lv.style_t()
style_knob_view_y_knob_main_indicator_default.init()
style_knob_view_y_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view_y_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_y_knob
knob_view_y_knob.add_style(style_knob_view_y_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_y_knob_main_knob_default
style_knob_view_y_knob_main_knob_default = lv.style_t()
style_knob_view_y_knob_main_knob_default.init()
style_knob_view_y_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_y_knob_main_knob_default.set_bg_opa(0)
style_knob_view_y_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_y_knob
knob_view_y_knob.add_style(style_knob_view_y_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_y_outline = lv.arc(knob_view)
knob_view_y_outline.set_pos(8,88)
knob_view_y_outline.set_size(65,65)
knob_view_y_outline.set_bg_angles(120, 60)
knob_view_y_outline.set_angles(120, 220)
knob_view_y_outline.set_rotation(0)
knob_view_y_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_y_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_y_outline_main_main_default
style_knob_view_y_outline_main_main_default = lv.style_t()
style_knob_view_y_outline_main_main_default.init()
style_knob_view_y_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_y_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_y_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_y_outline_main_main_default.set_bg_opa(0)
style_knob_view_y_outline_main_main_default.set_border_width(0)
style_knob_view_y_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_y_outline_main_main_default.set_arc_width(3)

# add style for knob_view_y_outline
knob_view_y_outline.add_style(style_knob_view_y_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_y_outline_main_indicator_default
style_knob_view_y_outline_main_indicator_default = lv.style_t()
style_knob_view_y_outline_main_indicator_default.init()
style_knob_view_y_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_y_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_y_outline
knob_view_y_outline.add_style(style_knob_view_y_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_y_outline_main_knob_default
style_knob_view_y_outline_main_knob_default = lv.style_t()
style_knob_view_y_outline_main_knob_default.init()
style_knob_view_y_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_y_outline_main_knob_default.set_bg_opa(0)
style_knob_view_y_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_y_outline
knob_view_y_outline.add_style(style_knob_view_y_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_y_label = lv.label(knob_view)
knob_view_y_label.set_pos(29,145)
knob_view_y_label.set_size(25,16)
knob_view_y_label.set_text("Y")
knob_view_y_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_y_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_y_label_main_main_default
style_knob_view_y_label_main_main_default = lv.style_t()
style_knob_view_y_label_main_main_default.init()
style_knob_view_y_label_main_main_default.set_radius(0)
style_knob_view_y_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_y_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_y_label_main_main_default.set_bg_opa(0)
style_knob_view_y_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_y_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view_y_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view_y_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_y_label_main_main_default.set_text_letter_space(2)
style_knob_view_y_label_main_main_default.set_pad_left(0)
style_knob_view_y_label_main_main_default.set_pad_right(0)
style_knob_view_y_label_main_main_default.set_pad_top(0)
style_knob_view_y_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_y_label
knob_view_y_label.add_style(style_knob_view_y_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_c_knob = lv.arc(knob_view)
knob_view_c_knob.set_pos(88,86)
knob_view_c_knob.set_size(60,60)
knob_view_c_knob.set_bg_angles(120, 60)
knob_view_c_knob.set_angles(120, 220)
knob_view_c_knob.set_rotation(0)
knob_view_c_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_c_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_c_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_c_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_c_knob_main_main_default
style_knob_view_c_knob_main_main_default = lv.style_t()
style_knob_view_c_knob_main_main_default.init()
style_knob_view_c_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_c_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_c_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_c_knob_main_main_default.set_bg_opa(0)
style_knob_view_c_knob_main_main_default.set_border_width(0)
style_knob_view_c_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_c_knob_main_main_default.set_arc_width(16)

# add style for knob_view_c_knob
knob_view_c_knob.add_style(style_knob_view_c_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_c_knob_main_indicator_default
style_knob_view_c_knob_main_indicator_default = lv.style_t()
style_knob_view_c_knob_main_indicator_default.init()
style_knob_view_c_knob_main_indicator_default.set_arc_color(lv.color_make(0x4b,0xaf,0xfa))
style_knob_view_c_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_c_knob
knob_view_c_knob.add_style(style_knob_view_c_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_c_knob_main_knob_default
style_knob_view_c_knob_main_knob_default = lv.style_t()
style_knob_view_c_knob_main_knob_default.init()
style_knob_view_c_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_c_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_c_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_c_knob_main_knob_default.set_bg_opa(0)
style_knob_view_c_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_c_knob
knob_view_c_knob.add_style(style_knob_view_c_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_c_label = lv.label(knob_view)
knob_view_c_label.set_pos(87,148)
knob_view_c_label.set_size(61,13)
knob_view_c_label.set_text("PARAM")
knob_view_c_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_c_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_c_label_main_main_default
style_knob_view_c_label_main_main_default = lv.style_t()
style_knob_view_c_label_main_main_default.init()
style_knob_view_c_label_main_main_default.set_radius(0)
style_knob_view_c_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_c_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_c_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_c_label_main_main_default.set_bg_opa(0)
style_knob_view_c_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_c_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_c_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_c_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_c_label_main_main_default.set_text_letter_space(2)
style_knob_view_c_label_main_main_default.set_pad_left(0)
style_knob_view_c_label_main_main_default.set_pad_right(0)
style_knob_view_c_label_main_main_default.set_pad_top(0)
style_knob_view_c_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_c_label
knob_view_c_label.add_style(style_knob_view_c_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_d_knob = lv.arc(knob_view)
knob_view_d_knob.set_pos(172,86)
knob_view_d_knob.set_size(60,60)
knob_view_d_knob.set_bg_angles(120, 60)
knob_view_d_knob.set_angles(120, 220)
knob_view_d_knob.set_rotation(0)
knob_view_d_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_d_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_d_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_d_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_d_knob_main_main_default
style_knob_view_d_knob_main_main_default = lv.style_t()
style_knob_view_d_knob_main_main_default.init()
style_knob_view_d_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_d_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_d_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_d_knob_main_main_default.set_bg_opa(0)
style_knob_view_d_knob_main_main_default.set_border_width(0)
style_knob_view_d_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_d_knob_main_main_default.set_arc_width(16)

# add style for knob_view_d_knob
knob_view_d_knob.add_style(style_knob_view_d_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_d_knob_main_indicator_default
style_knob_view_d_knob_main_indicator_default = lv.style_t()
style_knob_view_d_knob_main_indicator_default.init()
style_knob_view_d_knob_main_indicator_default.set_arc_color(lv.color_make(0x79,0x72,0xdf))
style_knob_view_d_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_d_knob
knob_view_d_knob.add_style(style_knob_view_d_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_d_knob_main_knob_default
style_knob_view_d_knob_main_knob_default = lv.style_t()
style_knob_view_d_knob_main_knob_default.init()
style_knob_view_d_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_d_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_d_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_d_knob_main_knob_default.set_bg_opa(0)
style_knob_view_d_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_d_knob
knob_view_d_knob.add_style(style_knob_view_d_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_d_label = lv.label(knob_view)
knob_view_d_label.set_pos(174,148)
knob_view_d_label.set_size(61,13)
knob_view_d_label.set_text("PARAM")
knob_view_d_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_d_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_d_label_main_main_default
style_knob_view_d_label_main_main_default = lv.style_t()
style_knob_view_d_label_main_main_default.init()
style_knob_view_d_label_main_main_default.set_radius(0)
style_knob_view_d_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_d_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_d_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_d_label_main_main_default.set_bg_opa(0)
style_knob_view_d_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_d_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_d_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_d_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_d_label_main_main_default.set_text_letter_space(2)
style_knob_view_d_label_main_main_default.set_pad_left(0)
style_knob_view_d_label_main_main_default.set_pad_right(0)
style_knob_view_d_label_main_main_default.set_pad_top(0)
style_knob_view_d_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_d_label
knob_view_d_label.add_style(style_knob_view_d_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_l_knob = lv.arc(knob_view)
knob_view_l_knob.set_pos(258,98)
knob_view_l_knob.set_size(45,45)
knob_view_l_knob.set_bg_angles(120, 60)
knob_view_l_knob.set_angles(120, 220)
knob_view_l_knob.set_rotation(0)
knob_view_l_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_l_knob_main_main_default
style_knob_view_l_knob_main_main_default = lv.style_t()
style_knob_view_l_knob_main_main_default.init()
style_knob_view_l_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_l_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_l_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_l_knob_main_main_default.set_bg_opa(0)
style_knob_view_l_knob_main_main_default.set_border_width(0)
style_knob_view_l_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_l_knob_main_main_default.set_arc_width(12)

# add style for knob_view_l_knob
knob_view_l_knob.add_style(style_knob_view_l_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_l_knob_main_indicator_default
style_knob_view_l_knob_main_indicator_default = lv.style_t()
style_knob_view_l_knob_main_indicator_default.init()
style_knob_view_l_knob_main_indicator_default.set_arc_color(lv.color_make(0xe6,0xc4,0xf8))
style_knob_view_l_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_l_knob
knob_view_l_knob.add_style(style_knob_view_l_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_l_knob_main_knob_default
style_knob_view_l_knob_main_knob_default = lv.style_t()
style_knob_view_l_knob_main_knob_default.init()
style_knob_view_l_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_l_knob_main_knob_default.set_bg_opa(0)
style_knob_view_l_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_l_knob
knob_view_l_knob.add_style(style_knob_view_l_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_l_outline = lv.arc(knob_view)
knob_view_l_outline.set_pos(247,88)
knob_view_l_outline.set_size(65,65)
knob_view_l_outline.set_bg_angles(120, 60)
knob_view_l_outline.set_angles(120, 220)
knob_view_l_outline.set_rotation(0)
knob_view_l_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_l_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_l_outline_main_main_default
style_knob_view_l_outline_main_main_default = lv.style_t()
style_knob_view_l_outline_main_main_default.init()
style_knob_view_l_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_l_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_l_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_l_outline_main_main_default.set_bg_opa(0)
style_knob_view_l_outline_main_main_default.set_border_width(0)
style_knob_view_l_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_l_outline_main_main_default.set_arc_width(3)

# add style for knob_view_l_outline
knob_view_l_outline.add_style(style_knob_view_l_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_l_outline_main_indicator_default
style_knob_view_l_outline_main_indicator_default = lv.style_t()
style_knob_view_l_outline_main_indicator_default.init()
style_knob_view_l_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_l_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_l_outline
knob_view_l_outline.add_style(style_knob_view_l_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_l_outline_main_knob_default
style_knob_view_l_outline_main_knob_default = lv.style_t()
style_knob_view_l_outline_main_knob_default.init()
style_knob_view_l_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_l_outline_main_knob_default.set_bg_opa(0)
style_knob_view_l_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_l_outline
knob_view_l_outline.add_style(style_knob_view_l_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_l_label = lv.label(knob_view)
knob_view_l_label.set_pos(269,145)
knob_view_l_label.set_size(25,16)
knob_view_l_label.set_text("L")
knob_view_l_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_l_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_l_label_main_main_default
style_knob_view_l_label_main_main_default = lv.style_t()
style_knob_view_l_label_main_main_default.init()
style_knob_view_l_label_main_main_default.set_radius(0)
style_knob_view_l_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_l_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_l_label_main_main_default.set_bg_opa(0)
style_knob_view_l_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_l_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view_l_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view_l_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_l_label_main_main_default.set_text_letter_space(2)
style_knob_view_l_label_main_main_default.set_pad_left(0)
style_knob_view_l_label_main_main_default.set_pad_right(0)
style_knob_view_l_label_main_main_default.set_pad_top(0)
style_knob_view_l_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_l_label
knob_view_l_label.add_style(style_knob_view_l_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_z_knob = lv.arc(knob_view)
knob_view_z_knob.set_pos(19,173)
knob_view_z_knob.set_size(45,45)
knob_view_z_knob.set_bg_angles(120, 60)
knob_view_z_knob.set_angles(120, 220)
knob_view_z_knob.set_rotation(0)
knob_view_z_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_z_knob_main_main_default
style_knob_view_z_knob_main_main_default = lv.style_t()
style_knob_view_z_knob_main_main_default.init()
style_knob_view_z_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_z_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_z_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_z_knob_main_main_default.set_bg_opa(0)
style_knob_view_z_knob_main_main_default.set_border_width(0)
style_knob_view_z_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_z_knob_main_main_default.set_arc_width(12)

# add style for knob_view_z_knob
knob_view_z_knob.add_style(style_knob_view_z_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_z_knob_main_indicator_default
style_knob_view_z_knob_main_indicator_default = lv.style_t()
style_knob_view_z_knob_main_indicator_default.init()
style_knob_view_z_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view_z_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_z_knob
knob_view_z_knob.add_style(style_knob_view_z_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_z_knob_main_knob_default
style_knob_view_z_knob_main_knob_default = lv.style_t()
style_knob_view_z_knob_main_knob_default.init()
style_knob_view_z_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_z_knob_main_knob_default.set_bg_opa(0)
style_knob_view_z_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_z_knob
knob_view_z_knob.add_style(style_knob_view_z_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_z_outline = lv.arc(knob_view)
knob_view_z_outline.set_pos(8,163)
knob_view_z_outline.set_size(65,65)
knob_view_z_outline.set_bg_angles(120, 60)
knob_view_z_outline.set_angles(120, 220)
knob_view_z_outline.set_rotation(0)
knob_view_z_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_z_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_z_outline_main_main_default
style_knob_view_z_outline_main_main_default = lv.style_t()
style_knob_view_z_outline_main_main_default.init()
style_knob_view_z_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_z_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_z_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_z_outline_main_main_default.set_bg_opa(0)
style_knob_view_z_outline_main_main_default.set_border_width(0)
style_knob_view_z_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_z_outline_main_main_default.set_arc_width(3)

# add style for knob_view_z_outline
knob_view_z_outline.add_style(style_knob_view_z_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_z_outline_main_indicator_default
style_knob_view_z_outline_main_indicator_default = lv.style_t()
style_knob_view_z_outline_main_indicator_default.init()
style_knob_view_z_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_z_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_z_outline
knob_view_z_outline.add_style(style_knob_view_z_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_z_outline_main_knob_default
style_knob_view_z_outline_main_knob_default = lv.style_t()
style_knob_view_z_outline_main_knob_default.init()
style_knob_view_z_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_z_outline_main_knob_default.set_bg_opa(0)
style_knob_view_z_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_z_outline
knob_view_z_outline.add_style(style_knob_view_z_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_z_label = lv.label(knob_view)
knob_view_z_label.set_pos(30,221)
knob_view_z_label.set_size(25,16)
knob_view_z_label.set_text("Z")
knob_view_z_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_z_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_z_label_main_main_default
style_knob_view_z_label_main_main_default = lv.style_t()
style_knob_view_z_label_main_main_default.init()
style_knob_view_z_label_main_main_default.set_radius(0)
style_knob_view_z_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_z_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_z_label_main_main_default.set_bg_opa(0)
style_knob_view_z_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_z_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_14)
except AttributeError:
    try:
        style_knob_view_z_label_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_knob_view_z_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_z_label_main_main_default.set_text_letter_space(2)
style_knob_view_z_label_main_main_default.set_pad_left(0)
style_knob_view_z_label_main_main_default.set_pad_right(0)
style_knob_view_z_label_main_main_default.set_pad_top(0)
style_knob_view_z_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_z_label
knob_view_z_label.add_style(style_knob_view_z_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_e_knob = lv.arc(knob_view)
knob_view_e_knob.set_pos(88,164)
knob_view_e_knob.set_size(60,60)
knob_view_e_knob.set_bg_angles(120, 60)
knob_view_e_knob.set_angles(120, 220)
knob_view_e_knob.set_rotation(0)
knob_view_e_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_e_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_e_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_e_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_e_knob_main_main_default
style_knob_view_e_knob_main_main_default = lv.style_t()
style_knob_view_e_knob_main_main_default.init()
style_knob_view_e_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_e_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_e_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_e_knob_main_main_default.set_bg_opa(0)
style_knob_view_e_knob_main_main_default.set_border_width(0)
style_knob_view_e_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_e_knob_main_main_default.set_arc_width(16)

# add style for knob_view_e_knob
knob_view_e_knob.add_style(style_knob_view_e_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_e_knob_main_indicator_default
style_knob_view_e_knob_main_indicator_default = lv.style_t()
style_knob_view_e_knob_main_indicator_default.init()
style_knob_view_e_knob_main_indicator_default.set_arc_color(lv.color_make(0x87,0xd7,0xc8))
style_knob_view_e_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_e_knob
knob_view_e_knob.add_style(style_knob_view_e_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_e_knob_main_knob_default
style_knob_view_e_knob_main_knob_default = lv.style_t()
style_knob_view_e_knob_main_knob_default.init()
style_knob_view_e_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_e_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_e_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_e_knob_main_knob_default.set_bg_opa(0)
style_knob_view_e_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_e_knob
knob_view_e_knob.add_style(style_knob_view_e_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_e_label = lv.label(knob_view)
knob_view_e_label.set_pos(86,226)
knob_view_e_label.set_size(61,13)
knob_view_e_label.set_text("PARAM")
knob_view_e_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_e_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_e_label_main_main_default
style_knob_view_e_label_main_main_default = lv.style_t()
style_knob_view_e_label_main_main_default.init()
style_knob_view_e_label_main_main_default.set_radius(0)
style_knob_view_e_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_e_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_e_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_e_label_main_main_default.set_bg_opa(0)
style_knob_view_e_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_e_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_e_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_e_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_e_label_main_main_default.set_text_letter_space(2)
style_knob_view_e_label_main_main_default.set_pad_left(0)
style_knob_view_e_label_main_main_default.set_pad_right(0)
style_knob_view_e_label_main_main_default.set_pad_top(0)
style_knob_view_e_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_e_label
knob_view_e_label.add_style(style_knob_view_e_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_f_knob = lv.arc(knob_view)
knob_view_f_knob.set_pos(172,164)
knob_view_f_knob.set_size(60,60)
knob_view_f_knob.set_bg_angles(120, 60)
knob_view_f_knob.set_angles(120, 220)
knob_view_f_knob.set_rotation(0)
knob_view_f_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_f_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_f_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_f_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_f_knob_main_main_default
style_knob_view_f_knob_main_main_default = lv.style_t()
style_knob_view_f_knob_main_main_default.init()
style_knob_view_f_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_f_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_f_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_f_knob_main_main_default.set_bg_opa(0)
style_knob_view_f_knob_main_main_default.set_border_width(0)
style_knob_view_f_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_f_knob_main_main_default.set_arc_width(16)

# add style for knob_view_f_knob
knob_view_f_knob.add_style(style_knob_view_f_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_f_knob_main_indicator_default
style_knob_view_f_knob_main_indicator_default = lv.style_t()
style_knob_view_f_knob_main_indicator_default.init()
style_knob_view_f_knob_main_indicator_default.set_arc_color(lv.color_make(0xf4,0xa2,0x2f))
style_knob_view_f_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view_f_knob
knob_view_f_knob.add_style(style_knob_view_f_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_f_knob_main_knob_default
style_knob_view_f_knob_main_knob_default = lv.style_t()
style_knob_view_f_knob_main_knob_default.init()
style_knob_view_f_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_f_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_f_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_f_knob_main_knob_default.set_bg_opa(0)
style_knob_view_f_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_f_knob
knob_view_f_knob.add_style(style_knob_view_f_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_f_label = lv.label(knob_view)
knob_view_f_label.set_pos(174,226)
knob_view_f_label.set_size(61,13)
knob_view_f_label.set_text("PARAM")
knob_view_f_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_f_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_f_label_main_main_default
style_knob_view_f_label_main_main_default = lv.style_t()
style_knob_view_f_label_main_main_default.init()
style_knob_view_f_label_main_main_default.set_radius(0)
style_knob_view_f_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_f_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_f_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_f_label_main_main_default.set_bg_opa(0)
style_knob_view_f_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_f_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view_f_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view_f_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_f_label_main_main_default.set_text_letter_space(2)
style_knob_view_f_label_main_main_default.set_pad_left(0)
style_knob_view_f_label_main_main_default.set_pad_right(0)
style_knob_view_f_label_main_main_default.set_pad_top(0)
style_knob_view_f_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_f_label
knob_view_f_label.add_style(style_knob_view_f_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view_r_knob = lv.arc(knob_view)
knob_view_r_knob.set_pos(258,173)
knob_view_r_knob.set_size(45,45)
knob_view_r_knob.set_bg_angles(120, 60)
knob_view_r_knob.set_angles(120, 220)
knob_view_r_knob.set_rotation(0)
knob_view_r_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_r_knob_main_main_default
style_knob_view_r_knob_main_main_default = lv.style_t()
style_knob_view_r_knob_main_main_default.init()
style_knob_view_r_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_r_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_r_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_r_knob_main_main_default.set_bg_opa(0)
style_knob_view_r_knob_main_main_default.set_border_width(0)
style_knob_view_r_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view_r_knob_main_main_default.set_arc_width(12)

# add style for knob_view_r_knob
knob_view_r_knob.add_style(style_knob_view_r_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_r_knob_main_indicator_default
style_knob_view_r_knob_main_indicator_default = lv.style_t()
style_knob_view_r_knob_main_indicator_default.init()
style_knob_view_r_knob_main_indicator_default.set_arc_color(lv.color_make(0xff,0x57,0x57))
style_knob_view_r_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view_r_knob
knob_view_r_knob.add_style(style_knob_view_r_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_r_knob_main_knob_default
style_knob_view_r_knob_main_knob_default = lv.style_t()
style_knob_view_r_knob_main_knob_default.init()
style_knob_view_r_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_r_knob_main_knob_default.set_bg_opa(0)
style_knob_view_r_knob_main_knob_default.set_pad_all(5)

# add style for knob_view_r_knob
knob_view_r_knob.add_style(style_knob_view_r_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_r_outline = lv.arc(knob_view)
knob_view_r_outline.set_pos(247,163)
knob_view_r_outline.set_size(65,65)
knob_view_r_outline.set_bg_angles(120, 60)
knob_view_r_outline.set_angles(120, 220)
knob_view_r_outline.set_rotation(0)
knob_view_r_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view_r_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view_r_outline_main_main_default
style_knob_view_r_outline_main_main_default = lv.style_t()
style_knob_view_r_outline_main_main_default.init()
style_knob_view_r_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_r_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view_r_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_r_outline_main_main_default.set_bg_opa(0)
style_knob_view_r_outline_main_main_default.set_border_width(0)
style_knob_view_r_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_r_outline_main_main_default.set_arc_width(3)

# add style for knob_view_r_outline
knob_view_r_outline.add_style(style_knob_view_r_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view_r_outline_main_indicator_default
style_knob_view_r_outline_main_indicator_default = lv.style_t()
style_knob_view_r_outline_main_indicator_default.init()
style_knob_view_r_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view_r_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view_r_outline
knob_view_r_outline.add_style(style_knob_view_r_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view_r_outline_main_knob_default
style_knob_view_r_outline_main_knob_default = lv.style_t()
style_knob_view_r_outline_main_knob_default.init()
style_knob_view_r_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_r_outline_main_knob_default.set_bg_opa(0)
style_knob_view_r_outline_main_knob_default.set_pad_all(5)

# add style for knob_view_r_outline
knob_view_r_outline.add_style(style_knob_view_r_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view_r_label = lv.label(knob_view)
knob_view_r_label.set_pos(269,220)
knob_view_r_label.set_size(25,16)
knob_view_r_label.set_text("R")
knob_view_r_label.set_long_mode(lv.label.LONG.WRAP)
knob_view_r_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view_r_label_main_main_default
style_knob_view_r_label_main_main_default = lv.style_t()
style_knob_view_r_label_main_main_default.init()
style_knob_view_r_label_main_main_default.set_radius(0)
style_knob_view_r_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view_r_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view_r_label_main_main_default.set_bg_opa(0)
style_knob_view_r_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view_r_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view_r_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view_r_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view_r_label_main_main_default.set_text_letter_space(2)
style_knob_view_r_label_main_main_default.set_pad_left(0)
style_knob_view_r_label_main_main_default.set_pad_right(0)
style_knob_view_r_label_main_main_default.set_pad_top(0)
style_knob_view_r_label_main_main_default.set_pad_bottom(0)

# add style for knob_view_r_label
knob_view_r_label.add_style(style_knob_view_r_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2 = lv.obj()
# create style style_knob_view2_main_main_default
style_knob_view2_main_main_default = lv.style_t()
style_knob_view2_main_main_default.init()
style_knob_view2_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_knob_view2_main_main_default.set_bg_opa(255)

# add style for knob_view2
knob_view2.add_style(style_knob_view2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_x_knob = lv.arc(knob_view2)
knob_view2_x_knob.set_pos(19,18)
knob_view2_x_knob.set_size(45,45)
knob_view2_x_knob.set_bg_angles(120, 60)
knob_view2_x_knob.set_angles(120, 220)
knob_view2_x_knob.set_rotation(0)
knob_view2_x_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_x_knob_main_main_default
style_knob_view2_x_knob_main_main_default = lv.style_t()
style_knob_view2_x_knob_main_main_default.init()
style_knob_view2_x_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_x_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_x_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_x_knob_main_main_default.set_bg_opa(0)
style_knob_view2_x_knob_main_main_default.set_border_width(0)
style_knob_view2_x_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_x_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_x_knob
knob_view2_x_knob.add_style(style_knob_view2_x_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_x_knob_main_indicator_default
style_knob_view2_x_knob_main_indicator_default = lv.style_t()
style_knob_view2_x_knob_main_indicator_default.init()
style_knob_view2_x_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view2_x_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_x_knob
knob_view2_x_knob.add_style(style_knob_view2_x_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_x_knob_main_knob_default
style_knob_view2_x_knob_main_knob_default = lv.style_t()
style_knob_view2_x_knob_main_knob_default.init()
style_knob_view2_x_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_x_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_x_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_x_knob
knob_view2_x_knob.add_style(style_knob_view2_x_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_x_outline = lv.arc(knob_view2)
knob_view2_x_outline.set_pos(8,8)
knob_view2_x_outline.set_size(65,65)
knob_view2_x_outline.set_bg_angles(120, 60)
knob_view2_x_outline.set_angles(120, 220)
knob_view2_x_outline.set_rotation(0)
knob_view2_x_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_x_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_x_outline_main_main_default
style_knob_view2_x_outline_main_main_default = lv.style_t()
style_knob_view2_x_outline_main_main_default.init()
style_knob_view2_x_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_x_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_x_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_x_outline_main_main_default.set_bg_opa(0)
style_knob_view2_x_outline_main_main_default.set_border_width(0)
style_knob_view2_x_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_x_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_x_outline
knob_view2_x_outline.add_style(style_knob_view2_x_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_x_outline_main_indicator_default
style_knob_view2_x_outline_main_indicator_default = lv.style_t()
style_knob_view2_x_outline_main_indicator_default.init()
style_knob_view2_x_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_x_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_x_outline
knob_view2_x_outline.add_style(style_knob_view2_x_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_x_outline_main_knob_default
style_knob_view2_x_outline_main_knob_default = lv.style_t()
style_knob_view2_x_outline_main_knob_default.init()
style_knob_view2_x_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_x_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_x_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_x_outline
knob_view2_x_outline.add_style(style_knob_view2_x_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_x_label = lv.label(knob_view2)
knob_view2_x_label.set_pos(30,66)
knob_view2_x_label.set_size(25,16)
knob_view2_x_label.set_text("X")
knob_view2_x_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_x_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_x_label_main_main_default
style_knob_view2_x_label_main_main_default = lv.style_t()
style_knob_view2_x_label_main_main_default.init()
style_knob_view2_x_label_main_main_default.set_radius(0)
style_knob_view2_x_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_x_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_x_label_main_main_default.set_bg_opa(0)
style_knob_view2_x_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_x_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view2_x_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view2_x_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_x_label_main_main_default.set_text_letter_space(2)
style_knob_view2_x_label_main_main_default.set_pad_left(0)
style_knob_view2_x_label_main_main_default.set_pad_right(0)
style_knob_view2_x_label_main_main_default.set_pad_top(0)
style_knob_view2_x_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_x_label
knob_view2_x_label.add_style(style_knob_view2_x_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_a_knob = lv.arc(knob_view2)
knob_view2_a_knob.set_pos(88,7)
knob_view2_a_knob.set_size(60,60)
knob_view2_a_knob.set_bg_angles(120, 60)
knob_view2_a_knob.set_angles(120, 220)
knob_view2_a_knob.set_rotation(0)
knob_view2_a_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_a_knob_main_main_default
style_knob_view2_a_knob_main_main_default = lv.style_t()
style_knob_view2_a_knob_main_main_default.init()
style_knob_view2_a_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_a_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_a_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_a_knob_main_main_default.set_bg_opa(0)
style_knob_view2_a_knob_main_main_default.set_border_width(0)
style_knob_view2_a_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_a_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_a_knob
knob_view2_a_knob.add_style(style_knob_view2_a_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_a_knob_main_indicator_default
style_knob_view2_a_knob_main_indicator_default = lv.style_t()
style_knob_view2_a_knob_main_indicator_default.init()
style_knob_view2_a_knob_main_indicator_default.set_arc_color(lv.color_make(0xe1,0x49,0xe4))
style_knob_view2_a_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_a_knob
knob_view2_a_knob.add_style(style_knob_view2_a_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_a_knob_main_knob_default
style_knob_view2_a_knob_main_knob_default = lv.style_t()
style_knob_view2_a_knob_main_knob_default.init()
style_knob_view2_a_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_a_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_a_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_a_knob
knob_view2_a_knob.add_style(style_knob_view2_a_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_a_outline = lv.arc(knob_view2)
knob_view2_a_outline.set_pos(83,2)
knob_view2_a_outline.set_size(70,70)
knob_view2_a_outline.set_bg_angles(120, 60)
knob_view2_a_outline.set_angles(120, 220)
knob_view2_a_outline.set_rotation(0)
knob_view2_a_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_a_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_a_outline_main_main_default
style_knob_view2_a_outline_main_main_default = lv.style_t()
style_knob_view2_a_outline_main_main_default.init()
style_knob_view2_a_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_a_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_a_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_a_outline_main_main_default.set_bg_opa(0)
style_knob_view2_a_outline_main_main_default.set_border_width(0)
style_knob_view2_a_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_a_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_a_outline
knob_view2_a_outline.add_style(style_knob_view2_a_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_a_outline_main_indicator_default
style_knob_view2_a_outline_main_indicator_default = lv.style_t()
style_knob_view2_a_outline_main_indicator_default.init()
style_knob_view2_a_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_a_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_a_outline
knob_view2_a_outline.add_style(style_knob_view2_a_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_a_outline_main_knob_default
style_knob_view2_a_outline_main_knob_default = lv.style_t()
style_knob_view2_a_outline_main_knob_default.init()
style_knob_view2_a_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_a_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_a_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_a_outline
knob_view2_a_outline.add_style(style_knob_view2_a_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_a_label = lv.label(knob_view2)
knob_view2_a_label.set_pos(87,69)
knob_view2_a_label.set_size(61,13)
knob_view2_a_label.set_text("PARAM")
knob_view2_a_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_a_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_a_label_main_main_default
style_knob_view2_a_label_main_main_default = lv.style_t()
style_knob_view2_a_label_main_main_default.init()
style_knob_view2_a_label_main_main_default.set_radius(0)
style_knob_view2_a_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_a_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_a_label_main_main_default.set_bg_opa(0)
style_knob_view2_a_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_a_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_a_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_a_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_a_label_main_main_default.set_text_letter_space(2)
style_knob_view2_a_label_main_main_default.set_pad_left(0)
style_knob_view2_a_label_main_main_default.set_pad_right(0)
style_knob_view2_a_label_main_main_default.set_pad_top(0)
style_knob_view2_a_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_a_label
knob_view2_a_label.add_style(style_knob_view2_a_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_b_knob = lv.arc(knob_view2)
knob_view2_b_knob.set_pos(172,7)
knob_view2_b_knob.set_size(60,60)
knob_view2_b_knob.set_bg_angles(120, 60)
knob_view2_b_knob.set_angles(120, 220)
knob_view2_b_knob.set_rotation(0)
knob_view2_b_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_b_knob_main_main_default
style_knob_view2_b_knob_main_main_default = lv.style_t()
style_knob_view2_b_knob_main_main_default.init()
style_knob_view2_b_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_b_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_b_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_b_knob_main_main_default.set_bg_opa(0)
style_knob_view2_b_knob_main_main_default.set_border_width(0)
style_knob_view2_b_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_b_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_b_knob
knob_view2_b_knob.add_style(style_knob_view2_b_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_b_knob_main_indicator_default
style_knob_view2_b_knob_main_indicator_default = lv.style_t()
style_knob_view2_b_knob_main_indicator_default.init()
style_knob_view2_b_knob_main_indicator_default.set_arc_color(lv.color_make(0xfe,0xe4,0x63))
style_knob_view2_b_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_b_knob
knob_view2_b_knob.add_style(style_knob_view2_b_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_b_knob_main_knob_default
style_knob_view2_b_knob_main_knob_default = lv.style_t()
style_knob_view2_b_knob_main_knob_default.init()
style_knob_view2_b_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_b_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_b_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_b_knob
knob_view2_b_knob.add_style(style_knob_view2_b_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_b_outline = lv.arc(knob_view2)
knob_view2_b_outline.set_pos(167,2)
knob_view2_b_outline.set_size(70,70)
knob_view2_b_outline.set_bg_angles(120, 60)
knob_view2_b_outline.set_angles(120, 220)
knob_view2_b_outline.set_rotation(0)
knob_view2_b_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_b_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_b_outline_main_main_default
style_knob_view2_b_outline_main_main_default = lv.style_t()
style_knob_view2_b_outline_main_main_default.init()
style_knob_view2_b_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_b_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_b_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_b_outline_main_main_default.set_bg_opa(0)
style_knob_view2_b_outline_main_main_default.set_border_width(0)
style_knob_view2_b_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_b_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_b_outline
knob_view2_b_outline.add_style(style_knob_view2_b_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_b_outline_main_indicator_default
style_knob_view2_b_outline_main_indicator_default = lv.style_t()
style_knob_view2_b_outline_main_indicator_default.init()
style_knob_view2_b_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_b_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_b_outline
knob_view2_b_outline.add_style(style_knob_view2_b_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_b_outline_main_knob_default
style_knob_view2_b_outline_main_knob_default = lv.style_t()
style_knob_view2_b_outline_main_knob_default.init()
style_knob_view2_b_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_b_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_b_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_b_outline
knob_view2_b_outline.add_style(style_knob_view2_b_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_b_label = lv.label(knob_view2)
knob_view2_b_label.set_pos(174,69)
knob_view2_b_label.set_size(61,13)
knob_view2_b_label.set_text("PARAM")
knob_view2_b_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_b_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_b_label_main_main_default
style_knob_view2_b_label_main_main_default = lv.style_t()
style_knob_view2_b_label_main_main_default.init()
style_knob_view2_b_label_main_main_default.set_radius(0)
style_knob_view2_b_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_b_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_b_label_main_main_default.set_bg_opa(0)
style_knob_view2_b_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_b_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_b_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_b_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_b_label_main_main_default.set_text_letter_space(2)
style_knob_view2_b_label_main_main_default.set_pad_left(0)
style_knob_view2_b_label_main_main_default.set_pad_right(0)
style_knob_view2_b_label_main_main_default.set_pad_top(0)
style_knob_view2_b_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_b_label
knob_view2_b_label.add_style(style_knob_view2_b_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_q_knob = lv.arc(knob_view2)
knob_view2_q_knob.set_pos(258,18)
knob_view2_q_knob.set_size(45,45)
knob_view2_q_knob.set_bg_angles(120, 60)
knob_view2_q_knob.set_angles(120, 220)
knob_view2_q_knob.set_rotation(0)
knob_view2_q_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_q_knob_main_main_default
style_knob_view2_q_knob_main_main_default = lv.style_t()
style_knob_view2_q_knob_main_main_default.init()
style_knob_view2_q_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_q_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_q_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_q_knob_main_main_default.set_bg_opa(0)
style_knob_view2_q_knob_main_main_default.set_border_width(0)
style_knob_view2_q_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_q_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_q_knob
knob_view2_q_knob.add_style(style_knob_view2_q_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_q_knob_main_indicator_default
style_knob_view2_q_knob_main_indicator_default = lv.style_t()
style_knob_view2_q_knob_main_indicator_default.init()
style_knob_view2_q_knob_main_indicator_default.set_arc_color(lv.color_make(0x3a,0x45,0xdf))
style_knob_view2_q_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_q_knob
knob_view2_q_knob.add_style(style_knob_view2_q_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_q_knob_main_knob_default
style_knob_view2_q_knob_main_knob_default = lv.style_t()
style_knob_view2_q_knob_main_knob_default.init()
style_knob_view2_q_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_q_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_q_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_q_knob
knob_view2_q_knob.add_style(style_knob_view2_q_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_q_outline = lv.arc(knob_view2)
knob_view2_q_outline.set_pos(247,8)
knob_view2_q_outline.set_size(65,65)
knob_view2_q_outline.set_bg_angles(120, 60)
knob_view2_q_outline.set_angles(120, 220)
knob_view2_q_outline.set_rotation(0)
knob_view2_q_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_q_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_q_outline_main_main_default
style_knob_view2_q_outline_main_main_default = lv.style_t()
style_knob_view2_q_outline_main_main_default.init()
style_knob_view2_q_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_q_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_q_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_q_outline_main_main_default.set_bg_opa(0)
style_knob_view2_q_outline_main_main_default.set_border_width(0)
style_knob_view2_q_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_q_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_q_outline
knob_view2_q_outline.add_style(style_knob_view2_q_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_q_outline_main_indicator_default
style_knob_view2_q_outline_main_indicator_default = lv.style_t()
style_knob_view2_q_outline_main_indicator_default.init()
style_knob_view2_q_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_q_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_q_outline
knob_view2_q_outline.add_style(style_knob_view2_q_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_q_outline_main_knob_default
style_knob_view2_q_outline_main_knob_default = lv.style_t()
style_knob_view2_q_outline_main_knob_default.init()
style_knob_view2_q_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_q_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_q_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_q_outline
knob_view2_q_outline.add_style(style_knob_view2_q_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_q_label = lv.label(knob_view2)
knob_view2_q_label.set_pos(269,66)
knob_view2_q_label.set_size(25,16)
knob_view2_q_label.set_text("Q")
knob_view2_q_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_q_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_q_label_main_main_default
style_knob_view2_q_label_main_main_default = lv.style_t()
style_knob_view2_q_label_main_main_default.init()
style_knob_view2_q_label_main_main_default.set_radius(0)
style_knob_view2_q_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_q_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_q_label_main_main_default.set_bg_opa(0)
style_knob_view2_q_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_q_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view2_q_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view2_q_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_q_label_main_main_default.set_text_letter_space(2)
style_knob_view2_q_label_main_main_default.set_pad_left(0)
style_knob_view2_q_label_main_main_default.set_pad_right(0)
style_knob_view2_q_label_main_main_default.set_pad_top(0)
style_knob_view2_q_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_q_label
knob_view2_q_label.add_style(style_knob_view2_q_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_y_knob = lv.arc(knob_view2)
knob_view2_y_knob.set_pos(19,98)
knob_view2_y_knob.set_size(45,45)
knob_view2_y_knob.set_bg_angles(120, 60)
knob_view2_y_knob.set_angles(120, 220)
knob_view2_y_knob.set_rotation(0)
knob_view2_y_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_y_knob_main_main_default
style_knob_view2_y_knob_main_main_default = lv.style_t()
style_knob_view2_y_knob_main_main_default.init()
style_knob_view2_y_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_y_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_y_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_y_knob_main_main_default.set_bg_opa(0)
style_knob_view2_y_knob_main_main_default.set_border_width(0)
style_knob_view2_y_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_y_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_y_knob
knob_view2_y_knob.add_style(style_knob_view2_y_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_y_knob_main_indicator_default
style_knob_view2_y_knob_main_indicator_default = lv.style_t()
style_knob_view2_y_knob_main_indicator_default.init()
style_knob_view2_y_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view2_y_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_y_knob
knob_view2_y_knob.add_style(style_knob_view2_y_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_y_knob_main_knob_default
style_knob_view2_y_knob_main_knob_default = lv.style_t()
style_knob_view2_y_knob_main_knob_default.init()
style_knob_view2_y_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_y_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_y_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_y_knob
knob_view2_y_knob.add_style(style_knob_view2_y_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_y_outline = lv.arc(knob_view2)
knob_view2_y_outline.set_pos(8,88)
knob_view2_y_outline.set_size(65,65)
knob_view2_y_outline.set_bg_angles(120, 60)
knob_view2_y_outline.set_angles(120, 220)
knob_view2_y_outline.set_rotation(0)
knob_view2_y_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_y_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_y_outline_main_main_default
style_knob_view2_y_outline_main_main_default = lv.style_t()
style_knob_view2_y_outline_main_main_default.init()
style_knob_view2_y_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_y_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_y_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_y_outline_main_main_default.set_bg_opa(0)
style_knob_view2_y_outline_main_main_default.set_border_width(0)
style_knob_view2_y_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_y_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_y_outline
knob_view2_y_outline.add_style(style_knob_view2_y_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_y_outline_main_indicator_default
style_knob_view2_y_outline_main_indicator_default = lv.style_t()
style_knob_view2_y_outline_main_indicator_default.init()
style_knob_view2_y_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_y_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_y_outline
knob_view2_y_outline.add_style(style_knob_view2_y_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_y_outline_main_knob_default
style_knob_view2_y_outline_main_knob_default = lv.style_t()
style_knob_view2_y_outline_main_knob_default.init()
style_knob_view2_y_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_y_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_y_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_y_outline
knob_view2_y_outline.add_style(style_knob_view2_y_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_y_label = lv.label(knob_view2)
knob_view2_y_label.set_pos(29,145)
knob_view2_y_label.set_size(25,16)
knob_view2_y_label.set_text("Y")
knob_view2_y_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_y_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_y_label_main_main_default
style_knob_view2_y_label_main_main_default = lv.style_t()
style_knob_view2_y_label_main_main_default.init()
style_knob_view2_y_label_main_main_default.set_radius(0)
style_knob_view2_y_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_y_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_y_label_main_main_default.set_bg_opa(0)
style_knob_view2_y_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_y_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view2_y_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view2_y_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_y_label_main_main_default.set_text_letter_space(2)
style_knob_view2_y_label_main_main_default.set_pad_left(0)
style_knob_view2_y_label_main_main_default.set_pad_right(0)
style_knob_view2_y_label_main_main_default.set_pad_top(0)
style_knob_view2_y_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_y_label
knob_view2_y_label.add_style(style_knob_view2_y_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_c_knob = lv.arc(knob_view2)
knob_view2_c_knob.set_pos(88,86)
knob_view2_c_knob.set_size(60,60)
knob_view2_c_knob.set_bg_angles(120, 60)
knob_view2_c_knob.set_angles(120, 220)
knob_view2_c_knob.set_rotation(0)
knob_view2_c_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_c_knob_main_main_default
style_knob_view2_c_knob_main_main_default = lv.style_t()
style_knob_view2_c_knob_main_main_default.init()
style_knob_view2_c_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_c_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_c_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_c_knob_main_main_default.set_bg_opa(0)
style_knob_view2_c_knob_main_main_default.set_border_width(0)
style_knob_view2_c_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_c_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_c_knob
knob_view2_c_knob.add_style(style_knob_view2_c_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_c_knob_main_indicator_default
style_knob_view2_c_knob_main_indicator_default = lv.style_t()
style_knob_view2_c_knob_main_indicator_default.init()
style_knob_view2_c_knob_main_indicator_default.set_arc_color(lv.color_make(0x4b,0xaf,0xfa))
style_knob_view2_c_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_c_knob
knob_view2_c_knob.add_style(style_knob_view2_c_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_c_knob_main_knob_default
style_knob_view2_c_knob_main_knob_default = lv.style_t()
style_knob_view2_c_knob_main_knob_default.init()
style_knob_view2_c_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_c_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_c_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_c_knob
knob_view2_c_knob.add_style(style_knob_view2_c_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_c_outline = lv.arc(knob_view2)
knob_view2_c_outline.set_pos(83,81)
knob_view2_c_outline.set_size(70,70)
knob_view2_c_outline.set_bg_angles(120, 60)
knob_view2_c_outline.set_angles(120, 220)
knob_view2_c_outline.set_rotation(0)
knob_view2_c_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_c_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_c_outline_main_main_default
style_knob_view2_c_outline_main_main_default = lv.style_t()
style_knob_view2_c_outline_main_main_default.init()
style_knob_view2_c_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_c_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_c_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_c_outline_main_main_default.set_bg_opa(0)
style_knob_view2_c_outline_main_main_default.set_border_width(0)
style_knob_view2_c_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_c_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_c_outline
knob_view2_c_outline.add_style(style_knob_view2_c_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_c_outline_main_indicator_default
style_knob_view2_c_outline_main_indicator_default = lv.style_t()
style_knob_view2_c_outline_main_indicator_default.init()
style_knob_view2_c_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_c_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_c_outline
knob_view2_c_outline.add_style(style_knob_view2_c_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_c_outline_main_knob_default
style_knob_view2_c_outline_main_knob_default = lv.style_t()
style_knob_view2_c_outline_main_knob_default.init()
style_knob_view2_c_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_c_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_c_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_c_outline
knob_view2_c_outline.add_style(style_knob_view2_c_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_c_label = lv.label(knob_view2)
knob_view2_c_label.set_pos(87,148)
knob_view2_c_label.set_size(61,13)
knob_view2_c_label.set_text("PARAM")
knob_view2_c_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_c_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_c_label_main_main_default
style_knob_view2_c_label_main_main_default = lv.style_t()
style_knob_view2_c_label_main_main_default.init()
style_knob_view2_c_label_main_main_default.set_radius(0)
style_knob_view2_c_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_c_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_c_label_main_main_default.set_bg_opa(0)
style_knob_view2_c_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_c_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_c_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_c_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_c_label_main_main_default.set_text_letter_space(2)
style_knob_view2_c_label_main_main_default.set_pad_left(0)
style_knob_view2_c_label_main_main_default.set_pad_right(0)
style_knob_view2_c_label_main_main_default.set_pad_top(0)
style_knob_view2_c_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_c_label
knob_view2_c_label.add_style(style_knob_view2_c_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_d_knob = lv.arc(knob_view2)
knob_view2_d_knob.set_pos(172,86)
knob_view2_d_knob.set_size(60,60)
knob_view2_d_knob.set_bg_angles(120, 60)
knob_view2_d_knob.set_angles(120, 220)
knob_view2_d_knob.set_rotation(0)
knob_view2_d_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_d_knob_main_main_default
style_knob_view2_d_knob_main_main_default = lv.style_t()
style_knob_view2_d_knob_main_main_default.init()
style_knob_view2_d_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_d_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_d_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_d_knob_main_main_default.set_bg_opa(0)
style_knob_view2_d_knob_main_main_default.set_border_width(0)
style_knob_view2_d_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_d_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_d_knob
knob_view2_d_knob.add_style(style_knob_view2_d_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_d_knob_main_indicator_default
style_knob_view2_d_knob_main_indicator_default = lv.style_t()
style_knob_view2_d_knob_main_indicator_default.init()
style_knob_view2_d_knob_main_indicator_default.set_arc_color(lv.color_make(0x79,0x72,0xdf))
style_knob_view2_d_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_d_knob
knob_view2_d_knob.add_style(style_knob_view2_d_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_d_knob_main_knob_default
style_knob_view2_d_knob_main_knob_default = lv.style_t()
style_knob_view2_d_knob_main_knob_default.init()
style_knob_view2_d_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_d_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_d_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_d_knob
knob_view2_d_knob.add_style(style_knob_view2_d_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_d_outline = lv.arc(knob_view2)
knob_view2_d_outline.set_pos(167,81)
knob_view2_d_outline.set_size(70,70)
knob_view2_d_outline.set_bg_angles(120, 60)
knob_view2_d_outline.set_angles(120, 220)
knob_view2_d_outline.set_rotation(0)
knob_view2_d_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_d_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_d_outline_main_main_default
style_knob_view2_d_outline_main_main_default = lv.style_t()
style_knob_view2_d_outline_main_main_default.init()
style_knob_view2_d_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_d_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_d_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_d_outline_main_main_default.set_bg_opa(0)
style_knob_view2_d_outline_main_main_default.set_border_width(0)
style_knob_view2_d_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_d_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_d_outline
knob_view2_d_outline.add_style(style_knob_view2_d_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_d_outline_main_indicator_default
style_knob_view2_d_outline_main_indicator_default = lv.style_t()
style_knob_view2_d_outline_main_indicator_default.init()
style_knob_view2_d_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_d_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_d_outline
knob_view2_d_outline.add_style(style_knob_view2_d_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_d_outline_main_knob_default
style_knob_view2_d_outline_main_knob_default = lv.style_t()
style_knob_view2_d_outline_main_knob_default.init()
style_knob_view2_d_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_d_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_d_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_d_outline
knob_view2_d_outline.add_style(style_knob_view2_d_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_d_label = lv.label(knob_view2)
knob_view2_d_label.set_pos(174,148)
knob_view2_d_label.set_size(61,13)
knob_view2_d_label.set_text("PARAM")
knob_view2_d_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_d_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_d_label_main_main_default
style_knob_view2_d_label_main_main_default = lv.style_t()
style_knob_view2_d_label_main_main_default.init()
style_knob_view2_d_label_main_main_default.set_radius(0)
style_knob_view2_d_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_d_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_d_label_main_main_default.set_bg_opa(0)
style_knob_view2_d_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_d_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_d_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_d_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_d_label_main_main_default.set_text_letter_space(2)
style_knob_view2_d_label_main_main_default.set_pad_left(0)
style_knob_view2_d_label_main_main_default.set_pad_right(0)
style_knob_view2_d_label_main_main_default.set_pad_top(0)
style_knob_view2_d_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_d_label
knob_view2_d_label.add_style(style_knob_view2_d_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_l_knob = lv.arc(knob_view2)
knob_view2_l_knob.set_pos(258,98)
knob_view2_l_knob.set_size(45,45)
knob_view2_l_knob.set_bg_angles(120, 60)
knob_view2_l_knob.set_angles(120, 220)
knob_view2_l_knob.set_rotation(0)
knob_view2_l_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_l_knob_main_main_default
style_knob_view2_l_knob_main_main_default = lv.style_t()
style_knob_view2_l_knob_main_main_default.init()
style_knob_view2_l_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_l_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_l_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_l_knob_main_main_default.set_bg_opa(0)
style_knob_view2_l_knob_main_main_default.set_border_width(0)
style_knob_view2_l_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_l_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_l_knob
knob_view2_l_knob.add_style(style_knob_view2_l_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_l_knob_main_indicator_default
style_knob_view2_l_knob_main_indicator_default = lv.style_t()
style_knob_view2_l_knob_main_indicator_default.init()
style_knob_view2_l_knob_main_indicator_default.set_arc_color(lv.color_make(0xe6,0xc4,0xf8))
style_knob_view2_l_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_l_knob
knob_view2_l_knob.add_style(style_knob_view2_l_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_l_knob_main_knob_default
style_knob_view2_l_knob_main_knob_default = lv.style_t()
style_knob_view2_l_knob_main_knob_default.init()
style_knob_view2_l_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_l_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_l_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_l_knob
knob_view2_l_knob.add_style(style_knob_view2_l_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_l_outline = lv.arc(knob_view2)
knob_view2_l_outline.set_pos(247,88)
knob_view2_l_outline.set_size(65,65)
knob_view2_l_outline.set_bg_angles(120, 60)
knob_view2_l_outline.set_angles(120, 220)
knob_view2_l_outline.set_rotation(0)
knob_view2_l_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_l_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_l_outline_main_main_default
style_knob_view2_l_outline_main_main_default = lv.style_t()
style_knob_view2_l_outline_main_main_default.init()
style_knob_view2_l_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_l_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_l_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_l_outline_main_main_default.set_bg_opa(0)
style_knob_view2_l_outline_main_main_default.set_border_width(0)
style_knob_view2_l_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_l_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_l_outline
knob_view2_l_outline.add_style(style_knob_view2_l_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_l_outline_main_indicator_default
style_knob_view2_l_outline_main_indicator_default = lv.style_t()
style_knob_view2_l_outline_main_indicator_default.init()
style_knob_view2_l_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_l_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_l_outline
knob_view2_l_outline.add_style(style_knob_view2_l_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_l_outline_main_knob_default
style_knob_view2_l_outline_main_knob_default = lv.style_t()
style_knob_view2_l_outline_main_knob_default.init()
style_knob_view2_l_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_l_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_l_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_l_outline
knob_view2_l_outline.add_style(style_knob_view2_l_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_l_label = lv.label(knob_view2)
knob_view2_l_label.set_pos(269,145)
knob_view2_l_label.set_size(25,16)
knob_view2_l_label.set_text("L")
knob_view2_l_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_l_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_l_label_main_main_default
style_knob_view2_l_label_main_main_default = lv.style_t()
style_knob_view2_l_label_main_main_default.init()
style_knob_view2_l_label_main_main_default.set_radius(0)
style_knob_view2_l_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_l_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_l_label_main_main_default.set_bg_opa(0)
style_knob_view2_l_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_l_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view2_l_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view2_l_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_l_label_main_main_default.set_text_letter_space(2)
style_knob_view2_l_label_main_main_default.set_pad_left(0)
style_knob_view2_l_label_main_main_default.set_pad_right(0)
style_knob_view2_l_label_main_main_default.set_pad_top(0)
style_knob_view2_l_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_l_label
knob_view2_l_label.add_style(style_knob_view2_l_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_z_knob = lv.arc(knob_view2)
knob_view2_z_knob.set_pos(19,173)
knob_view2_z_knob.set_size(45,45)
knob_view2_z_knob.set_bg_angles(120, 60)
knob_view2_z_knob.set_angles(120, 220)
knob_view2_z_knob.set_rotation(0)
knob_view2_z_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_z_knob_main_main_default
style_knob_view2_z_knob_main_main_default = lv.style_t()
style_knob_view2_z_knob_main_main_default.init()
style_knob_view2_z_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_z_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_z_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_z_knob_main_main_default.set_bg_opa(0)
style_knob_view2_z_knob_main_main_default.set_border_width(0)
style_knob_view2_z_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_z_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_z_knob
knob_view2_z_knob.add_style(style_knob_view2_z_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_z_knob_main_indicator_default
style_knob_view2_z_knob_main_indicator_default = lv.style_t()
style_knob_view2_z_knob_main_indicator_default.init()
style_knob_view2_z_knob_main_indicator_default.set_arc_color(lv.color_make(0xfa,0x50,0xaa))
style_knob_view2_z_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_z_knob
knob_view2_z_knob.add_style(style_knob_view2_z_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_z_knob_main_knob_default
style_knob_view2_z_knob_main_knob_default = lv.style_t()
style_knob_view2_z_knob_main_knob_default.init()
style_knob_view2_z_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_z_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_z_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_z_knob
knob_view2_z_knob.add_style(style_knob_view2_z_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_z_outline = lv.arc(knob_view2)
knob_view2_z_outline.set_pos(8,163)
knob_view2_z_outline.set_size(65,65)
knob_view2_z_outline.set_bg_angles(120, 60)
knob_view2_z_outline.set_angles(120, 220)
knob_view2_z_outline.set_rotation(0)
knob_view2_z_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_z_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_z_outline_main_main_default
style_knob_view2_z_outline_main_main_default = lv.style_t()
style_knob_view2_z_outline_main_main_default.init()
style_knob_view2_z_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_z_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_z_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_z_outline_main_main_default.set_bg_opa(0)
style_knob_view2_z_outline_main_main_default.set_border_width(0)
style_knob_view2_z_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_z_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_z_outline
knob_view2_z_outline.add_style(style_knob_view2_z_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_z_outline_main_indicator_default
style_knob_view2_z_outline_main_indicator_default = lv.style_t()
style_knob_view2_z_outline_main_indicator_default.init()
style_knob_view2_z_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_z_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_z_outline
knob_view2_z_outline.add_style(style_knob_view2_z_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_z_outline_main_knob_default
style_knob_view2_z_outline_main_knob_default = lv.style_t()
style_knob_view2_z_outline_main_knob_default.init()
style_knob_view2_z_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_z_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_z_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_z_outline
knob_view2_z_outline.add_style(style_knob_view2_z_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_z_label = lv.label(knob_view2)
knob_view2_z_label.set_pos(30,221)
knob_view2_z_label.set_size(25,16)
knob_view2_z_label.set_text("Z")
knob_view2_z_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_z_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_z_label_main_main_default
style_knob_view2_z_label_main_main_default = lv.style_t()
style_knob_view2_z_label_main_main_default.init()
style_knob_view2_z_label_main_main_default.set_radius(0)
style_knob_view2_z_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_z_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_z_label_main_main_default.set_bg_opa(0)
style_knob_view2_z_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_z_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_14)
except AttributeError:
    try:
        style_knob_view2_z_label_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_knob_view2_z_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_z_label_main_main_default.set_text_letter_space(2)
style_knob_view2_z_label_main_main_default.set_pad_left(0)
style_knob_view2_z_label_main_main_default.set_pad_right(0)
style_knob_view2_z_label_main_main_default.set_pad_top(0)
style_knob_view2_z_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_z_label
knob_view2_z_label.add_style(style_knob_view2_z_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_e_knob = lv.arc(knob_view2)
knob_view2_e_knob.set_pos(88,164)
knob_view2_e_knob.set_size(60,60)
knob_view2_e_knob.set_bg_angles(120, 60)
knob_view2_e_knob.set_angles(120, 220)
knob_view2_e_knob.set_rotation(0)
knob_view2_e_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_e_knob_main_main_default
style_knob_view2_e_knob_main_main_default = lv.style_t()
style_knob_view2_e_knob_main_main_default.init()
style_knob_view2_e_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_e_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_e_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_e_knob_main_main_default.set_bg_opa(0)
style_knob_view2_e_knob_main_main_default.set_border_width(0)
style_knob_view2_e_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_e_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_e_knob
knob_view2_e_knob.add_style(style_knob_view2_e_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_e_knob_main_indicator_default
style_knob_view2_e_knob_main_indicator_default = lv.style_t()
style_knob_view2_e_knob_main_indicator_default.init()
style_knob_view2_e_knob_main_indicator_default.set_arc_color(lv.color_make(0x87,0xd7,0xc8))
style_knob_view2_e_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_e_knob
knob_view2_e_knob.add_style(style_knob_view2_e_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_e_knob_main_knob_default
style_knob_view2_e_knob_main_knob_default = lv.style_t()
style_knob_view2_e_knob_main_knob_default.init()
style_knob_view2_e_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_e_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_e_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_e_knob
knob_view2_e_knob.add_style(style_knob_view2_e_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_e_outline = lv.arc(knob_view2)
knob_view2_e_outline.set_pos(83,159)
knob_view2_e_outline.set_size(70,70)
knob_view2_e_outline.set_bg_angles(120, 60)
knob_view2_e_outline.set_angles(120, 220)
knob_view2_e_outline.set_rotation(0)
knob_view2_e_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_e_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_e_outline_main_main_default
style_knob_view2_e_outline_main_main_default = lv.style_t()
style_knob_view2_e_outline_main_main_default.init()
style_knob_view2_e_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_e_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_e_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_e_outline_main_main_default.set_bg_opa(0)
style_knob_view2_e_outline_main_main_default.set_border_width(0)
style_knob_view2_e_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_e_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_e_outline
knob_view2_e_outline.add_style(style_knob_view2_e_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_e_outline_main_indicator_default
style_knob_view2_e_outline_main_indicator_default = lv.style_t()
style_knob_view2_e_outline_main_indicator_default.init()
style_knob_view2_e_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_e_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_e_outline
knob_view2_e_outline.add_style(style_knob_view2_e_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_e_outline_main_knob_default
style_knob_view2_e_outline_main_knob_default = lv.style_t()
style_knob_view2_e_outline_main_knob_default.init()
style_knob_view2_e_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_e_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_e_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_e_outline
knob_view2_e_outline.add_style(style_knob_view2_e_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_e_label = lv.label(knob_view2)
knob_view2_e_label.set_pos(86,226)
knob_view2_e_label.set_size(61,13)
knob_view2_e_label.set_text("PARAM")
knob_view2_e_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_e_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_e_label_main_main_default
style_knob_view2_e_label_main_main_default = lv.style_t()
style_knob_view2_e_label_main_main_default.init()
style_knob_view2_e_label_main_main_default.set_radius(0)
style_knob_view2_e_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_e_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_e_label_main_main_default.set_bg_opa(0)
style_knob_view2_e_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_e_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_e_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_e_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_e_label_main_main_default.set_text_letter_space(2)
style_knob_view2_e_label_main_main_default.set_pad_left(0)
style_knob_view2_e_label_main_main_default.set_pad_right(0)
style_knob_view2_e_label_main_main_default.set_pad_top(0)
style_knob_view2_e_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_e_label
knob_view2_e_label.add_style(style_knob_view2_e_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_f_knob = lv.arc(knob_view2)
knob_view2_f_knob.set_pos(172,164)
knob_view2_f_knob.set_size(60,60)
knob_view2_f_knob.set_bg_angles(120, 60)
knob_view2_f_knob.set_angles(120, 220)
knob_view2_f_knob.set_rotation(0)
knob_view2_f_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_f_knob_main_main_default
style_knob_view2_f_knob_main_main_default = lv.style_t()
style_knob_view2_f_knob_main_main_default.init()
style_knob_view2_f_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_f_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_f_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_f_knob_main_main_default.set_bg_opa(0)
style_knob_view2_f_knob_main_main_default.set_border_width(0)
style_knob_view2_f_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_f_knob_main_main_default.set_arc_width(16)

# add style for knob_view2_f_knob
knob_view2_f_knob.add_style(style_knob_view2_f_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_f_knob_main_indicator_default
style_knob_view2_f_knob_main_indicator_default = lv.style_t()
style_knob_view2_f_knob_main_indicator_default.init()
style_knob_view2_f_knob_main_indicator_default.set_arc_color(lv.color_make(0xf4,0xa2,0x2f))
style_knob_view2_f_knob_main_indicator_default.set_arc_width(16)

# add style for knob_view2_f_knob
knob_view2_f_knob.add_style(style_knob_view2_f_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_f_knob_main_knob_default
style_knob_view2_f_knob_main_knob_default = lv.style_t()
style_knob_view2_f_knob_main_knob_default.init()
style_knob_view2_f_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_f_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_f_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_f_knob
knob_view2_f_knob.add_style(style_knob_view2_f_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_f_outline = lv.arc(knob_view2)
knob_view2_f_outline.set_pos(167,159)
knob_view2_f_outline.set_size(70,70)
knob_view2_f_outline.set_bg_angles(120, 60)
knob_view2_f_outline.set_angles(120, 220)
knob_view2_f_outline.set_rotation(0)
knob_view2_f_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_f_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_f_outline_main_main_default
style_knob_view2_f_outline_main_main_default = lv.style_t()
style_knob_view2_f_outline_main_main_default.init()
style_knob_view2_f_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_f_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_f_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_f_outline_main_main_default.set_bg_opa(0)
style_knob_view2_f_outline_main_main_default.set_border_width(0)
style_knob_view2_f_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_f_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_f_outline
knob_view2_f_outline.add_style(style_knob_view2_f_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_f_outline_main_indicator_default
style_knob_view2_f_outline_main_indicator_default = lv.style_t()
style_knob_view2_f_outline_main_indicator_default.init()
style_knob_view2_f_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_f_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_f_outline
knob_view2_f_outline.add_style(style_knob_view2_f_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_f_outline_main_knob_default
style_knob_view2_f_outline_main_knob_default = lv.style_t()
style_knob_view2_f_outline_main_knob_default.init()
style_knob_view2_f_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_f_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_f_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_f_outline
knob_view2_f_outline.add_style(style_knob_view2_f_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_f_label = lv.label(knob_view2)
knob_view2_f_label.set_pos(174,226)
knob_view2_f_label.set_size(61,13)
knob_view2_f_label.set_text("PARAM")
knob_view2_f_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_f_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_f_label_main_main_default
style_knob_view2_f_label_main_main_default = lv.style_t()
style_knob_view2_f_label_main_main_default.init()
style_knob_view2_f_label_main_main_default.set_radius(0)
style_knob_view2_f_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_f_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_f_label_main_main_default.set_bg_opa(0)
style_knob_view2_f_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_f_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_11)
except AttributeError:
    try:
        style_knob_view2_f_label_main_main_default.set_text_font(lv.font_montserrat_11)
    except AttributeError:
        style_knob_view2_f_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_f_label_main_main_default.set_text_letter_space(2)
style_knob_view2_f_label_main_main_default.set_pad_left(0)
style_knob_view2_f_label_main_main_default.set_pad_right(0)
style_knob_view2_f_label_main_main_default.set_pad_top(0)
style_knob_view2_f_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_f_label
knob_view2_f_label.add_style(style_knob_view2_f_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

knob_view2_r_knob = lv.arc(knob_view2)
knob_view2_r_knob.set_pos(258,173)
knob_view2_r_knob.set_size(45,45)
knob_view2_r_knob.set_bg_angles(120, 60)
knob_view2_r_knob.set_angles(120, 220)
knob_view2_r_knob.set_rotation(0)
knob_view2_r_knob.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_knob.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_knob.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_knob.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_r_knob_main_main_default
style_knob_view2_r_knob_main_main_default = lv.style_t()
style_knob_view2_r_knob_main_main_default.init()
style_knob_view2_r_knob_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_r_knob_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_r_knob_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_r_knob_main_main_default.set_bg_opa(0)
style_knob_view2_r_knob_main_main_default.set_border_width(0)
style_knob_view2_r_knob_main_main_default.set_arc_color(lv.color_make(0x78,0x78,0x78))
style_knob_view2_r_knob_main_main_default.set_arc_width(12)

# add style for knob_view2_r_knob
knob_view2_r_knob.add_style(style_knob_view2_r_knob_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_r_knob_main_indicator_default
style_knob_view2_r_knob_main_indicator_default = lv.style_t()
style_knob_view2_r_knob_main_indicator_default.init()
style_knob_view2_r_knob_main_indicator_default.set_arc_color(lv.color_make(0xff,0x57,0x57))
style_knob_view2_r_knob_main_indicator_default.set_arc_width(12)

# add style for knob_view2_r_knob
knob_view2_r_knob.add_style(style_knob_view2_r_knob_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_r_knob_main_knob_default
style_knob_view2_r_knob_main_knob_default = lv.style_t()
style_knob_view2_r_knob_main_knob_default.init()
style_knob_view2_r_knob_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_knob_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_knob_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_r_knob_main_knob_default.set_bg_opa(0)
style_knob_view2_r_knob_main_knob_default.set_pad_all(5)

# add style for knob_view2_r_knob
knob_view2_r_knob.add_style(style_knob_view2_r_knob_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_r_outline = lv.arc(knob_view2)
knob_view2_r_outline.set_pos(247,163)
knob_view2_r_outline.set_size(65,65)
knob_view2_r_outline.set_bg_angles(120, 60)
knob_view2_r_outline.set_angles(120, 220)
knob_view2_r_outline.set_rotation(0)
knob_view2_r_outline.set_style_pad_top(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_outline.set_style_pad_bottom(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_outline.set_style_pad_left(0, lv.PART.MAIN | lv.STATE.DEFAULT)
knob_view2_r_outline.set_style_pad_right(0, lv.PART.MAIN | lv.STATE.DEFAULT)
# create style style_knob_view2_r_outline_main_main_default
style_knob_view2_r_outline_main_main_default = lv.style_t()
style_knob_view2_r_outline_main_main_default.init()
style_knob_view2_r_outline_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_r_outline_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_knob_view2_r_outline_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_r_outline_main_main_default.set_bg_opa(0)
style_knob_view2_r_outline_main_main_default.set_border_width(0)
style_knob_view2_r_outline_main_main_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_r_outline_main_main_default.set_arc_width(3)

# add style for knob_view2_r_outline
knob_view2_r_outline.add_style(style_knob_view2_r_outline_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_knob_view2_r_outline_main_indicator_default
style_knob_view2_r_outline_main_indicator_default = lv.style_t()
style_knob_view2_r_outline_main_indicator_default.init()
style_knob_view2_r_outline_main_indicator_default.set_arc_color(lv.color_make(0x32,0x32,0x32))
style_knob_view2_r_outline_main_indicator_default.set_arc_width(1)

# add style for knob_view2_r_outline
knob_view2_r_outline.add_style(style_knob_view2_r_outline_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_knob_view2_r_outline_main_knob_default
style_knob_view2_r_outline_main_knob_default = lv.style_t()
style_knob_view2_r_outline_main_knob_default.init()
style_knob_view2_r_outline_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_outline_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_outline_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_r_outline_main_knob_default.set_bg_opa(0)
style_knob_view2_r_outline_main_knob_default.set_pad_all(5)

# add style for knob_view2_r_outline
knob_view2_r_outline.add_style(style_knob_view2_r_outline_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

knob_view2_r_label = lv.label(knob_view2)
knob_view2_r_label.set_pos(269,220)
knob_view2_r_label.set_size(25,16)
knob_view2_r_label.set_text("R")
knob_view2_r_label.set_long_mode(lv.label.LONG.WRAP)
knob_view2_r_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_knob_view2_r_label_main_main_default
style_knob_view2_r_label_main_main_default = lv.style_t()
style_knob_view2_r_label_main_main_default.init()
style_knob_view2_r_label_main_main_default.set_radius(0)
style_knob_view2_r_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_knob_view2_r_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_knob_view2_r_label_main_main_default.set_bg_opa(0)
style_knob_view2_r_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_knob_view2_r_label_main_main_default.set_text_font(lv.font_MuseoSansRounded_900_15)
except AttributeError:
    try:
        style_knob_view2_r_label_main_main_default.set_text_font(lv.font_montserrat_15)
    except AttributeError:
        style_knob_view2_r_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_knob_view2_r_label_main_main_default.set_text_letter_space(2)
style_knob_view2_r_label_main_main_default.set_pad_left(0)
style_knob_view2_r_label_main_main_default.set_pad_right(0)
style_knob_view2_r_label_main_main_default.set_pad_top(0)
style_knob_view2_r_label_main_main_default.set_pad_bottom(0)

# add style for knob_view2_r_label
knob_view2_r_label.add_style(style_knob_view2_r_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(patch_selection)

while SDL.check():
    time.sleep_ms(5)
