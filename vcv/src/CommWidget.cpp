#include "CommWidget.h"

void CommModuleWidget::addLabeledKnob(const std::string labelText, const int knobID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromTop(position.y),
	};
	addLabel(labelText, pos, {LabelButtonID::Types::Knob, knobID, -1});
	addParam(createParamCentered<RoundBlackKnob>(mm2px(pos), module, knobID));
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

void CommModuleWidget::addLabeledOutput(const std::string labelText, const int outputID, const Vec position)
{
	const Vec pos = {
		gridToXCentered(position.x),
		gridToYFromBottom(position.y),
	};
	addLabel(labelText, pos, {LabelButtonID::Types::OutputJack, outputID, -1});
	addOutput(createOutputCentered<PJ301MPort>(mm2px(pos), module, outputID));
}

void CommModuleWidget::addLabel(const std::string labelText, const Vec pos, const LabelButtonID id)
{
	LabeledButton *button = new LabeledButton{*this};
	button->box.pos = mm2px(Vec(pos.x - kKnobSpacingX / 2.0f, pos.y + kTextOffset));
	button->box.size.x = kGridSpacingX;
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
	addLabel(labelText, {pos.x + 17, pos.y - 8.5f}, {LabelButtonID::Types::Toggle, paramID, -1});
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

void CommModuleWidget::notifyLabelButtonClicked(LabeledButton &button)
{
	button.id.moduleID = module->id;
	auto mapstate = centralData->getMappingState();

	if (mapstate == MappingState::MappingPending) {

		if (button.state == MappingState::IsMapped) {
			button.state = MappingState::MappingPending;
			centralData->unregisterMapDest(button.id);
		} else if (button.state == MappingState::MappingPending) {
			button.state = MappingState::IsMapped;
			centralData->registerMapDest(button.id);
		}
	}
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

	if (state == MappingState::IsMapped) {
		nvgFillColor(args.vg, rack::color::BLUE);
		nvgFill(args.vg);
	} else {
		auto mapstate = centralData->getMappingState();
		state = mapstate;

		if (state == MappingState::Normal) {
			nvgFillColor(args.vg, rack::color::WHITE);
			nvgFill(args.vg);
		}
		if (state == MappingState::MappingPending) {
			nvgFillColor(args.vg, rack::color::YELLOW);
			nvgFill(args.vg);
		}
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

	_parent.notifyLabelButtonClicked(*this);

	if (quantity)
		quantity->setMax();
}
