#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "ui.hh"

void create_test_page();

static RotaryEncoderKeys keys{
	.turn_cw = SDLK_RIGHT,
	.turn_ccw = SDLK_LEFT,
	.click = SDLK_DOWN,
	.aux_button = SDLK_UP,
	.quit = SDLK_ESCAPE,
};

int main(void) {
	lv_init();
	lv_port_disp_init(320, 240);

	{
		auto input_driver = LvglEncoderSimulatorDriver{keys};

		lv_log("Starting LVGL\n");

		MetaModule::PatchPlayer patch_player;
		MetaModule::PatchStorageProxy patch_storage;
		MetaModule::PatchPlayLoader patch_playloader{patch_storage, patch_player};
		MetaModule::PatchModQueue patch_mod_queue;

		MetaModule::Ui ui{patch_playloader, patch_storage, patch_mod_queue};
		ui.start();

		while (input_driver.get_quit() == LV_QUIT_NONE) {
			ui.update();
		}

		lv_port_disp_deinit();
	}

	lv_deinit();

	return 0;
}
