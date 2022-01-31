#pragma once
#include "MapMarks.hpp"
#include "base_concepts.hh"
#include "hub_knob_menu.hpp"
#include "paletteHub.hpp"
#include "plugin.hpp"
#include <rack.hpp>

template<typename BaseKnobT>
class MappableKnob : public BaseKnobT {
	static_assert(std::is_base_of<app::SvgKnob, BaseKnobT>(), "Knob class must derive from SvgKnob");

	static constexpr float Hmargin = 20;
	static constexpr float Vmargin = 40;
	bool hovered = false;

public:
	MappableKnob()
	{
		// this->sw->box = this->sw->box.grow(Vec{Hmargin, Vmargin});
		// this->fb->box.pos = this->fb->box.pos.plus(Vec{margin / 2, margin / 2});
		// this->shadow->box.pos = this->shadow->box.pos.plus(Vec{margin / 2, margin / 2});
		this->box = this->box.grow(Vec{Hmargin, Vmargin});
	}

	void onEnter(const event::Enter &e) override
	{
		hovered = true;
		if (!centralData->isMappingInProgress())
			centralData->notifyEnterHover(getId());
	}

	void onLeave(const event::Leave &e) override
	{
		hovered = false;
		if (!centralData->isMappingInProgress())
			centralData->notifyLeaveHover(getId());
	}

	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		if (centralData->isMappingInProgress()) {
			auto src = centralData->getMappingSource();

			nvgBeginPath(args.vg);
			nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
			NVGcolor color;
			if (src.objType == getId().objType) {
				float alphac = hovered ? 0.75 : 0.4;
				color = rack::color::alpha(PaletteHub::color[src.objID], alphac);
			} else {
				color = rack::color::alpha(color::WHITE, 0.5f);
				// dim out BaseJackT::draw()?
			}
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
		} else if (centralData->isMappedPartnerHovered(getId())) {
			nvgBeginPath(args.vg);
			nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
			NVGcolor color;
			auto src = centralData->getMappedSrcFromDst(getId());
			color = rack::color::alpha(PaletteHub::color[src.objID], 0.75);
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

			auto moduleid = getId().moduleID;
			auto paramid = getId().objID;

			LabelButtonID dst = getId();
			LabelButtonID src = centralData->getMappedSrcFromDst(dst);

			if ((moduleid >= 0) && src.moduleID != -1) {
				auto aliasItem = new HubKnobAliasNameMenuField{src};
				aliasItem->box.size.x = 100;
				menu->addChild(aliasItem);

				MinSlider *mn = new MinSlider({LabelButtonID::Types::Knob, paramid, moduleid});
				mn->box.size.x = 100;
				menu->addChild(mn);

				MaxSlider *mx = new MaxSlider({LabelButtonID::Types::Knob, paramid, moduleid});
				mx->box.size.x = 100;
				menu->addChild(mx);

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
	const LabelButtonID getId() const
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
