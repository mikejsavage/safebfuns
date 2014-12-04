This repository contains a C source and header file which define
`explicit_bzero`, `timingsafe_bcmp` and `timingsafe_memcmp`. They
include preprocessor directives to ensure that the calls are not
optimised out of the program or otherwise.

It is currently implemented for:

* GCC >= 4.4
* clang >= 3.5

It should fail to compile with anything else.


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
