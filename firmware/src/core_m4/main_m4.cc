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
#include "firmware_files.hh"
#include "fs/fatfs/ramdisk_ops.hh"
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

using namespace mdrivlib;

static void app_startup() {
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

void main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	app_startup();

	pr_info("M4 starting\n");

	auto param_block_base = SharedMemoryS::ptrs.param_block;
	auto auxsignal_buffer = SharedMemoryS::ptrs.auxsignal_block;
	auto virtdrive = SharedMemoryS::ptrs.ramdrive;
	auto raw_patch_span = SharedMemoryS::ptrs.raw_patch_span;
	auto shared_message = SharedMemoryS::ptrs.icc_message;
	auto shared_patch_file_list = SharedMemoryS::ptrs.patch_file_list;

	I2CPeriph i2c{a7m4_shared_i2c_codec_conf};
	// I2CPeriph auxi2c{aux_i2c_conf}; //This is the Aux header for button/pot expander
	i2c.enable_IT(a7m4_shared_i2c_codec_conf.priority1, a7m4_shared_i2c_codec_conf.priority2);

	mdrivlib::GPIOExpander ext_gpio_expander{i2c, extaudio_gpio_expander_conf};
	mdrivlib::GPIOExpander main_gpio_expander{i2c, mainboard_gpio_expander_conf};

	RamDiskOps ramdiskops{*virtdrive};

	// USB
	UsbManager usb{ramdiskops};
	usb.start();
	auto usb_fileio = usb.get_msc_fileio();

	// SD Card
	SDCardOps<SDCardConf> sdcard_ops;
	FatFileIO sdcard_fileio{&sdcard_ops, Volume::SDCard};

	// IO with USB and SD Card
	InterCoreComm<ICCCoreType::Responder, IntercoreStorageMessage> intercore_comm{*shared_message};
	PatchStorage patch_storage{
		*raw_patch_span, *shared_patch_file_list, sdcard_fileio, usb_fileio, reload_default_patches};
	FirmwareFileFinder firmware_files{*raw_patch_span, sdcard_fileio, usb_fileio};

	// Controls
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

		auto message = intercore_comm.get_new_message();
		patch_storage.handle_message(message);
		firmware_files.handle_message(message);

		patch_storage.send_pending_message(intercore_comm);
		firmware_files.send_pending_message(intercore_comm);

		__NOP();
	}
}
