#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/ipcc.hh"
#include "drivers/pin.hh"
#include "drivers/rcc.hh"
#include "drivers/system_clocks.hh"
#include "fs/fatfs/sd_host.hh"
#include "fs/fs_manager.hh"
#include "hsem_handler.hh"
#include "usb/usb_manager.hh"

#ifdef ENABLE_WIFI_BRIDGE
#include <wifi_interface.hh>
#endif

namespace MetaModule
{

constexpr bool reload_default_patches = false;

static void app_startup() {
	using namespace mdrivlib;

	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4CoreReady>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<AuxCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
	core_m4::RCC_Enable::IPCC_::set();
};

} // namespace MetaModule

void main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	app_startup();

	pr_info("M4 starting\n");

	// USB
	UsbManager usb{*SharedMemoryS::ptrs.ramdrive};
	usb.start();

	// SD Card
	SDCardHost sd;

	FilesystemManager fs{usb.get_msc_fileio(), sd.get_fileio(), SharedMemoryS::ptrs.icc_message};
	if (reload_default_patches)
		fs.reload_default_patches();

#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::init(&fs.get_patch_storage());
#endif

	// Controls
	auto param_block_base = SharedMemoryS::ptrs.param_block;
	auto auxsignal_buffer = SharedMemoryS::ptrs.auxsignal_block;
	Controls controls{*param_block_base, *auxsignal_buffer, usb.get_midi_host()};

	HWSemaphoreCoreHandler::enable_global_ISR(0, 1);

	controls.start();

	// Read controls a few times before letting A7 start
	uint32_t startup_delay = 0x10000;
	while (startup_delay--) {
		controls.process();
	}

	pr_info("M4 initialized\n");
	HWSemaphore<MetaModule::M4CoreReady>::unlock();

	while (true) {
		controls.process();

		usb.process();
		sd.process();
		fs.process();

#ifdef ENABLE_WIFI_BRIDGE
		WifiInterface::run();
#endif
	}
}
