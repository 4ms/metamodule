#include "auxsignal.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "conf/ramdisk_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system_startup.hh"
#include "fatfs/ramdisk_ops.hh"
#include "mp1m4/hsem_handler.hh"
#include "params.hh"
#include "ramdisk.hh"
#include "shared_bus_queue.hh"
#include "shared_memory.hh"
#include "usb/usb_manager.hh"

#include "patch_mod_queue.hh"
#include "patch_storage.hh"

namespace MetaModule
{

using namespace mdrivlib;

static void app_startup() {
	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
	core_m4::RCC_Enable::IPCC_::set();
};

static void signal_m4_ready_after_delay() {
	static uint32_t ctr = 0x10000;
	if (ctr == 1) {
		printf_("M4 initialized\n");
		HWSemaphore<MetaModule::M4_ready>::unlock();
	}
	if (ctr > 0)
		ctr--;
}

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	app_startup();

	printf_("M4 starting\n");

	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto auxsignal_buffer = SharedMemory::read_address_of<DoubleAuxStreamBlock *>(SharedMemory::AuxSignalBlockLocation);
	auto virtdrive = SharedMemory::read_address_of<RamDrive *>(SharedMemory::RamDiskLocation);
	auto raw_patch_data = SharedMemory::read_address_of<std::span<char> *>(SharedMemory::PatchDataLocation);
	auto shared_message =
		SharedMemory::read_address_of<InterCoreCommMessage volatile *>(SharedMemory::InterCoreCommParamsLocation);
	auto shared_patch_file_list =
		SharedMemory::read_address_of<std::span<PatchFile> *>(SharedMemory::PatchListLocation);

	PatchModQueue patch_mod_queue; //TODO: share with A7

	I2CPeriph i2c{a7m4_shared_i2c_codec_conf};
	// I2CPeriph auxi2c{aux_i2c_conf}; //This is the Aux header for button/pot expander
	i2c.enable_IT(a7m4_shared_i2c_codec_conf.priority1, a7m4_shared_i2c_codec_conf.priority2);

	mdrivlib::GPIOExpander ext_gpio_expander{i2c, extaudio_gpio_expander_conf};
	mdrivlib::GPIOExpander main_gpio_expander{i2c, mainboard_gpio_expander_conf};

	RamDiskOps ramdiskops{*virtdrive};
	UsbManager usb{ramdiskops};

	auto usb_fileio = usb.get_msc_fileio();
	PatchStorage patch_storage{*raw_patch_data, *shared_message, *shared_patch_file_list, usb_fileio};

	usb.start();

	Controls controls{*param_block_base, *auxsignal_buffer, main_gpio_expander, ext_gpio_expander, usb.get_midi_host()};
	SharedBusQueue i2cqueue{main_gpio_expander, ext_gpio_expander};

	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	controls.start();

	while (true) {
		signal_m4_ready_after_delay();

		if (i2c.is_ready()) {
			i2cqueue.update();
		}

		usb.process();
		patch_storage.handle_messages();

		__NOP();
	}
}

void recover_from_task_fault() {
	while (true)
		;
}
