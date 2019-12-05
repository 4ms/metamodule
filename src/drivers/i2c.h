#pragma once
#include <stm32f7xx.h>


// I2C Config
//
#define I2Cx						 I2C2
#define I2C_CLK_ENABLE			     __HAL_RCC_I2C2_CLK_ENABLE
#define I2C_CLK_DISABLE		         __HAL_RCC_I2C2_CLK_DISABLE
#define I2C_GPIO_CLOCK_ENABLE	     __HAL_RCC_GPIOB_CLK_ENABLE
#define I2C_GPIO_AF				     GPIO_AF4_I2C2
#define I2C_GPIO					 GPIOB
#define I2C_SCL_PIN				     GPIO_PIN_10
#define I2C_SDA_PIN				     GPIO_PIN_11

#define I2Cx_EV_IRQHandler      I2C2_EV_IRQHandler


enum I2CErrors {
	I2C_NO_ERR,
	I2C_INIT_ERR,
	I2C_ALREADY_INIT
};

uint32_t i2c_mem_read(uint16_t dev_address, uint16_t mem_address, uint8_t *data, uint16_t size);
uint32_t i2c_mem_write(uint16_t dev_address, uint16_t mem_address, uint8_t *data, uint16_t size);
uint32_t i2c_read(uint16_t dev_address, uint8_t *data, uint16_t size);
uint32_t i2c_write(uint16_t address, uint8_t *data, uint16_t size);
void i2c_deinit(void);
enum I2CErrors i2c_init(void);
