#pragma once
#include "conf/board_conf.hh"
#include "drivers/pin_change.hh"
#include "pcb_detect.hh"
#include "ping_methods.hh"

namespace LDKit
{

class Timer {
	Board::PingJack ping_jack;
	mdrivlib::PinChangeInt<Brain::LRClkPinChangeConf> pin_change;
	Board::ClkOut clk_out;
	Board::BusClkOut bus_clk_out;
	Board::LoopLED loop_led;

	Board::LoopClkBuilt loop_out_built;
	Board::LoopClkKit loop_out_kit;

	uint32_t _ping_tmr = 0;
	uint32_t _ping_time = 12000;
	bool _ping_changed = true;
	uint32_t _pingled_tmr = 0;
	float _loop_tmr = 0;
	float _loop_time = 0;
	bool _ping_led_high = false;
	bool _ping_cycled = false;
	bool _ping_tmr_needs_reset = false;
	PingMethod &_ping_method;

	bool is_kit = false;

public:
	Timer(PingMethod &ping_method)
		: _ping_method{ping_method} {
		pin_change.init([this] { inc(); });
		is_kit = PCBDetect::is_kit();
	}

	void start() {
		pin_change.start();
	}

	void inc() {
		if (_ping_tmr_needs_reset) {
			_ping_tmr_needs_reset = false;
			_ping_tmr = 0;
			clk_out.high();
			bus_clk_out.high();
		} else
			_ping_tmr++;

		_pingled_tmr++;
		_loop_tmr++;

		ping_jack.update();
		if (ping_jack.just_went_high()) {
			// TODO: if ping_method != last_ping_method PingMethodAlgorithm::reset();
			auto newtime = PingMethodAlgorithm::filter(_ping_time, _ping_tmr, _ping_method);
			if (newtime.has_value()) {
				_ping_time = newtime.value();
				_pingled_tmr = 0;

				_ping_changed = true;
				clk_out.high();
				bus_clk_out.high();
			}
			_ping_tmr = 0;
		}

		if (_pingled_tmr >= _ping_time) {
			_pingled_tmr = 0;
			_ping_led_high = true;
			_ping_cycled = true;
			clk_out.high();
			bus_clk_out.high();
		} else if (_pingled_tmr >= (_ping_time / 2)) {
			_ping_led_high = false;
			clk_out.low();
			bus_clk_out.low();
		}

		if (_loop_tmr >= _loop_time) {
			reset_loop_tmr(_loop_tmr - _loop_time);
		} else if (_loop_tmr >= (_loop_time / 2)) {
			loop_led.low();
			is_kit ? loop_out_kit.low() : loop_out_built.low();
		}
	}

	void set_divmult_time(float time) {
		_loop_time = time;
	}

	bool take_ping_changed() {
		if (_ping_changed) {
			_ping_changed = false;
			return true;
		}
		return false;
	}

	uint32_t get_ping_time() {
		return _ping_time;
	}

	uint32_t reset_ping_tmr() {
		_ping_time = _ping_tmr;
		_ping_tmr_needs_reset = true;
		return _ping_time;
	}

	void reset_loop_tmr(float reset_to = 0.f) {
		loop_led.high();
		is_kit ? loop_out_kit.high() : loop_out_built.high();
		_loop_tmr = reset_to;
	}

	bool ping_led_high() {
		return _ping_led_high;
	}

	bool take_ping_cycled() {
		auto t = _ping_cycled;
		_ping_cycled = false;
		return t;
	}
};

} // namespace LDKit
