#pragma once
#include "../comm/comm_module.hh"
#include "CoreModules/moduleFactory.hh"
#include "hub_knob.hh"
#include "hub_midi.hh"
#include "hub_module.hh"
#include "mapping/Mapping.h"
#include "mapping/ModuleID.h"
#include "mapping/map_palette.hh"
#include "mapping/module_directory.hh"
#include "mapping/patch_writer.hh"
#include "util/math.hh"
#include "util/string_util.hh"
#include <functional>
#include <string>

struct MetaModuleHubWidget : rack::app::ModuleWidget {

	rack::Label *statusText;
	MetaModuleHubBase *hubModule;

	MetaModuleHubWidget() = default;

	static constexpr float kKnobSpacingY = 17;
	static constexpr float kKnobSpacingX = 18;
	static constexpr float kTextOffset = 5;

	template<typename KnobType>
	void addLabeledKnobPx(std::string_view labelText,
						  int knobId,
						  rack::math::Vec posPx,
						  float sz_mm = kKnobSpacingX,
						  float defaultValue = 0.f) {
		auto button = new HubKnobMapButton{hubModule, *this};
		button->box.pos =
			rack::math::Vec(posPx.x - rack::mm2px(sz_mm) / 2, posPx.y - rack::mm2px(sz_mm) / 2); // top-left
		button->box.size.x = rack::mm2px(sz_mm);
		button->box.size.y = rack::mm2px(sz_mm);
		button->text = labelText;
		button->hubParamObj = {MappableObj::Type::Knob, knobId, hubModule ? hubModule->id : -1};
		addChild(button);

		auto *p = new HubKnob<KnobType>{hubModule, *button};
		p->box.pos = posPx;
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		p->rack::app::ParamWidget::module = hubModule;
		p->rack::app::ParamWidget::paramId = knobId;
		p->initParamQuantity();

		if (module) {
			auto pq = p->getParamQuantity();
			pq = module->paramQuantities[knobId];
			pq->defaultValue = defaultValue;
			button->setParamQuantity(pq);
		}
		addParam(p);
	}

	void addMidiValueMapSrc(const std::string labelText, int knobId, rack::math::Vec posPx, MappableObj::Type type) {
		auto *button = new HubMidiMapButton{hubModule, *this};
		button->box.size.x = rack::mm2px(13.5);
		button->box.size.y = rack::mm2px(5.6);
		button->box.pos = posPx;
		button->box.pos = button->box.pos.minus(button->box.size.div(2));
		button->text = labelText;
		button->hubParamObj = {type, knobId, hubModule ? hubModule->id : -1};
		addChild(button);

		auto *p = new HubMidiParam{hubModule, *button};
		p->setSize(rack::mm2px({12, 4}));
		p->box.pos = posPx;
		p->box.pos = p->box.pos.minus(p->box.size.div(2));
		p->rack::app::ParamWidget::module = hubModule;
		p->rack::app::ParamWidget::paramId = knobId;
		p->initParamQuantity();

		if (module) {
			auto pq = p->getParamQuantity();
			pq = module->paramQuantities[knobId];
			pq->defaultValue = 0.f;
			button->setParamQuantity(pq);
		}
		addParam(p);
	}
};
