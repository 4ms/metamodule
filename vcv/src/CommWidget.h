#pragma once
#include "CommModule.h"
#include <rack.hpp>
using namespace rack;

class LabeledButton;

class CommModuleWidget : public app::ModuleWidget {
protected:
	const float kKnobSpacingY = 17;
	const float kKnobSpacingX = 20.32f;
	const float kTextOffset = 5;
	const float kTopMargin = 13;
	const float kBottomMargin = 15;
	const float kGridSpacingX = 60;
	const float kModuleHeight = 128.5f;

public:
	virtual void notifyLabelButtonClicked(LabeledButton &button);

protected:
	void
	addLabeledKnob(const std::string labelText, const int knobID, const Vec position, const float defaultValue = 0.f);
	void addLabeledInput(const std::string labelText, const int inputID, const Vec position);
	void addLabeledOutput(const std::string labelText, const int outputID, const Vec position);

	void
	addLabeledKnobPx(const std::string labelText, const int knobID, const Vec position, const float defaultValue = 0.f);
	void addLabeledInputPx(const std::string labelText, const int inputID, const Vec position);
	void addLabeledOutputPx(const std::string labelText, const int outputID, const Vec position);

	void addLabeledToggle(const std::string labelText, const int lightID, const int paramID, const Vec position);
	void addModuleTitle(const std::string moduleTitle);

private:
	constexpr float gridToYFromTop(const float y);
	constexpr float gridToYFromBottom(const float y);
	constexpr float gridToXCentered(const float x);
	Vec grid2mm(Vec position);
	Vec grid2px(Vec position);

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
	virtual void onDragStart(const event::DragStart &e) override;
	void updateState();
	void createMapping(LabelButtonID srcId);

	LabelButtonID id;
	bool isMapped = false;
	bool isOnHub = false;
	bool isPossibleMapDest = false;
	bool isCurrentMapSrc = false;
	LabelButtonID mappedToId{LabelButtonID::Types::None, -1, -1};

private:
	CommModuleWidget &_parent;
};

class MetaModuleTextBox : public LedDisplayTextField {
	virtual void draw(const DrawArgs &args) override;
};
