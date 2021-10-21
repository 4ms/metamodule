#pragma once
#include "paletteHub.hh"
#include "plugin.hpp"
#include <rack.hpp>

enum class MappableJackType { Input, Output };

template<MappableJackType InputOrOutput, typename BaseJackT>
class MappableJack : public BaseJackT {
public:
	MappableJack() = default;

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		BaseJackT::draw(args);

		int moduleId = this->module ? this->module->id : -1;
		if (moduleId >= 0 && this->portId >= 0) {
			LabelButtonID id;
			if constexpr (InputOrOutput == MappableJackType::Input)
				id = {LabelButtonID::Types::InputJack, this->portId, moduleId};
			else
				id = {LabelButtonID::Types::OutputJack, this->portId, moduleId};

			bool isMapped = centralData->isLabelButtonDstMapped(id);

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

		// Register this jack with CentralData as the "TouchedJack",
		// Hub jacks can use this to determine what jack you clicked on after clicking on the Hub Jack Mapping Button,
		// when creating a new mapping
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			centralData->registerTouchedJack(this);
			e.consume(this);
		}
	}

	// TODO: right-click menui
};

template<typename BaseJackT>
using MappableInputJack = MappableJack<MappableJackType::Input, BaseJackT>;

template<typename BaseJackT>
using MappableOutputJack = MappableJack<MappableJackType::Output, BaseJackT>;
