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
		printf("Deselect hub jack %lld %lld %d\n", id.moduleID, id.objID, id.objType);
		bool registerSuccess = false;
		auto touchedJack = centralData->getAndClearTouchedJack();
		printf("Touched %lld %lld %d\n", touchedJack.moduleID, touchedJack.objID, touchedJack.objType);
		if (touchedJack.objType == id.objType) {
			registerSuccess = registerMapping(touchedJack.moduleID, touchedJack.objID);
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

	void onHover(const event::Hover &e) override
	{
		// If the jack is mapped, then we want to pass the hover down to the HubJackMapButton object below
		// so that the HubMapJackButton can highlight even if we're hovering the jack itself.
		// So, don't consume the hover and just do nothing.
		// On the other hand, if the jack is not mapped, then consume the hover so that hovering the jack
		// doesn't make the background highlight appear
		if (centralData->isLabelButtonSrcMapped(hubJackLabel.id))
			return;

		e.consume(this);
	}

private:
	HubJackMapButton &hubJackLabel;
};
