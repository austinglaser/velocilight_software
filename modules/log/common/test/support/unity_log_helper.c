/**@file    unity_log_helper.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   UnityLogHelper Source
 *
 * @addtogroup UNITY_LOG_HELPER
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity_log_helper.h"

#include "log.h"
#include "unity.h"
#include "unity_util.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void AssertEqual_log_binary_data_t(log_binary_data_t expected,
                                   log_binary_data_t actual,
                                   unsigned short line,
                                   const char * message)
{
    char full_message[128];

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Binary data type");
    UNITY_TEST_ASSERT_EQUAL_HEX8(expected.type, actual.type,
                                 line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Binary data len");
    UNITY_TEST_ASSERT_EQUAL_UINT32(expected.len, actual.len,
                                   line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Binary data pointer");
    UNITY_TEST_ASSERT_EQUAL_PTR(expected.data, actual.data,
                                line, full_message);

}

void AssertEqual_log_entry_t(log_entry_t expected,
                             log_entry_t actual,
                             unsigned short line,
                             const char * message)
{
    char full_message[128];

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Log entry type");
    UNITY_TEST_ASSERT_EQUAL_HEX8(expected.type, actual.type,
                                 line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Log entry subtype");
    UNITY_TEST_ASSERT_EQUAL_HEX8(expected.subtype, actual.subtype,
                                 line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Log entry flags");
    UNITY_TEST_ASSERT_EQUAL_HEX16(expected.flags, actual.flags,
                                  line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Log entry descriptor string");
    UNITY_TEST_ASSERT_EQUAL_STRING(expected.descriptor_string,
                                   actual.descriptor_string,
                                   line, full_message);

    strncat_if_nonempty(full_message, sizeof(full_message),
                        message, "Log entry binary data count");
    UNITY_TEST_ASSERT_EQUAL_UINT32(expected.binary_data_count,
                                   actual.binary_data_count,
                                   line, full_message);

    uint32_t i;
    for (i = 0; i < LOG_MAX_BINARY_DATA; i++) {
        strncat_if_nonempty(full_message, sizeof(full_message),
                            message, "Log entry binary data");

        char number_string[16];
        snprintf(number_string, sizeof(number_string), " %" PRIu32, i);
        strncat(full_message, number_string,
                sizeof(full_message) - strlen(full_message) - 1);

        UNITY_TEST_ASSERT_EQUAL_log_binary_data_t(expected.binary_data[i],
                                                  actual.binary_data[i],
                                                  line, full_message);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup UNITY_LOG_HELPER */
