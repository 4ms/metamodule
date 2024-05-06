#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/MPEG_info.hh"

#include "peg/main.hh"

namespace MetaModule
{

class MPEGCore : public SmartCoreProcessor<MPEGInfo> {
	using Info = MPEGInfo;
	using ThisCore = MPEGCore;
	using enum Info::Elem;

public:
	MPEGCore()
	{

	};

	void update() override {
		peg.update();
	}

	void set_samplerate(float sr) override {
	}

private:
	PEG::MiniPEG peg;

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on
};

} // namespace MetaModule
