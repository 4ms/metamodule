#include "CommWidget.h"
#include "LabeledButton.hh"
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

// Knobs

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

// Input Jacks

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
	addLabeledButton(labelText, posPx, {LabelButtonID::Types::InputJack, inputID, -1});
	addInput(createInputCentered<PJ301MPort>(posPx, module, inputID));
}

// Output Jacks

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
	addLabeledButton(labelText, posPx, {LabelButtonID::Types::OutputJack, outputID, -1});
	addOutput(createOutputCentered<PJ301MPort>(posPx, module, outputID));
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

void CommModuleWidget::addLabel(const std::string labelText, Vec posPx, LabelButtonID id)
{
	auto label = new CenterLabel{};
	label->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y + mm2px(kTextOffset));
	label->box.size.x = mm2px(kKnobSpacingX);
	label->box.size.y = 18;
	label->text = labelText;
	label->fontSize = 8;
	label->alignment = rack::ui::Label::Alignment::CENTER_ALIGNMENT;
	label->color = rack::color::BLACK;
	addChild(label);
}

void CommModuleWidget::addLabeledButton(const std::string labelText, Vec posPx, LabelButtonID id)
{
	LabeledButton *button = new LabeledButton{*this};
	button->isOnHub = false;
	button->box.pos = Vec(posPx.x - mm2px(kKnobSpacingX) / 2, posPx.y + mm2px(kTextOffset));
	button->box.size.x = mm2px(kKnobSpacingX);
	button->box.size.y = 18;
	button->text = labelText;
	button->id = id;
	addChild(button);
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

int CommModuleWidget::getModuleId()
{
	if (module)
		return module->id;
	else
		return -1;
}

void MetaModuleTextBox::draw(const DrawArgs &args)
{
	// Todo: draw it a custom way
	LedDisplayTextField::draw(args);
}
