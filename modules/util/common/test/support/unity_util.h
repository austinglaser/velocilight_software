/**@file    unity_util.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityUtil Interface
 */

#ifndef UNITY_UTIL_H
#define UNITY_UTIL_H

/**@defgroup UNITY_UTIL UnityUtil
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

/** Preprocess-out TEST_CASE definitions
 *
 * These are understood by the unity runner generator, and have no effect on
 * actual test code
 */
#if defined(TEST_PP)
#   define TEST_VALUE(...) TEST_CASE(__VA_ARGS__)
#else
#   define TEST_VALUE(...)
#endif

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Puts '@p first. @p second' into @p out, if @p first is nonempty
 *
 * If @p first is neither NULL nor the empty string, concatenates it with
 * second. Otherwise, simply copies @p second to @p out
 *
 * Will never overrun @p out, and will always null-terminate.
 *
 * @param[out] out:     Location to write the concatenated string
 * @param[in] out_len:  Available space in @p out
 * @param[in] first:    First string to be concatenated
 * @param[in] second:   Second string to be concatenated
 *
 * @return              @p out
 */
char * strncat_if_nonempty(char * out,
                           size_t out_len,
                           char const * first,
                           char const * second);

/** @} defgroup UNITY_UTIL */

#endif /* ifndef UNITY_UTIL_H */
