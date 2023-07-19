#pragma once
#include "lvgl.h"
#include <string_view>

#if defined(USE_FEWER_MODULES) //&& USE_FEWER_MODULES == 1
#include "image_list_short.hh"
#else

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(Warps_artwork_240);
LV_IMG_DECLARE(Veils_artwork_240);
LV_IMG_DECLARE(Tides2_artwork_240);
LV_IMG_DECLARE(Tides_artwork_240);
LV_IMG_DECLARE(Streams_artwork_240);
LV_IMG_DECLARE(Stages_artwork_240);
LV_IMG_DECLARE(Shelves_artwork_240);
LV_IMG_DECLARE(Sheep_artwork_240);
LV_IMG_DECLARE(Shades_artwork_240);
LV_IMG_DECLARE(Ripples_artwork_240);
LV_IMG_DECLARE(Rings_artwork_240);
LV_IMG_DECLARE(Plaits_artwork_240);
LV_IMG_DECLARE(Peaks_artwork_240);
LV_IMG_DECLARE(Marbles_artwork_240);
LV_IMG_DECLARE(Links_artwork_240);
LV_IMG_DECLARE(Kinks_artwork_240);
LV_IMG_DECLARE(Frames_artwork_240);
LV_IMG_DECLARE(Elements_artwork_240);
LV_IMG_DECLARE(Clouds_artwork_240);
LV_IMG_DECLARE(Branches_artwork_240);
LV_IMG_DECLARE(Blinds_artwork_240);
LV_IMG_DECLARE(StereoStrip_artwork_240);
LV_IMG_DECLARE(SlewLimiter_artwork_240);
LV_IMG_DECLARE(SamplingModulator_artwork_240);
LV_IMG_DECLARE(STMix_artwork_240);
LV_IMG_DECLARE(Rampage_artwork_240);
LV_IMG_DECLARE(PonyVCO_artwork_240);
LV_IMG_DECLARE(Percall_artwork_240);
LV_IMG_DECLARE(NoisePlethora_artwork_240);
LV_IMG_DECLARE(Muxlicer_artwork_240);
LV_IMG_DECLARE(MotionMTR_artwork_240);
LV_IMG_DECLARE(Morphader_artwork_240);
LV_IMG_DECLARE(Mex_artwork_240);
LV_IMG_DECLARE(Kickall_artwork_240);
LV_IMG_DECLARE(HexmixVCA_artwork_240);
LV_IMG_DECLARE(ChoppingKinky_artwork_240);
LV_IMG_DECLARE(ADSR_artwork_240);
LV_IMG_DECLARE(ABC_artwork_240);
LV_IMG_DECLARE(SpringReverb_artwork_240);
LV_IMG_DECLARE(DEV_artwork_240);
LV_IMG_DECLARE(SHEV_artwork_240);
LV_IMG_DECLARE(ENVVCA_artwork_240);
LV_IMG_DECLARE(Freeverb_artwork_240);
LV_IMG_DECLARE(STS_artwork_240);
LV_IMG_DECLARE(VCAM_artwork_240);
LV_IMG_DECLARE(Tapo_artwork_240);
LV_IMG_DECLARE(SISM_artwork_240);
LV_IMG_DECLARE(SCM_artwork_240);
LV_IMG_DECLARE(RCD_artwork_240);
LV_IMG_DECLARE(QPLFO_artwork_240);
LV_IMG_DECLARE(QCD_artwork_240);
LV_IMG_DECLARE(PI_artwork_240);
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(LIO_artwork_240);
LV_IMG_DECLARE(L4_artwork_240);
LV_IMG_DECLARE(DLD_artwork_240);
LV_IMG_DECLARE(SH_artwork_240);
LV_IMG_DECLARE(GRev_artwork_240);
LV_IMG_DECLARE(ADEnv_artwork_240);
LV_IMG_DECLARE(Shift_artwork_240);
LV_IMG_DECLARE(Mixer4_artwork_240);
LV_IMG_DECLARE(LPG_artwork_240);
LV_IMG_DECLARE(Gate8_artwork_240);
LV_IMG_DECLARE(Gate32_artwork_240);
LV_IMG_DECLARE(Fade_artwork_240);
LV_IMG_DECLARE(Comp_artwork_240);
LV_IMG_DECLARE(CLKM_artwork_240);
LV_IMG_DECLARE(CLKD_artwork_240);
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
LV_IMG_DECLARE(DualAtenuverter_artwork_240);
LV_IMG_DECLARE(Braids_artwork_240);
LV_IMG_DECLARE(EvenVCO_artwork_240);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug) {
		// SLUG TO IMAGE HERE

		if (slug == "Warps")
			return &Warps_artwork_240;

		if (slug == "Veils")
			return &Veils_artwork_240;

		if (slug == "Tides2")
			return &Tides2_artwork_240;

		if (slug == "Tides")
			return &Tides_artwork_240;

		if (slug == "Streams")
			return &Streams_artwork_240;

		if (slug == "Stages")
			return &Stages_artwork_240;

		if (slug == "Shelves")
			return &Shelves_artwork_240;

		if (slug == "Sheep")
			return &Sheep_artwork_240;

		if (slug == "Shades")
			return &Shades_artwork_240;

		if (slug == "Ripples")
			return &Ripples_artwork_240;

		if (slug == "Rings")
			return &Rings_artwork_240;

		if (slug == "Plaits")
			return &Plaits_artwork_240;

		if (slug == "Peaks")
			return &Peaks_artwork_240;

		if (slug == "Marbles")
			return &Marbles_artwork_240;

		if (slug == "Links")
			return &Links_artwork_240;

		if (slug == "Kinks")
			return &Kinks_artwork_240;

		if (slug == "Frames")
			return &Frames_artwork_240;

		if (slug == "Elements")
			return &Elements_artwork_240;

		if (slug == "Clouds")
			return &Clouds_artwork_240;

		if (slug == "Branches")
			return &Branches_artwork_240;

		if (slug == "Blinds")
			return &Blinds_artwork_240;

		if (slug == "StereoStrip")
			return &StereoStrip_artwork_240;

		if (slug == "SlewLimiter")
			return &SlewLimiter_artwork_240;

		if (slug == "SamplingModulator")
			return &SamplingModulator_artwork_240;

		if (slug == "STMix")
			return &STMix_artwork_240;

		if (slug == "Rampage")
			return &Rampage_artwork_240;

		if (slug == "PonyVCO")
			return &PonyVCO_artwork_240;

		if (slug == "Percall")
			return &Percall_artwork_240;

		if (slug == "NoisePlethora")
			return &NoisePlethora_artwork_240;

		if (slug == "Muxlicer")
			return &Muxlicer_artwork_240;

		if (slug == "MotionMTR")
			return &MotionMTR_artwork_240;

		if (slug == "Morphader")
			return &Morphader_artwork_240;

		if (slug == "Mex")
			return &Mex_artwork_240;

		if (slug == "Kickall")
			return &Kickall_artwork_240;

		if (slug == "HexmixVCA")
			return &HexmixVCA_artwork_240;

		if (slug == "ChoppingKinky")
			return &ChoppingKinky_artwork_240;

		if (slug == "Mixer4")
			return &Mixer4_artwork_240;

		if (slug == "ADSR")
			return &ADSR_artwork_240;

		if (slug == "ABC")
			return &ABC_artwork_240;

		if (slug == "SpringReverb")
			return &SpringReverb_artwork_240;

		if (slug == "DEV")
			return &DEV_artwork_240;

		if (slug == "SHEV")
			return &SHEV_artwork_240;

		if (slug == "ENVVCA")
			return &ENVVCA_artwork_240;

		if (slug == "Freeverb")
			return &Freeverb_artwork_240;

		if (slug == "STS")
			return &STS_artwork_240;

		if (slug == "VCAM")
			return &VCAM_artwork_240;

		if (slug == "Tapo")
			return &Tapo_artwork_240;

		if (slug == "SISM")
			return &SISM_artwork_240;

		if (slug == "SCM")
			return &SCM_artwork_240;

		if (slug == "RCD")
			return &RCD_artwork_240;

		if (slug == "QPLFO")
			return &QPLFO_artwork_240;

		if (slug == "QCD")
			return &QCD_artwork_240;

		if (slug == "PI")
			return &PI_artwork_240;

		if (slug == "PEG")
			return &PEG_artwork_240;

		if (slug == "LIO")
			return &LIO_artwork_240;

		if (slug == "L4")
			return &L4_artwork_240;

		if (slug == "DLD")
			return &DLD_artwork_240;

		if (slug == "SH")
			return &SH_artwork_240;

		if (slug == "GRev")
			return &GRev_artwork_240;

		if (slug == "ADEnv")
			return &ADEnv_artwork_240;

		if (slug == "Shift")
			return &Shift_artwork_240;

		if (slug == "LPG")
			return &LPG_artwork_240;

		if (slug == "Gate8")
			return &Gate8_artwork_240;

		if (slug == "Gate32")
			return &Gate32_artwork_240;

		if (slug == "Fade")
			return &Fade_artwork_240;

		if (slug == "Comp")
			return &Comp_artwork_240;

		if (slug == "CLKM")
			return &CLKM_artwork_240;

		if (slug == "CLKD")
			return &CLKD_artwork_240;

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

		if (slug == "DualAtenuverter")
			return &DualAtenuverter_artwork_240;

		if (slug == "Braids")
			return &Braids_artwork_240;

		if (slug == "EvenVCO")
			return &EvenVCO_artwork_240;

		if (slug == "ENVVCA")
			return &ENVVCA_artwork_240;

		return nullptr;
	}
};

#endif
