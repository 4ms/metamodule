#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
// #include "info/EnOsc_info.hh"
#include "enosc/altparam_EnOsc_info.hh"
#include "enosc/ui.hh"

namespace MetaModule
{

class EnOscCore : public CoreProcessor {
	// using Info = APEnOscInfo;
	using Info = EnOscInfo;
	using ThisCore = EnOscCore;
	enum { NumKnobs = Info::KnobWarp + 1 };

	enum { kBlockSize = 64 };
	enum { kUiUpdateRate = 60 };
	enum { kUiProcessRate = 20 };

public:
	EnOscCore() = default;

	void update() override {
		// Low-priority thread
		// in while loop:
		if (ui_process_ctr++ > ui_process_throttle) {
			ui_process_ctr = 0;
			enosc.Process(); //EventHandler::Process
		}

		if (ui_update_ctr++ > ui_update_throttle) {
			ui_update_ctr = 0;
			enosc.Update(); //LED update
		}

		// SampleRate / BlockRate (6kHz for 48k)
		if (++block_ctr >= kBlockSize) {
			block_ctr = 0;
			enosc.Poll();
			enosc.osc().Process(out_block_);
		}
	}

	// DOWN=0 / MID=0.5 / UP=1.0
	Switches::State switchstate(float val) {
		return val < 0.25f ? Switches::State::DOWN : val < 0.75f ? Switches::State::MID : Switches::State::UP;
	}

