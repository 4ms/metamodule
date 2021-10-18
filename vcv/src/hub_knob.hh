#pragma once
#include "CommWidget.h"
#include "hub_knob_menu.hh"
#include "knob_map.hh"
#include "paletteHub.hh"

// HubKnobLabel needs to know:
// parent module->id (onDeselect aborts mapping if we deselected by clicking on the hub)
// All knobMaps of parent module [Todo: don't need this, can check with centralData or with VCV engin)
// knobMap for this knob (onDeselect: knobmap.create()
//
// HubKnob needs to know:
// parent module ptr (draw() checks if it's null before reading knobMaps)
// parent module knobMap for this knob
// onButton (right-click menu): this knobMap so it can draw all mappings
class HubKnobLabel : public LabeledButton {
public:
	// Constructor for widget-only view:
	HubKnobLabel(CommModuleWidget &parent)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap{nullptr}
	{}

	// Constructor for use as a module:
	HubKnobLabel(CommModuleWidget &parent, KnobMap &knobmap)
		: LabeledButton{static_cast<CommModuleWidget &>(parent)}
		, _knobmap(&knobmap)
	{}

	void onDeselect(const event::Deselect &e) override;
	void draw(const DrawArgs &args) override;
	KnobMap *_knobmap;

private:
};

template<typename BaseKnobT>
class HubKnob : public BaseKnobT {
public:
	HubKnob(HubKnobLabel &_hubKnobLabel)
		: hubKnobLabel{_hubKnobLabel}
	{}

	void draw(const typename BaseKnobT::DrawArgs &args) override
	{
		RoundBlackKnob::draw(args);

		KnobMap *knobmap = hubKnobLabel._knobmap;

		if (knobmap) {
			bool isKnobMapped = knobmap->getNumMaps() > 0;
			if (isKnobMapped) {
				nvgBeginPath(args.vg);
				const float radius = 6;
				// nvgCircle(args.vg, box.size.x / 2, box.size.y / 2, radius);
				nvgRect(args.vg, this->box.size.x - radius, this->box.size.y - radius, radius, radius);
				NVGcolor color = knobmap->get_color();
				nvgFillColor(args.vg, color);
				nvgFill(args.vg);
				nvgStrokeColor(args.vg, color::mult(color, 0.5));
				nvgStrokeWidth(args.vg, 1.0);
				nvgStroke(args.vg);
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
						auto &ph = mapping.paramHandle;
						bool knobMapped = ph.moduleId != -1;
						if (knobMapped) {
							MapFieldEntry *paramLabel2 = new MapFieldEntry;
							paramLabel2->moduleName = ph.module->model->name;
							paramLabel2->paramName = ph.module->paramQuantities[ph.paramId]->getLabel();
							paramLabel2->moduleId = ph.moduleId;
							paramLabel2->paramId = ph.paramId;
							menu->addChild(paramLabel2);

							MinField *o = new MinField(mapping.range);
							o->box.size.x = 100;
							menu->addChild(o);

							MaxField *l = new MaxField(mapping.range);
							l->box.size.x = 100;
							menu->addChild(l);
						}
					}
				}

				// ParamFineItem *fineItem = new ParamFineItem;
				// fineItem->text = "Fine adjust";
				// fineItem->rightText = RACK_MOD_CTRL_NAME "+drag";
				// fineItem->disabled = true;
				// menu->addChild(fineItem);

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
	HubKnobLabel &hubKnobLabel;
};
