#pragma once

static inline constexpr float InputLowRangeVolts = -7.87f;
static inline constexpr float InputHighRangeVolts = 7.87f;

static inline constexpr float OutputLowRangeVolts = -7.91367f;
static inline constexpr float OutputHighRangeVolts = 7.91367f;

//mp1 med:
//with 330's removed: biased up ~2.4V
//-8.1V ==> 0x00800000
//2.39-2.40V => 0x00000000
//10.1V => 0x005E0000
//
//imagine subtracting 2.4V:
//-10.5V => -1
//0V => 0
//12.5V => +1
//
//range is still too large, and not centered on 0
// if we subtracted 3.4V:
// -11.5V => -1
// -1V => 0
// 11.5V => +1
// Why not linear?
