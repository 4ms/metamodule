#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include "module_widget_adaptor.hh"
#include <app/ModuleWidget.hpp>

static constexpr inline bool LogWidgetPlacements = false;

static void log_widget(std::string_view preface, rack::widget::Widget const *widget);

namespace rack::app
{

struct ModuleWidget::Internal {
	app::SvgPanel *panel = nullptr;
	std::unique_ptr<MetaModule::ModuleWidgetAdaptor> adaptor;
	std::vector<ModuleWidget::WidgetElement> drawable_widgets;

	unsigned first_graphic_idx = 0;
	unsigned graphic_display_idx = 200;
};

std::vector<ModuleWidget::WidgetElement> &ModuleWidget::get_drawable_widgets() {
	return internal->drawable_widgets;
}

ModuleWidget::ModuleWidget() {
	internal = new Internal;
	internal->adaptor = std::make_unique<MetaModule::ModuleWidgetAdaptor>();
	box.size = math::Vec(0, RACK_GRID_HEIGHT);
}

ModuleWidget::~ModuleWidget() {
	clearChildren();
	delete internal;
}

plugin::Model *ModuleWidget::getModel() {
	return model;
}

void ModuleWidget::setModel(plugin::Model *m) {
	model = m;
}

engine::Module *ModuleWidget::getModule() {
	return module;
}

void ModuleWidget::setModule(engine::Module *m) {
	if (!m) {
		pr_err("ModuleWidget is not allowed to delete Module\n");
		return;
	}
	if (this->module) {
		pr_err("Error: Setting the module of a ModuleWidget when a module is already set!\n");
	}
	this->module = m;

	internal->graphic_display_idx = std::max(m->lights.size(), m->lightInfos.size());
	internal->first_graphic_idx = internal->graphic_display_idx;

	if (model && model->slug.size())
		pr_trace("setModule for %s\n", model->slug.c_str());
	else if (m->model && m->model->slug.size())
		pr_trace("setModule for %s\n", m->model->slug.c_str());
}

app::SvgPanel *ModuleWidget::getPanel() {
	return internal->panel;
}

void ModuleWidget::setPanel(app::SvgPanel *newpanel) {
	bool first_panel = false;

	// Remove existing panel
	if (internal->panel) {
		removeChild(internal->panel);
		delete internal->panel;
		internal->panel = nullptr;
	} else {
		first_panel = true;
	}

	if (newpanel) {
		Widget::addChild(newpanel);
		internal->panel = newpanel;

		if (newpanel->svg) {
			box.size = newpanel->svg->getSize();
			if (box.size != newpanel->box.size)
				pr_err("Error: In ModuleWidget::setPanel, new panel's svg->getSize() != box.size\n");

			if (first_panel) {
				internal->adaptor->addModuleWidget(internal->graphic_display_idx, this);
				internal->drawable_widgets.push_back({internal->graphic_display_idx, this});
				printf("Panel graphic_display_idx %d\n", internal->graphic_display_idx);
				internal->graphic_display_idx++;
			}
		}
	}
}

void ModuleWidget::setPanel(std::shared_ptr<window::Svg> svg) {
	auto *panel = new SvgPanel;
	panel->setBackground(svg);
	setPanel(panel);
}

//
// Params
//

void ModuleWidget::addParam(app::Knob *widget) {
	log_widget("addParam(Knob)", widget);
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgKnob *widget) {
	log_widget("addParam(SvgKnob)", widget);
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(rack::componentlibrary::Rogan *widget) {
	log_widget("addParam(Rogan)", widget);
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SliderKnob *widget) {
	log_widget("addParam(SliderKnob)", widget);
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgSlider *widget) {
	log_widget("addParam(SvgSlider)", widget);
	// Modify the widget's box to match the background
	// widget->box.pos = widget->box.pos + widget->background->box.pos;
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgSwitch *widget) {
	log_widget("addParam(SvgSwitch)", widget);
	internal->adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::ParamWidget *widget) {
	// Most-specialized to least:
	if (auto w = dynamic_cast<rack::componentlibrary::Rogan *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgKnob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgSlider *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SliderKnob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::Knob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgSwitch *>(widget))
		addParam(w);
	else {
		log_widget("addParam(unknown ParamWidget)", widget);
		Widget::addChild(widget);
	}
}

//
// Param + Light
//

void ModuleWidget::addLightSwitch(app::SvgSwitch *widget, app::ModuleLightWidget *light) {
	log_widget("addLightSwitch()", widget);
	internal->adaptor->addLightParam(widget, light);
	Widget::addChild(widget);
}

void ModuleWidget::addLightSlider(app::SvgSlider *widget, app::ModuleLightWidget *light) {
	log_widget("addLightSwitch()", widget);
	internal->adaptor->addLightParam(widget, light);
	Widget::addChild(light);
}

//
// Lights
//

void ModuleWidget::addChild(app::ModuleLightWidget *widget) {
	log_widget("addChild(ModuleLightWidget)", widget);
	if (widget) {
		Widget::addChild(widget);

		if (widget->getNumColors()) {
			internal->adaptor->addLight(widget);
		} else {
			auto box = widget->box;
			internal->adaptor->addGraphicDisplay(internal->graphic_display_idx, internal->first_graphic_idx, widget);
			internal->drawable_widgets.push_back({internal->graphic_display_idx, widget});
			internal->graphic_display_idx++;

			pr_dbg("Add drawable (light) at (%f, %f) size (%f, %f) ", box.pos.x, box.pos.y, box.size.x, box.size.y);
			pr_dbg("idx %d (firstLightId = %d)\n", internal->graphic_display_idx - 1, widget->firstLightId);
		}
	}
}

void ModuleWidget::addSvgLight(std::string_view image, app::ModuleLightWidget *widget) {
	log_widget("addSvgLight()", widget);
	internal->adaptor->addSvgLight(widget, image);
	Widget::addChild(widget);
}

//
// Ports
//

void ModuleWidget::addInput(app::PortWidget *widget) {
	if (auto w = dynamic_cast<app::SvgPort *>(widget)) {
		addInput(w);
	} else {
		log_widget("addInput(PortWidget)", widget);
		internal->adaptor->addInput(widget);
		Widget::addChild(widget);
	}
}

void ModuleWidget::addInput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	internal->adaptor->addInput(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addOutput(app::PortWidget *widget) {
	if (auto w = dynamic_cast<app::SvgPort *>(widget)) {
		addOutput(w);
	} else {
		log_widget("addOutput(PortWidget)", widget);
		internal->adaptor->addOutput(widget);
		Widget::addChild(widget);
	}
}

void ModuleWidget::addOutput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	internal->adaptor->addOutput(widget);
	Widget::addChild(widget);
}

//
// Image-only
//

void ModuleWidget::addChild(app::SvgScrew *widget) {
	log_widget("addChild(SvgScrew)", widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(Widget *widget) {
	log_widget("addChild(unknown Widget)", widget);
	Widget::addChild(widget);

	internal->adaptor->addGraphicDisplay(internal->graphic_display_idx, internal->first_graphic_idx, widget);
	internal->drawable_widgets.push_back({internal->graphic_display_idx, widget});
	internal->graphic_display_idx++;

	auto box = widget->box;
	pr_dbg("Add drawable at (%f, %f) size (%f, %f) ", box.pos.x, box.pos.y, box.size.x, box.size.y);
	pr_dbg("idx %d\n", internal->graphic_display_idx - 1);
}

void ModuleWidget::addChild(MetaModule::VCVTextDisplay *widget) {
	internal->adaptor->addTextDisplay(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(widget::SvgWidget *widget) {
	log_widget("addChild(SvgWidget)", widget);
	internal->adaptor->addImage(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(app::SvgButton *widget) {
	log_widget("addChild(SvgButton)", widget);
	widget->sw->box.pos = widget->box.pos;
	internal->adaptor->addImage(widget->sw);
	Widget::addChild(widget);
}

//
// Panel
//

void ModuleWidget::addChild(SvgPanel *child) {
	if (child->visible)
		setPanel(child);
	else
		Widget::addChild(child);
}

void ModuleWidget::addChildBottom(SvgPanel *child) {
	if (child->visible)
		setPanel(child);
	else
		Widget::addChild(child);
}

template<class T, typename F>
T *getFirstDescendantOfTypeWithCondition(widget::Widget *w, F f) {
	T *t = dynamic_cast<T *>(w);
	if (t && f(t))
		return t;

	for (widget::Widget *child : w->children) {
		T *foundT = getFirstDescendantOfTypeWithCondition<T>(child, f);
		if (foundT)
			return foundT;
	}
	return nullptr;
}

ParamWidget *ModuleWidget::getParam(int paramId) {
	return getFirstDescendantOfTypeWithCondition<ParamWidget>(
		this, [&](ParamWidget *pw) -> bool { return pw && pw->paramId == paramId; });
}

PortWidget *ModuleWidget::getInput(int portId) {
	return getFirstDescendantOfTypeWithCondition<PortWidget>(
		this, [&](PortWidget *pw) -> bool { return pw && pw->type == engine::Port::INPUT && pw->portId == portId; });
}

PortWidget *ModuleWidget::getOutput(int portId) {
	return getFirstDescendantOfTypeWithCondition<PortWidget>(
		this, [&](PortWidget *pw) -> bool { return pw && pw->type == engine::Port::OUTPUT && pw->portId == portId; });
}

template<class T, typename F>
void doIfTypeRecursive(widget::Widget *w, F f) {
	T *t = dynamic_cast<T *>(w);
	if (t)
		f(t);

	for (widget::Widget *child : w->children) {
		doIfTypeRecursive<T>(child, f);
	}
}

std::vector<ParamWidget *> ModuleWidget::getParams() {
	std::vector<ParamWidget *> pws;
	doIfTypeRecursive<ParamWidget>(this, [&](ParamWidget *pw) { pws.push_back(pw); });
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getPorts() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) { pws.push_back(pw); });
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getInputs() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) {
		if (pw->type == engine::Port::INPUT)
			pws.push_back(pw);
	});
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getOutputs() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) {
		if (pw->type == engine::Port::OUTPUT)
			pws.push_back(pw);
	});
	return pws;
}

void ModuleWidget::populate_elements_indices(rack::plugin::Model *model) {
	// 
	if (auto panel = getPanel()) {
		for (auto *child : panel->fb->children) {
			// Move panel->fb children to mw children
			child->parent = nullptr;
			if (auto svg = dynamic_cast<widget::SvgWidget*>(child)) {
				printf("Add fb child svgwidget %f,%f\n", svg->box.pos.x, svg->box.pos.y);
				addChild(svg);
			} else {
				printf("Add fb child widget %f,%f\n", child->box.pos.x, child->box.pos.y);
				addChild(child);
			}
		}
		panel->fb->children.clear();
	}
	internal->adaptor->populate_elements_indices(model->elements, model->indices);
}

//////////////// No-ops:

void ModuleWidget::draw(const DrawArgs &args) {
}
void ModuleWidget::drawLayer(const DrawArgs &args, int layer) {
}
void ModuleWidget::onHover(const HoverEvent &e) {
}
void ModuleWidget::onHoverKey(const HoverKeyEvent &e) {
}
void ModuleWidget::onButton(const ButtonEvent &e) {
}
void ModuleWidget::onDragStart(const DragStartEvent &e) {
}
void ModuleWidget::onDragEnd(const DragEndEvent &e) {
}
void ModuleWidget::onDragMove(const DragMoveEvent &e) {
}
void ModuleWidget::onDragHover(const DragHoverEvent &e) {
}
json_t *ModuleWidget::toJson() {
	return {};
}
void ModuleWidget::fromJson(json_t *rootJ) {
}
bool ModuleWidget::pasteJsonAction(json_t *rootJ) {
	return false;
}
void ModuleWidget::copyClipboard() {
}
bool ModuleWidget::pasteClipboardAction() {
	return {};
}
void ModuleWidget::load(std::string filename) {
}
void ModuleWidget::loadAction(std::string filename) {
}
void ModuleWidget::loadTemplate() {
}
void ModuleWidget::loadDialog() {
}
void ModuleWidget::save(std::string filename) {
}
void ModuleWidget::saveTemplate() {
}
void ModuleWidget::saveTemplateDialog() {
}
bool ModuleWidget::hasTemplate() {
	return {};
}
void ModuleWidget::clearTemplate() {
}
void ModuleWidget::clearTemplateDialog() {
}
void ModuleWidget::saveDialog() {
}
void ModuleWidget::disconnect() {
}
void ModuleWidget::resetAction() {
}
void ModuleWidget::randomizeAction() {
}
void ModuleWidget::appendDisconnectActions(history::ComplexAction *complexAction) {
}
void ModuleWidget::disconnectAction() {
}
void ModuleWidget::cloneAction(bool cloneCables) {
}
void ModuleWidget::bypassAction(bool bypassed) {
}
void ModuleWidget::removeAction() {
}
void ModuleWidget::createContextMenu() {
}
math::Vec ModuleWidget::getGridPosition() {
	return {};
}
void ModuleWidget::setGridPosition(math::Vec pos) {
}
math::Vec ModuleWidget::getGridSize() {
	return {};
}
math::Rect ModuleWidget::getGridBox() {
	return {};
}

} // namespace rack::app

static void log_widget(std::string_view preface, rack::widget::Widget const *widget) {
	if (!widget)
		pr_err("%s: Null widget\n", preface.data());

	if constexpr (LogWidgetPlacements) {
		auto box = widget->box;
		pr_trace("%s at (%f, %f) size (%f, %f)\n", preface.data(), box.pos.x, box.pos.y, box.size.x, box.size.y);
	}
}
