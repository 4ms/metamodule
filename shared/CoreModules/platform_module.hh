#ifdef VCVRACK

#include "rack.hpp"
template<typename T>
struct PlatformModule : rack::Module {};

#else

#include "VCVCoreProcessor.hh"
template<typename InfoT>
struct PlatformModule : VCVCoreProcessor<InfoT> {};

#endif
