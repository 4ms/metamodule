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

	bool registerMapping(MappableObj src);

	MappableObj id;
	bool isMapped = false;
	bool isCurrentMapSrc = false;
	MappableObj mappedToId{MappableObj::Type::None, -1, -1};

	// void _createMapping(LabelButtonID srcId);
protected:
	void _updateState();
	bool _hovered{false};

private:
	CommModuleWidget &_parent;
};
