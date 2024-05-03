#pragma once
#include "audio_stream_conf.hh"
#include <cstdint>

#include "../mocks/mocks.hh"
#include "./elements.hh"

namespace LDKit
{

struct Util {

	// in_between()
	// Utility function to determine if address mid is in between addresses beg and end in a circular (ring) buffer.
	constexpr static bool in_between(uint32_t mid, uint32_t beg, uint32_t end, uint8_t reverse) {
		if (beg == end)
			return mid == beg;

		if (beg < end) {
			return ((mid >= beg) && (mid <= end)) != reverse;
		}
		return ((mid >= end) && (mid <= beg)) == reverse;
	}

	//  !rev &&  (end > start): |     [->........]     |   NOT WRAPPING: rev != (end>start)
	//   rev &&  (end > start): |...<-]          [.....|       WRAPPING: rev == (end>start)
	//  !rev && !(end > start): |.....]          [->...|       WRAPPING: rev == (end>start)
	//   rev && !(end > start): |     [........<-]     |   NOT WRAPPING: rev != (end>start)
	// Key:
	//  [-> or <-] === start
	//    [ or ]   === end
	//     .....   === loop
	//     |   |   === memory boundaries

};

static_assert(!Util::in_between(5, 1, 4, 0), "not wrapped, not reverse, mid not between");
static_assert(Util::in_between(3, 1, 4, 0), "not wrapped, not reverse, mid between");
static_assert(Util::in_between(5, 1, 4, 1), "not wrapped, reverse, mid not between");
static_assert(!Util::in_between(3, 1, 4, 1), "not wrapped, reverse, mid between");

static_assert(Util::in_between(5, 4, 1, 0), "wrapped, not reverse, mid not between");
static_assert(!Util::in_between(3, 4, 1, 0), "wrapped, not reverse, mid between");
static_assert(!Util::in_between(5, 4, 1, 1), "wrapped, reverse, mid not between");
static_assert(Util::in_between(3, 4, 1, 1), "wrapped, reverse, mid between");

static_assert(Util::in_between(3, 3, 3, 1), "zero length, reverse, mid equal");
static_assert(Util::in_between(3, 3, 3, 0), "zero length, not reverse, mid equal");
static_assert(!Util::in_between(2, 3, 3, 1), "zero length, reverse, mid not equal");
static_assert(!Util::in_between(2, 3, 3, 0), "zero length, not reverse, mid not equal");
} // namespace LDKit
