/* Public domain */

#include <string.h>

#if __clang__
	/*
	 * http://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros
	 * http://lists.cs.uiuc.edu/pipermail/llvmdev/2013-April/061527.html
	 */
	#if __has_attribute( noinline )
		#define NOINLINE __attribute__ (( noinline ))
	#else
		#error "require clang that supports noinline"
	#endif
#elif __GNUC__
	/*
	 * http://gcc.gnu.org/onlinedocs/gcc/Function-Specific-Option-Pragmas.html
	 * http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
	 */
	#if __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ > 4 )
		#define NOINLINE __attribute__ (( noinline ))
	#else
		#error "require gcc >= 4.4"
	#endif
#else
	#error "unrecognised compiler"
#endif

NOINLINE void explicit_bzero( void * const buf, const size_t n );
NOINLINE int timingsafe_bcmp( const void * const b1, const void * const b2, const size_t n );

#undef NOINLINE
