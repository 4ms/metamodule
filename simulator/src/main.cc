#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "ui.hh"

#include <cstdio>
void _log_cb(const char *buf) {
	printf("%s", buf);
	fflush(stdout);
}

void create_test_page();

int main(void) {
	lv_init();
	lv_log_register_print_cb(_log_cb);
	lv_port_disp_init(320, 240);
	lv_port_indev_init(true);

	lv_log("Starting LVGL\n");

	// Create page
	create_test_page();
	//////

	while (lv_get_quit() == LV_QUIT_NONE) {
		lv_task_handler();
	}

	lv_port_disp_deinit();
	lv_port_indev_deinit();
	lv_deinit();

	return 0;
}

void create_test_page() {
	static lv_group_t *g;
	static lv_obj_t *tv;

	g = lv_group_create();
	lv_group_set_default(g);

	lv_indev_t *cur_drv = lv_indev_get_next(nullptr);
	if (cur_drv) {
		if (cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD) {
			lv_indev_set_group(cur_drv, g);
		}
	}

	tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, LV_DPI_DEF / 3);

	lv_tabview_add_tab(tv, "Selectors");
	lv_tabview_add_tab(tv, "Text input");
}
