#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_player.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "ui.hh"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc_storage.h"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

extern PCD_HandleTypeDef hpcd;

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	PatchPlayer patch_player;
	ParamQueue param_queue;
	UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};

	Ui ui{patch_player, param_queue, mbox};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_queue,
					  mbox,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

	//Used by mini, but will be deprecated:
	static uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);

	// Needed for LED refresh
	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// // Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;
	param_queue.clear();
	audio.start();
	ui.start();

	USBD_HandleTypeDef USBD_Device;
	auto init_ok = USBD_Init(&USBD_Device, &MSC_Desc, 0);
	if (init_ok != USBD_OK) {
		printf("USB Device failed to initialize!\r\n");
		printf("Error code: %d", static_cast<int>(init_ok));
	}
	USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);
	USBD_MSC_RegisterStorage(&USBD_Device, &USBD_MSC_fops);
	USBD_Start(&USBD_Device);

	InterruptManager::register_and_start_isr(OTG_IRQn, 1, 1, []{
		Debug::Pin2::high();
		HAL_PCD_IRQHandler(&hpcd);
		Debug::Pin2::low();
	});

	while (true) {
		ui.update();
	}
}

void recover_from_task_fault() {
	main();
}
