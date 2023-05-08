#pragma once
#include "hub_map_button.hh"
#include "../mapping/map_marks.hh"
#include "../mapping/map_palette.hh"

class HubJackMapButton : public HubMapButton {
public:
	HubJackMapButton(rack::app::ModuleWidget &parent)
		: HubMapButton{static_cast<rack::app::ModuleWidget &>(parent)}
	{}

	void onDeselect(const rack::event::Deselect &e) override
	{
		// printf("Deselect hub jack %lld %lld %d\n", id.moduleID, id.objID, id.objType);
		bool registerSuccess = false;
		auto touchedJack = centralData->getAndClearTouchedJack();
		// printf("Touched %lld %lld %d\n", touchedJack.moduleID, touchedJack.objID, touchedJack.objType);
		if (touchedJack.objType == mapObj.objType) {
			registerSuccess = registerMapping(touchedJack);
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
			NVGcolor color = PaletteHub::color(hubJackLabel.mapObj.objID);
			if (hubJackLabel.mapObj.objType == MappableObj::Type::InputJack)
				MapMark::markInputJack(args.vg, this->box, color);
			else
				MapMark::markOutputJack(args.vg, this->box, color);
		}
	}

	void onHover(const rack::event::Hover &e) override
	{
		// If the jack is mapped, then we want to pass the hover down to the HubJackMapButton object below
		// so that the HubMapJackButton can highlight even if we're hovering the jack itself.
		// So, don't consume the hover and just do nothing.
		// On the other hand, if the jack is not mapped, then consume the hover so that hovering the jack
		// doesn't make the background highlight appear
		if (centralData->isLabelButtonSrcMapped(hubJackLabel.mapObj)) {
			rack::PortWidget::onHover(e);
			return;
		}

		e.consume(this);
	}

private:
	HubJackMapButton &hubJackLabel;
};
