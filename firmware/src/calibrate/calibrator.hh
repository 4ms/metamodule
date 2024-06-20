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
	CalData caldata;
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
		return caldata.ins_data[chan_num];
	}

	enum class CalibrationEvent { None, MeasuredLow, MeasuredHigh };

	CalibrationEvent read(unsigned chan_num, AnalyzedSig &reading) {
		CalibrationEvent event = CalibrationEvent::None;

		if (chan_num < caldata.ins_data.size()) {
			if (delay_ctr == 0)
				reading.reset_to(reading.iir);

			if (++delay_ctr >= 4) {
				delay_ctr = 0;

				if (validate_reading(reading, Calibration::from_volts(config.low_measurement_volts))) {
					pr_dbg("Low: ");
					caldata.ins_data[chan_num].first = reading.iir;
					event = CalibrationEvent::MeasuredLow;
				}

				else if (validate_reading(reading, Calibration::from_volts(config.high_measurement_volts)))
				{
					pr_dbg("High: ");
					caldata.ins_data[chan_num].second = reading.iir;
					event = CalibrationEvent::MeasuredHigh;
				}

				else
				{
					pr_dbg("Rejected: ");
				}

				debug_print_reading(chan_num, reading);
			}
		}

		return event;
	}

	bool validate_reading(AnalyzedSig &reading, float target, float tolerance = Calibration::DefaultTolerance) {
		if (std::abs(reading.iir - target) < tolerance) {
			if (std::abs(reading.min - target) < tolerance) {
				if (std::abs(reading.max - target) < tolerance) {
					if ((reading.max - reading.min) < Calibration::from_volts(0.001f))
						return true;
					else
						pr_dbg("max-min = %f > %f\n", (reading.max - reading.min), Calibration::from_volts(0.001f));
				} else
					pr_dbg("max = %f\n", reading.max);
			} else
				pr_dbg("min = %f\n", reading.min);
		} else
			pr_dbg("iir = %f\n", reading.iir);
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
