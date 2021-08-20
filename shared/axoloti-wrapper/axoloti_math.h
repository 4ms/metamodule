/**
 * Copyright (C) 2013, 2014 Johannes Taelman
 * Modified in 2021 by Dan Green, making it not depend on ARM or any architecture
 *
 * This file is part of Axoloti.
 *
 * Axoloti is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Axoloti is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Axoloti. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <cmath>
#include <cstdint>

//Todo: these might not be valid defs. Also add some for A7 etc
#if defined(__ARM__) && defined(__CORTEX_M4__)
	#include "arch_arm.h"
#else
	#include "arch_generic.h"
#endif

#define SINETSIZE 1024
extern int16_t sinet[SINETSIZE + 1];
#define SINE2TSIZE 4096
extern int32_t sine2t[SINE2TSIZE + 1];
#define WINDOWSIZE 1024
extern int16_t windowt[WINDOWSIZE + 1];
#define PITCHTSIZE 257
extern uint32_t pitcht[PITCHTSIZE];
#define EXPTSIZE 256
extern uint16_t expt[EXPTSIZE];
#define LOGTSIZE 256
#define LOGTSIZEN 8
extern uint16_t logt[LOGTSIZE];

//Q27 format: -16..+16
struct frac32_s {
	int32_t val;

	void operator=(int32_t v)
	{
		val = v;
	}
	operator int32_t()
	{
		return val;
	}

	//Converts -1..+1 to -1<<27..1<<27
	void set_from_float(float f)
	{
		if (f > 1.f)
			val = 1UL << 27UL;
		else if (f < -1.f)
			f = -(1L << 27L);
		else
			val = f * (1UL << 27UL);
	}

	//Converts 0..+1 to -1<<27..1<<27
	void set_from_positive_float(float f)
	{
		set_from_float(f * 2.f - 1.f);
	}

	//converts -1<<27..1<<27 to -1..+1
	float to_float() const
	{
		if (val >= 1L << 27L)
			return 1.f;
		if (val <= -(1L << 27L))
			return -1.f;
		return (float)val / (float)(1UL << 27UL);
	}
};

struct frac32_u {
	int32_t val;

	void operator=(int32_t v)
	{
		val = v;
	}
	operator int32_t()
	{
		return val;
	}

	//Converts 0..+1 to 0..1<<27
	void set_from_float(float f)
	{
		if (f > 1.f)
			val = 1UL << 27UL;
		else if (f < 0.f)
			val = 0;
		else
			val = f * (1UL << 27UL);
	}

	//Converts 0..+1 to -1<<27..1<<27
	void set_from_positive_float(float f)
	{
		set_from_float(f);
	}

	//converts -1<<27..1<<27 to -1..+1
	float to_float() const
	{
		if (val >= 1L << 27L)
			return 1.f;
		if (val <= 0)
			return 0.f;
		return (float)val / (float)(1UL << 27UL);
	}
};

typedef union {
	int32_t i;
	float f;
	struct {
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	} parts;
} Float_t;

#define PI_F 3.1415927f
#define SAMPLERATE 48000
#define BUFSIZE 16
#define BUFSIZE_POW 4
typedef int32_t int32buffer[BUFSIZE];

void axoloti_math_init(void);

static inline uint32_t mtof48k_q31(int32_t pitch)
{
	int32_t p = __SSAT(pitch, 28);
	uint32_t pi = p >> 21;
	int32_t y1 = pitcht[128 + pi];
	int32_t y2 = pitcht[128 + 1 + pi];
	int32_t pf = (p & 0x1fffff) << 10;
	int32_t pfc = INT32_MAX - pf;
	uint32_t r;
	r = ___SMMUL(y1, pfc);
	r = ___SMMLA(y2, pf, r);
	uint32_t frequency = r << 1;
	return frequency;
}

static inline uint32_t mtof48k_ext_q31(int32_t pitch)
{
	int32_t p = __SSAT(pitch, 29);
	uint32_t pi = p >> 21;
	int32_t y1 = pitcht[128 + pi];
	int32_t y2 = pitcht[128 + 1 + pi];
	int32_t pf = (p & 0x1fffff) << 10;
	int32_t pfc = INT32_MAX - pf;
	uint32_t r;
	r = ___SMMUL(y1, pfc);
	r = ___SMMLA(y2, pf, r);
	uint32_t frequency = r << 1;
	return frequency;
}

static inline int32_t sin_q31(int32_t phase)
{
	uint32_t p = (uint32_t)(phase);
	uint32_t pi = p >> 20;
	int32_t y1 = sine2t[pi];
	int32_t y2 = sine2t[1 + pi];
	int32_t pf = (p & 0xfffff) << 11;
	int32_t pfc = INT32_MAX - pf;
	int32_t rr;
	rr = ___SMMUL(y1, pfc);
	rr = ___SMMLA(y2, pf, rr);
	return rr << 1;
}

static inline uint32_t hann_q31(int32_t phase)
{
	uint32_t p = phase;
	uint32_t pi = p >> 22;
	int32_t y1 = windowt[pi];
	int32_t y2 = windowt[1 + pi];
	int32_t pf = (p & 0x3fffff) << 9;
	int32_t pfc = INT32_MAX - pf;
	int32_t rr;
	rr = ___SMMUL(y1 << 16, pfc);
	rr = ___SMMLA(y2 << 16, pf, rr);
	return rr << 1;
}

static inline int32_t ConvertIntToFrac(int i)
{
	return (i << 21);
}

static inline int32_t ConvertFracToInt(int i)
{
	return (i >> 21);
}

static inline int32_t ConvertFloatToFrac(float f)
{
	return (int32_t)(f * (1 << 21));
}

#ifdef RAND_MAX
	#undef RAND_MAX
#endif

#define RAND_MAX INT32_MAX
static inline int ax_rand(void)
{
	// standard C rand()
	return ((uint32_t)rand_s32()) >> 1;
}

//Oh no you don't....
//#define rand ax_rand

uint32_t FastLog(uint32_t f);

// deprecated macro's
#define MTOF(pitch, frequency) frequency = mtof48k_q31(pitch);

#define MTOFEXTENDED(pitch, frequency) frequency = mtof48k_ext_q31(pitch);

#define SINE2TINTERP(phase, output) output = sin_q31(phase);

#define HANNING2TINTERP(phase, output) output = hann_q31(phase);

// deprecated functions
static inline uint32_t GenerateRandomNumber(void)
{
	return rand_s32();
}
