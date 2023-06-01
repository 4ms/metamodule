#ifdef VCVRACK

#include "mapping/central_data.hh"
#include "moduleFactory.hh"
#include "rack.hpp"

template<typename Info, typename Core>
struct PlatformModule : rack::Module {
	void onAdd() override {
		ModuleID selfID;
		selfID.id = id;
		selfID.slug = Info::slug;
		centralData->registerModule(selfID, this);
	}
};

using rack::simd::float_4;

#else

#include "VCV-adaptor/VCVCoreProcessor.hh"
template<typename Info, typename Core>
struct PlatformModule : VCVCoreProcessor<Info, Core> {};

using float_4 = float;

#endif
