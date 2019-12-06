#pragma once
#include <stm32f7xx.h>
#include "pin.hh"
#include "debug.h"
extern "C" {
#include "i2c.h"
}
#include "util/circular_buffer.hh"

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

//--------------

template <typename MemAddrT, typename DataT>
struct Message {
    enum class Type {Read, Write, ReadAlterWrite};
    Message (Type type=Type::Write, MemAddrT reg=Register::MAIN_CONTROL, DataT bits=bitfield(0)) 
	: dir(type), 
	  address(static_cast<MemAddrT>(reg)), 
	  data(static_cast<DataT>(bits))
	{}

	// Message() 
	// : dir(Type::ReadAlterWrite), 
	//   address(Register::MAIN_CONTROL), 
	//   data(bitfield(0))
	// {}

    Type dir;
    MemAddrT address;
    DataT data;
    DataT bits_to_set;
    DataT bits_to_clear;
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

using TouchMessage = Message<Register, BitField>;

class TouchCtl {
public:
	TouchCtl() {
	}

	void begin() {
		i2c_init();
		i2c_enable_IT();
		set_i2c_irq_callback((void (*)(uint8_t))(process_message_completed));
		sensor_.begin();
		sensor_.set_sensitivity(Sensitivity::_1x);
   		sensor_.enable_alerts();
   	}

	bool touched(uint8_t padnum) {
		return sensor_.is_pad_touched(padnum);
	}

	bool check_alert_received() {
		if (alert_pin_.is_on()) {
			if (!alert_state_) {
				alert_state_=true;
                messages_.put( TouchMessage{TouchMessage::Type::Write, Register::MAIN_CONTROL, bitfield(0)} ); 
                messages_.put( TouchMessage{TouchMessage::Type::Read, Register::SENSOR_INPUT_STATUS} ); 

                // auto bits_to_set = bitfield(0);
                // auto bits_to_clear = bitfield(MainCtl::Interrupt);
                // messages_.put(TouchMessage{TouchMessage::Type::ReadAlterWrite, Register::MAIN_CONTROL, bits_to_set, bits_to_clear}); 

                //Todo: get the reg/bitfield from CAP1203 class
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
        	message.data |= message.bits_to_set;
        	message.data &= ~(message.bits_to_clear);
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
    		if (message.address==Register::SENSOR_INPUT_STATUS) {
    			if (bitfield(message.data) & bitfield(Channel::_1)) {
    				//Save state of pad 1 = touched
    			}
    		}
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
    static inline bool is_xmitting_;
    static inline bool data_received_;
    static inline CircularBuffer<TouchMessage, 16> messages_;
	PinInverted alert_pin_ {LL_GPIO_PIN_7, GPIOC, PinMode::INPUT};
	bool alert_state_ = false;
	CAP1203Controller sensor_ {bitfield(Channel::_1, Channel::_3)};
};
