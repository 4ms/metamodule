#pragma once
#include "lvgl.h"
#include <string_view>

#if defined(USE_FEWER_MODULES) //&& USE_FEWER_MODULES == 1
#include "image_list_short.hh"
#else

extern "C" {
// DECLARE HERE
LV_IMG_DECLARE(Warps_artwork_240);
LV_IMG_DECLARE(Warps_artwork_120);
LV_IMG_DECLARE(Veils_artwork_240);
LV_IMG_DECLARE(Veils_artwork_120);
LV_IMG_DECLARE(Tides2_artwork_240);
LV_IMG_DECLARE(Tides2_artwork_120);
LV_IMG_DECLARE(Tides_artwork_240);
LV_IMG_DECLARE(Tides_artwork_120);
LV_IMG_DECLARE(Streams_artwork_240);
LV_IMG_DECLARE(Streams_artwork_120);
LV_IMG_DECLARE(Stages_artwork_240);
LV_IMG_DECLARE(Stages_artwork_120);
LV_IMG_DECLARE(Shelves_artwork_240);
LV_IMG_DECLARE(Shelves_artwork_120);
LV_IMG_DECLARE(Sheep_artwork_240);
LV_IMG_DECLARE(Sheep_artwork_120);
LV_IMG_DECLARE(Shades_artwork_240);
LV_IMG_DECLARE(Shades_artwork_120);
LV_IMG_DECLARE(Ripples_artwork_240);
LV_IMG_DECLARE(Ripples_artwork_120);
LV_IMG_DECLARE(Rings_artwork_240);
LV_IMG_DECLARE(Rings_artwork_120);
LV_IMG_DECLARE(Plaits_artwork_240);
LV_IMG_DECLARE(Plaits_artwork_120);
LV_IMG_DECLARE(Peaks_artwork_240);
LV_IMG_DECLARE(Peaks_artwork_120);
LV_IMG_DECLARE(Marbles_artwork_240);
LV_IMG_DECLARE(Marbles_artwork_120);
LV_IMG_DECLARE(Links_artwork_240);
LV_IMG_DECLARE(Links_artwork_120);
LV_IMG_DECLARE(Kinks_artwork_240);
LV_IMG_DECLARE(Kinks_artwork_120);
LV_IMG_DECLARE(Frames_artwork_240);
LV_IMG_DECLARE(Frames_artwork_120);
LV_IMG_DECLARE(Elements_artwork_240);
LV_IMG_DECLARE(Elements_artwork_120);
LV_IMG_DECLARE(Clouds_artwork_240);
LV_IMG_DECLARE(Clouds_artwork_120);
LV_IMG_DECLARE(Branches_artwork_240);
LV_IMG_DECLARE(Branches_artwork_120);
LV_IMG_DECLARE(Blinds_artwork_240);
LV_IMG_DECLARE(Blinds_artwork_120);
LV_IMG_DECLARE(StereoStrip_artwork_240);
LV_IMG_DECLARE(StereoStrip_artwork_120);
LV_IMG_DECLARE(SlewLimiter_artwork_240);
LV_IMG_DECLARE(SlewLimiter_artwork_120);
LV_IMG_DECLARE(SamplingModulator_artwork_240);
LV_IMG_DECLARE(SamplingModulator_artwork_120);
LV_IMG_DECLARE(STMix_artwork_240);
LV_IMG_DECLARE(STMix_artwork_120);
LV_IMG_DECLARE(Rampage_artwork_240);
LV_IMG_DECLARE(Rampage_artwork_120);
LV_IMG_DECLARE(PonyVCO_artwork_240);
LV_IMG_DECLARE(PonyVCO_artwork_120);
LV_IMG_DECLARE(Percall_artwork_240);
LV_IMG_DECLARE(Percall_artwork_120);
LV_IMG_DECLARE(NoisePlethora_artwork_240);
LV_IMG_DECLARE(NoisePlethora_artwork_120);
LV_IMG_DECLARE(Muxlicer_artwork_240);
LV_IMG_DECLARE(Muxlicer_artwork_120);
LV_IMG_DECLARE(MotionMTR_artwork_240);
LV_IMG_DECLARE(MotionMTR_artwork_120);
LV_IMG_DECLARE(Morphader_artwork_240);
LV_IMG_DECLARE(Morphader_artwork_120);
LV_IMG_DECLARE(Mex_artwork_240);
LV_IMG_DECLARE(Mex_artwork_120);
LV_IMG_DECLARE(Kickall_artwork_240);
LV_IMG_DECLARE(Kickall_artwork_120);
LV_IMG_DECLARE(HexmixVCA_artwork_240);
LV_IMG_DECLARE(HexmixVCA_artwork_120);
LV_IMG_DECLARE(ChoppingKinky_artwork_240);
LV_IMG_DECLARE(ChoppingKinky_artwork_120);
LV_IMG_DECLARE(ADSR_artwork_240);
LV_IMG_DECLARE(ADSR_artwork_120);
LV_IMG_DECLARE(ABC_artwork_240);
LV_IMG_DECLARE(ABC_artwork_120);
LV_IMG_DECLARE(SpringReverb_artwork_240);
LV_IMG_DECLARE(SpringReverb_artwork_120);
LV_IMG_DECLARE(DEV_artwork_240);
LV_IMG_DECLARE(DEV_artwork_120);
LV_IMG_DECLARE(SHEV_artwork_240);
LV_IMG_DECLARE(SHEV_artwork_120);
LV_IMG_DECLARE(ENVVCA_artwork_240);
LV_IMG_DECLARE(ENVVCA_artwork_120);
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
LV_IMG_DECLARE(QPLFO_artwork_240);
LV_IMG_DECLARE(QPLFO_artwork_120);
LV_IMG_DECLARE(QCD_artwork_240);
LV_IMG_DECLARE(QCD_artwork_120);
LV_IMG_DECLARE(PI_artwork_240);
LV_IMG_DECLARE(PI_artwork_120);
LV_IMG_DECLARE(PEG_artwork_240);
LV_IMG_DECLARE(PEG_artwork_120);
LV_IMG_DECLARE(LIO_artwork_240);
LV_IMG_DECLARE(LIO_artwork_120);
LV_IMG_DECLARE(L4_artwork_240);
LV_IMG_DECLARE(L4_artwork_120);
LV_IMG_DECLARE(DLD_artwork_240);
LV_IMG_DECLARE(DLD_artwork_120);
LV_IMG_DECLARE(SH_artwork_240);
LV_IMG_DECLARE(SH_artwork_120);
LV_IMG_DECLARE(GRev_artwork_240);
LV_IMG_DECLARE(GRev_artwork_120);
LV_IMG_DECLARE(ADEnv_artwork_240);
LV_IMG_DECLARE(ADEnv_artwork_120);
LV_IMG_DECLARE(Shift_artwork_240);
LV_IMG_DECLARE(Shift_artwork_120);
LV_IMG_DECLARE(Mixer4_artwork_240);
LV_IMG_DECLARE(Mixer4_artwork_120);
LV_IMG_DECLARE(LPG_artwork_240);
LV_IMG_DECLARE(LPG_artwork_120);
LV_IMG_DECLARE(Gate8_artwork_240);
LV_IMG_DECLARE(Gate8_artwork_120);
LV_IMG_DECLARE(Gate32_artwork_240);
LV_IMG_DECLARE(Gate32_artwork_120);
LV_IMG_DECLARE(Fade_artwork_240);
LV_IMG_DECLARE(Fade_artwork_120);
LV_IMG_DECLARE(Comp_artwork_240);
LV_IMG_DECLARE(Comp_artwork_120);
LV_IMG_DECLARE(CLKM_artwork_240);
LV_IMG_DECLARE(CLKM_artwork_120);
LV_IMG_DECLARE(CLKD_artwork_240);
LV_IMG_DECLARE(CLKD_artwork_120);
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
LV_IMG_DECLARE(DualAtenuverter_artwork_240);
LV_IMG_DECLARE(DualAtenuverter_artwork_120);
LV_IMG_DECLARE(Braids_artwork_240);
LV_IMG_DECLARE(Braids_artwork_120);
LV_IMG_DECLARE(EvenVCO_artwork_240);
LV_IMG_DECLARE(EvenVCO_artwork_120);
}

