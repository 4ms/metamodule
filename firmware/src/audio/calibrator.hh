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
	using CalData = std::array<std::pair<float, float>, PanelDef::NumAudioIn /* + PanelDef::NumAudioOut*/>;

	CalData caldata;

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

	void record_low_measurements(std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> &cal_readings) {
		for (auto [i, ain] : enumerate(cal_readings)) {
			debug_print_reading(i, ain);
			caldata[i].first = ain.iir;
		}
	}

	void record_high_measurements(std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> &cal_readings) {
		for (auto [i, ain] : enumerate(cal_readings)) {
			debug_print_reading(i, ain);
			caldata[i].second = ain.iir;
		}
	}

	void reset_readings(std::span<AnalyzedSignal<1000>, PanelDef::NumAudioIn> cal_readings) {
		for (auto &chan : cal_readings) {
			chan.reset_to(chan.iir);
		}
	}

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
