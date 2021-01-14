#pragma once
#include "CommModule.h"
#include <rack.hpp>
using namespace rack;

class CommModuleWidget : public app::ModuleWidget {
	const float kKnobSpacingY = 20;
	const float kKnobSpacingX = 20.32f;
	const float kTextOffset = 5;
	const float kTopMargin = 10;
	const float kBottomMargin = 15;
	const float kGridSpacingX = 60;
	const float kModuleHeight = 128.5f;

protected:
	void addLabeledKnob(const std::string labelText, const int knobID, const Vec position);
	void addLabeledInput(const std::string labelText, const int inputID, const Vec position);
	void addLabeledOutput(const std::string labelText, const int outputID, const Vec position);
	void addLabeledToggle(const std::string labelText, const int lightID, const int paramID, const Vec position);

private:
	constexpr float gridToYFromTop(const float y);
	constexpr float gridToYFromBottom(const float y);
	constexpr float gridToXCentered(const float x);
	void addLabel(const std::string labelText, const Vec pos, const LabelButtonID id);
};

class LabeledButton : public Button {
public:
	void draw(const DrawArgs &args) override;
	void onDragStart(const event::DragStart &e) override;

	LabelButtonID id;
	LabelState state = LabelState::Normal;

private:
	int toggleState = 0;
};
