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

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void str_cpy(char *dest, const char *src);
void str_cat(char *dest, const char *srca, const char *srcb);
uint32_t str_len(const char *str);
uint8_t str_split(const char *string, char split_char, char *before_split, char *after_split);
uint8_t str_rstr(const char *string, char split_char, char *before_split);
void str_tok(char *in_string, char find, char *tokk);
uint32_t str_xt_int(const char *string);
uint32_t intToStr(uint32_t x, char *str, uint32_t d);
char upper(char a);
char lower(char a);
void str_to_upper(const char *str_in, char *str_up);
void str_to_lower(const char *str_in, char *str_lo);
uint8_t str_cmp(const char *a, const char *b);
uint8_t str_cmp_nocase(const char *a, const char *b);
int str_cmp_alpha(const char *a, const char *b);
uint8_t str_startswith(const char *string, const char *prefix);
uint8_t str_startswith_nocase(const char *string, const char *prefix);
uint32_t str_pos(char needle, const char *haystack);
uint8_t str_found(const char *str, const char *find);

uint8_t trim_slash(char *string);
uint8_t add_slash(char *string);

#ifdef __cplusplus
}
#endif
