#include "dma_config_struct.hh"
#include "pin.hh"
#include "sai_config_struct.hh"
#include "stm32xx.h"

const SaiDef kCodecSAIDef = {
	.sai = SAI1,
	.tx_block = SAI1_Block_A,
	.rx_block = SAI1_Block_B,

	.dma_init_tx = {
		.DMAx = DMA2,
		.stream = DMA2_Stream1,
		.channel = DMA_CHANNEL_0,
		.IRQn = DMA2_Stream1_IRQn,
		.pri = 0,
		.subpri = 1,
	},
	.dma_init_rx = {
		.DMAx = DMA2,
		.stream = DMA2_Stream4,
		.channel = DMA_CHANNEL_1,
		.IRQn = DMA2_Stream4_IRQn,
		.pri = 0,
		.subpri = 1,
	},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK_GPIO = GPIO::E,
	.MCLK_PIN = 2,
	.MCLK_AF = GPIO_AF6_SAI1,

	.SCLK_GPIO = GPIO::E,
	.SCLK_PIN = 5,
	.SCLK_AF = GPIO_AF6_SAI1,

	.LRCLK_GPIO = GPIO::E,
	.LRCLK_PIN = 4,
	.LRCLK_AF = GPIO_AF6_SAI1,

	.MTX_DAC_GPIO = GPIO::E,
	.MTX_DAC_PIN = 6,
	.MTX_DAC_AF = GPIO_AF6_SAI1,

	.MRX_ADC_GPIO = GPIO::E,
	.MRX_ADC_PIN = 3,
	.MRX_ADC_AF = GPIO_AF6_SAI1,
};

