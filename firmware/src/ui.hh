#pragma once
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "params.hh"
#include "patchlist.hh"
#include "static_buffers.hh"
#include "util/analyzed_signal.hh"
#include "util/countzip.hh"

namespace MetaModule
{

class Ui {
private:
	ParamQueue &param_queue;
	PatchList &patch_list;
	UiAudioMailbox &mbox;

	PageManager page_manager;
	Params params;
	MetaParams metaparams;

	static inline LVGLDriver gui{
		MMDisplay::flush_to_screen, MMDisplay::read_input, StaticBuffers::framebuf1, StaticBuffers::framebuf2};

public:
	Ui(PatchPlayer &pp, PatchList &pl, ParamQueue &pc, UiAudioMailbox &uiaudiomailbox)
		: param_queue{pc}
		, patch_list{pl}
		, mbox{uiaudiomailbox}
		, page_manager{patch_list, pp, params, metaparams, uiaudiomailbox} {
	}

	void start() {
		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams, StaticBuffers::framebuf2);
		page_manager.init();

		page_update_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz
				.priority1 = 1,
				.priority2 = 2,
			},
			[&] { page_update_task(); });
		page_update_tm.start();

		ui_event_tm.init(
			{
				.TIMx = TIM16,
				.period_ns = 1000000000 / 600, // =  600Hz
				.priority1 = 3,
				.priority2 = 3,
			},
			[&] { update(); });
		ui_event_tm.start();

		MMDisplay::start();
	}

	void update() {
		Debug::Pin1::high();
		if (MMDisplay::is_ready()) {
			MMDisplay::clear_ready();
			// lv_timer_handler(); //v8
			page_update_tm.stop();
			lv_task_handler();
			if (flag_prev_page) {
				page_manager.prev_page();
				flag_prev_page = false;
			}
			if (flag_next_page) {
				page_manager.next_page();
				flag_next_page = false;
			}
			page_update_tm.start();
		}

		auto msg = mbox.get_message();
		if (!msg.empty()) {
			printf("%s", msg.data());
			mbox.clear_message();
		}
		// output_debug_info();
		Debug::Pin1::low();
	}

	void page_update_task() {
		bool read_ok = param_queue.read_sync(&params, &metaparams);
		if (read_ok) {
			handle_rotary();
			page_manager.update_current_page();
		}
	}

	void handle_rotary() {
		auto rotary_pushed_turned = metaparams.rotary_pushed.use_motion();
		//Queue the call to next/prev_page here because it can be slow, e.g. if the page has lots of images
		if (rotary_pushed_turned < 0)
			flag_prev_page = true;
		if (rotary_pushed_turned > 0)
			flag_next_page = true;
	}

private:
	mdrivlib::Timekeeper page_update_tm;
	mdrivlib::Timekeeper ui_event_tm;

	uint32_t last_dbg_output_tm = 0;
	float pot_min[12]{9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
	float pot_max[12]{};
	float pot_iir[12]{};
	// std::array<AnalyzedSignal<1000>, 12> pots;
	AnalyzedSignal<1000> patchcv;
	uint32_t readings = 0;
	static constexpr float iir_coef = 1.f / 1000.f;
	static constexpr float iir_coef_inv = 1.f - iir_coef;

	bool flag_next_page = false;
	bool flag_prev_page = false;

	void output_debug_info() {
		for (auto [i, pot] : enumerate(params.knobs)) {
			if (pot < pot_min[i])
				pot_min[i] = pot;
			if (pot > pot_max[i])
				pot_max[i] = pot;
			pot_iir[i] = pot_iir[i] * iir_coef_inv + pot * iir_coef;
		}
		patchcv.update(metaparams.patchcv);

		readings++;

		if ((HAL_GetTick() - last_dbg_output_tm) > 500) {
			printf("\r\nnumber of readings: %d\r\n", readings);
			readings = 0;

			for (auto [i, pot] : enumerate(params.knobs)) {
				printf("Pot %d: iir=%d min=%d max=%d range=%d\r\n",
					   i,
					   (int32_t)(4096.f * pot_iir[i]),
					   (int32_t)(4096.f * pot_min[i]),
					   (int32_t)(4096.f * pot_max[i]),
					   (int32_t)(4096.f * (pot_max[i] - pot_min[i])));
				pot_iir[i] = pot;
				pot_min[i] = 4096.f;
				pot_max[i] = 0.f;
			}

			printf("PatchCV: iir=%d min=%d max=%d range=%d\r\n",
				   (int32_t)(patchcv.iir * 4096.f),
				   (int32_t)(4096.f * patchcv.min),
				   (int32_t)(4096.f * patchcv.max),
				   (int32_t)(4096.f * (patchcv.max - patchcv.min)));
			patchcv.reset_to(metaparams.patchcv);

			printf("Button: %d GateIn1: %d GateIn2: %d\r\n",
				   metaparams.meta_buttons[0].is_high() ? 1 : 0,
				   params.gate_ins[0].is_high() ? 1 : 0,
				   params.gate_ins[1].is_high() ? 1 : 0);

			printf("Jack senses: %08x\r\n", params.jack_senses);

			for (auto [i, ain] : enumerate(metaparams.ins)) {
				printf("AIN %d: iir=%d min=%d max=%d range=%d\r\n",
					   i,
					   (int32_t)(ain.iir * 32768.f),
					   (int32_t)(ain.min * 32768.f),
					   (int32_t)(ain.max * 32768.f),
					   (int32_t)((ain.max - ain.min) * 32768.f));
				ain.reset_to(ain.iir);
			}

			last_dbg_output_tm = HAL_GetTick();
		}
	}
};
} // namespace MetaModule
