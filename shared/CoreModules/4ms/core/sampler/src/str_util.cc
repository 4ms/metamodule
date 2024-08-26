/*
 * str_util.c - string utilities
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */

#include "str_util.h"

uint32_t str_len(const char *str) {
	uint32_t i = 0;

	while (*str != 0) {
		str++;
		i++;
		if (i == 255)
			return 0xFFFFFFFF;
	}
	return i;
}

// removes trailing slash if it exists
// returns 1 if slash existed, 0 if not
uint8_t trim_slash(char *string) {
	uint8_t len;

	len = str_len(string);

	if (string[len - 1] == '/') {
		string[len - 1] = 0;
		return 1; // trimmed
	} else
		return 0; // not trimmed
}

// adds trailing slash if it doesn't already exist
// returns 1 if slash was added, 0 if it already existed
uint8_t add_slash(char *string) {
	uint8_t len;

	len = str_len(string);

	if (string[len - 1] == '/')
		return 0; // not added
	else {
		string[len] = '/';
		string[len + 1] = '\0';
		return 1; // added
	}
}

// str_split()
//
// Returns 0 if split_char is not found:
//    -before_split will be the entire string
//    -after_split will be a null string
// Returns the position+1 of the split_char if it is found
//    -Copies everything found before and including split_char into before_split
//    -Copies everything found after split_char (excluded) into after_split
// Example:
// str_split("abcdX1234", 'X',...):
//    returns 5
//    before_split <== abcdX
//    after_split <== 1234
//
// Example:
// str_split("path/to/file.wav", '/', ...):
// returns 5
// before_split <== path/
// after_split <== to/file.wav
//
uint8_t str_split(const char *string, char split_char, char *before_split, char *after_split) {
	const char *cp;
	uint8_t pos;
	str_cpy(before_split, string);

	pos = 0;
	for (cp = string; *cp != 0; cp++) {
		if (*cp == split_char)
			break;
		pos++;
	}
	if (*cp != split_char) {
		after_split[0] = 0;
		return 0; // split_char not found
	} else {
		before_split[pos + 1] = 0;
		str_cpy(after_split, &(string[pos + 1]));
		return (pos + 1);
	}
}

// Returns position+1 of split_char in string
// Returns 0 if split_char is not found in string
// Copies everything found before and including split_char into "before_split"
// str_rstr("MyPath/file.wav", '/', before_split) --->> returns 7, before_split is "MyPath/"
// str_rstr("filename.wav", '/', before_split) -->>> returns 0, before_split is "filename.wav"
// str_rstr("/root.wav", '/', before_split)  -->> returns 1, before_split is "/"
uint8_t str_rstr(const char *string, char split_char, char *before_split) {

	const char *cp;
	const char *rp;
	rp = 0;
	str_cpy(before_split, string);

	for (cp = string; *cp != 0; cp++) {
		if (*cp == split_char)
			rp = cp + 1;
	}
	if (rp == 0)
		return 0;
	else {
		before_split[str_len(before_split) - str_len(rp)] = 0;
		return (rp - string);
	}
}

// Returns the head of a string up until the first 'find' char
// Copies the tail following the 'find' char into string
//  str_tok(Path/To/A/File,'/') -->> returns Path, and string becomes "To/A/File"
void str_tok(char *in_string, char find, char *tokk) {
	char *cp;
	uint8_t flag = 0;

	if (in_string[0] != '\0') {
		str_cpy(tokk, in_string);

		for (cp = in_string; *cp != 0; cp++) {
			if (*cp == find) {
				flag = 1;
				break;
			}
		}

		if (flag) {
			tokk[str_len(in_string) - str_len(cp)] = 0;
			str_cpy(in_string, cp + 1);
		} else {
			in_string[0] = '\0';
		}
	} else {
		tokk[0] = '\0';
	}
}

// Returns a (positive) integer from a string
uint32_t str_xt_int(const char *string) {

	const char *cp;
	uint32_t n = UINT32_MAX; // max value of uin32_t
	uint8_t found_number = 0;

	for (cp = string; *cp != 0; cp++) {
		if ((*cp >= '0') && (*cp <= '9')) {
			if (!found_number) {
				n = 0;
				found_number = 1;
			}
			n = n * 10 + *cp - '0';
		} else {
			if (found_number)
				break;
		}
	}
	return (n);
}

// Copy string dest <= src
// REmoved: limit to 255 characters, which reduces harm from bad addresses
//
void str_cpy(char *dest, const char *src) {
	// uint32_t i = 0;

	while (*src != 0 /* && i < 255*/) {
		*dest++ = *src++;
		// i++;
	}

	*dest = 0;
}

