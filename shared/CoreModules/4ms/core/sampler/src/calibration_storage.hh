#pragma once
#include "elements.hh"
#include "util/colors.hh"
#include <cstdint>

#ifndef METAMODULE
#include "conf/flash_layout.hh"
#include "flash_block.hh"
#include "util/wear_level.hh"
#endif

namespace SamplerKit
{

struct CalibrationData {
	uint32_t major_firmware_version;
	uint32_t minor_firmware_version;
	int32_t cv_calibration_offset[NumCVs];
	int32_t codec_adc_calibration_dcoffset[2];
	int32_t codec_dac_calibration_dcoffset[2];
	float tracking_comp;
	int32_t pitch_pot_detent_offset;
	Color::Adjustment bank_rgb_adj;
	uint8_t _pad1;
	Color::Adjustment play_rgb_adj;
	uint8_t _pad2;
	Color::Adjustment rev_rgb_adj;
	uint8_t _pad3;

	bool validate() {
		return (major_firmware_version < 100) && (minor_firmware_version < 100) &&
			   (major_firmware_version + minor_firmware_version > 0) && //
			   tracking_comp > 0.5f && tracking_comp < 1.5f &&			//
			   bank_rgb_adj.r > 32 && bank_rgb_adj.r < 216 &&			//
			   bank_rgb_adj.g > 32 && bank_rgb_adj.g < 216 &&			//
			   bank_rgb_adj.b > 32 && bank_rgb_adj.b < 216 &&			//
			   play_rgb_adj.r > 32 && play_rgb_adj.r < 216 &&			//
			   play_rgb_adj.g > 32 && play_rgb_adj.g < 216 &&			//
			   play_rgb_adj.b > 32 && play_rgb_adj.b < 216 &&			//
			   rev_rgb_adj.r > 32 && rev_rgb_adj.r < 216 &&				//
			   rev_rgb_adj.g > 32 && rev_rgb_adj.g < 216 &&				//
			   rev_rgb_adj.b > 32 && rev_rgb_adj.b < 216;
	}
};

struct CalibrationStorage {
#ifndef METAMODULE
	WearLevel<FlashBlock<SettingsFlashAddr, CalibrationData, 8>> flash;
#endif
	CalibrationData cal_data;
	bool storage_is_ok = true;

	CalibrationStorage();
	bool save_flash_params();
	void factory_reset();

private:
	void apply_firmware_specific_adjustments();
	void handle_updated_firmware();
	void set_default_cal();
};

} // namespace SamplerKit
