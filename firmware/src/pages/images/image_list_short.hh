#include "lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(PEG_artwork_120);
LV_IMG_DECLARE(PitchShift_artwork_240);
LV_IMG_DECLARE(PitchShift_artwork_120);
LV_IMG_DECLARE(HPF_artwork_240);
LV_IMG_DECLARE(HPF_artwork_120);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_120);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_120);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(StMix_artwork_120);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(SMR_artwork_120);
LV_IMG_DECLARE(InfOsc_artwork_120);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(KPLS_artwork_120);
LV_IMG_DECLARE(KPLS_artwork_240);
LV_IMG_DECLARE(Freeverb_artwork_240);
LV_IMG_DECLARE(Freeverb_artwork_120);
LV_IMG_DECLARE(Seq8_artwork_120);
LV_IMG_DECLARE(Seq8_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_120);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(ENVVCA_artwork_240);
LV_IMG_DECLARE(ENVVCA_artwork_120);
// Audible
LV_IMG_DECLARE(Braids_artwork_120);
LV_IMG_DECLARE(Braids_artwork_240);
LV_IMG_DECLARE(Clouds_artwork_120);
LV_IMG_DECLARE(Clouds_artwork_240);
// Befaco
LV_IMG_DECLARE(DualAtenuverter_artwork_120);
LV_IMG_DECLARE(DualAtenuverter_artwork_240);
LV_IMG_DECLARE(EvenVCO_artwork_120);
LV_IMG_DECLARE(EvenVCO_artwork_240);
LV_IMG_DECLARE(SpringReverb_artwork_240);
LV_IMG_DECLARE(SpringReverb_artwork_120);
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
LV_IMG_DECLARE(ABC_artwork_120);
LV_IMG_DECLARE(ADSR_artwork_120);
LV_IMG_DECLARE(ChoppingKinky_artwork_120);
LV_IMG_DECLARE(HexmixVCA_artwork_120);
LV_IMG_DECLARE(Kickall_artwork_120);
LV_IMG_DECLARE(Mixer_artwork_120);
LV_IMG_DECLARE(Morphader_artwork_120);
LV_IMG_DECLARE(MotionMTR_artwork_120);
LV_IMG_DECLARE(Muxlicer_artwork_120);
LV_IMG_DECLARE(Percall_artwork_120);
LV_IMG_DECLARE(PonyVCO_artwork_120);
LV_IMG_DECLARE(Rampage_artwork_120);
LV_IMG_DECLARE(STMix_artwork_120);
LV_IMG_DECLARE(SamplingModulator_artwork_120);
LV_IMG_DECLARE(SlewLimiter_artwork_120);
LV_IMG_DECLARE(StereoStrip_artwork_120);

extern const uint8_t PEG_artwork_240_map[];
static const lv_img_dsc_t PEG_png{
	.header =
		{
			.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
			.always_zero = 0,
			.w = 75,
			.h = 240, //detect from file
		},
	.data_size = 39301,
	.data = PEG_artwork_240_map,
};
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug, size_t height = 240) {
		// SLUG TO IMAGE HERE

		if (slug == "PEG")
			return &PEG_png;
		// return (height == 240) ? &PEG_artwork_240 : &PEG_artwork_120;

		if (slug == "PitchShift")
			return (height == 240) ? &PitchShift_artwork_240 : &PitchShift_artwork_120;

		if (slug == "HPF")
			return (height == 240) ? &HPF_artwork_240 : &HPF_artwork_120;

		if (slug == "MultiLFO")
			return (height == 240) ? &MultiLFO_artwork_240 : &MultiLFO_artwork_120;

		if (slug == "Djembe")
			return (height == 240) ? &Djembe_artwork_240 : &Djembe_artwork_120;

		if (slug == "StMix")
			return (height == 240) ? &StMix_artwork_240 : &StMix_artwork_120;

		if (slug == "SMR")
			return (height == 240) ? &SMR_artwork_240 : &SMR_artwork_120;

		if (slug == "InfOsc")
			return (height == 240) ? &InfOsc_artwork_240 : &InfOsc_artwork_120;

		if (slug == "KPLS")
			return (height == 240) ? &KPLS_artwork_240 : &KPLS_artwork_120;

		if (slug == "Freeverb")
			return (height == 240) ? &Freeverb_artwork_240 : &Freeverb_artwork_120;

		if (slug == "Seq8")
			return (height == 240) ? &Seq8_artwork_240 : &Seq8_artwork_120;

		if (slug == "EnOsc")
			return (height == 240) ? &EnOsc_artwork_240 : &EnOsc_artwork_120;

		if (slug == "ENVVCA")
			return (height == 240) ? &ENVVCA_artwork_240 : &ENVVCA_artwork_120;

		// Audible Instruments
		if (slug == "Braids")
			return (height == 240) ? &Braids_artwork_240 : &Braids_artwork_120;
		if (slug == "Clouds")
			return (height == 240) ? &Clouds_artwork_240 : &Clouds_artwork_120;

		// Befaco
		if (slug == "DualAtenuverter")
			return (height == 240) ? &DualAtenuverter_artwork_240 : &DualAtenuverter_artwork_120;
		if (slug == "EvenVCO")
			return (height == 240) ? &EvenVCO_artwork_240 : &EvenVCO_artwork_120;
		if (slug == "SpringReverb")
			return (height == 240) ? &SpringReverb_artwork_240 : &SpringReverb_artwork_120;
		if (slug == "ABC")
			return (height == 240) ? &ABC_artwork_240 : &ABC_artwork_120;
		if (slug == "ADSR")
			return (height == 240) ? &ADSR_artwork_240 : &ADSR_artwork_120;
		if (slug == "ChoppingKinky")
			return (height == 240) ? &ChoppingKinky_artwork_240 : &ChoppingKinky_artwork_120;
		if (slug == "HexmixVCA")
			return (height == 240) ? &HexmixVCA_artwork_240 : &HexmixVCA_artwork_120;
		if (slug == "Kickall")
			return (height == 240) ? &Kickall_artwork_240 : &Kickall_artwork_120;
		if (slug == "Mixer")
			return (height == 240) ? &Mixer_artwork_240 : &Mixer_artwork_120;
		if (slug == "Morphader")
			return (height == 240) ? &Morphader_artwork_240 : &Morphader_artwork_120;
		if (slug == "MotionMTR")
			return (height == 240) ? &MotionMTR_artwork_240 : &MotionMTR_artwork_120;
		// if (slug == "Muxlicer")
		// 	return (height == 240) ? &Muxlicer_artwork_240 : &Muxlicer_artwork_120;
		if (slug == "Percall")
			return (height == 240) ? &Percall_artwork_240 : &Percall_artwork_120;
		if (slug == "PonyVCO")
			return (height == 240) ? &PonyVCO_artwork_240 : &PonyVCO_artwork_120;
		if (slug == "Rampage")
			return (height == 240) ? &Rampage_artwork_240 : &Rampage_artwork_120;
		if (slug == "STMix")
			return (height == 240) ? &STMix_artwork_240 : &STMix_artwork_120;
		if (slug == "SamplingModulator")
			return (height == 240) ? &SamplingModulator_artwork_240 : &SamplingModulator_artwork_120;
		if (slug == "SlewLimiter")
			return (height == 240) ? &SlewLimiter_artwork_240 : &SlewLimiter_artwork_120;
		if (slug == "StereoStrip")
			return (height == 240) ? &StereoStrip_artwork_240 : &StereoStrip_artwork_120;

		return nullptr;
	}
};
