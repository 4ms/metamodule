#ifdef VCVRACK

#include "rack.hpp"
template<typename T, typename U>
struct PlatformModule : rack::Module {};

using rack::simd::float_4;

#else

#include "VCV-adaptor/VCVCoreProcessor.hh"
template<typename Info, typename Core>
struct PlatformModule : VCVCoreProcessor<Info, Core> {};

using float_4 = float;

#endif
