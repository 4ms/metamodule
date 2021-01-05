#include "sai.hh"
#include "interrupt.hh"
#include "stm32xx.h"
#include "system.hh"

DMA_HandleTypeDef *SaiPeriph::get_rx_dmahandle()
{
	return &hdma_rx;
}

DMA_HandleTypeDef *SaiPeriph::get_tx_dmahandle()
{
	return &hdma_tx;
}

SaiPeriph::Error SaiPeriph::init()
{
	_init_pins();

	System::enable_sai_rcc(saidef_.sai);
	System::enable_dma_rcc(saidef_.dma_init_rx.DMAx);
	System::enable_dma_rcc(saidef_.dma_init_tx.DMAx);

	{
		_config_rx_sai();
		_config_tx_sai();
		auto err = _init_sai_protocol();
		if (err != SAI_NO_ERR)
			return err;
	}
	{
		_config_rx_dma();
		_config_tx_dma();
		auto err = _init_sai_dma();
		if (err != SAI_NO_ERR)
			return err;
	}

	__HAL_SAI_ENABLE(&hsai_rx);
	__HAL_SAI_ENABLE(&hsai_tx);

	tx_irqn = saidef_.dma_init_tx.IRQn;
	HAL_NVIC_SetPriority(tx_irqn, 1, 0);
	HAL_NVIC_DisableIRQ(tx_irqn);

	rx_irqn = saidef_.dma_init_rx.IRQn;
	HAL_NVIC_SetPriority(rx_irqn, 1, 1);
	HAL_NVIC_DisableIRQ(rx_irqn);

	return SAI_NO_ERR;
}

void SaiPeriph::_config_rx_sai()
{
	__HAL_SAI_RESET_HANDLE_STATE(&hsai_rx);
	hsai_rx.Instance = saidef_.rx_block;
	__HAL_SAI_DISABLE(&hsai_rx);

	hsai_rx.Init.AudioMode = SAI_MODESLAVE_RX;
	hsai_rx.Init.Synchro = SAI_SYNCHRONOUS;
	hsai_rx.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
	hsai_rx.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
	hsai_rx.Init.NoDivider = SAI_MASTERDIVIDER_DISABLE;
	hsai_rx.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
	hsai_rx.Init.AudioFrequency = saidef_.samplerate;
#ifdef STM32H7
	hsai_rx.Init.MckOutput = SAI_MCK_OUTPUT_DISABLE; //todo: also used for MP1
	hsai_rx.Init.MckOverSampling = SAI_MCK_OVERSAMPLING_DISABLE;
	hsai_rx.Init.PdmInit.Activation = DISABLE;
#endif
	hsai_rx.Init.MonoStereoMode = SAI_STEREOMODE;
	hsai_rx.Init.CompandingMode = SAI_NOCOMPANDING;
	hsai_rx.Init.TriState = SAI_OUTPUT_NOTRELEASED;
	HAL_SAI_DeInit(&hsai_rx);
}

void SaiPeriph::_config_tx_sai()
{
	__HAL_SAI_RESET_HANDLE_STATE(&hsai_tx);
	hsai_tx.Instance = saidef_.tx_block;
	__HAL_SAI_DISABLE(&hsai_tx);

	hsai_tx.Init.AudioMode = SAI_MODEMASTER_TX;
	hsai_tx.Init.Synchro = SAI_ASYNCHRONOUS;
	hsai_tx.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
	hsai_tx.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
	hsai_tx.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
	hsai_tx.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
	hsai_tx.Init.AudioFrequency = saidef_.samplerate;
#ifdef STM32H7
	hsai_tx.Init.MckOutput = SAI_MCK_OUTPUT_ENABLE;
	hsai_tx.Init.MckOverSampling = SAI_MCK_OVERSAMPLING_DISABLE;
	hsai_tx.Init.PdmInit.Activation = DISABLE;
#endif
	hsai_tx.Init.MonoStereoMode = SAI_STEREOMODE;
	hsai_tx.Init.CompandingMode = SAI_NOCOMPANDING;
	hsai_tx.Init.TriState = SAI_OUTPUT_NOTRELEASED;
	HAL_SAI_DeInit(&hsai_tx);
}

SaiPeriph::Error SaiPeriph::_init_sai_protocol()
{
	if (HAL_SAI_InitProtocol(&hsai_tx, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_24BIT, 2) != HAL_OK)
		return SAI_INIT_ERR;

	if (HAL_SAI_InitProtocol(&hsai_rx, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_24BIT, 2) != HAL_OK)
		return SAI_INIT_ERR;

	return SAI_NO_ERR;
}

