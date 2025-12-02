#include "conf/hsem_conf.hh"
#include "controls.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/hsem.hh"
#include "drivers/system_clocks.hh"
#include "fs/fs_messages.hh"
#include "hsem_handler.hh"

namespace MetaModule
{

constexpr bool reload_default_patches = false;

static void app_startup() {
	using namespace mdrivlib;

	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4CoreReady>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
	core_m4::RCC_Enable::IPCC_::set();
};

} // namespace MetaModule

int main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	app_startup();

	pr_info("M4 starting\n");

	// SD Card
	// SDCardHost sd;

	FilesystemMessages fs_messages{SharedMemoryS::ptrs.icc_message};

	// if (reload_default_patches)
	// 	fs_messages.reload_default_patches();

	// Controls
	Controls controls{*SharedMemoryS::ptrs.param_block};

	HWSemaphoreCoreHandler::enable_global_ISR(0, 1);

	controls.start();

	// Read controls and allow time for USB drive to be detected before letting A7 start
	uint32_t startup_delay = 0x4'0000;
	while (startup_delay--) {
		controls.process();
	}

	pr_info("M4 initialized\n");

	HWSemaphore<MetaModule::M4CoreReady>::unlock();

	while (true) {
		controls.process();
		fs_messages.process();
	}
}
