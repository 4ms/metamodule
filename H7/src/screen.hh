#pragma once
// #include "Adafruit_ST7789.h"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/spi_config_struct.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

// conf/screen_conf.hh
constexpr struct ScreenConf {
	static constexpr unsigned ScreenSPIx = 6;
	static constexpr SpiConfig<ScreenSPIx> screen_SPI_conf = {
		.IRQn = SPI6_IRQn,
		.priority1 = 2,
		.priority2 = 3,

		.SCLK = {GPIO::A, 5, LL_GPIO_AF_8},
		.COPI = {GPIO::A, 7, LL_GPIO_AF_8},
		.CIPO = {GPIO::A, 15, 0}, // unused pin
		.CS =
			{
				{GPIO::A, 4, LL_GPIO_AF_8},
			},

		.use_hardware_ss = true,
		.clock_division = 8,
		.data_size = 8,
		.data_dir = SpiDataDir::TXOnly,
	};
	PinNoInit DCPin{GPIO::A, 6};
} screen_conf;
// end conf/screen_conf.hh

struct Screen {
	Screen(const ScreenConf &conf)
		: spi{ScreenConf::screen_SPI_conf}
		, _ready(true)
	{
		InterruptManager::registerISR(conf.screen_SPI_conf.IRQn, [this]() {
			if (spi.is_end_of_transfer()) {
				spi.clear_EOT_flag();
				spi.clear_TXTF_flag();
				_ready = true;
			}
		});

		spi.configure();

		auto pri = System::encode_nvic_priority(conf.screen_SPI_conf.priority1, conf.screen_SPI_conf.priority2);
		NVIC_SetPriority(conf.screen_SPI_conf.IRQn, pri);
		NVIC_EnableIRQ(conf.screen_SPI_conf.IRQn);

		spi.set_tx_data_size(1);
		spi.enable();
		spi.enable_end_of_xfer_interrupt();
	}

	void init();
	void demo();
	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);

	enum PacketType { DataPacket, CmdPacket };

private:
	SpiPeriph<SpiConfig<ScreenConf::ScreenSPIx>> spi;
	FPin<screen_conf.DCPin.gpio, screen_conf.DCPin.pin> dcpin;
	volatile bool _ready;

	template<PacketType ByteType>
	void write(uint8_t byte)
	{
		while (!_ready) {
		}
		_ready = false;
		if constexpr (ByteType == DataPacket)
			dcpin.low();
		if constexpr (ByteType == CmdPacket)
			dcpin.high();
		spi.load_tx_data(byte);
		spi.start_transfer();
	}

	// void write_cmd(uint8_t cmd)
	// {
	// 	while (!_ready) {
	// 	}
	// 	_ready = false;
	// 	dcpin.low();
	// 	spi.load_tx_data(cmd);
	// 	spi.start_transfer();
	// }
	// void write_data(uint8_t data)
	// {
	// 	while (!_ready) {
	// 	}
	// 	_ready = false;
	// 	dcpin.high();
	// 	spi.load_tx_data(data);
	// 	spi.start_transfer();
	// }
};

