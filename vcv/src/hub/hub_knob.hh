#pragma once
#include "mapping/map_marks.hh"
#include "mapping/map_palette.hh"
#include "mapping/knob_alias_menu.hh"
#include "mapping/range_slider.hh"
#include "hub_knob_menu.hh"
#include "hub_map_button.hh"
#include "hub_module.hh"

// This is needed in case someone maps a Hub Knobs to their MIDI CC module or something else

class HubKnobMapButton : public HubMapButton {
	rack::ParamQuantity *paramQuantity = nullptr;
	MetaModuleHubBase *hub;

public:
	HubKnobMapButton(MetaModuleHubBase *hub, rack::app::ModuleWidget &parent)
		: HubMapButton{hub, parent}
		, hub{hub} {
	}

	void setParamQuantity(rack::ParamQuantity *paramQ) {
		paramQuantity = paramQ;
	}

	void onDeselect(const rack::event::Deselect &e) override {
		if (!hub)
			return;

		// Check if a ParamWidget was touched
		auto touchedParam = APP->scene->rack->getTouchedParam();
		if (touchedParam && touchedParam->getParamQuantity()) {
			int param_id = touchedParam->getParamQuantity()->paramId;
			APP->scene->rack->setTouchedParam(nullptr);

			hub->registerMap(hubParamObj.objID, touchedParam->module, param_id);
		}
	}

	void onButton(const rack::event::Button &e) override {
		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			if (paramQuantity) {
				makeKnobMenu();
				e.consume(this);
			}
		} else {
			Button::onButton(e);
		}
	}

	void makeKnobMenu() {
		rack::ui::Menu *menu = rack::createMenu();

		KnobNameMenuLabel *paramLabel = new KnobNameMenuLabel;
		paramLabel->paramQty = paramQuantity;
		menu->addChild(paramLabel);

		KnobValueMenuItem *paramField = new KnobValueMenuItem{120, 0.4f, paramQuantity};
		menu->addChild(paramField);

		if (!hub)
			return;

		if (hub->mappings.getNumMappings(hubParamObj.objID) > 0) {
			auto *sep = new rack::MenuSeparator;
			menu->addChild(sep);

			auto aliasItem = new KnobAliasMenuItem{hubParamObj};
			menu->addChild(aliasItem);

			auto maps = hub->mappings.getMappings(hubParamObj.objID);
			for (auto const &m : maps) {
				if (!m.paramHandle.module)
					continue;
				if (m.paramHandle.module->id < 0)
					continue;
				if (!m.paramHandle.module->model)
					continue;
				auto paramId = m.paramHandle.paramId;
				auto moduleId = m.paramHandle.moduleId;
				if (!m.paramHandle.module->paramQuantities[paramId])
					continue;

				auto *sep = new rack::MenuSeparator;
				menu->addChild(sep);

				MappedKnobMenuLabel *paramLabel2 = new MappedKnobMenuLabel;
				paramLabel2->moduleName = m.paramHandle.module->model->name;
				paramLabel2->paramName = m.paramHandle.module->paramQuantities[paramId]->getLabel();
				paramLabel2->moduleId = moduleId;
				paramLabel2->paramId = paramId;
				menu->addChild(paramLabel2);

				MappableObj paramObj{MappableObj::Type::Knob, paramId, moduleId};

				auto mn = new RangeSlider<RangePart::Min>(hub, paramObj);
				mn->box.size.x = 100;
				menu->addChild(mn);

				auto mx = new RangeSlider<RangePart::Max>(hub, paramObj);
				mx->box.size.x = 100;
				menu->addChild(mx);
			}

			rack::ParamHandle *paramHandle =
				paramQuantity ? APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId) :
								nullptr;
			if (paramHandle) {
				ParamUnmapItem *unmapItem = new ParamUnmapItem;
				unmapItem->text = "Unmap";
				unmapItem->rightText = paramHandle->text;
				unmapItem->paramQuantity = paramQuantity;
				menu->addChild(unmapItem);
			}
		}
	}

	struct ParamUnmapItem : rack::ui::MenuItem {
		rack::ParamQuantity *paramQuantity;

		void onAction(const rack::event::Action &e) override {
			rack::ParamHandle *paramHandle =
				APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId);
			if (paramHandle) {
				APP->engine->updateParamHandle(paramHandle, -1, 0);
			}
		}
	};
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	HubKnob(MetaModuleHubBase *hub, HubKnobMapButton &hubknob_mapbut)
		: hub{hub}
		, mapBut{hubknob_mapbut} {
	}

	void draw(const typename BaseKnobT::DrawArgs &args) override {
		BaseKnobT::draw(args);

		if (!hub)
			return;

		auto numMaps = std::min(hub->mappings.getNumMappings(mapBut.hubParamObj.objID), 16U);

		const float spacing = 8;
		const NVGcolor color = PaletteHub::color(mapBut.hubParamObj.objID);
		auto _box = this->box;
		for (unsigned i = 0; i < numMaps; i++) {
			MapMark::markKnob(args.vg, _box, color);
			if (i % 4 == 3) {
				_box.size.x = this->box.size.x;
				_box.size.y -= spacing;
			} else
				_box.size.x -= spacing;
		}
	}

	void onButton(const rack::event::Button &e) override {
		rack::math::Vec c = this->box.size.div(2);
		float dist = e.pos.minus(c).norm();
		if (dist <= c.x) {
			rack::OpaqueWidget::onButton(e);

			// Touch parameter
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
				if (this->getParamQuantity()) {
					APP->scene->rack->setTouchedParam(this);
				}
				e.consume(this);
			}

			// Right click to open context menu
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
				mapBut.makeKnobMenu();
				e.consume(this);
			}
		}
	}

	void onHover(const rack::event::Hover &e) override {
		// If the knob is mapped, then we want to pass the hover down to the HubKnobMapButton object below
		// so that the HubMapKnobButton can highlight even if we're hovering the knob itself.
		// So, don't consume the hover and just do nothing.
		// On the other hand, if the knob is not mapped, then consume the hover so that hovering the knob
		// doesn't make the background highlight appear
		if (centralData->isLabelButtonSrcMapped(mapBut.hubParamObj))
			return;

		e.consume(this);
	}

	struct ParamResetItem : rack::ui::MenuItem {
		rack::ParamWidget *paramWidget;
		void onAction(const rack::event::Action &e) override {
			paramWidget->resetAction();
		}
	};

private:
	MetaModuleHubBase *hub;
	HubKnobMapButton &mapBut;
};
