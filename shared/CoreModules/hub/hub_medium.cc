#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "HubMedium_info.hh"

#ifdef VCVRACK
#define printf_(...)
#else
#include "printf.h"
#endif

namespace MetaModule
{

class HubMedium : public CoreProcessor {
public:
	using Info = HubMediumInfo;
	using ThisCore = HubMedium;

	HubMedium() = default;

	void update() final {
		printf_("Error! Hub should not be run\n");
	}

	void set_samplerate(const float sr) final {
		printf_("Error! Hub should not be run\n");
	}

	void set_param(const int param_id, const float val) final {
		printf_("Error! Hub should not be run\n");
	}

	void set_input(const int jack_id, const float val) final {
		printf_("Error! Hub should not be run\n");
	}

	float get_output(const int jack_id) const final {
		printf_("Error! Hub should not be run\n");
		return 0;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on
};

} // namespace MetaModule
