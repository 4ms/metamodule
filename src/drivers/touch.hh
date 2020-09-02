#pragma once
#include "cap1203.hh"
#include "circular_buffer.hh"
#include "debug.h"
#include "pin.hh"
#include <stm32f7xx.h>
extern "C" {
#include "i2c.h"
}

template<typename MemAddrT, typename DataT>
struct Message {
	enum class Type { Read,
					  Write,
					  ReadAlterWrite };

	Message() = default;

	Message(Type type, MemAddrT reg, DataT bits = 0)
		: dir(type)
		, address(static_cast<MemAddrT>(reg))
		, data(static_cast<DataT>(bits))
	{
	}

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

using TouchMessage = Message<CAP1203::Register, CAP1203::RegisterContents>;

class TouchCtl {
public:
	TouchCtl()
	{
	}

	void begin()
	{
		i2c_init();
		set_i2c_irq_callback((void (*)(uint8_t))(process_message_completed));
		if (!sensor_.begin()) {
			//panic? reset I2C and retry?
			//...
			return;
		}
		sensor_.set_sensitivity(CAP1203::Sensitivity::_128x);
		sensor_.disable_repeated_alerts();
		sensor_.enable_alerts();
		i2c_enable_IT();
		enabled_ = true;
	}

	bool touched(uint8_t padnum)
	{
		return pressed_[padnum & 1];
	}

	bool just_touched(uint8_t padnum)
	{
		sincePress[padnum & 1] = HAL_GetTick() - lastPress[padnum & 1];
		if (just_pressed_[padnum & 1] && sincePress[padnum & 1] > 15) {
			just_pressed_[padnum & 1] = false;
			lastPress[padnum & 1] = HAL_GetTick();
			return true;
		}
		else
			return false;
	}

	bool just_released(uint8_t padnum)
	{
		if (just_released_[padnum & 1]) {
			just_released_[padnum & 1] = false;
			return true;
		}
		else
			return false;
	}

	bool check_alert_received()
	{
		if (!enabled_)
			return false;

		if (alert_pin_.is_on()) {
			if (!alert_state_) {
				alert_state_ = true;
				// auto t2 = sensor_.is_pad_touched(0);
				//Todo: get the reg/bitfield from CAP1203 class
				messages_.put(TouchMessage{TouchMessage::Type::Read, CAP1203::Register::SENSOR_INPUT_STATUS});
				messages_.put(TouchMessage{TouchMessage::Type::Write, CAP1203::Register::MAIN_CONTROL, 0});
				return true;
			}
		}
		else {
			alert_state_ = false;
		}
		return false;
	}

	//IRQ handler callback
	static void process_message_completed(uint8_t received_data)
	{
		auto &message = messages_.first();
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

	void handle_message_queue()
	{
		if (!enabled_)
			return;

		if (data_received_) {
			auto &message = messages_.first();
			if (message.address == CAP1203::Register::SENSOR_INPUT_STATUS) {
				if (message.data & CAP1203::Chan1) {
					pressed_[0] = true;
					just_pressed_[0] = true;
				}
				if (message.data & CAP1203::Chan3) {
					pressed_[1] = true;
					just_pressed_[1] = true;
				}
			}
			data_received_ = false;
			messages_.remove_first();
		}

		if (!is_xmitting_) {
			if (!messages_.empty()) {
				auto &message = messages_.first();

				if (message.dir == TouchMessage::Type::Write) {
					is_xmitting_ = true;
					sensor_.write_in_bg(message.address, message.data);
				}
				else if (message.dir == TouchMessage::Type::Read) {
					is_xmitting_ = true;
					sensor_.read_in_bg(message.address);
				}
			}
		}
	}

private:
	bool enabled_ = false;
	bool pressed_[2];
	bool just_pressed_[2];
	bool just_released_[2];
	static inline bool is_xmitting_;
	static inline bool data_received_;
	static inline CircularBuffer<TouchMessage, 16> messages_;
	PinL<GPIO::C, 7, PinPolarity::Inverted> alert_pin_{PinMode::Input};
	bool alert_state_ = false;
	CAP1203::Controller sensor_{CAP1203::Chan1 | CAP1203::Chan3};
	unsigned long sincePress[2] = {0, 0};
	unsigned long lastPress[2] = {0, 0};
};
