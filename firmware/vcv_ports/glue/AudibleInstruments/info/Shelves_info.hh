#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include "gcem/include/gcem.hpp"
#include <array>

namespace MetaModule
{
struct ShelvesInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Shelves"};
	static constexpr std::string_view description{"EQ Filter"};
	static constexpr uint32_t width_hp = 18;
	static constexpr std::string_view svg_filename{"res/modules/Shelves_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Shelves.png"};

	using enum Coords;

	static constexpr float kFreqKnobMin = 20.f;
	static constexpr float kFreqKnobMax = 20e3f;
	static constexpr float kGainKnobRange = 18.f;
	static constexpr float kQKnobMin = 0.5f;
	static constexpr float kQKnobMax = 40.f;
	static constexpr float freqMin = gcem::log2(kFreqKnobMin);
	static constexpr float freqMax = gcem::log2(kFreqKnobMax);
	static constexpr float freqInit = (freqMin + freqMax) / 2;
	static constexpr float gainMin = -kGainKnobRange;
	static constexpr float gainMax = kGainKnobRange;
	static constexpr float qMin = gcem::log2(kQKnobMin);
	static constexpr float qMax = gcem::log2(kQKnobMax);
	static constexpr float qInit = (qMin + qMax) / 2;

	static constexpr std::array<Element, 31> Elements{{
		WhiteMediumKnob{{to_mm<72>(117.89), to_mm<72>(55.72), Center, "HS Freq", ""}, freqMin, freqMax, freqInit, "", " Hz", 2.f},
		WhiteMediumKnob{{to_mm<72>(186.25), to_mm<72>(55.72), Center, "HS Gain", ""}, gainMin, gainMax, 0.f, "", " dB"},
		RedMediumKnob{{to_mm<72>(117.89), to_mm<72>(123.23), Center, "P1 Freq", ""}, freqMin, freqMax, freqInit, "", " Hz", 2.f},
		RedMediumKnob{{to_mm<72>(186.25), to_mm<72>(123.23), Center, "P1 Gain", ""}, gainMin, gainMax, 0.f, "", " dB"},
		Trimpot{{to_mm<72>(58.5), to_mm<72>(136.38), Center, "P1 Q", ""}, qMin, qMax, qInit, "", "", 2.f},
		BlueMediumKnob{{to_mm<72>(117.89), to_mm<72>(190.73), Center, "P2 Freq", ""}, freqMin, freqMax, freqInit, "", " Hz", 2.f},
		BlueMediumKnob{{to_mm<72>(186.25), to_mm<72>(190.73), Center, "P2 Gain", ""}, gainMin, gainMax, 0.f, "", " dB"},
		Trimpot{{to_mm<72>(58.5), to_mm<72>(179.85), Center, "P2 Q", ""}, qMin, qMax, qInit, "", "", 2.f},
		WhiteMediumKnob{{to_mm<72>(117.89), to_mm<72>(258.24), Center, "LS Freq", ""}, freqMin, freqMax, freqInit, "", " Hz", 2.f},
		WhiteMediumKnob{{to_mm<72>(186.25), to_mm<72>(258.24), Center, "LS Gain", ""}, gainMin, gainMax, 0.f, "", " dB"},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(49.12), Center, "HS Freq CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.47), to_mm<72>(49.12), Center, "HS Gain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(95.88), Center, "P1 Freq CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.47), to_mm<72>(95.88), Center, "P1 Gain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(136.38), Center, "P1 Q CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(220.35), Center, "P2 Freq CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.47), to_mm<72>(220.35), Center, "P2 Gain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(179.85), Center, "P2 Q CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(267.11), Center, "LS Freq CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.47), to_mm<72>(267.11), Center, "LS Gain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(19.81), to_mm<72>(310.32), Center, "All Freq CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(58.47), to_mm<72>(310.32), Center, "All Gain CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(117.84), to_mm<72>(310.32), Center, "In", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.31), to_mm<72>(49.12), Center, "P1 HP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.31), to_mm<72>(92.76), Center, "P1 BP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.35), to_mm<72>(136.38), Center, "P1 LP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.35), to_mm<72>(179.85), Center, "P2 HP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.31), to_mm<72>(223.46), Center, "P2 BP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(239.31), to_mm<72>(267.11), Center, "P2 LP Out", ""}},
		AnalogJackOutput4ms{{to_mm<72>(186.2), to_mm<72>(310.32), Center, "Out", ""}},
		RedLight{{to_mm<72>(152.04), to_mm<72>(310.32), Center, "Clip Light", ""}},
	}};

	enum class Elem {
		HsFreqKnob,
		HsGainKnob,
		P1FreqKnob,
		P1GainKnob,
		P1QKnob,
		P2FreqKnob,
		P2GainKnob,
		P2QKnob,
		LsFreqKnob,
		LsGainKnob,
		HsFreqCvIn,
		HsGainCvIn,
		P1FreqCvIn,
		P1GainCvIn,
		P1QCvIn,
		P2FreqCvIn,
		P2GainCvIn,
		P2QCvIn,
		LsFreqCvIn,
		LsGainCvIn,
		AllFreqCvIn,
		AllGainCvIn,
		In,
		P1HpOut,
		P1BpOut,
		P1LpOut,
		P2HpOut,
		P2BpOut,
		P2LpOut,
		Out,
		ClipLight,
	};

	// Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)

	enum {
		KnobHs_Freq,
		KnobHs_Gain,
		KnobP1_Freq,
		KnobP1_Gain,
		KnobP1_Q,
		KnobP2_Freq,
		KnobP2_Gain,
		KnobP2_Q,
		KnobLs_Freq,
		KnobLs_Gain,
		NumKnobs,
	};

	enum {
		InputHs_Freq_Cv,
		InputHs_Gain_Cv,
		InputP1_Freq_Cv,
		InputP1_Gain_Cv,
		InputP1_Q_Cv,
		InputP2_Freq_Cv,
		InputP2_Gain_Cv,
		InputP2_Q_Cv,
		InputLs_Freq_Cv,
		InputLs_Gain_Cv,
		InputAll_Freq_Cv,
		InputAll_Gain_Cv,
		InputIn,
		NumInJacks,
	};

	enum {
		OutputP1_Hp_Out,
		OutputP1_Bp_Out,
		OutputP1_Lp_Out,
		OutputP2_Hp_Out,
		OutputP2_Bp_Out,
		OutputP2_Lp_Out,
		OutputOut,
		NumOutJacks,
	};

	enum {
		LedClip_Light,
		NumDiscreteLeds,
	};
};
} // namespace MetaModule
