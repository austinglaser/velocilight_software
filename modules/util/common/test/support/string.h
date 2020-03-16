/* Workaround for missing bsd definitions (strlcpy, strlcat) in gnu's
 * <string.h> header.
 *
 * To preserve the philosophy of "production source should not have test
 * hacks", this hack exists instead. It should only be on the include path when
 * the project is being built in test mode. For extra safety, it checks the
 * TEST definition, and transparently includes the correct version if it
 * somehow slips into production code.
 *
 * Effectively, this is just a wrapper around <bsd/string.h>. However, an extra
 * wrinkle is introduced by the fact that <bsd/string.h> ITSELF includes
 * <string.h>. We must detect this recursive inclusion (which presents as a
 * failure of the preprocessor guard condition) and properly forward onto the
 * ordinary <string.h> so that the *usual* definitions (strcmp, memcpy, etc)
 * are also available.
 */
#if !defined(UTIL_STRING_H) && defined(TEST)

#   define UTIL_STRING_H
#   include <bsd/string.h>

#elif defined(TEST)

/* In non-test mode, we rely on the multiple include guards in <string.h>,
 * since UTIL_STRING_H will never be defined */
#   include_next <string.h>

#endif
