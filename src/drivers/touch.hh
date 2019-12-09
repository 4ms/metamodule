#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "debug.h"
extern "C" {
#include "i2c.h"
}
#include "util/circular_buffer.hh"

//casts an enum class as a bitfield
template <typename Rt=uint8_t, typename T> 
Rt constexpr const bitfield(T const val) { 
	//assert(sizeof(Rt)>=sizeof(T) || val>>sizeof(Rt) == 0);
	return(static_cast<Rt>(val)); 
}
template<typename... Args>
uint8_t constexpr const bitfield(const Args... args) { 
	return ( ... | bitfield(args));
}

//returns a BitField with one bit set
template <typename Rt=uint8_t> 
Rt constexpr const setbit(uint8_t const bitnum) { 
	//assert(val<sizeof(uint8_t));
	return(static_cast<Rt>(1<<bitnum));
}



namespace CAP1203 {

const uint8_t kDefaultAddr = 0x28<<1;
const uint8_t kProductID = 0x6D;

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

class Controller {
public:
	 Controller(BitField enabled_channels = bitfield(Channel::_1, Channel::_2, Channel::_3),
	 		 uint16_t addr = kDefaultAddr)
		: addr_(addr),
		  enabled_chan_(enabled_channels) {}

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
	void disable_alert_on_release() {
		clear(Register::CONFIG_2, bitfield(Config::InterruptOnRelease));
	}

	bool is_pad_touched(uint8_t padnum) {
		if (!((1<<padnum) & enabled_chan_))
			return false;

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

public:
	uint8_t read(Register reg) {
	    uint8_t value;
	    i2c_mem_read(addr_, static_cast<uint16_t>(reg), &value, 1);
	    return value;
	}
	void read_in_bg(Register reg) {
	    i2c_mem_read_register_IT(addr_, static_cast<uint16_t>(reg));
	}

	void write(Register reg, uint8_t data) {
		i2c_mem_write(addr_, static_cast<uint16_t>(reg), &data, 1);
	}
	void write_in_bg(Register reg, BitField data) {
	    i2c_mem_write_register_IT(addr_, static_cast<uint16_t>(reg), static_cast<uint8_t>(data));
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

};


//--------------

template <typename MemAddrT, typename DataT>
struct Message {
    enum class Type {Read, Write, ReadAlterWrite};

	Message() = default; 

    Message (Type type, MemAddrT reg, DataT bits=0) 
	: dir(type), 
	  address(static_cast<MemAddrT>(reg)), 
	  data(static_cast<DataT>(bits))
	{}

    Type dir;
    MemAddrT address;
    DataT data;
    DataT alter_setbits;
    DataT alter_clearbits;
};

// struct RisingEdgeDetector {
// 	typedef bool check_func_type();

// 	RisingEdgeDetector(check_func_type& check_func) : check_func_(check_func) {}
// 	bool check() {
// 		if (check_func_()) {
// 			if (!last_measured_state_) {
// 				last_measured_state_=true;
// 				return true;
// 			}
// 		} else {
// 			last_measured_state_=false;
// 		}
// 		return false;
// 	}

// 	check_func_type check_func_;
// 	bool last_measured_state_=false;
// };
// using JustActivated = RisingEdgeDetector;

using TouchMessage = Message<CAP1203::Register, CAP1203::BitField>;

class TouchCtl {
public:
	TouchCtl() {
	}

	void begin() {
		i2c_init();
		set_i2c_irq_callback((void (*)(uint8_t))(process_message_completed));
		if (!sensor_.begin()) {
			//panic? reset I2C and retry?
			//...
			return;
		}
		sensor_.set_sensitivity(CAP1203::Sensitivity::_128x);
   		sensor_.enable_alerts();
		i2c_enable_IT();
   	}

	bool touched(uint8_t padnum) {
		return pressed_[padnum & 1];
	}

	bool just_touched(uint8_t padnum) {
		if (just_pressed_[padnum & 1]) {
			just_pressed_[padnum & 1] = false;
			return true;
		} else
			return false;
	}

	bool just_released(uint8_t padnum) {
		if (just_released_[padnum & 1]) {
			just_released_[padnum & 1] = false;
			return true;
		} else
			return false;
	}

	bool check_alert_received() {
		if (alert_pin_.is_on()) {
			if (!alert_state_) {
				alert_state_=true;
                //Todo: get the reg/bitfield from CAP1203 class
                messages_.put( TouchMessage{TouchMessage::Type::Read, CAP1203::Register::SENSOR_INPUT_STATUS} ); 
                messages_.put( TouchMessage{TouchMessage::Type::Write, CAP1203::Register::MAIN_CONTROL, bitfield(0)} ); 
				return true;
			}
		} else {
			alert_state_=false;
		}
		return false;
	}

	//IRQ handler callback
    static void process_message_completed(uint8_t received_data) {
        auto& message = messages_.first();
        if (message.dir == TouchMessage::Type::ReadAlterWrite) {
        	//Convert to a Write message, and keep in queue
        	message.data = received_data;
        	message.data |= message.alter_setbits;
        	message.data &= ~(message.alter_clearbits);
        	message.dir = TouchMessage::Type::Write;
        }
        else if (message.dir == TouchMessage::Type::Read) {
        	message.data = received_data;
        	data_received_ = true;
        }
        else
        	messages_.remove_first();

        is_xmitting_ = false;
    }

    void handle_message_queue() {
    	if (data_received_) {
    		auto& message = messages_.first();
    		if (message.address==CAP1203::Register::SENSOR_INPUT_STATUS) {
    			if (bitfield(message.data) & bitfield(CAP1203::Channel::_1)) {
    				pressed_[0] = true;
    				just_pressed_[0] = true;
    			}
    			if (bitfield(message.data) & bitfield(CAP1203::Channel::_3)) {
    				pressed_[1] = true;
    				just_pressed_[1] = true;
    			}
    		}
    		data_received_ = false;
        	messages_.remove_first();
    	}

    	if (!is_xmitting_) {
	        if (!messages_.empty()) {
	            auto& message = messages_.first();

	            if (message.dir == TouchMessage::Type::Write) {
	                is_xmitting_ = true;
	                sensor_.write_in_bg(message.address, message.data);
	            }
	            else if (message.dir ==TouchMessage::Type::Read) {
	                is_xmitting_ = true;
	                sensor_.read_in_bg(message.address);
	            }
	        }
	    }
    }

private:
	bool pressed_[2];
	bool just_pressed_[2];
	bool just_released_[2];
    static inline bool is_xmitting_;
    static inline bool data_received_;
    static inline CircularBuffer<TouchMessage, 16> messages_;
	PinL<GPIO::C, 7, PinPolarity::INVERTED> alert_pin_ {PinMode::INPUT};
	bool alert_state_ = false;
	CAP1203::Controller sensor_ {bitfield(CAP1203::Channel::_1, CAP1203::Channel::_3)};
};
