#include "screen_writer.hh"
#include <atomic>

namespace Mousai
{

class Display {
	MetaModule::ScreenFrameWriter _spi_driver;
	static inline Display *_instance;
	std::atomic<bool> busy;

public:
	Display() {
		_instance = this;
	}

	void init() {
		_spi_driver.init();
		_spi_driver.register_xfer_complete_cb(end_flush);
		_spi_driver.clear_overrun_on_interrupt();
	}

	static void end_flush() {
		_instance->busy.store(false, std::memory_order_release);
	}

	static bool is_ready() {
		return !_instance->busy.load(std::memory_order_acquire);
	}

	void flush_screen(std::span<uint8_t> buffer) {
		bool expected = false;
		while (!busy.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
		}

		_spi_driver.transfer_frame(buffer.data());
	}
};

} // namespace Mousai
