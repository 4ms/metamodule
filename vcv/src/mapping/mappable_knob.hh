#pragma once
#include "map_marks.hh"
#include "map_palette.hh"
#include "central_data.hh"
#include "util/base_concepts.hh"
#include <rack.hpp>

class MappableKnobRing : public rack::OpaqueWidget {
protected:
	rack::ParamWidget &_inner_knob;
	bool _hovered = false;

public:
	MappableKnobRing(rack::ParamWidget &inner_knob, float ring_thickness)
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

	void onEnter(const rack::event::Enter &e) override
	{
		_hovered = true;
		if (!centralData->isMappingInProgress())
			centralData->notifyEnterHover(getId());
	}

	void onLeave(const rack::event::Leave &e) override
	{
		_hovered = false;
		if (!centralData->isMappingInProgress())
			centralData->notifyLeaveHover(getId());
	}

	void onButton(const rack::event::Button &e) override { _inner_knob.onButton(e); }

	const MappableObj getId() const
	{
		int64_t moduleId = -1;
		int paramId = -1;
		if (_inner_knob.getParamQuantity()) {
			moduleId = _inner_knob.getParamQuantity()->module ? _inner_knob.getParamQuantity()->module->id : -1;
			paramId = _inner_knob.getParamQuantity()->paramId;
		}
		return {MappableObj::Type::Knob, paramId, moduleId};
	}
};

class MappableSliderRing : public MappableKnobRing {
public:
	MappableSliderRing(rack::ParamWidget &inner_knob, float ring_width, float ring_height)
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

struct KnobAliasTextBox : rack::ui::TextField {
	MappableObj _src;
	KnobAliasTextBox(MappableObj src)
		: _src{src}
	{}

	void onChange(const rack::event::Change &e) override { centralData->setMapAliasName(_src, text); }
};


struct KnobAliasMenuItem : rack::widget::Widget {
	MappableObj _src;
	KnobAliasTextBox *txt;

	KnobAliasMenuItem(MappableObj src)
		: _src{src}
	{
		box.pos = {0, 0};
		box.size = {120, BND_WIDGET_HEIGHT};
		txt = new KnobAliasTextBox{src};
		txt->box.pos = {45, 0};
		txt->box.size = {120 - txt->box.pos.x, BND_WIDGET_HEIGHT};
		txt->text = centralData->getMapAliasName(_src);
		addChild(txt);
	}

	void draw(const DrawArgs &args) override
	{
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Alias:");
		Widget::draw(args);
	}
};

enum class RangePart { Min, Max };
template<RangePart MINMAX>
struct MappedRangeQuantity : rack::Quantity {
private:
	float _val{0.f};
	std::string _label;
	MappableObj const _dst_id;

public:
	MappedRangeQuantity(std::string label, MappableObj const knobLabelID)
		: _label{label}
		, _dst_id{knobLabelID}
	{}
	void setValue(float value) override
	{
		_val = MathTools::constrain(value, 0.0f, 1.0f);
		if constexpr (MINMAX == RangePart::Min)
			centralData->setMapRangeMin(_dst_id, _val);
		else
			centralData->setMapRangeMax(_dst_id, _val);
	}
	float getValue() override
	{
		float val;
		if constexpr (MINMAX == RangePart::Min)
			val = centralData->getMapRange(_dst_id).first;
		else
			val = centralData->getMapRange(_dst_id).second;
		return val;
	}
	// clang-format off
	float getMinValue() override { return 0; }
	float getMaxValue() override { return 1; }
	float getDefaultValue() override { return 0.0; }
	float getDisplayValue() override { return getValue() * 100.f; }
	void setDisplayValue(float displayValue) override { setValue(displayValue / 100.f); }
	std::string getLabel() override { return _label; }
	std::string getUnit() override { return "%"; }
	// clang-format on
};


struct MinSlider : rack::ui::Slider {
public:
	MinSlider(MappableObj const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Min>{"Min: ", knobLabelID};
	}
	~MinSlider() { delete quantity; }
};

struct MaxSlider : rack::ui::Slider {
public:
	MaxSlider(MappableObj const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Max>{"Max: ", knobLabelID};
	}
	~MaxSlider() { delete quantity; }
};

template<typename BaseKnobT>
class MappableInnerKnob : public BaseKnobT {
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
	void onButton(const rack::event::Button &e) override
	{
		rack::OpaqueWidget::onButton(e);

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			rack::ui::Menu *menu = rack::createMenu();

			ParamLabel *paramLabel = new ParamLabel;
			paramLabel->paramWidget = this;
			menu->addChild(paramLabel);

			auto moduleid = getId().moduleID;
			auto paramid = getId().objID;

			MappableObj dst = getId();
			MappableObj src = centralData->getMappedSrcFromDst(dst);

			if ((moduleid >= 0) && src.moduleID != -1) {
				auto aliasItem = new KnobAliasMenuItem{src};
				aliasItem->box.size.x = 120;
				menu->addChild(aliasItem);

				MinSlider *mn = new MinSlider({MappableObj::Type::Knob, paramid, moduleid});
				mn->box.size.x = 100;
				menu->addChild(mn);

				MaxSlider *mx = new MaxSlider({MappableObj::Type::Knob, paramid, moduleid});
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

				rack::MenuSeparator *sep = new rack::MenuSeparator;
				menu->addChild(sep);

				rack::ui::MenuItem *label = new rack::ui::MenuItem;
				label->text = "Not mapped";
				label->rightText = "Click next to a MetaModule knob to begin mapping";
				menu->addChild(label);
			}
			e.consume(this);
		} else {
			// printf("Touch %p, module id %lld\n", this, this->module->id);
			rack::ParamWidget::onButton(e);
		}
	}

