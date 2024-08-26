#include "../firmware/src/medium/debug_raw.h"
#include "CoreModules/CoreHelper.hh"
#include "CoreModules/async_thread.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/STS_info.hh"
#include "sampler/channel_mapping.hh"
#include "sampler/sampler_channel.hh"
#include "sampler/src/sts_filesystem.hh"
#include "sdcard.hh"

namespace MetaModule
{

class STSCore : public CoreProcessor {
public:
	using Info = STSInfo;
	using ThisCore = STSCore;
	using enum Info::Elem;

private:
	// Run this in the low-pri thread:
	AsyncThread fs_thread{[this]() {
		if (tm - last_tm >= 1.0f) {
			// DebugPin1High();
			last_tm = tm;
			chanL.fs_process(tm);
			chanR.fs_process(tm);
			// DebugPin1Low();
			// index_loader.handle_events();
		}
	}};

public:
	STSCore() {
		// sd.reload();
		// TODO: load index
		SamplerKit::Flags flags;
		SamplerKit::SampleIndexLoader index_loader{sd, samples, banks, flags};
		index_loader.load_all_banks();
	}

	void update() override {
		tm += ms_per_update;
		chanL.update(tm);
		chanR.update(tm);

		if (!started_fs_thread && id > 0) {
			fs_thread.start(id);
			started_fs_thread = true;
		}
	}

	void set_param(int param_id, float val) override {
		if (chanL.set_param(param_id, val))
			return;
		else
			chanR.set_param(param_id, val);
	}

	void set_input(int input_id, float val) override {
		if (chanL.set_input(input_id, val))
			return;
		else
			chanR.set_input(input_id, val);
	}

	float get_output(int output_id) const override {
		if (output_id == OutL) {
			return chanL.get_output(OutL).value_or(0) + chanR.get_output(OutL).value_or(0);

		} else if (output_id == OutR) {
			return chanL.get_output(OutR).value_or(0) + chanR.get_output(OutR).value_or(0);

		} else if (auto found = chanL.get_output(output_id); found.has_value()) {
			return *found;

		} else if (auto found = chanR.get_output(output_id); found.has_value()) {
			return *found;
		}
		return 0.f;
	}

	void set_samplerate(float sr) override {
		chanL.set_samplerate(sr);
		chanR.set_samplerate(sr);
		ms_per_update = 1000.f / sr;
	}

