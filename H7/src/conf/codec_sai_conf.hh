#pragma once
#include "drivers/dma_config_struct.hh"
#include "drivers/pin.hh"
#include "drivers/sai_config_struct.hh"
#include "drivers/stm32xx.h"

const SaiConfig codec_sai_conf = {
	.sai = SAI4,
	.tx_block = SAI4_Block_A,
	.rx_block = SAI4_Block_B,

	.dma_init_tx =
		{
			.stream = BDMA_Channel0,
			.request = BDMA_REQUEST_SAI4_A,
			.IRQn = BDMA_Channel0_IRQn,
			.pri = 1,
			.subpri = 0,
		},
	.dma_init_rx =
		{
			.stream = BDMA_Channel1,
			.request = BDMA_REQUEST_SAI4_A,
			.IRQn = BDMA_Channel1_IRQn,
			.pri = 1,
			.subpri = 0,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK = {GPIO::E, 2, GPIO_AF8_SAI4},
	.SCLK = {GPIO::E, 5, GPIO_AF8_SAI4},
	.LRCLK = {GPIO::E, 4, GPIO_AF8_SAI4},
	.SD_DAC = {GPIO::E, 6, GPIO_AF8_SAI4},
	.SD_ADC = {GPIO::E, 3, GPIO_AF8_SAI4},
};
