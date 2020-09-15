#ifndef _SRC_DRIVERS_PCA9685_LED_DRIVER
#define _SRC_DRIVERS_PCA9685_LED_DRIVER
#include "dma.hh"
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

//Todo: make PCA9685DriverDMA class, inherits/extends PCA9685Driver by adding DMA functions
class PCA9685Driver {

public:
	PCA9685Driver(I2CPeriph &i2c, uint32_t num_chips);

	LEDDriverError start();
	void start_it_mode();
	LEDDriverError start_dma_mode(uint16_t *led_frame_buf, const DMAConfig dma_defs);
	LEDDriverError set_rgb_led(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue);
	LEDDriverError set_single_led(uint8_t led_element_number, uint16_t brightness);

private:
	I2CPeriph &i2cp_;
	uint32_t num_chips_;
	LEDDriverError g_led_error;

	static uint8_t get_red_led_element_id(uint8_t rgb_led_id);
	static uint8_t get_chip_num(uint8_t rgb_led_id);

	LEDDriverError write_register(uint8_t driverAddr, uint8_t registerAddr, uint8_t registerValue);
	LEDDriverError reset_chip(uint8_t driverAddr);

	struct DMADriver : public DMAMem2Periph, HALCallbackManager::HALCBBase {
		DMADriver(PCA9685Driver &parent)
			: parent_(parent)
		{}
		LEDDriverError start_dma(uint16_t *led_frame_buf, const DMAConfig dma_defs);
		LEDDriverError init_dma(const DMAConfig dmaconf);
		void advance_frame_buffer();
		void write_current_frame_to_chip();
		virtual void isr();
		virtual void halcb();

		PCA9685Driver &parent_;
		uint8_t cur_chip_num_ = 0;
		uint8_t *frame_buffer_start;
		uint8_t *frame_buffer_cur_pos;
	};
	friend class PCA9685Driver::DMADriver;
	DMADriver dma_;

	const int kNumRGBLEDsPerChip = 5;
	const static inline uint32_t REG_MODE1 = 0x00;
	const static inline uint32_t REG_MODE2 = 0x01;
	const static inline uint32_t REG_LED0 = 0x06;
	const static inline uint32_t I2C_BASE_ADDRESS = 0b10000000;
	const static inline auto REGISTER_ADDR_SIZE = I2C_MEMADD_SIZE_8BIT;
};
#endif
