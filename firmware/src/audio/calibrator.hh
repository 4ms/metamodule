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

//TODO: move calibration from main to here
namespace MetaModule
{
struct AudioInCalibrator {
	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};

	bool read_calibration(AudioStream &audio) {
		std::array<std::pair<float, float>, PanelDef::NumAudioIn> caldata;

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
			pr_dbg("Cal data validated: setting audio cal\n");
			audio.set_calibration<0, 4000>(caldata);
			return true;

		} else {
			pr_dbg("Error reading calibration data in flash\n");
			return false;
		}
	}

	void calibrate(AudioStream &audio) {
		std::array<std::pair<float, float>, PanelDef::NumAudioIn> caldata;
		std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> cal_readings;
		mdrivlib::
			FPin<mdrivlib::GPIO::D, mdrivlib::PinNum::_8, mdrivlib::PinMode::Input, mdrivlib::PinPolarity::Inverted>
				button0{mdrivlib::PinPull::Up};

		audio.start();
		audio.start_calibration_mode(cal_readings);
		HAL_Delay(1000);

		{
			pr_dbg("Ready to calibrate: patch 0V and press the back button\n");

			while (!button0.read())
				;
			while (button0.read())
				;

			audio.step_calibration();
			HAL_Delay(1000);
			for (auto [i, ain] : enumerate(cal_readings)) {
				print_reading(i, ain);
				caldata[i].first = ain.iir;
			}
		}

		{
			pr_dbg("Ready: patch 4V and press the back button\n");
			while (!button0.read())
				;
			while (button0.read())
				;

			audio.step_calibration();
			HAL_Delay(1000);
			for (auto [i, ain] : enumerate(cal_readings)) {
				print_reading(i, ain);
				caldata[i].second = ain.iir;
			}
		}

		if (!flash_.write(reinterpret_cast<uint8_t *>(caldata.data()), CalDataFlashOffset, sizeof caldata)) {
			pr_err("Could not write cal data to flash\n");
		}

		audio.set_calibration<0, 4000>(caldata);
		audio.end_calibration_mode();
	}

	void print_reading(unsigned idx, AnalyzedSignal<1000> ain) {
		pr_dbg("AIN %zu: iir=%d min=%d max=%d range=%d\r\n",
			   idx,
			   (int)(ain.iir),
			   (int)(ain.min),
			   (int)(ain.max),
			   (int)((ain.max - ain.min)));
	}
};

} // namespace MetaModule
