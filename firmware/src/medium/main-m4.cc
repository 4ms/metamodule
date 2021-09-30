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
	static inline ScreenFrameWriter _spi_driver;
	static inline Timekeeper _run_lv_tasks_tmr;
	static inline bool _ready = false;

public:
	static void init()
	{
		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);

		_run_lv_tasks_tmr.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 333, // =  333Hz = 3ms
				.priority1 = 2,
				.priority2 = 2,
			},
			[] { _ready = true; });
	}

	static void start()
	{
		_run_lv_tasks_tmr.start();
	}

	static bool is_ready()
	{
		return _ready;
	}

	static void clear_ready()
	{
		_ready = false;
	}

	static inline lv_disp_drv_t *last_used_disp_drv;
	static void end_flush()
	{
		lv_disp_flush_ready(last_used_disp_drv);
	}

	static void flush_to_screen(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
	{
		last_used_disp_drv = disp_drv;
		_spi_driver.transfer_partial_frame(
			area->x1, area->y1, area->x2, area->y2, reinterpret_cast<uint16_t *>(color_p));
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

	MMDisplay::init();
	LVGLDriver<MMScreenBufferConf::viewWidth, MMScreenBufferConf::viewHeight> gui{MMDisplay::flush_to_screen};
	MMDisplay::start();
	lv_obj_t *slider1 = lv_slider_create(lv_scr_act());
	lv_obj_set_x(slider1, 30);
	lv_obj_set_y(slider1, 10);
	lv_obj_set_size(slider1, 15, 100);

	Timekeeper slider_tm;
	int32_t slider_val = 30;
	slider_tm.init(
		{
			.TIMx = TIM17,
			.period_ns = 1000000000 / 30, // =  30Hz
			.priority1 = 2,
			.priority2 = 2,
		},
		[slider1 = slider1, &slider_val = slider_val] {
			slider_val -= 1;
			if (slider_val == 0)
				slider_val = 100;
			lv_slider_set_value(slider1, slider_val, LV_ANIM_ON);
		});
	slider_tm.start();

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
		if (MMDisplay::is_ready()) {
			Debug::Pin1::high();
			MMDisplay::clear_ready();
			lv_timer_handler(); //calls disp.flush_cb -> MMDisplay::flush_to_screen -> spi_driver.transfer_partial_frame
			Debug::Pin1::low();
		}
		__NOP();
	}
}

void recover_from_task_fault()
{
	while (true)
		;
}
