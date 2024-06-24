#pragma once
#include "conf/panel_conf.hh"
#include "pr_dbg.hh"
#include "util/calibrator.hh"
#include <array>
#include <cmath>
#include <cstdio>

namespace MetaModule
{

namespace Calibration
{

constexpr float from_volts(float v) {
	return (v / 10.3f) * 8388608.f;
}

constexpr float to_volts(float v) {
	return (v / 10.3f) * 8388608.f;
}

static constexpr float DefaultTolerance = from_volts(0.5);
static constexpr float DefaultLowV = 1;
static constexpr float DefaultHighV = 4;
static constexpr float DefaultLowReading = from_volts(DefaultLowV);
static constexpr float DefaultHighReading = from_volts(DefaultHighV);

} // namespace Calibration

struct CalData {
	std::array<Calibrator, PanelDef::NumAudioIn> in_cal{};
	std::array<Calibrator, PanelDef::NumAudioOut> out_cal{};

	static constexpr Calibrator DefaultInput{{Calibration::DefaultLowV, Calibration::DefaultHighV},
											 {Calibration::DefaultLowReading, Calibration::DefaultHighReading}};

	static constexpr Calibrator DefaultOutput{{Calibration::DefaultLowReading, Calibration::DefaultHighReading},
											  {Calibration::DefaultLowV, Calibration::DefaultHighV}};

	bool validate() const {
		for (auto chan : in_cal) {
			if (std::isnan(chan.offset()) || std::isnan(chan.slope()))
				return false;

			if (std::fabs(chan.adjust(0x0040'0000) - 5.f) > 0.5f) {
				return false;
			}
		}

		for (auto chan : out_cal) {
			if (std::isnan(chan.offset()) || std::isnan(chan.slope()))
				return false;

			if (std::fabs(chan.adjust(5.f) - (float)0x0040'0000) > Calibration::from_volts(0.5f)) {
				return false;
			}
		}

		return true;
	}

	void reset_to_default() {
		in_cal = {{
			{DefaultInput},
			{DefaultInput},
			{DefaultInput},
			{DefaultInput},
			{DefaultInput},
			{DefaultInput},
		}};

		out_cal = {{
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
			{DefaultOutput},
		}};
	}

	void print_calibration() const {
		for (auto chan : in_cal)
			pr_dbg("Input: slope: 1/%f offset: %f\n", 1.f / chan.slope(), chan.offset());

		for (auto chan : out_cal)
			pr_dbg("Output: slope: %f offset: %f\n", chan.slope(), chan.offset());
	}
};

} // namespace MetaModule
