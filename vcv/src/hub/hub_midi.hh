#pragma once
#include "hub_knob.hh"

class HubMidiMapButton : public HubKnobMapButton {

public:
	HubMidiMapButton(rack::app::ModuleWidget &parent)
		: HubKnobMapButton{static_cast<rack::app::ModuleWidget &>(parent)} {
	}

	void draw(const DrawArgs &args) override {
		HubMapButton::_updateState();

		// Same as HubMapButton::draw except use a rounded rect, and don't draw alias below

		// Draw a large background rounded rect to highlight a mapping has begun from this knob
		if (isCurrentMapSrc || _hovered || centralData->isMappedPartnerHovered(hubParamObj)) {
			// const float padding_x = 2;
			nvgBeginPath(args.vg);
			nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 4);
			const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
			nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color(hubParamObj.objID), alpha));
			nvgFill(args.vg);
		}
	}

	//TODO:
	//
	// void onDragStart(const rack::event::DragStart &e) override
	// {
	// 	if (id.objType == MappableObj::Type::MidiNote) {
	// 	}
	// }
};

class HubMidiParam : public rack::ParamWidget {
public:
	HubMidiParam(HubMidiMapButton &hubmidi_mapbut)
		: hubmidi_mapbut{hubmidi_mapbut} {
	}

	void draw(const DrawArgs &args) override {
		auto numMaps = std::min(centralData->getNumMappingsFromSrc(hubmidi_mapbut.hubParamObj), 16U);

		// TODO: different color for each one
		const float spacing = 8;
		const NVGcolor color = PaletteHub::color(hubmidi_mapbut.hubParamObj.objID);
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
				hubmidi_mapbut.makeKnobMenu(); //this->getParamQuantity(), hubmidi_mapbut.mapObj);
				e.consume(this);
			}
		}
	}

	void onHover(const rack::event::Hover &e) override {
		// For MidiMap, always show the highlight. Returning allows HubMidiMapButton to handle onHover
		return;
	}

	// onDeselect and onDragStart are passed to the HubMidiMapButton
	// In order to make the HubMidiParam seem "invisible"
	// but still will accept onButton events so it can be mapped
	// to VCV's MidiMaps module
	void onDeselect(const rack::event::Deselect &e) override {
		rack::ParamWidget::onDeselect(e);
		hubmidi_mapbut.onDeselect(e);
	}

	void onDragStart(const rack::event::DragStart &e) override {
		hubmidi_mapbut.onDragStart(e);
	}

	struct ParamResetItem : rack::ui::MenuItem {
		rack::ParamWidget *paramWidget;
		void onAction(const rack::event::Action &e) override {
			paramWidget->resetAction();
		}
	};

private:
	HubKnobMapButton &hubmidi_mapbut;
};
