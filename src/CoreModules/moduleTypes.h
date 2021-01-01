#pragma once
#include "coreProcessor.h"
#include "lfoCore.h"
#include "mixer4Core.h"
#include "panel.hh"
#include <memory>

enum ModuleType {
	PANEL,
	LFO,
	AD_ENVELOPE,
	CROSSFADE,
	MIXER4,
	LOGIC,

	NUM_MODULE_TYPES,
};

class ModuleFactory {
public:
	ModuleFactory() = delete;

	static std::unique_ptr<CoreProcessor> create(const ModuleType id)
	{
		switch (id) {
			case (ModuleType::PANEL):
				return std::make_unique<Panel>();
			case (ModuleType::LFO):
				return std::make_unique<LFOCore>();
			case (ModuleType::MIXER4):
				return std::make_unique<Mixer4Core>();
			default:
				return nullptr;
		}
	}
};

