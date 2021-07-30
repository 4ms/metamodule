#pragma once
#include "drivers/codec_PCM3168.hh"
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

using mdrivlib::GPIO;
using mdrivlib::SaiConfig;

using CodecT = mdrivlib::CodecPCM3168;

const SaiConfig codecA_sai_conf = {
	.sai = SAI3,
	.tx_block = SAI3_Block_A,
	.rx_block = SAI3_Block_B,

	.mode = SaiConfig::TXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream3,
			.channel = DMA_REQUEST_SAI3_A,
			.IRQn = DMA2_Stream3_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream4,
			.channel = DMA_REQUEST_SAI3_B,
			.IRQn = DMA2_Stream4_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 256,
	.samplerate = 48000,

	.MCLK = {GPIO::D, 15, LL_GPIO_AF_6},
	.SCLK = {GPIO::D, 0, LL_GPIO_AF_6},
	.LRCLK = {GPIO::D, 4, LL_GPIO_AF_6},
	.SD_DAC = {GPIO::D, 1, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::E, 1, LL_GPIO_AF_6}, // SD B

	.reset_pin = {GPIO::B, 1, 0},

	.bus_address = 0b00,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = SaiConfig::BlockASendsSync,
	.sync_receive_from = SaiConfig::NoReceiveSync,
};

const SaiConfig codecB_sai_conf = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.mode = SaiConfig::ExtSynced,

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
	.framesize = 256,
	.samplerate = 48000,

	.MCLK = {GPIO::E, 2, LL_GPIO_AF_6},	  //not used
	.SCLK = {GPIO::E, 5, LL_GPIO_AF_6},	  //not used
	.LRCLK = {GPIO::G, 15, LL_GPIO_AF_6}, //not used
	.SD_DAC = {GPIO::E, 6, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::E, 3, LL_GPIO_AF_6}, // SD B

	.reset_pin = {GPIO::G, 0, 0},

	.bus_address = 0b01,

	.num_tdm_ins = 6,
	.num_tdm_outs = 8,

	.sync_send = SaiConfig::NoSendSync,
	.sync_receive_from = SaiConfig::SyncToSAI3,
};
