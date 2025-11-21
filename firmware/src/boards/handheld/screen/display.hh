#include "conf/debug.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/cache.hh"
#include "drivers/screen_9bit_spi_setup.hh"
#include "drivers/screen_ltdc.hh"
#include "drivers/spi_transfer.hh"
#include "drivers/ss7701s_lcd_init.hh"
#include "sketch/sketch.hh"
#include <span>

namespace Handheld
{

void set_buffer(std::span<Color>);
}

namespace MetaModule
{

void start_pixel_clock();

class Display {
	static constexpr uint32_t ScreenWidth = ScreenBufferConf::viewWidth;
	static constexpr uint32_t ScreenHeight = ScreenBufferConf::viewHeight;

	static inline ScreenParallelWriter<ScreenConf> ltdc_driver;

	using FrameBufferT = std::array<Handheld::Color, MetaModule::ScreenBufferConf::NumPixels>;
	static inline std::array<FrameBufferT, 2> framebuf alignas(64);
	static inline unsigned cur_buf = 0;

public:
	static void init() {
		using namespace mdrivlib;

		Screen9BitSpiSetup<SpiTransferDriver<ScreenControlConf>> screen_setup{ScreenControlConf::reset};

		screen_setup.setup_driver_chip(mdrivlib::ST7701S::InitCmds);

		start_pixel_clock();
		HAL_Delay(1);

		TIM3->CNT = 0;
		ltdc_driver.init(framebuf[cur_buf].data());

		swap();
		swap();

		printf("MMDisplay::init\n");
	}

	static void swap() {
		auto next_buf = (cur_buf == 1) ? 0 : 1;

		// clean the buffer that we are done writing into, and we want to pass to the LTDC driver
		mdrivlib::SystemCache::clean_dcache_by_range(framebuf[cur_buf].data(), ScreenWidth * ScreenHeight * 2);

		// invalidate the buffer LVGL will write into next
		mdrivlib::SystemCache::invalidate_dcache_by_range(framebuf[next_buf].data(), ScreenWidth * ScreenHeight * 2);

		// Display the old buffer
		ltdc_driver.set_buffer(framebuf[cur_buf].data());

		// Draw into the new buffer
		Handheld::set_buffer(framebuf[next_buf]);

		// Swap
		cur_buf = next_buf;
	}
};
} // namespace MetaModule
