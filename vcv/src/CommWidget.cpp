#include "CommWidget.h"
#include "paletteHub.hh"

void CommModuleWidget::addModuleTitle(const std::string moduleTitle)
{
	Label *moduleLabel = new Label();
	moduleLabel->text = moduleTitle;
	moduleLabel->box.pos = {0, 0};
	moduleLabel->box.size.x = box.size.x;
	moduleLabel->color = rack::color::BLACK;
	moduleLabel->alignment = Label::CENTER_ALIGNMENT;
	moduleLabel->fontSize = 13;
	addChild(moduleLabel);
}

void CommModuleWidget::addLabeledKnob(const std::string labelText, int knobID, Vec posGrid, float defaultValue)
{
	addLabeledKnobPx(labelText, knobID, gridFromTop2px(posGrid), defaultValue);
}

void CommModuleWidget::addLabeledKnobMM(const std::string labelText, int knobID, Vec posMM, float defaultValue)
{
	addLabeledKnobPx(labelText, knobID, mm2px(posMM), defaultValue);
}

void CommModuleWidget::addLabeledKnobPx(const std::string labelText, int knobID, Vec posPx, float defaultValue)
{
	addLabel(labelText, posPx, {LabelButtonID::Types::Knob, knobID, -1});
	auto p = createParamCentered<RoundBlackKnob>(posPx, module, knobID);
	if (p->paramQuantity) {
		p->paramQuantity->defaultValue = defaultValue;
		p->paramQuantity->label = labelText;
	}
	addParam(p);
}

void CommModuleWidget::addSmallLabeledKnob(const std::string labelText, int knobID, Vec posGrid, float defaultValue)
{
	addLabeledKnobPx(labelText, knobID, gridFromTop2px(posGrid), defaultValue);
}

void CommModuleWidget::addSmallLabeledKnobMM(const std::string labelText, int knobID, Vec posMM, float defaultValue)
{
	addLabeledKnobPx(labelText, knobID, mm2px(posMM), defaultValue);
}

void CommModuleWidget::addSmallLabeledKnobPx(const std::string labelText, int knobID, Vec posPx, float defaultValue)
{
	addLabel(labelText, posPx, {LabelButtonID::Types::Knob, knobID, -1});
	auto p = createParamCentered<RoundSmallBlackKnob>(posPx, module, knobID);
	if (p->paramQuantity) {
		p->paramQuantity->defaultValue = defaultValue;
		p->paramQuantity->label = labelText;
	}
	addParam(p);
}

void CommModuleWidget::addLabeledInput(const std::string labelText, int inputID, Vec posGrid)
{
	addLabeledInputPx(labelText, inputID, gridFromBottom2px(posGrid));
}

void CommModuleWidget::addLabeledInputMM(const std::string labelText, int inputID, Vec posMM)
{
	addLabeledInputPx(labelText, inputID, mm2px(posMM));
}

void CommModuleWidget::addLabeledInputPx(const std::string labelText, int inputID, Vec posPx)
{
	addLabel(labelText, posPx, {LabelButtonID::Types::InputJack, inputID, -1});
	addInput(createInputCentered<PJ301MPort>(posPx, module, inputID));
}

void CommModuleWidget::addLabeledOutput(const std::string labelText, int outputID, Vec posGrid)
{
	addLabeledOutputPx(labelText, outputID, gridFromBottom2px(posGrid));
}

void CommModuleWidget::addLabeledOutputMM(const std::string labelText, int outputID, Vec posMM)
{
	addLabeledOutputPx(labelText, outputID, mm2px(posMM));
}
void CommModuleWidget::addLabeledOutputPx(const std::string labelText, int outputID, Vec posPx)
{
	addLabel(labelText, posPx, {LabelButtonID::Types::OutputJack, outputID, -1});
	addOutput(createOutputCentered<PJ301MPort>(posPx, module, outputID));
}

LabeledButton *CommModuleWidget::createLabel()
{
	auto tmp = new LabeledButton{*this};
	tmp->isOnHub = false;
	return tmp;
}

