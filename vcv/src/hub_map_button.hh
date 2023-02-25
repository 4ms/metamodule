#pragma once
#include "comm_widget.hh"
#include <rack.hpp>
using namespace rack;

class HubMapButton : public Button {

public:
	HubMapButton(CommModuleWidget &parent)
		: _parent{parent}
	{}
	void draw(const DrawArgs &args) override;
	void onDragStart(const event::DragStart &e) override;
	void onHover(const event::Hover &e) override;
	void onLeave(const event::Leave &e) override;
	void onEnter(const event::Enter &e) override;

	bool registerMapping(LabelButtonID src);

	LabelButtonID id;
	bool isMapped = false;
	bool isCurrentMapSrc = false;
	LabelButtonID mappedToId{LabelButtonID::Types::None, -1, -1};

private:
	// void _createMapping(LabelButtonID srcId);
	void _updateState();
	bool _hovered{false};
	CommModuleWidget &_parent;
};
