#include "../src/calibration_storage.hh"
#include <span>

namespace SamplerKit
{

void CalibrationStorage::set_default_cal() {
	cal_data.major_firmware_version = FirmwareMajorVersion;
	cal_data.minor_firmware_version = FirmwareMinorVersion;
	cal_data.cv_calibration_offset[0] = 0;
	cal_data.cv_calibration_offset[1] = 0;
	cal_data.cv_calibration_offset[2] = 0;
	cal_data.cv_calibration_offset[3] = 0;
	cal_data.cv_calibration_offset[4] = 0;
	cal_data.codec_adc_calibration_dcoffset[0] = 0;
	cal_data.codec_adc_calibration_dcoffset[1] = 0;
	cal_data.codec_dac_calibration_dcoffset[0] = 0;
	cal_data.codec_dac_calibration_dcoffset[1] = 0;
	cal_data.tracking_comp = 1.f;
	cal_data.pitch_pot_detent_offset = 0;
	cal_data.bank_rgb_adj.r = 128;
	cal_data.bank_rgb_adj.g = 128;
	cal_data.bank_rgb_adj.b = 128;
	cal_data.play_rgb_adj.r = 128;
	cal_data.play_rgb_adj.g = 128;
	cal_data.play_rgb_adj.b = 128;
	cal_data.rev_rgb_adj.r = 128;
	cal_data.rev_rgb_adj.g = 128;
	cal_data.rev_rgb_adj.b = 128;
}

void CalibrationStorage::factory_reset() {
	set_default_cal();
	save_flash_params();
}

CalibrationStorage::CalibrationStorage() {
	set_default_cal();
}

bool CalibrationStorage::save_flash_params() { //
	return true;
}

void CalibrationStorage::handle_updated_firmware() {
	if (cal_data.major_firmware_version == FirmwareMajorVersion &&
		cal_data.minor_firmware_version == FirmwareMinorVersion)
		return;

	apply_firmware_specific_adjustments();
	cal_data.major_firmware_version = FirmwareMajorVersion;
	cal_data.minor_firmware_version = FirmwareMinorVersion;
	save_flash_params();
}

void CalibrationStorage::apply_firmware_specific_adjustments() {
}

} // namespace SamplerKit
