
template<size_t CAPACITY>
bool from_chars(ryml::csubstr buf, StaticString<CAPACITY> *s) {
	size_t sz = std::min(buf.len, CAPACITY);
	size_t i = 0;
	for (; i < sz; i++) {
		if (buf[i])
			s->_data[i] = buf[i];
	}
	s->_data[i] = '\0';
	return i != 0;
}
