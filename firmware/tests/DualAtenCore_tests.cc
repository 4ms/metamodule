#include "CoreModules/Befaco/DualAtenuverterCore.hh"

// must define this to avoid linker error missing vtable for this class
void DualAtenuverterCore::process(const ProcessArgs &args) {
}

static_assert(DualAtenuverterCore::params.size() == 4);
static_assert(DualAtenuverterCore::inputs.size() == 2);
static_assert(DualAtenuverterCore::outputs.size() == 2);
static_assert(DualAtenuverterCore::lights.size() == 2);
static_assert(DualAtenuverterCore::param_scales.size() == 4);
static_assert(DualAtenuverterCore::param_scales[0].range == 2.f);
static_assert(DualAtenuverterCore::param_scales[0].offset == -1.f);
static_assert(DualAtenuverterCore::param_scales[1].range == 20.f);
static_assert(DualAtenuverterCore::param_scales[1].offset == -10.f);
static_assert(DualAtenuverterCore::param_scales[2].range == 2.f);
static_assert(DualAtenuverterCore::param_scales[2].offset == -1.f);
static_assert(DualAtenuverterCore::param_scales[3].range == 20.f);
static_assert(DualAtenuverterCore::param_scales[3].offset == -10.f);
