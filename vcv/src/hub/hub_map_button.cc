#include "hub_map_button.hh"
#include "../mapping/central_data.hh"
#include "../mapping/map_palette.hh"
#include <cstdio>

void HubMapButton::updateState() {
	hubParamObj.moduleID = parent.module ? parent.module->id : -1;

	isCurrentMapSrc = false;
	if (centralData->isMappingInProgress() && (centralData->getMappingSource() == hubParamObj)) {
		isCurrentMapSrc = true;
	}
	mappedToId = centralData->getMappedDstFromSrc(hubParamObj);
	isMapped = mappedToId.objType != MappableObj::Type::None;
}

void HubMapButton::draw(const DrawArgs &args) {
	updateState();

	// Draw a large background circle to highlight a mapping has begun from this knob
	if (isCurrentMapSrc || hovered || centralData->isMappedPartnerHovered(hubParamObj)) {
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, box.size.y / 2);
		const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color(hubParamObj.objID), alpha));
		nvgFill(args.vg);
	}

	// Draw the label text
	// CRASHES
	if (hub) {
		text = hub->mappings.getMapAliasName(hubParamObj);
		nvgBeginPath(args.vg);
		nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
		nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
		nvgFontSize(args.vg, 9.0f);
		nvgText(args.vg, box.size.x / 2.0f, box.size.y + 10, text.c_str(), NULL);
	}
}

void HubMapButton::onDragStart(const rack::event::DragStart &e) {
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	// Start a mapping unless one is in progress from this object (in which case, abort it)
	bool currentSourceIsThisButton = false;

	if (centralData->isMappingInProgress()) {
		currentSourceIsThisButton = (centralData->getMappingSource() == hubParamObj);
		centralData->abortMappingProcedure();
	}
	if (!currentSourceIsThisButton) {
		printf("Starting mapping: src m:%lld, p:%lld, t:%d\n",
			   hubParamObj.moduleID,
			   hubParamObj.objID,
			   hubParamObj.objType);
		centralData->startMappingProcedure(hubParamObj);
	}

	if (quantity)
		quantity->setMax();
}

void HubMapButton::onHover(const rack::event::Hover &e) {
	e.consume(this);
}

void HubMapButton::onLeave(const rack::event::Leave &e) {
	hovered = false;
	centralData->notifyLeaveHover(hubParamObj);
	e.consume(this);
}

void HubMapButton::onEnter(const rack::event::Enter &e) {
	hovered = true;
	centralData->notifyEnterHover(hubParamObj);
	e.consume(this);
}
