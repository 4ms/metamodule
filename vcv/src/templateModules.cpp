#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct TemplateFour : public CommModule {

	enum ParamIds {
		ENUMS(KNOBS, 3),
		NUM_PARAMS
	};
	enum InputIds {
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUTS, 2),
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	TemplateFour()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct TemplateFourWidget : CommModuleWidget {

	TemplateFourWidget(TemplateFour *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		for (int i = 0; i < TemplateFour::NUM_PARAMS; i++) {
			addLabeledKnob(std::to_string(i + 1), i, {0, (float)i});
		}
		for (int i = 0; i < TemplateFour::NUM_OUTPUTS; i++) {
			addLabeledOutput("OUT", i, {0, (float)i});
		}
		addLabeledInput("IN", 0, {0, 2});
	}
};

Model *modelTemplate4 = createModel<TemplateFour, TemplateFourWidget>("4hptemplate");

struct TemplateEight : CommModule {

	enum ParamIds {
		ENUMS(KNOBS, 6),
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUTS, 3),
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUTS, 3),
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	TemplateEight()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct TemplateEightWidget : CommModuleWidget {

	TemplateEightWidget(TemplateEight *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		for (int i = 0; i < TemplateEight::NUM_PARAMS; i++) {
			if (i < 3) {
				addLabeledKnob("KNOB", i, {0, (float)i});
			}
			else {
				addLabeledKnob("KNOB", i, {1, (float)(i - 3)});
			}
		}
		for (int i = 0; i < TemplateEight::NUM_OUTPUTS; i++) {
			addLabeledInput("IN", i, {0, (float)i});
		}
		for (int i = 0; i < TemplateEight::NUM_INPUTS; i++) {
			addLabeledOutput("OUT", i, {1, (float)i});
		}
	}
};

Model *modelTemplate8 = createModel<TemplateEight, TemplateEightWidget>("8hptemplate");

struct TemplateTwelve : CommModule {

	enum ParamIds {
		ENUMS(KNOBS, 6),
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUTS, 3),
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUTS, 3),
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	TemplateTwelve()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct TemplateTwelveWidget : CommModuleWidget {

	TemplateTwelveWidget(TemplateTwelve *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hpTemplate.svg")));

		for (int i = 0; i < TemplateTwelve::NUM_PARAMS; i++) {
			if (i < 3) {
				addLabeledKnob("KNOB", i, {(float)i, 0});
			}
			else {
				addLabeledKnob("KNOB", i, {(float(i - 3)), 1});
			}
		}
		for (int i = 0; i < TemplateTwelve::NUM_OUTPUTS; i++) {
			addLabeledOutput("OUT", i, {(float)i, 0});
		}
		for (int i = 0; i < TemplateTwelve::NUM_INPUTS; i++) {
			addLabeledInput("IN", i, {(float)i, 1});
		}
	}
};

Model *modelTemplate12 = createModel<TemplateTwelve, TemplateTwelveWidget>("12hptemplate");

struct TemplateSixteen : CommModule {

	enum ParamIds {
		ENUMS(KNOBS, 12),
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUTS, 4),
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUTS, 4),
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	TemplateSixteen()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct TemplateSixteenWidget : CommModuleWidget {

	TemplateSixteenWidget(TemplateSixteen *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));

		for (int i = 0; i < TemplateSixteen::NUM_PARAMS; i++) {
			addLabeledKnob("KNOB", i, {(float)(i % 4), (float)(i % 3)});
		}
		for (int i = 0; i < TemplateSixteen::NUM_OUTPUTS; i++) {
			addLabeledOutput("OUT", i, {(float)i, 0});
		}
		for (int i = 0; i < TemplateSixteen::NUM_INPUTS; i++) {
			addLabeledInput("IN", i, {(float)i, 1});
		}
	}
};

Model *modelTemplate16 = createModel<TemplateSixteen, TemplateSixteenWidget>("16hptemplate");
