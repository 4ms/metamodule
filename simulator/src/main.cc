#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "ui.hh"

void create_test_page();

int main(void) {
	lv_init();
	lv_port_disp_init(320, 240);

	MetaModule::PatchPlayer patch_player;
	MetaModule::PatchStorageProxy patch_storage;
	MetaModule::PatchPlayLoader patch_playloader{patch_storage, patch_player};
	MetaModule::PatchModQueue patch_mod_queue;
	MetaModule::Ui ui{patch_playloader, patch_storage, patch_mod_queue};

	ui.start();

	while (ui.update()) {
	}

	lv_port_disp_deinit();

	lv_deinit();

	return 0;
}