void CommModuleWidget::addLabel(const std::string labelText, Vec posPx, LabelButtonID id)
{
	LabeledButton *button = createLabel();
	button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y + mm2px(kTextOffset));
	button->box.size.x = mm2px(kKnobSpacingX);
	button->box.size.y = 18;
	button->text = labelText;
	button->id = id;
	addChild(button);
}

void CommModuleWidget::addLabeledToggle(const std::string labelText, int lightID, int paramID, Vec posGrid)
{
	const Vec posMM = {gridToXCentered(posGrid.x), gridToYFromBottom(posGrid.y)};
	addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px(posMM), module, paramID));
	addChild(createLight<LEDBezelLight<WhiteLight>>(mm2px({posMM.x - 3.0f, posMM.y - 3.0f}), module, lightID));
	addLabel(labelText, mm2px({posMM.x + 17, posMM.y - 6.7f}), {LabelButtonID::Types::Toggle, paramID, -1});
}

void CommModuleWidget::addLabeledToggleMM(const std::string labelText,
										  const int lightID,
										  const int paramID,
										  const Vec position)
{
	addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px(position), module, paramID));
	addChild(createLight<LEDBezelLight<WhiteLight>>(mm2px({position.x - 3.0f, position.y - 3.0f}), module, lightID));
	addLabel(labelText, mm2px({position.x, position.y - 1.f}), {LabelButtonID::Types::Toggle, paramID, -1});
}

constexpr float CommModuleWidget::gridToYFromTop(const float y)
{
	return y * kKnobSpacingY + kTopMargin;
}

constexpr float CommModuleWidget::gridToYFromBottom(const float y)
{
	return kModuleHeight - (y * kKnobSpacingY) - kBottomMargin;
}
constexpr float CommModuleWidget::gridToXCentered(const float x)
{
	return kKnobSpacingX * (x + 0.5f);
}

Vec CommModuleWidget::gridFromTop2mm(Vec posGrid)
{
	return {gridToXCentered(posGrid.x), gridToYFromTop(posGrid.y)};
}

Vec CommModuleWidget::gridFromBottom2mm(Vec posGrid)
{
	return {gridToXCentered(posGrid.x), gridToYFromBottom(posGrid.y)};
}

Vec CommModuleWidget::gridFromTop2px(Vec posGrid)
{
	return mm2px(gridFromTop2mm(posGrid));
}

Vec CommModuleWidget::gridFromBottom2px(Vec posGrid)
{
	return mm2px(gridFromBottom2mm(posGrid));
}

// Todo: disallow creating an InputJack mapping to a patched jack
// Can probably not highlight input jacks that are patched (if we can get that info from the module or centralData)
// Consider how to handle:
// User makes the InJack mapping on an unpatched jack, then patches the jack
//
// Or allow everything but then give an error when creating the patch?
//
// Related todo: how to handle patching the Panel jacks to its own modules...!
void CommModuleWidget::notifyLabelButtonClicked(LabeledButton &button)
{
	button.id.moduleID = module->id;

	if (centralData->isMappingInProgress()) {
		if (centralData->getMappingSource().objType == button.id.objType) {

			if (button.isMapped) {
				centralData->unregisterMapByDest(button.id);

				if (button.mappedToId == centralData->getMappingSource()) {
					button.isMapped = false;
					button.mappedToId.moduleID = -1;
					button.mappedToId.objID = -1;
				} else {
					button.createMapping(centralData->getMappingSource());
				}

			} else {
				button.createMapping(centralData->getMappingSource());
			}
		}
	} else {
		// Todo: Initiate a mapping (virtual module clicked first)
	}
}

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
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

void LabeledButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	bool isTypeKnob = this->id.objType == LabelButtonID::Types::Knob;

	if (isOnHub || (!isOnHub && !isTypeKnob)) {
		_parent.notifyLabelButtonClicked(*this);
	}

	if (quantity)
		quantity->setMax();
}

void MetaModuleTextBox::draw(const DrawArgs &args)
{
	// Todo: draw it a custom way
	LedDisplayTextField::draw(args);
}
