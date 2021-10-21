#include "LabeledButton.hh"
#include "paletteHub.hh"

void LabeledButton::createMapping(LabelButtonID srcId)
{
	isMapped = true;
	mappedToId = srcId;
	centralData->registerMapDest(id);
}

void LabeledButton::updateState()
{
	if (_parent.module != nullptr)
		if (_parent.module->id > 0)
			id.moduleID = _parent.module->id;

	isCurrentMapSrc = false;
	isPossibleMapDest = false;
	if (isOnHub) {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource() == id)) {
			isCurrentMapSrc = true;
		}
		mappedToId = centralData->getMappedDstFromSrc(this->id);
	} else {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == id.objType)) {
			isPossibleMapDest = true;
		}
		mappedToId = centralData->getMappedSrcFromDst(this->id);
	}
	isMapped = mappedToId.objType != LabelButtonID::Types::None;
}

void LabeledButton::draw(const DrawArgs &args)
{
	updateState();

	bool isTypeJack =
		this->id.objType == LabelButtonID::Types::InputJack || this->id.objType == LabelButtonID::Types::OutputJack;
	if (isTypeJack) {
		if (isMapped) {
			const float radius = 4;
			// Todo: get the knobmap so we can get the color
			NVGcolor color = PaletteHub::color[(isOnHub ? id.objID : mappedToId.objID) & 0x7];
			nvgBeginPath(args.vg);
			nvgCircle(args.vg, this->box.size.x - radius, this->box.size.y - radius, radius);
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
			nvgStrokeColor(args.vg, color::mult(color, 0.5));
			nvgStrokeWidth(args.vg, 1.0f);
			nvgStroke(args.vg);
			// } else {
		}

		// const int jackHeight = 30;
		NVGcolor color = isPossibleMapDest ? rack::color::alpha(rack::color::YELLOW, 0.8f)
										   : rack::color::alpha(rack::color::BLACK, 0.0f);
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 5.0);
		nvgFillColor(args.vg, color);
		nvgFill(args.vg);
	}

	// if (APP->event->hoveredWidget == this)
	// 	nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.4f));

	// Draw text
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_BOTTOM);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y * 0.75f, text.c_str(), NULL);
}

void LabeledButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	bool isTypeKnob = this->id.objType == LabelButtonID::Types::Knob;

	if (!isTypeKnob) {
		id.moduleID = _parent.getModuleId();

		printf("LabeledButton::onDragStart() moduleID=%d\n", id.moduleID);
		if (centralData->isMappingInProgress()) {
			if (centralData->getMappingSource().objType == id.objType) {
				if (isMapped) {
					centralData->unregisterMapByDest(id);
					if (mappedToId == centralData->getMappingSource()) {
						isMapped = false;
						mappedToId.moduleID = -1;
						mappedToId.objID = -1;
					} else {
						createMapping(centralData->getMappingSource());
					}
				} else {
					createMapping(centralData->getMappingSource());
				}
			}
		}
	}

	if (quantity)
		quantity->setMax();
}

void CenterLabel::draw(const DrawArgs &args)
{
	if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == LabelButtonID::Types::Knob)) {
		nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.8f));
	}
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_BOTTOM);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y * 0.75f, text.c_str(), NULL);
}
