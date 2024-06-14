#pragma once
#include "conf/panel_conf.hh"
#include <array>
#include <cmath>
#include <cstdio>

namespace MetaModule
{

namespace Calibration
{

constexpr float from_volts(float v) {
	return (v / 10.f) * 8388608.f;
}

static constexpr float DefaultTolerance = from_volts(0.1);
static constexpr float DefaultLowV = 2;
static constexpr float DefaultHighV = 4;

} // namespace Calibration

struct CalData {

	const uint32_t version = 1;
	std::pair<float, float> ins_measured_mv;
	std::pair<float, float> outs_measured_mv;
	std::array<std::pair<float, float>, PanelDef::NumAudioIn> ins_data;
	std::array<std::pair<float, float>, PanelDef::NumAudioOut> outs_data;

	bool validate() {

		printf("version=%x, %x %x\n", version, ins_data[0].first, ins_data[0].second);
		auto within_tol = [](float x, float y) {
			return std::abs(x - y) < Calibration::DefaultTolerance;
		};

		if (version == 1) {
			for (auto chan : ins_data) {
				if (isnanf(chan.first) || isnanf(chan.second) ||
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

		ins_measured_mv = {DefaultLowV * 1000.f, DefaultHighV * 1000.f};
		outs_measured_mv = {DefaultLowV * 1000.f, DefaultHighV * 1000.f};

		ins_data = {{
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
		}};

		outs_data = {{
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
			{from_volts(DefaultLowV), from_volts(DefaultHighV)},
		}};
	}
};

} // namespace MetaModule
