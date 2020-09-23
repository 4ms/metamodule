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

	GPIO MTX_DAC_GPIO;
	uint8_t MTX_DAC_PIN;
	uint8_t MTX_DAC_AF;

	GPIO MRX_ADC_GPIO;
	uint8_t MRX_ADC_PIN;
	uint8_t MRX_ADC_AF;
};

