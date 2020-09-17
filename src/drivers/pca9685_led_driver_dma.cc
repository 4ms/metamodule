#include "interrupt.hh"
#include "pca9685_led_driver.hh"

PCA9685Driver::DMADriver::DMADriver(PCA9685Driver &parent)
	: driver_(parent)
{}

LEDDriverError PCA9685Driver::DMADriver::start_dma(const DMAConfig &dma_defs)
{
	frame_buffer_cur_pos = frame_buffer;

	auto err = init_dma(dma_defs);
	if (err != LEDDriverError::None)
		return err;

	//Link I2C and DMA
	driver_.i2cp_.link_DMA_TX(&dmah_);

	dma_task.registerISR(dma_defs.IRQn, [dmah_ptr = &dmah_]() { HAL_DMA_IRQHandler(dmah_ptr); });
	HAL_NVIC_SetPriority(dma_defs.IRQn, dma_defs.pri, dma_defs.subpri);
	HAL_NVIC_EnableIRQ(dma_defs.IRQn);

	HALCallbackManager::registerHALCB(HALCallbackID::I2C_MemTxCplt, this);

	write_current_frame_to_chip();

	if (driver_.led_error_ == LEDDriverError::DMA_XMIT_ERR)
		return LEDDriverError::DMA_XMIT_ERR;
	return LEDDriverError::None;
}

LEDDriverError PCA9685Driver::DMADriver::init_dma(const DMAConfig &dma_defs)
{
	dmah_.Instance = dma_defs.stream;
	dmah_.Init.Channel = dma_defs.channel;
	dmah_.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dmah_.Init.PeriphInc = DMA_PINC_DISABLE;
	dmah_.Init.MemInc = DMA_MINC_ENABLE;
	dmah_.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dmah_.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dmah_.Init.Mode = DMA_NORMAL; //DMA_CIRCULAR
	dmah_.Init.Priority = DMA_PRIORITY_LOW;
	dmah_.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	dmah_.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	dmah_.Init.MemBurst = DMA_MBURST_SINGLE;
	dmah_.Init.PeriphBurst = DMA_PBURST_SINGLE;

	HAL_DMA_DeInit(&dmah_);
	auto hal_err = HAL_DMA_Init(&dmah_);
	if (hal_err != HAL_OK)
		return LEDDriverError::DMA_XMIT_ERR;

	return LEDDriverError::None;
}

void PCA9685Driver::DMADriver::advance_frame_buffer()
{
	if (++cur_chip_num_ >= driver_.num_chips_)
		cur_chip_num_ = 0;

	uint32_t start_of_cur_chip = cur_chip_num_ * PCA9685Driver::kNumLedsPerChip;
	frame_buffer_cur_pos = &(frame_buffer[start_of_cur_chip]);
}

void PCA9685Driver::DMADriver::write_current_frame_to_chip()
{
	auto err = driver_.i2cp_.mem_write_dma(
		I2C_BASE_ADDRESS,
		REG_LED0,
		REGISTER_ADDR_SIZE,
		reinterpret_cast<uint8_t *>(frame_buffer_cur_pos),
		PCA9685Driver::kNumLedsPerChip * sizeof(frame_buffer[0]));

	if (err != I2CPeriph::Error::I2C_NO_ERR)
		driver_.led_error_ = LEDDriverError::DMA_XMIT_ERR;
}

void PCA9685Driver::DMADriver::halcb()
{
	advance_frame_buffer();
	write_current_frame_to_chip();
}

