#pragma once
#include "info/DualAtenuverter_info.hh"
#include "platform_module.hh"

struct DualAtenuverterCore : PlatformModule<MetaModule::DualAtenuverterInfo> {
	void process(const ProcessArgs &args) override;
};
