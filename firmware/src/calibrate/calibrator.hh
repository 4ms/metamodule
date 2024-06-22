#pragma once
#include "calibrate/calibration_data.hh"
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

struct CalibrationConfig {
	float low_measurement_volts;
	float high_measurement_volts;
	float tolerance_volts; //valid range = measurement +/- tolerance
};

class CalibrationMeasurer {
private:
	std::array<std::pair<float, float>, PanelDef::NumAudioIn> caldata;
	unsigned delay_ctr = 0;
	CalibrationConfig config;

public:
	CalibrationMeasurer(CalibrationConfig config)
		: config{config} {
	}

	void start_chan(unsigned chan_num) {
		delay_ctr = 0;
	}

	[[nodiscard]] std::pair<float, float> get_cal_data(unsigned chan_num) {
		return caldata[chan_num];
	}

	enum class CalibrationEvent { None, MeasuredLow, MeasuredHigh };

	CalibrationEvent read(unsigned chan_num, AnalyzedSig &reading) {
		CalibrationEvent event = CalibrationEvent::None;

		if (chan_num < caldata.size()) {
			if (delay_ctr == 0)
				reading.reset_to(reading.iir);

			if (++delay_ctr >= 4) {
				delay_ctr = 0;

				if (validate_reading(reading, config.low_measurement_volts)) {
					caldata[chan_num].first = reading.iir;
					event = CalibrationEvent::MeasuredLow;
				}

				else if (validate_reading(reading, config.high_measurement_volts))
				{
					caldata[chan_num].second = reading.iir;
					event = CalibrationEvent::MeasuredHigh;
				}

				debug_print_reading(chan_num, reading);
			}
		}

		return event;
	}

	bool validate_reading(AnalyzedSig &reading, float target, float tolerance = 0.5f, float max_noise = 0.001f) {
		if (std::abs(reading.iir - target) < tolerance) {
			if (std::abs(reading.min - target) < tolerance) {
				if (std::abs(reading.max - target) < tolerance) {
					if ((reading.max - reading.min) < max_noise)
						return true;
				}
			}
		}
		return false;
	}

private:
	void debug_print_reading(unsigned idx, AnalyzedSig ain) {
		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
			   idx,
			   (int)(ain.iir),
			   (int)(ain.min),
			   (int)(ain.max),
			   (int)((ain.max - ain.min)));
	}
};

} // namespace MetaModule
