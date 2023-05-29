#ifdef VCVRACK

#include "rack.hpp"
template<typename T>
struct PlatformModule : rack::Module {};

using rack::simd::float_4;

#else

#include "VCVCoreProcessor.hh"
template<typename InfoT>
struct PlatformModule : VCVCoreProcessor<InfoT> {};

using float_4 = float;

#endif
