#pragma once
#include "../mapping/map_marks.hh"
#include "../mapping/map_palette.hh"
#include "../mapping/mappable_knob.hh"
#include "hub_knob_menu.hh"
#include "hub_map_button.hh"

// This is needed in case someone maps a Hub Knobs to their MIDI CC module or something else

struct ParamUnmapItem : rack::ui::MenuItem {
	rack::ParamQuantity *paramQuantity;
	void onAction(const rack::event::Action &e) override {
		rack::ParamHandle *paramHandle = APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId);
		if (paramHandle) {
			APP->engine->updateParamHandle(paramHandle, -1, 0);
		}
	}
};

static void makeKnobMenu(rack::ParamQuantity *paramQuantity, MappableObj id) {
	rack::ui::Menu *menu = rack::createMenu();

	KnobNameMenuLabel *paramLabel = new KnobNameMenuLabel;
	paramLabel->paramQty = paramQuantity;
	menu->addChild(paramLabel);

	KnobValueMenuItem *paramField = new KnobValueMenuItem{120, 0.4f, paramQuantity};
	menu->addChild(paramField);

	// ParamResetItem *resetItem = new ParamResetItem;
	// resetItem->text = "Initialize";
	// resetItem->rightText = "Double-click";
	// resetItem->paramWidget = this;
	// menu->addChild(resetItem);

	if (centralData->getNumMappingsFromSrc(id) > 0) {
		auto *sep = new rack::MenuSeparator;
		menu->addChild(sep);

		auto aliasItem = new KnobAliasMenuItem{id};
		menu->addChild(aliasItem);

		auto maps = centralData->getMappingsFromSrc(id);
		for (auto const &m : maps) {
			if (m.dst.moduleID != -1) {
				auto *sep = new rack::MenuSeparator;
				menu->addChild(sep);

				MappedKnobMenuLabel *paramLabel2 = new MappedKnobMenuLabel;
				paramLabel2->moduleName = m.dst_module->model->name;
				paramLabel2->paramName = m.dst_module->paramQuantities[m.dst.objID]->getLabel();
				paramLabel2->moduleId = m.dst.moduleID;
				paramLabel2->paramId = m.dst.objID;
				menu->addChild(paramLabel2);

				MinSlider *mn = new MinSlider({MappableObj::Type::Knob, m.dst.objID, m.dst.moduleID});
				mn->box.size.x = 100;
				menu->addChild(mn);

				MaxSlider *mx = new MaxSlider({MappableObj::Type::Knob, m.dst.objID, m.dst.moduleID});
				mx->box.size.x = 100;
				menu->addChild(mx);
			}
		}

		rack::engine::ParamHandle *paramHandle =
			paramQuantity ? APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId) : NULL;
		if (paramHandle) {
			ParamUnmapItem *unmapItem = new ParamUnmapItem;
			unmapItem->text = "Unmap";
			unmapItem->rightText = paramHandle->text;
			unmapItem->paramQuantity = paramQuantity;
			menu->addChild(unmapItem);
		}
	}
}

class HubKnobMapButton : public HubMapButton {
	rack::ParamQuantity *paramQuantity = nullptr;

public:
	HubKnobMapButton(rack::app::ModuleWidget &parent)
		: HubMapButton{static_cast<rack::app::ModuleWidget &>(parent)} {
	}

	void setParamQuantity(rack::ParamQuantity *paramQ) {
		paramQuantity = paramQ;
	}

	void onDeselect(const rack::event::Deselect &e) override {
		bool registerSuccess = false;

		// Check if a ParamWidget was touched
		auto touchedParam = APP->scene->rack->getTouchedParam();
		if (touchedParam && touchedParam->getParamQuantity()) {
			int64_t moduleId = touchedParam->module->id;
			int objId = touchedParam->getParamQuantity()->paramId;
			APP->scene->rack->setTouchedParam(nullptr);

			registerSuccess =
				registerMapping({.objType = MappableObj::Type::Knob, .objID = objId, .moduleID = moduleId});
		}

		if (!registerSuccess) {
			centralData->abortMappingProcedure();
			printf("Failed mapping\n");
		}
	}

	void onButton(const rack::event::Button &e) override {
		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			if (paramQuantity) {
				makeKnobMenu(paramQuantity, mapObj);
				e.consume(this);
			}
		} else {
			Button::onButton(e);
		}
	}
	// TODO: add right-click menu, same as in HubKnob
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	HubKnob(HubKnobMapButton &hubknob_mapbut)
		: hubKnobMapBut{hubknob_mapbut} {
	}

	void draw(const typename BaseKnobT::DrawArgs &args) override {
		BaseKnobT::draw(args);

		auto numMaps = std::min(centralData->getNumMappingsFromSrc(hubKnobMapBut.mapObj), 16U);

		const float spacing = 8;
		const NVGcolor color = PaletteHub::color(hubKnobMapBut.mapObj.objID);
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
				makeKnobMenu(this->getParamQuantity(), hubKnobMapBut.mapObj);
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
		if (centralData->isLabelButtonSrcMapped(hubKnobMapBut.mapObj))
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
	HubKnobMapButton &hubKnobMapBut;
};
