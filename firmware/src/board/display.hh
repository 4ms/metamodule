#include "conf/hsem_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "drivers/hsem.hh"
#include "screen_writer.hh"
#include <cstddef>

namespace Mousai
{

class Display {
	static constexpr size_t BufferSize = ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight;
	static inline MetaModule::ScreenFrameWriter _spi_driver;

public:
	static void init() {
		_spi_driver.init();
		_spi_driver.register_partial_frame_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();
	}

	static void end_flush() {
		HWSemaphore<MetaModule::ScreenFrameWriteLock>::unlock();
	}

	static bool is_ready() {
		return HWSemaphore<MetaModule::ScreenFrameWriteLock>::is_locked();
	}

	static void flush_screen(std::span<uint8_t> buffer) {
		while (HWSemaphore<MetaModule::ScreenFrameWriteLock>::lock() == HWSemaphoreFlag::LockFailed) {
			// spin until reaady
		}

		_spi_driver.transfer_partial_frame(
			0, 0, ScreenBufferConf::viewWidth, ScreenBufferConf::viewHeight, buffer.data());
	}

	static void flush_portion(int xstart, int ystart, int xend, int yend, std::span<uint8_t> buffer) {
		while (HWSemaphore<MetaModule::ScreenFrameWriteLock>::lock() == HWSemaphoreFlag::LockFailed) {
			// spin until reaady
		}

		_spi_driver.transfer_partial_frame(xstart, ystart, xend, yend, buffer.data());
	}
};

} // namespace Mousai
