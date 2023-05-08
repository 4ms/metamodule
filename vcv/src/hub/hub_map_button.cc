#include "hub_map_button.hh"
#include "map_palette.hh"
#include "central_data.hh"
#include <cstdio>

void HubMapButton::_updateState()
{
	mapObj.moduleID = _parent.module ? _parent.module->id : -1;

	isCurrentMapSrc = false;
	if (centralData->isMappingInProgress() && (centralData->getMappingSource() == mapObj)) {
		isCurrentMapSrc = true;
	}
	mappedToId = centralData->getMappedDstFromSrc(mapObj);
	isMapped = mappedToId.objType != MappableObj::Type::None;
}

void HubMapButton::draw(const DrawArgs &args)
{
	_updateState();

	// Draw a large background circle to highlight a mapping has begun from this knob
	if (isCurrentMapSrc || _hovered || centralData->isMappedPartnerHovered(mapObj)) {
		// const float padding_x = 2;
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, box.size.y / 2);
		const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color(mapObj.objID), alpha));
		nvgFill(args.vg);
	}

	// Draw the label text
	text = centralData->getMapAliasName(mapObj);
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 9.0f);
	// nvgFontFaceId(args.vg, fontid);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y + 10, text.c_str(), NULL);
}

void HubMapButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	// Start a mapping unless one is in progress from this object (in which case, abort it)
	bool currentSourceIsThisButton = false;

	if (centralData->isMappingInProgress()) {
		currentSourceIsThisButton = (centralData->getMappingSource() == mapObj);
		centralData->abortMappingProcedure();
	}
	if (!currentSourceIsThisButton) {
		printf("Starting mapping: src m:%lld, p:%lld, t:%d\n", mapObj.moduleID, mapObj.objID, mapObj.objType);
		centralData->startMappingProcedure(mapObj);
	}

	if (quantity)
		quantity->setMax();
}

void HubMapButton::onHover(const event::Hover &e) { e.consume(this); }

void HubMapButton::onLeave(const event::Leave &e)
{
	_hovered = false;
	// if (!centralData->isMappingInProgress())
	centralData->notifyLeaveHover(mapObj);
	e.consume(this);
}

void HubMapButton::onEnter(const event::Enter &e)
{
	_hovered = true;
	// if (!centralData->isMappingInProgress())
	centralData->notifyEnterHover(mapObj);
	e.consume(this);
}

bool HubMapButton::registerMapping(MappableObj src)
{
	if (centralData->isMappingInProgress()) {
		if (src.moduleID > -1) {
			if (mapObj.moduleID != src.moduleID) {
				if (!centralData->isRegisteredHub(src.moduleID)) {
					centralData->registerMapDest(src);
					return true;
				}
			}
		}
	}
	return false;
}
