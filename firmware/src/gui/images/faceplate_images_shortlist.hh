#include "lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(PitchShift_artwork_240);
LV_IMG_DECLARE(HPF_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(KPLS_artwork_240);
LV_IMG_DECLARE(Freeverb_artwork_240);
LV_IMG_DECLARE(Seq8_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(ENVVCA_artwork_240);
// Audible
LV_IMG_DECLARE(Braids_artwork_240);
// LV_IMG_DECLARE(Clouds_artwork_240);
// Befaco
LV_IMG_DECLARE(DualAtenuverter_artwork_240);
LV_IMG_DECLARE(EvenVCO_artwork_240);
LV_IMG_DECLARE(SpringReverb_artwork_240);
LV_IMG_DECLARE(ABC_artwork_240);
LV_IMG_DECLARE(ADSR_artwork_240);
LV_IMG_DECLARE(ChoppingKinky_artwork_240);
LV_IMG_DECLARE(HexmixVCA_artwork_240);
LV_IMG_DECLARE(Kickall_artwork_240);
LV_IMG_DECLARE(Mixer_artwork_240);
LV_IMG_DECLARE(Morphader_artwork_240);
LV_IMG_DECLARE(MotionMTR_artwork_240);
LV_IMG_DECLARE(Muxlicer_artwork_240);
LV_IMG_DECLARE(Percall_artwork_240);
LV_IMG_DECLARE(PonyVCO_artwork_240);
LV_IMG_DECLARE(Rampage_artwork_240);
LV_IMG_DECLARE(STMix_artwork_240);
LV_IMG_DECLARE(SamplingModulator_artwork_240);
LV_IMG_DECLARE(SlewLimiter_artwork_240);
LV_IMG_DECLARE(StereoStrip_artwork_240);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		// SLUG TO IMAGE HERE

		if (slug == "PEG")
			return &PEG_artwork_240;

		if (slug == "PitchShift")
			return &PitchShift_artwork_240;

		if (slug == "HPF")
			return &HPF_artwork_240;

		if (slug == "MultiLFO")
			return &MultiLFO_artwork_240;

		if (slug == "Djembe")
			return &Djembe_artwork_240;

		if (slug == "StMix")
			return &StMix_artwork_240;

		if (slug == "SMR")
			return &SMR_artwork_240;

		if (slug == "InfOsc")
			return &InfOsc_artwork_240;

		if (slug == "KPLS")
			return &KPLS_artwork_240;

		if (slug == "Freeverb")
			return &Freeverb_artwork_240;

		if (slug == "Seq8")
			return &Seq8_artwork_240;

		if (slug == "EnOsc")
			return &EnOsc_artwork_240;

		if (slug == "ENVVCA")
			return &ENVVCA_artwork_240;

		// Audible Instruments
		if (slug == "Braids")
			return &Braids_artwork_240;
		// if (slug == "Clouds")
		// 	return &Clouds_artwork_240;

		// Befaco
		if (slug == "DualAtenuverter")
			return &DualAtenuverter_artwork_240;
		if (slug == "EvenVCO")
			return &EvenVCO_artwork_240;
		if (slug == "SpringReverb")
			return &SpringReverb_artwork_240;
		if (slug == "ABC")
			return &ABC_artwork_240;
		if (slug == "ADSR")
			return &ADSR_artwork_240;
		if (slug == "ChoppingKinky")
			return &ChoppingKinky_artwork_240;
		if (slug == "HexmixVCA")
			return &HexmixVCA_artwork_240;
		if (slug == "Kickall")
			return &Kickall_artwork_240;
		if (slug == "Mixer")
			return &Mixer_artwork_240;
		if (slug == "Morphader")
			return &Morphader_artwork_240;
		if (slug == "MotionMTR")
			return &MotionMTR_artwork_240;
		// if (slug == "Muxlicer")
		// 	return &Muxlicer_artwork_240;
		if (slug == "Percall")
			return &Percall_artwork_240;
		if (slug == "PonyVCO")
			return &PonyVCO_artwork_240;
		if (slug == "Rampage")
			return &Rampage_artwork_240;
		if (slug == "STMix")
			return &STMix_artwork_240;
		if (slug == "SamplingModulator")
			return &SamplingModulator_artwork_240;
		if (slug == "SlewLimiter")
			return &SlewLimiter_artwork_240;
		if (slug == "StereoStrip")
			return &StereoStrip_artwork_240;

		return nullptr;
	}
};
