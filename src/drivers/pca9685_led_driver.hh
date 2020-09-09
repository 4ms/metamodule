#pragma once
#include "stm32f7xx.h"

class i2c {
};

enum class LEDDriverError {
	NO_ERR = 0,
	HAL_INIT_ERR = 1,
	I2C_XMIT_TIMEOUT = 2,
	I2C_XMIT_ERR = 3,
	SET_LED_ERR = 4,
	BAD_LED_PARAM = 5,
	DMA_XMIT_ERR = 6,
	IT_XMIT_ERR = 7
};

class PCA9685Driver {
public:
	PCA9685Driver(i2c &bus, uint32_t num_chips)
		: i2c_(bus)
		, num_chips_(num_chips)
	{
	}

	uint8_t get_cur_buf(void);
	uint8_t get_cur_chip(void);

	uint32_t init_dma(uint8_t numdrivers, uint8_t *led_image1, uint8_t *led_image2);
	uint32_t init_direct(uint8_t numdrivers);
	LEDDriverError setRGBLED_RGB(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue);
	LEDDriverError set_single_LED(uint8_t led_element_number, uint16_t brightness);

	uint8_t get_red_led_element_id(uint8_t rgb_led_id);
	uint8_t get_chip_num(uint8_t rgb_led_id);

	void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);

private:
	i2c &i2c_;
	uint32_t num_chips_;
	I2C_HandleTypeDef pwmleddriver_i2c;
	DMA_HandleTypeDef pwmleddriver_dmatx;

	uint8_t cur_chip_num_ = 0;
	uint8_t *leddriver_buffer_start;
	uint8_t *leddriver_buffer;
	LEDDriverError g_led_error;

	LEDDriverError writeregister(uint8_t driverAddr, uint8_t RegisterAddr, uint8_t RegisterValue);
	LEDDriverError reset_chip(uint8_t driverAddr);
	void GPIO_Init(void);
	LEDDriverError I2C_Init(void);
	LEDDriverError I2C_DMA_Init();
	LEDDriverError I2C_IT_Init();
	void tx_complete(DMA_HandleTypeDef *_hdma);
};
