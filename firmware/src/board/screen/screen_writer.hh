#pragma once
#include "conf/screen_conf.hh"
#include "drivers/cache.hh"
#include "drivers/pin.hh"
#include "drivers/spi_dma_datacmd_driver.hh"
#include "screen/ssd1306.hh"

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

		transmit_blocking<Cmd>(SSD1306::InitCmds<SSD1306::VCCMode::SWITCHCAPVCC>);
	}

	void register_xfer_complete_cb(auto cb) {
		register_callback(cb);
	}

	void transfer_frame(uint8_t *buffer) {
		transmit_blocking<Cmd>(SSD1306::StartRedrawCmds);

		auto buffer_size_bytes = ScreenConf::width * ScreenConf::height / 8;

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
};
} // namespace MetaModule
