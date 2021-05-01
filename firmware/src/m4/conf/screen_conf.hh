#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/bdma.hh"
#include "drivers/bdma_config_struct.hh"
#include "drivers/interrupt.hh"
#include "drivers/spi_screen_config_struct.hh"
#include "drivers/spi_screen_driver.hh"

struct MMScreenConf : DefaultSpiScreenConf {
	struct ScreenSpiConf : DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 6; // SPI6
		static constexpr uint16_t NumChips = 1;
		static constexpr IRQType IRQn = SPI6_IRQn;
		static constexpr uint16_t priority1 = 2;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::A, 5, LL_GPIO_AF_8};
		static constexpr PinNoInit COPI = {GPIO::A, 7, LL_GPIO_AF_8};
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::A, 4, LL_GPIO_AF_8};
		static constexpr bool use_hardware_ss = true;
		static constexpr uint16_t clock_division = 2;
		static constexpr uint16_t data_size = 8;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;

		static constexpr bool pulse_hardware_ss = true;
	};

	struct BDMAConf : BDMA_Conf {
		static constexpr unsigned StreamNum = 2;
		static constexpr unsigned RequestNum = BDMA_REQUEST_SPI6_TX;
		static constexpr IRQn_Type IRQn = BDMA_Channel2_IRQn;
		static constexpr uint32_t pri = 2;
		static constexpr uint32_t subpri = 2;
		static constexpr Direction dir = Mem2Periph;
		static constexpr bool circular = false;
		static constexpr TransferSize transfer_size_mem = Byte;
		static constexpr TransferSize transfer_size_periph = Byte;
		static constexpr uint8_t dma_priority = Low;
		static constexpr bool mem_inc = true;
		static constexpr bool periph_inc = false;
		static constexpr bool half_transfer_interrupt_enable = false;
	};

	using DCPin = FPin<GPIO::A, 6, PinMode::Output>;

	static constexpr uint32_t rowstart = 80;
	static constexpr uint32_t colstart = 0;

	static constexpr uint32_t width = MMScreenBufferConf::width;
	static constexpr uint32_t height = MMScreenBufferConf::height;
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90; // Todo: set this from ScreenBufferConfT

	using FrameBufferT = MMScreenBufferConf::FrameBufferT;

	using HalfFrameBufferT = std::array<uint16_t, width * height / 2>;
	static constexpr uint32_t FrameBytes = sizeof(FrameBufferT);
	static constexpr uint32_t HalfFrameBytes = sizeof(HalfFrameBufferT);
};

using ScreenTransferDriverT = target::BDMATransfer<typename MMScreenConf::BDMAConf>;
