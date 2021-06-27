// #include "util/math.hh"
#include <arm_neon.h>

class ParallelBPIIR {
	float32x4_t __attribute__((aligned(16))) fSlow19202122;
	// float32x4_t __attribute__((aligned(16))) fRec0567_0;
	float32x4_t __attribute__((aligned(16))) fRec0567_1;
	float32x4_t __attribute__((aligned(16))) fRec0567_2;
	float32x4_t __attribute__((aligned(16))) fConst691215;
	float32x4_t __attribute__((aligned(16))) outmixWeights;

public:
	// float[4]: initOutmixWeights (a0?)
	// float[4]: initSlow = control-dependant values (a1?)
	// float[4]: initConst = samplerate-dependant values (a2?)
	ParallelBPIIR(float slows[4], float consts[4], float par_weights[4])
	{
		fRec0567_1 = vdupq_n_f32(0.f);
		fRec0567_2 = vdupq_n_f32(0.f);
		fSlow19202122 = vld1q_f32(slows);
		fConst691215 = vld1q_f32(consts);
		outmixWeights = vld1q_f32(par_weights);
	}

	void recalc_slows(float slows[4])
	{
		fSlow19202122 = vld1q_f32(slows);
	}

	float calc_4iir(float in)
	{
		// fRec0[0] = (in - ((fSlow19 * fRec0[1]) + (fConst6 * fRec0[2])));
		// fRec5[0] = (in - ((fSlow20 * fRec5[1]) + (fConst9 * fRec5[2])));
		// fRec6[0] = (in - ((fSlow21 * fRec6[1]) + (fConst12 * fRec6[2])));
		// fRec7[0] = (in - ((fSlow22 * fRec7[1]) + (fConst15 * fRec7[2])));

		// Todo: can get rid of fRec0567_0 member and rename tmp0 to it
		float32x4_t fRec0567_0;
		fRec0567_0 = vmulq_f32(fSlow19202122, fRec0567_1);
		fRec0567_0 = vmlaq_f32(fRec0567_0, fConst691215, fRec0567_2);

		float32x4_t in_v = vdupq_n_f32(in);
		fRec0567_0 = vsubq_f32(in_v, fRec0567_0);

		// signalOut = 0.f;
		// signalOut += 1.0f * (fRec0[0] - fRec0[2]);
		// signalOut += 0.25f * (fRec5[0] - fRec5[2]);
		// signalOut += 0.111111112f * (fRec6[0] - fRec6[2]);
		// signalOut += 0.0625f * (fRec7[0] - fRec7[2]);

		float32x4_t diff0567_02 = vsubq_f32(fRec0567_0, fRec0567_2);
		float32x4_t outvec = vmulq_f32(diff0567_02, outmixWeights);
		float32x2_t sum_tmp1 = vpadd_f32(vget_low_f32(outvec), vget_high_f32(outvec));

		// We need to do this, but it compiles to a no-op:
		// fRec0567_2 = fRec0567_1;
		// fRec0567_1 = fRec0567_0;
		// There is no vmovq_f32(), so we need another solution.
		// This works, at the expense of a pipeline delay
		fRec0567_2 = vmaxq_f32(fRec0567_1, fRec0567_1);
		fRec0567_1 = vmaxq_f32(fRec0567_0, fRec0567_0);

		return vget_lane_f32(sum_tmp1, 0) + vget_lane_f32(sum_tmp1, 1);
	}
};

extern "C" void __exit() {}
