#include "dma_config_struct.hh"
#include "pin.hh"
#include "stm32xx.h"

struct SaiDef {
	SAI_TypeDef *sai;
	SAI_Block_TypeDef *tx_block;
	SAI_Block_TypeDef *rx_block;

	DMAConfig dma_init_tx;
	DMAConfig dma_init_rx;

	uint32_t datasize;
	uint32_t framesize;
	uint32_t samplerate;

	GPIO MCLK_GPIO;
	uint8_t MCLK_PIN;
	uint8_t MCLK_AF;

	GPIO SCLK_GPIO;
	uint8_t SCLK_PIN;
	uint8_t SCLK_AF;

	GPIO LRCLK_GPIO;
	uint8_t LRCLK_PIN;
	uint8_t LRCLK_AF;

	GPIO MTX_SDI_GPIO;
	uint8_t MTX_SDI_PIN;
	uint8_t MTX_SDI_AF;

	GPIO MRX_SDO_GPIO;
	uint8_t MRX_SDO_PIN;
	uint8_t MRX_SDO_AF;
};

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

	.MTX_SDI_GPIO = GPIO::E,
	.MTX_SDI_PIN = 6,
	.MTX_SDI_AF = GPIO_AF6_SAI1,

	.MRX_SDO_GPIO = GPIO::E,
	.MRX_SDO_PIN = 3,
	.MRX_SDO_AF = GPIO_AF6_SAI1,
};

