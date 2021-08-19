#pragma once
#include "arm_math.h"
#include <cstdint>

__attribute__((always_inline)) __STATIC_INLINE int32_t ___SMMUL(int32_t op1,
                                                                int32_t op2) {
  int32_t result;

  __ASM volatile("smmul %0, %1, %2" : "=r"(result) : "r"(op1), "r"(op2));
  return (result);
}

__attribute__((always_inline)) __STATIC_INLINE int32_t ___SMMLA(int32_t op1,
                                                                int32_t op2,
                                                                int32_t op3) {
  int32_t result;

  __ASM volatile("smmla %0, %1, %2, %3"
                 : "=r"(result)
                 : "r"(op1), "r"(op2), "r"(op3));
  return (result);
}

__attribute__((always_inline)) __STATIC_INLINE int32_t ___SMMLS(int32_t op1,
                                                                int32_t op2,
                                                                int32_t op3) {
  int32_t result;

  __ASM volatile("smmls %0, %1, %2, %3"
                 : "=r"(result)
                 : "r"(op1), "r"(op2), "r"(op3));
  return (result);
}

__attribute__((always_inline)) __STATIC_INLINE float _VSQRTF(float op1) {
  float result;
  __ASM volatile("vsqrt.f32 %0, %1" : "=w"(result) : "w"(op1));
  return (result);
}

__attribute__((always_inline)) __STATIC_INLINE float q27_to_float(int32_t op1) {
  float fop1 = *(float *)(&op1);
  __ASM volatile("VCVT.F32.S32 %0, %0, 27" : "+w"(fop1));
  return (fop1);
}

__attribute__((always_inline)) __STATIC_INLINE int32_t
float_to_q27(float fop1) {
  __ASM volatile("VCVT.S32.F32 %0, %0, 27" : "+w"(fop1));
  int32_t r = *(int32_t *)(&fop1);
  return (r);
}

__attribute__((always_inline)) __STATIC_INLINE int32_t rand_s32(void) {
  // This function differs from the standard C rand() definition, standard C
  // rand() only returns positive numbers, while rand_s32() returns the full
  // signed 32 bit range.
  // The hardware random generator can't provide new data as quick as desireable
  // but rather than waiting for a new true random number,
  // we multiply/add the seed with the latest hardware-generated number.
  static uint32_t randSeed = 22222;
  return randSeed = (randSeed * 196314165) + RNG->DR;
}
