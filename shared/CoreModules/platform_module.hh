#ifdef VCVRACK

#include "rack.hpp"

template<typename Info, typename Core>
struct PlatformModule : rack::Module {
	static inline bool s_registered = true;
};

using rack::simd::float_4;

#else

#include "VCV-adaptor/VCVCoreProcessor.hh"

namespace MetaModule
{

template<typename Info, typename Core>
struct PlatformModule : VCVCoreProcessor<Info, Core> {};

using float_4 = float;

} // namespace MetaModule

#endif
