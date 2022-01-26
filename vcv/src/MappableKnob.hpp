#pragma once
#include "MapMarks.hpp"
#include "base_concepts.hh"
#include "hub_knob_menu.hpp"
#include "paletteHub.hpp"
#include "plugin.hpp"
#include <rack.hpp>

template<typename BaseKnobT>
requires(std::is_base_of<app::SvgKnob, BaseKnobT>() == true) class MappableKnob : public BaseKnobT {

	static constexpr float Hmargin = 20;
	static constexpr float Vmargin = 40;

public:
	MappableKnob()
	{
		this->box = this->box.grow(Vec{Hmargin, Vmargin});
	}

	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		if (centralData->isMappingInProgress()) {
			auto src = centralData->getMappingSource();

			nvgBeginPath(args.vg);
			nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
			NVGcolor color;
			if (src.objType == getId().objType) {
				// float alphac = this->hovered ? 0.75 : 0.4;
				float alphac = 0.75f;
				color = rack::color::alpha(PaletteHub::color[src.objID], alphac);
			} else {
				color = rack::color::alpha(color::WHITE, 0.5f);
				// dim out BaseJackT::draw()?
			}
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
		}

		BaseKnobT::draw(args);
	}

	// onButton is provided to customize the context menu for mappable knobs
	void onButton(const event::Button &e) override
	{
		OpaqueWidget::onButton(e);

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			ui::Menu *menu = createMenu();

			ParamLabel *paramLabel = new ParamLabel;
			paramLabel->paramWidget = this;
			menu->addChild(paramLabel);

			ParamField *paramField = new ParamField;
			paramField->box.size.x = 100;
			paramField->setParamWidget(this);
			menu->addChild(paramField);

			MenuSeparator *sep = new MenuSeparator;
			menu->addChild(sep);

			if ((getId().moduleID >= 0) && centralData->isLabelButtonDstMapped(getId())) {
				// MapFieldEntry *paramLabel2 = new MapFieldEntry;
				// paramLabel2->moduleName = this->paramQuantity->module->model->name;
				// paramLabel2->paramName = this->paramQuantity->getLabel();
				// paramLabel2->moduleId = this->paramQuantity->moduleId;
				// paramLabel2->paramId = this->paramQuantity->paramId;
				// menu->addChild(paramLabel2);

				// LabelButtonID src = getMappedSrcFromDst(getId());

				// Min/Max field can't modify the float value directly
				// Instead, rename PercentQuantity to MappedQty and have setValue call
				// centralData->requestHubUpdateMapRange<Min>(src, val); When Hub goes to refresh centralData->maps,
				// it'll check if there's a new map range val, and update its own KnobMaps
				//  MinField *o = new MinField(mapping->range);
				//  o->box.size.x = 100;
				//  menu->addChild(o);

				// MaxField *l = new MaxField(mapping->range);
				// l->box.size.x = 100;
				// menu->addChild(l);

				KnobUnmapItem *unmapItem = new KnobUnmapItem{getId()};
				unmapItem->text = "Unmap";
				// unmapItem->rightText = .... TODO: name of metamodule jack
				menu->addChild(unmapItem);
			} else {
				ui::MenuItem *label = new ui::MenuItem;
				label->text = "Not mapped";
				label->rightText = "Click under a MetaModule knob to begin mapping";
				menu->addChild(label);
			}
			e.consume(this);
		} else {
			ParamWidget::onButton(e);
		}
	}

	void onHover(const event::Hover &e) override
	{
		e.consume(this);
	}

private:
	LabelButtonID getId()
	{
		int moduleId = -1;
		int paramId = -1;
		if (this->paramQuantity) {
			moduleId = this->paramQuantity->module ? this->paramQuantity->module->id : -1;
			paramId = this->paramQuantity->paramId;
		}
		return {LabelButtonID::Types::Knob, paramId, moduleId};
	}

	struct KnobUnmapItem : ui::MenuItem {
		const LabelButtonID _id;
		KnobUnmapItem(LabelButtonID id)
			: _id{id}
		{}
		void onAction(const event::Action &e) override
		{
			centralData->unregisterMapByDest(_id);
		}
	};

	// ParamLabel: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamLabel : ui::MenuLabel {
		ParamWidget *paramWidget;
		void step() override
		{
			text = paramWidget->paramQuantity->getString();
			MenuLabel::step();
		}
	};

	// ParamField: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamField : ui::TextField {
		ParamWidget *paramWidget;

		void step() override
		{
			// Keep selected
			APP->event->setSelected(this);
			TextField::step();
		}

		void setParamWidget(ParamWidget *paramWidget)
		{
			this->paramWidget = paramWidget;
			if (paramWidget->paramQuantity)
				text = paramWidget->paramQuantity->getDisplayValueString();
			selectAll();
		}

		void onSelectKey(const event::SelectKey &e) override
		{
			if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
				float oldValue = paramWidget->paramQuantity->getValue();
				if (paramWidget->paramQuantity)
					paramWidget->paramQuantity->setDisplayValueString(text);
				float newValue = paramWidget->paramQuantity->getValue();

				if (oldValue != newValue) {
					// Push ParamChange history action
					history::ParamChange *h = new history::ParamChange;
					h->moduleId = paramWidget->paramQuantity->module->id;
					h->paramId = paramWidget->paramQuantity->paramId;
					h->oldValue = oldValue;
					h->newValue = newValue;
					APP->history->push(h);
				}

				ui::MenuOverlay *overlay = getAncestorOfType<ui::MenuOverlay>();
				overlay->requestDelete();
				e.consume(this);
			}

			if (!e.getTarget())
				TextField::onSelectKey(e);
		}
	};
};
