#include "CommWidget.h"

void CommModuleWidget::addLabeledKnob(const std::string labelText, const int knobID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromTop(position.y),
	};
	addLabel(labelText, pos);
	addParam(createParamCentered<RoundBlackKnob>(mm2px(pos), module, knobID));
}

void CommModuleWidget::addLabeledInput(const std::string labelText, const int inputID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addLabel(labelText, pos);
	addInput(createInputCentered<PJ301MPort>(mm2px(pos), module, inputID));
}

void CommModuleWidget::addLabeledOutput(const std::string labelText, const int outputID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addLabel(labelText, pos);
	addOutput(createOutputCentered<PJ301MPort>(mm2px(pos), module, outputID));
}

void CommModuleWidget::addLabel(const std::string labelText, const Vec pos)
{
	LabeledButton *button = createWidget<LabeledButton>(mm2px(Vec(pos.x - kKnobSpacingX / 2.0f, pos.y + kTextOffset)));
	button->box.size.x = kGridSpacingX;
	button->text = labelText;
	addChild(button);
}

void CommModuleWidget::addLabeledToggle(const std::string labelText, const int lightID, const int paramID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px(pos), module, paramID));
	addChild(createLight<LEDBezelLight<WhiteLight>>(mm2px({pos.x - 3.0f, pos.y - 3.0f}), module, lightID));
	addLabel(labelText, {pos.x + 17, pos.y - 8.5f});
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

void LabeledButton::draw(const DrawArgs &args)
{
	nvgBeginPath(args.vg);
	nvgRoundedRect(args.vg, 0, 0, box.size.x, box.size.y, 5.0);
	nvgStrokeWidth(args.vg, 1.0);
	if (APP->event->hoveredWidget == this)
		nvgStrokeColor(args.vg, rack::color::RED);
	else
		nvgStrokeColor(args.vg, rack::color::BLACK);
	nvgStroke(args.vg);
	if (toggleState) {
		nvgFillColor(args.vg, rack::color::GREEN);
		nvgFill(args.vg);
	}

	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

void LabeledButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	toggleState = !toggleState;

	if (quantity)
		quantity->setMax();
}