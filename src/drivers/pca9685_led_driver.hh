#pragma once
#include "dma.hh"
#include "i2c.hh"
#include "stm32f7xx.h"

enum class LEDDriverError {
	None = 0,
	HAL_INIT_ERR = 1,
	I2C_XMIT_TIMEOUT = 2,
	I2C_XMIT_ERR = 3,
	SET_LED_ERR = 4,
	BAD_LED_PARAM = 5,
	DMA_XMIT_ERR = 6,
	IT_XMIT_ERR = 7
};

//Todo: make PCA9685DriverDMA class, inherits/extends PCA9685Driver by adding DMA functions
class PCA9685Driver {

public:
	PCA9685Driver(i2cPeriph &i2c, uint32_t num_chips);

	LEDDriverError init_as_dma(uint8_t *led_image, DMAConfig dma_defs);
	LEDDriverError init_as_direct();

	LEDDriverError set_rgb_led(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue);
	LEDDriverError set_single_led(uint8_t led_element_number, uint16_t brightness);

	uint8_t get_cur_chip(void);

private:
	i2cPeriph &i2cp_;
	uint32_t num_chips_;
	uint8_t cur_chip_num_ = 0;
	LEDDriverError g_led_error;

	uint8_t *frame_buffer_start;
	uint8_t *frame_buffer_cur_pos;

	uint8_t get_red_led_element_id(uint8_t rgb_led_id);
	uint8_t get_chip_num(uint8_t rgb_led_id);

	void advance_frame_buffer();
	void write_current_frame_to_chip();

	LEDDriverError writeregister(uint8_t driverAddr, uint8_t registerAddr, uint8_t registerValue);
	LEDDriverError reset_chip(uint8_t driverAddr);
	LEDDriverError I2C_Init();
	LEDDriverError I2C_DMA_Init(DMAConfig dma_defs);
	void tx_complete(DMA_HandleTypeDef *_hdma);

	struct I2C_DMA : public DMAMem2Periph {
		I2C_DMA(PCA9685Driver &parent)
			: parent_(parent)
		{
		}
		LEDDriverError init_with_conf(const DMAConfig dmaconf, i2cPeriph &i2c);
		virtual void isr();
		PCA9685Driver &parent_;
	};
	friend class PCA9685Driver::I2C_DMA;
	I2C_DMA dma_;

	const int kNumRGBLEDsPerChip = 5;
	const static inline uint32_t REG_MODE1 = 0x00;
	const static inline uint32_t REG_MODE2 = 0x01;
	const static inline uint32_t REG_LED0 = 0x06;
	const static inline uint32_t I2C_BASE_ADDRESS = 0b10000000;
	const static inline auto REGISTER_ADDR_SIZE = I2C_MEMADD_SIZE_8BIT;
};

