#pragma once
#include "audio/calibration_data.hh"
#include "conf/panel_conf.hh"
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

struct CalibrationConfig {
	float low_measurement_volts;
	float high_measurement_volts;
	float tolerance_volts; //valid range = measurement +/- tolerance
};

class CalibrationRoutine {
private:
	CalData caldata;
	unsigned delay_ctr = 0;

	enum class State { Idle, WaitingForReading, Done };
	std::array<State, PanelDef::NumAudioIn> states{};
	std::array<bool, PanelDef::NumAudioIn> got_low{};
	std::array<bool, PanelDef::NumAudioIn> got_high{};

	CalibrationConfig config;

public:
	CalibrationRoutine(CalibrationConfig config)
		: config{config} {
	}

	void start_chan(unsigned chan_num) {
		if (chan_num >= states.size())
			return;

		states[chan_num] = State::WaitingForReading;
		got_low[chan_num] = false;
		got_high[chan_num] = false;
		delay_ctr = 0;
	}

	// return channel's validated readings if we got them both
	[[nodiscard]] std::optional<std::pair<float, float>> stop_chan(unsigned chan_num) {
		if (chan_num >= states.size())
			return std::nullopt;

		auto old_state = states[chan_num];
		states[chan_num] = State::Idle;

		if (old_state == State::Done)
			return caldata.ins_data[chan_num];
		else
			return std::nullopt;
	}

	void update(unsigned chan_num, AnalyzedSignal<16> &reading) {
		if (chan_num >= states.size())
			return;

		switch (states[chan_num]) {
			case State::Idle: {
			} break;

			case State::WaitingForReading: {
				if (delay_ctr == 0)
					reading.reset_to(reading.iir);

				if (++delay_ctr == 16) { //@16ms update rate = 256ms between attempts

					if (validate_reading(reading, Calibration::from_volts(config.low_measurement_volts))) {
						pr_dbg("Low: ");
						caldata.ins_data[chan_num].first = reading.iir;
						got_low[chan_num] = true;
					}

					else if (validate_reading(reading, Calibration::from_volts(config.high_measurement_volts)))
					{
						pr_dbg("High: ");
						caldata.ins_data[chan_num].second = reading.iir;
						got_high[chan_num] = true;
					}

					else
					{
						pr_dbg("Rejected: ");
						delay_ctr = 0;
					}

					debug_print_reading(chan_num, reading);

					if (got_low[chan_num] && got_high[chan_num])
						states[chan_num] = State::Done;
				}
			} break;

			case State::Done: {
			} break;
		}
	}

private:
	bool validate_reading(AnalyzedSignal<16> &reading, float target) {
		if (std::abs(reading.iir - target) < Calibration::DefaultTolerance) {
			if (std::abs(reading.min - target) < Calibration::DefaultTolerance) {
				if (std::abs(reading.max - target) < Calibration::DefaultTolerance) {
					if ((reading.max - reading.min) < 200)
						return true;
				}
			}
		}
		pr_dbg(" X target=%f ", target);
		return false;
	}

	void debug_print_reading(unsigned idx, AnalyzedSignal<16> ain) {
		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
			   idx,
			   (int)(ain.iir),
			   (int)(ain.min),
			   (int)(ain.max),
			   (int)((ain.max - ain.min)));
	}
};

} // namespace MetaModule
