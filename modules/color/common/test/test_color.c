/**
 * @file    test_color.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   TestColor Source
 *
 * @addtogroup TEST_COLOR
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

#include "unity.h"
#include "unity_color_helper.h"
#include "color.h"

#include "util.h"
#include "unity_util.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */

typedef struct {
    color_t rgb;
    color_t hsv;
    color_t hsl;
} color_equivalence_t;

/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static const color_equivalence_t color_equivalences[] = {
    /* black */
    {
      .rgb = COLOR_RGB_INIT(0.0,            0.0,  0.0),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      0.0, 0.0),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      0.0, 0.0)
    },
    /* dark gray */
    {
      .rgb = COLOR_RGB_INIT(0.25,           0.25, 0.25),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      0.0, 0.25),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      0.0, 0.25)
    },
    /* gray */
    {
      .rgb = COLOR_RGB_INIT(0.5,            0.5,  0.5),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      0.0, 0.5),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      0.0, 0.5)
    },
    /* light gray */
    {
      .rgb = COLOR_RGB_INIT(0.75,           0.75, 0.75),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      0.0, 0.75),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      0.0, 0.75)
    },
    /* white */
    {
      .rgb = COLOR_RGB_INIT(1.0,            1.0,  1.0),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      0.0, 1.0),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      0.0, 1.0)
    },
    /* red */
    {
      .rgb = COLOR_RGB_INIT(1.0,            0.0,  0.0),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      1.0, 1.0),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      1.0, 0.5)
    },
    /* gren */
    {
      .rgb = COLOR_RGB_INIT(0.0,            1.0,  0.0),
      .hsv = COLOR_HSV_INIT(120.0/360.0,    1.0, 1.0),
      .hsl = COLOR_HSL_INIT(120.0/360.0,    1.0, 0.5)
    },
    /* blue */
    {
      .rgb = COLOR_RGB_INIT(0.0,            0.0,  1.0),
      .hsv = COLOR_HSV_INIT(240.0/360.0,    1.0, 1.0),
      .hsl = COLOR_HSL_INIT(240.0/360.0,    1.0, 0.5)
    },
    /* yellow */
    {
      .rgb = COLOR_RGB_INIT(1.0,            1.0,  0.0),
      .hsv = COLOR_HSV_INIT(60.0/360.0,     1.0, 1.0),
      .hsl = COLOR_HSL_INIT(60.0/360.0,     1.0, 0.5)
    },
    /* magenta */
    {
      .rgb = COLOR_RGB_INIT(1.0,            0.0,  1.0),
      .hsv = COLOR_HSV_INIT(300.0/360.0,    1.0, 1.0),
      .hsl = COLOR_HSL_INIT(300.0/360.0,    1.0, 0.5)
    },
    /* cyan */
    {
      .rgb = COLOR_RGB_INIT(0.0,            1.0,  1.0),
      .hsv = COLOR_HSV_INIT(180.0/360.0,    1.0, 1.0),
      .hsl = COLOR_HSL_INIT(180.0/360.0,    1.0, 0.5)
    },
    /* dark red */
    {
      .rgb = COLOR_RGB_INIT(0.5,            0.0,  0.0),
      .hsv = COLOR_HSV_INIT(0.0/360.0,      1.0, 0.5),
      .hsl = COLOR_HSL_INIT(0.0/360.0,      1.0, 0.25)
    },
    /* dark green */
    {
      .rgb = COLOR_RGB_INIT(0.0,            0.5,  0.0),
      .hsv = COLOR_HSV_INIT(120.0/360.0,    1.0, 0.5),
      .hsl = COLOR_HSL_INIT(120.0/360.0,    1.0, 0.25)
    },
    /* dark blue */
    {
      .rgb = COLOR_RGB_INIT(0.0,            0.0,  0.5),
      .hsv = COLOR_HSV_INIT(240.0/360.0,    1.0, 0.5),
      .hsl = COLOR_HSL_INIT(240.0/360.0,    1.0, 0.25)
    },
    /* dark yellow */
    {
      .rgb = COLOR_RGB_INIT(0.5,            0.5,  0.0),
      .hsv = COLOR_HSV_INIT(60.0/360.0,     1.0, 0.5),
      .hsl = COLOR_HSL_INIT(60.0/360.0,     1.0, 0.25)
    },
    /* dark magenta */
    {
      .rgb = COLOR_RGB_INIT(0.5,            0.0,  0.5),
      .hsv = COLOR_HSV_INIT(300.0/360.0,    1.0, 0.5),
      .hsl = COLOR_HSL_INIT(300.0/360.0,    1.0, 0.25)
    },
    /* dark cyan */
    {
      .rgb = COLOR_RGB_INIT(0.0,            0.5,  0.5),
      .hsv = COLOR_HSV_INIT(180.0/360.0,    1.0, 0.5),
      .hsl = COLOR_HSL_INIT(180.0/360.0,    1.0, 0.25)
    },
};

static unsigned int n_color_equivalences = ARRAY_ELEMENTS(color_equivalences);

