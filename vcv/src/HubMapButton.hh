#pragma once
#include "CommWidget.h"
#include <rack.hpp>
using namespace rack;

class HubMapButton : public Button {

public:
	HubMapButton(CommModuleWidget &parent)
		: _parent{parent}
	{}
	void draw(const DrawArgs &args) override;
	void onDragStart(const event::DragStart &e) override;

	bool registerMapping(int moduleId, int objId);

	LabelButtonID id;
	bool isMapped = false;
	bool isOnHub = false;
	bool isPossibleMapDest = false;
	bool isCurrentMapSrc = false;
	LabelButtonID mappedToId{LabelButtonID::Types::None, -1, -1};

private:
	void _createMapping(LabelButtonID srcId);
	void _updateState();
	CommModuleWidget &_parent;
};
