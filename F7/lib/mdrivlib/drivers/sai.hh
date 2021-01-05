#pragma once
#include "interrupt.hh"
#include "pin.hh"
#include "sai_config_struct.hh"
#include <cstdint>

class SaiPeriph {
public:
	enum Error {
		SAI_NO_ERR,
		SAI_INIT_ERR,
		SAI_I2C_ERR,
		SAI_XMIT_ERR,
	};

	SaiPeriph(const SaiConfig &def)
		: saidef_(def)
	{}

	~SaiPeriph() = default;

	Error init();
	void set_txrx_buffers(uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size);
	void set_callbacks(std::function<void()> &&tx_complete_cb, std::function<void()> &&tx_half_complete_cb);

	Error init(uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size)
	{
		set_txrx_buffers(tx_buf_ptr, rx_buf_ptr, block_size);
		return init();
	}

	void start();
	void stop();
	DMA_HandleTypeDef *get_tx_dmahandle();
	DMA_HandleTypeDef *get_rx_dmahandle();

private:
	const SaiConfig &saidef_;
	DMA_HandleTypeDef hdma_tx;
	DMA_HandleTypeDef hdma_rx;
	SAI_HandleTypeDef hsai_tx;
	SAI_HandleTypeDef hsai_rx;
	IRQn_Type tx_irqn;
	IRQn_Type rx_irqn;
	uint8_t *tx_buf_ptr_;
	uint8_t *rx_buf_ptr_;
	uint32_t block_size_;

	void _init_pins();
	void _config_rx_sai();
	void _config_tx_sai();
	void _config_rx_dma();
	void _config_tx_dma();
	Error _init_sai_protocol();
	Error _init_sai_dma();

	std::function<void()> tx_tc_cb;
	std::function<void()> tx_ht_cb;

	// Todo: can these be const and assigned in ctor?
	uint32_t dma_tc_flag_index;		 // = __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_tx);
	uint32_t dma_ht_flag_index;		 // = __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_tx);
	volatile uint32_t *dma_isr_reg;	 //= __HAL_DMA_GET_ISR(saidef_.dma_init_tx.stream);
	volatile uint32_t *dma_ifcr_reg; // = __HAL_DMA_GET_IFCR(saidef_.dma_init_tx.stream);
};

