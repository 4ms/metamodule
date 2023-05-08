#pragma once
#include "hub_knob.hh"

class HubMidiMapButton : public HubKnobMapButton {

public:
	HubMidiMapButton(app::ModuleWidget &parent)
		: HubKnobMapButton{static_cast<app::ModuleWidget &>(parent)}
	{}

	void draw(const DrawArgs &args) override
	{
		HubMapButton::_updateState();

		// Same as HubMapButton::draw except use a rounded rect, and don't draw alias below

		// Draw a large background rounded rect to highlight a mapping has begun from this knob
		if (isCurrentMapSrc || _hovered || centralData->isMappedPartnerHovered(mapObj)) {
			// const float padding_x = 2;
			nvgBeginPath(args.vg);
			nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 4);
			const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
			nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color(mapObj.objID), alpha));
			nvgFill(args.vg);
		}
	}

	//TODO:
	// 
	// void onDragStart(const event::DragStart &e) override
	// {
	// 	if (id.objType == MappableObj::Type::MidiNote) {
	// 	}
	// }
};

class HubMidiParam : public ParamWidget {
public:
	HubMidiParam(HubMidiMapButton &hubmidi_mapbut)
		: hubmidi_mapbut{hubmidi_mapbut}
	{}

	void draw(const DrawArgs &args) override
	{
		auto numMaps = std::min(centralData->getNumMappingsFromSrc(hubmidi_mapbut.mapObj), 16U);

		// TODO: different color for each one
		const float spacing = 8;
		const NVGcolor color = PaletteHub::color(hubmidi_mapbut.mapObj.objID);
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
				makeKnobMenu(this->getParamQuantity(), hubmidi_mapbut.mapObj);
				e.consume(this);
			}
		}
	}

	void onHover(const event::Hover &e) override
	{
		// For MidiMap, always show the highlight. Returning allows HubMidiMapButton to handle onHover
		return;
	}

	// onDeselect and onDragStart are passed to the HubMidiMapButton
	// In order to make the HubMidiParam seem "invisible"
	// but still will accept onButton events so it can be mapped
	// to VCV's MidiMaps module
	void onDeselect(const event::Deselect &e) override
	{
		ParamWidget::onDeselect(e);
		hubmidi_mapbut.onDeselect(e);
	}

	void onDragStart(const event::DragStart &e) override { hubmidi_mapbut.onDragStart(e); }

	struct ParamResetItem : ui::MenuItem {
		ParamWidget *paramWidget;
		void onAction(const event::Action &e) override { paramWidget->resetAction(); }
	};

private:
	HubKnobMapButton &hubmidi_mapbut;
};
