#pragma once
#include "hub_knob_menu.hh"
#include "map_marks.hh"
#include "map_palette.hh"
#include "plugin.hh"
#include "util/base_concepts.hh"
#include <rack.hpp>

class MappableKnobRing : public OpaqueWidget {
protected:
	ParamWidget &_inner_knob;
	bool _hovered = false;

public:
	MappableKnobRing(ParamWidget &inner_knob, float ring_thickness)
		: _inner_knob{inner_knob}
	{
		box.pos = _inner_knob.box.pos.minus({ring_thickness, ring_thickness});
		box.size = _inner_knob.box.size.plus({ring_thickness * 2, ring_thickness * 2});
	}

	void draw(const DrawArgs &args) override
	{
		auto id = getId();
		bool isMappingNow = centralData->isMappingInProgress();
		if (isMappingNow || centralData->isMappedPartnerHovered(id)) {
			auto src = isMappingNow ? centralData->getMappingSource() : centralData->getMappedSrcFromDst(id);
			if (src.mappable_to(getId().objType) && src.objID >= 0) {
				nvgBeginPath(args.vg);
				nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, box.size.y * 0.5f);
				float alphac = _hovered ? 0.75 : 0.4;
				NVGcolor color = rack::color::alpha(PaletteHub::color(src.objID), alphac);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
			}
		}
	}

	void onEnter(const event::Enter &e) override
	{
		_hovered = true;
		if (!centralData->isMappingInProgress())
			centralData->notifyEnterHover(getId());
	}

	void onLeave(const event::Leave &e) override
	{
		_hovered = false;
		if (!centralData->isMappingInProgress())
			centralData->notifyLeaveHover(getId());
	}

	void onButton(const event::Button &e) override { _inner_knob.onButton(e); }

	const LabelButtonID getId() const
	{
		int64_t moduleId = -1;
		int paramId = -1;
		if (_inner_knob.getParamQuantity()) {
			moduleId = _inner_knob.getParamQuantity()->module ? _inner_knob.getParamQuantity()->module->id : -1;
			paramId = _inner_knob.getParamQuantity()->paramId;
		}
		return {LabelButtonID::Types::Knob, paramId, moduleId};
	}
};

class MappableSliderRing : public MappableKnobRing {
public:
	MappableSliderRing(ParamWidget &inner_knob, float ring_width, float ring_height)
		: MappableKnobRing(inner_knob, 0)
	{
		box.pos = _inner_knob.box.pos.minus({ring_width / 2, ring_height / 2});
		box.size = _inner_knob.box.size.plus({ring_width, ring_height});
	}

	void draw(const DrawArgs &args) override
	{
		auto id = getId();
		bool isMappingNow = centralData->isMappingInProgress();
		if (isMappingNow || centralData->isMappedPartnerHovered(id)) {
			auto src = isMappingNow ? centralData->getMappingSource() : centralData->getMappedSrcFromDst(id);
			if (src.objType == getId().objType && src.objID >= 0) {
				nvgBeginPath(args.vg);
				nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
				float alphac = _hovered ? 0.75 : 0.4;
				NVGcolor color = rack::color::alpha(PaletteHub::color(src.objID), alphac);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
			}
		}
	}
};

template<typename BaseKnobT>
class MappableKnob : public BaseKnobT {
	// static_assert(std::is_base_of_v<app::SvgKnob, BaseKnobT>, "Knob class must derive from SvgKnob");
	// ^^^ this fails for BaseKnobT = LEDLightSlider<WhiteLight>
	// TODO: Make concept

public:
	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		auto src = centralData->getMappedSrcFromDst(getId());
		if (src.moduleID > 0) {
			const NVGcolor color = PaletteHub::color(src.objID);
			MapMark::markKnob(args.vg, this->box, color);
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

			auto moduleid = getId().moduleID;
			auto paramid = getId().objID;

			LabelButtonID dst = getId();
			LabelButtonID src = centralData->getMappedSrcFromDst(dst);

			if ((moduleid >= 0) && src.moduleID != -1) {
				auto aliasItem = new KnobAliasMenuItem{src};
				aliasItem->box.size.x = 120;
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
				ParamField *paramField = new ParamField;
				paramField->box.size.x = 100;
				paramField->setParamWidget(this);
				menu->addChild(paramField);

				MenuSeparator *sep = new MenuSeparator;
				menu->addChild(sep);

				ui::MenuItem *label = new ui::MenuItem;
				label->text = "Not mapped";
				label->rightText = "Click next to a MetaModule knob to begin mapping";
				menu->addChild(label);
			}
			e.consume(this);
		} else {
			// printf("Touch %p, module id %lld\n", this, this->module->id);
			ParamWidget::onButton(e);
		}
	}

	void onHover(const event::Hover &e) override
	{
		// override the e.consume(this) so that the ring will get passed the hover event
	}

private:
	const LabelButtonID getId() // const
	{
		int64_t moduleId = -1;
		int paramId = -1;
		if (this->getParamQuantity()) {
			moduleId = this->getParamQuantity()->module ? this->getParamQuantity()->module->id : -1;
			paramId = this->getParamQuantity()->paramId;
		}
		return {LabelButtonID::Types::Knob, paramId, moduleId};
	}

	struct KnobUnmapItem : ui::MenuItem {
		const LabelButtonID _id;
		KnobUnmapItem(LabelButtonID id)
			: _id{id}
		{}

		void onAction(const event::Action &e) override { centralData->unregisterMapByDest(_id); }
	};

	// ParamLabel: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamLabel : ui::MenuLabel {
		ParamWidget *paramWidget;
		void step() override
		{
			text = paramWidget->getParamQuantity()->getString();
			MenuLabel::step();
		}
	};

	// ParamField: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamField : ui::TextField {
		ParamWidget *paramWidget;

		void step() override
		{
			// Keep selected
			APP->event->setSelectedWidget(this);
			TextField::step();
		}

		void setParamWidget(ParamWidget *paramWidget)
		{
			this->paramWidget = paramWidget;
			if (paramWidget->getParamQuantity())
				text = paramWidget->getParamQuantity()->getDisplayValueString();
			selectAll();
		}

		void onSelectKey(const event::SelectKey &e) override
		{
			if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
				float oldValue = paramWidget->getParamQuantity()->getValue();
				if (paramWidget->getParamQuantity())
					paramWidget->getParamQuantity()->setDisplayValueString(text);
				float newValue = paramWidget->getParamQuantity()->getValue();

				if (oldValue != newValue) {
					// Push ParamChange history action
					history::ParamChange *h = new history::ParamChange;
					h->moduleId = paramWidget->getParamQuantity()->module->id;
					h->paramId = paramWidget->getParamQuantity()->paramId;
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
