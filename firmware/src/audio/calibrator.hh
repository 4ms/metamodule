#pragma once
#include "conf/panel_conf.hh"
#include "drivers/stm32xx.h"
#include "pr_dbg.hh"
#include "util/analyzed_signal.hh"
#include "util/countzip.hh"
#include <array>
#include <cmath>
#include <optional>
#include <span>

namespace MetaModule
{

// TODO: remove dependency on AudioStream so we can use this from CA7 core 2
// GUI will request via PatchLoader to start/end calibration mode
// audio.step_calibration() => AudioInCalibrator::step_calibration()
// QSpiFlash -> use M4

class Calibrator {
	using CalData = std::array<std::pair<float, float>, PanelDef::NumAudioIn>;

	CalData caldata;
	unsigned delay_ctr = 0;

public:
	// caller needs to send message via PatchPlayLoader to tell audio to disable calibration
	// cal.reset_readings(analyzed_signal);
	// ...wait for a few blocks
	// cal.record_low_measurements(metaparams.cal_readings);
	//
	// cal.reset_readings(analyzed_signal);
	// ...wait for a few blocks
	// cal.record_high_measurements(metaparams.cal_readings);
	//
	// write()

	void start() {
		state = State::WaitingForLow;
		delay_ctr = 0;
	}

	void update(unsigned chan_num, AnalyzedSignal<1000> reading) {

		switch (state) {
			case State::Idle: {
			} break;

			case State::WaitingForLow: {
				if (delay_ctr == 0)
					reading.reset_to(reading.iir);

				if (++delay_ctr > 16) { //256ms
					caldata[chan_num].first = reading.iir;
					state = State::WaitingforHigh;
					delay_ctr = 0;
				}
			} break;

			case State::WaitingforHigh: {
				if (delay_ctr == 0)
					reading.reset_to(reading.iir);

				if (++delay_ctr > 16) { //256ms
					caldata[chan_num].second = reading.iir;
					state = State::WaitingforHigh;
					delay_ctr = 0;

					debug_print_reading(chan_num, reading);
				}
			} break;

			case State::Done: {
			} break;
		}
	}

	enum class State { Idle, WaitingForLow, WaitingforHigh, Done } state = State::Idle;

	CalData &get_cal_data() {
		return caldata;
	}

	void debug_print_reading(unsigned idx, AnalyzedSignal<1000> ain) {
		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
			   idx,
			   (int)(ain.iir),
			   (int)(ain.min),
			   (int)(ain.max),
			   (int)((ain.max - ain.min)));
	}
};

} // namespace MetaModule
