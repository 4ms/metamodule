#pragma once
#include "lvgl/lvgl.h"
#include <string_view>

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(ADEnv_artwork_240);
LV_IMG_DECLARE(VCA_artwork_240);
LV_IMG_DECLARE(Shift_artwork_240);
LV_IMG_DECLARE(Send_artwork_240);
LV_IMG_DECLARE(Mixer_artwork_240);
LV_IMG_DECLARE(Logic_artwork_240);
LV_IMG_DECLARE(LPG_artwork_240);
LV_IMG_DECLARE(LFO_artwork_240);
LV_IMG_DECLARE(Gate8_artwork_240);
LV_IMG_DECLARE(Gate32_artwork_240);
LV_IMG_DECLARE(Fade_artwork_240);
LV_IMG_DECLARE(FadeDelay_artwork_240);
LV_IMG_DECLARE(Comp_artwork_240);
LV_IMG_DECLARE(CLKM_artwork_240);
LV_IMG_DECLARE(CLKD_artwork_240);
LV_IMG_DECLARE(Att_artwork_240);
LV_IMG_DECLARE(AD_artwork_240);
LV_IMG_DECLARE(Sequant_artwork_240);
LV_IMG_DECLARE(Switch14_artwork_240);
LV_IMG_DECLARE(Seq4_artwork_240);
LV_IMG_DECLARE(Octave_artwork_240);
LV_IMG_DECLARE(MNMX_artwork_240);
LV_IMG_DECLARE(LPF_artwork_240);
LV_IMG_DECLARE(Verb_artwork_240);
LV_IMG_DECLARE(Switch41_artwork_240);
LV_IMG_DECLARE(Seq8_artwork_240);
LV_IMG_DECLARE(Quant_artwork_240);
LV_IMG_DECLARE(Prob8_artwork_240);
LV_IMG_DECLARE(Source_artwork_240);
LV_IMG_DECLARE(Slew_artwork_240);
LV_IMG_DECLARE(PitchShift_artwork_240);
LV_IMG_DECLARE(Noise_artwork_240);
LV_IMG_DECLARE(KPLS_artwork_240);
LV_IMG_DECLARE(HPF_artwork_240);
LV_IMG_DECLARE(Gate_artwork_240);
LV_IMG_DECLARE(Detune_artwork_240);
LV_IMG_DECLARE(BPF_artwork_240);
LV_IMG_DECLARE(PanelMed_artwork_240);
LV_IMG_DECLARE(ComplexEG_artwork_240);
LV_IMG_DECLARE(Pan_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(Follow_artwork_240);
LV_IMG_DECLARE(FM_artwork_240);
LV_IMG_DECLARE(Drum_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(Atvert2_artwork_240);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(BuffMult_artwork_240);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		// SLUG TO IMAGE HERE

		if (slug == "ADEnv")
			return &ADEnv_artwork_240;

		if (slug == "VCA")
			return &VCA_artwork_240;

		if (slug == "Shift")
			return &Shift_artwork_240;

		if (slug == "Send")
			return &Send_artwork_240;

		if (slug == "Mixer")
			return &Mixer_artwork_240;

		if (slug == "Logic")
			return &Logic_artwork_240;

		if (slug == "LPG")
			return &LPG_artwork_240;

		if (slug == "LFO")
			return &LFO_artwork_240;

		if (slug == "Gate8")
			return &Gate8_artwork_240;

		if (slug == "Gate32")
			return &Gate32_artwork_240;

		if (slug == "Fade")
			return &Fade_artwork_240;

		if (slug == "FadeDelay")
			return &FadeDelay_artwork_240;

		if (slug == "Comp")
			return &Comp_artwork_240;

		if (slug == "CLKM")
			return &CLKM_artwork_240;

		if (slug == "CLKD")
			return &CLKD_artwork_240;

		if (slug == "Att")
			return &Att_artwork_240;

		if (slug == "AD")
			return &AD_artwork_240;

		if (slug == "Sequant")
			return &Sequant_artwork_240;

		if (slug == "Switch14")
			return &Switch14_artwork_240;

		if (slug == "Seq4")
			return &Seq4_artwork_240;

		if (slug == "Octave")
			return &Octave_artwork_240;

		if (slug == "MNMX")
			return &MNMX_artwork_240;

		if (slug == "LPF")
			return &LPF_artwork_240;

		if (slug == "Verb")
			return &Verb_artwork_240;

		if (slug == "Switch41")
			return &Switch41_artwork_240;

		if (slug == "Seq8")
			return &Seq8_artwork_240;

		if (slug == "Quant")
			return &Quant_artwork_240;

		if (slug == "Prob8")
			return &Prob8_artwork_240;

		if (slug == "Source")
			return &Source_artwork_240;

		if (slug == "Slew")
			return &Slew_artwork_240;

		if (slug == "PitchShift")
			return &PitchShift_artwork_240;

		if (slug == "Noise")
			return &Noise_artwork_240;

		if (slug == "KPLS")
			return &KPLS_artwork_240;

		if (slug == "HPF")
			return &HPF_artwork_240;

		if (slug == "Gate")
			return &Gate_artwork_240;

		if (slug == "Detune")
			return &Detune_artwork_240;

		if (slug == "BPF")
			return &BPF_artwork_240;

		if (slug == "PanelMed")
			return &PanelMed_artwork_240;

		if (slug == "ComplexEG")
			return &ComplexEG_artwork_240;

		if (slug == "Pan")
			return &Pan_artwork_240;

		if (slug == "MultiLFO")
			return &MultiLFO_artwork_240;

		if (slug == "Follow")
			return &Follow_artwork_240;

		if (slug == "FM")
			return &FM_artwork_240;

		if (slug == "Drum")
			return &Drum_artwork_240;

		if (slug == "Djembe")
			return &Djembe_artwork_240;

		if (slug == "Atvert2")
			return &Atvert2_artwork_240;

		if (slug == "StMix")
			return &StMix_artwork_240;

		if (slug == "InfOsc")
			return &InfOsc_artwork_240;

		if (slug == "SMR")
			return &SMR_artwork_240;

		if (slug == "EnOsc")
			return &EnOsc_artwork_240;

		if (slug == "BuffMult")
			return &BuffMult_artwork_240;

		return nullptr;
	}
};