	// TODO: re-arrange AdcInput enums to match
	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobBalance:
				enosc.set_potcv(AdcInput::POT_BALANCE, val);
				break;
			case Info::KnobCross_Fm:
				enosc.set_potcv(AdcInput::POT_MOD, val);
				break;
			case Info::KnobDetune:
				enosc.set_potcv(AdcInput::POT_DETUNE, val);
				break;
			case Info::KnobPitch:
				enosc.set_potcv(AdcInput::POT_PITCH, val);
				break;
			case Info::KnobRoot:
				enosc.set_potcv(AdcInput::POT_ROOT, val);
				break;
			case Info::KnobScale:
				enosc.set_potcv(AdcInput::POT_SCALE, val);
				break;
			case Info::KnobSpread:
				enosc.set_potcv(AdcInput::POT_SPREAD, val);
				break;
			case Info::KnobTwist:
				enosc.set_potcv(AdcInput::POT_TWIST, val);
				break;
			case Info::KnobWarp:
				enosc.set_potcv(AdcInput::POT_WARP, val);
				break;
			case static_cast<int>(Info::SwitchLearn) + NumKnobs:
				enosc.set_learn_button(val > 0.5f);
				break;
			case static_cast<int>(Info::SwitchFreeze) + NumKnobs:
				enosc.set_freeze_button(val > 0.5f);
				break;
			case static_cast<int>(Info::SwitchScale_Switch) + NumKnobs:
				enosc.switches().scale_.set(switchstate(val));
				break;
			case static_cast<int>(Info::SwitchCross_Fm_Switch) + NumKnobs:
				enosc.switches().mod_.set(switchstate(val));
				break;
			case static_cast<int>(Info::SwitchTwist_Switch) + NumKnobs:
				enosc.switches().twist_.set(switchstate(val));
				break;
			case static_cast<int>(Info::SwitchWarp_Switch) + NumKnobs:
				enosc.switches().warp_.set(switchstate(val));
				break;
		}
	}

	void set_alt_param(const int alt_param_id, const float val) override {
		switch (alt_param_id) {
			case Info::AltStereo_Split:
				enosc.set_stereo_mode(static_cast<SplitMode>(val));
				break;
			case Info::AltNum_Oscs:
				enosc.set_num_osc(val);
				break;
			case Info::AltCrossfade_Time:
				enosc.set_crossfade(val);
				break;
			case Info::AltFreeze_Split:
				enosc.set_freeze_mode(static_cast<SplitMode>(val));
				break;
		}
	}

	void set_input(int input_id, float val) override {
		//val: -5V..+5V converted to -1..1 by CommModule
		val *= -0.5f; //-1..1 => 0.5..-0.5
		val += 0.5f;  // => 1..0
					  // Ui::set_potcv will clamp
		switch (input_id) {
			case Info::InputBalance_Jack:
				enosc.set_potcv(AdcInput::CV_BALANCE, val);
				break;
			case Info::InputCross_Fm_Jack:
				enosc.set_potcv(AdcInput::CV_MOD, val);
				break;
			case Info::InputPitch_Jack:
				enosc.set_pitchroot_cv(SpiAdcInput::CV_PITCH, val);
				break;
			case Info::InputRoot_Jack:
				enosc.set_pitchroot_cv(SpiAdcInput::CV_ROOT, val);
				break;
			case Info::InputScale_Jack:
				enosc.set_potcv(AdcInput::CV_SCALE, val);
				break;
			case Info::InputSpread_Jack:
				enosc.set_potcv(AdcInput::CV_SPREAD, val);
				break;
			case Info::InputTwist_Jack:
				enosc.set_potcv(AdcInput::CV_TWIST, val);
				break;
			case Info::InputWarp_Jack:
				enosc.set_potcv(AdcInput::CV_WARP, val);
				break;
			case Info::InputFreeze_Jack:
				enosc.set_freeze_gate(val > 0.5f);
				break;
			case Info::InputLearn_Jack:
				enosc.set_learn_gate(val > 0.5f);
				break;
		}
	}

	float get_output(int output_id) const override {
		s9_23 sample = output_id == 0 ? out_block_[block_ctr].l : out_block_[block_ctr].r;
		auto s = f::inclusive(sample).repr() * 2.f; //0..1 is mapped to 0-5V
		return s;
	}

	void set_samplerate(float sr) override {
		if (sample_rate_ != sr) {
			sample_rate_ = sr;
			ui_process_throttle = (unsigned)sample_rate_ / kUiProcessRate;
			ui_update_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
		}
	}

	float get_led_brightness(int led_id) const override {
		if (led_id < 0 || led_id > 5)
			return 0.f;

		if (led_id < 3) {
			auto c = enosc.get_learn_led_color();
			auto el = led_id == 0 ? c.red() : led_id == 1 ? c.green() : c.blue();
			return f::inclusive(el).repr();
		} else {
			auto c = enosc.get_freeze_led_color();
			auto el = led_id == 3 ? c.red() : led_id == 4 ? c.green() : c.blue();
			return f::inclusive(el).repr();
		}
	}

	static constexpr std::string_view NumString[16] = {
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};

	constexpr std::string_view get_alt_param_value(unsigned alt_id, float val) override {
		switch (alt_id) {
			case Info::AltStereo_Split:
				return val < 0.5f ? "Even/Odd" : val < 1.5f ? "Low/High" : "Root/Others";
				break;

			case Info::AltNum_Oscs:
				if (val < 1 || val > 16)
					return "";
				return NumString[((int)val) - 1];
				break;

			case Info::AltCrossfade_Time:
				if (val < 0 || val > 1)
					return "";
				return NumString[(int)(val * 10.f)];
				break;

			case Info::AltFreeze_Split:
				return val < 0.5f ? "Even/Odd" : val < 1.5f ? "Low/High" : "Root/Others";
				break;
		}
		return "";
	}

	void mark_all_inputs_unpatched() override {
		for (unsigned i = 0; i < 10; /*Info::NumInJacks*/ i++)
			set_input(i, 0.f);
	}
	void mark_input_unpatched(const int input_id) override {
		set_input(input_id, 0.f);
	}
	void mark_input_patched(const int input_id) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	Ui<kUiUpdateRate, kBlockSize> enosc;
	Buffer<Frame, kBlockSize> out_block_;
	DynamicData dydata;
	Math math;

	float sample_rate_ = 48000.f;

	unsigned ui_process_throttle = (unsigned)sample_rate_ / kUiProcessRate;
	unsigned ui_process_ctr = ui_process_throttle;

	unsigned ui_update_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
	unsigned ui_update_ctr = ui_update_throttle;

	unsigned block_ctr = kBlockSize;
};

} // namespace MetaModule
