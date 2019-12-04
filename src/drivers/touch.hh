#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "debug.h"
extern "C" {
#include "i2c.h"
}



const uint8_t kCAP1203DefaultAddr = 0x28<<1;
const uint8_t kCAP1203ProductID = 0x6D;


namespace CAP1203 {
using BitField = uint8_t;

enum class Channel : BitField { 
	_1 = 1, 
	_2 = 2, 
	_3 = 4, 
};

//Todo: convert to CamelCase
enum class Register : BitField 
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

enum class MainCtl : BitField {
	Standby = 0x20,
	Sleep = 0x08,
	Interrupt = 0x01,
};

enum class Sensitivity : BitField  {
	_128x = 0<<4,
	_64x = 1<<4,
	_32x = 2<<4,
	_16x = 3<<4,
	_8x = 4<<4,
	_4x = 5<<4,
	_2x = 6<<4,
	_1x = 7<<4,
};

enum class Config  : BitField {
	InterruptOnRelease = (1<<0),
};

//casts an enum class as a bitfield
template <typename Rt=BitField, typename T> 
Rt constexpr const bitfield(T const val) { 
	//assert(sizeof(Rt)>=sizeof(T) || val>>sizeof(Rt) == 0);
	return(static_cast<Rt>(val)); 
}
template<typename... Args>
BitField constexpr const bitfield(const Args... args) { 
	return ( ... | bitfield(args));
}

//returns a BitField with one bit set
template <typename Rt=BitField> 
Rt constexpr const setbit(uint8_t const bitnum) { 
	//assert(val<sizeof(BitField));
	return(static_cast<Rt>(1<<bitnum));
}

};

//   void testbf(){
//   	auto sense16 = bitfield(CAP1203Sensitivity::_16x);
//   	auto sense1 = bitfield(CAP1203Sensitivity::_1x);
//   	auto senseauto_16_1 = bitfield<uint16_t>(CAP1203Sensitivity::_1x);
//   	auto bit5 = setbit(4);
//   	auto bit15 = setbit(15);
//   	auto bitauto_15 = setbit<uint16_t>(15);
//   	uint16_t bit16_15 = setbit<uint16_t>(15);
//		auto chan123_16 = channels(kCAP1203Chan3, kCAP1203Chan1, kCAP1203Chan1);
//   }

//----------------------------

using namespace CAP1203;

class CAP1203Controller {
public:
	//Todo: varidiac parameters for brace initializer? BitField... Chans) : enabled_chan_(Chans...)
	 CAP1203Controller(BitField enabled_channels = bitfield(Channel::_1, Channel::_2, Channel::_3),
	 		 uint16_t addr = kCAP1203DefaultAddr)
		: addr_(addr),
		  enabled_chan_(enabled_channels) {}

	bool begin() 
	{
		auto product_id = read(Register::PROD_ID);
		// if (product_id != kCAP1203ProductID) 
		// 	return false; //wrong product ID, cannot begin
		auto manuf_id = read(Register::MANUFACTURE_ID);

		clear(Register::MAIN_CONTROL, bitfield(MainCtl::Standby));
		
	    uint8_t status = read(Register::MAIN_CONTROL);
	    status &= ~bitfield(MainCtl::Standby);
	    write(Register::MAIN_CONTROL, status);

		write(Register::SENSOR_INPUT_ENABLE, enabled_chan_);

		//Todo: allow control over averaging and sampling time 
		uint8_t average = 0x30;
		uint8_t sampletime = 0x08;
		uint8_t cycletime = 0x01;
    	write(Register::AVERAGING_AND_SAMPLE_CONFIG, average|sampletime|cycletime); 

    	return true;
    }

	void set_sensitivity(Sensitivity sensitivity) {
		auto sensereg = read(Register::SENSITIVITY_CONTROL);
		sensereg |= bitfield(sensitivity);
	    write(Register::SENSITIVITY_CONTROL, sensereg);
	}

	void allow_multiple_simulataneous_pads() {

	} 

	void enable_alert_on_release() {
		set(Register::CONFIG_2, bitfield(Config::InterruptOnRelease));
	}
	void clear_alert_on_release() {
		clear(Register::CONFIG_2, bitfield(Config::InterruptOnRelease));
	}

	bool is_pad_touched(uint8_t padnum) {
		if (!((1<<padnum) & enabled_chan_)) return false;

		auto status = read(Register::SENSOR_INPUT_STATUS);
		if (status & (1<<padnum)) {
			clear_alert();
			return true;
		} else 
		return false;
	}

	void enable_alerts() {
		write(Register::INTERRUPT_ENABLE, enabled_chan_);
	}
	void enable_alerts(BitField channels) {
		set(Register::INTERRUPT_ENABLE, channels);
	}
	void disable_alerts() {
		write(Register::INTERRUPT_ENABLE, 0);
	}
	void disable_alerts(BitField channels) {
		clear(Register::INTERRUPT_ENABLE, channels);
	}
	void clear_alert() {
		clear(Register::MAIN_CONTROL, bitfield(MainCtl::Interrupt));
	}

private:
	uint16_t const addr_;
	BitField enabled_chan_;

	uint8_t read(Register reg) {
	    uint8_t value;
	    i2c_mem_read(addr_, static_cast<uint16_t>(reg), &value, 1);
	    return value;
	}

	void write(Register reg, uint8_t data) {
		i2c_mem_write(addr_, static_cast<uint16_t>(reg), &data, 1);
	}
	void set(Register reg, BitField bits) {
		auto regstate = read(reg);
		regstate |= bits;
		write(reg, regstate);
	}
	void clear(Register reg, BitField bits) {
		auto regstate = read(reg);
		regstate &= ~bits;
		write(reg, regstate);
	}
};

class TouchCtl {
public:
	TouchCtl() {
		sensor_.begin();
		sensor_.set_sensitivity(Sensitivity::_1x);
   		sensor_.enable_alerts();
	}
	bool touched(uint8_t padnum) {
		return sensor_.is_pad_touched(padnum);
	}
	bool alert_received() {
		if (alert_pin_.is_on()) {
			sensor_.clear_alert();
			// if (!alert_state_) {
			// 	alert_state_=true;
				return true;
		// 	}
		// } else {
		// 	alert_state_=false;
		}
		return false;
	}
private:
	PinInverted alert_pin_ {LL_GPIO_PIN_7, GPIOC, PinMode::INPUT};
	bool alert_state_ = false;
	CAP1203Controller sensor_ {bitfield(Channel::_1, Channel::_3)};
};
