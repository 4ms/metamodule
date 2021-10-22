#include "HubMapButton.hh"
#include "paletteHub.hh"

void HubMapButton::_createMapping(LabelButtonID srcId)
{
	isMapped = true;
	mappedToId = srcId;
	centralData->registerMapDest(id);
}

void HubMapButton::_updateState()
{
	id.moduleID = _parent.getModuleId();

	isCurrentMapSrc = false;
	isPossibleMapDest = false;
	if (isOnHub) {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource() == id)) {
			isCurrentMapSrc = true;
		}
		mappedToId = centralData->getMappedDstFromSrc(id);
	} else {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == id.objType)) {
			isPossibleMapDest = true;
		}
		mappedToId = centralData->getMappedSrcFromDst(id);
	}
	isMapped = mappedToId.objType != LabelButtonID::Types::None;
}

void HubMapButton::draw(const DrawArgs &args)
{
	_updateState();

	// Draw huge background rect to highlight a mapping has begun from this knob
	if (isCurrentMapSrc) {
		float padding_x = 2;
		float knob_height = 40;
		auto knobNum = id.objID;
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, padding_x, -knob_height, box.size.x - padding_x * 2, knob_height + box.size.y, 5.0);
		nvgStrokeColor(args.vg, rack::color::WHITE);
		nvgStrokeWidth(args.vg, 0.0);
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color[knobNum], 0.75f));
		nvgStroke(args.vg);
		nvgFill(args.vg);
	}

	// Draw the label text
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);

	// if (APP->event->hoveredWidget == this)
	// 	nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.4f));
}

void HubMapButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	printf("HubMapButton::onDragStart() moduleID=%d type=%s\n", id.moduleID, id.objTypeStr());
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
