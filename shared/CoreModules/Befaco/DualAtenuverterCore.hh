#pragma once
#include "info/DualAtenuverter_info.hh"
#include "platform_module.hh"

struct DualAtenuverterCore : PlatformModule<MetaModule::DualAtenuverterInfo, DualAtenuverterCore> {
	void process(const ProcessArgs &args) override;

	static inline bool register_module = PlatformModule::s_registered;
};
