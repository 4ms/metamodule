#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

using mdrivlib::GPIO;
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
	.framesize = 256,
	.samplerate = 48000,

	.MCLK = {GPIO::E, 0, LL_GPIO_AF_10},
	.SCLK = {GPIO::D, 13, LL_GPIO_AF_10},
	.LRCLK = {GPIO::D, 12, LL_GPIO_AF_10},
	.SD_DAC = {GPIO::D, 11, LL_GPIO_AF_10}, // SD A
	.SD_ADC = {GPIO::G, 10, LL_GPIO_AF_10}, // SD B

	.reset_pin = {GPIO::E, 10, 0},

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

	.MCLK = {GPIO::Unused, 0, 0},
	.SCLK = {GPIO::Unused, 0, 0},
	.LRCLK = {GPIO::Unused, 0, 0},
	.SD_DAC = {GPIO::B, 2, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::F, 6, LL_GPIO_AF_6}, // SD B

	.reset_pin = {GPIO::E, 8},

	.bus_address = 0b01,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = SaiConfig::NoSendSync,
	.sync_receive_from = SaiConfig::SyncToSAI3,
};