	float get_led_brightness(int led_id) const override {
		if (auto found = chanL.get_led_brightness(led_id); found.has_value())
			return *found;

		else if (auto found = chanR.get_led_brightness(led_id); found.has_value())
			return *found;

		else
			return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	SamplerKit::Sdcard sd{"1:/"};
	SamplerKit::SampleList samples;
	SamplerKit::BankManager banks{samples};
	SamplerKit::UserSettings settings;
	SamplerKit::CalibrationStorage cal_storage;

	float tm = 0;
	float last_tm = 0;
	float ms_per_update = 1000.f / 48000.f;
	bool started_fs_thread = false;

	constexpr static uint8_t OutL = CoreHelper<STSInfo>::output_index<OutLOut>();
	constexpr static uint8_t OutR = CoreHelper<STSInfo>::output_index<OutROut>();

	constexpr static STSChanMapping MappingL{
		.PitchKnob = CoreHelper<STSInfo>::param_index<PitchLKnob>(),
		.SampleKnob = CoreHelper<STSInfo>::param_index<SampleLKnob>(),
		.StartPosKnob = CoreHelper<STSInfo>::param_index<StartPos_LKnob>(),
		.LengthKnob = CoreHelper<STSInfo>::param_index<LengthLKnob>(),
		.PlayButton = CoreHelper<STSInfo>::param_index<PlayLButton>(),
		.BankButton = CoreHelper<STSInfo>::param_index<BankLButton>(),
		.ReverseButton = CoreHelper<STSInfo>::param_index<ReverseLButton>(),
		.PlayTrigIn = CoreHelper<STSInfo>::input_index<PlayTrigLIn>(),
		.VOctIn = CoreHelper<STSInfo>::input_index<_1V_OctLIn>(),
		.ReverseTrigIn = CoreHelper<STSInfo>::input_index<ReverseTrigLIn>(),
		.LengthCvIn = CoreHelper<STSInfo>::input_index<LengthCvLIn>(),
		.StartPosCvIn = CoreHelper<STSInfo>::input_index<StartPosCvLIn>(),
		.SampleCvIn = CoreHelper<STSInfo>::input_index<SampleCvLIn>(),
		.RecIn = CoreHelper<STSInfo>::input_index<LeftRecIn>(),
		.OutL = OutL,
		.OutR = OutR,
		.EndOut = CoreHelper<STSInfo>::output_index<EndOutLOut>(),
		.PlayLight = CoreHelper<STSInfo>::first_light_index<PlayLLight>(),
		.PlayButR = CoreHelper<STSInfo>::first_light_index<PlayLButton>() + 0,
		.PlayButG = CoreHelper<STSInfo>::first_light_index<PlayLButton>() + 1,
		.PlayButB = CoreHelper<STSInfo>::first_light_index<PlayLButton>() + 2,
		.RevButR = CoreHelper<STSInfo>::first_light_index<ReverseLButton>() + 0,
		.RevButG = CoreHelper<STSInfo>::first_light_index<ReverseLButton>() + 1,
		.RevButB = CoreHelper<STSInfo>::first_light_index<ReverseLButton>() + 2,
		.BankButR = CoreHelper<STSInfo>::first_light_index<BankLButton>() + 0,
		.BankButG = CoreHelper<STSInfo>::first_light_index<BankLButton>() + 1,
		.BankButB = CoreHelper<STSInfo>::first_light_index<BankLButton>() + 2,
	};

	constexpr static STSChanMapping MappingR{
		.PitchKnob = CoreHelper<STSInfo>::param_index<PitchRKnob>(),
		.SampleKnob = CoreHelper<STSInfo>::param_index<SampleRKnob>(),
		.StartPosKnob = CoreHelper<STSInfo>::param_index<StartPos_RKnob>(),
		.LengthKnob = CoreHelper<STSInfo>::param_index<LengthRKnob>(),
		.PlayButton = CoreHelper<STSInfo>::param_index<PlayLButton>(),
		.BankButton = CoreHelper<STSInfo>::param_index<BankRButton>(),
		.ReverseButton = CoreHelper<STSInfo>::param_index<ReverseRButton>(),
		.PlayTrigIn = CoreHelper<STSInfo>::input_index<PlayTrigRIn>(),
		.VOctIn = CoreHelper<STSInfo>::input_index<_1V_OctRIn>(),
		.ReverseTrigIn = CoreHelper<STSInfo>::input_index<ReverseTrigRIn>(),
		.LengthCvIn = CoreHelper<STSInfo>::input_index<LengthCvRIn>(),
		.StartPosCvIn = CoreHelper<STSInfo>::input_index<StartPosCvRIn>(),
		.SampleCvIn = CoreHelper<STSInfo>::input_index<SampleCvRIn>(),
		.RecIn = CoreHelper<STSInfo>::input_index<RightRecIn>(),
		.OutL = OutL,
		.OutR = OutR,
		.EndOut = CoreHelper<STSInfo>::output_index<EndOutROut>(),
		.PlayLight = CoreHelper<STSInfo>::first_light_index<PlayRLight>(),
		.PlayButR = CoreHelper<STSInfo>::first_light_index<PlayRButton>() + 0,
		.PlayButG = CoreHelper<STSInfo>::first_light_index<PlayRButton>() + 1,
		.PlayButB = CoreHelper<STSInfo>::first_light_index<PlayRButton>() + 2,
		.RevButR = CoreHelper<STSInfo>::first_light_index<ReverseRButton>() + 0,
		.RevButG = CoreHelper<STSInfo>::first_light_index<ReverseRButton>() + 1,
		.RevButB = CoreHelper<STSInfo>::first_light_index<ReverseRButton>() + 2,
		.BankButR = CoreHelper<STSInfo>::first_light_index<BankRButton>() + 0,
		.BankButG = CoreHelper<STSInfo>::first_light_index<BankRButton>() + 1,
		.BankButB = CoreHelper<STSInfo>::first_light_index<BankRButton>() + 2,
	};

	SamplerChannel chanL{MappingL, sd, banks, settings, cal_storage};
	SamplerChannel chanR{MappingR, sd, banks, settings, cal_storage};
};

} // namespace MetaModule
