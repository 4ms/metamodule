#pragma once
#include "conf/panel_conf.hh"
#include "util/calibrator.hh"
#include <array>
#include <cmath>
#include <cstdio>

namespace MetaModule
{

struct SavedCalData {
	std::array<Calibrator, PanelDef::NumAudioIn> in_cal{};
	std::array<Calibrator, PanelDef::NumAudioOut> out_cal{};
};

namespace Calibration
{

constexpr float from_volts(float v) {
	return (v / 10.3f) * 8388608.f;
}

static constexpr float DefaultTolerance = from_volts(0.5);
static constexpr float DefaultLowV = 2;
static constexpr float DefaultHighV = 4;
static constexpr float DefaultLowReading = from_volts(DefaultLowV);
static constexpr float DefaultHighReading = from_volts(DefaultHighV);

} // namespace Calibration

struct CalData {

	const uint32_t version = 1;
	std::pair<float, float> ins_target_volts;
	std::pair<float, float> outs_measured_volts;
	std::array<std::pair<float, float>, PanelDef::NumAudioIn> ins_data;
	std::array<std::pair<float, float>, PanelDef::NumAudioOut> outs_data;

	bool validate() {

		// printf("version=%x, %x %x\n", version, ins_data[0].first, ins_data[0].second);
		auto within_tol = [](float x, float y) {
			return std::abs(x - y) < Calibration::DefaultTolerance;
		};

		if (version == 1) {
			for (auto chan : ins_data) {
				if (std::isnan(chan.first) || std::isnan(chan.second) ||
					!within_tol(chan.first, Calibration::from_volts(Calibration::DefaultLowV)) ||
					!within_tol(chan.second, Calibration::from_volts(Calibration::DefaultHighV)))
				{
					return false;
				}
			}
			return true;

		} else {
			return false;
		}
	}

	void reset_to_default() {
		using namespace Calibration;

		ins_target_volts = {DefaultLowV, DefaultHighV};
		outs_measured_volts = {DefaultLowV, DefaultHighV};

		ins_data = {{
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
		}};

		outs_data = {{
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
			{DefaultLowReading, DefaultHighReading},
		}};
	}
};

} // namespace MetaModule
