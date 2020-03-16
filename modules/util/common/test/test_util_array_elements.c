/**
 * @file    test_util.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestUtil Source
 *
 * @addtogroup TEST_UTIL
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "util.h"
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_array_elements_char(void)
{
    char arr1[1];
    char arr5[5];
    char arr1024[1024];

    TEST_ASSERT_EQUAL(1, ARRAY_ELEMENTS(arr1));
    TEST_ASSERT_EQUAL(5, ARRAY_ELEMENTS(arr5));
    TEST_ASSERT_EQUAL(1024, ARRAY_ELEMENTS(arr1024));
}

void test_array_elements_int(void)
{
    int arr1[1];
    int arr5[5];
    int arr1024[1024];

    TEST_ASSERT_EQUAL(1, ARRAY_ELEMENTS(arr1));
    TEST_ASSERT_EQUAL(5, ARRAY_ELEMENTS(arr5));
    TEST_ASSERT_EQUAL(1024, ARRAY_ELEMENTS(arr1024));
}

void test_array_elements_double(void)
{
    double arr1[1];
    double arr5[5];
    double arr1024[1024];

    TEST_ASSERT_EQUAL(1, ARRAY_ELEMENTS(arr1));
    TEST_ASSERT_EQUAL(5, ARRAY_ELEMENTS(arr5));
    TEST_ASSERT_EQUAL(1024, ARRAY_ELEMENTS(arr1024));
}

void test_array_elements_pointer(void)
{
    void * arr1[1];
    void * arr5[5];
    void * arr1024[1024];

    TEST_ASSERT_EQUAL(1, ARRAY_ELEMENTS(arr1));
    TEST_ASSERT_EQUAL(5, ARRAY_ELEMENTS(arr5));
    TEST_ASSERT_EQUAL(1024, ARRAY_ELEMENTS(arr1024));
}

void test_array_elements_struct(void)
{
    struct DummyStruct{
        int x;
        double y;
        void * next;
    };

    struct DummyStruct arr1[1];
    struct DummyStruct arr5[5];
    struct DummyStruct arr1024[1024];

    TEST_ASSERT_EQUAL(1, ARRAY_ELEMENTS(arr1));
    TEST_ASSERT_EQUAL(5, ARRAY_ELEMENTS(arr5));
    TEST_ASSERT_EQUAL(1024, ARRAY_ELEMENTS(arr1024));
}

void test_array_elements_implicit_length(void)
{
    uint32_t arr[] = { 1, 2, 3, 4, 5, 6, 7 };

    TEST_ASSERT_EQUAL(7, ARRAY_ELEMENTS(arr));
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_UTIL */