struct ModuleImages {

	static const lv_img_dsc_t *get_image_by_slug(const std::string_view slug, size_t height = 240) {
		// SLUG TO IMAGE HERE

		if (slug == "Warps")
			return (height == 240) ? &Warps_artwork_240 : &Warps_artwork_120;

		if (slug == "Veils")
			return (height == 240) ? &Veils_artwork_240 : &Veils_artwork_120;

		if (slug == "Tides2")
			return (height == 240) ? &Tides2_artwork_240 : &Tides2_artwork_120;

		if (slug == "Tides")
			return (height == 240) ? &Tides_artwork_240 : &Tides_artwork_120;

		if (slug == "Streams")
			return (height == 240) ? &Streams_artwork_240 : &Streams_artwork_120;

		if (slug == "Stages")
			return (height == 240) ? &Stages_artwork_240 : &Stages_artwork_120;

		if (slug == "Shelves")
			return (height == 240) ? &Shelves_artwork_240 : &Shelves_artwork_120;

		if (slug == "Sheep")
			return (height == 240) ? &Sheep_artwork_240 : &Sheep_artwork_120;

		if (slug == "Shades")
			return (height == 240) ? &Shades_artwork_240 : &Shades_artwork_120;

		if (slug == "Ripples")
			return (height == 240) ? &Ripples_artwork_240 : &Ripples_artwork_120;

		if (slug == "Rings")
			return (height == 240) ? &Rings_artwork_240 : &Rings_artwork_120;

		if (slug == "Plaits")
			return (height == 240) ? &Plaits_artwork_240 : &Plaits_artwork_120;

		if (slug == "Peaks")
			return (height == 240) ? &Peaks_artwork_240 : &Peaks_artwork_120;

		if (slug == "Marbles")
			return (height == 240) ? &Marbles_artwork_240 : &Marbles_artwork_120;

		if (slug == "Links")
			return (height == 240) ? &Links_artwork_240 : &Links_artwork_120;

		if (slug == "Kinks")
			return (height == 240) ? &Kinks_artwork_240 : &Kinks_artwork_120;

		if (slug == "Frames")
			return (height == 240) ? &Frames_artwork_240 : &Frames_artwork_120;

		if (slug == "Elements")
			return (height == 240) ? &Elements_artwork_240 : &Elements_artwork_120;

		if (slug == "Clouds")
			return (height == 240) ? &Clouds_artwork_240 : &Clouds_artwork_120;

		if (slug == "Branches")
			return (height == 240) ? &Branches_artwork_240 : &Branches_artwork_120;

		if (slug == "Blinds")
			return (height == 240) ? &Blinds_artwork_240 : &Blinds_artwork_120;

		if (slug == "StereoStrip")
			return (height == 240) ? &StereoStrip_artwork_240 : &StereoStrip_artwork_120;

		if (slug == "SlewLimiter")
			return (height == 240) ? &SlewLimiter_artwork_240 : &SlewLimiter_artwork_120;

		if (slug == "SamplingModulator")
			return (height == 240) ? &SamplingModulator_artwork_240 : &SamplingModulator_artwork_120;

		if (slug == "STMix")
			return (height == 240) ? &STMix_artwork_240 : &STMix_artwork_120;

		if (slug == "Rampage")
			return (height == 240) ? &Rampage_artwork_240 : &Rampage_artwork_120;

		if (slug == "PonyVCO")
			return (height == 240) ? &PonyVCO_artwork_240 : &PonyVCO_artwork_120;

		if (slug == "Percall")
			return (height == 240) ? &Percall_artwork_240 : &Percall_artwork_120;

		if (slug == "NoisePlethora")
			return (height == 240) ? &NoisePlethora_artwork_240 : &NoisePlethora_artwork_120;

		if (slug == "Muxlicer")
			return (height == 240) ? &Muxlicer_artwork_240 : &Muxlicer_artwork_120;

		if (slug == "MotionMTR")
			return (height == 240) ? &MotionMTR_artwork_240 : &MotionMTR_artwork_120;

		if (slug == "Morphader")
			return (height == 240) ? &Morphader_artwork_240 : &Morphader_artwork_120;

		if (slug == "Mex")
			return (height == 240) ? &Mex_artwork_240 : &Mex_artwork_120;

		if (slug == "Kickall")
			return (height == 240) ? &Kickall_artwork_240 : &Kickall_artwork_120;

		if (slug == "HexmixVCA")
			return (height == 240) ? &HexmixVCA_artwork_240 : &HexmixVCA_artwork_120;

		if (slug == "ChoppingKinky")
			return (height == 240) ? &ChoppingKinky_artwork_240 : &ChoppingKinky_artwork_120;

		if (slug == "Mixer4")
			return (height == 240) ? &Mixer4_artwork_240 : &Mixer4_artwork_120;

		if (slug == "ADSR")
			return (height == 240) ? &ADSR_artwork_240 : &ADSR_artwork_120;

		if (slug == "ABC")
			return (height == 240) ? &ABC_artwork_240 : &ABC_artwork_120;

		if (slug == "SpringReverb")
			return (height == 240) ? &SpringReverb_artwork_240 : &SpringReverb_artwork_120;

		if (slug == "DEV")
			return (height == 240) ? &DEV_artwork_240 : &DEV_artwork_120;

		if (slug == "SHEV")
			return (height == 240) ? &SHEV_artwork_240 : &SHEV_artwork_120;

		if (slug == "ENVVCA")
			return (height == 240) ? &ENVVCA_artwork_240 : &ENVVCA_artwork_120;

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

		if (slug == "QPLFO")
			return (height == 240) ? &QPLFO_artwork_240 : &QPLFO_artwork_120;

		if (slug == "QCD")
			return (height == 240) ? &QCD_artwork_240 : &QCD_artwork_120;

		if (slug == "PI")
			return (height == 240) ? &PI_artwork_240 : &PI_artwork_120;

		if (slug == "PEG")
			return (height == 240) ? &PEG_artwork_240 : &PEG_artwork_120;

		if (slug == "LIO")
			return (height == 240) ? &LIO_artwork_240 : &LIO_artwork_120;

		if (slug == "L4")
			return (height == 240) ? &L4_artwork_240 : &L4_artwork_120;

		if (slug == "DLD")
			return (height == 240) ? &DLD_artwork_240 : &DLD_artwork_120;

		if (slug == "SH")
			return (height == 240) ? &SH_artwork_240 : &SH_artwork_120;

		if (slug == "GRev")
			return (height == 240) ? &GRev_artwork_240 : &GRev_artwork_120;

		if (slug == "ADEnv")
			return (height == 240) ? &ADEnv_artwork_240 : &ADEnv_artwork_120;

		if (slug == "Shift")
			return (height == 240) ? &Shift_artwork_240 : &Shift_artwork_120;

		if (slug == "LPG")
			return (height == 240) ? &LPG_artwork_240 : &LPG_artwork_120;

		if (slug == "Gate8")
			return (height == 240) ? &Gate8_artwork_240 : &Gate8_artwork_120;

		if (slug == "Gate32")
			return (height == 240) ? &Gate32_artwork_240 : &Gate32_artwork_120;

		if (slug == "Fade")
			return (height == 240) ? &Fade_artwork_240 : &Fade_artwork_120;

		if (slug == "Comp")
			return (height == 240) ? &Comp_artwork_240 : &Comp_artwork_120;

		if (slug == "CLKM")
			return (height == 240) ? &CLKM_artwork_240 : &CLKM_artwork_120;

		if (slug == "CLKD")
			return (height == 240) ? &CLKD_artwork_240 : &CLKD_artwork_120;

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

		if (slug == "DualAtenuverter")
			return (height == 240) ? &DualAtenuverter_artwork_240 : &DualAtenuverter_artwork_120;

		if (slug == "Braids")
			return (height == 240) ? &Braids_artwork_240 : &Braids_artwork_120;

		if (slug == "EvenVCO")
			return (height == 240) ? &EvenVCO_artwork_240 : &EvenVCO_artwork_120;

		if (slug == "ENVVCA")
			return (height == 240) ? &ENVVCA_artwork_240 : &ENVVCA_artwork_120;

		return nullptr;
	}
};

#endif
