#include "interrupt.hh"
#include "pca9685_led_driver.hh"

PCA9685Driver::DMADriver::DMADriver(PCA9685Driver &parent, PCA9685Driver::FrameBuffer &frame_buf)
	: driver_(parent)
	, frame_buffer(frame_buf)
{}

LEDDriverError PCA9685Driver::DMADriver::start_dma(const DMAConfig &dma_defs)
{
	frame_buffer_cur_pos = frame_buffer;

	auto err = init_dma(dma_defs);
	if (err != LEDDriverError::None)
		return err;

	// Link I2C and DMA
	driver_.i2c_periph_.link_DMA_TX(&hal_dma_h_);

	InterruptManager::registerISR(dma_defs.IRQn,
								  [dmah_ptr = &hal_dma_h_]() { HAL_DMA_IRQHandler(dmah_ptr); });

	HAL_NVIC_SetPriority(dma_defs.IRQn, dma_defs.pri, dma_defs.subpri);
	HAL_NVIC_EnableIRQ(dma_defs.IRQn);
	

	write_current_frame_to_chip();

	if (driver_.led_error_ == LEDDriverError::DMA_XMIT_ERR)
		return LEDDriverError::DMA_XMIT_ERR;
	return LEDDriverError::None;
}

LEDDriverError PCA9685Driver::DMADriver::init_dma(const DMAConfig &dma_defs)
{
	System::enable_dma_rcc(dma_defs.DMAx);
	hal_dma_h_.Instance = dma_defs.stream;
	hal_dma_h_.Init.Channel = dma_defs.channel;
	hal_dma_h_.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hal_dma_h_.Init.PeriphInc = DMA_PINC_DISABLE;
	hal_dma_h_.Init.MemInc = DMA_MINC_ENABLE;
	hal_dma_h_.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hal_dma_h_.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hal_dma_h_.Init.Mode = DMA_NORMAL; // DMA_CIRCULAR
	hal_dma_h_.Init.Priority = DMA_PRIORITY_LOW;
	hal_dma_h_.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hal_dma_h_.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hal_dma_h_.Init.MemBurst = DMA_MBURST_SINGLE;
	hal_dma_h_.Init.PeriphBurst = DMA_PBURST_SINGLE;

	HAL_DMA_DeInit(&hal_dma_h_);
	auto hal_err = HAL_DMA_Init(&hal_dma_h_);
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
	uint16_t chip_address = I2C_BASE_ADDRESS | (cur_chip_num_ << 1);
	auto err =
		driver_.i2c_periph_.mem_write_dma(chip_address, REG_LED0, REGISTER_ADDR_SIZE,
										  reinterpret_cast<uint8_t *>(frame_buffer_cur_pos),
										  PCA9685Driver::kNumLedsPerChip * sizeof(frame_buffer[0]));

	if (err != I2CPeriph::Error::I2C_NO_ERR)
		driver_.led_error_ = LEDDriverError::DMA_XMIT_ERR;
}

