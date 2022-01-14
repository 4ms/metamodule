#pragma once
#include "MapMarks.hpp"
#include "hub_knob_menu.hpp"
#include "paletteHub.hpp"
#include "plugin.hpp"
// #include <concepts>
#include <rack.hpp>

enum class MappableJackType { Input, Output };

template<MappableJackType InputOrOutput, typename BaseJackT>
// requires(std::is_base_of<app::SvgPort, BaseJackT>() == true)
class MappableJack : public BaseJackT {
	static_assert(std::is_base_of<app::SvgPort, BaseJackT>(), "Jack class must derive from SvgPort");
	static constexpr float margin = 10;

public:
	MappableJack()
	{
		this->sw->box.pos = this->sw->box.pos.plus(Vec{margin / 2, margin / 2});
		this->fb->box.pos = this->fb->box.pos.plus(Vec{margin / 2, margin / 2});
		this->shadow->box.pos = this->shadow->box.pos.plus(Vec{margin / 2, margin / 2});
		this->box = this->box.grow(Vec{margin, margin});
	}

	void draw(const typename BaseJackT::DrawArgs &args) override
	{
		BaseJackT::draw(args);
		if (centralData->isMappingInProgress()) {
			auto src = centralData->getMappingSource();
			if (src.objType == getId().objType) {
				auto srcId = src.objID;
				nvgBeginPath(args.vg);
				nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
				float alpha = this->hovered ? 0.75 : 0.4;
				NVGcolor color = rack::color::alpha(PaletteHub::color[srcId], alpha);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
			} else {
				nvgBeginPath(args.vg);
				nvgRect(args.vg, 0, 0, this->box.size.x, this->box.size.y);
				NVGcolor color = rack::color::alpha(color::WHITE, 0.5f);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
				// dim out BaseJackT::draw()?
			}
		}

		auto id = getId();
		if ((id.moduleID >= 0) && centralData->isLabelButtonDstMapped(id)) {
			int srcPortId = centralData->getMappedSrcFromDst(id).objID;
			NVGcolor color = PaletteHub::color[srcPortId];
			Rect box = this->box.grow(Vec{-margin / 2, -margin / 2});
			if constexpr (InputOrOutput == MappableJackType::Output)
				MapMark::markOutputJack(args.vg, box, color);
			else
				MapMark::markInputJack(args.vg, box, color);
		}
	}

	void onDragStart(const event::DragStart &e) override
	{
		if (!(centralData->isMappingInProgress() && (centralData->getMappingSource().objType == getId().objType))) {
			PortWidget::onDragStart(e);
		} else {
			centralData->registerTouchedJack(getId());
			e.consume(this);
		}
	}

	void onButton(const event::Button &e) override
	{
		OpaqueWidget::onButton(e);

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			ui::Menu *menu = createMenu();

			if ((getId().moduleID >= 0) && centralData->isLabelButtonDstMapped(getId())) {
				JackUnmapItem *unmapItem = new JackUnmapItem{getId()};
				unmapItem->text = "Unmap";
				// unmapItem->rightText = .... TODO: name of metamodule jack
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

	void onHover(const event::Hover &e) override
	{
		e.consume(this);
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