static const int bad_types[] = {
    -1,
    MAX_COLOR_TYPE,
    MAX_COLOR_TYPE + 1,
    COLOR_TYPE_INVALID,
    324,
    INT_MAX,
    INT_MIN,
};

static unsigned int n_bad_types = ARRAY_ELEMENTS(bad_types);

const float bad_channels[] = {
    -1.0,
    2.0,
    1.1,
    -0.1,
    FLT_MAX,
    -FLT_MAX,
    0.0 / 0.0, // NaN
    1.0 / 0.0, // +inf
    (-1.0) / 0.0, // -inf
};

static unsigned int n_bad_channels = ARRAY_ELEMENTS(bad_channels);

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void test_color_rgb_init(void)
{
    color_t rgb_color = COLOR_RGB_INIT(0.1, 0.2, 0.3);

    TEST_ASSERT_EQUAL(COLOR_TYPE_RGB, rgb_color.type);
    TEST_ASSERT_EQUAL_FLOAT(0.1, rgb_color.r);
    TEST_ASSERT_EQUAL_FLOAT(0.2, rgb_color.g);
    TEST_ASSERT_EQUAL_FLOAT(0.3, rgb_color.b);
}

void test_color_hsv_init(void)
{
    color_t hsv_color = COLOR_HSV_INIT(0.1, 0.2, 0.3);

    TEST_ASSERT_EQUAL(COLOR_TYPE_HSV, hsv_color.type);
    TEST_ASSERT_EQUAL_FLOAT(0.1, hsv_color.h);
    TEST_ASSERT_EQUAL_FLOAT(0.2, hsv_color.s);
    TEST_ASSERT_EQUAL_FLOAT(0.3, hsv_color.v);
}

void test_color_hsl_init(void)
{
    color_t hsl_color = COLOR_HSL_INIT(0.1, 0.2, 0.3);

    TEST_ASSERT_EQUAL(COLOR_TYPE_HSL, hsl_color.type);
    TEST_ASSERT_EQUAL_FLOAT(0.1, hsl_color.h);
    TEST_ASSERT_EQUAL_FLOAT(0.2, hsl_color.s);
    TEST_ASSERT_EQUAL_FLOAT(0.3, hsl_color.l);
}

void test_color_rgb_to_rgb(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].rgb), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].rgb), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_RGB);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_rgb_to_hsv(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].rgb), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsv), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_rgb_to_hsl(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].rgb), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsl), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSL);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsv_to_rgb(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsv), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].rgb), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_RGB);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsv_to_hsv(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsv), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsv), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsv_to_hsl(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsv), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsl), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSL);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsl_to_rgb(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsl), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].rgb), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_RGB);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsl_to_hsv(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsl), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsv), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_color_hsl_to_hsl(void)
{
    unsigned int i;
    color_t converted;
    color_t expected;

    for (i = 0; i < n_color_equivalences; i++) {
        memcpy(&converted, &(color_equivalences[i].hsl), sizeof(color_t));
        memcpy(&expected,  &(color_equivalences[i].hsl), sizeof(color_t));

        color_err_t err = color_convert(&converted, COLOR_TYPE_HSL);
        TEST_ASSERT_EQUAL(COLOR_SUCCESS, err);
        TEST_ASSERT_EQUAL_color_t(expected, converted);
    }
}

void test_convert_from_invalid_color_type(void)
{
    unsigned int i;
    color_err_t err;
    color_t bad_type = {
        .type = COLOR_TYPE_INVALID,
    };

    for (i = 0; i < n_bad_types; i++) {
        bad_type.type = bad_types[i];
        err = color_convert(&bad_type, COLOR_TYPE_RGB);
        TEST_ASSERT_EQUAL(COLOR_ERR_TYPE, err);
    }
}

void test_convert_to_invalid_color_type(void)
{
    unsigned int i;
    color_err_t err;
    color_t white = {
        .type = COLOR_TYPE_RGB,
        .r = 0.0,
        .g = 0.0,
        .b = 0.0,
    };

    for (i = 0; i < n_bad_types; i++) {
        err = color_convert(&white, bad_types[i]);
        TEST_ASSERT_EQUAL(COLOR_ERR_TYPE, err);
    }
}

void test_convert_with_invalid_channel(void)
{
    unsigned int i;
    color_err_t err;
    color_t invalid;

    for (i = 0; i < n_bad_channels; i++) {
        invalid.type    = COLOR_TYPE_RGB;
        invalid.r       = bad_channels[i];
        invalid.g       = 0.0;
        invalid.b       = 0.0;
        err = color_convert(&invalid, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_ERR_LEVEL, err);

        invalid.type    = COLOR_TYPE_RGB;
        invalid.r       = 0.0;
        invalid.g       = bad_channels[i];
        invalid.b       = 0.0;
        err = color_convert(&invalid, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_ERR_LEVEL, err);

        invalid.type    = COLOR_TYPE_RGB;
        invalid.r       = 0.0;
        invalid.g       = 0.0;
        invalid.b       = bad_channels[i];
        err = color_convert(&invalid, COLOR_TYPE_HSV);
        TEST_ASSERT_EQUAL(COLOR_ERR_LEVEL, err);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} addtogroup TEST_COLOR */
