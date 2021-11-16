#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/dma_transfer.hh"
#include "drivers/interrupt.hh"
#include "drivers/spi_dma_datacmd_driver.hh"
#include "drivers/spi_screen_config_struct.hh"
#include "spi_screen_ST77XX.hh"

namespace MetaModule
{
using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinMode;
using mdrivlib::PinNoInit;
using mdrivlib::SpiDataDir;

struct MMScreenConf : mdrivlib::DefaultSpiScreenConf {
	struct ScreenSpiConf : mdrivlib::DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 4; // SPI4
		static constexpr uint16_t NumChips = 1;
		static constexpr IRQn_Type IRQn = SPI4_IRQn;
		static constexpr uint16_t priority1 = 2;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinNoInit SCLK = {GPIO::E, 12, LL_GPIO_AF_5};
		static constexpr PinNoInit COPI = {GPIO::E, 6, LL_GPIO_AF_5}; // p4: PE14
		static constexpr PinNoInit CIPO = {GPIO::A, 0};
		static constexpr PinNoInit CS0 = {GPIO::E, 11, LL_GPIO_AF_5};
		static constexpr bool use_hardware_ss = true;
		static constexpr uint16_t clock_division = 2;
		static constexpr uint16_t data_size = 8;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 1;
		static constexpr bool LSBfirst = false;

		static constexpr bool pulse_hardware_ss = true;
	};

	struct DMAConf : mdrivlib::DefaultDMAConf {
		static constexpr auto DMAx = 1;
		static constexpr auto StreamNum = 3;
		static constexpr auto RequestNum = DMA_REQUEST_SPI4_TX;
		static constexpr auto IRQn = DMA1_Stream3_IRQn;
		static constexpr auto pri = 1;
		static constexpr auto subpri = 1;
		static constexpr auto dir = Mem2Periph;
		static constexpr auto circular = false;
		static constexpr auto transfer_size_mem = HalfWord;
		static constexpr auto transfer_size_periph = HalfWord;
		static constexpr auto dma_priority = Low;
		static constexpr auto mem_inc = true;
		static constexpr auto periph_inc = false;
		static constexpr auto half_transfer_interrupt_enable = false;
		static constexpr auto enable_fifo = true;
		static constexpr auto fifo_threshold = FifoHalfFull;
		static constexpr auto mem_burst = Single;
		static constexpr auto periph_burst = Single;
	};

	using DCPin = FPin<GPIO::H, 5, PinMode::Output>; // p4: PH4

	static constexpr bool IsInverted = false;
	static constexpr uint32_t rowstart = 0;
	static constexpr uint32_t colstart = 0;

	static constexpr uint32_t width = ScreenBufferConf::width;
	static constexpr uint32_t height = ScreenBufferConf::height;
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90; // Todo: set this from ScreenBufferConfT

	using FrameBufferT = std::array<uint16_t, width * height>;

	using HalfFrameBufferT = std::array<uint16_t, width * height / 2>;
	static constexpr uint32_t FrameBytes = sizeof(FrameBufferT);
	static constexpr uint32_t HalfFrameBytes = sizeof(HalfFrameBufferT);
};

using ScreenTransferDriverT = mdrivlib::DMATransfer<typename MMScreenConf::DMAConf>;
} // namespace MetaModule
