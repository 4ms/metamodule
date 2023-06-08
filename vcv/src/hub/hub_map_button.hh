#pragma once

#include "hub/hub_module.hh"
#include "mapping/Mapping.h"
#include <rack.hpp>

class HubMapButton : public rack::Button {

public:
	HubMapButton(MetaModuleHubBase &hub, rack::app::ModuleWidget &parent)
		: parent{parent}
		, hub{hub} {
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
	void updateState();
	bool hovered{false};
	rack::app::ModuleWidget &parent;
	MetaModuleHubBase &hub;
};
