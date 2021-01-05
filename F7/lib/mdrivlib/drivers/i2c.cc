#include "i2c.hh"
#include "interrupt.hh"
#include "stm32xx.h"
#include "system.hh"

const uint32_t _I2C_FLAG_TIMEOUT = 1;
const uint32_t _I2C_LONG_TIMEOUT = 30;
const uint32_t _I2C_VLONG_TIMEOUT = 100;

I2CPeriph::Error I2CPeriph::read(uint16_t dev_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Master_Receive(&hal_i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

I2CPeriph::Error I2CPeriph::write(uint16_t dev_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Master_Transmit(&hal_i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

I2CPeriph::Error
I2CPeriph::mem_read(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Read(&hal_i2c_, dev_address, mem_address, memadd_size, data, size, _I2C_VLONG_TIMEOUT)) !=
		   HAL_OK)
	{
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

I2CPeriph::Error
I2CPeriph::mem_write(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Write(
				&hal_i2c_, dev_address, mem_address, memadd_size, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK)
	{
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

I2CPeriph::Error
I2CPeriph::mem_write_IT(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Write_IT(&hal_i2c_, dev_address, mem_address, memadd_size, data, size)) != HAL_OK) {
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

I2CPeriph::Error
I2CPeriph::mem_write_dma(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Write_DMA(&hal_i2c_, dev_address, mem_address, memadd_size, data, size)) != HAL_OK) {
		if (HAL_I2C_GetError(&hal_i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

bool I2CPeriph::is_ready()
{
	return (HAL_I2C_GetState(&hal_i2c_) == HAL_I2C_STATE_READY);
}

void I2CPeriph::deinit(I2C_TypeDef *periph)
{
	System::disable_i2c_rcc(periph);
}

I2CPeriph::Error I2CPeriph::init(I2C_TypeDef *periph)
{
	const I2CTimingConfig t = {.PRESC = 0x50, .SCLDEL_SDADEL = 0x70, .SCLH = 0x75, .SCLL = 0xB1};
	return init(periph, t);
}

I2CPeriph::Error I2CPeriph::init(I2C_TypeDef *periph, const I2CTimingConfig &timing)
{
	if (already_init)
		return I2C_ALREADY_INIT;

	deinit(periph);

	System::enable_i2c_rcc(periph);

	hal_i2c_.Instance = periph;
	hal_i2c_.Init.Timing = timing.calc();
	hal_i2c_.Init.OwnAddress1 = 0x33;
	hal_i2c_.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hal_i2c_.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hal_i2c_.Init.OwnAddress2 = 0;
	hal_i2c_.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hal_i2c_.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hal_i2c_.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (hal_i2c_.Instance == I2C1) {
		i2c_irq_num_ = I2C1_EV_IRQn;
		i2c_err_irq_num_ = I2C1_ER_IRQn;
	} else if (hal_i2c_.Instance == I2C2) {
		i2c_irq_num_ = I2C2_EV_IRQn;
		i2c_err_irq_num_ = I2C2_ER_IRQn;
	} else if (hal_i2c_.Instance == I2C3) {
		i2c_irq_num_ = I2C3_EV_IRQn;
		i2c_err_irq_num_ = I2C3_ER_IRQn;
	}

	HAL_I2C_DeInit(&hal_i2c_);
	if (HAL_I2C_Init(&hal_i2c_) != HAL_OK)
		return I2C_INIT_ERR;

	// if (HAL_I2CEx_ConfigAnalogFilter(&i2c_, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	// 	return I2C_INIT_ERR;

	// if (HAL_I2CEx_ConfigDigitalFilter(&i2c_, 0) != HAL_OK)
	// 	return I2C_INIT_ERR;

	already_init = true;
	return I2C_NO_ERR;
}

void I2CPeriph::enable_IT(uint8_t pri1, uint8_t pri2)
{
	event_isr.registerISR(i2c_irq_num_, [this]() { i2c_event_handler(); });
	HAL_NVIC_SetPriority(i2c_irq_num_, pri1, pri2);
	HAL_NVIC_EnableIRQ(i2c_irq_num_);

	error_isr.registerISR(i2c_err_irq_num_, [this]() { i2c_error_handler(); });
	HAL_NVIC_SetPriority(i2c_err_irq_num_, pri1, pri2);
	HAL_NVIC_EnableIRQ(i2c_err_irq_num_);
}

void I2CPeriph::disable_IT()
{
	HAL_NVIC_DisableIRQ(i2c_irq_num_);
	HAL_NVIC_DisableIRQ(i2c_err_irq_num_);
}

void I2CPeriph::i2c_event_handler()
{
	HAL_I2C_EV_IRQHandler(&hal_i2c_);
}

void I2CPeriph::i2c_error_handler()
{
	HAL_I2C_ER_IRQHandler(&hal_i2c_);
}

void I2CPeriph::link_DMA_TX(DMA_HandleTypeDef *dmatx)
{
	__HAL_LINKDMA(&hal_i2c_, hdmatx, *dmatx);
}

void I2CPeriph::link_DMA_RX(DMA_HandleTypeDef *dmarx)
{
	__HAL_LINKDMA(&hal_i2c_, hdmarx, *dmarx);
}

