#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/MPEG_info.hh"

#include "mpeg/PingGenerator.h"

#include "helpers/EdgeDetector.h"
#include "helpers/FlipFlop.h"
#include "helpers/Gestures.h"

namespace MetaModule
{

class MPEGCore : public SmartCoreProcessor<MPEGInfo> {
	using Info = MPEGInfo;
	using ThisCore = MPEGCore;
	using enum Info::Elem;

public:
	MPEGCore() 
		: mode(SYNC), ticks(0), triggerPing(1.0f, 2.0f), tapLongPress(2.f)
	{

	};

	void update() override {
		ticks++;

		if (tapEdge(getState<PingButton>() == MomentaryButton::State_t::PRESSED))
		{
			ping.tap(ticks);
		}

		if(tapLongPress(getState<PingButton>() == MomentaryButton::State_t::PRESSED))
		{
			ping.reset();
		}

		if (auto pingIn = getInput<PingTrigIn>(); pingIn.has_value())
		{
			if (pingEdge(triggerPing(*pingIn)))
			{
				ping.ping(ticks);
			}
		}

		ping.setFreeRunning(getState<FreeNRunningPingAltParam>() == 0);

		ping.update(ticks);

		setLED<CycleButton>(ping.getPhase() < 0.5f);
		setOutput<EofOut>(ping.getPhase() < 0.5f);
	}

	void set_samplerate(float sr) override {
		tapLongPress.set_samplerate(sr);
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	enum mode_t {ASYNC, SYNC};

	mode_t mode;

	uint32_t ticks;

private:
	PingGenerator ping;
	EdgeDetector tapEdge;
	FlipFlop triggerPing;
	EdgeDetector pingEdge;
	LongPressDetector tapLongPress;
};

} // namespace MetaModule
