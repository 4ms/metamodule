#include "CoreModules/element_counter.hh"
#include "info/DualAtenuverter_info.hh"

namespace
{
using Info = MetaModule::DualAtenuverterInfo;
constexpr static typename ElementCount<Info>::Counts counts = ElementCount<Info>::count();
static_assert(counts.num_params == 4);
static_assert(counts.num_inputs == 2);
static_assert(counts.num_outputs == 2);
static_assert(counts.num_lights == 6); //why 6?

using ParamScale = typename ElementCount<Info>::ParamScale;
constexpr static std::array<ParamScale, counts.num_params> param_scales = ElementCount<Info>::param_scales();

static_assert(param_scales.size() == 4);
static_assert(param_scales[0].range == 2.f);
static_assert(param_scales[0].offset == -1.f);
static_assert(param_scales[1].range == 20.f);
static_assert(param_scales[1].offset == -10.f);
static_assert(param_scales[2].range == 2.f);
static_assert(param_scales[2].offset == -1.f);
static_assert(param_scales[3].range == 20.f);
static_assert(param_scales[3].offset == -10.f);
} // namespace
