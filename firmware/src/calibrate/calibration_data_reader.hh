#pragma once
#include "calibrate/calibration_data.hh"
#include "flash_loader/flash_loader.hh"
#include "fs/norflash_layout.hh"
#include "pr_dbg.hh"
#include "util/analyzed_signal.hh"
#include <array>
#include <cmath>
#include <optional>

namespace MetaModule
{

class CalibrationDataReader {
	FlashLoader &loader;

public:
	CalibrationDataReader(FlashLoader &loader)
		: loader{loader} {
	}

	CalData read_calibration_or_defaults() {
		CalData caldata;

		auto valid = read_calibration(&caldata);
		if (!valid) {
			caldata.reset_to_default();
			pr_info("No Calibration data found, using defaults\n");
		}

		return caldata;
	}

	bool read_calibration(CalData *caldata) {
		pr_dbg("Read Calibration at %x\n", CalDataFlashOffset);

		if (loader.read_sectors(CalDataFlashOffset, {reinterpret_cast<uint8_t *>(caldata), sizeof(CalData)})) {

			if (caldata->validate()) {
				pr_info("Calibration data read and validated\n");
				return true;

			} else {
				pr_info("Calibration data invalid\n");
				return false;
			}

		} else {
			pr_dbg("Error reading calibration data in flash\n");
			return false;
		}
	}
};

} // namespace MetaModule
