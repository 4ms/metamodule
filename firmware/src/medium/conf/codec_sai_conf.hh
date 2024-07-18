#pragma once
#include "audio_settings.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

using mdrivlib::GPIO;
using mdrivlib::PinAF;
using mdrivlib::PinNum;
using mdrivlib::SaiConfig;

const SaiConfig codec_mainPCB_sai_conf = {
	.sai = SAI2,
	.tx_block = SAI2_Block_A,
	.rx_block = SAI2_Block_B,

	.mode = SaiConfig::TXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,
			.channel = DMA_REQUEST_SAI2_A,
			.IRQn = DMA2_Stream1_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream2,
			.channel = DMA_REQUEST_SAI2_B,
			.IRQn = DMA2_Stream2_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 256, //24bit extends to 32bits * max(num_tdm_outs, num_td_ins) = 256
	.samplerate = MetaModule::AudioSettings::DefaultSampleRate,

	.MCLK = {GPIO::E, PinNum::_0, PinAF::AltFunc10},
	.SCLK = {GPIO::D, PinNum::_13, PinAF::AltFunc10},
	.LRCLK = {GPIO::D, PinNum::_12, PinAF::AltFunc10},
	.SD_DAC = {GPIO::D, PinNum::_11, PinAF::AltFunc10}, // SD A
	.SD_ADC = {GPIO::G, PinNum::_10, PinAF::AltFunc10}, // SD B

	.reset_pin = {GPIO::E, PinNum::_10, PinAF::AFNone},

	.bus_address = 0b00,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = SaiConfig::BlockASendsSync,
	.sync_receive_from = SaiConfig::NoReceiveSync,
};

// External header
const SaiConfig codec_ext_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.mode = SaiConfig::ExtSynced,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream4,
			.channel = DMA_REQUEST_SAI1_A,
			.IRQn = DMA2_Stream4_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream6,
			.channel = DMA_REQUEST_SAI1_B,
			.IRQn = DMA2_Stream6_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 256,
	.samplerate = 48000,

	.MCLK = {GPIO::Unused, PinNum::_0, PinAF::AFNone},
	.SCLK = {GPIO::Unused, PinNum::_0, PinAF::AFNone},
	.LRCLK = {GPIO::Unused, PinNum::_0, PinAF::AFNone},
	.SD_DAC = {GPIO::B, PinNum::_2, PinAF::AltFunc6}, // SD A
	.SD_ADC = {GPIO::F, PinNum::_6, PinAF::AltFunc6}, // SD B

	.reset_pin = {GPIO::E, PinNum::_8},

	.bus_address = 0b01,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = SaiConfig::NoSendSync,
	.sync_receive_from = SaiConfig::SyncToSAI3,
};
