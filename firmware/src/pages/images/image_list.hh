#pragma once
#include "lvgl/lvgl.h"
#include <string_view>

#if defined(USE_FEWER_MODULES) //&& USE_FEWER_MODULES == 1
#include "image_list_short.hh"
#else

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(Freeverb_artwork_240);
LV_IMG_DECLARE(Freeverb_artwork_120);
LV_IMG_DECLARE(STS_artwork_240);
LV_IMG_DECLARE(STS_artwork_120);
LV_IMG_DECLARE(VCAM_artwork_240);
LV_IMG_DECLARE(VCAM_artwork_120);
LV_IMG_DECLARE(Tapo_artwork_240);
LV_IMG_DECLARE(Tapo_artwork_120);
LV_IMG_DECLARE(SISM_artwork_240);
LV_IMG_DECLARE(SISM_artwork_120);
LV_IMG_DECLARE(SCM_artwork_240);
LV_IMG_DECLARE(SCM_artwork_120);
LV_IMG_DECLARE(RCD_artwork_240);
LV_IMG_DECLARE(RCD_artwork_120);
LV_IMG_DECLARE(RCDBO_artwork_240);
LV_IMG_DECLARE(RCDBO_artwork_120);
LV_IMG_DECLARE(QPLFO_artwork_240);
LV_IMG_DECLARE(QPLFO_artwork_120);
LV_IMG_DECLARE(QCD_artwork_240);
LV_IMG_DECLARE(QCD_artwork_120);
LV_IMG_DECLARE(QCDEXP_artwork_240);
LV_IMG_DECLARE(QCDEXP_artwork_120);
LV_IMG_DECLARE(PI_artwork_240);
LV_IMG_DECLARE(PI_artwork_120);
LV_IMG_DECLARE(PIExp_artwork_240);
LV_IMG_DECLARE(PIExp_artwork_120);
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(PEG_artwork_120);
LV_IMG_DECLARE(LIO_artwork_240);
LV_IMG_DECLARE(LIO_artwork_120);
LV_IMG_DECLARE(L4_artwork_240);
LV_IMG_DECLARE(L4_artwork_120);
LV_IMG_DECLARE(L4Q_artwork_240);
LV_IMG_DECLARE(L4Q_artwork_120);
LV_IMG_DECLARE(DLD_artwork_240);
LV_IMG_DECLARE(DLD_artwork_120);
LV_IMG_DECLARE(SH_artwork_240);
LV_IMG_DECLARE(SH_artwork_120);
LV_IMG_DECLARE(GRev_artwork_240);
LV_IMG_DECLARE(GRev_artwork_120);
LV_IMG_DECLARE(ADEnv_artwork_240);
LV_IMG_DECLARE(ADEnv_artwork_120);
LV_IMG_DECLARE(VCA_artwork_240);
LV_IMG_DECLARE(VCA_artwork_120);
LV_IMG_DECLARE(Shift_artwork_240);
LV_IMG_DECLARE(Shift_artwork_120);
LV_IMG_DECLARE(Send_artwork_240);
LV_IMG_DECLARE(Send_artwork_120);
LV_IMG_DECLARE(Mixer_artwork_240);
LV_IMG_DECLARE(Mixer_artwork_120);
LV_IMG_DECLARE(Logic_artwork_240);
LV_IMG_DECLARE(Logic_artwork_120);
LV_IMG_DECLARE(LPG_artwork_240);
LV_IMG_DECLARE(LPG_artwork_120);
LV_IMG_DECLARE(LFO_artwork_240);
LV_IMG_DECLARE(LFO_artwork_120);
LV_IMG_DECLARE(Gate8_artwork_240);
LV_IMG_DECLARE(Gate8_artwork_120);
LV_IMG_DECLARE(Gate32_artwork_240);
LV_IMG_DECLARE(Gate32_artwork_120);
LV_IMG_DECLARE(Fade_artwork_240);
LV_IMG_DECLARE(Fade_artwork_120);
LV_IMG_DECLARE(FadeDelay_artwork_240);
LV_IMG_DECLARE(FadeDelay_artwork_120);
LV_IMG_DECLARE(Comp_artwork_240);
LV_IMG_DECLARE(Comp_artwork_120);
LV_IMG_DECLARE(CLKM_artwork_240);
LV_IMG_DECLARE(CLKM_artwork_120);
LV_IMG_DECLARE(CLKD_artwork_240);
LV_IMG_DECLARE(CLKD_artwork_120);
LV_IMG_DECLARE(Att_artwork_240);
LV_IMG_DECLARE(Att_artwork_120);
LV_IMG_DECLARE(Sequant_artwork_240);
LV_IMG_DECLARE(Sequant_artwork_120);
LV_IMG_DECLARE(Switch14_artwork_240);
LV_IMG_DECLARE(Switch14_artwork_120);
LV_IMG_DECLARE(Seq4_artwork_240);
LV_IMG_DECLARE(Seq4_artwork_120);
LV_IMG_DECLARE(Octave_artwork_240);
LV_IMG_DECLARE(Octave_artwork_120);
LV_IMG_DECLARE(MNMX_artwork_240);
LV_IMG_DECLARE(MNMX_artwork_120);
LV_IMG_DECLARE(LPF_artwork_240);
LV_IMG_DECLARE(LPF_artwork_120);
LV_IMG_DECLARE(Verb_artwork_240);
LV_IMG_DECLARE(Verb_artwork_120);
LV_IMG_DECLARE(Switch41_artwork_240);
LV_IMG_DECLARE(Switch41_artwork_120);
LV_IMG_DECLARE(Seq8_artwork_240);
LV_IMG_DECLARE(Seq8_artwork_120);
LV_IMG_DECLARE(Quant_artwork_240);
LV_IMG_DECLARE(Quant_artwork_120);
LV_IMG_DECLARE(Prob8_artwork_240);
LV_IMG_DECLARE(Prob8_artwork_120);
LV_IMG_DECLARE(Source_artwork_240);
LV_IMG_DECLARE(Source_artwork_120);
LV_IMG_DECLARE(Slew_artwork_240);
LV_IMG_DECLARE(Slew_artwork_120);
LV_IMG_DECLARE(PitchShift_artwork_240);
LV_IMG_DECLARE(PitchShift_artwork_120);
LV_IMG_DECLARE(Noise_artwork_240);
LV_IMG_DECLARE(Noise_artwork_120);
LV_IMG_DECLARE(KPLS_artwork_240);
LV_IMG_DECLARE(KPLS_artwork_120);
LV_IMG_DECLARE(HPF_artwork_240);
LV_IMG_DECLARE(HPF_artwork_120);
LV_IMG_DECLARE(Gate_artwork_240);
LV_IMG_DECLARE(Gate_artwork_120);
LV_IMG_DECLARE(Detune_artwork_240);
LV_IMG_DECLARE(Detune_artwork_120);
LV_IMG_DECLARE(BPF_artwork_240);
LV_IMG_DECLARE(BPF_artwork_120);
LV_IMG_DECLARE(ComplexEG_artwork_240);
LV_IMG_DECLARE(ComplexEG_artwork_120);
LV_IMG_DECLARE(Pan_artwork_240);
LV_IMG_DECLARE(Pan_artwork_120);
LV_IMG_DECLARE(MultiLFO_artwork_240);
LV_IMG_DECLARE(MultiLFO_artwork_120);
LV_IMG_DECLARE(Follow_artwork_240);
LV_IMG_DECLARE(Follow_artwork_120);
LV_IMG_DECLARE(FM_artwork_240);
LV_IMG_DECLARE(FM_artwork_120);
LV_IMG_DECLARE(Drum_artwork_240);
LV_IMG_DECLARE(Drum_artwork_120);
LV_IMG_DECLARE(Djembe_artwork_240);
LV_IMG_DECLARE(Djembe_artwork_120);
LV_IMG_DECLARE(Atvert2_artwork_240);
LV_IMG_DECLARE(Atvert2_artwork_120);
LV_IMG_DECLARE(StMix_artwork_240);
LV_IMG_DECLARE(StMix_artwork_120);
LV_IMG_DECLARE(InfOsc_artwork_240);
LV_IMG_DECLARE(InfOsc_artwork_120);
LV_IMG_DECLARE(SMR_artwork_240);
LV_IMG_DECLARE(SMR_artwork_120);
LV_IMG_DECLARE(EnOsc_artwork_240);
LV_IMG_DECLARE(EnOsc_artwork_120);
LV_IMG_DECLARE(BuffMult_artwork_240);
LV_IMG_DECLARE(BuffMult_artwork_120);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug, size_t height = 240) {
		// SLUG TO IMAGE HERE

		if (slug == "Freeverb")
			return (height == 240) ? &Freeverb_artwork_240 : &Freeverb_artwork_120;

		if (slug == "STS")
			return (height == 240) ? &STS_artwork_240 : &STS_artwork_120;

		if (slug == "VCAM")
			return (height == 240) ? &VCAM_artwork_240 : &VCAM_artwork_120;

		if (slug == "Tapo")
			return (height == 240) ? &Tapo_artwork_240 : &Tapo_artwork_120;

		if (slug == "SISM")
			return (height == 240) ? &SISM_artwork_240 : &SISM_artwork_120;

		if (slug == "SCM")
			return (height == 240) ? &SCM_artwork_240 : &SCM_artwork_120;

		if (slug == "RCD")
			return (height == 240) ? &RCD_artwork_240 : &RCD_artwork_120;

		if (slug == "RCDBO")
			return (height == 240) ? &RCDBO_artwork_240 : &RCDBO_artwork_120;

		if (slug == "QPLFO")
			return (height == 240) ? &QPLFO_artwork_240 : &QPLFO_artwork_120;

		if (slug == "QCD")
			return (height == 240) ? &QCD_artwork_240 : &QCD_artwork_120;

		if (slug == "QCDEXP")
			return (height == 240) ? &QCDEXP_artwork_240 : &QCDEXP_artwork_120;

		if (slug == "PI")
			return (height == 240) ? &PI_artwork_240 : &PI_artwork_120;

		if (slug == "PIExp")
			return (height == 240) ? &PIExp_artwork_240 : &PIExp_artwork_120;

		if (slug == "PEG")
			return (height == 240) ? &PEG_artwork_240 : &PEG_artwork_120;

		if (slug == "LIO")
			return (height == 240) ? &LIO_artwork_240 : &LIO_artwork_120;

		if (slug == "L4")
			return (height == 240) ? &L4_artwork_240 : &L4_artwork_120;

		if (slug == "L4Q")
			return (height == 240) ? &L4Q_artwork_240 : &L4Q_artwork_120;

		if (slug == "DLD")
			return (height == 240) ? &DLD_artwork_240 : &DLD_artwork_120;

		if (slug == "SH")
			return (height == 240) ? &SH_artwork_240 : &SH_artwork_120;

		if (slug == "GRev")
			return (height == 240) ? &GRev_artwork_240 : &GRev_artwork_120;

		if (slug == "ADEnv")
			return (height == 240) ? &ADEnv_artwork_240 : &ADEnv_artwork_120;

		if (slug == "VCA")
			return (height == 240) ? &VCA_artwork_240 : &VCA_artwork_120;

		if (slug == "Shift")
			return (height == 240) ? &Shift_artwork_240 : &Shift_artwork_120;

		if (slug == "Send")
			return (height == 240) ? &Send_artwork_240 : &Send_artwork_120;

		if (slug == "Mixer")
			return (height == 240) ? &Mixer_artwork_240 : &Mixer_artwork_120;

		if (slug == "Logic")
			return (height == 240) ? &Logic_artwork_240 : &Logic_artwork_120;

		if (slug == "LPG")
			return (height == 240) ? &LPG_artwork_240 : &LPG_artwork_120;

		if (slug == "LFO")
			return (height == 240) ? &LFO_artwork_240 : &LFO_artwork_120;

		if (slug == "Gate8")
			return (height == 240) ? &Gate8_artwork_240 : &Gate8_artwork_120;

		if (slug == "Gate32")
			return (height == 240) ? &Gate32_artwork_240 : &Gate32_artwork_120;

		if (slug == "Fade")
			return (height == 240) ? &Fade_artwork_240 : &Fade_artwork_120;

		if (slug == "FadeDelay")
			return (height == 240) ? &FadeDelay_artwork_240 : &FadeDelay_artwork_120;

		if (slug == "Comp")
			return (height == 240) ? &Comp_artwork_240 : &Comp_artwork_120;

		if (slug == "CLKM")
			return (height == 240) ? &CLKM_artwork_240 : &CLKM_artwork_120;

		if (slug == "CLKD")
			return (height == 240) ? &CLKD_artwork_240 : &CLKD_artwork_120;

		if (slug == "Att")
			return (height == 240) ? &Att_artwork_240 : &Att_artwork_120;

		if (slug == "Sequant")
			return (height == 240) ? &Sequant_artwork_240 : &Sequant_artwork_120;

		if (slug == "Switch14")
			return (height == 240) ? &Switch14_artwork_240 : &Switch14_artwork_120;

		if (slug == "Seq4")
			return (height == 240) ? &Seq4_artwork_240 : &Seq4_artwork_120;

		if (slug == "Octave")
			return (height == 240) ? &Octave_artwork_240 : &Octave_artwork_120;

		if (slug == "MNMX")
			return (height == 240) ? &MNMX_artwork_240 : &MNMX_artwork_120;

		if (slug == "LPF")
			return (height == 240) ? &LPF_artwork_240 : &LPF_artwork_120;

		if (slug == "Verb")
			return (height == 240) ? &Verb_artwork_240 : &Verb_artwork_120;

		if (slug == "Switch41")
			return (height == 240) ? &Switch41_artwork_240 : &Switch41_artwork_120;

		if (slug == "Seq8")
			return (height == 240) ? &Seq8_artwork_240 : &Seq8_artwork_120;

		if (slug == "Quant")
			return (height == 240) ? &Quant_artwork_240 : &Quant_artwork_120;

		if (slug == "Prob8")
			return (height == 240) ? &Prob8_artwork_240 : &Prob8_artwork_120;

		if (slug == "Source")
			return (height == 240) ? &Source_artwork_240 : &Source_artwork_120;

		if (slug == "Slew")
			return (height == 240) ? &Slew_artwork_240 : &Slew_artwork_120;

		if (slug == "PitchShift")
			return (height == 240) ? &PitchShift_artwork_240 : &PitchShift_artwork_120;

		if (slug == "Noise")
			return (height == 240) ? &Noise_artwork_240 : &Noise_artwork_120;

		if (slug == "KPLS")
			return (height == 240) ? &KPLS_artwork_240 : &KPLS_artwork_120;

		if (slug == "HPF")
			return (height == 240) ? &HPF_artwork_240 : &HPF_artwork_120;

		if (slug == "Gate")
			return (height == 240) ? &Gate_artwork_240 : &Gate_artwork_120;

		if (slug == "Detune")
			return (height == 240) ? &Detune_artwork_240 : &Detune_artwork_120;

		if (slug == "BPF")
			return (height == 240) ? &BPF_artwork_240 : &BPF_artwork_120;

		if (slug == "ComplexEG")
			return (height == 240) ? &ComplexEG_artwork_240 : &ComplexEG_artwork_120;

		if (slug == "Pan")
			return (height == 240) ? &Pan_artwork_240 : &Pan_artwork_120;

		if (slug == "MultiLFO")
			return (height == 240) ? &MultiLFO_artwork_240 : &MultiLFO_artwork_120;

		if (slug == "Follow")
			return (height == 240) ? &Follow_artwork_240 : &Follow_artwork_120;

		if (slug == "FM")
			return (height == 240) ? &FM_artwork_240 : &FM_artwork_120;

		if (slug == "Drum")
			return (height == 240) ? &Drum_artwork_240 : &Drum_artwork_120;

		if (slug == "Djembe")
			return (height == 240) ? &Djembe_artwork_240 : &Djembe_artwork_120;

		if (slug == "Atvert2")
			return (height == 240) ? &Atvert2_artwork_240 : &Atvert2_artwork_120;

		if (slug == "StMix")
			return (height == 240) ? &StMix_artwork_240 : &StMix_artwork_120;

		if (slug == "InfOsc")
			return (height == 240) ? &InfOsc_artwork_240 : &InfOsc_artwork_120;

		if (slug == "SMR")
			return (height == 240) ? &SMR_artwork_240 : &SMR_artwork_120;

		if (slug == "EnOsc")
			return (height == 240) ? &EnOsc_artwork_240 : &EnOsc_artwork_120;

		if (slug == "BuffMult")
			return (height == 240) ? &BuffMult_artwork_240 : &BuffMult_artwork_120;

		return nullptr;
	}
};

#endif
