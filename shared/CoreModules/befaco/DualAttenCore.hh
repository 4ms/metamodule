#include "info/DualAtten_info.hh"
#include "platform_module.hh"

struct DualAtenuverterCore : PlatformModule<MetaModule::BefacoDualAttenInfo> {
	void process(const ProcessArgs &args) override;
};
