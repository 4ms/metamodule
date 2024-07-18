#pragma once
#include "audio.hh"
#include "util/countzip.hh"
#include "util/zip.hh"

namespace MetaModule
{
struct AudioTestSignal {
	static void passthrough(std::span<AudioInFrame> in, std::span<AudioOutFrame> out) {

		// for (auto [i, o] : zip(in, out)) {
		for (auto idx = 0u; auto const &i : in) {
			auto &o = out[idx++];
			o.chan[0] = i.chan[0];
			o.chan[1] = i.chan[1];
			o.chan[2] = i.chan[2];
			o.chan[3] = i.chan[3];
			o.chan[4] = i.chan[4];
			o.chan[5] = i.chan[5];
			o.chan[6] = 0x00100000;
			o.chan[7] = 0x00400000;
		}
	}

	static void sines_out(AudioInBuffer &in, AudioOutBuffer &out) {
		static PhaseAccum<48000> phase0{80};
		static PhaseAccum<48000> phase1{200};
		static PhaseAccum<48000> phase2{250};
		static PhaseAccum<48000> phase3{700};
		static PhaseAccum<48000> phase4{900};
		static PhaseAccum<48000> phase5{2200};
		static PhaseAccum<48000> phase6{1000};
		static PhaseAccum<48000> phase7{1000};

		//This assumes values are right aligned (max 0x00FFFFFF)
		//and that unused bits in a sample <= log2(block size)
		int32_t refsum = 0;
		for (auto inframe : in)
			refsum += inframe.chan[0];
		float refavg = AudioInFrame::scaleInput(refsum >> MathTools::Log2<AudioConf::MaxBlockSize>::val);

		constexpr float refref = 0x004A3000UL / AudioInFrame::kOutScaling;
		float temp_adj = refref / refavg;

		int32_t pitchsum = 0;
		for (auto inframe : in)
			pitchsum += inframe.chan[5];
		float pitchavg = AudioInFrame::scaleInput(pitchsum >> MathTools::Log2<AudioConf::MaxBlockSize>::val);
		float adjpitch = pitchavg * temp_adj;

		//Adjusted
		float freq_mult6 = exp5Table.interp(MathTools::constrain(adjpitch / 2.f + 0.5f, 0.f, 1.0f)); //1..1024
		phase6.set_frequency(20 * freq_mult6);

		//Unadjusted
		float freq_mult7 = exp5Table.interp(MathTools::constrain(pitchavg / 2.f + 0.5f, 0.f, 1.0f)); //1..1024
		phase7.set_frequency(20 * freq_mult7);

		for (auto &o : out) {
			o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
			o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));
			o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
			o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
			o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase4.process_float()));
			o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase5.process_float()));
			o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase6.process_float()));
			o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase7.process_float()));
		}

		// Temp stability:
		// ~1V/oct
		// using exp10 table
		//
		// using adjpitch = pitchavg * (refref/refavg);
		// Blowing on PCM chip --> 8.1kHz output deviates +70 and -70Hz.
		// 1 semitone = 481Hz, so +/-70Hz = span 140Hz = +/-15cents = span 30cents
		//
		// using pitchavg: +65/-20Hz = span 85Hz = span 17cents
		//
		// using refavg/refref (inverted): deviates 260Hz (obviously, math is bad)
	}

	static void dual_passthrough(AudioInBuffer &inA, AudioOutBuffer &outA, AudioInBuffer &inB, AudioOutBuffer &outB) {

		static PhaseAccum<48000> phase0{80};
		static PhaseAccum<48000> phase1{200};
		static PhaseAccum<48000> phase2{250};
		static PhaseAccum<48000> phase3{700};
		for (auto [ina, inb, outa, outb] : zip(inA, inB, outA, outB)) {
			outa.chan[0] = ina.chan[0];
			outa.chan[1] = ina.chan[1];
			outa.chan[2] = ina.chan[2];
			outa.chan[3] = ina.chan[3];
			outa.chan[4] = ina.chan[4];
			outa.chan[5] = ina.chan[5];
			outa.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
			outa.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));

			outb.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
			outb.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
			outb.chan[2] = inb.chan[0];
			outb.chan[3] = inb.chan[1];
			outb.chan[4] = inb.chan[2];
			outb.chan[5] = inb.chan[3];
			outb.chan[6] = inb.chan[4];
			outb.chan[7] = inb.chan[5];
			// a.clock_out = 0;
		}
	}

	static void dual_sines_out(AudioOutBuffer &outA, AudioOutBuffer &outB) {
		static PhaseAccum<48000> phase0{80};
		static PhaseAccum<48000> phase1{200};
		static PhaseAccum<48000> phase2{250};
		static PhaseAccum<48000> phase3{700};
		static PhaseAccum<48000> phase4{900};
		static PhaseAccum<48000> phase5{2200};
		static PhaseAccum<48000> phase6{6000};
		static PhaseAccum<48000> phase7{12000};

		static PhaseAccum<48000> phase8{60};
		static PhaseAccum<48000> phase9{100};
		static PhaseAccum<48000> phase10{175};
		static PhaseAccum<48000> phase11{300};
		static PhaseAccum<48000> phase12{375};
		static PhaseAccum<48000> phase13{800};
		static PhaseAccum<48000> phase14{4000};
		static PhaseAccum<48000> phase15{8000};

		for (auto &o : outA) {
			o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase0.process_float()));
			o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase1.process_float()));
			o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase2.process_float()));
			o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase3.process_float()));
			o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase4.process_float()));
			o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase5.process_float()));
			o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase6.process_float()));
			o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase7.process_float()));
		}
		for (auto &o : outB) {
			o.chan[0] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase8.process_float()));
			o.chan[1] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase9.process_float()));
			o.chan[2] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase10.process_float()));
			o.chan[3] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase11.process_float()));
			o.chan[4] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase12.process_float()));
			o.chan[5] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase13.process_float()));
			o.chan[6] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase14.process_float()));
			o.chan[7] = AudioOutFrame::scaleOutput(sinTable.interp_wrap(phase15.process_float()));
		}
	}
};
} // namespace MetaModule
