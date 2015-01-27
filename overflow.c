/*
 * Copyright (c) 2015 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Kamil Rytarowski.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <limits.h>

#include "overflow.h"

int overflow_add_char(char *r, char a, char b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#else

#if (CHAR_MIN < 0)
	if (b < 0)
		return overflow_sub_char(r, a, -b);
#endif

	if (a > CHAR_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_schar(signed char *r, signed char a, signed char b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_schar(r, a, -b);

	if (a > SCHAR_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_shrt(short *r, short a, short b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_shrt(r, a, -b);

	if (a > SHRT_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_int(int *r, int a, int b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_sadd_overflow)
	return __builtin_sadd_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_int(r, a, -b);

	if (a > INT_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_long(long *r, long a, long b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_saddl_overflow)
	return __builtin_saddl_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_long(r, a, -b);

	if (a > LONG_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_llong(long long *r, long long a, long long b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_saddll_overflow)
	return __builtin_saddll_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_llong(r, a, -b);

	if (a > LLONG_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_uchar(unsigned char *r, unsigned char a, unsigned char b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#else
	if (a > UCHAR_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_ushrt(unsigned short *r, unsigned short a, unsigned short b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#else
	if (a > USHRT_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_uint(unsigned int *r, unsigned int a, unsigned int b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_sadd_overflow)
	return __builtin_uadd_overflow(a,b,r);
#else
	if (a > UINT_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_ulong(unsigned long *r, unsigned long a, unsigned long b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_saddl_overflow)
	return __builtin_uaddl_overflow(a,b,r);
#else
	if (a > ULONG_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_add_ullong(unsigned long long *r, unsigned long long a, unsigned long long b)
{
#if __has_builtin(__builtin_add_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_add_overflow(a,b,r);
#elif __has_builtin(__builtin_saddll_overflow)
	return __builtin_uaddll_overflow(a,b,r);
#else
	if (a > ULLONG_MAX - b)
		return 1;

	*r = a + b;
	return 0;
#endif
}

int overflow_sub_char(char *r, char a, char b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#else

#if (CHAR_MIN < 0)
	if (b < 0)
		return overflow_add_char(r, a, -b);
#endif

	if (a < CHAR_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_schar(signed char *r, signed char a, signed char b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_add_schar(r, a, -b);

	if (a < SCHAR_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_shrt(short *r, short a, short b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_add_shrt(r, a, -b);

	if (a < SHRT_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_int(int *r, int a, int b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_ssub_overflow)
	return __builtin_ssub_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_int(r, a, -b);

	if (a < INT_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_long(long *r, long a, long b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_ssubl_overflow)
	return __builtin_ssubl_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_long(r, a, -b);

	if (a < LONG_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_llong(long long *r, long long a, long long b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_ssubll_overflow)
	return __builtin_ssubll_overflow(a,b,r);
#else
	if (b < 0)
		return overflow_sub_llong(r, a, -b);

	if (a < LLONG_MIN + b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_uchar(unsigned char *r, unsigned char a, unsigned char b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#else
	if (a < b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_ushrt(unsigned short *r, unsigned short a, unsigned short b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#else
	if (a < b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_uint(unsigned int *r, unsigned int a, unsigned int b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_ssub_overflow)
	return __builtin_usub_overflow(a,b,r);
#else
	if (a < b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_ulong(unsigned long *r, unsigned long a, unsigned long b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_ssubl_overflow)
	return __builtin_usubl_overflow(a,b,r);
#else
	if (a < b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_sub_ullong(unsigned long long *r, unsigned long long a, unsigned long long b)
{
#if __has_builtin(__builtin_sub_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_sub_overflow(a,b,r);
#elif __has_builtin(__builtin_usubll_overflow)
	return __builtin_usubll_overflow(a,b,r);
#else
	if (a < b)
		return 1;

	*r = a - b;
	return 0;
#endif
}

int overflow_mul_char(char *r, char a, char b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#else
#if CHAR_MIN < 0
	if (a < 0 && b < 0)
		return overflow_mul_char(r, -a, -b);
#endif

	if (a != 0 && b != 0) {
#if CHAR_MIN < 0
		if (((a > 0 && b > 0) && (a > CHAR_MAX / b)) ||
		    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < CHAR_MIN / b)))) {
			return 1;
		}
#else
		if (a > CHAR_MAX / b) {
			return 1;
		}
#endif
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_schar(signed char *r, signed char a, signed char b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#else
	if (a < 0 && b < 0) {
#if (-SCHAR_MAX == SCHAR_MIN)
		if (a == SCHAR_MIN || b == SCHAR_MIN)
			return 1;
#endif
		return overflow_mul_schar(r, -a, -b);
	}

	if ((a != 0 && b != 0) &&
	    ((((a > 0 && b > 0) && (a > SCHAR_MAX / b)) ||
	    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < SCHAR_MIN / b))))) {
		return 1;
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_shrt(short *r, short a, short b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#else
	if (a < 0 && b < 0) {
#if (-SHRT_MAX == SHRT_MIN)
		if (a == SHRT_MIN || b == SHRT_MIN)
			return 1;
#endif
		return overflow_mul_shrt(r, -a, -b);
	}

	if ((a != 0 && b != 0) &&
	    ((((a > 0 && b > 0) && (a > SHRT_MAX / b)) ||
	    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < SHRT_MIN / b)))))) {
		return 1;
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_int(int *r, int a, int b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_smul_overflow)
	return __builtin_smul_overflow(a,b,r);
#else
	if (a < 0 && b < 0) {
#if (-INT_MAX == INT_MIN)
		if (a == INT_MIN || b == INT_MIN)
			return 1;
#endif
		return overflow_mul_int(r, -a, -b);
	}

	if ((a != 0 && b != 0) &&
	    (((a > 0 && b > 0) && (a > INT_MAX / b)) ||
	    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < INT_MIN / b)))) {
		return 1;
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_long(long *r, long a, long b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_smull_overflow)
	return __builtin_smull_overflow(a,b,r);
#else
	if (a < 0 && b < 0) {
#if (-LONG_MAX == LONG_MIN)
		if (a == LONG_MIN || b == LONG_MIN)
			return 1;
#endif
		return overflow_mul_long(r, -a, -b);
	}

	if ((a != 0 && b != 0) &&
	    (((a > 0 && b > 0) && (a > LONG_MAX / b)) ||
	    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < LONG_MIN / b))))) {
		return 1;
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_llong(long long *r, long long a, long long b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_smulll_overflow)
	return __builtin_smulll_overflow(a,b,r);
#else
	if (a < 0 && b < 0) {
#if (-LLONG_MAX == LLONG_MIN)
		if (a == LLONG_MIN || b == LLONG_MIN)
			return 1;
#endif
		return overflow_mul_llong(r, -a, -b);
	}

	if ((a != 0 && b != 0) &&
	    (((a > 0 && b > 0) && (a > LLONG_MAX / b)) ||
	    ((((a < 0 && b > 0) || (a > 0 && b < 0)) && (a < LLONG_MIN / b))))) {
		return 1;
	}

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_uchar(unsigned char *r, unsigned char a, unsigned char b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#else
	if (b != 0 && a > UCHAR_MAX / b)
		return 1;

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_ushrt(unsigned short *r, unsigned short a, unsigned short b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#else
	if (b != 0 && a > USHRT_MAX / b)
		return 1;

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_uint(unsigned int *r, unsigned int a, unsigned int b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_umul_overflow)
	return __builtin_umul_overflow(a,b,r);
#else
	if (b != 0 && a > UINT_MAX / b)
		return 1;

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_ulong(unsigned long *r, unsigned long a, unsigned long b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_umull_overflow)
	return __builtin_umull_overflow(a,b,r);
#else
	if (b != 0 && a > ULONG_MAX / b)
		return 1;

	*r = a * b;
	return 0;
#endif
}

int overflow_mul_ullong(unsigned long long *r, unsigned long long a, unsigned long long b)
{
#if __has_builtin(__builtin_mul_overflow) || __GNUC_PREREQ__(5,0)
	return __builtin_mul_overflow(a,b,r);
#elif __has_builtin(__builtin_umulll_overflow)
	return __builtin_umulll_overflow(a,b,r);
#else
	if (b != 0 && a > ULLONG_MAX / b)
		return 1;

	*r = a * b;
	return 0;
#endif
}

int overflow_div_char(char *r, char a, char b)
{
	if (b == 0)
		return 1;

#if (CHAR_MIN < 0) && (CHAR_MIN < (-1 * CHAR_MAX))
	if (a == CHAR_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_schar(signed char *r, signed char a, signed char b)
{
	if (b == 0)
		return 1;

#if (SCHAR_MIN < (-1 * SCHAR_MAX))
	if (a == SCHAR_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_shrt(short *r, short a, short b)
{
	if (b == 0)
		return 1;

#if (SHRT_MIN < (-1 * SHRT_MAX))
	if (a == SHRT_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_int(int *r, int a, int b)
{
	if (b == 0)
		return 1;

#if (INT_MIN < (-1 * INT_MAX))
	if (a == INT_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_long(long *r, long a, long b)
{
	if (b == 0)
		return 1;

#if (LONG_MIN < (-1 * LONG_MAX))
	if (a == LONG_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_llong(long long *r, long long a, long long b)
{
	if (b == 0)
		return 1;

#if (LLONG_MIN < (-1 * LLONG_MAX))
	if (a == LLONG_MIN && b == -1)
		return 1;
#endif

	*r = a / b;
	return 0;
}

int overflow_div_uchar(unsigned char *r, unsigned char a, unsigned char b)
{
	if (b == 0)
		return 1;

	*r = a / b;
	return 0;
}

int overflow_div_ushrt(unsigned short *r, unsigned short a, unsigned short b)
{
	if (b == 0)
		return 1;

	*r = a / b;
	return 0;
}

int overflow_div_uint(unsigned int *r, unsigned int a, unsigned int b)
{
	if (b == 0)
		return 1;

	*r = a / b;
	return 0;
}

int overflow_div_ulong(unsigned long *r, unsigned long a, unsigned long b)
{
	if (b == 0)
		return 1;

	*r = a / b;
	return 0;
}

int overflow_div_ullong(unsigned long long *r, unsigned long long a, unsigned long long b)
{
	if (b == 0)
		return 1;

	*r = a / b;
	return 0;
}
