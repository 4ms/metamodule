#pragma once
#include <stm32f7xx.h>
extern "C" {
#include "i2c.h"
}
#include "bitfield.hh"

namespace CAP1203 {

const uint8_t kDefaultAddr = 0x28 << 1;
const uint8_t kProductID = 0x6D;

using RegisterContents = uint8_t;

enum Channel : RegisterContents {
	Chan1 = 1,
	Chan2 = 2,
	Chan3 = 4,
};

//Todo: convert to CamelCase
enum class Register : RegisterContents {
	MAIN_CONTROL = 0x00,
	GENERAL_STATUS = 0x02,
	SENSOR_INPUT_STATUS = 0x03,
	NOISE_FLAG_STATUS = 0x0A,
	SENSOR_INPUT_1_DELTA_COUNT = 0x10,
	SENSOR_INPUT_2_DELTA_COUNT = 0X11,
	SENSOR_INPUT_3_DELTA_COUNT = 0X12,
	SENSITIVITY_CONTROL = 0x1F,
	CONFIG = 0x20,
	SENSOR_INPUT_ENABLE = 0x21,
	SENSOR_INPUT_CONFIG = 0x22,
	SENSOR_INPUT_CONFIG_2 = 0x23,
	AVERAGING_AND_SAMPLE_CONFIG = 0x24,
	CALIBRATION_ACTIVATE_AND_STATUS = 0x26,
	INTERRUPT_ENABLE = 0x27,
	REPEAT_RATE_ENABLE = 0x28,
	MULTIPLE_TOUCH_CONFIG = 0x2A,
	MULTIPLE_TOUCH_PATTERN_CONFIG = 0x2B,
	MULTIPLE_TOUCH_PATTERN = 0x2D,
	BASE_COUNT_OUT = 0x2E,
	RECALIBRATION_CONFIG = 0x2F,
	SENSOR_1_INPUT_THRESH = 0x30,
	SENSOR_2_INPUT_THRESH = 0x31,
	SENSOR_3_INPUT_THRESH = 0x32,
	SENSOR_INPUT_NOISE_THRESH = 0x38,
	STANDBY_CHANNEL = 0x40,
	STANDBY_CONFIG = 0x41,
	STANDBY_SENSITIVITY = 0x42,
	STANDBY_THRESH = 0x43,
	CONFIG_2 = 0x44,
	SENSOR_INPUT_1_BASE_COUNT = 0x50,
	SENSOR_INPUT_2_BASE_COUNT = 0x51,
	SENSOR_INPUT_3_BASE_COUNT = 0x52,
	POWER_BUTTON = 0x60,
	POWER_BUTTON_CONFIG = 0x61,
	SENSOR_INPUT_1_CALIBRATION = 0xB1,
	SENSOR_INPUT_2_CALIBRATION = 0xB2,
	SENSOR_INPUT_3_CALIBRATION = 0xB3,
	SENSOR_INPUT_CALIBRATION_LSB_1 = 0xB9,
	PROD_ID = 0xFD,
	MANUFACTURE_ID = 0xFE,
	REVISION = 0xFF,
};

enum class MainCtl : RegisterContents {
	Standby = 0x20,
	Sleep = 0x08,
	Interrupt = 0x01,
};

enum class Sensitivity : RegisterContents {
	_128x = 0 << 4,
	_64x = 1 << 4,
	_32x = 2 << 4,
	_16x = 3 << 4,
	_8x = 4 << 4,
	_4x = 5 << 4,
	_2x = 6 << 4,
	_1x = 7 << 4,
};

enum class Config : RegisterContents {
	InterruptOnRelease = (1 << 0),
};

using RegisterBitField = RegisterContents;
class Controller : BitFieldBase<RegisterBitField> {
public:
	Controller(RegisterBitField enabled_channels = (Chan1 | Chan2 | Chan3),
			   uint16_t addr = kDefaultAddr)
		: addr_(addr)
		, enabled_chan_(enabled_channels)
	{
	}

