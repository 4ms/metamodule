#pragma once
#include "LabeledButton.hh"
#include "hub_knob_menu.hh"
#include "knob_map.hh"
#include "paletteHub.hh"

class HubKnobMapButton : public LabeledButton {
public:
	// Constructor for widget-only view:
	HubKnobMapButton(CommModuleWidget &parent)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap{nullptr}
	{}

	// Constructor for use as a module:
	HubKnobMapButton(CommModuleWidget &parent, KnobMap &knobmap)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap(&knobmap)
	{}

	void onDeselect(const event::Deselect &e) override;
	void onDragStart(const event::DragStart &e) override;
	void draw(const DrawArgs &args) override;
	KnobMap *_knobmap;
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	HubKnob(HubKnobMapButton &_hubKnobLabel)
		: hubKnobLabel{_hubKnobLabel}
	{}

	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		BaseKnobT::draw(args);

		KnobMap *knobmap = hubKnobLabel._knobmap;

		if (knobmap) {
			const float radius = 6;
			const float spacing = 2;
			auto numMaps = std::min(knobmap->getNumMaps(), 16);
			float x = this->box.size.x - radius;
			float y = this->box.size.y - radius;
			for (int i = 0; i < numMaps; i++) {
				nvgBeginPath(args.vg);
				nvgRect(args.vg, x, y, radius, radius);
				NVGcolor color = knobmap->get_color();
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
				nvgStrokeColor(args.vg, color::mult(color, 0.5));
				nvgStrokeWidth(args.vg, 1.0);
				nvgStroke(args.vg);
				if (i % 4 == 3) {
					x = this->box.size.x - radius;
					y -= radius + spacing;
				} else
					x -= radius + spacing;
			}
		}
	}

	void onButton(const event::Button &e) override
	{
		math::Vec c = this->box.size.div(2);
		float dist = e.pos.minus(c).norm();
		if (dist <= c.x) {
			OpaqueWidget::onButton(e);

			// Touch parameter
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT && (e.mods & RACK_MOD_MASK) == 0) {
				if (this->paramQuantity) {
					APP->scene->rack->touchedParam = this;
				}
				e.consume(this);
			}

			// Right click to open context menu
			if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
				ui::Menu *menu = createMenu();

				MapFieldLabel *paramLabel = new MapFieldLabel;
				paramLabel->paramWidget = this;
				menu->addChild(paramLabel);

				MapField *paramField = new MapField;
				paramField->box.size.x = 100;
				paramField->setParamWidget(this);
				menu->addChild(paramField);

				ParamResetItem *resetItem = new ParamResetItem;
				resetItem->text = "Initialize";
				resetItem->rightText = "Double-click";
				resetItem->paramWidget = this;
				menu->addChild(resetItem);

				KnobMap *thisMap = hubKnobLabel._knobmap;
				if (thisMap) {
					for (auto &mapping : thisMap->maps) {
						auto &ph = mapping->paramHandle;
						bool knobMapped = ph.moduleId != -1;
						if (knobMapped) {
							MapFieldEntry *paramLabel2 = new MapFieldEntry;
							paramLabel2->moduleName = ph.module->model->name;
							paramLabel2->paramName = ph.module->paramQuantities[ph.paramId]->getLabel();
							paramLabel2->moduleId = ph.moduleId;
							paramLabel2->paramId = ph.paramId;
							menu->addChild(paramLabel2);

							MinField *o = new MinField(mapping->range);
							o->box.size.x = 100;
							menu->addChild(o);

							MaxField *l = new MaxField(mapping->range);
							l->box.size.x = 100;
							menu->addChild(l);
						}
					}
				}

				engine::ParamHandle *paramHandle =
					this->paramQuantity
						? APP->engine->getParamHandle(this->paramQuantity->module->id, this->paramQuantity->paramId)
						: NULL;
				if (paramHandle) {
					ParamUnmapItem *unmapItem = new ParamUnmapItem;
					unmapItem->text = "Unmap";
					unmapItem->rightText = paramHandle->text;
					unmapItem->paramWidget = this;
					menu->addChild(unmapItem);
				}
				e.consume(this);
			}
		}
	}

	// This is needed in case someone maps a Hub Knobs to their MIDI CC module or something else
	struct ParamUnmapItem : ui::MenuItem {
		ParamWidget *paramWidget;
		void onAction(const event::Action &e) override
		{
			ParamHandle *paramHandle = APP->engine->getParamHandle(paramWidget->paramQuantity->module->id,
																   paramWidget->paramQuantity->paramId);
			if (paramHandle) {
				APP->engine->updateParamHandle(paramHandle, -1, 0);
			}
		}
	};

	struct ParamResetItem : ui::MenuItem {
		ParamWidget *paramWidget;
		void onAction(const event::Action &e) override
		{
			paramWidget->resetAction();
		}
	};

private:
	HubKnobMapButton &hubKnobLabel;
};
