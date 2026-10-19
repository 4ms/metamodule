#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

// PCM3168 on the jack board, connected via J21.
// TDM: single DIN1/DOUT1, shared BCK/LRCK for AD and DA (same as MP1).
//
// !! p1 HARDWARE ISSUE: PE11/PE13/PE14/PE15 (FS/SD_A/MCLK/SCK) are on VDDIO2, which is
// tied to +1V8 on the mp2-devboard. The PCM3168 digital I/O runs at 3.3V, so these four
// MCU outputs are below its VIH. They need 1.8V -> 3.3V level shifting
// (p1: a level-shifter board between J21 and J20).
// SD_B (PB13, codec DOUT -> MCU) is on a 3.3V bank and is fine.

namespace MetaModule
{

// PCM3168 ADR1:ADR0 pins. I2C address = 0x44 + this
#ifdef MP2_TEST_CARRIER
constexpr uint8_t CodecBusAddress = 0b01; // test carrier's PCM3168 module: ADR0 = 3.3V, ADR1 = GND -> 0x45
#else
constexpr uint8_t CodecBusAddress = 0b00; // p1: ADR0 = ADR1 = GND -> 0x44
#endif
constexpr uint8_t CodecAddr7bit = 0x44 + CodecBusAddress;

const mdrivlib::SaiConfig codec_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.mode = mdrivlib::SaiConfig::TXMaster,

	// HPDMA: stream = channel, channel = request (see mdrivlib target/stm32mp2/drivers/sai_tdm.hh)
	.dma_init_tx =
		{
			.DMAx = HPDMA1,
			.stream = HPDMA1_Channel0,
			.channel = HPDMA_REQUEST_SAI1_A,
			.IRQn = HPDMA1_Channel0_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = HPDMA1,
			.stream = HPDMA1_Channel1,
			.channel = HPDMA_REQUEST_SAI1_B,
			.IRQn = HPDMA1_Channel1_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 256, // 32-bit slots * max(num_tdm_outs, num_tdm_ins)
	.samplerate = 48000,

	.MCLK = {mdrivlib::GPIO::E, mdrivlib::PinNum::_14, mdrivlib::PinAF::AltFunc4},
	.SCLK = {mdrivlib::GPIO::E, mdrivlib::PinNum::_15, mdrivlib::PinAF::AltFunc4},
	.LRCLK = {mdrivlib::GPIO::E, mdrivlib::PinNum::_11, mdrivlib::PinAF::AltFunc4},
	.SD_DAC = {mdrivlib::GPIO::E, mdrivlib::PinNum::_13, mdrivlib::PinAF::AltFunc4}, // SD A
	.SD_ADC = {mdrivlib::GPIO::B, mdrivlib::PinNum::_13, mdrivlib::PinAF::AltFunc4}, // SD B

	.reset_pin = {mdrivlib::GPIO::D, mdrivlib::PinNum::_2, mdrivlib::PinAF::AFNone},

	.bus_address = CodecBusAddress,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = mdrivlib::SaiConfig::NoSendSync,
	.sync_receive_from = mdrivlib::SaiConfig::NoReceiveSync,
};

} // namespace MetaModule
