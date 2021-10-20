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
	if (!isOnHub) {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == id.objType)) {
			isPossibleMapDest = true;
		}
		mappedToId = centralData->getMappedSrcFromDst(this->id);
	} else {
		if (centralData->isMappingInProgress() && (centralData->getMappingSource() == id)) {
			isCurrentMapSrc = true;
		}
		mappedToId = centralData->getMappedDstFromSrc(this->id);
	}
	isMapped = mappedToId.objType != LabelButtonID::Types::None;
}

void LabeledButton::draw(const DrawArgs &args)
{
	updateState();

	bool isTypeJack =
		this->id.objType == LabelButtonID::Types::InputJack || this->id.objType == LabelButtonID::Types::OutputJack;
	if (isTypeJack) {
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 5.0);
		if (isMapped) {
			unsigned palid = (isOnHub ? id.objID : mappedToId.objID) & 0x7; // Todo: handle more than 8 colors
			nvgStrokeColor(args.vg, PaletteHub::color[palid]);
			nvgStrokeWidth(args.vg, 2.0f);
		}
		if (!isMapped) {
			nvgStrokeColor(args.vg, rack::color::WHITE);
			nvgStrokeWidth(args.vg, 0.0);
		}
		if (isPossibleMapDest) {
			nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.8f));
		} else if (isCurrentMapSrc) {
			nvgFillColor(args.vg, rack::color::alpha(rack::color::BLUE, 0.8f));
		} else {
			nvgFillColor(args.vg, rack::color::alpha(rack::color::BLACK, 0.0f));
		}
		nvgStroke(args.vg);
		nvgFill(args.vg);
	}

	if (APP->event->hoveredWidget == this)
		nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.4f));

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

	// FixMe: same as (isOnHub || !isTypeKnob)
	if (isOnHub || (!isOnHub && !isTypeKnob)) {
		_parent.notifyLabelButtonClicked(*this);
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
