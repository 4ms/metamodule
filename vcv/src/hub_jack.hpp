#pragma once
#include "HubMapButton.hpp"
#include "MapMarks.hpp"
#include "paletteHub.hpp"

class HubJackMapButton : public HubMapButton {
public:
	HubJackMapButton(CommModuleWidget &parent)
		: HubMapButton{static_cast<CommModuleWidget &>(parent)}
	{}

	void onDeselect(const event::Deselect &e) override
	{
		bool registerSuccess = false;
		auto touchedJack = centralData->getAndClearTouchedJack();
		if (touchedJack.objType == id.objType) {
			int moduleId = touchedJack.moduleID;
			int objId = touchedJack.objID;
			registerSuccess = registerMapping(moduleId, objId);
		}

		if (!registerSuccess) {
			centralData->abortMappingProcedure();
		}
	}
};

template<typename BaseJackT>
class HubJack : public BaseJackT {
public:
	HubJack(HubJackMapButton &_hubJackLabel)
		: hubJackLabel{_hubJackLabel}
	{}

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		BaseJackT::draw(args);

		// Draw mapped circle
		if (hubJackLabel.isMapped) {
			NVGcolor color = PaletteHub::color[hubJackLabel.id.objID];
			if (hubJackLabel.id.objType == LabelButtonID::Types::InputJack)
				MapMark::markInputJack(args.vg, this->box, color);
			else
				MapMark::markOutputJack(args.vg, this->box, color);
		}
	}

private:
	HubJackMapButton &hubJackLabel;
};
