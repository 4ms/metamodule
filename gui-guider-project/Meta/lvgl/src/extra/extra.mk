CSRCS += lv_extra.c
CSRCS += lv_theme_default.c
CSRCS += lv_theme_basic.c
CSRCS += lv_theme_mono.c
CSRCS += lv_flex.c
CSRCS += lv_grid.c
CSRCS += lv_meter.c
CSRCS += lv_keyboard.c
CSRCS += lv_win.c
CSRCS += lv_chart.c
CSRCS += lv_tileview.c
CSRCS += lv_spinner.c
CSRCS += lv_calendar_header_dropdown.c
CSRCS += lv_calendar.c
CSRCS += lv_calendar_header_arrow.c
CSRCS += lv_tabview.c
CSRCS += lv_list.c
CSRCS += lv_led.c
CSRCS += lv_colorwheel.c
CSRCS += lv_animimg.c
CSRCS += lv_imgbtn.c
CSRCS += lv_spinbox.c
CSRCS += lv_span.c
CSRCS += lv_msgbox.c


DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/basic
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/mono
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/animimg
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/calendar
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/chart
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/colorwheel
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/imgbtn
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/keyboard
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/led
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/list
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/meter
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/msgbox
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/span
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinbox
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinner
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tabview
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tileview
DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/win
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/basic
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/mono
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/animimg
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/calendar
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/chart
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/colorwheel
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/imgbtn
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/keyboard
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/led
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/list
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/meter
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/msgbox
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/span
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinbox
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinner
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tabview
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tileview
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/win

CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/basic \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/mono \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/animimg \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/calendar \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/chart \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/colorwheel \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/imgbtn \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/keyboard \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/led \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/list \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/meter \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/msgbox \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/span \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinbox \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinner \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tabview \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tileview \
           -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/win \
"