	bool begin()
	{
		auto product_id = read(Register::PROD_ID);
		if (product_id != kProductID)
			return false; //Todo: handle error wrong product ID, cannot begin

		auto manuf_id = read(Register::MANUFACTURE_ID);

		// clear(Register::MAIN_CONTROL, bitfield(MainCtl::Standby));
		write(Register::MAIN_CONTROL, 0);

		write(Register::SENSOR_INPUT_ENABLE, enabled_chan_);

		//Todo: allow control over averaging and sampling time
		uint8_t average = 0x30;
		uint8_t sampletime = 0x08;
		uint8_t cycletime = 0x01;
		write(Register::AVERAGING_AND_SAMPLE_CONFIG, average | sampletime | cycletime);

		return true;
	}

	void set_sensitivity(Sensitivity sensitivity)
	{
		auto sensereg = read(Register::SENSITIVITY_CONTROL);
		sensereg |= bitfield(sensitivity);
		write(Register::SENSITIVITY_CONTROL, sensereg);
	}

	void allow_multiple_simulataneous_pads()
	{
	}

	void enable_alert_on_release()
	{
		set(Register::CONFIG_2, bitfield(Config::InterruptOnRelease));
	}
	void disable_alert_on_release()
	{
		clear(Register::CONFIG_2, bitfield(Config::InterruptOnRelease));
	}

	bool is_pad_touched(uint8_t padnum)
	{
		if (!((1 << padnum) & enabled_chan_))
			return false;

		auto status = read(Register::SENSOR_INPUT_STATUS);
		clear_alert();

		if (status & (1 << padnum)) {
			return true;
		}
		else
			return false;
	}

	//Enables repeated alerts as long as a pad is pressed
	void enable_repeated_alerts()
	{
		write(Register::REPEAT_RATE_ENABLE, enabled_chan_);
	}
	void enable_repeated_alerts(RegisterBitField channels)
	{
		set(Register::REPEAT_RATE_ENABLE, channels);
	}
	void disable_repeated_alerts()
	{
		write(Register::REPEAT_RATE_ENABLE, 0);
	}
	void disable_repeated_alerts(RegisterBitField channels)
	{
		clear(Register::REPEAT_RATE_ENABLE, channels);
	}

	void enable_alerts()
	{
		write(Register::INTERRUPT_ENABLE, enabled_chan_);
	}
	void enable_alerts(RegisterBitField channels)
	{
		set(Register::INTERRUPT_ENABLE, channels);
	}
	void disable_alerts()
	{
		write(Register::INTERRUPT_ENABLE, 0);
	}
	void disable_alerts(RegisterBitField channels)
	{
		clear(Register::INTERRUPT_ENABLE, channels);
	}
	void clear_alert()
	{
		clear(Register::MAIN_CONTROL, bitfield(MainCtl::Interrupt));
	}

private:
	uint16_t const addr_;
	RegisterBitField enabled_chan_;

public:
	uint8_t read(Register reg)
	{
		uint8_t value;
		i2c_mem_read(addr_, static_cast<uint16_t>(reg), &value, 1);
		return value;
	}
	void read_in_bg(Register reg)
	{
		i2c_mem_read_register_IT(addr_, static_cast<uint16_t>(reg));
	}

	void write(Register reg, RegisterContents data)
	{
		i2c_mem_write(addr_, static_cast<uint16_t>(reg), &data, 1);
	}
	void write_in_bg(Register reg, RegisterContents data)
	{
		i2c_mem_write_register_IT(addr_, static_cast<uint16_t>(reg), static_cast<uint8_t>(data));
	}

	void set(Register reg, RegisterBitField bits)
	{
		auto regstate = read(reg);
		regstate |= bits;
		write(reg, regstate);
	}
	void clear(Register reg, RegisterBitField bits)
	{
		auto regstate = read(reg);
		regstate &= ~bits;
		write(reg, regstate);
	}
};

}; // namespace CAP1203

