#pragma once
#include "conf/screen_buffer_conf.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/dma_transfer.hh"
#include "drivers/interrupt.hh"
#include "drivers/spi_dma_datacmd_driver.hh"
#include "drivers/spi_screen_config_struct.hh"

namespace MetaModule
{
using mdrivlib::FPin;
using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinDef;
using mdrivlib::PinMode;
using mdrivlib::PinNum;
using mdrivlib::SpiDataDir;

struct MMScreenConf : mdrivlib::DefaultSpiScreenConf {
	struct ScreenSpiConf : mdrivlib::DefaultSpiConf {
		static constexpr uint16_t PeriphNum = 4; // SPI4
		static constexpr uint16_t NumChips = 1;
		static constexpr IRQn_Type IRQn = SPI4_IRQn;
		static constexpr uint16_t priority1 = 2;
		static constexpr uint16_t priority2 = 3;
		static constexpr PinDef SCLK = {GPIO::E, PinNum::_12, PinAF::AltFunc5};
		static constexpr PinDef COPI = {GPIO::E, PinNum::_6, PinAF::AltFunc5};
		static constexpr PinDef CIPO = {GPIO::Unused, PinNum::_0};
		static constexpr PinDef CS0 = {GPIO::E, PinNum::_11, PinAF::AltFunc5};
		static constexpr bool use_hardware_ss = true;
		static constexpr uint16_t clock_division = 4;
		static constexpr uint16_t data_size = 8;
		static constexpr SpiDataDir data_dir = SpiDataDir::TXOnly;
		static constexpr uint8_t FifoThreshold = 2;
		static constexpr bool LSBfirst = false;

		static constexpr bool pulse_hardware_ss = true;
	};

	struct DMAConf : mdrivlib::DefaultDMAConf {
		static constexpr auto DMAx = 1;
		static constexpr auto StreamNum = 3;
		static constexpr auto RequestNum = DMA_REQUEST_SPI4_TX;
		static constexpr auto IRQn = DMA1_Stream3_IRQn;
		static constexpr auto pri = 0;
		static constexpr auto subpri = 0;
		static constexpr auto dir = Mem2Periph;
		static constexpr auto circular = false;
		static constexpr auto periph_flow = false;
		static constexpr auto transfer_size_mem = HalfWord;
		static constexpr auto transfer_size_periph = HalfWord;
		static constexpr auto dma_priority = High;
		static constexpr auto mem_inc = true;
		static constexpr auto periph_inc = false;
		static constexpr auto half_transfer_interrupt_enable = false;
		static constexpr auto enable_fifo = true;
		static constexpr auto fifo_threshold = FifoHalfFull;
		static constexpr auto mem_burst = Single;
		static constexpr auto periph_burst = Single;
	};

	using DCPin = FPin<GPIO::B, PinNum::_7, PinMode::Output>;
	// static constexpr PinDef ResetPin{GPIO::B, PinNum::_12}; //p10 jumper
	static constexpr PinDef ResetPin{GPIO::C, PinNum::_4}; //p11
	//p9c:PE8 using wire to short EX_CODEC_RST to reset pin on screen connector

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
