#pragma once
#include "hub_knob.hh"

class HubMidiMapButton : public HubKnobMapButton {
	// ParamQuantity *paramQuantity = nullptr;

public:
	HubMidiMapButton(CommModuleWidget &parent)
		: HubKnobMapButton{static_cast<CommModuleWidget &>(parent)}
	{}

	// void draw(const DrawArgs &args) override { HubKnobMapButton::draw(args); }

	// void setParamQuantity(ParamQuantity *paramQ) { paramQuantity = paramQ; }

	// void onDeselect(const event::Deselect &e) override
	// {
	// 	bool registerSuccess = false;

	// 	// Check if a ParamWidget was touched
	// 	ParamWidget *touchedParam = APP->scene->rack->getTouchedParam();
	// 	printf("touchedParam: %p\n", touchedParam);
	// 	if (touchedParam && touchedParam->getParamQuantity()) {
	// 		printf("touchedParam->PQ: %p\n", touchedParam->getParamQuantity());

	// 		int64_t moduleId = touchedParam->module->id;
	// 		printf("touchedParam->module->id: %lld\n", touchedParam->module->id);

	// 		int objId = touchedParam->getParamQuantity()->paramId;
	// 		printf("touchedParam->PQ->paramId: %d\n", touchedParam->getParamQuantity()->paramId);

	// 		APP->scene->rack->setTouchedParam(nullptr);

	// 		registerSuccess = registerMapping(moduleId, objId);
	// 	}

	// 	if (!registerSuccess) {
	// 		centralData->abortMappingProcedure();
	// 		printf("Failed mapping\n");
	// 	}
	// }

	// void onButton(const event::Button &e) override
	// {
	// 	// Right click to open context menu
	// 	if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
	// 		if (paramQuantity) {
	// 			makeKnobMenu(paramQuantity, id);
	// 			e.consume(this);
	// 		}
	// 	} else {
	// 		Button::onButton(e);
	// 	}
	// }
	// TODO: add right-click menu, same as in HubKnob
};

class HubMidiParam : public ParamWidget {
public:
	HubMidiParam(HubMidiMapButton &hubmidi_mapbut)
		: hubmidi_mapbut{hubmidi_mapbut}
	{}

	void draw(const DrawArgs &args) override
	{
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 10);
		nvgStrokeColor(args.vg, rack::color::BLACK);
		nvgStroke(args.vg);

		nvgBeginPath(args.vg);
		nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
		nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
		nvgFontSize(args.vg, 9.0f);
		nvgText(args.vg, box.size.x / 2.f, box.size.y / 2.f, hubmidi_mapbut.text.c_str(), NULL);

		auto numMaps = std::min(centralData->getNumMappingsFromSrc(hubmidi_mapbut.id), 16U);

		const float spacing = 8;
		const NVGcolor color = PaletteHub::color(hubmidi_mapbut.id.objID);
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
				makeKnobMenu(this->getParamQuantity(), hubmidi_mapbut.id);
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
		if (centralData->isLabelButtonSrcMapped(hubmidi_mapbut.id))
			return;

		e.consume(this);
	}

	struct ParamResetItem : ui::MenuItem {
		ParamWidget *paramWidget;
		void onAction(const event::Action &e) override { paramWidget->resetAction(); }
	};

private:
	HubKnobMapButton &hubmidi_mapbut;
};
