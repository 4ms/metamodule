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
public:
	static CalData read_calibration_or_defaults(auto &&loader, uint32_t address) {
		CalData caldata;

		auto valid = read_calibration(&caldata, std::move(loader), address);
		if (!valid) {
			caldata.reset_to_default();
			pr_info("No Calibration data found, using defaults\n");
		}

		caldata.print_calibration();
		return caldata;
	}

	static bool read_calibration(CalData *caldata, auto &&loader, uint32_t address) {
		pr_dbg("Read Calibration at %x\n", address);

		if (loader.read(address, {reinterpret_cast<uint8_t *>(caldata), sizeof(CalData)})) {

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
