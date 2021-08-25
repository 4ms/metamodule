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

void CommModuleWidget::addLabeledKnob(const std::string labelText,
									  const int knobID,
									  const Vec position,
									  const float defaultValue)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromTop(position.y),
	};
	addLabeledKnobMM(labelText, knobID, pos, defaultValue);
}

void CommModuleWidget::addLabeledKnobMM(const std::string labelText,
										const int knobID,
										const Vec position,
										const float defaultValue)
{
	addLabel(labelText, position, {LabelButtonID::Types::Knob, knobID, -1});
	auto p = createParamCentered<RoundBlackKnob>(mm2px(position), module, knobID);
	if (p->paramQuantity)
		p->paramQuantity->defaultValue = defaultValue;
	addParam(p);
}

void CommModuleWidget::addLabeledInput(const std::string labelText, const int inputID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addLabel(labelText, pos, {LabelButtonID::Types::InputJack, inputID, -1});
	addInput(createInputCentered<PJ301MPort>(mm2px(pos), module, inputID));
}

void CommModuleWidget::addLabeledInputMM(const std::string labelText, const int inputID, const Vec position)
{
	addLabel(labelText, position, {LabelButtonID::Types::InputJack, inputID, -1});
	addInput(createInputCentered<PJ301MPort>(mm2px(position), module, inputID));
}

void CommModuleWidget::addLabeledOutput(const std::string labelText, const int outputID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addLabel(labelText, pos, {LabelButtonID::Types::OutputJack, outputID, -1});
	addOutput(createOutputCentered<PJ301MPort>(mm2px(pos), module, outputID));
}

void CommModuleWidget::addLabeledOutputMM(const std::string labelText, const int outputID, const Vec position)
{
	addLabel(labelText, position, {LabelButtonID::Types::OutputJack, outputID, -1});
	addOutput(createOutputCentered<PJ301MPort>(mm2px(position), module, outputID));
}

LabeledButton *CommModuleWidget::createLabel()
{
	auto tmp = new LabeledButton{*this};
	tmp->isOnHub = false;
	return tmp;
}

void CommModuleWidget::addLabel(const std::string labelText, const Vec pos, const LabelButtonID id)
{
	LabeledButton *button = createLabel();
	button->box.pos = mm2px(Vec(pos.x - kKnobSpacingX / 4.0f, pos.y + kTextOffset));
	button->box.size.x = kGridSpacingX / 2.0f;
	button->box.size.y = 12;
	button->text = labelText;
	button->id = id;
	addChild(button);
}

void CommModuleWidget::addLabeledToggle(const std::string labelText,
										const int lightID,
										const int paramID,
										const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px(pos), module, paramID));
	addChild(createLight<LEDBezelLight<WhiteLight>>(mm2px({pos.x - 3.0f, pos.y - 3.0f}), module, lightID));
	addLabel(labelText, {pos.x + 17, pos.y - 6.7f}, {LabelButtonID::Types::Toggle, paramID, -1});
}

void CommModuleWidget::addLabeledToggleMM(const std::string labelText,
										  const int lightID,
										  const int paramID,
										  const Vec position)
{
	addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px(position), module, paramID));
	addChild(createLight<LEDBezelLight<WhiteLight>>(mm2px({position.x - 3.0f, position.y - 3.0f}), module, lightID));
	addLabel(labelText, {position.x + 17, position.y - 6.7f}, {LabelButtonID::Types::Toggle, paramID, -1});
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

	bool isTypeKnob = this->id.objType == LabelButtonID::Types::Knob;

	if ((isOnHub) || (!isOnHub && !isTypeKnob)) {
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
			nvgFillColor(args.vg, rack::color::alpha(rack::color::BLACK, 0.1f));
		}
		nvgStroke(args.vg);
		nvgFill(args.vg);
	}

	if (APP->event->hoveredWidget == this)
		nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.4f));

	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 10.0f);
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
