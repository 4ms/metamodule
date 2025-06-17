#pragma once
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "user_settings/audio_settings.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;
using mdrivlib::SaiConfig;

const SaiConfig codec_mainPCB_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.mode = SaiConfig::TXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,
			.channel = DMA_REQUEST_SAI1_A,
			.IRQn = DMA2_Stream1_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream2,
			.channel = DMA_REQUEST_SAI1_B,
			.IRQn = DMA2_Stream2_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 256, //24bit extends to 32bits * max(num_tdm_outs, num_td_ins) = 256
	.samplerate = MetaModule::AudioSettings::DefaultSampleRate,

	.MCLK = {GPIO::Unused}, //not connected
	.SCLK = {GPIO::E, PinNum::_5, PinAF::AltFunc6},
	.LRCLK = {GPIO::E, PinNum::_4, PinAF::AltFunc6},
	.SD_DAC = {GPIO::B, PinNum::_2, PinAF::AltFunc6}, // SD A
	.SD_ADC = {GPIO::F, PinNum::_6, PinAF::AltFunc6}, // SD B

	.reset_pin = {GPIO::Unused},

	.bus_address = 0b00,

	.num_tdm_ins = 2,
	.num_tdm_outs = 2,

	.sync_send = SaiConfig::NoSendSync,
	.sync_receive_from = SaiConfig::NoReceiveSync,
};
