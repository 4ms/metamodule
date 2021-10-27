#pragma once
#include "MapMarks.hh"
#include "hub_knob_menu.hh"
#include "paletteHub.hh"
#include "plugin.hpp"
#include <rack.hpp>

enum class MappableJackType { Input, Output };

// class MapButton : public Button {
// 	LabelButtonID::Types objType;

// public:
// 	MapButton(LabelButtonID::Types parent_type)
// 		: objType{parent_type}
// 	{}

// 	void draw(const DrawArgs &args) override
// 	{
// 		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == objType)) {
// 			nvgBeginPath(args.vg);
// 			nvgCircle(args.vg, this->box.size.x / 2, this->box.size.y / 2, this->box.size.y);
// 			NVGcolor color = rack::color::alpha(rack::color::YELLOW, 0.25f);
// 			nvgFillColor(args.vg, color);
// 			nvgFill(args.vg);
// 		} else {
// 			nvgBeginPath(args.vg);
// 			nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
// 			NVGcolor color = rack::color::alpha(rack::color::RED, 0.25f);
// 			nvgFillColor(args.vg, color);
// 			nvgFill(args.vg);
// 		}
// 	}
// 	void onButton(const event::Button &e) override
// 	{
// 		printf("onButton\n");
// 		// this->parent->onButton(e);
// 		// e.setTarget(this->parent);
// 	}

// 	void onDragStart(const event::DragStart &e) override
// 	{
// 		printf("onDragStart\n");
// 		// this->parent->onDragStart(e);
// 		// e.setTarget(this->parent);
// 	}
// };

template<MappableJackType InputOrOutput, typename BaseJackT>
class MappableJack : public BaseJackT {
	// BaseJackT *jack;
	// MapButton *border;

public:
	MappableJack()
	{
		const float margin = 10;
		this->sw->box.pos = this->sw->box.pos.plus(Vec{margin / 2, margin / 2});
		this->fb->box.pos = this->fb->box.pos.plus(Vec{margin / 2, margin / 2});
		this->shadow->box.pos = this->shadow->box.pos.plus(Vec{margin / 2, margin / 2});
		this->box = this->box.grow(Vec{margin, margin});
		// this->box.pos = this->box.pos.minus(Vec{margin,  margin});
		// this->box.size = Vec{this->box.size.x + margin * 2, this->box.size.y + margin * 2};
		printf("MappableJack(): fb->box.pos = %f,%f size=%f,%f\n",
			   this->fb->box.pos.x,
			   this->fb->box.pos.y,
			   this->fb->box.size.x,
			   this->fb->box.size.y);
	}

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == getId().objType)) {
			nvgBeginPath(args.vg);
			nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
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

	void onDragStart(const event::DragStart &e) override
	{
		printf("MappableJack got onDragStart\n");
		printf(
			"    box.pos = %f,%f size=%f,%f\n", this->box.pos.x, this->box.pos.y, this->box.size.x, this->box.size.y);
	}

	void onButton(const event::Button &e) override
	{
		printf("MappableJack got onButton\n");

		// Register this jack with CentralData as the "TouchedJack",
		// Hub jacks can use this to determine what jack you clicked on after clicking on the Hub Jack Mapping Button,
		// when creating a new mapping
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
			printf("MappableJack got left click\n");
			if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == getId().objType)) {
				printf("MappableJack registered touchedJack\n");
				centralData->registerTouchedJack(getId());
				OpaqueWidget::onButton(e);
				e.consume(this);
			}
		}

		// Right click to open context menu
		else if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0)
		{
			OpaqueWidget::onButton(e);
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
		} else
			OpaqueWidget::onButton(e);
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
