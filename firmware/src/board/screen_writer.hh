#pragma once
#include "conf/screen_conf.hh"
#include "drivers/cache.hh"
#include "drivers/pin.hh"
#include "drivers/screen_ST77XX.hh"
#include "drivers/spi_dma_datacmd_driver.hh"

#include <span>

using namespace mdrivlib;

namespace MetaModule
{

using ScreenConf = Mousai::ScreenConf;
using ScreenTransferDriverT = Mousai::ScreenTransferDriverT;

class ScreenFrameWriter : public mdrivlib::SpiDmaDataCmdDriver<Mousai::ScreenConf, Mousai::ScreenTransferDriverT> {

public:
	ScreenFrameWriter() = default;

	void reinit() {
		SpiDmaDataCmdDriver<ScreenConf, ScreenTransferDriverT>::reinit();
	}

	void init() {
		SpiDmaDataCmdDriver<ScreenConf, ScreenTransferDriverT>::init();
		reset();
		using InitCommands =
			mdrivlib::ST77XX::ST7789Init<ScreenConf::width,
										 ScreenConf::height,
										 ScreenConf::IsInverted ? ST77XX::Inverted : ST77XX::NotInverted>;
		init_display_driver(InitCommands::cmds);
	}

	void register_partial_frame_cb(auto cb) {
		register_callback(cb);
	}

	void transfer_partial_frame(int xstart, int ystart, int xend, int yend, uint8_t *buffer) {
		set_pos(xstart, ystart, xend, yend);
		auto buffer_size_bytes = (xend - xstart + 1) * (yend - ystart + 1) / 8;
		config_dma_transfer(reinterpret_cast<uint32_t>(buffer), buffer_size_bytes);
		mdrivlib::SystemCache::clean_dcache_by_range(buffer, buffer_size_bytes);
		__DSB();

		start_dma_transfer();
	}

	void reset() {
		Pin reset_pin{ScreenConf::ResetPin, PinMode::Output};
		reset_pin.high();
		HAL_Delay(1);
		reset_pin.low();
		HAL_Delay(10);
		reset_pin.high();
		HAL_Delay(120);
	}

protected:
	ScreenConf::Rotation _rotation;
	int _width = ScreenConf::width;
	int _height = ScreenConf::height;

	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
		transmit_blocking<Cmd>(ST77XX::CASET);
		transmit_blocking<Data>(Xstart, Xend);

		transmit_blocking<Cmd>(ST77XX::RASET);
		transmit_blocking<Data>(Ystart, Yend);

		transmit_blocking<Cmd>(ST77XX::RAMWR);
	}

	void init_display_driver(std::span<const ScreenInitCommand> cmds) {
		for (auto &c : cmds) {
			transmit_blocking<Cmd>(c.cmd);
			for (int i = 0; i < c.num_args; i++) {
				transmit_blocking<Data>(c.args[i]);
			}
			if (c.delay_ms)
				HAL_Delay(c.delay_ms);
		}
	}
};
} // namespace MetaModule
