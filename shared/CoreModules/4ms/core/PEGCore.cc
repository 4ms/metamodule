#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/PEG_info.hh"

#include "peg/PEGChannel.h"



#include <array>
#include <algorithm>

namespace MetaModule
{

class PEGCore : public SmartCoreProcessor<PEGInfo> {
	using Info = PEGInfo;
	using ThisCore = PEGCore;
	using enum Info::Elem;

public:
	template<Info::Elem EL>
	void setOutput(auto val) {
		return SmartCoreProcessor<Info>::setOutput<EL>(val);
	}

	template<Info::Elem EL>
	auto getInput() {
		return SmartCoreProcessor<Info>::getInput<EL>();
	}

	template<Info::Elem EL, typename VAL>
	void setLED(const VAL &value) {
		return SmartCoreProcessor<Info>::setLED<EL>(value);
	}

	template<Info::Elem EL>
	auto getState() {
		return SmartCoreProcessor<Info>::getState<EL>();
	}

private:

	private:
	struct MappingA
	{
		const static Info::Elem ShapeCvIn    = SkewRedJackIn;
		const static Info::Elem DivIn        = DivRedJackIn;
		const static Info::Elem ScaleKnob    = ScaleRedKnob;
		const static Info::Elem OffsetKnob   = SkewRedKnob;
		const static Info::Elem ShapeKnob    = CurveRedKnob;
		const static Info::Elem Div_MultKnob = PingDivMultRedKnob;
		const static Info::Elem PingButton   = PingRedButton;
		const static Info::Elem CycleButton  = CycleRedButton;
		const static Info::Elem CycleTrigIn  = QntRedIn;
		const static Info::Elem TriggerIn    = AsyncRedIn;
		const static Info::Elem PingTrigIn   = PingRedJackIn;
		const static Info::Elem EofOut       = EofRedOut;
		const static Info::Elem EnvOut       = EnvRedOut;
		const static Info::Elem _5VEnvOut    = P5VEnvRedOut;
		const static Info::Elem EnvOutLight  = EnvredlightLight;
		const static Info::Elem _5VEnvLight  = EorredlightLight;
		const static Info::Elem EofLight     = EofredlightLight;
	};

	struct MappingB
	{		
		const static Info::Elem ShapeCvIn    = SkewBlueJackIn;
		const static Info::Elem DivIn        = DivBlueJackIn;
		const static Info::Elem ScaleKnob    = ScaleBlueKnob;
		const static Info::Elem OffsetKnob   = SkewBlueKnob;
		const static Info::Elem ShapeKnob    = CurveBlueKnob;
		const static Info::Elem Div_MultKnob = PingDivMultBlueKnob;
		const static Info::Elem PingButton   = PingBlueButton;
		const static Info::Elem CycleButton  = CycleBlueButton;
		const static Info::Elem CycleTrigIn  = QntBlueIn;
		const static Info::Elem TriggerIn    = AsyncBlueIn;
		const static Info::Elem PingTrigIn   = PingBlueJackIn;
		const static Info::Elem EofOut       = EofBlueOut;
		const static Info::Elem EnvOut       = EnvBlueOut;
		const static Info::Elem _5VEnvOut    = P5VEnvBlueOut;
		const static Info::Elem EnvOutLight  = EnvbluelightLight;
		const static Info::Elem _5VEnvLight  = HalfriseblueLight;
		const static Info::Elem EofLight     = EofblueLight;
	};

	PEGChannel<PEGCore,MappingA> channelA;
	PEGChannel<PEGCore,MappingB> channelB;

	friend PEGChannel<PEGCore,MappingA>;
	friend PEGChannel<PEGCore,MappingB>;

	public : 
	PEGCore()
		: channelA(this), channelB(this)
		{
		}

	void update() override {
		channelA.update();
		channelB.update();
	}

	void set_samplerate(float sr) override {
		channelA.set_samplerate(sr);
		channelB.set_samplerate(sr);
	}


	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
};

} // namespace MetaModule
