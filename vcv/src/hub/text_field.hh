#pragma once
#include <rack.hpp>
#include <string_view>

struct MetaModuleTextField : rack::LedDisplayTextField {
	using CallbackT = std::function<void(std::string const &)>;
	CallbackT onChangeCallback;

	MetaModuleTextField(CallbackT &&callback)
		: onChangeCallback{callback} {
	}

	void onChange(const ChangeEvent &event) override {
		onChangeCallback(text);
	}
};
