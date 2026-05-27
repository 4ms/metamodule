#include "plugin.hpp"

namespace rack::core
{

struct Split : Module {
	static constexpr unsigned MaxPoly = CoreProcessor::MaxPolyChannels;

	enum ParamIds { NUM_PARAMS };
	enum InputIds { POLY_INPUT, NUM_INPUTS };
	enum OutputIds { ENUMS(MONO_OUTPUTS, 16), NUM_OUTPUTS };
	enum DisplayIds { ChannelDisplay = 0 };

	int lastChannels = 0;

	Split() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, 0);
		configInput(POLY_INPUT, "Polyphonic");
		for (int i = 0; i < 16; i++)
			configOutput(MONO_OUTPUTS + i, string::f("Channel %d", i + 1));
	}

	void process(const ProcessArgs &args) override {
		for (int c = 0; c < 16; c++) {
			float v = inputs[POLY_INPUT].getVoltage(c);
			// To allow users to debug buggy modules, don't assume that undefined channel voltages are 0V.
			outputs[MONO_OUTPUTS + c].setVoltage(v);
		}

		lastChannels = inputs[POLY_INPUT].getChannels();
	}

	size_t get_display_text(int display_id, std::span<char> text) override {
		int chars_written = snprintf(text.data(), text.size(), "%d", lastChannels);
		return (chars_written < 0) ? 0 : chars_written;
	}
};

struct SplitWidget : ModuleWidget {
	SplitWidget(Split *module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Split.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(10.16f, 33.f)), module, Split::POLY_INPUT));

		// Split-16 (two column module)
		// float space_x = 10.8f;
		// float first_col = (Split::MaxPoly > 8) ? 7.3f : 12.7f;
		// float space_y = 81.3f / std::min(Split::MaxPoly, 8u);
		// float first_row = (42.f - 10.16f / 2) + space_y / 2;

		float space_x = 0;
		float first_col = 10.16f;
		float space_y = 70.f / std::min(Split::MaxPoly, 8u);
		float first_row = 45.f + space_y / 2;

		for (auto i = 0u; i < Split::MaxPoly; i++)
			addInput(createOutputCentered<ThemedPJ301MPort>(
				mm2px(Vec(first_col + space_x * int(i / 8), first_row + (i % 8) * space_y)),
				module,
				Split::MONO_OUTPUTS + i));

		auto *display = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(6.f, 13.f)));
		display->box.size = mm2px(Vec(9.f, 9.f));
		display->font = "Segment7Standard24";
		display->color = Colors565::Yellow;
		display->firstLightId = Split::ChannelDisplay;
		addChild(display);
	}
};

Model *modelSplit = createModel<Split, SplitWidget>("Split");

} // namespace rack::core
