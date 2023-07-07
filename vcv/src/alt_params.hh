#pragma once
#include <rack.hpp>

// Alt Params are hidden parameters normally accessed only by a pressing/turning
// controls in a special way (i.e. hold a button and turn a knob, or via a special
// System Settings Mode) on normal hardware modules.
//
// On Metamodule, they are accessed when inspecting a module, but they cannot be mapped.
//
// In VCV, they are accessed by a right-click menu on the module
// They do not have an associated widget.
//
// TODO: Make this work
// -- add AltParms to Info files

// TODO: make a choose-one-of-two/three button array instead of slider
// Can use it when Range is Integer and max-min <= 3
// Can query names with get_alt_param_value(id, min|..|max);
struct AltParamQty : rack::Quantity {
	const AltParamDef &_alt;
	CommModule &_module;
	float _val;

	AltParamQty(CommModule &module, const AltParamDef &alt)
		: _alt{alt}
		, _module{module}
		, _val{alt.default_val} {
		for (auto &ap : _module.altParams) {
			if (ap.id == _alt.id) {
				_val = ap.val;
				break;
			}
		}
	}

	void setValue(float value) override {
		float prev_val = _val;
		_val = std::clamp(value, _alt.min_val, _alt.max_val);
		if (_alt.control_type == AltParamDef::Range::Integer)
			_val = (int)(_val + 0.5f);

		if (prev_val == _val)
			return;

		for (auto &ap : _module.altParams) {
			if (ap.id == _alt.id) {
				ap.is_updated = true;
				ap.val = _val;
				break;
			}
		}
	}

	std::string getDisplayValueString() override {
		if (_module.core)
			return std::string{_module.core->get_alt_param_value(_alt.id, _val)};
		return std::to_string(_val);
	}

	float getValue() override {
		return _val;
	}
	float getMinValue() override {
		return _alt.min_val;
	}
	float getMaxValue() override {
		return _alt.max_val;
	}
	float getDefaultValue() override {
		return _alt.default_val;
	}
};

struct AltParamSlider : rack::ui::Slider {
	AltParamSlider(CommModule &module, const AltParamDef &alt) {
		quantity = new AltParamQty{module, alt};
	}
	~AltParamSlider() {
		delete quantity;
	}
};
