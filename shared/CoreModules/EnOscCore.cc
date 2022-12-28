#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "enosc/ui.hh"

#include <iostream>

class EnOscCore : public CoreProcessor {
	using Info = EnOscInfo;
	using ThisCore = EnOscCore;

	enum { kBlockSize = 8 };
	enum { kUiUpdateRate = 60 };
	enum { kSysTickRate = 200 };

	float sample_rate_ = 48000.f;

	unsigned ui_process_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
	unsigned ui_process_ctr = ui_process_throttle;

	unsigned ui_update_throttle = (unsigned)sample_rate_ / kSysTickRate;
	unsigned ui_update_ctr = ui_update_throttle;

	mutable unsigned block_ctr = kBlockSize;

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

		// Should happen at SampleRate / BlockRate (6kHz for 48k)
		if (block_ctr >= kBlockSize) {
			enosc.Poll();
			// process SpiAdc channel,
			// EventHandler::Poll: Polls each event source
			// freeze_led set color
			enosc.osc().Process(out_block_);
			block_ctr = 0;
		}
	}

	Switches::State switchstate(float val) {
		return val < 0.5f ? Switches::State::DOWN : val < 1.5f ? Switches::State::MID : Switches::State::UP;
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
			case Info::SwitchLearn + Info::NumKnobs:
				enosc.buttons().learn_.set(val > 0.5f);
				break;
			case Info::SwitchFreeze + Info::NumKnobs:
				enosc.buttons().freeze_.set(val > 0.5f);
				break;
			case Info::SwitchScale_Switch + Info::NumKnobs:
				enosc.switches().scale_.set(switchstate(val));
				break;
			case Info::SwitchCross_Fm_Switch + Info::NumKnobs:
				enosc.switches().mod_.set(switchstate(val));
				break;
			case Info::SwitchTwist_Switch + Info::NumKnobs:
				enosc.switches().twist_.set(switchstate(val));
				break;
			case Info::SwitchWarp_Switch + Info::NumKnobs:
				enosc.switches().warp_.set(switchstate(val));
				break;
		}
	}

	void set_input(int input_id, float val) override {
		//val: -1..1 => 0..1
		val += 1.f;
		val *= 0.5f;
		//TODO: Pitch/Root have different scaling?
		switch (input_id) {
			case Info::InputBalance_Jack:
				enosc.set_potcv(AdcInput::CV_BALANCE, val);
				break;
			case Info::InputCross_Fm_Jack:
				enosc.set_potcv(AdcInput::CV_MOD, val);
				break;
			case Info::InputPitch_Jack:
				enosc.set_highres_cv(SpiAdcInput::CV_PITCH, val);
				break;
			case Info::InputRoot_Jack:
				enosc.set_highres_cv(SpiAdcInput::CV_ROOT, val);
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
				//TODO:
				break;
			case Info::InputLearn_Jack:
				//TODO:
				break;
		}
	}

	float get_output(int output_id) const override {
		s9_23 sample = output_id == 0 ? out_block_[block_ctr].l : out_block_[block_ctr].r;
		if (output_id == 1) {
			block_ctr++;
			// if (block_ctr > kBlockSize) {
			// 	block_ctr = kBlockSize;
			// 	std::cout << "OVF!" << std::endl;
			// }
		}
		return f::inclusive(sample).repr() * 2.f; //0..1 is mapped to 0-5V
	}

	void set_samplerate(float sr) override {
		if (sample_rate_ != sr) {
			sample_rate_ = sr;
			ui_process_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
			ui_update_throttle = (unsigned)sample_rate_ / kSysTickRate;
			std::cout << "Freq = " << sr << std::endl;
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
};
