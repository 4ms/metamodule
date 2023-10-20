#pragma once
#include <cstdint>

static inline constexpr float InputLowRangeVolts = -10.27f;
static inline constexpr int32_t InputLowRangeMillivolts = -10270;
static inline constexpr float InputHighRangeVolts = 10.31f;
static inline constexpr int32_t InputHighRangeMillivolts = 10310;
static inline constexpr float InputRangeVolts = InputHighRangeVolts - InputLowRangeVolts;
static inline constexpr float InputRangeCenterVolts = (InputHighRangeVolts + InputLowRangeVolts) / 2.f;

#if defined(METAMODULE_PCB_VERSION) && (METAMODULE_PCB_VERSION == 12)
static inline constexpr float OutputMaxVolts = 10.4f;
#else
static inline constexpr float OutputMaxVolts = 8.59f;
#endif