// Concatenate string dest <= srca + srcb
void str_cat(char *dest, const char *srca, const char *srcb) {
	while (*srca != 0)
		*dest++ = *srca++;
	while (*srcb != 0)
		*dest++ = *srcb++;
	*dest = 0;
}

// Converts lower case characters to uppercase
// returns everything else untouched
char upper(char a) {
	if (a >= 'a' && a <= 'z')
		return (a - 'a' + 'A');
	else
		return (a);
}

// Converts upper case characters to lowercase
// returns everything else untouched
char lower(char a) {
	if (a >= 'A' && a <= 'Z')
		return (a - 'A' + 'a');
	else
		return (a);
}

void str_to_upper(const char *str_in, char *str_up) {
	while (*str_in != 0) {
		*str_up++ = upper(*str_in++);
	}
	*str_up++ = 0;
}

void str_to_lower(const char *str_in, char *str_lo) {
	while (*str_in != 0) {
		*str_lo++ = lower(*str_in++);
	}
	*str_lo++ = 0;
}

// Compare strings a and b
// Return 1 if the same, 0 if not
// Case insensitive
uint8_t str_cmp_nocase(const char *a, const char *b) {
	while (*a != 0)
		if (upper(*b++) != upper(*a++))
			return 0;

	if (*a != *b)
		return 0; // strings must be the same length

	return 1;
}

// Compare strings a and b
// Return 1 if the same, 0 if not
uint8_t str_cmp(const char *a, const char *b) {
	while (*a != 0)
		if (*b++ != *a++)
			return 0;

	if (*a != *b)
		return 0; // strings must be the same length

	return 1;
}

// Compare strings a and b alphabetically
//   - case-insensitive (since two files cannot be next to each other with the same name and different case)
//   - shorter strings first
//  0  if  b == a  (strings are the same)
//  > 0 if b < a   (b first alphabetically)
//  < 0 if b > a   (a is fist alphabetically)
int str_cmp_alpha(const char *a, const char *b) {
	int count = 0;

	// compare alphabetically
	while ((*a != 0) && (*b != 0)) {
		count = upper(*a++) - upper(*b++);
		if (count != 0)
			return (count);
	}

	// check lenght (if strings seem to be the same)
	if (str_len(b) < str_len(a)) {
		count++;
	} else if (str_len(b) > str_len(a)) {
		count--;
	}

	return (count);
}

// Returns 1 if string begins with (or is equal to) prefix
// Returns 0 if not
// E.g.:
//  string=ABCD, prefix=ABC -->> returns 1
//  string=ABCD, prefix=ABCD -->>> returns 1
//  string=ABCD, prefix=ABCDE -->>> returns 0
//  string=ABCD, prefix=anything except {A, AB, ABC, ABCD} -->> returns 0
uint8_t str_startswith(const char *string, const char *prefix) {
	while (*prefix) {
		if (*prefix++ != *string++)
			return 0;
	}
	return 1;
}

// Returns 1 if string begins with (or is equal to) prefix -- case insensitive
// Returns 0 if not
uint8_t str_startswith_nocase(const char *string, const char *prefix) {
	while (*prefix) {
		if (upper(*prefix++) != upper(*string++))
			return 0;
	}
	return 1;
}

// Returns first position of character needle in haystack string
// Returns 0xFFFFFFFF if not found
uint32_t str_pos(char needle, const char *haystack) {
	uint32_t i = 0;
	while (*haystack++) {
		if (*haystack == needle)
			return (i);
		i++;
	}
	return (0xFFFFFFFF); // not found
}

// Convert integer x to a string, padding with 0's to make it d digits
// Returns the length
uint32_t intToStr(uint32_t x, char *str, uint32_t d) {
	uint32_t i = 0;
	uint32_t len;
	char temp;

	if (x > 0) {
		while (x) {
			str[i++] = (x % 10) + '0';
			x = x / 10;
		}

		// If number of digits required is more, then
		// add 0s at the beginning
		while (i < d)
			str[i++] = '0';

		len = i;

		x = i - 1;
		i = 0;
		while (i < x) {
			temp = str[i];
			str[i] = str[x];
			str[x] = temp;
			i++;
			x--;
		}

		str[len] = '\0';
		return len;
	}

	else // if integer == 0;
	{
		str[0] = '0';
		str[1] = '\0';
		return 1;
	}
}

// looks for 'find' string into 'str'
// returns 1 if found, 0 otherwise
uint8_t str_found(const char *str, const char *find) {
	int flag = 0;

	int len_str = str_len(str);
	int len_find = str_len(find);

	for (int i = 0; i <= len_str - len_find; i++) {
		for (int j = i; j < i + len_find; j++) {
			flag = 1;
			if (str[j] != find[j - i]) {
				flag = 0;
				break;
			}
		}
		if (flag)
			return 1;
	}
	return 0;
}
