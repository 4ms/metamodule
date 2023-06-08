#pragma once

#include "mapping/Mapping.h"
#include <rack.hpp>

class HubMapButton : public rack::Button {

public:
	HubMapButton(rack::app::ModuleWidget &parent)
		: _parent{parent} {
	}
	void draw(const DrawArgs &args) override;
	void onDragStart(const rack::event::DragStart &e) override;
	void onHover(const rack::event::Hover &e) override;
	void onLeave(const rack::event::Leave &e) override;
	void onEnter(const rack::event::Enter &e) override;

	MappableObj hubParamObj;
	bool isMapped = false;
	bool isCurrentMapSrc = false;
	MappableObj mappedToId{MappableObj::Type::None, -1, -1};

	// void _createMapping(LabelButtonID srcId);
protected:
	void _updateState();
	bool _hovered{false};

private:
	rack::app::ModuleWidget &_parent;
};
