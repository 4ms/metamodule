#pragma once
#include "info/DualAtenuverter_info.hh"
#include "platform_module.hh"

#include "CoreModules/moduleFactory.hh"
#include "coreProcessor.h"
#include <memory>

struct DualAtenuverterCore : PlatformModule<MetaModule::DualAtenuverterInfo> {
	using Info = MetaModule::DualAtenuverterInfo;

	void process(const ProcessArgs &args) override;

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<DualAtenuverterCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on
};
