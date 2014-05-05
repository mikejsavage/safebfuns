/* Public domain */

#include <string.h>

#if __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ > 4 )
	// http://gcc.gnu.org/onlinedocs/gcc/Function-Specific-Option-Pragmas.html
	// http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
	#pragma GCC push_options
	#pragma GCC optimize ( "-O0" )
	#define NOINLINE __attribute__ (( noinline ))
#else
	#error "require gcc >= 4.4"
#endif

NOINLINE void explicit_bzero( void * const buf, const size_t n ) {
	size_t i;
	unsigned char * p = buf;

	for( i = 0; i < n; i++ ) {
		p[ i ] = 0;
	}
}

NOINLINE int timingsafe_bcmp( const void * const b1, const void * const b2, const size_t n ) {
	size_t i;
	const unsigned char * p1 = b1;
	const unsigned char * p2 = b2;
	int result = 0;

	for( i = 0; i < n; i++ ) {
		result |= p1[ i ] != p2[ i ];
	}

	return result;
}

#pragma GCC pop_options
