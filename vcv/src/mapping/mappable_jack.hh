#pragma once
#include "central_data.hh"
#include "map_marks.hh"
#include "map_palette.hh"
#include <rack.hpp>

enum class MappableJackType { Input, Output };
enum class CoordinateType { Center, TopLeft };

template<MappableJackType InputOrOutput, typename BaseJackT, CoordinateType Coords = CoordinateType::Center>
class MappableJack : public BaseJackT {
	static_assert(std::is_base_of<rack::app::SvgPort, BaseJackT>(), "Jack class must derive from SvgPort");
	static constexpr float margin = 10;

public:
	MappableJack() {
		if constexpr (Coords == CoordinateType::Center) {
			this->sw->box.pos = this->sw->box.pos.plus(rack::math::Vec{margin / 2, margin / 2});
			this->fb->box.pos = this->fb->box.pos.plus(rack::math::Vec{margin / 2, margin / 2});
			this->shadow->box.pos = this->shadow->box.pos.plus(rack::math::Vec{margin / 2, margin / 2});
			this->box = this->box.grow(rack::math::Vec{margin, margin});
		} else {
			this->box = this->box.grow(rack::math::Vec{margin, margin});
		}
	}

	void draw(const typename BaseJackT::DrawArgs &args) override {
		BaseJackT::draw(args);
		auto id = getId();

		bool isMappingNow = centralData->isMappingInProgress();
		if (isMappingNow || centralData->isMappedPartnerHovered(id)) {
			auto src = isMappingNow ? centralData->getMappingSource() : centralData->getMappedSrcFromDst(id);
			if (src.objType == getId().objType && src.objID >= 0) {
				nvgBeginPath(args.vg);
				nvgCircle(args.vg, this->box.size.x / 2, this->box.size.y / 2, this->box.size.y / 2);
				float alpha = hovered ? 0.75 : 0.4;
				NVGcolor color = rack::color::alpha(PaletteHub::color(src.objID), alpha);
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
			}
		}

		if ((id.moduleID >= 0) && centralData->isLabelButtonDstMapped(id)) {
			int srcPortId = centralData->getMappedSrcFromDst(id).objID;
			NVGcolor color = PaletteHub::color(srcPortId);
			rack::math::Rect box = this->box.grow(rack::math::Vec{-margin / 2, -margin / 2});
			if constexpr (InputOrOutput == MappableJackType::Output)
				MapMark::markOutputJack(args.vg, box, color);
			else
				MapMark::markInputJack(args.vg, box, color);
		}
	}

	void onDragStart(const rack::event::DragStart &e) override {
		if (!(centralData->isMappingInProgress() && (centralData->getMappingSource().objType == getId().objType))) {
			rack::PortWidget::onDragStart(e);
		} else {
			centralData->registerTouchedJack(getId());
			e.consume(this);
		}
	}

	void onButton(const rack::event::Button &e) override {
		rack::OpaqueWidget::onButton(e);

		// Right click to open context menu
		if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
			rack::ui::Menu *menu = rack::createMenu();

			if ((getId().moduleID >= 0) && centralData->isLabelButtonDstMapped(getId())) {
				JackUnmapItem *unmapItem = new JackUnmapItem{getId()};
				unmapItem->text = "Unmap";
				// unmapItem->rightText = .... TODO: name of metamodule jack
				menu->addChild(unmapItem);
			} else {
				rack::ui::MenuItem *label = new rack::ui::MenuItem;
				label->text = "Not mapped";
				label->rightText = "Click a MetaModule jack to begin mapping";
				menu->addChild(label);
			}
			e.consume(this);
		}
	}

	void onHover(const rack::event::Hover &e) override {
		e.consume(this);
	}

	void onEnter(const rack::event::Enter &e) override {
		hovered = true;
		if (!centralData->isMappingInProgress())
			centralData->notifyEnterHover(getId());
		BaseJackT::onEnter(e);
	}

	void onLeave(const rack::event::Leave &e) override {
		hovered = false;
		if (!centralData->isMappingInProgress())
			centralData->notifyLeaveHover(getId());
		BaseJackT::onLeave(e);
	}

private:
	bool hovered = false;

	MappableObj getId() {
		int64_t moduleId = this->module ? this->module->id : -1;
		if constexpr (InputOrOutput == MappableJackType::Input)
			return {MappableObj::Type::InputJack, this->portId, moduleId};
		else
			return {MappableObj::Type::OutputJack, this->portId, moduleId};
	}

	struct JackUnmapItem : rack::ui::MenuItem {
		const MappableObj _id;
		JackUnmapItem(MappableObj id)
			: _id{id} {
		}
		void onAction(const rack::event::Action &e) override {
			centralData->unregisterMapByDest(_id);
		}
	};
};

template<typename BaseJackT>
using MappableInputCentered = MappableJack<MappableJackType::Input, BaseJackT, CoordinateType::Center>;

template<typename BaseJackT>
using MappableOutputCentered = MappableJack<MappableJackType::Output, BaseJackT, CoordinateType::Center>;

template<typename BaseJackT>
using MappableInput = MappableJack<MappableJackType::Input, BaseJackT, CoordinateType::TopLeft>;

template<typename BaseJackT>
using MappableOutput = MappableJack<MappableJackType::Output, BaseJackT, CoordinateType::TopLeft>;
