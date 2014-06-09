/* Public domain */

#include <string.h>

#if __clang__
	// http://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
	// http://lists.cs.uiuc.edu/pipermail/llvmdev/2013-April/061527.html
	#if __has_attribute( noinline )
		#pragma clang optimize push
		#pragma clang optimize ( "O0" )
		#define NOINLINE __attribute__ (( noinline ))
	#else
		#error "require clang that supports noinline"
	#endif
#elif __GNUC__
	// http://gcc.gnu.org/onlinedocs/gcc/Function-Specific-Option-Pragmas.html
	// http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
	#if __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ > 4 )
		#pragma GCC push_options
		#pragma GCC optimize ( "-O0" )
		#define NOINLINE __attribute__ (( noinline ))
	#else
		#error "require gcc >= 4.4"
	#endif
#else
	#error "unrecognised compiler"
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
	const unsigned char * const p1 = b1;
	const unsigned char * const p2 = b2;
	int result = 0;

	for( i = 0; i < n; i++ ) {
		result |= p1[ i ] ^ p2[ i ];
	}

	return result;
}

#ifdef __clang__
	#pragma clang optimize pop
#else
	#pragma GCC pop_options
#endif
