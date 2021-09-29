#include "auxsignal.hh"
#include "conf/adc_i2c_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/screen_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/register_access.hh"
#include "drivers/system_startup.hh"
#include "lvgl_driver.hh"
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
	core_m4::RCC_Enable::HSEM_::set();

	// Tell A7 we're not ready yet
	HWSemaphore<M4_ready>::lock();

	// Wait until A7 is ready
	while (HWSemaphore<MainCoreReady>::is_locked())
		;

	SystemClocks init_system_clocks{};
};

class MMDisplay {
	static inline ScreenFrameWriter spi_driver;
	static inline Timekeeper update_tasks;

public:
	static void init()
	{
		spi_driver.init();
		update_tasks.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 333, // =  333Hz = 3ms
				.priority1 = 2,
				.priority2 = 2,
			},
			[] { lv_timer_handler(); });
	}
	static void start()
	{
		update_tasks.start();
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
	{
		spi_driver.transfer_partial_frame(
			area->x1, area->y1, area->x2, area->y2, reinterpret_cast<uint16_t *>(color_p), [&] {
				lv_disp_flush_ready(disp_drv);
			});
	}
};

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	app_startup();

	SharedBus::i2c.init(i2c_conf_controls);

	auto param_block_base = SharedMemory::read_address_of<DoubleBufParamBlock *>(SharedMemory::ParamsPtrLocation);
	auto screen_readbuf = SharedMemory::read_address_of<MMScreenConf::FrameBufferT *>(SharedMemory::ScreenBufLocation);
	auto auxsignal_buffer = SharedMemory::read_address_of<DoubleAuxStreamBlock *>(SharedMemory::AuxSignalBlockLocation);

	// Controls
	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	Controls controls{potadc, *param_block_base, *auxsignal_buffer};

	// SharedBus
	SharedBusQueue i2cqueue{controls};
	SharedBus::i2c.enable_IT(i2c_conf_controls.priority1, i2c_conf_controls.priority2);

	controls.start();

	// ScreenFrameWriter screen_writer{screen_readbuf, &StaticBuffers::half_screen_writebuf, MMScreenConf::FrameBytes};
	// screen_writer.init();

	//HWSemaphore<ScreenFrameBufLock>::clear_ISR();
	//HWSemaphore<ScreenFrameBufLock>::disable_channel_ISR();
	//HWSemaphoreCoreHandler::register_channel_ISR<ScreenFrameBufLock>([&]() {
	//	//@16Hz screen refresh rate: 60ms, 12us width
	//	screen_writer.transfer_buffer_to_screen();
	//});
	//HWSemaphore<ScreenFrameBufLock>::enable_channel_ISR();

	//HWSemaphore<ScreenFrameWriteLock>::disable_channel_ISR();
	//HWSemaphore<ScreenFrameWriteLock>::unlock();

	//HWSemaphoreCoreHandler::enable_global_ISR(2, 2);

	MMDisplay::init();
	LVGLDriver<MMScreenBufferConf::viewHeight, MMScreenBufferConf::viewHeight> gui{MMDisplay::flush_to_screen};

	MMDisplay::start();

	while (true) {
		Debug::Pin2::high();
		if (SharedBus::i2c.is_ready()) {
			// Debug::red_LED2::high();
			Debug::Pin3::high();
			i2cqueue.update();
			Debug::Pin3::low();
			// Debug::red_LED2::low();
		}
		Debug::Pin2::low();
		__NOP();
	}
}

void recover_from_task_fault()
{
	while (true)
		;
}
