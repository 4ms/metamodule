#pragma once
#include "HubMapButton.hpp"
#include "MapMarks.hpp"
#include "hub_knob_menu.hpp"
#include "knob_map.hpp"
#include "paletteHub.hpp"

// This is needed in case someone maps a Hub Knobs to their MIDI CC module or something else

struct ParamUnmapItem : ui::MenuItem {
	ParamQuantity *paramQuantity;
	void onAction(const event::Action &e) override
	{
		ParamHandle *paramHandle = APP->engine->getParamHandle(paramQuantity->module->id, paramQuantity->paramId);
		if (paramHandle) {
			APP->engine->updateParamHandle(paramHandle, -1, 0);
		}
	}
};

static void makeKnobMenu(ParamQuantity *paramQuantity, LabelButtonID id)
{
	ui::Menu *menu = createMenu();

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
		MenuSeparator *sep = new MenuSeparator;
		menu->addChild(sep);

		auto aliasItem = new KnobAliasMenuItem{id};
		menu->addChild(aliasItem);

		auto paramHandles = centralData->getParamHandlesFromSrc(id);
		for (auto const &ph : paramHandles) {
			if (ph.moduleId != -1) {
				MenuSeparator *sep = new MenuSeparator;
				menu->addChild(sep);

				MappedKnobMenuLabel *paramLabel2 = new MappedKnobMenuLabel;
				paramLabel2->moduleName = ph.module->model->name;
				paramLabel2->paramName = ph.module->paramQuantities[ph.paramId]->getLabel();
				paramLabel2->moduleId = ph.moduleId;
				paramLabel2->paramId = ph.paramId;
				menu->addChild(paramLabel2);

				MinSlider *mn = new MinSlider({LabelButtonID::Types::Knob, ph.paramId, ph.moduleId});
				mn->box.size.x = 100;
				menu->addChild(mn);

				MaxSlider *mx = new MaxSlider({LabelButtonID::Types::Knob, ph.paramId, ph.moduleId});
				mx->box.size.x = 100;
				menu->addChild(mx);
			}
		}

		engine::ParamHandle *paramHandle =
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
	ParamQuantity *paramQuantity = nullptr;

public:
	HubKnobMapButton(CommModuleWidget &parent)
		: HubMapButton{static_cast<CommModuleWidget &>(parent)}
	{}

	void setParamQuantity(ParamQuantity *paramQ) { paramQuantity = paramQ; }

	void onDeselect(const event::Deselect &e) override
	{
		bool registerSuccess = false;

		// Check if a ParamWidget was touched
		ParamWidget *touchedParam = APP->scene->rack->getTouchedParam();
		printf("touchedParam: %p\n", touchedParam);
		if (touchedParam && touchedParam->getParamQuantity()) {
			printf("touchedParam->PQ: %p\n", touchedParam->getParamQuantity());
			int moduleId = touchedParam->module->id;
			printf("touchedParam->module->id: %lld\n", touchedParam->module->id);
			int objId = touchedParam->getParamQuantity()->paramId;
			printf("touchedParam->PQ->paramId: %d\n", touchedParam->getParamQuantity()->paramId);

			APP->scene->rack->setTouchedParam(nullptr);

			registerSuccess = registerMapping(moduleId, objId);
		}

		if (!registerSuccess) {
			centralData->abortMappingProcedure();
			printf("Failed mapping\n");
		}
	}

	void onButton(const event::Button &e) override
	{
		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			if (paramQuantity) {
				makeKnobMenu(paramQuantity, id);
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
		: hubKnobMapBut{hubknob_mapbut}
	{}

	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		BaseKnobT::draw(args);

		auto numMaps = std::min(centralData->getNumMappingsFromSrc(hubKnobMapBut.id), 16U);

		const float spacing = 8;
		const NVGcolor color = PaletteHub::color[hubKnobMapBut.id.objID];
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

	void onButton(const event::Button &e) override
	{
		math::Vec c = this->box.size.div(2);
		float dist = e.pos.minus(c).norm();
		if (dist <= c.x) {
			OpaqueWidget::onButton(e);

			// Touch parameter
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
				if (this->getParamQuantity()) {
					APP->scene->rack->setTouchedParam(this);
				}
				e.consume(this);
			}

			// Right click to open context menu
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
				makeKnobMenu(this->getParamQuantity(), hubKnobMapBut.id);
				e.consume(this);
			}
		}
	}

	void onHover(const event::Hover &e) override
	{
		// If the knob is mapped, then we want to pass the hover down to the HubKnobMapButton object below
		// so that the HubMapKnobButton can highlight even if we're hovering the knob itself.
		// So, don't consume the hover and just do nothing.
		// On the other hand, if the knob is not mapped, then consume the hover so that hovering the knob
		// doesn't make the background highlight appear
		if (centralData->isLabelButtonSrcMapped(hubKnobMapBut.id))
			return;

		e.consume(this);
	}

	struct ParamResetItem : ui::MenuItem {
		ParamWidget *paramWidget;
		void onAction(const event::Action &e) override { paramWidget->resetAction(); }
	};

private:
	HubKnobMapButton &hubKnobMapBut;
};
