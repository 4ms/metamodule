#pragma once
#include "AudibleInstruments/AudibleInstruments_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct ElementsInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Elements"};
	static constexpr std::string_view description{"Pecussion Synthesizer"};
	static constexpr uint32_t width_hp = 34;
	static constexpr std::string_view svg_filename{"res/modules/Elements_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Elements.png"};

	using enum Coords;

	static constexpr std::array<Element, 48> Elements{{
		WhiteMediumKnob{{to_mm<72>(47.58), to_mm<72>(60.35), Center, "Contour", ""}, 0, 1, 1.0f},
		WhiteMediumKnob{{to_mm<72>(114.99), to_mm<72>(60.35), Center, "Bow", ""}, 0, 1, 0.0f},
		RedMediumKnob{{to_mm<72>(182.51), to_mm<72>(60.35), Center, "Blow", ""}, 0, 1, 0.0f},
		RedMediumKnob{{to_mm<72>(250.03), to_mm<72>(60.35), Center, "Strike", ""}, 0, 1, 0.5f},
		WhiteMediumKnob{{to_mm<72>(317.55), to_mm<72>(60.35), Center, "Coarse", ""}, -30, 30, 0.f},
		WhiteMediumKnob{{to_mm<72>(385.07), to_mm<72>(60.35), Center, "Fine", ""}, -2, 2, 0.f},
		WhiteMediumKnob{{to_mm<72>(452.59), to_mm<72>(60.35), Center, "FM", ""}, -1, 1, 0},
		RedLargeKnob{{to_mm<72>(135.71), to_mm<72>(137.31), Center, "Flow", ""}, 0, 1, 0.5f},
		BlueLargeKnob{{to_mm<72>(229.31), to_mm<72>(137.31), Center, "Mallet", ""}, 0, 1, 0.5f},
		WhiteLargeKnob{{to_mm<72>(338.27), to_mm<72>(137.31), Center, "Geometry", ""}, 0, 1, 0.5f},
		WhiteLargeKnob{{to_mm<72>(431.87), to_mm<72>(137.31), Center, "Brightness", ""}, 0, 1, 0.5f},
		WhiteMediumKnob{{to_mm<72>(114.99), to_mm<72>(214.27), Center, "Bow Timbre", ""}, 0, 1, 0.5f},
		RedMediumKnob{{to_mm<72>(182.51), to_mm<72>(214.27), Center, "Blow Timbre", ""}, 0, 1, 0.5f},
		BlueMediumKnob{{to_mm<72>(250.03), to_mm<72>(214.27), Center, "Strike Timbre", ""}, 0, 1, 0.5f},
		WhiteMediumKnob{{to_mm<72>(317.55), to_mm<72>(214.27), Center, "Damping", ""}, 0, 1, 0.5f},
		WhiteMediumKnob{{to_mm<72>(385.07), to_mm<72>(214.27), Center, "Position", ""}, 0, 1, 0.5f},
		WhiteMediumKnob{{to_mm<72>(452.59), to_mm<72>(214.27), Center, "Reverb space", ""}, 0, 2, 0.0f},
		Trimpot{{to_mm<72>(108.81), to_mm<72>(270.97), Center, "Bow Timbre Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(145.66), to_mm<72>(270.97), Center, "Flow Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(182.51), to_mm<72>(270.97), Center, "Blow Timbre Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(219.36), to_mm<72>(270.97), Center, "Mallet Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(256.21), to_mm<72>(270.97), Center, "Strike Timbre Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(311.37), to_mm<72>(270.97), Center, "Damping Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(348.22), to_mm<72>(270.97), Center, "Geometry Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(385.07), to_mm<72>(270.97), Center, "Position Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(421.92), to_mm<72>(270.97), Center, "Brightness Atten", ""}, -1, 1, 0},
		Trimpot{{to_mm<72>(458.77), to_mm<72>(270.97), Center, "Reverb Atten", ""}, -2, 2, 0},
		WhiteMomentary7mm{{to_mm<72>(47.58), to_mm<72>(124.27), Center, "Play", ""}},
		AnalogJackInput4ms{{to_mm<72>(30.49), to_mm<72>(182.75), Center, "V/Oct", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(182.75), Center, "FM", ""}},
		GateJackInput4ms{{to_mm<72>(30.49), to_mm<72>(226.86), Center, "Gate", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(226.86), Center, "Strength", ""}},
		AnalogJackInput4ms{{to_mm<72>(30.49), to_mm<72>(270.97), Center, "Ext IN Blow", ""}},
		AnalogJackInput4ms{{to_mm<72>(64.67), to_mm<72>(270.97), Center, "Ext IN Strike", ""}},
		AnalogJackInput4ms{{to_mm<72>(108.81), to_mm<72>(315.07), Center, "Bow Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(145.66), to_mm<72>(315.07), Center, "Flow CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(182.51), to_mm<72>(315.07), Center, "Blow Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(219.36), to_mm<72>(315.07), Center, "Mallet CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(256.21), to_mm<72>(315.07), Center, "Strike Timbre CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(311.37), to_mm<72>(315.07), Center, "Damping CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(348.22), to_mm<72>(315.07), Center, "Geometry CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(385.07), to_mm<72>(315.07), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(421.92), to_mm<72>(315.07), Center, "Brightness CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(458.77), to_mm<72>(315.07), Center, "Space CV", ""}},
		AnalogJackOutput4ms{{to_mm<72>(30.49), to_mm<72>(315.07), Center, "Out L", ""}},
		AnalogJackOutput4ms{{to_mm<72>(64.67), to_mm<72>(315.07), Center, "Out R", ""}},
		GreenLight{{to_mm<72>(182.51), to_mm<72>(163.87), Center, "ControlExciter LED", ""}},
		RedLight{{to_mm<72>(385.07), to_mm<72>(163.87), Center, "Resonator LED", ""}},
	}};

	enum class Elem {
		ContourKnob,
		BowKnob,
		BlowKnob,
		StrikeKnob,
		CoarseKnob,
		FineKnob,
		FmKnob,
		FlowKnob,
		MalletKnob,
		GeometryKnob,
		BrightnessKnob,
		BowTimbreKnob,
		BlowTimbreKnob,
		StrikeTimbreKnob,
		DampingKnob,
		PositionKnob,
		SpaceKnob,
		BowTimbreAttenKnob,
		FlowAttenKnob,
		BlowTimbreAttenKnob,
		MalletAttenKnob,
		StrikeTimbreAttenKnob,
		DampingAttenKnob,
		GeometryAttenKnob,
		PositionAttenKnob,
		BrightnessAttenKnob,
		SpaceAttenKnob,
		PlayButton,
		V_OctIn,
		FmIn,
		GateIn,
		StrengthIn,
		ExtInBlowIn,
		ExtInStrikeIn,
		BowTimbreCvIn,
		FlowCvIn,
		BlowTimbreCvIn,
		MalletCvIn,
		StrikeTimbreCvIn,
		DampingCvIn,
		GeometryCvIn,
		PositionCvIn,
		BrightnessCvIn,
		SpaceCvIn,
		OutLOut,
		OutROut,
		ControlexciterLedLight,
		ResonatorLedLight,
	};

	// Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)

	enum {
		KnobContour,
		KnobBow,
		KnobBlow,
		KnobStrike,
		KnobCoarse,
		KnobFine,
		KnobFm,
		KnobFlow,
		KnobMallet,
		KnobGeometry,
		KnobBrightness,
		KnobBow_Timbre,
		KnobBlow_Timbre,
		KnobStrike_Timbre,
		KnobDamping,
		KnobPosition,
		KnobSpace,
		KnobBow_Timbre_Atten,
		KnobFlow_Atten,
		KnobBlow_Timbre_Atten,
		KnobMallet_Atten,
		KnobStrike_Timbre_Atten,
		KnobDamping_Atten,
		KnobGeometry_Atten,
		KnobPosition_Atten,
		KnobBrightness_Atten,
		KnobSpace_Atten,
		NumKnobs,
	};

	enum {
		SwitchPlay,
		NumSwitches,
	};

	enum {
		InputV_Oct,
		InputFm,
		InputGate,
		InputStrength,
		InputExt_In_Blow,
		InputExt_In_Strike,
		InputBow_Timbre_Cv,
		InputFlow_Cv,
		InputBlow_Timbre_Cv,
		InputMallet_Cv,
		InputStrike_Timbre_Cv,
		InputDamping_Cv,
		InputGeometry_Cv,
		InputPosition_Cv,
		InputBrightness_Cv,
		InputSpace_Cv,
		NumInJacks,
	};

	enum {
		OutputOut_L,
		OutputOut_R,
		NumOutJacks,
	};

	enum {
		LedControlexciter_Led,
		LedResonator_Led,
		NumDiscreteLeds,
	};
};
} // namespace MetaModule
