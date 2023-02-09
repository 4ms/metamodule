#pragma once
#include "conf/jack_sense_conf.hh" // for debug out
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "lvgl_driver.hh"
#include "pages/page_manager.hh"
#include "pages/styles.hh"
#include "param_cache.hh"
#include "params.hh"
#include "patch_loader.hh"
#include "patch_mod_queue.hh"
#include "patchlist.hh"
#include "static_buffers.hh"
#include "util/analyzed_signal.hh"
#include "util/countzip.hh"

namespace MetaModule
{
// TODO: remove patch_list ctor parameter, and instead get it from patch_loader.get_patch_list();
class Ui {
private:
	ParamCache &param_cache;
	PatchStorage &patch_storage;
	PatchLoader &patch_loader;

	MessageQueue msg_queue;
	PageManager page_manager;
	Params params;
	MetaParams metaparams;

	static inline LVGLDriver gui{
		MMDisplay::flush_to_screen, MMDisplay::read_input, StaticBuffers::framebuf1, StaticBuffers::framebuf2};

public:
	Ui(PatchLoader &patch_loader, PatchStorage &patch_storage, ParamCache &pc, PatchModQueue &patch_mod_queue)
		: param_cache{pc}
		, patch_storage{patch_storage}
		, patch_loader{patch_loader}
		, msg_queue{1024}
		, page_manager{patch_storage, patch_loader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void start() {
		params.clear();
		metaparams.clear();

		MMDisplay::init(metaparams, StaticBuffers::framebuf2);
		Gui::init_lvgl_styles();
		page_manager.init();

		page_update_tm.init(
			{
				.TIMx = TIM17,
				.period_ns = 1000000000 / 60, // =  60Hz = 16ms
				.priority1 = 2,
				.priority2 = 0,
			},
			[&] { page_update_task(); });
		page_update_tm.start();

		ui_event_tm.init(
			{
				.TIMx = TIM16,
				.period_ns = 1000000000 / 600, // =  600Hz = 1.6ms
				.priority1 = 3,
				.priority2 = 3,
			},
			[&] { lvgl_update_task(); });
		ui_event_tm.start();

		MMDisplay::start();
	}

private:
	void lvgl_update_task() {
		// Debug::Pin1::high();
		page_update_tm.stop();
		lv_timer_handler();
		page_update_tm.start();

		auto msg = msg_queue.get_message();
		if (!msg.empty()) {
			printf_("%s", msg.data());
			msg_queue.clear_message();
		}
		// output_debug_info();
		// Debug::Pin1::low();
	}

	void page_update_task() { //60Hz
		//This returns false when audio stops
		bool read_ok = param_cache.read_sync(&params, &metaparams);
		// if (read_ok) {
		// 	Debug::Pin1::low();
		// } else {
		// 	Debug::Pin1::high();
		// }
		page_manager.update_current_page();
		patch_loader.handle_sync_patch_loading();
	}

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
			printf_("\r\nnumber of readings: %d\r\n", readings);
			readings = 0;

			for (auto [i, pot] : enumerate(params.knobs)) {
				printf_("Pot %d: iir=%d min=%d max=%d range=%d\r\n",
						i,
						(int32_t)(4096.f * pot_iir[i]),
						(int32_t)(4096.f * pot_min[i]),
						(int32_t)(4096.f * pot_max[i]),
						(int32_t)(4096.f * (pot_max[i] - pot_min[i])));
				pot_iir[i] = pot;
				pot_min[i] = 4096.f;
				pot_max[i] = 0.f;
			}

			// printf_("PatchCV: iir=%d min=%d max=%d range=%d\r\n",
			// 		(int32_t)(patchcv.iir * 4096.f),
			// 		(int32_t)(4096.f * patchcv.min),
			// 		(int32_t)(4096.f * patchcv.max),
			// 		(int32_t)(4096.f * (patchcv.max - patchcv.min)));
			// patchcv.reset_to(metaparams.patchcv);

			auto b = [j = params.jack_senses](uint32_t bit) -> uint32_t {
				return (j >> (jacksense_pin_order[bit])) & 1;
			};

			printf_("Outs patched: %d %d %d %d %d %d %d %d\n", b(8), b(9), b(10), b(11), b(12), b(13), b(14), b(15));

			printf_("Button: %d GateIn1: %d [%d] GateIn2: %d [%d] \r\n",
					metaparams.meta_buttons[0].is_high() ? 1 : 0,
					params.gate_ins[0].is_high() ? 1 : 0,
					b(6),
					params.gate_ins[1].is_high() ? 1 : 0,
					b(7));

			// printf_("Audio INs: %d %d %d %d %d %d\n", b(0), b(1), b(2), b(3), b(4), b(5));
			// printf_("Gate INs: %d %d\n", b(6), b(7));

			for (auto [i, ain] : enumerate(metaparams.ins)) {
				printf_("AIN %d: [%d] iir=%d min=%d max=%d range=%d\r\n",
						i,
						b(i),
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
