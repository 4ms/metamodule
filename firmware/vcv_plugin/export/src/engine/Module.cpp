#include "engine/Module.hpp"
#include "CoreModules/elements/units.hh"
#include "app/ModuleWidget.hpp"
#include "console/pr_dbg.hh"
#include "jansson.h"
#include "vcv_plugin/internal/nanovg_pixbuf.hh"
#include <array>
#include <context.hpp>
#include <engine/Engine.hpp>
#include <string_view>

namespace rack::engine
{

struct Module::Internal {
	struct Display {
		rack::widget::Widget *widget{};
		rack::app::ModuleWidget::DrawArgs args{};
		std::span<uint32_t> pix_buffer;
	};

	std::map<int, Display> displays;
};

Module::Module()
	: internal{new Internal} {
	onReset();
}

Module::~Module() {
	for (auto paramQuantity : paramQuantities) {
		if (paramQuantity)
			delete paramQuantity;
	}
	for (auto inputInfo : inputInfos) {
		if (inputInfo)
			delete inputInfo;
	}
	for (auto outputInfo : outputInfos) {
		if (outputInfo)
			delete outputInfo;
	}
	for (auto lightInfo : lightInfos) {
		if (lightInfo)
			delete lightInfo;
	}

	for (auto &[id, _] : internal->displays) {
		hide_graphic_display(id);
	}

	delete internal;
}

void Module::load_state(std::string_view state_data) {
	if (state_data.size() == 0) {
		onReset();
		return;
	}

	json_error_t err;

	json_t *root = json_loadb((char *)state_data.data(), state_data.size(), 0, &err);
	if (!root) {
		pr_err("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
		return;
	}

	// we need to check if the incoming state data is a preset or patch
	// occasionally presets use params, and other times they use the data node.
	// the params node is always present, however the data node is not.
	const auto is_preset = [root]() {
		std::array<std::string_view, 4> nodes = {
			"plugin",
			"model",
			"version",
			"params",
		};

		for (const auto i : nodes) {
			if (!json_object_get(root, i.data())) {
				return false;
			}
		}
		return true;
	}();

	if (is_preset) {
		if (auto node = json_object_get(root, "data"); node) {
			this->dataFromJson(node);
		}
		if (auto node = json_object_get(root, "params"); node) {
			this->paramsFromJson(node);
		}
	} else {
		this->dataFromJson(root);
	}

	json_decref(root);
}

std::string Module::save_state() {
	json_t *dataJ = this->dataToJson();

	if (!dataJ)
		return {};

	std::string state_data;
	auto sz = json_dumpb(dataJ, nullptr, 0, JSON_COMPACT);
	if (sz > 0) {
		state_data.resize(sz);
		json_dumpb(dataJ, (char *)state_data.data(), sz, JSON_COMPACT);
	}

	json_decref(dataJ);

	return state_data;
}

void Module::config(int num_params, int num_inputs, int num_outputs, int num_lights) {
	params.resize(num_params);
	for (auto &x : params)
		x.value = 0;

	inputs.resize(num_inputs);
	for (auto &x : inputs)
		x.setVoltage(0.f);

	outputs.resize(num_outputs);
	for (auto &x : outputs)
		x.setVoltage(0.f);

	lights.resize(num_lights);
	for (auto &x : lights)
		x.value = 0;

	paramQuantities.resize(num_params);

	inputInfos.resize(num_inputs);

	outputInfos.resize(num_outputs);

	lightInfos.resize(num_lights);
}

void Module::update(const ProcessArgs &args, bool bypassed) {
	if (bypassed)
		processBypass(args);
	else
		process(args);
}

void Module::processBypass(const ProcessArgs &args) {
	for (BypassRoute &bypassRoute : bypassRoutes) {
		// Route input voltages to output
		Input &input = inputs[bypassRoute.inputId];
		Output &output = outputs[bypassRoute.outputId];
		int channels = input.getChannels();
		for (int c = 0; c < channels; c++) {
			float v = input.getVoltage(c);
			output.setVoltage(v, c);
		}
		output.setChannels(channels);
	}
}

std::string Module::createPatchStorageDirectory() {
	return "";
}

std::string Module::getPatchStorageDirectory() {
	return "";
}

void Module::set_samplerate(float rate) {
	APP->engine->setSampleRate(rate);
	args.sampleRate = rate;
	args.sampleTime = 1.f / rate;
	onSampleRateChange({.sampleRate = rate, .sampleTime = 1.f / rate});
}

json_t *Module::toJson() {
	return nullptr;
}

void Module::fromJson(json_t *rootJ) {
}

json_t *Module::paramsToJson() {
	json_t *rootJ = json_array();
	for (size_t paramId = 0; paramId < paramQuantities.size(); paramId++) {
		if (!paramQuantities[paramId])
			continue;

		// Don't serialize unbounded Params
		if (!paramQuantities[paramId]->isBounded())
			continue;

		json_t *paramJ = paramQuantities[paramId]->toJson();

		json_object_set_new(paramJ, "id", json_integer(paramId));

		json_array_append_new(rootJ, paramJ);
	}
	return rootJ;
}

void Module::paramsFromJson(json_t *rootJ) {
	size_t i{};
	json_t *paramJ{};
	json_array_foreach(rootJ, i, paramJ) {
		// Get paramId
		json_t *paramIdJ = json_object_get(paramJ, "id");
		// Legacy v0.6 to <v1
		if (!paramIdJ)
			paramIdJ = json_object_get(paramJ, "paramId");
		size_t paramId{};
		if (paramIdJ)
			paramId = json_integer_value(paramIdJ);
		// Use index if all else fails
		else
			paramId = i;

		// Check ID bounds
		if (paramId >= paramQuantities.size())
			continue;

		ParamQuantity *pq = paramQuantities[paramId];
		// Check that the Param is bounded
		if (!pq->isBounded())
			continue;

		json_t *valueJ = json_object_get(paramJ, "value");
		if (valueJ)
			pq->setImmediateValue(json_number_value(valueJ));
	}
}

void Module::onReset(const ResetEvent &e) {
}

void Module::onRandomize(const RandomizeEvent &e) {
}

bool Module::isBypassed() {
	return false;
}

void Module::show_graphic_display(int display_id, std::span<uint32_t> pix_buffer, unsigned width, lv_obj_t *canvas) {
	auto find_widget = [&] -> widget::Widget * {
		auto graphics = module_widget->get_drawable_widgets();
		for (auto &gr : graphics) {
			if (gr.element_idx == (unsigned)display_id)
				return gr.widget;
		}
		return nullptr;
	};

	if (auto widget = find_widget()) {
		if (pix_buffer.size()) {
			auto height = pix_buffer.size() / width;

			uint32_t px_per_3U =
				std::round((float)width / MetaModule::svgpx_to_pngpx(widget->box.getWidth(), 240) * 240);

			auto &disp = internal->displays[display_id];
			disp.widget = widget;
			disp.pix_buffer = pix_buffer;
			disp.args.vg = nvgCreatePixelBufferContext(canvas, pix_buffer, width, px_per_3U);
			disp.args.fb = nullptr;

			pr_trace("rack show_graphic_display(): id:%d canvas at %d, %d (%u x %u, 3u=%u)\n",
					 display_id,
					 MetaModule::svgpx_to_pngpx(widget->box.pos.x),
					 MetaModule::svgpx_to_pngpx(widget->box.pos.y),
					 width,
					 height,
					 px_per_3U);

			pr_trace(" -- Create NVGContext %p buffer %p\n", disp.args.vg, pix_buffer.data());
		} else {
			auto &disp = internal->displays[display_id];
			disp.widget = widget;
			disp.pix_buffer = std::span<uint32_t>{};
			pr_dbg("rack::Module::show_graphic_display(): step()-only display id:%u\n", display_id);
		}
	} else {
		pr_warn("rack::Module::show_graphic_display() could not find widget (id: %d, w: %u)\n", display_id, width);
	}
}

bool Module::draw_graphic_display(int display_id) {
	if (auto entry = internal->displays.find(display_id); entry != internal->displays.end()) {

		auto &disp = entry->second;

		// Non-drawable item: just call step()
		if (disp.pix_buffer.size() == 0) {
			disp.widget->step();
			return true;
		}

		if (!disp.widget->isVisible())
			return false;

		if (!disp.args.vg)
			return false;

		rack::contextGet()->window->vg = disp.args.vg;
		std::ranges::fill(disp.pix_buffer, 0);

		nvgBeginFrame(disp.args.vg, disp.widget->box.getWidth(), disp.widget->box.getHeight(), 1);

		disp.args.clipBox = disp.widget->getBox().zeroPos();

		disp.widget->step();

		// Iterate children
		for (auto *child : disp.widget->children) {
			if (child->isVisible())
				child->step();
		}

		disp.widget->draw(disp.args);
		disp.widget->drawLayer(disp.args, 1);

		nvgEndFrame(disp.args.vg);

		return true;
	} else {
		pr_err("cannot find display %d\n", display_id);
		return false;
	}
}

void Module::hide_graphic_display(int display_id) {
	if (auto entry = internal->displays.find(display_id); entry != internal->displays.end()) {
		auto &disp = entry->second;
		if (disp.pix_buffer.size() && disp.args.vg) {
			pr_trace("rack hide_graphic_display(): call nvgDeletePixelBufferContext(NVGcontext %p)\n", disp.args.vg);
			nvgDeletePixelBufferContext(disp.args.vg);
			disp.args.vg = nullptr;
		}
	}
}

} // namespace rack::engine
