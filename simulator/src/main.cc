#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "ui.hh"

// #include <cstdio>
// void _log_cb(const char *buf) {
// 	printf("%s", buf);
// 	fflush(stdout);
// }

void create_test_page();

int main(void) {
	lv_init();
	// lv_log_register_print_cb(_log_cb);
	lv_port_disp_init(320, 240);
	lv_port_indev_init(false);

	lv_log("Starting LVGL\n");

	MetaModule::PatchPlayer patch_player;
	MetaModule::PatchStorageProxy patch_storage;
	MetaModule::PatchPlayLoader patch_playloader{patch_storage, patch_player};
	MetaModule::PatchModQueue patch_mod_queue;

	MetaModule::Ui ui{patch_playloader, patch_storage, patch_mod_queue};
	ui.start();

	while (lv_get_quit() == LV_QUIT_NONE) {
		ui.update();
	}

	lv_port_disp_deinit();
	lv_port_indev_deinit();
	lv_deinit();

	return 0;
}
