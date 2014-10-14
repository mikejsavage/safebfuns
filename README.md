This repository contains a C source and header file which define
`explicit_bzero`, `timingsafe_bcmp` and `timingsafe_memcmp`. They
include preprocessor directives to ensure that the calls are not
optimised out of the program or otherwise.

It is currently implemented for:

* GCC >= 4.4
* clang, see below

It should fail to compile with anything else.


Clang
-----

I'm not able to find anywhere mentioning exactly what version
`__attribute__ (( noinline ))` and `#pragma clang optimize` were added,
and I don't think you can explicitly test for the latter. I have only
tested with clang 3.4 so if you want to use an older version, you should
verify clang is producing correct assembly.


Example usage
--------------

	#include "safebfuns.h"
	
	int main() {
		char b1[ 128 ];
		char b2[ 128 ];
		char b3[ 128 ];
	
		explicit_bzero( b1, 128 );
		explicit_bzero( b3, 128 );

		const int ret = timingsafe_memcmp( b1, b2, 128 );
	
		return timingsafe_bcmp( b1, b2, 128 ) + ret;
	}

You can validate this is correctly preventing optimisation by running
`gcc -O3 -S foo.c safebfuns.c` and examining the output in `foo.s` and
`safebfuns.s`.
