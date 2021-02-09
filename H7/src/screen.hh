#pragma once
// #include "Adafruit_ST7789.h"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/spi_config_struct.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

// drivers/spi_screen_config_struct.hh
struct DefaultSpiScreenConf {
	static constexpr unsigned ScreenSPIx = 0;
	static constexpr SpiConfig<ScreenSPIx> screen_SPI_conf{
		.IRQn = HardFault_IRQn,
		.priority1 = 3,
		.priority2 = 3,

		.SCLK = {},
		.COPI = {},
		.CIPO = {},
		.CS = {{}},

		.use_hardware_ss = true,
		.clock_division = 8,
		.data_size = 8,
		.data_dir = SpiDataDir::TXOnly,
	};
	using DCPin = FPin<GPIO::A, 0>;
	// static constexpr PinNoInit DCPin{};
};

//////////
// conf/screen_conf.hh
constexpr struct ScreenConf : DefaultSpiScreenConf {
	static constexpr unsigned ScreenSPIx = 6;
	static constexpr SpiConfig<ScreenSPIx> screen_SPI_conf = {
		.IRQn = SPI6_IRQn,
		.priority1 = 2,
		.priority2 = 3,

		.SCLK = {GPIO::A, 5, LL_GPIO_AF_8}, // A4 on H745 pcb
		.COPI = {GPIO::A, 7, LL_GPIO_AF_8},
		.CIPO = {GPIO::A, 0}, // unused pin
		.CS =
			{
				{GPIO::A, 4, LL_GPIO_AF_8}, // A5 on H745 pcb
			},

		.use_hardware_ss = true,
		.clock_division = 8,
		.data_size = 8,
		.data_dir = SpiDataDir::TXOnly,
	};
	using DCPin = FPin<GPIO::A, 6>;
} screen_conf;
///////// end conf/screen_conf.hh

///////////
// driver/screen_driver.hh
template<typename ConfT, typename DCPinT>
struct SpiScreenDriver {
	SpiScreenDriver(const ConfT &conf)
		: spi{ScreenConf::screen_SPI_conf}
		, _ready(true)
	{
		InterruptManager::registerISR(conf.IRQn, [this]() {
			if (spi.is_end_of_transfer()) {
				spi.clear_EOT_flag();
				spi.clear_TXTF_flag();
				_ready = true;
			}
		});

		spi.configure();
		auto pri = System::encode_nvic_priority(conf.priority1, conf.priority2);
		NVIC_SetPriority(conf.IRQn, pri);
		NVIC_EnableIRQ(conf.IRQn);

		spi.set_tx_data_size(1);
		spi.enable();
		spi.enable_end_of_xfer_interrupt();
	}

private:
	SpiPeriph<ConfT> spi;
	DCPinT dcpin;
	volatile bool _ready;

protected:
	enum PacketType { Cmd, Data };

	template<PacketType ByteType>
	void write(uint8_t byte)
	{
		while (!_ready) {
		}
		_ready = false;
		if constexpr (ByteType == Cmd)
			dcpin.low();
		if constexpr (ByteType == Data)
			dcpin.high();
		spi.load_tx_data(byte);
		spi.start_transfer();
	}
};
//////////////

/////////
// screen.hh
struct Screen : public SpiScreenDriver<SpiConfig<ScreenConf::ScreenSPIx>, ScreenConf::DCPin> {
	Screen(const ScreenConf &conf)
		: SpiScreenDriver<SpiConfig<ScreenConf::ScreenSPIx>, ScreenConf::DCPin>{conf.screen_SPI_conf}
	{}

	void init();
	void demo();
	void set_rotation(uint8_t m);

private:
	int window_width;
	int window_height;
	int rotation;
	int _xstart;
	int _ystart;
	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
	void init_display(const uint8_t *addr);
};

