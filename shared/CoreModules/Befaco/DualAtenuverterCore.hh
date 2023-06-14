#pragma once
#include "CoreModules/platform_module.hh"
// Note: platform_module.hh must be declared first because of the ENUMS macro

#include "info/DualAtenuverter_info.hh"

struct DualAtenuverterCore : PlatformModule<MetaModule::DualAtenuverterInfo, DualAtenuverterCore> {
	void process(const ProcessArgs &args) override;

	static inline bool register_module = PlatformModule::s_registered;
};
