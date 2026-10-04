#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
#include "conf/panel_conf.hh"
#include <cstdint>

namespace MetaModule::ClipDetect
{

// True if a calibrated DAC value would be clamped by 24-bit saturation
constexpr bool exceeds_24bit(int32_t v) {
	return v > 0x7F'FFFF || v < -0x80'0000;
}

// get_ext_audio_output() receives a codec channel; clip bits are indexed by panel output
constexpr unsigned ext_output_bit(unsigned codec_chan) {
	return PanelDef::NumAudioOut + AudioExpander::out_order[codec_chan];
}

} // namespace MetaModule::ClipDetect