void SaiPeriph::_config_rx_dma()
{
	hdma_rx.Instance = saidef_.dma_init_rx.stream;
#ifdef STM32H7
	hdma_rx.Init.Request = saidef_.dma_init_rx.channel;
#endif
#ifdef STM32F7
	hdma_rx.Init.Channel = saidef_.dma_init_rx.channel;
#endif
	hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma_rx.Init.Mode = DMA_CIRCULAR;
	hdma_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	__HAL_LINKDMA(&hsai_rx, hdmarx, hdma_rx);
	HAL_DMA_DeInit(&hdma_rx);
}

void SaiPeriph::_config_tx_dma()
{
	hdma_tx.Instance = saidef_.dma_init_tx.stream;
#ifdef STM32H7
	hdma_tx.Init.Request = saidef_.dma_init_tx.channel;
#endif
#ifdef STM32F7
	hdma_tx.Init.Channel = saidef_.dma_init_tx.channel;
#endif
	hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma_tx.Init.Mode = DMA_CIRCULAR;
	hdma_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	__HAL_LINKDMA(&hsai_tx, hdmatx, hdma_tx);
	HAL_DMA_DeInit(&hdma_tx);
}

SaiPeriph::Error SaiPeriph::_init_sai_dma()
{
	if (HAL_DMA_Init(&hdma_rx) != HAL_OK)
		return SAI_INIT_ERR;

	if (HAL_DMA_Init(&hdma_tx) != HAL_OK)
		return SAI_INIT_ERR;

	return SAI_NO_ERR;
}

void SaiPeriph::_init_pins()
{
	Pin sai_mclk{saidef_.MCLK.gpio,
				 saidef_.MCLK.pin,
				 PinMode::Alt,
				 saidef_.MCLK.af,
				 PinPull::None,
				 PinPolarity::Normal,
				 PinSpeed::High,
				 PinOType::PushPull};
	Pin sai_sclk{saidef_.SCLK.gpio,
				 saidef_.SCLK.pin,
				 PinMode::Alt,
				 saidef_.SCLK.af,
				 PinPull::None,
				 PinPolarity::Normal,
				 PinSpeed::High,
				 PinOType::PushPull};
	Pin sai_lrclk{saidef_.LRCLK.gpio,
				  saidef_.LRCLK.pin,
				  PinMode::Alt,
				  saidef_.LRCLK.af,
				  PinPull::None,
				  PinPolarity::Normal,
				  PinSpeed::High,
				  PinOType::PushPull};
	Pin sai_mrx_adc{saidef_.SD_ADC.gpio,
					saidef_.SD_ADC.pin,
					PinMode::Alt,
					saidef_.SD_ADC.af,
					PinPull::None,
					PinPolarity::Normal,
					PinSpeed::High,
					PinOType::PushPull};
	Pin sai_mtx_dac{saidef_.SD_DAC.gpio,
					saidef_.SD_DAC.pin,
					PinMode::Alt,
					saidef_.SD_DAC.af,
					PinPull::None,
					PinPolarity::Normal,
					PinSpeed::High,
					PinOType::PushPull};
}

void SaiPeriph::set_txrx_buffers(uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size)
{
	rx_buf_ptr_ = rx_buf_ptr;
	tx_buf_ptr_ = tx_buf_ptr;
	block_size_ = block_size;
}
void SaiPeriph::set_callbacks(std::function<void()> &&tx_complete_cb, std::function<void()> &&tx_half_complete_cb)
{
	tx_tc_cb = std::move(tx_complete_cb);
	tx_ht_cb = std::move(tx_half_complete_cb);
}

void SaiPeriph::start()
{
	dma_tc_flag_index = __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_tx);
	dma_ht_flag_index = __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_tx);
	dma_isr_reg = __HAL_DMA_GET_ISR(saidef_.dma_init_tx.stream);
	dma_ifcr_reg = __HAL_DMA_GET_IFCR(saidef_.dma_init_tx.stream);

	InterruptManager::registerISR(tx_irqn, [this]() {
		if ((*dma_isr_reg & dma_tc_flag_index) && (saidef_.dma_init_tx.stream->CR & DMA_IT_TC)) {
			*dma_ifcr_reg = dma_tc_flag_index;
			tx_tc_cb();
		}

		if ((*dma_isr_reg & dma_ht_flag_index) && (saidef_.dma_init_tx.stream->CR & DMA_IT_HT)) {
			*dma_ifcr_reg = dma_ht_flag_index;
			tx_ht_cb();
		}
	});

	HAL_NVIC_EnableIRQ(tx_irqn);
	HAL_SAI_Receive_DMA(&hsai_rx, rx_buf_ptr_, block_size_);
	HAL_SAI_Transmit_DMA(&hsai_tx, tx_buf_ptr_, block_size_);
}

void SaiPeriph::stop()
{
	HAL_NVIC_DisableIRQ(tx_irqn);
	HAL_NVIC_DisableIRQ(rx_irqn);
}
