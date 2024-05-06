#include <algorithm>
#include <common.hpp>
#include <cstdarg>
#include <string>
#include <vector>

namespace rack::string
{

std::string fV(const char *format, va_list args) {
	// va_lists cannot be reused but we need it twice, so clone args.
	va_list args2;
	va_copy(args2, args);
	DEFER({ va_end(args2); });
	// Compute size of required buffer
	int size = vsnprintf(nullptr, 0, format, args);
	if (size < 0)
		return "";
	// Create buffer
	std::string s;
	s.resize(size);
	vsnprintf(&s[0], size + 1, format, args2);
	return s;
}

std::string f(const char *format, ...) {
	va_list args;
	va_start(args, format);
	std::string s = fV(format, args);
	va_end(args);
	return s;
}

std::string lowercase(const std::string &s) {
	std::string r = s;
	std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return std::tolower(c); });
	return r;
}

std::string uppercase(const std::string &s) {
	std::string r = s;
	std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return std::toupper(c); });
	return r;
}

std::string trim(const std::string &s) {
	const std::string whitespace = " \n\r\t";
	size_t first = s.find_first_not_of(whitespace);
	if (first == std::string::npos)
		return "";
	size_t last = s.find_last_not_of(whitespace);
	if (last == std::string::npos)
		return "";
	return s.substr(first, last - first + 1);
}

std::string ellipsize(const std::string &s, size_t len) {
	if (s.size() <= len)
		return s;
	else
		return s.substr(0, len - 3) + "...";
}

std::string ellipsizePrefix(const std::string &s, size_t len) {
	if (s.size() <= len)
		return s;
	else
		return "..." + s.substr(s.size() - (len - 3));
}

bool startsWith(const std::string &str, const std::string &prefix) {
	if (str.size() < prefix.size())
		return false;
	return std::equal(prefix.begin(), prefix.end(), str.begin());
}

bool endsWith(const std::string &str, const std::string &suffix) {
	if (str.size() < suffix.size())
		return false;
	return std::equal(suffix.begin(), suffix.end(), str.end() - suffix.size());
}

std::string toBase64(const uint8_t *data, size_t dataLen) {
	static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	size_t numBlocks = (dataLen + 2) / 3;
	size_t strLen = numBlocks * 4;
	std::string str;
	str.reserve(strLen);

	for (size_t b = 0; b < numBlocks; b++) {
		// Encode block
		uint32_t block = 0;
		int i = 0;
		for (i = 0; i < 3 && 3 * b + i < dataLen; i++) {
			block |= uint32_t(data[3 * b + i]) << (8 * (2 - i));
		}

		// Decode block
		str += alphabet[(block >> 18) & 0x3f];
		str += alphabet[(block >> 12) & 0x3f];
		str += (i > 1) ? alphabet[(block >> 6) & 0x3f] : '=';
		str += (i > 2) ? alphabet[(block >> 0) & 0x3f] : '=';
	}
	return str;
}

std::string toBase64(const std::vector<uint8_t> &data) {
	return toBase64(data.data(), data.size());
}

std::vector<uint8_t> fromBase64(const std::string &str) {
	std::vector<uint8_t> data;
	uint32_t block = 0;
	int i = 0;
	int padding = 0;

	for (char c : str) {
		uint8_t d = 0;

		if ('A' <= c && c <= 'Z') {
			d = c - 'A';
		} else if ('a' <= c && c <= 'z') {
			d = c - 'a' + 26;
		} else if ('0' <= c && c <= '9') {
			d = c - '0' + 52;
		} else if (c == '+') {
			d = 62;
		} else if (c == '/') {
			d = 63;
		} else if (c == '=') {
			padding++;
		} else {
			// Ignore whitespace and non-base64 characters
			continue;
		}

		block |= uint32_t(d) << (6 * (3 - i));
		i++;

		if (i >= 4) {
			// Decode block
			data.push_back((block >> (8 * (2 - 0))) & 0xff);
			if (padding < 2)
				data.push_back((block >> (8 * (2 - 1))) & 0xff);
			if (padding < 1)
				data.push_back((block >> (8 * (2 - 2))) & 0xff);
			// Reset block
			block = 0;
			i = 0;
			padding = 0;
		}
	}
	return data;
}

} // namespace rack::string
