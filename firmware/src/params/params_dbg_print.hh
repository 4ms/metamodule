#pragma once
#include "conf/jack_sense_conf.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "pr_dbg.hh"
#include "util/countzip.hh"
#include "util/term_codes.hh"

namespace MetaModule
{

struct ParamDbgPrint {
	ParamsState &params;
	MetaParams &metaparams;

	ParamDbgPrint(ParamsState &params, MetaParams &metaparams)
		: params{params}
		, metaparams{metaparams} {
	}

	uint32_t last_dbg_output_tm = 0;
	float pot_min[12]{9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
	float pot_max[12]{};
	float pot_iir[12]{};
	uint32_t readings = 0;
	static constexpr float iir_coef = 1.f / 1000.f;
	static constexpr float iir_coef_inv = 1.f - iir_coef;

	bool flag_next_page = false;
	bool flag_prev_page = false;

	void output_load(uint32_t now_ticks) {
		if ((now_ticks - last_dbg_output_tm) > 2000) {
			last_dbg_output_tm = now_ticks;
			pr_dbg("Load = %d%%n", metaparams.audio_load);
		}
	}

	void output_debug_info(uint32_t now_ticks) {
		for (auto [i, pot] : enumerate(params.knobs)) {
			if (pot < pot_min[i])
				pot_min[i] = pot;
			if (pot > pot_max[i])
				pot_max[i] = pot;
			pot_iir[i] = pot_iir[i] * iir_coef_inv + pot * iir_coef;
		}

		readings++;

		if ((now_ticks - last_dbg_output_tm) > 2000) {
			pr_dbg("%s", Term::ClearScreen);
			pr_dbg("\r\nnumber of readings: %d\r\n", (int)readings);
			readings = 0;

			for (auto [i, pot] : enumerate(params.knobs)) {
				pr_dbg("Pot %zu: iir=%d min=%d max=%d range=%d\r\n",
					   i,
					   (int)(4096.f * pot_iir[i]),
					   (int)(4096.f * pot_min[i]),
					   (int)(4096.f * pot_max[i]),
					   (int)(4096.f * (pot_max[i] - pot_min[i])));
				pot_iir[i] = pot;
				pot_min[i] = 4096.f;
				pot_max[i] = 0.f;
			}

			auto b = [j = params.jack_senses](uint32_t bit) -> int {
				return (j >> (jacksense_pin_order[bit])) & 1;
			};

			pr_dbg("Outs patched: %d %d %d %d %d %d %d %d\n", b(8), b(9), b(10), b(11), b(12), b(13), b(14), b(15));

			pr_dbg("Button: %d GateIn1: %d [%d] GateIn2: %d [%d] \r\n",
				   metaparams.meta_buttons[0].is_high() ? 1 : 0,
				   params.gate_ins[0].is_high() ? 1 : 0,
				   b(6),
				   params.gate_ins[1].is_high() ? 1 : 0,
				   b(7));

			for (auto [i, ain] : enumerate(metaparams.ins)) {
				pr_dbg("AIN %zu: [%d] iir=%d min=%d max=%d range=%d\r\n",
					   i,
					   b(i),
					   (int)(ain.iir * 32768.f),
					   (int)(ain.min * 32768.f),
					   (int)(ain.max * 32768.f),
					   (int)((ain.max - ain.min) * 32768.f));
				ain.reset_to(ain.iir);
			}

			last_dbg_output_tm = now_ticks;
		}
	}
};

} // namespace MetaModule
