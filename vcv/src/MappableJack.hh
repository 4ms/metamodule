#pragma once
#include "paletteHub.hh"
#include "plugin.hpp"
#include <rack.hpp>

template<typename BaseJackT>
class MappableJack : public BaseJackT {
public:
	MappableJack() = default;

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		BaseJackT::draw(args);

		int moduleId = this->module ? this->module->id : -1;
		if (moduleId >= 0 && this->portId >= 0) {
			LabelButtonID tryInputJack = {LabelButtonID::Types::InputJack, this->portId, moduleId};
			LabelButtonID tryOutputJack = {LabelButtonID::Types::OutputJack, this->portId, moduleId};
			LabelButtonID id;
			bool isMapped = false;
			if (centralData->isLabelButtonDstMapped(tryInputJack)) {
				isMapped = true;
				id = tryInputJack;
			} else if (centralData->isLabelButtonDstMapped(tryOutputJack)) {
				isMapped = true;
				id = tryOutputJack;
			}

			// Draw mapped circle
			if (isMapped) {
				const float radius = 4;
				int srcPortId = centralData->getMappedSrcFromDst(id).objID;
				NVGcolor color = PaletteHub::color[srcPortId];
				nvgBeginPath(args.vg);
				nvgCircle(args.vg, this->box.size.x - radius, this->box.size.y - radius, radius);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
				nvgStrokeColor(args.vg, color::mult(color, 0.5));
				nvgStrokeWidth(args.vg, 1.0f);
				nvgStroke(args.vg);
			}
		}
	}

	void onButton(const event::Button &e) override
	{
		OpaqueWidget::onButton(e);

		// Touch port
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			centralData->registerTouchedJack(this);
			e.consume(this);
		}
	}
};
