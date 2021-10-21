#pragma once
#include "LabeledButton.hh"
#include "hub_knob_menu.hh"
#include "knob_map.hh"
#include "paletteHub.hh"

// todo: this whole class is exactly the same as HubKnobMapButton
// except for touchedJack vs touchedParam, and having _knobmap
// Maybe HubMapButton is the base class for both, and each implements its own registerMapping() and getTouched()
class HubJackMapButton : public LabeledButton {
public:
	HubJackMapButton(CommModuleWidget &parent)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
	{}

	void onDragStart(const event::DragStart &e) override
	{
		if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
			return;
		}

		// id.moduleID = _parent.getModuleId();

		printf("HubJackMapButton::onDragStart() moduleID=%d\n", id.moduleID);
		bool currentSourceIsThisButton = false;

		if (centralData->isMappingInProgress()) {
			printf("Mapping is in progress, aborting.\n");
			currentSourceIsThisButton = (centralData->getMappingSource() == id);
			centralData->abortMappingProcedure();
			// TODO: centraData->sendMessage("Aborted mapping");
			// valueLabel->text = "Aborted mapping";
		}
		if (!currentSourceIsThisButton) {
			printf("currentSource is not this button: starting mapping\n");
			centralData->startMappingProcedure(id);
			// TODO: centraData->sendMessage("Started mapping...");
			// valueLabel->text = "Start Mapping from: " + std::to_string(static_cast<int>(button.id.objType)) + ", " +
			// std::to_string(button.id.objID);
		}

		if (quantity)
			quantity->setMax();
	}

	void onDeselect(const event::Deselect &e) override
	{
		// Check if a ParamWidget was touched
		auto touchedJack = centralData->getAndClearTouchedJack();

		if (touchedJack && centralData->isMappingInProgress()) {
			if (touchedJack->module) {
				int moduleId = touchedJack->module->id;
				int jackId = touchedJack->portId;

				if (id.moduleID != moduleId) {
					// Todo: Check if already mapped to a different hub. Use centralData to query if the moduleId has
					// been registered as a hub
					centralData->registerMapDest({id.objType, jackId, moduleId});
				}
			} else {

				// clicked on another knob on this hub
				centralData->abortMappingProcedure();
			}
		} else {
			// Didn't click on a knob -- OR -- we're not mapping
			centralData->abortMappingProcedure();
		}
	}

	void draw(const DrawArgs &args) override
	{
		updateState();

		// Draw huge background rect to highlight a mapping has begun from this knob
		nvgBeginPath(args.vg);
		float padding_x = 2;
		float knob_height = 40;
		nvgRoundedRect(args.vg, padding_x, -knob_height, box.size.x - padding_x * 2, knob_height + box.size.y, 5.0);
		nvgStrokeColor(args.vg, rack::color::WHITE);
		nvgStrokeWidth(args.vg, 0.0);
		// Draw solid bg if this knob is the active mapping source
		if (isCurrentMapSrc) {
			auto knobNum = id.objID;
			nvgFillColor(args.vg, PaletteHub::color[knobNum]);
		} else {
			nvgFillColor(args.vg, rack::color::alpha(rack::color::BLACK, 0.0f));
		}
		nvgStroke(args.vg);
		nvgFill(args.vg);

		nvgBeginPath(args.vg);
		nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
		nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
		nvgFontSize(args.vg, 8.0f);
		nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
	}
};

template<typename BaseJackT>
class HubJack : public BaseJackT {
public:
	HubJack(HubJackMapButton &_hubJackLabel)
		: hubJackLabel{_hubJackLabel}
	{}

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		BaseJackT::draw(args);

		// Draw mapped circle
		if (hubJackLabel.isMapped) {
			const float radius = 4;
			NVGcolor color = PaletteHub::color[hubJackLabel.id.objID];
			nvgBeginPath(args.vg);
			nvgCircle(args.vg, this->box.size.x - radius, this->box.size.y - radius, radius);
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
			nvgStrokeColor(args.vg, color::mult(color, 0.5));
			nvgStrokeWidth(args.vg, 1.0f);
			nvgStroke(args.vg);
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

private:
	HubJackMapButton &hubJackLabel;
};
