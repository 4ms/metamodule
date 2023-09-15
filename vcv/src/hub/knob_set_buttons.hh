#pragma once
#include <rack.hpp>

struct KnobSetButton : rack::Widget {
	int set_idx;

	void drawLayer(const DrawArgs &args, int layer) override;
	void onDragEnter(const rack::event::DragEnter &e) override;
	void onButton(const rack::event::Button &e) override;

	void onDragHover(const rack::event::DragHover &e) override {
		if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
			e.consume(this);
		}
		Widget::onDragHover(e);
	}
};

struct KnobSetButtonGroup : rack::OpaqueWidget {
	std::function<void(unsigned)> onChange;
	unsigned active_idx = 0;

	KnobSetButtonGroup(std::function<void(unsigned)> &&onChangeCallback, rack::Vec pos)
		: onChange{std::move(onChangeCallback)} {
		box.pos = pos;
		box.size = rack::mm2px(rack::Vec(80, 20));
		const int num_sets = 8;

		const float spacing = rack::mm2px(3);
		const float size = rack::mm2px(3);

		rack::math::Rect bbox;
		bbox.size = rack::math::Vec(size + spacing, size + spacing);
		bbox.pos = rack::math::Vec(0, 0);

		for (unsigned i = 0; i < num_sets; i++) {
			auto button = new KnobSetButton();
			button->box = bbox;
			button->set_idx = i;
			addChild(button);
			if (i % 2 == 1) {
				bbox.pos.x = 0;
				bbox.pos.y += spacing + size;
			} else
				bbox.pos.x += spacing + size;
		}
	}
};

inline void KnobSetButton::drawLayer(const DrawArgs &args, int layer) {
	if (layer != 1)
		return;

	rack::Vec c = box.size.div(2);
	float r = rack::mm2px(2); //(box.size.x + box.size.y) / 2;

	auto *group = getAncestorOfType<KnobSetButtonGroup>();
	int active_idx = group ? group->active_idx : 0;

	auto color = (active_idx == set_idx) ? rack::SCHEME_YELLOW : rack::color::alpha(rack::color::WHITE, 0.33);
	nvgBeginPath(args.vg);
	nvgCircle(args.vg, c.x, c.y, r);
	nvgFillColor(args.vg, color);
	nvgFill(args.vg);
}

inline void KnobSetButton::onDragEnter(const rack::event::DragEnter &e) {
	if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
		auto origin = dynamic_cast<KnobSetButtonGroup *>(e.origin);
		if (origin) {
			KnobSetButtonGroup *group = getAncestorOfType<KnobSetButtonGroup>();
			if (group) {
				group->active_idx = set_idx;
				group->onChange(set_idx);
			}
		}
	}
	Widget::onDragEnter(e);
}

inline void KnobSetButton::onButton(const rack::event::Button &e) {
	if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
		KnobSetButtonGroup *group = getAncestorOfType<KnobSetButtonGroup>();
		if (group) {
			group->active_idx = set_idx;
			group->onChange(set_idx);
		}
	}
	Widget::onButton(e);
}
