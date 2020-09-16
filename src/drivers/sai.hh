#pragma once
#include "defs/codec_sai_defs.hh"
#include "globals.h"
#include "pin.hh"
#include <stdint.h>

//Todo: pass const SaiDef &def to ctor, and have private reference to it
//instead of passing it to all the init/config functions
class SaiPeriph /*: NonCopyable*/ {
public:
	enum Error {
		SAI_NO_ERR,
		SAI_INIT_ERR,
		SAI_I2C_ERR,
		SAI_XMIT_ERR
	};

	SaiPeriph() = default;
	~SaiPeriph() = default;

	Error init(const SaiDef &def);
	void set_txrx_buffers(uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size);
	Error init(const SaiDef &def, uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size)
	{
		set_txrx_buffers(tx_buf_ptr, rx_buf_ptr, block_size);
		return init(def);
	}

	void start();
	void stop();
	DMA_HandleTypeDef *get_tx_dmahandle();
	DMA_HandleTypeDef *get_rx_dmahandle();

private:
	DMA_HandleTypeDef hdma_tx;
	DMA_HandleTypeDef hdma_rx;
	SAI_HandleTypeDef hsai_tx;
	SAI_HandleTypeDef hsai_rx;
	IRQn_Type tx_irqn;
	IRQn_Type rx_irqn;
	uint8_t *tx_buf_ptr_;
	uint8_t *rx_buf_ptr_;
	uint32_t block_size_;
	void _init_pins(const SaiDef &def);

	void _config_rx_sai(const SaiDef &def);
	void _config_tx_sai(const SaiDef &def);
	void _config_rx_dma(const SaiDef &def);
	void _config_tx_dma(const SaiDef &def);
	Error _init_sai_protocol();
	Error _init_sai_dma();
};

