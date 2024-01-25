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
#include "hsem_handler.hh"
#include "usb/usb_manager.hh"

#include "patch_file/patch_storage.hh"
#include "fw_update/firmware_file_finder.hh"
#include "fw_update/firmware_writer.hh"

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

	// ICC dependant modules
	PatchStorage patch_storage{sd.get_fileio(), usb.get_msc_fileio()};
	FirmwareFileFinder firmware_files{sd.get_fileio(), usb.get_msc_fileio()};
	FirmwareWriter firmware_writer{sd.get_fileio(), usb.get_msc_fileio()};

	mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage> intercore_comm(*SharedMemoryS::ptrs.icc_message);

	if (reload_default_patches)
		patch_storage.reload_default_patches();

#ifdef ENABLE_WIFI_BRIDGE
	WifiInterface::init(&patch_storage);
	WifiInterface::start();
#endif

	// Controls
	Controls controls{*SharedMemoryS::ptrs.param_block, *SharedMemoryS::ptrs.auxsignal_block, usb.get_midi_host()};

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
		
		auto message = intercore_comm.get_new_message();

		if (message.message_type != IntercoreStorageMessage::MessageType::None)
		{
			// Function to pass a message to a receiver
			// If message is handled by the receiver, the response is sent
			// otherwise we can continue with the next receiver
			auto process_receiver = [&intercore_comm, &message](auto& receiver)
			{
				if (auto response = receiver.handle_message(message); response)
				{
					// mark message as handled
					message.message_type = IntercoreStorageMessage::MessageType::None;

					// try to send response infinitely
					while (not intercore_comm.send_message(*response));
					return true;
				}
				return false;
			};

			// Handle all receivers
			if (not process_receiver(firmware_files))
			{
				if (not process_receiver(patch_storage))
				{
					if (not process_receiver(firmware_writer))
					{
						pr_err("ICC message of type %u not handled\n", message.message_type);
					}
				}
			}
		}

#ifdef ENABLE_WIFI_BRIDGE
		WifiInterface::run();
#endif
	}
}
