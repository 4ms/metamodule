#include "auxsignal.hh"
#include "boot/system_startup_m4.hh"
#include "conf/adc_spi_conf.hh"
#include "conf/gpio_expander_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/gpio_expander.hh"
#include "drivers/hsem.hh"
#include "drivers/pca9685_led_driver.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system.hh"
#include "mp1m4/hsem_handler.hh"
#include "muxed_adc.hh"
#include "params.hh"
#include "screen_writer.hh"
#include "shared_bus.hh"
#include "shared_bus_queue.hh"
#include "shared_memory.hh"

namespace MetaModule
{
static void app_startup()
{
	target::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<M7_ready>::is_locked())
		;

	target::SystemClocks init_system_clocks{};
};

struct StaticBuffers {
	static inline /*__attribute__((section(".shared_memory")))*/ MMScreenConf::FrameBufferT screen_writebuf;
} _sb;
} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	app_startup();

	SharedBus::i2c.init(i2c_conf_controls);

	auto led_frame_buffer = SharedMemory::read_address_of<uint32_t *>(SharedMemory::LEDFrameBufLocation);
	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto screen_readbuf = SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenBufLocation);
	auto auxsignal_buffer =
		SharedMemory::read_address_of<DoubleAuxSignalStreamBlock *>(SharedMemory::AuxSignalBlockLocation);

	// Led Driver
	PCA9685Driver led_driver{SharedBus::i2c, kNumLedDriverChips, led_frame_buffer};

	// Controls
	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CVAdcChipT cvadc;
	GPIOExpander gpio_expander{SharedBus::i2c, gpio_expander_conf};
	Controls controls{potadc, cvadc, *param_block_base, gpio_expander, *auxsignal_buffer};

	// SharedBus
	SharedBusQueue<LEDUpdateHz> i2cqueue{led_driver, controls};
	SharedBus::i2c.enable_IT(i2c_conf_controls.priority1, i2c_conf_controls.priority2);
	led_driver.start_it_mode();

	controls.start();

	// Screen: Full frame transfer mode
	ScreenFrameWriter screen_writer{screen_readbuf, &StaticBuffers::screen_writebuf, MMScreenConf::FrameBytes};
	screen_writer.init();

	HWSemaphore<ScreenFrameBufLock>::clear_ISR();
	HWSemaphore<ScreenFrameBufLock>::disable_channel_ISR();
	HWSemaphoreCoreHandler::register_channel_ISR<ScreenFrameBufLock>([&]() {
		// Todo: ideally we would disable this ISR here, then enable it when transfer has completed
		// HWSemaphore<ScreenFrameBufLock>::disable_channel_ISR();
		screen_writer.transfer_buffer_to_screen();
	});
	HWSemaphore<ScreenFrameBufLock>::enable_channel_ISR();

	HWSemaphore<ScreenFrameWriteLock>::disable_channel_ISR();
	HWSemaphore<ScreenFrameWriteLock>::unlock();

	HWSemaphoreCoreHandler::enable_global_ISR(2, 2);

	while (1) {
		if (SharedBus::i2c.is_ready()) {
			i2cqueue.update();
		}
		__NOP();
	}

	// while (1) {
	// 	Debug::red_LED2::low();
	// 	HAL_Delay(10);
	// 	Debug::red_LED2::high();
	// 	HAL_Delay(50);
	// }
}

void recover_from_task_fault()
{
	while (1)
		;
}
