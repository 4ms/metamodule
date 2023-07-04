//#pragma once
//#include "CoreModules/coreProcessor.h"
//#include "CoreModules/module_info_base.hh"

//struct PanelMediumInfo : ModuleInfoBase {
//	static constexpr std::string_view slug{"PanelMedium"};
//	static constexpr std::string_view description{"Panel 28HP"};
//	static constexpr uint32_t width_hp = 28;
//	static constexpr std::string_view svg_filename{""};

//	static constexpr int NumKnobs = 12;

//	enum {
//		KnobA,
//		KnobB,
//		KnobC,
//		KnobD,
//		KnobE,
//		KnobF,
//		KnobX,
//		KnobY,
//		KnobZ,
//		KnobL,
//		KnobR,
//		KnobQ,
//	};
//	//FIXME: finish this
//	// static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{
//	// 	"A", "B", "C", "D", "E", "F", "x", "y", "z", "l", "r", "q"};
//	// static inline const std::array<StaticString<NameChars>, NumUserFacingOutJacks> InJackNames{
//	// 	"Out1", "Out2", "Out3", "Out4", "Out5", "Out6", "Out7", "Out8", "GateOut1", "GateOut2"};
//	// static inline const std::array<StaticString<NameChars>, NumUserFacingInJacks> OutJackNames{
//	// 	"In1", "In2", "In3", "In4", "In5", "In6", "GateIn1", "GateIn2"};
//	// static inline const StaticString<LongNameChars> description{"Panel"};

//	static constexpr std::array<KnobDef, NumKnobs> Knobs{{
//		{
//			.id = KnobA,
//			.x_mm = px_to_mm<72>(32.88f),
//			.y_mm = px_to_mm<72>(40.33f),
//			.short_name = "Pitch",
//			.long_name = "Pitch",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobB,
//			.x_mm = px_to_mm<72>(84.41f),
//			.y_mm = px_to_mm<72>(40.33f),
//			.short_name = "Mix",
//			.long_name = "Mix",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobC,
//			.x_mm = px_to_mm<72>(32.88f),
//			.y_mm = px_to_mm<72>(83.47f),
//			.short_name = "Index",
//			.long_name = "Index",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobD,
//			.x_mm = px_to_mm<72>(84.41f),
//			.y_mm = px_to_mm<72>(83.47f),
//			.short_name = "Index CV",
//			.long_name = "Index CV",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobE,
//			.x_mm = px_to_mm<72>(32.88f),
//			.y_mm = px_to_mm<72>(126.62f),
//			.short_name = "Ratio C",
//			.long_name = "Ratio C",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobF,
//			.x_mm = px_to_mm<72>(84.41f),
//			.y_mm = px_to_mm<72>(126.62f),
//			.short_name = "Ratio F",
//			.long_name = "Ratio F",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobX,
//			.x_mm = px_to_mm<72>(32.88f),
//			.y_mm = px_to_mm<72>(169.76f),
//			.short_name = "Shape",
//			.long_name = "Shape",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//		{
//			.id = KnobY,
//			.x_mm = px_to_mm<72>(84.41f),
//			.y_mm = px_to_mm<72>(169.76f),
//			.short_name = "Shape CV",
//			.long_name = "Shape CV",
//			.default_val = 0.0f,
//			.knob_style = KnobDef::Small,
//			.orientation = KnobDef::Round,
//		},
//	}};

//	static constexpr int NumInJacks = 5;

//	enum {
//		InputV_Oct_P = 0,
//		InputV_Oct_S = 1,
//		InputMix = 2,
//		InputIndex = 3,
//		InputShape = 4,
//	};

//	static constexpr std::array<InJackDef, NumInJacks> InJacks{{
//		{
//			.id = InputV_Oct_P,
//			.x_mm = px_to_mm<72>(33.02f),
//			.y_mm = px_to_mm<72>(214.61f),
//			.short_name = "V/Oct P",
//			.long_name = "V/Oct P",
//			.unpatched_val = 0.f,
//			.signal_type = InJackDef::Analog,
//		},
//		{
//			.id = InputV_Oct_S,
//			.x_mm = px_to_mm<72>(84.55f),
//			.y_mm = px_to_mm<72>(214.61f),
//			.short_name = "V/Oct S",
//			.long_name = "V/Oct S",
//			.unpatched_val = 0.f,
//			.signal_type = InJackDef::Analog,
//		},
//		{
//			.id = InputMix,
//			.x_mm = px_to_mm<72>(33.02f),
//			.y_mm = px_to_mm<72>(263.71f),
//			.short_name = "Mix",
//			.long_name = "Mix",
//			.unpatched_val = 0.f,
//			.signal_type = InJackDef::Analog,
//		},
//		{
//			.id = InputIndex,
//			.x_mm = px_to_mm<72>(84.55f),
//			.y_mm = px_to_mm<72>(263.71f),
//			.short_name = "Index",
//			.long_name = "Index",
//			.unpatched_val = 0.f,
//			.signal_type = InJackDef::Analog,
//		},
//		{
//			.id = InputShape,
//			.x_mm = px_to_mm<72>(33.02f),
//			.y_mm = px_to_mm<72>(311.3f),
//			.short_name = "Shape",
//			.long_name = "Shape",
//			.unpatched_val = 0.f,
//			.signal_type = InJackDef::Analog,
//		},
//	}};

//	static constexpr int NumOutJacks = 1;

//	enum {
//		OutputOut = 0,
//	};

//	static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
//		{
//			.id = OutputOut,
//			.x_mm = px_to_mm<72>(84.55f),
//			.y_mm = px_to_mm<72>(311.3f),
//			.short_name = "Out",
//			.long_name = "Out",
//			.signal_type = OutJackDef::Analog,
//		},
//	}};

//	static constexpr int NumSwitches = 0;

//	static constexpr std::array<SwitchDef, NumSwitches> Switches{{}};

//	static constexpr int NumDiscreteLeds = 0;

//	static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{}};
//};
