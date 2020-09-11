#include "i2c.hh"
#include "interrupt.hh"
#include "stm32f7xx.h"
#include "system.hh"

const uint32_t _I2C_FLAG_TIMEOUT = 1;
const uint32_t _I2C_LONG_TIMEOUT = 30;
const uint32_t _I2C_VLONG_TIMEOUT = 100;

i2cPeriph::Error i2cPeriph::read(uint16_t dev_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Master_Receive(&i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

i2cPeriph::Error i2cPeriph::write(uint16_t dev_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Master_Transmit(&i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

i2cPeriph::Error i2cPeriph::mem_read(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Read(&i2c_, dev_address, mem_address, memadd_size, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

i2cPeriph::Error i2cPeriph::mem_write(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Write(&i2c_, dev_address, mem_address, memadd_size, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK) {
		if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

i2cPeriph::Error i2cPeriph::mem_write_dma(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef err;
	while ((err = HAL_I2C_Mem_Write_DMA(&i2c_, dev_address, mem_address, memadd_size, data, size)) != HAL_OK) {
		if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
			return I2C_XMIT_ERR;
	}
	return err == HAL_OK ? I2C_NO_ERR : I2C_XMIT_ERR;
}

bool i2cPeriph::is_ready()
{
	return (HAL_I2C_GetState(&i2c_) == HAL_I2C_STATE_READY);
}

void i2cPeriph::deinit(I2C_TypeDef *periph)
{
	System::disable_i2c_rcc(periph);
}

i2cPeriph::Error i2cPeriph::init(I2C_TypeDef *periph)
{
	//0x307075B1
	//0x20448787
	i2cTimingReg t = {.PRESC = 0x50, .SCLDEL_SDADEL = 0x70, .SCLH = 0x75, .SCLL = 0xB1};
	return init(periph, t);
}

i2cPeriph::Error i2cPeriph::init(I2C_TypeDef *periph, const i2cTimingReg &timing)
{
	if (already_init) return I2C_ALREADY_INIT;

	deinit(periph);

	System::enable_i2c_rcc(periph);

	i2c_.Instance = periph;
	i2c_.Init.Timing = timing.calc();
	i2c_.Init.OwnAddress1 = 0x33;
	i2c_.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c_.Init.OwnAddress2 = 0;
	i2c_.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	i2c_.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c_.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	HAL_I2C_DeInit(&i2c_);
	if (HAL_I2C_Init(&i2c_) != HAL_OK)
		return I2C_INIT_ERR;

	// if (HAL_I2CEx_ConfigAnalogFilter(&i2c_, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	// 	return I2C_INIT_ERR;

	// if (HAL_I2CEx_ConfigDigitalFilter(&i2c_, 0) != HAL_OK)
	// 	return I2C_INIT_ERR;

	already_init = true;
	return I2C_NO_ERR;
}

void i2cPeriph::enable_IT(uint8_t pri1, uint8_t pri2)
{
	if (i2c_.Instance == I2C1) {
		Interrupts::I2C::I2C1_handle = &i2c_;
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	}
	if (i2c_.Instance == I2C2) {
		Interrupts::I2C::I2C2_handle = &i2c_;
		HAL_NVIC_SetPriority(I2C2_ER_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
		HAL_NVIC_SetPriority(I2C2_EV_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
	}
	if (i2c_.Instance == I2C3) {
		Interrupts::I2C::I2C3_handle = &i2c_;
		HAL_NVIC_SetPriority(I2C3_ER_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
		HAL_NVIC_SetPriority(I2C3_EV_IRQn, pri1, pri2);
		HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
	}
}

void i2cPeriph::disable_IT()
{
	if (i2c_.Instance == I2C1) {
		Interrupts::I2C::I2C1_handle = nullptr;
		HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
	}
	if (i2c_.Instance == I2C2) {
		Interrupts::I2C::I2C2_handle = nullptr;
		HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
	}
	if (i2c_.Instance == I2C3) {
		Interrupts::I2C::I2C3_handle = nullptr;
		HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
	}
}

void i2cPeriph::link_DMA_TX(DMA_HandleTypeDef *dmatx)
{
	__HAL_LINKDMA(&i2c_, hdmatx, *dmatx);
}

void i2cPeriph::link_DMA_RX(DMA_HandleTypeDef *dmarx)
{
	__HAL_LINKDMA(&i2c_, hdmarx, *dmarx);
}

