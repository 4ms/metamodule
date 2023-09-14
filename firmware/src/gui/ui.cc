#include "ui.hh"
#include "debug.hh"
#include "gui/pages/page_manager.hh"
#include "params/params.hh"
#include "params/params_dbg_print.hh"
#include "params/params_state.hh"
#include "params/sync_params.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_file/patchlist.hh"
#include "patch_play/patch_playloader.hh"
#include "screen/lvgl_driver.hh"

namespace MetaModule
{

namespace
{
using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 8>;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf1;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf2;

static inline UartLog init_uart;
static inline LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, framebuf1, framebuf2};
constexpr int32_t throttle_amt = 10;
} // namespace

Ui::Ui(PatchPlayLoader &patch_playloader,
	   PatchStorageProxy &patch_storage,
	   SyncParams &sync_params,
	   PatchModQueue &patch_mod_queue)
	: sync_params{sync_params}
	, patch_playloader{patch_playloader}
	, msg_queue{1024}
	, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {

	params.clear();
	metaparams.clear();

	MMDisplay::init(metaparams, framebuf2);
	Gui::init_lvgl_styles();
	page_manager.init();
}

void Ui::update() {
	auto now = HAL_GetTick();
	if ((now - last_update_tm) <= 2)
		return;

	last_update_tm = now;

	lv_timer_handler();

	if (throttle_ctr-- <= 0) {
		throttle_ctr = throttle_amt;
		page_update_task();
	}

	auto msg = msg_queue.get_message();
	if (!msg.empty()) {
		// printf_("%s", msg.data());
		msg_queue.clear_message();
	}
	// Debug::Pin0::low();

	// Uncomment to enable:
	// print_dbg_params.output_debug_info(HAL_GetTick());
	// print_dbg_params.output_load(HAL_GetTick());
}

void Ui::page_update_task() {
	//This returns false when audio stops
	[[maybe_unused]] bool read_ok = sync_params.read_sync(params, metaparams);
	//if (!read_ok) ... restart audio
	page_manager.update_current_page();
	patch_playloader.handle_sync_patch_loading();
}

} // namespace MetaModule
