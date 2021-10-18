#include "hub_knob.hh"
#include "CommModule.h"
#include "paletteHub.hh"

void HubKnobLabel::onDeselect(const event::Deselect &e)
{
	if (!_knobmap)
		return;

	// Check if a ParamWidget was touched
	ParamWidget *touchedParam = APP->scene->rack->touchedParam;
	if (touchedParam && centralData->isMappingInProgress()) {
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;
		APP->scene->rack->touchedParam = NULL;

		if (id.moduleID != moduleId) {

			// Check if it already exists
			// Todo: Use centralData or APP->engine to accomodate multiple Hubs
			bool is_already_mapped = false;
			// for (auto &knobmap : _hub.expModule->knobMaps) {
			// 	if (knobmap.mapping_already_exists(moduleId, paramId)) {
			// 		is_already_mapped = true;
			// 		break;
			// 	}
			// }
			if (!is_already_mapped) {
				int knobToMap = centralData->getMappingSource().objID;
				int thisKnob = id.objID;
				assert(knobToMap == thisKnob);
				if (_knobmap->create(moduleId, paramId, PaletteHub::color[thisKnob])) {
					centralData->registerMapDest({LabelButtonID::Types::Knob, paramId, moduleId});
				}
			} else {
				// already mapped
				centralData->abortMappingProcedure();
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

void HubKnobLabel::draw(const DrawArgs &args)
{
	updateState();

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
