#pragma once
#include <span>
#include <cstdint>

// Fills buf with null-terminated string conversion of `value`.
// Returns false if value won't fit.
// Assumes base-10. Prepends a `-` if value is negative
bool int_to_str(int32_t value, const std::span<char> buf);

// Fills buf with null-terminated string conversion of `value`.
// Truncates the most signficant digit(s) of result if it
// won't fit (null-terminator and sign are always preserved).
// Assumes base-10. Prepends a `-` if value is negative
void int_to_str_chop(int32_t value, const std::span<char> buf);

//Returns number of digits in a base-10 value
unsigned num_digits(unsigned value);
