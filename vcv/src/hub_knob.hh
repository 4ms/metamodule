#pragma once
#include "CommWidget.h"
#include "knob_map.hh"

// HubKnobLabel needs to know:
// parent module->id (onDeselect aborts mapping if we deselected by clicking on the hub)
// All knobMaps of parent module [Todo: don't need this, can check with centralData or with VCV engin)
// knobMap for this knob (onDeselect: knobmap.create()
//
// HubKnob needs to know:
// parent module ptr (draw() checks if it's null before reading knobMaps)
// parent module knobMap for this knob
// onButton (right-click menu): this knobMap so it can draw all mappings
class HubKnobLabel : public LabeledButton {
public:
	// Constructor for widget-only view:
	HubKnobLabel(CommModuleWidget &parent)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap{nullptr}
	{}

	// Constructor for use as a module:
	HubKnobLabel(CommModuleWidget &parent, KnobMap &knobmap)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap(&knobmap)
	{}

	void onDeselect(const event::Deselect &e) override;
	void draw(const DrawArgs &args) override;
	KnobMap *_knobmap;

private:
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	void onButton(const event::Button &e) override;
	void draw(const typename BaseKnobT::DrawArgs &args) override;
	HubKnob(HubKnobLabel &_hubKnobLabel)
		: hubKnobLabel{_hubKnobLabel}
	{}
	HubKnobLabel &hubKnobLabel;
};
