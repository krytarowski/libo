#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <err.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <util.h>

#include "overflow.h"

#define FUN(name,type,min,max, wrapped, print) \
void test_##name(char *a, char *b) \
{ \
	type v1 = wrapped(a, 0, min, max); \
	type v2 = wrapped(b, 0, min, max); \
\
	type res; \
	bool o; \
\
	o = overflow_add(&res, v1, v2); \
	printf("[%s] %" #print " + %" #print " = %" #print " [status %s]\n", #name , v1, v2, res, o ? "overflow" : "ok"); \
	o = overflow_sub(&res, v1, v2); \
	printf("[%s] %" #print " - %" #print " = %" #print " [status %s]\n", #name , v1, v2, res, o ? "overflow" : "ok"); \
	o = overflow_mul(&res, v1, v2); \
	printf("[%s] %" #print " * %" #print " = %" #print " [status %s]\n", #name , v1, v2, res, o ? "overflow" : "ok"); \
	o = overflow_div(&res, v1, v2); \
	printf("[%s] %" #print " / %" #print " = %" #print " [status %s]\n", #name , v1, v2, res, o ? "overflow" : "ok"); \
}

FUN(char,char,CHAR_MIN,CHAR_MAX,estrtoi, d)
FUN(schar,signed char,SCHAR_MIN,SCHAR_MAX,estrtoi, hhd)
FUN(uchar,unsigned char,0,UCHAR_MAX,estrtou, hhu)
FUN(shrt,short,SHRT_MIN,SHRT_MAX,estrtoi, hd)
FUN(ushrt,unsigned short,0,USHRT_MAX,estrtou, hu)
FUN(int,int,INT_MIN,INT_MAX,estrtoi, d)
FUN(uint,unsigned int,0,UINT_MAX,estrtou, u)
FUN(long,long,LONG_MIN,LONG_MAX,estrtoi, ld)
FUN(ulong,unsigned long,0,ULONG_MAX,estrtou, lu)
FUN(llong,long long,LLONG_MIN,LLONG_MAX,estrtoi, lld)
FUN(ullong,unsigned long long,0,ULLONG_MAX,estrtou, llu)

#define IF_CHECK(name) \
if (strcmp(argv[1], #name ) == 0) { \
	test_##name (argv[2], argv[3]); \
}

void usage(void)
{
	errx(EXIT_FAILURE, "usage: ./prog [char|schar|uchar|int|uint|long|ulong|llong|ullong] NUM1 NUM2");
}

int main(int argc, char **argv)
{
	if (argc < 4)
		usage();

	IF_CHECK(char)
	else IF_CHECK(schar)
	else IF_CHECK(uchar)
	else IF_CHECK(shrt)
	else IF_CHECK(ushrt)
	else IF_CHECK(int)
	else IF_CHECK(uint)
	else IF_CHECK(long)
	else IF_CHECK(ulong)
	else IF_CHECK(llong)
	else IF_CHECK(ullong)
	else usage();

	return 0;
}
