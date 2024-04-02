#pragma once
#include <app/MultiLightWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

struct ModuleLightWidget : MultiLightWidget {
	engine::Module *module = nullptr;
	int firstLightId = -1;

	engine::Light *getLight(int colorId) {
		if (!module || firstLightId < 0)
			return nullptr;
		return &module->lights[firstLightId + colorId];
	}

	engine::LightInfo *getLightInfo() {
		if (!module || firstLightId < 0)
			return nullptr;
		return module->lightInfos[firstLightId].get();
	}

	void createTooltip() {
	}
	void destroyTooltip() {
	}
};

} // namespace rack::app
