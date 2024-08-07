#pragma once
#include "CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct MarblesInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Marbles"};
	static constexpr std::string_view description{"Random Sampler"};
	static constexpr uint32_t width_hp = 19;
	static constexpr std::string_view svg_filename{"res/modules/Marbles_artwork.svg"};
	static constexpr std::string_view png_filename{"4ms/fp/Marbles.png"};

	using enum Coords;

	static constexpr std::array<Element, 43> Elements{{
		OrangeButton{{to_mm<72>(46.78), to_mm<72>(50.91), Center, "T Deja Vu", ""}},
		Davies1900hBlackKnob{{to_mm<72>(129.41), to_mm<72>(63.52), Center, "DejaVu x23 WhiteMediumKnob", ""}, 0.5f},
		OrangeButton{{to_mm<72>(212.04), to_mm<72>(50.91), Center, "X Deja Vu", ""}},
		Toggle3posHoriz{{to_mm<72>(19.57), to_mm<72>(110.435), Center, "t Mode Switch x40 1 x40 2 x40 3", ""}},
		DaviesLargeKnob{{to_mm<72>(83.35), to_mm<72>(100.37), Center, "Rate x23 WhiteLargeKnob", ""}, 0.5f},
		DaviesLargeKnob{{to_mm<72>(175.48), to_mm<72>(100.37), Center, "Spread x23 WhiteLargeKnob", ""}, 0.5f},
		Toggle3posHoriz{{to_mm<72>(239.26), to_mm<72>(110.435), Center, "X Mode Switch x40 1 x40 2 x40 3", ""}},
		Davies1900hBlackKnob{{to_mm<72>(26.94), to_mm<72>(165.99), Center, "T Bias x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle3posHoriz{{to_mm<72>(75.41), to_mm<72>(169.675), Center, "Clock Range Switch x40 d4 x40 x1 x40 x4", ""}},
		Davies1900hBlackKnob{{to_mm<72>(129.41), to_mm<72>(145.44), Center, "Length x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle3posHoriz{{to_mm<72>(183.42), to_mm<72>(169.675), Center, "Output Range Switch x40 2 x40 5 x40 5", ""}},
		Davies1900hBlackKnob{{to_mm<72>(231.89), to_mm<72>(165.99), Center, "X Bias x23 WhiteMediumKnob", ""}, 0.5f},
		Davies1900hBlackKnob{{to_mm<72>(89.3), to_mm<72>(209.36), Center, "Jitter x23 WhiteMediumKnob", ""}, 0.5f},
		Toggle2posHoriz{{to_mm<72>(129.42), to_mm<72>(191.225), Center, "Mode Switch x40 Off x40 On", ""}},
		Davies1900hBlackKnob{{to_mm<72>(169.52), to_mm<72>(209.36), Center, "Steps x23 WhiteMediumKnob", ""}, 0.5f},
		AnalogJackInput4ms{{to_mm<72>(26.94), to_mm<72>(232.75), Center, "T Bias CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(231.89), to_mm<72>(232.75), Center, "X Bias CV", ""}},
		GateJackInput4ms{{to_mm<72>(26.94), to_mm<72>(274.14), Center, "T Clock", ""}},
		AnalogJackInput4ms{{to_mm<72>(61.1), to_mm<72>(274.14), Center, "Rate CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(95.26), to_mm<72>(274.14), Center, "Jitter CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(129.41), to_mm<72>(274.14), Center, "Deja Vu CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(163.57), to_mm<72>(274.14), Center, "Steps CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(197.73), to_mm<72>(274.14), Center, "Spread CV", ""}},
		GateJackInput4ms{{to_mm<72>(231.89), to_mm<72>(274.14), Center, "X Clock", ""}},
		GateJackOutput4ms{{to_mm<72>(26.94), to_mm<72>(315.52), Center, "t1", ""}},
		GateJackOutput4ms{{to_mm<72>(61.1), to_mm<72>(315.52), Center, "t2", ""}},
		GateJackOutput4ms{{to_mm<72>(95.26), to_mm<72>(315.52), Center, "t3", ""}},
		AnalogJackOutput4ms{{to_mm<72>(129.41), to_mm<72>(315.52), Center, "Y", ""}},
		AnalogJackOutput4ms{{to_mm<72>(163.57), to_mm<72>(315.52), Center, "X1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(197.73), to_mm<72>(315.52), Center, "X2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(231.89), to_mm<72>(315.52), Center, "X3", ""}},
		RedGreenBlueLight{{to_mm<72>(19.57), to_mm<72>(85.21), Center, "t Mode LED x23 RedGreenYellow", ""}},
		RedGreenBlueLight{{to_mm<72>(239.26), to_mm<72>(85.21), Center, "X Mode LED x23 RedGreenYellow", ""}},
		RedGreenBlueLight{{to_mm<72>(75.41), to_mm<72>(153.52), Center, "Fall LED B", ""}},
		RedGreenBlueLight{{to_mm<72>(183.41), to_mm<72>(153.52), Center, "Fall LED B1", ""}},
		RedGreenBlueLight{{to_mm<72>(129.41), to_mm<72>(216.45), Center, "Fall LED B2", ""}},
		RedGreenBlueLight{{to_mm<72>(17.02), to_mm<72>(297.52), Center, "t1 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(51.18), to_mm<72>(297.52), Center, "t2 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(85.34), to_mm<72>(297.52), Center, "t3 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(119.49), to_mm<72>(297.52), Center, "Y x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(153.65), to_mm<72>(297.52), Center, "X1 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(187.81), to_mm<72>(297.52), Center, "X2 x23 GreenLight", ""}},
		RedGreenBlueLight{{to_mm<72>(221.97), to_mm<72>(297.52), Center, "X3 x23 GreenLight", ""}},
	}};

	enum class Elem {
		T_Deja_VuButton,
		Dejavu_X23_WhitemediumknobKnob,
		X_Deja_VuButton,
		T_Mode_Switch_X40_1_X40_2_X40_3Switch,
		Rate_X23_WhitelargeknobKnob,
		Spread_X23_WhitelargeknobKnob,
		X_Mode_Switch_X40_1_X40_2_X40_3Switch,
		T_Bias_X23_WhitemediumknobKnob,
		Clock_Range_Switch_X40_D4_X40_X1_X40_X4Switch,
		Length_X23_WhitemediumknobKnob,
		Output_Range_Switch_X40_2_X40_5_X40_5Switch,
		X_Bias_X23_WhitemediumknobKnob,
		Jitter_X23_WhitemediumknobKnob,
		Mode_Switch_X40_Off_X40_OnSwitch,
		Steps_X23_WhitemediumknobKnob,
		T_Bias_CvIn,
		X_Bias_CvIn,
		T_ClockIn,
		Rate_CvIn,
		Jitter_CvIn,
		Deja_Vu_CvIn,
		Steps_CvIn,
		Spread_CvIn,
		X_ClockIn,
		T1Out,
		T2Out,
		T3Out,
		YOut,
		X1Out,
		X2Out,
		X3Out,
		T_Mode_Led_X23_RedgreenyellowLight,
		X_Mode_Led_X23_RedgreenyellowLight,
		Fall_Led_BLight,
		Fall_Led_B1Light,
		Fall_Led_B2Light,
		T1_X23_GreenlightLight,
		T2_X23_GreenlightLight,
		T3_X23_GreenlightLight,
		Y_X23_GreenlightLight,
		X1_X23_GreenlightLight,
		X2_X23_GreenlightLight,
		X3_X23_GreenlightLight,
	};

	// Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)

	enum {
		KnobDejavu_X23_Whitemediumknob,
		KnobRate_X23_Whitelargeknob,
		KnobSpread_X23_Whitelargeknob,
		KnobT_Bias_X23_Whitemediumknob,
		KnobLength_X23_Whitemediumknob,
		KnobX_Bias_X23_Whitemediumknob,
		KnobJitter_X23_Whitemediumknob,
		KnobSteps_X23_Whitemediumknob,
		NumKnobs,
	};

	enum {
		SwitchT_Deja_Vu,
		SwitchX_Deja_Vu,
		SwitchT_Mode_Switch_X40_1_X40_2_X40_3,
		SwitchX_Mode_Switch_X40_1_X40_2_X40_3,
		SwitchClock_Range_Switch_X40_D4_X40_X1_X40_X4,
		SwitchOutput_Range_Switch_X40_2_X40_5_X40_5,
		SwitchMode_Switch_X40_Off_X40_On,
		NumSwitches,
	};

	enum {
		InputT_Bias_Cv,
		InputX_Bias_Cv,
		InputT_Clock,
		InputRate_Cv,
		InputJitter_Cv,
		InputDeja_Vu_Cv,
		InputSteps_Cv,
		InputSpread_Cv,
		InputX_Clock,
		NumInJacks,
	};

	enum {
		OutputT1,
		OutputT2,
		OutputT3,
		OutputY,
		OutputX1,
		OutputX2,
		OutputX3,
		NumOutJacks,
	};

	enum {
		LedT_Mode_Led_X23_Redgreenyellow,
		LedX_Mode_Led_X23_Redgreenyellow,
		LedFall_Led_B,
		LedFall_Led_B,
		LedFall_Led_B,
		LedT1_X23_Greenlight,
		LedT2_X23_Greenlight,
		LedT3_X23_Greenlight,
		LedY_X23_Greenlight,
		LedX1_X23_Greenlight,
		LedX2_X23_Greenlight,
		LedX3_X23_Greenlight,
		NumDiscreteLeds,
	};
};
} // namespace MetaModule
