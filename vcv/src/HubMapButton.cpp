#include "HubMapButton.hpp"
#include "paletteHub.hpp"
#include <cstdio>

void HubMapButton::_updateState()
{
	id.moduleID = _parent.module ? _parent.module->id : -1;

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
	if (isCurrentMapSrc || _hovered || centralData->isMappedPartnerHovered(id)) {
		// const float padding_x = 2;
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, box.size.y / 2);
		const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color[id.objID], alpha));
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
	}
	if (!currentSourceIsThisButton) {
		centralData->startMappingProcedure(id);
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
	// if (!centralData->isMappingInProgress())
	centralData->notifyLeaveHover(id);
	e.consume(this);
}

void HubMapButton::onEnter(const event::Enter &e)
{
	_hovered = true;
	// if (!centralData->isMappingInProgress())
	centralData->notifyEnterHover(id);
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
