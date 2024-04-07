#pragma once
#include <algorithm>
#include <array>
#include <common.hpp>
#include <engine/Light.hpp>
#include <numeric>

namespace rack::engine
{

static const int PORT_MAX_CHANNELS = 4;

struct Port {
	std::array<float, PORT_MAX_CHANNELS> voltages = {};
	uint8_t channels = 0;

	enum Type {
		INPUT,
		OUTPUT,
	};

	void setVoltage(float v, uint8_t channel = 0) {
		voltages[channel] = v;
	}

	float getVoltage(uint8_t chan = 0) const {
		return voltages[chan];
	}

	float getPolyVoltage(uint8_t channel) const {
		return isMonophonic() ? getVoltage(0) : getVoltage(channel);
	}

	float getNormalVoltage(float normalVoltage, uint8_t channel = 0) const {
		return isConnected() ? getVoltage(channel) : normalVoltage;
	}

	float getNormalPolyVoltage(float normalVoltage, uint8_t channel) const {
		return isConnected() ? getPolyVoltage(channel) : normalVoltage;
	}

	float *getVoltages(uint8_t firstChannel = 0) {
		return &voltages[firstChannel];
	}

	void readVoltages(float *v) const {
		for (uint8_t c = 0; c < channels; c++) {
			v[c] = voltages[c];
		}
	}

	void writeVoltages(const float *v) {
		for (uint8_t c = 0; c < channels; c++) {
			voltages[c] = v[c];
		}
	}

	void clearVoltages() {
		for (uint8_t c = 0; c < channels; c++) {
			voltages[c] = 0.f;
		}
	}

	float getVoltageSum() const {
		return std::accumulate(voltages.begin(), voltages.begin() + channels, 0.f);
		// float sum = 0.f;
		// for (uint8_t c = 0; c < channels; c++) {
		// 	sum += voltages[c];
		// }
		// return sum;
	}

	float getVoltageRMS() const {
		if (channels == 0) {
			return 0.f;
		} else if (channels == 1) {
			return std::fabs(voltages[0]);
		} else {
			auto sum_squares = [](float sum, float v) {
				return sum + v * v;
			};
			return std::sqrt(std::accumulate(voltages.begin(), voltages.begin() + channels, 0.f, sum_squares));

			// float sum = 0.f;
			// for (uint8_t c = 0; c < channels; c++) {
			// 	sum += std::pow(voltages[c], 2);
			// }
			// return std::sqrt(sum);
		}
		// return connected ? std::fabs(voltage) : 0;
	}

	template<typename T>
	T getVoltageSimd(int firstChannel) const {
		return T::load(&voltages[firstChannel]);
		// return T(voltage); // return vector with all elements set to voltage
	}

	template<typename T>
	T getPolyVoltageSimd(int firstChannel) const {
		return isMonophonic() ? getVoltage(0) : getVoltageSimd<T>(firstChannel);
	}

	template<typename T>
	T getNormalVoltageSimd(T normalVoltage, int firstChannel) const {
		return isConnected() ? getVoltageSimd<T>(firstChannel) : normalVoltage;
	}

	template<typename T>
	T getNormalPolyVoltageSimd(T normalVoltage, int firstChannel) const {
		return isConnected() ? getPolyVoltageSimd<T>(firstChannel) : normalVoltage;
	}

	template<typename T>
	void setVoltageSimd(T v, int firstChannel) {
		// voltage = v[0];
		v.store(&voltages[firstChannel]);
	}

	// In VCV Rack:
	//    Sets the number of polyphony channels.
	//    Also clears voltages of higher channels.
	//    If disconnected, this does nothing (`channels` remains 0).
	//    If 0 is given, `channels` is set to 1 but all voltages are cleared.
	// For MM, is this what we want? When would a Module call this?
	void setChannels(int channels) {
		// If disconnected, keep the number of channels at 0.
		if (this->channels == 0) {
			return;
		}
		// Set higher channel voltages to 0

		// FIXME: if channels = 0, then this sets voltages[0] to 0,
		// but then sets this->channels to 1. Is that the right behavoir?
		for (uint8_t c = channels; c < this->channels; c++) {
			voltages[c] = 0.f;
		}
		// Don't allow caller to set port as disconnected
		if (channels == 0) {
			channels = 1;
		}
		this->channels = channels;
	}

	int getChannels() const {
		return channels;
	}

	bool isConnected() const {
		return channels > 0;
	}

	bool isMonophonic() const {
		return channels == 1;
	}

	bool isPolyphonic() const {
		return channels > 1;
	}

	DEPRECATED float normalize(float normalVoltage) const {
		return getNormalVoltage(normalVoltage);
	}
};

struct Output : Port {};

struct Input : Port {};

} // namespace rack::engine
