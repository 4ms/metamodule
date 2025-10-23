#pragma once
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "pr_dbg.hh"
#include "util/analyzed_signal.hh"
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
	float pot_min[PanelDef::NumPot]{9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999};
	float pot_max[PanelDef::NumPot]{};
	float pot_iir[PanelDef::NumPot]{};
	uint32_t readings = 0;
	static constexpr float iir_coef = 1.f / 1000.f;
	static constexpr float iir_coef_inv = 1.f - iir_coef;

	std::array<AnalyzedSignal<1000>, PanelDef::NumAudioIn> ins;

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

		for (auto [source, ain] : zip(params.smoothed_ins, ins)) {
			ain.update(source.val());
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

			pr_dbg("GateIn1: %d. GateIn2: %d \r\n",
				   params.gate_ins[0].is_high() ? 1 : 0,
				   params.gate_ins[1].is_high() ? 1 : 0);

			for (auto [i, ain] : enumerate(ins)) {
				pr_dbg("ADC %zu: iir=%f min=%f max=%f range=%f\r\n",
					   i,
					   ain.iir,
					   ain.min,
					   ain.max,
					   std::fabs(ain.max - ain.min));
				ain.reset_to(ain.iir);
			}

			last_dbg_output_tm = now_ticks;
		}
	}
};

} // namespace MetaModule
