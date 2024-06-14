#pragma once
#include "audio/audio.hh"
#include "conf/panel_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "drivers/pin.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/norflash_layout.hh"
#include "pr_dbg.hh"
#include "util/analyzed_signal.hh"
#include <array>
#include <cmath>
#include <optional>

namespace MetaModule
{

class CalibrationDataReader {

	// struct CalData2 {
	// 	std::pair<float, float> ins_measured_millivolts;
	// 	std::array<std::pair<float, float>, PanelDef::NumAudioIn> ins_data;
	// };

	using CalData = std::array<std::pair<float, float>, PanelDef::NumAudioIn /* + PanelDef::NumAudioOut*/>;
	CalData caldata;

	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};

public:
	bool read_calibration() {
		if (flash_.read(reinterpret_cast<uint8_t *>(caldata.data()), CalDataFlashOffset, sizeof caldata)) {

			for (auto chan : caldata) {

				pr_dbg("Read: %f %f\n", chan.first, chan.second);

				if (isnanf(chan.first) || isnanf(chan.second) || chan.first < -100'000.f || chan.first > 100'000.f ||
					chan.second < 3'000'000.f || chan.second > 3'500'000.f)
				{
					pr_info("Cal data invalid\n");
					return false;
				}
			}

			pr_dbg("Cal data validated\n");
			return true;

		} else {
			pr_dbg("Error reading calibration data in flash\n");
			return false;
		}
	}

	void use_default_values() {
		caldata = {{
			{-7603.204102, 3258431.500000},
			{-7982.296387, 3268419.500000},
			{-12926.662109, 3255171.250000},
			{-7208.814453, 3256771.000000},
			{-16831.820312, 3262270.250000},
			{-14835.051758, 3257434.250000},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
			// {0, 1.f},
		}};
	}

	void read_calibration_or_defaults() {
		auto valid = read_calibration();
		if (!valid) {
			use_default_values();
			pr_info("No CV calibration data found, using defaults\n");
		}
	}

	CalData &get_cal_data() {
		return caldata;
	}
};

} // namespace MetaModule
