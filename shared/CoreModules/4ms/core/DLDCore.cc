#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/DLD_info.hh"
#include "looping-delay/DLDChannel.hh"

namespace MetaModule
{

class DLDCore : public SmartCoreProcessor<DLDInfo> {
	using Info = DLDInfo;
	using ThisCore = DLDCore;
	using enum Info::Elem;

public:
	template<Info::Elem EL>
	void setOutput(auto val)
	{
		return SmartCoreProcessor<Info>::setOutput<EL>(val);
	}

	template<Info::Elem EL>
	auto getInput()
	{
		return SmartCoreProcessor<Info>::getInput<EL>();
	}

	template<Info::Elem EL, typename VAL>
	void setLED(const VAL &value)
	{
		return SmartCoreProcessor<Info>::setLED<EL>(value);
	}

	template<Info::Elem EL>
	auto getState()
	{
		return SmartCoreProcessor<Info>::getState<EL>();
	}

private:
	struct MappingA
	{
		const static Info::Elem TimeKnob       = TimeAKnob;
		const static Info::Elem FeedbackKnob   = FeedbackAKnob;
		const static Info::Elem DelayFeedKnob  = DelayFeedAKnob;
		const static Info::Elem MixKnob        = MixAKnob;
		const static Info::Elem ReverseButton  = ReverseAButton;
		const static Info::Elem HoldButton     = HoldAButton;
		const static Info::Elem AudioInput     = InAIn;
		const static Info::Elem AudioOutput    = OutAOut;
		const static Info::Elem ReturnInput    = ReturnAIn;
		const static Info::Elem SendOutput     = SendAOut;
		const static Info::Elem ReverseInput   = ReverseAJackIn;
		const static Info::Elem HoldInput      = HoldAJackIn;
		const static Info::Elem TimeInput      = TimeAJackIn;
		const static Info::Elem FeedbackInput  = FeedbackAJackIn;
		const static Info::Elem DelayFeedInput = DelayFeedAJackIn;
		const static Info::Elem LoopOutput     = LoopAOut;
		const static Info::Elem TimeLight      = TimeALedLight;
		const static Info::Elem TimeModSwitch  = P16_OR_1_8ThASwitch;
	};

	struct MappingB
	{
		const static Info::Elem TimeKnob       = TimeBKnob;
		const static Info::Elem FeedbackKnob   = FeedbackBKnob;
		const static Info::Elem DelayFeedKnob  = DelayFeedBKnob;
		const static Info::Elem MixKnob        = MixBKnob;
		const static Info::Elem ReverseButton  = ReverseBButton;
		const static Info::Elem HoldButton     = HoldBButton;
		const static Info::Elem AudioInput     = InBIn;
		const static Info::Elem AudioOutput    = OutBOut;
		const static Info::Elem ReturnInput    = ReturnBIn;
		const static Info::Elem SendOutput     = SendBOut;
		const static Info::Elem ReverseInput   = ReverseBJackIn;
		const static Info::Elem HoldInput      = HoldBJackIn;
		const static Info::Elem TimeInput      = TimeBJackIn;
		const static Info::Elem FeedbackInput  = FeedbackBJackIn;
		const static Info::Elem DelayFeedInput = DelayFeedBJackIn;
		const static Info::Elem LoopOutput     = LoopBOut;
		const static Info::Elem TimeLight      = TimeBLedLight;
		const static Info::Elem TimeModSwitch  = P16_OR_1_8ThBSwitch;
	};	

	DLDChannel<DLDCore, MappingA> channelA;
	DLDChannel<DLDCore, MappingB> channelB;

	friend DLDChannel<DLDCore, MappingA>;
	friend DLDChannel<DLDCore, MappingB>;

public:
	DLDCore()
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
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
};

} // namespace MetaModule
