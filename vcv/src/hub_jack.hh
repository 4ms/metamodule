#pragma once
#include "HubMapButton.hh"
#include "MapMarks.hh"
#include "paletteHub.hh"

class HubJackMapButton : public HubMapButton {
public:
	HubJackMapButton(CommModuleWidget &parent)
		: HubMapButton{static_cast<CommModuleWidget &>(parent)}
	{}

	void onDeselect(const event::Deselect &e) override
	{
		// Check if a MappableJack was touched
		auto touchedJack = centralData->getAndClearTouchedJack();

		bool registerSucess = false;

		if (centralData->isMappingInProgress()) {
			if (touchedJack.objType == id.objType) {
				if (touchedJack.moduleID > -1) {
					if (id.moduleID != touchedJack.moduleID) {
						// Todo: Check if already mapped to a different hub. Use centralData to query if the moduleId
						// has been registered as a hub
						centralData->registerMapDest({id.objType, touchedJack.objID, touchedJack.moduleID});
						registerSucess = true;
					}
				}
			}
		}

		if (!registerSucess) {
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
