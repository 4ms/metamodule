#include "i2c.h"
#define _I2C_FLAG_TIMEOUT             ((uint32_t)1)
#define _I2C_LONG_TIMEOUT             ((uint32_t)(300))
#define _I2C_VLONG_TIMEOUT            ((uint32_t)(1000))

void i2c_GPIO_init(void);
enum Codec_Errors codec_I2C_init(void);

I2C_HandleTypeDef i2c_;
uint8_t already_init = 0;

uint32_t i2c_write(uint16_t dev_address, uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef   err;

    while((err = HAL_I2C_Master_Transmit(&i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK)
    {
        if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
            return 2;
    }

	if (err==HAL_OK)
		return 0;
	else
		return 1;
}

uint32_t i2c_mem_write(uint16_t dev_address, uint16_t mem_address, uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef   err;

    while((err = HAL_I2C_Mem_Write(&i2c_, dev_address, mem_address, I2C_MEMADD_SIZE_8BIT, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK)
    {
        if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
            return 2;
    }

	if (err==HAL_OK) 	
		return 0;
	else				
		return 1;
}

uint32_t i2c_read(uint16_t dev_address, uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef   err;

    while((err = HAL_I2C_Master_Receive(&i2c_, dev_address, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK)
    {
        if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
            return 2;
    }

	if (err==HAL_OK) 	
		return 0;
	else				
		return 1;
}

uint32_t i2c_mem_read(uint16_t dev_address, uint16_t mem_address, uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef   err;

    while((err = HAL_I2C_Mem_Read(&i2c_, dev_address, mem_address, I2C_MEMADD_SIZE_8BIT, data, size, _I2C_VLONG_TIMEOUT)) != HAL_OK)
    {
        if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
            return 2;
    }

	if (err==HAL_OK) 	
		return 0;
	else				
		return 1;
}

uint32_t i2c_mem_read_intrpt(uint16_t dev_address, uint16_t mem_address, uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef   err;

    while((err = HAL_I2C_Mem_Read_IT(&i2c_, dev_address, mem_address, I2C_MEMADD_SIZE_8BIT, data, size)) != HAL_OK)
    {
        if (HAL_I2C_GetError(&i2c_) != HAL_I2C_ERROR_AF)
            return 2;
    }
}

void I2Cx_EV_IRQHandler(void) {

}

uint8_t i2c_is_ready(void) {
    return (HAL_I2C_GetState(&i2c_) == HAL_I2C_STATE_READY);
}

void i2c_deinit(void)
{
    I2C_CLK_DISABLE();
}

void i2c_GPIO_init(void)
{
    GPIO_InitTypeDef gpio;

	I2C_GPIO_CLOCK_ENABLE();
	I2C_CLK_ENABLE();

	//I2C pins SDA SCL
	gpio.Mode 		= GPIO_MODE_AF_OD;
	gpio.Pull 		= GPIO_PULLUP;//NOPULL;
	gpio.Speed 		= GPIO_SPEED_FREQ_HIGH;
	gpio.Alternate 	= I2C_GPIO_AF;
	gpio.Pin 		= I2C_SCL_PIN | I2C_SDA_PIN;
	HAL_GPIO_Init(I2C_GPIO, &gpio);
}

enum I2CErrors i2c_init(void)
{
	if (already_init) return I2C_ALREADY_INIT;

	i2c_deinit();

	i2c_GPIO_init();

    i2c_.Instance = I2Cx;

	i2c_.Init.Timing 				= 0x20404768;//0x20445757; //Todo: use set_i2c_timing()
	i2c_.Init.OwnAddress1		 	= 0x33;
	i2c_.Init.AddressingMode 		= I2C_ADDRESSINGMODE_7BIT;
	i2c_.Init.DualAddressMode 	= I2C_DUALADDRESS_DISABLE;
	i2c_.Init.OwnAddress2 		= 0;
	i2c_.Init.OwnAddress2Masks	= I2C_OA2_NOMASK;
	i2c_.Init.GeneralCallMode 	= I2C_GENERALCALL_DISABLE;
	i2c_.Init.NoStretchMode 		= I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&i2c_) != HAL_OK)
		return I2C_INIT_ERR;

  	if (HAL_I2CEx_ConfigAnalogFilter(&i2c_, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
		return I2C_INIT_ERR;

  	if (HAL_I2CEx_ConfigDigitalFilter(&i2c_, 0) != HAL_OK)
		return I2C_INIT_ERR;
	
	already_init = 1;
	return I2C_NO_ERR;
}