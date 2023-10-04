#include "util/static_string.hh"
#include <algorithm>
#include <cstddef>

template<size_t CAPACITY>
bool from_chars(ryml::csubstr buf, StaticString<CAPACITY> *s) {
	size_t sz = std::min(buf.len, CAPACITY);
	size_t i = 0;
	for (; i < sz; i++) {
		s->_data[i] = buf[i];
	}
	s->_data[i] = '\0';
	return true;
}

template<size_t CAPACITY>
size_t to_chars(ryml::substr buf, StaticString<CAPACITY> s) {
	size_t sz = s.length();
	// From docs: "... if the return value
	// is larger than buf.len, ryml will resize the buffer and
	// call this again with a larger buffer of the correct size."
	if (buf.len < sz)
		return sz;

	for (size_t i = 0; i < sz; i++) {
		buf[i] = s[i];
	}
	return sz;
}
