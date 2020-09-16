#ifndef _SRC_DRIVERS_PCA9685_LED_DRIVER
#define _SRC_DRIVERS_PCA9685_LED_DRIVER

#include "defs/led_driver_defs.hh"
#include "dma_config_struct.hh"
#include "hal_callback.hh"
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

class PCA9685Driver {
public:
	const static int kNumLedsPerChip = 16;
	const static int kNumRGBLEDsPerChip = 5;

public:
	PCA9685Driver(I2CPeriph &i2c, const DMAConfig &dma_defs = LedDriverDmaDef);

	LEDDriverError start();
	void start_it_mode();
	LEDDriverError start_dma_mode(uint32_t *led_frame_buf);
	LEDDriverError set_rgb_led(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue);
	LEDDriverError set_single_led(uint8_t led_element_number, uint16_t brightness);
	uint8_t get_red_led_element_id(uint8_t rgb_led_id);
	uint8_t get_chip_num(uint8_t rgb_led_id);

private:
	I2CPeriph &i2cp_;
	uint32_t num_chips_;
	LEDDriverError led_error_;
	const DMAConfig &dma_defs_;

	LEDDriverError write_register(uint8_t driverAddr, uint8_t registerAddr, uint8_t registerValue);
	LEDDriverError reset_chip(uint8_t driverAddr);

	class DMADriver : public InterruptManager::ISRBase, HALCallbackManager::HALCBBase {
	public:
		DMADriver(PCA9685Driver &parent);
		LEDDriverError start_dma(const DMAConfig &dma_defs);

	private:
		LEDDriverError init_dma(const DMAConfig &dma_defs);
		void advance_frame_buffer();
		void write_current_frame_to_chip();
		virtual void isr();
		virtual void halcb();

		PCA9685Driver &driver_;
		DMA_HandleTypeDef dmah_;
		uint8_t cur_chip_num_ = 0;
		uint32_t *frame_buffer_cur_pos;
		uint32_t frame_buffer[kNumLedDriverChips * PCA9685Driver::kNumLedsPerChip];
	};
	friend class PCA9685Driver::DMADriver;
	DMADriver dma_;

private:
	const static inline uint32_t REG_MODE1 = 0x00;
	const static inline uint32_t REG_MODE2 = 0x01;
	const static inline uint32_t REG_LED0 = 0x06;
	const static inline uint32_t I2C_BASE_ADDRESS = 0b10000000;
	const static inline auto REGISTER_ADDR_SIZE = I2C_MEMADD_SIZE_8BIT;
};
#endif
