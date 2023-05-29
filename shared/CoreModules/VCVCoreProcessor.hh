#pragma once
#include "coreProcessor.h"

template<typename InfoT>
struct VCVCoreProcessor : CoreProcessor {

	// VCV rack::Module::ProcessArgs
	struct ProcessArgs {
		float sampleRate;
		float sampleTime;
		int64_t frame;
	};
	struct Param {
		float value = 0.f;
		float getValue() {
			return value;
		}
		void setValue(float value) {
			this->value = value;
		}
	};
	struct Light {
		float value = 0.f;
		float getBrightness() {
			return value;
		}
		void setBrightness(float value) {
			this->value = value;
		}
		void setBrightnessSmooth(float value, int steps, float lambda) { //??? check signature
			setBrightness(value);
		}
	};
	struct Port {
		float voltage = 0.f;
		bool connected = false;
		float getVoltage(int channel = 0) {
			return voltage;
		}
		template<typename T>
		float getVoltageSimd(int firstChannel) {
			return getVoltage(0);
		}
		void setVoltage(float voltage, int channel = 0) {
			this->voltage = voltage;
		}
		template<typename T>
		void setVoltageSimd(float voltage, int firstChannel) {
			setVoltage(voltage, 0);
		}
		bool isConnected() {
			return connected;
		}
		bool isMonophonic() {
			return connected;
		}
		bool isPolyphonic() {
			return false;
		}
		void setChannels(int) {
		}
	};

	virtual void process(ProcessArgs &) = 0;

	void update() override {
		args.frame++;
		process(args);
	}

	void set_samplerate(float rate) override {
		args.sampleRate = rate;
		args.sampleTime = 1.f / rate;
	}

	void set_param(int id, float val) override {
		params[id].setValue(val);
	}
	void set_input(const int input_id, const float val) override {
		inputs[input_id].setVoltage(val);
	}
	float get_output(const int output_id) const override {
		return outputs[output_id].getVoltage();
	}

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};
	std::array<Param, InfoT::knobs.size()> params;
	std::array<Port, InfoT::injacks.size()> inputs;
	std::array<Port, InfoT::outjacks.size()> outputs;
};
