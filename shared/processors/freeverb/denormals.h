#pragma once

#define undenormalise(sample)                                                                                          \
	if (((*(unsigned int *)&sample) & 0x7f800000) == 0)                                                                \
	sample = 0.0f