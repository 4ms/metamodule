#include "calibration_storage.hh"
#include "conf/flash_layout.hh"
#include "flash.hh"
#include "ping_methods.hh"
#include <span>

namespace LDKit
{

void PersistentStorage::set_default_cal() {
	data.major_firmware_version = FirmwareMajorVersion;
	data.minor_firmware_version = FirmwareMinorVersion;
	data.cv_calibration_offset[0] = -Brain::CVAdcConf::bi_min_value;
	data.cv_calibration_offset[1] = -Brain::CVAdcConf::uni_min_value;
	data.cv_calibration_offset[2] = -Brain::CVAdcConf::uni_min_value;
	data.cv_calibration_offset[3] = -Brain::CVAdcConf::uni_min_value;
	data.tracking_comp = 1.f;
	data.codec_adc_calibration_dcoffset[0] = 0;
	data.codec_adc_calibration_dcoffset[1] = 0;
	data.codec_dac_calibration_dcoffset[0] = 0;
	data.codec_dac_calibration_dcoffset[1] = 0;
	data.settings.auto_mute = true;
	data.settings.soft_clip = true;
	data.settings.ping_method = PingMethod::IGNORE_FLAT_DEVIATION_10;
	data.settings.rev_jack = GateType::Trig;
	data.settings.inf_jack = GateType::Trig;
	data.settings.loop_clock = GateType::Trig;
	data.settings.main_clock = GateType::Gate;
	data.settings.log_delay_feed = true;
	data.settings.auto_unquantize_timejack = false;
	data.settings.send_return_before_loop = false;
	data.settings.stereo_mode = false;

	data.settings.crossfade_samples = 384;		 // SLOW_FADE_SAMPLES
	data.settings.write_crossfade_samples = 384; // FAST_FADE_SAMPLES

	data.settings.crossfade_rate =
		data.settings.calc_fade_increment(data.settings.crossfade_samples); // SLOW_FADE_INCREMENT
	data.settings.write_crossfade_rate =
		data.settings.calc_fade_increment(data.settings.crossfade_samples); // FAST_FADE_INCREMENT
}

void PersistentStorage::factory_reset() {
	set_default_cal();
	save_flash_params();
}

PersistentStorage::PersistentStorage() {
	if (!flash.read(data) || !data.validate()) {
		set_default_cal();
		if (!flash.write(data)) {
			storage_is_ok = false;
			// __BKPT(2); // ERROR!
		}
	}
	handle_updated_firmware();
}

bool PersistentStorage::save_flash_params() { //
	if (!storage_is_ok)
		return false;
	return flash.write(data);
}

void PersistentStorage::handle_updated_firmware() {
	if (data.major_firmware_version == FirmwareMajorVersion && data.minor_firmware_version == FirmwareMinorVersion)
		return;

	apply_firmware_specific_adjustments();
	data.major_firmware_version = FirmwareMajorVersion;
	data.minor_firmware_version = FirmwareMinorVersion;
	save_flash_params();
}

void PersistentStorage::apply_firmware_specific_adjustments() {
	if (data.major_firmware_version == 0 && data.minor_firmware_version == 0) {
		// v0.0 => newer
	}
}

} // namespace LDKit
