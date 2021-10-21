#include "hub_knob.hh"
#include "CommModule.h"
#include "paletteHub.hh"

void HubKnobMapButton::onDeselect(const event::Deselect &e)
{
	if (!_knobmap)
		return;

	// Check if a ParamWidget was touched
	ParamWidget *touchedParam = APP->scene->rack->touchedParam;

	if (touchedParam && centralData->isMappingInProgress()) {
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;
		APP->scene->rack->touchedParam = NULL;

		// Todo: clean up this logic, don't have two calls to abortMappingProcedure()
		if (id.moduleID != moduleId) {
			printf("HubKnobMapButton::onDeselect our id=%d, touchedParam->paramQuantity->moduleId=%d\n",
				   id.moduleID,
				   moduleId);
			// Todo: Check if already mapped to a different hub. Use centralData to query if the moduleId has been
			// registered as a hub
			int thisKnob = id.objID;
			if (_knobmap->create(moduleId, paramId, PaletteHub::color[thisKnob])) {
				centralData->registerMapDest({LabelButtonID::Types::Knob, paramId, moduleId});
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

void HubKnobMapButton::draw(const DrawArgs &args)
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

void HubKnobMapButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	// id.moduleID = _parent.getModuleId();

	printf("HubKnobMapButton::onDragStart() moduleID=%d\n", id.moduleID);
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
