#include "hub_knob.hh"
// #include "CommData.h"
#include "CommModule.h"
#include "hub_knob_menu.hh"
#include "paletteHub.hh"

void HubKnobLabel::onDeselect(const event::Deselect &e)
{
	if (!_knobmap)
		return;

	// Check if a ParamWidget was touched
	ParamWidget *touchedParam = APP->scene->rack->touchedParam;
	if (touchedParam && centralData->isMappingInProgress()) {
		int moduleId = touchedParam->paramQuantity->module->id;
		int paramId = touchedParam->paramQuantity->paramId;
		APP->scene->rack->touchedParam = NULL;

		if (id.moduleID != moduleId) {

			// Check if it already exists
			// Todo: Use centralData or APP->engine to accomodate multiple Hubs
			bool is_already_mapped = false;
			// for (auto &knobmap : _hub.expModule->knobMaps) {
			// 	if (knobmap.mapping_already_exists(moduleId, paramId)) {
			// 		is_already_mapped = true;
			// 		break;
			// 	}
			// }
			if (!is_already_mapped) {
				int knobToMap = centralData->getMappingSource().objID;
				int thisKnob = id.objID;
				assert(knobToMap == thisKnob);
				if (_knobmap->create(moduleId, paramId, PaletteHub::color[thisKnob])) {
					centralData->registerMapDest({LabelButtonID::Types::Knob, paramId, moduleId});
				}
			} else {
				// already mapped
				centralData->abortMappingProcedure();
			}
		} else {
			// clicked on another knob on this hub
			centralData->abortMappingProcedure();
		}
	} else {
		// Didn't click on a knob -- OR -- we're not mapping
		centralData->abortMappingProcedure();
	}
}

void HubKnobLabel::draw(const DrawArgs &args)
{
	updateState();

	nvgBeginPath(args.vg);
	float padding_x = 2;
	float knob_height = 40;
	nvgRoundedRect(args.vg, padding_x, -knob_height, box.size.x - padding_x * 2, knob_height + box.size.y, 5.0);
	nvgStrokeColor(args.vg, rack::color::WHITE);
	nvgStrokeWidth(args.vg, 0.0);
	// Draw solid bg if this knob is the active mapping source
	if (isCurrentMapSrc) {
		auto knobNum = id.objID;
		nvgFillColor(args.vg, PaletteHub::color[knobNum]);
	} else {
		nvgFillColor(args.vg, rack::color::alpha(rack::color::BLACK, 0.0f));
	}
	nvgStroke(args.vg);
	nvgFill(args.vg);

	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

template<typename BaseKnobT>
void HubKnob<BaseKnobT>::draw(const typename BaseKnobT::DrawArgs &args)
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
			// FixMe: color should be read from knobmap
			auto knobNum = hubKnobLabel.id.objID;
			NVGcolor color = PaletteHub::color[knobNum];
			nvgFillColor(args.vg, color);
			nvgFill(args.vg);
			nvgStrokeColor(args.vg, color::mult(color, 0.5));
			nvgStrokeWidth(args.vg, 1.0);
			nvgStroke(args.vg);
		}
	}
}

template<typename BaseKnobT>
void HubKnob<BaseKnobT>::onButton(const event::Button &e)
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
					bool knobMapped = mapping.paramHandle.moduleId != -1;
					if (knobMapped) {

						// Todo: get Module name? get Param name?
						MapFieldEntry *paramLabel2 = new MapFieldEntry;
						paramLabel2->moduleId = mapping.paramHandle.moduleId;
						paramLabel2->paramId = mapping.paramHandle.paramId;
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