	void onHover(const rack::event::Hover &e) override
	{
		// override the e.consume(this) so that the ring will get passed the hover event
	}

private:
	const MappableObj getId() // const
	{
		int64_t moduleId = -1;
		int paramId = -1;
		if (this->getParamQuantity()) {
			moduleId = this->getParamQuantity()->module ? this->getParamQuantity()->module->id : -1;
			paramId = this->getParamQuantity()->paramId;
		}
		return {MappableObj::Type::Knob, paramId, moduleId};
	}

	struct KnobUnmapItem : rack::ui::MenuItem {
		const MappableObj _id;
		KnobUnmapItem(MappableObj id)
			: _id{id}
		{}

		void onAction(const rack::event::Action &e) override { centralData->unregisterMapByDest(_id); }
	};

	// ParamLabel: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamLabel : rack::ui::MenuLabel {
		rack::ParamWidget *paramWidget;
		void step() override
		{
			text = paramWidget->getParamQuantity()->getString();
			MenuLabel::step();
		}
	};

	// ParamField: copied from Rack/src/app/ParamWidget.cpp (not exported)
	struct ParamField : rack::ui::TextField {
		rack::ParamWidget *paramWidget;

		void step() override
		{
			// Keep selected
			APP->event->setSelectedWidget(this);
			TextField::step();
		}

		void setParamWidget(rack::ParamWidget *paramWidget)
		{
			this->paramWidget = paramWidget;
			if (paramWidget->getParamQuantity())
				text = paramWidget->getParamQuantity()->getDisplayValueString();
			selectAll();
		}

		void onSelectKey(const rack::event::SelectKey &e) override
		{
			if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
				float oldValue = paramWidget->getParamQuantity()->getValue();
				if (paramWidget->getParamQuantity())
					paramWidget->getParamQuantity()->setDisplayValueString(text);
				float newValue = paramWidget->getParamQuantity()->getValue();

				if (oldValue != newValue) {
					// Push ParamChange history action
					rack::history::ParamChange *h = new rack::history::ParamChange;
					h->moduleId = paramWidget->getParamQuantity()->module->id;
					h->paramId = paramWidget->getParamQuantity()->paramId;
					h->oldValue = oldValue;
					h->newValue = newValue;
					APP->history->push(h);
				}

				rack::ui::MenuOverlay *overlay = getAncestorOfType<rack::ui::MenuOverlay>();
				overlay->requestDelete();
				e.consume(this);
			}

			if (!e.getTarget())
				TextField::onSelectKey(e);
		}
	};
};

template<typename BaseKnobT>
class MappableKnob : public MappableInnerKnob<BaseKnobT> {

public:
	MappableKnob() {
		this->addChild(new MappableKnobRing{*this, 10});
	}
};
