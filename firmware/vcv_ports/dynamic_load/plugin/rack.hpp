#pragma once
// #include <vector>

struct ProcessArgs {};

namespace rack::engine
{
struct Param {
	float value = 0.f;

	float getValue() {
		return value;
	}

	void setValue(float value) {
		this->value = value;
	}
};

struct Port {
	float voltage = 0.f;
	bool connected = false;

	void setVoltage(float v, int channel = 0) {
		voltage = v;
	}

	float getVoltage(int chan = 0) const {
		return voltage;
	}
};

struct Output : Port {};
struct Input : Port {};

} // namespace rack::engine

struct Module {
	rack::engine::Param params[2];
	rack::engine::Input inputs[2];
	rack::engine::Output outputs[2];
	// std::vector<rack::engine::Param> params;
	// std::vector<rack::engine::Input> inputs;
	// std::vector<rack::engine::Output> outputs;
	// std::vector<rack::engine::Light> lights;

	virtual void process(const ProcessArgs &args) = 0;

	void config(unsigned num_params, unsigned num_inputs, unsigned num_outputs, unsigned num_lights = 0) {
	}
};

struct ModuleWidget {
	Module *module;

	void setModule(Module *module) {
		this->module = module;
	}
};

struct Model {
	const char *slug;
};

template<typename ModelT, typename WidgetT>
Model *createModel(const char *slug) {
	static Model model{slug};
	return &model;
}

struct Plugin {
	Model *models[2];
	void addModel(Model *model) {
		models[0] = model;
	}
};
