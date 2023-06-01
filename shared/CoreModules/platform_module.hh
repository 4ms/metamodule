#ifdef VCVRACK

#include "moduleFactory.hh"
#include "rack.hpp"

template<typename Info, typename Core>
struct PlatformModule : rack::Module {
	// Auto-register in ModuleFactory
	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<Core>();
	}
	static inline bool s_registered =
		ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
};

using rack::simd::float_4;

#else

#include "VCV-adaptor/VCVCoreProcessor.hh"
template<typename Info, typename Core>
struct PlatformModule : VCVCoreProcessor<Info, Core> {};

using float_4 = float;

#endif
