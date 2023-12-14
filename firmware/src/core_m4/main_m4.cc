#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "conf/ramdisk_conf.hh"
#include "controls.hh"
#include "core_intercom/shared_memory.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system_clocks.hh"
#include "firmware_file_finder.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fatfs/sd_host.hh"
#include "fs/fs_manager.hh"
#include "fs/ramdisk.hh"
#include "gpio_expander_reader.hh"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_file/patch_storage.hh"
#include "patch_play/patch_mod_queue.hh"
#include "usb/usb_manager.hh"

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

	// Controls
	I2CPeriph i2c{a7m4_shared_i2c_codec_conf};
	i2c.enable_IT(a7m4_shared_i2c_codec_conf.priority1, a7m4_shared_i2c_codec_conf.priority2);

	mdrivlib::GPIOExpander ext_gpio_expander{i2c, extaudio_gpio_expander_conf};
	mdrivlib::GPIOExpander main_gpio_expander{i2c, mainboard_gpio_expander_conf};

	auto param_block_base = SharedMemoryS::ptrs.param_block;
	auto auxsignal_buffer = SharedMemoryS::ptrs.auxsignal_block;
	Controls controls{*param_block_base, *auxsignal_buffer, main_gpio_expander, ext_gpio_expander, usb.get_midi_host()};
	SharedBusQueue i2cqueue{main_gpio_expander, ext_gpio_expander};

	HWSemaphoreCoreHandler::enable_global_ISR(0, 1);

	controls.start();

	// Run the i2c queue a few times before letting A7 start
	uint32_t startup_delay = 0x10000;
	while (startup_delay--) {
		if (i2c.is_ready())
			i2cqueue.update();
	}

	pr_info("M4 initialized\n");
	HWSemaphore<MetaModule::M4CoreReady>::unlock();

	while (true) {
		if (i2c.is_ready())
			i2cqueue.update();

		usb.process();
		sd.process();

		fs.process();
	}
}
