#include "HubMapButton.hpp"
#include "paletteHub.hpp"
#include <cstdio>

void HubMapButton::_updateState()
{
	id.moduleID = _parent.module ? _parent.module->id : -1;

	isCurrentMapSrc = false;
	if (centralData->isMappingInProgress() && (centralData->getMappingSource() == id)) {
		isCurrentMapSrc = true;
	}
	mappedToId = centralData->getMappedDstFromSrc(id);
	isMapped = mappedToId.objType != LabelButtonID::Types::None;
}

void HubMapButton::draw(const DrawArgs &args)
{
	_updateState();

	// Draw huge background rect to highlight a mapping has begun from this knob
	if (isCurrentMapSrc || _hovered || centralData->isMappedPartnerHovered(id)) {
		const float padding_x = 2;
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, padding_x, 0, box.size.x - padding_x * 2, box.size.y, 5.0);
		const float alpha = isCurrentMapSrc ? 0.75f : 0.4f;
		nvgFillColor(args.vg, rack::color::alpha(PaletteHub::color[id.objID], alpha));
		nvgFill(args.vg);
	}

	// Draw the label text
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_MIDDLE);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y / 2.0f, text.c_str(), NULL);
}

void HubMapButton::onDragStart(const event::DragStart &e)
{
	if (e.button != GLFW_MOUSE_BUTTON_LEFT) {
		return;
	}

	bool currentSourceIsThisButton = false;

	if (centralData->isMappingInProgress()) {
		currentSourceIsThisButton = (centralData->getMappingSource() == id);
		centralData->abortMappingProcedure();
		// TODO: centraData->sendMessage("Aborted mapping");
		// valueLabel->text = "Aborted mapping";
	}
	if (!currentSourceIsThisButton) {
		centralData->startMappingProcedure(id);
		// TODO: centraData->sendMessage("Started mapping...");
		// valueLabel->text = "Start Mapping from: " + std::to_string(static_cast<int>(button.id.objType)) + ", " +
		// std::to_string(button.id.objID);
	}

	if (quantity)
		quantity->setMax();
}

void HubMapButton::onButton(const event::Button &e)
{
	// Right click to open context menu
	if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_RIGHT && (e.mods & RACK_MOD_MASK) == 0) {
		ui::Menu *menu = createMenu();

		// MapFieldLabel *paramLabel = new MapFieldLabel;
		// paramLabel->paramWidget = this;
		// menu->addChild(paramLabel);

		// MapField *paramField = new MapField;
		// paramField->box.size.x = 100;
		// paramField->setParamWidget(this);
		// menu->addChild(paramField);

		// ParamResetItem *resetItem = new ParamResetItem;
		// resetItem->text = "Initialize";
		// resetItem->rightText = "Double-click";
		// resetItem->paramWidget = this;
		// menu->addChild(resetItem);

		MenuSeparator *sep = new MenuSeparator;
		menu->addChild(sep);

		auto aliasItem = new HubKnobAliasNameMenuField{id};
		aliasItem->box.size.x = 100;
		menu->addChild(aliasItem);

		auto paramHandles = centralData->getParamHandlesFromSrc(id);
		for (auto const &ph : paramHandles) {
			if (ph.moduleId != -1) {
				MappedKnobMenuLabel *paramLabel2 = new MappedKnobMenuLabel;
				paramLabel2->moduleName = ph.module->model->name;
				paramLabel2->paramName = ph.module->paramQuantities[ph.paramId]->getLabel();
				paramLabel2->moduleId = ph.moduleId;
				paramLabel2->paramId = ph.paramId;
				menu->addChild(paramLabel2);

				MinSlider *mn = new MinSlider({LabelButtonID::Types::Knob, ph.paramId, ph.moduleId});
				mn->box.size.x = 100;
				menu->addChild(mn);

				MaxSlider *mx = new MaxSlider({LabelButtonID::Types::Knob, ph.paramId, ph.moduleId});
				mx->box.size.x = 100;
				menu->addChild(mx);
			}
		}

		// engine::ParamHandle *paramHandle =
		// 	this->paramQuantity
		// 		? APP->engine->getParamHandle(this->paramQuantity->module->id, this->paramQuantity->paramId)
		// 		: NULL;
		// if (paramHandle) {
		// 	ParamUnmapItem *unmapItem = new ParamUnmapItem;
		// 	unmapItem->text = "Unmap";
		// 	unmapItem->rightText = paramHandle->text;
		// 	unmapItem->paramWidget = this;
		// 	menu->addChild(unmapItem);
		// }
		e.consume(this);
	} else {
		Button::onButton(e);
	}
}

void HubMapButton::onHover(const event::Hover &e)
{
	e.consume(this);
}

void HubMapButton::onLeave(const event::Leave &e)
{
	_hovered = false;
	// if (!centralData->isMappingInProgress())
	centralData->notifyLeaveHover(id);
	e.consume(this);
}

void HubMapButton::onEnter(const event::Enter &e)
{
	_hovered = true;
	// if (!centralData->isMappingInProgress())
	centralData->notifyEnterHover(id);
	e.consume(this);
}

bool HubMapButton::registerMapping(int moduleId, int objId)
{
	if (centralData->isMappingInProgress()) {
		if (moduleId > -1) {
			if (id.moduleID != moduleId) {
				if (!centralData->isRegisteredHub(moduleId)) {
					centralData->registerMapDest({id.objType, objId, moduleId});
					return true;
				}
			}
		}
	}
	return false;
}
