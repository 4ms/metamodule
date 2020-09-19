#include "dma_config_struct.hh"
#include "pin.hh"
#include "sai_config_struct.hh"
#include "stm32xx.h"

const SaiDef kCodecSAIDef = {
	.sai = SAI2,
	.tx_block = SAI2_Block_B,
	.rx_block = SAI2_Block_A,

	.dma_init_tx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream1,
			.channel = DMA_CHANNEL_10,
			.IRQn = DMA2_Stream1_IRQn,
			.pri = 0,
			.subpri = 1,
		},
	.dma_init_rx =
		{
			.DMAx = DMA2,
			.stream = DMA2_Stream2,
			.channel = DMA_CHANNEL_10,
			.IRQn = DMA2_Stream2_IRQn,
			.pri = 0,
			.subpri = 1,
		},

	.datasize = SAI_DATASIZE_24,
	.framesize = 32,
	.samplerate = 48000,

	.MCLK_GPIO = GPIO::E,
	.MCLK_PIN = 14,
	.MCLK_AF = GPIO_AF10_SAI2,

	.SCLK_GPIO = GPIO::E,
	.SCLK_PIN = 12,
	.SCLK_AF = GPIO_AF10_SAI2,

	.LRCLK_GPIO = GPIO::E,
	.LRCLK_PIN = 13,
	.LRCLK_AF = GPIO_AF10_SAI2,

	.MTX_SDI_GPIO = GPIO::E,
	.MTX_SDI_PIN = 11,
	.MTX_SDI_AF = GPIO_AF10_SAI2,

	.MRX_SDO_GPIO = GPIO::D,
	.MRX_SDO_PIN = 11,
	.MRX_SDO_AF = GPIO_AF10_SAI2,
};

