#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

using mdrivlib::GPIO;
using mdrivlib::SaiConfig;

const SaiConfig codec_sai_conf = {
	.sai = SAI3,
	.tx_block = SAI3_Block_A,
	.rx_block = SAI3_Block_B,

	.mode = SaiConfig::TXMaster,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,
			.channel = DMA_REQUEST_SAI3_A,
			.IRQn = DMA2_Stream1_IRQn,
			.pri = 1,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream2,
			.channel = DMA_REQUEST_SAI3_B,
			.IRQn = DMA2_Stream2_IRQn,
			.pri = 1,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::D, 15, LL_GPIO_AF_6},
	.SCLK = {GPIO::D, 0, LL_GPIO_AF_6},
	.LRCLK = {GPIO::D, 4, LL_GPIO_AF_6},
	.SD_DAC = {GPIO::D, 1, LL_GPIO_AF_6}, // SD A
	.SD_ADC = {GPIO::E, 1, LL_GPIO_AF_6}, // SD B

	.reset_pin = {GPIO::A, 1, 0}, //not used

	.bus_address = 0b00,

	.num_tdm_ins = 2,
	.num_tdm_outs = 2,

	.sync_send = SaiConfig::NoSendSync,
	.sync_receive_from = SaiConfig::NoReceiveSync,
};
