#pragma once
#include <stm32f7xx.h>
#include "debug.h"
extern "C" {
#include "i2c.h"
}
// enum class TouchChan { 
// 	_1 = CS1, 
// 	_2 = CS2, 
// 	_3 = CS3, 
// 	_1_2 = (CS1|CS2), 
// 	_1_3 = (CS1|CS3), 
// 	_2_3 = (CS2|CS3), 
// 	_1_2_3 = (CS1|CS2|CS3), 
// 	_0 = 0,
// };

using BitField = uint8_t;
const BitField kCAP1203Chan1 = 0b001;
const BitField kCAP1203Chan2 = 0b010;
const BitField kCAP1203Chan3 = 0b100;
const uint8_t kCAP1203DefaultAddr = 0x28<<1;
const uint8_t kCAP1203ProductID = 0x6D;

enum class CAP1203_Register
{
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

enum class CAP1203_MainCtl {
	Standby = 0x20,
	Sleep = 0x08,
	Interrupt = 0x01,
};

enum class TouchSensitivity {
	_128x = 0,
	_64x = 1,
	_32x = 2,
	_16x = 3,
	_8x = 4,
	_4x = 5,
	_2x = 6,
	_1x = 7
};

template <class T> 
uint8_t bit(T val) { return(static_cast<uint8_t>(val)); }

class CAP1203 {
public:
	CAP1203(	BitField enabled_channels = (kCAP1203Chan1 | kCAP1203Chan2 | kCAP1203Chan3),
	 			uint16_t addr = kCAP1203DefaultAddr) 
		: addr_(addr),
		  enabled_chan_(enabled_channels)
	{}

	bool begin() 
	{
		uint8_t product_id = read(CAP1203_Register::PROD_ID);
		if (product_id != kCAP1203ProductID) 
			return false; //wrong product ID, cannot begin

	    uint8_t status = read(CAP1203_Register::MAIN_CONTROL);
	    status &= ~bit(CAP1203_MainCtl::Standby);

	    write(CAP1203_Register::MAIN_CONTROL, status);
		write(CAP1203_Register::SENSITIVITY_CONTROL, enabled_chan_);

		//Todo: allow control over averaging and sampling time 
		uint8_t average = 0x30;
		uint8_t sampletime = 0x08;
		uint8_t cycletime = 0x01;
    	write(CAP1203_Register::AVERAGING_AND_SAMPLE_CONFIG, average|sampletime|cycletime); 
    	
    	return true;
    }

	void set_sensitivity(TouchSensitivity sensitivity) {
		// CAP1203_SetSensitivity(static_cast<uint8_t>(sensitivity));
	}
	bool is_pad_touched(uint8_t padnum) {
		if (!((1<<padnum) & enabled_chan_)) return false;

		uint8_t status = read(CAP1203_Register::SENSOR_INPUT_STATUS);
		if (status & (1<<padnum)) {
			clear_interrupt();
			return true;
		} else 
		return false;
	}

	void clear_interrupt()
	{
	    uint8_t reg = read(CAP1203_Register::MAIN_CONTROL);
	    reg &= ~bit(CAP1203_MainCtl::Interrupt);
	    write(CAP1203_Register::MAIN_CONTROL, reg);
	}

private:
	uint16_t const addr_;
	BitField enabled_chan_;


	uint8_t read(CAP1203_Register reg) {
	    uint8_t value;
	    i2c_mem_read(addr_, static_cast<uint16_t>(reg), &value, 1);
	    return value;
	}

	void write(CAP1203_Register reg, uint8_t data) {
		i2c_mem_write(addr_, static_cast<uint16_t>(reg), &data, 1);
	}
};


class TouchCtl {
public:
	TouchCtl() {
		sensor_.begin();
	}

	bool touched(uint8_t padnum) {
		return sensor_.is_pad_touched(padnum);
	}

private:
	CAP1203 sensor_ {kCAP1203Chan1 | kCAP1203Chan3};
};