#include "plugin.hpp"

namespace rack::core
{

struct Merge : Module {
	static constexpr unsigned MaxPoly = CoreProcessor::MaxPolyChannels;

	enum ParamIds { NUM_PARAMS };
	enum InputIds { ENUMS(MONO_INPUTS, MaxPoly), NUM_INPUTS };
	enum OutputIds { POLY_OUTPUT, NUM_OUTPUTS };
	enum DisplayIds { ChannelDisplay = 0 };

	int channels = -1;
	int automaticChannels = 0;

	Merge() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, 0);
		for (auto i = 0u; i < MaxPoly; i++)
			configInput(MONO_INPUTS + i, string::f("Channel %d", i + 1));
		configOutput(POLY_OUTPUT, "Polyphonic");

		onReset();
	}

	void onReset() override {
		channels = -1;
	}

	void process(const ProcessArgs &args) override {
		int lastChannel = -1;
		for (auto c = 0u; c < MaxPoly; c++) {
			float v = 0.f;
			if (inputs[MONO_INPUTS + c].isConnected()) {
				lastChannel = c;
				v = inputs[MONO_INPUTS + c].getVoltage();
			}
			outputs[POLY_OUTPUT].setVoltage(v, c);
		}
		automaticChannels = lastChannel + 1;

		// In order to allow 0 channels, modify `channels` directly instead of using `setChannels()`
		outputs[POLY_OUTPUT].channels = (channels >= 0) ? channels : automaticChannels;
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "channels", json_integer(channels));
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *channelsJ = json_object_get(rootJ, "channels");
		if (channelsJ)
			channels = json_integer_value(channelsJ);
	}

	size_t get_display_text(int display_id, std::span<char> text) override {
		int chars_written = snprintf(text.data(), text.size(), "%d", (channels < 0) ? automaticChannels : channels);
		return (chars_written < 0) ? 0 : chars_written;
	}
};

struct MergeWidget : ModuleWidget {
	MergeWidget(Merge *module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Merge.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(10.16f, 32.f)), module, Merge::POLY_OUTPUT));

		// Merge-16 (two column module):
		// float space_x = 10.8f;
		// float first_col = (Split::MaxPoly > 8) ? 7.3f : 12.7f;
		// float space_y = 81.3f / std::min(Split::MaxPoly, 8u);
		// float first_row = (42.f - 10.16f / 2) + space_y / 2;

		float space_x = 0;
		float first_col = 10.16f;
		float space_y = 70.f / std::min(Merge::MaxPoly, 8u);
		float first_row = 45.f + space_y / 2;

		for (auto i = 0u; i < Merge::MaxPoly; i++)
			addInput(createInputCentered<ThemedPJ301MPort>(
				mm2px(Vec(first_col + space_x * int(i / 8), first_row + (i % 8) * space_y)),
				module,
				Merge::MONO_INPUTS + i));

		auto *display = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(6, 13)));
		display->box.size = mm2px(Vec(9.f, 9.f));

		display->font = "Segment7Standard24";
		display->color = Colors565::Yellow;
		display->firstLightId = Merge::ChannelDisplay;

		addChild(display);
	}

	void appendContextMenu(Menu *menu) override {
		Merge *module = dynamic_cast<Merge *>(this->module);

		menu->addChild(new MenuSeparator);

		std::vector<std::string> channelLabels;
		channelLabels.push_back(string::f("Automatic (%d)", module->automaticChannels));
		for (auto i = 0u; i <= Merge::MaxPoly; i++) {
			channelLabels.push_back(string::f("%d", i));
		}
		menu->addChild(createIndexSubmenuItem(
			"Channels",
			channelLabels,
			[=]() { return module->channels + 1; },
			[=](int i) { module->channels = i - 1; }));
	}
};

Model *modelMerge = createModel<Merge, MergeWidget>("Merge");
} // namespace rack::core
