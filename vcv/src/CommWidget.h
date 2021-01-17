#pragma once
#include "CommModule.h"
#include <rack.hpp>
using namespace rack;

class LabeledButton;

class CommModuleWidget : public app::ModuleWidget {
protected:
	const float kKnobSpacingY = 20;
	const float kKnobSpacingX = 20.32f;
	const float kTextOffset = 5;
	const float kTopMargin = 10;
	const float kBottomMargin = 15;
	const float kGridSpacingX = 60;
	const float kModuleHeight = 128.5f;

public:
	virtual void notifyLabelButtonClicked(LabeledButton &button);

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
	virtual LabeledButton *createLabel();
};

class LabeledButton : public Button {
	// protected:
	// static inline const NVGcolor ORANGE = nvgRGB(0xff, 0x80, 0x00);
	// static inline const NVGcolor BROWN = nvgRGB(0x80, 0x40, 0x00);

	// static inline const NVGcolor labelPalette[8] = {
	// 	rack::color::BLACK,
	// 	BROWN,
	// 	rack::color::RED,
	// 	ORANGE,
	// 	rack::color::YELLOW,
	// 	rack::color::GREEN,
	// 	rack::color::BLUE,
	// 	rack::color::MAGENTA,
	// };

public:
	LabeledButton(CommModuleWidget &parent)
		: _parent{parent}
	{}
	virtual void draw(const DrawArgs &args) override;
	virtual void updateState();
	virtual void onDragStart(const event::DragStart &e) override;
	void createMapping(LabelButtonID srcId);

	LabelButtonID id;
	bool isMapped = false;
	bool isOnHub = false;
	bool isPossibleMapDest = false;
	bool isCurrentMapSrc = false;
	LabelButtonID mappedToId{LabelButtonID::Types::None, 0, 0};
	MappingState state = MappingState::Normal;

private:
	CommModuleWidget &_parent;
};

class HubLabeledButton : public LabeledButton {
public:
	HubLabeledButton(CommModuleWidget &parent)
		: LabeledButton{parent}
	{}
	virtual void updateState() override;
};

