This repository contains a single C header file which defines
`explicit_bzero` and `timingsafe_bcmp` with pragmas to ensure calls to
them are not optimised out of the program or otherwise.

It is currently only implemented for GCC >= 4.4 and should fail to
compile with other compilers.


Example usage
--------------

	#include "safebfuns.h"
	
	int main() {
		char b1[ 128 ];
		char b2[ 128 ];
		char b3[ 128 ];
	
		explicit_bzero( b1, 128 );
		explicit_bzero( b3, 128 );
	
		return timingsafe_bcmp( b1, b2, 128 );
	}

You can validate this is correctly preventing optimisation by running
`gcc -O3 -S foo.c` and examining the output in `foo.s`.
