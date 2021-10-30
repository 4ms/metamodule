#include "HubMapButton.hh"
#include "paletteHub.hh"
#include <cstdio>

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
	if (centralData->isMappingInProgress() && (centralData->getMappingSource() == id)) {
		isCurrentMapSrc = true;
	}
	mappedToId = centralData->getMappedDstFromSrc(id);
	isMapped = mappedToId.objType != LabelButtonID::Types::None;
}

void HubMapButton::draw(const DrawArgs &args)
{
	_updateState();

	// Draw huge background rect to highlight a mapping has begun from this knob
	if (isCurrentMapSrc || _hovered) {
		float padding_x = 2;
		auto knobNum = id.objID;
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, padding_x, 0, box.size.x - padding_x * 2, box.size.y, 5.0);
		float alpha = isCurrentMapSrc ? 0.75 : 0.4;
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color[knobNum], alpha));
		nvgFill(args.vg);
	}

	// Draw the label text
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

void HubMapButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	bool currentSourceIsThisButton = false;

	if (centralData->isMappingInProgress()) {
		currentSourceIsThisButton = (centralData->getMappingSource() == id);
		centralData->abortMappingProcedure();
		// TODO: centraData->sendMessage("Aborted mapping");
		// valueLabel->text = "Aborted mapping";
	}
	if (!currentSourceIsThisButton) {
		centralData->startMappingProcedure(id);
		// TODO: centraData->sendMessage("Started mapping...");
		// valueLabel->text = "Start Mapping from: " + std::to_string(static_cast<int>(button.id.objType)) + ", " +
		// std::to_string(button.id.objID);
	}

	if (quantity)
		quantity->setMax();
}
void HubMapButton::onHover(const event::Hover &e)
{
	e.consume(this);
}

void HubMapButton::onLeave(const event::Leave &e)
{
	_hovered = false;
	e.consume(this);
}

void HubMapButton::onEnter(const event::Enter &e)
{
	_hovered = true;
	e.consume(this);
}

bool HubMapButton::registerMapping(int moduleId, int objId)
{
	if (centralData->isMappingInProgress()) {
		if (moduleId > -1) {
			if (id.moduleID != moduleId) {
				if (!centralData->isRegisteredHub(moduleId)) {
					centralData->registerMapDest({id.objType, objId, moduleId});
					return true;
				}
			}
		}
	}
	return false;
}
