#pragma once
#include "MapMarks.hh"
#include "hub_knob_menu.hh"
#include "paletteHub.hh"
#include "plugin.hpp"
#include <rack.hpp>

enum class MappableJackType { Input, Output };

template<MappableJackType InputOrOutput, typename BaseJackT>
class MappableJack : public BaseJackT {
public:
	MappableJack() = default;

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == getId().objType)) {
			nvgBeginPath(args.vg);
			const float margin = 0;
			nvgCircle(args.vg, this->box.size.x / 2, this->box.size.y / 2, this->box.size.y + margin);
			NVGcolor color = rack::color::alpha(rack::color::YELLOW, 0.25f);
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
		}

		BaseJackT::draw(args);

		auto id = getId();
		if ((id.moduleID >= 0) && centralData->isLabelButtonDstMapped(id)) {
			// const float radius = 4;
			int srcPortId = centralData->getMappedSrcFromDst(id).objID;
			NVGcolor color = PaletteHub::color[srcPortId];
			if constexpr (InputOrOutput == MappableJackType::Output)
				MapMark::markOutputJack(args.vg, this->box, color);
			else
				MapMark::markInputJack(args.vg, this->box, color);
		}
	}

	void onButton(const event::Button &e) override
	{
		OpaqueWidget::onButton(e);

		// Register this jack with CentralData as the "TouchedJack",
		// Hub jacks can use this to determine what jack you clicked on after clicking on the Hub Jack Mapping Button,
		// when creating a new mapping
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			centralData->registerTouchedJack(getId());
			e.consume(this);
		}

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			ui::Menu *menu = createMenu();

			if ((getId().moduleID >= 0) && centralData->isLabelButtonDstMapped(getId())) {
				JackUnmapItem *unmapItem = new JackUnmapItem{getId()};
				unmapItem->text = "Unmap";
				// TODO: can we write which MetaModule jack it's mapped to?
				// unmapItem->rightText = paramHandle->text;
				menu->addChild(unmapItem);
			} else {
				ui::MenuItem *label = new ui::MenuItem;
				label->text = "Not mapped";
				label->rightText = "Click a MetaModule jack to begin mapping";
				menu->addChild(label);
			}
			e.consume(this);
		}
	}

private:
	LabelButtonID getId()
	{
		int moduleId = this->module ? this->module->id : -1;
		if constexpr (InputOrOutput == MappableJackType::Input)
			return {LabelButtonID::Types::InputJack, this->portId, moduleId};
		else
			return {LabelButtonID::Types::OutputJack, this->portId, moduleId};
	}

	struct JackUnmapItem : ui::MenuItem {
		const LabelButtonID _id;
		JackUnmapItem(LabelButtonID id)
			: _id{id}
		{}
		void onAction(const event::Action &e) override
		{
			centralData->unregisterMapByDest(_id);
		}
	};
};

template<typename BaseJackT>
using MappableInputJack = MappableJack<MappableJackType::Input, BaseJackT>;

template<typename BaseJackT>
using MappableOutputJack = MappableJack<MappableJackType::Output, BaseJackT>;
