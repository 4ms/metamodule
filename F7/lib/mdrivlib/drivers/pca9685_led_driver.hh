#pragma once

#include "conf/led_driver_conf.hh"
#include "dma_config_struct.hh"
#include "hal_callback.hh"
#include "i2c.hh"
#include "led_driver.hh"
#include "stm32f7xx.h"

class PCA9685Driver : public ILedDmaDriver {
public:
	const static int kNumLedsPerChip = 16;
	const static int kNumRGBLEDsPerChip = 5;
	const static size_t kRequiredBufferSize = kNumLedDriverChips * PCA9685Driver::kNumLedsPerChip;

	using FrameBuffer = uint32_t[kRequiredBufferSize];

public:
	PCA9685Driver(I2CPeriph &i2c, uint32_t num_chips, const DMAConfig &dma_defs, FrameBuffer& frame_buf);

	virtual LEDDriverError start();
	virtual void start_it_mode();
	virtual LEDDriverError start_dma_mode();
	virtual uint32_t *const get_buf_addr(const uint32_t chip_num, const uint32_t led_num);

	LEDDriverError set_rgb_led(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue);
	LEDDriverError set_single_led(uint8_t led_element_number, uint16_t brightness);
	uint8_t get_red_led_element_id(uint8_t rgb_led_id);
	uint8_t get_chip_num(uint8_t rgb_led_id);

private:
	I2CPeriph &i2c_periph_;
	uint32_t num_chips_;
	LEDDriverError led_error_;
	const DMAConfig &dma_defs_;

	LEDDriverError write_register(uint8_t driverAddr, uint8_t registerAddr, uint8_t registerValue);
	LEDDriverError reset_chip(uint8_t driverAddr);

	class DMADriver {
		friend class PCA9685Driver;

	public:
		DMADriver(PCA9685Driver &parent, FrameBuffer &frame_buf);
		LEDDriverError start_dma(const DMAConfig &dma_defs);

	private:
		LEDDriverError init_dma(const DMAConfig &dma_defs);
		void advance_frame_buffer();
		void write_current_frame_to_chip();

		PCA9685Driver &driver_;
		DMA_HandleTypeDef hal_dma_h_;
		Interrupt dma_task;
		uint8_t cur_chip_num_ = 0;
		uint32_t *frame_buffer_cur_pos;
		uint32_t (&frame_buffer)[kRequiredBufferSize];

		HALCallback transfer_complete{HALCallbackID::I2C_MemTxCplt, [this]() {
										  advance_frame_buffer();
										  write_current_frame_to_chip();
									  }};
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
