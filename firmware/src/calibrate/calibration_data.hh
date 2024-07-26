#pragma once
#include "conf/panel_conf.hh"
#include "pr_dbg.hh"
#include "util/calibrator.hh"
#include "util/math.hh"
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

constexpr double to_volts(float val) {
	return (double)val * (10.3 / 8388608.);
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
											  {-Calibration::DefaultLowV, -Calibration::DefaultHighV}};

	static_assert(int(DefaultOutput.adjust(5.f)) == -4072139);
	static_assert(int(DefaultOutput.adjust(1.f)) == -814427);
	static_assert(int(DefaultOutput.adjust(0.f)) == 0);
	static_assert(int(DefaultOutput.adjust(-1.f)) == 814427);
	static_assert(int(DefaultOutput.adjust(-5.f)) == 4072139);

	bool validate() const {
		for (auto chan : in_cal) {
			if (!MathTools::is_finite_fastmath(chan.offset()) || !MathTools::is_finite_fastmath(chan.slope()))
				return false;

			if (std::fabs(chan.adjust(0x0040'0000) - 5.f) > 0.5f) {
				return false;
			}
		}

		for (auto chan : out_cal) {
			if (!MathTools::is_finite_fastmath(chan.offset()) || !MathTools::is_finite_fastmath(chan.slope()))
				return false;

			if (std::fabs(chan.adjust(-5.f) - (float)0x0040'0000) > Calibration::from_volts(0.5f)) {
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
		for (auto chan : in_cal) {
			[[maybe_unused]] auto slope_ratio =
				chan.slope() == 0 ? 0. : double(DefaultInput.slope()) / double(chan.slope());
			[[maybe_unused]] double offset_v = Calibration::to_volts(chan.offset());
			pr_trace("Input: slope: %f offset(V): %f\n", slope_ratio, offset_v);
		}
		for (auto chan : out_cal) {
			[[maybe_unused]] auto slope_ratio =
				chan.slope() == 0 ? 0. : double(DefaultOutput.slope()) / double(chan.slope());
			pr_trace("Output: slope: %f offset(V): %f\n", slope_ratio, double(chan.offset()));
		}
	}
};

} // namespace MetaModule
