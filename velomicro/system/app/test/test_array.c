/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Array Test Source
///
/// @addtogroup ARRAY
/// @{
///
/// @defgroup ARRAY_TEST Array Tests
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// Test arraywork
#include "unity.h"

// Module under test
#include "array.h"

// Supporting modules
#include "color.h"
#include "error.h"
#include "util.h"

// Mocks, fakes, test support
#include "unity_color_helper.h"

// Source dependencies (present only to make Ceedling include the right
// objects)
#include "unity_util.h"

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //
// --- PRIVATE DATATYPES --------------------------------------------------- //

typedef struct {
    struct array_methods const * vmt;
    _array_data
    size_t alpha;
    size_t beta;
    color_t color;
    err_t to_return;
    bool was_called;
} test_array_t;

// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

err_t _test_array_write(
    array_t * array,
    size_t alpha,
    size_t beta,
    color_t color
);

err_t _test_array_write_all(array_t * array, color_t color);

err_t _test_array_read(
    array_t const * array,
    size_t alpha,
    size_t beta,
    color_t * color
);

err_t _test_array_show(array_t const * array);

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //

static test_array_t _test_array;
static const struct array_methods _test_array_methods = {
    .write = _test_array_write,
    .write_all = _test_array_write_all,
    .read = _test_array_read,
    .show = _test_array_show,
};

static array_t * const _array = (array_t *) &_test_array;

// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

void setUp(void) {
    _test_array.vmt = &_test_array_methods;

    _test_array.was_called = false;
}

// --- PUBLIC TESTS -------------------------------------------------------- //

void test_array_write_calls_write_function(void) {
    static const struct write_params {
        size_t alpha;
        size_t beta;
        color_t color;
        err_t err;
    } write_params[] = {
        {
            .alpha = 0,
            .beta = 0,
            .color = COLOR_RGB_INIT(0., 0., 0.),
            .err = ERROR_NONE,
        },
        {
            .alpha = 3,
            .beta = 5,
            .color = COLOR_HSL_INIT(0.5, 0.2, 0.9),
            .err = ERROR_COMM,
        },
        {
            .alpha = 1,
            .beta = 2,
            .color = COLOR_HSV_INIT(1.0, 1.0, 1.0),
            .err = ERROR_PARAM,
        },
    };

    for (size_t i = 0; i < ARRAY_ELEMENTS(write_params); i++) {
        struct write_params const * p = &write_params[i];

        _test_array.alpha = p->alpha;
        _test_array.beta = p->beta;
        _test_array.color = p->color;
        _test_array.to_return = p->err;

        _test_array.was_called = false;

        TEST_ASSERT_EQUAL(
            p->err,
            array_write(_array, p->alpha, p->beta, p->color)
        );
        TEST_ASSERT(_test_array.was_called);
    }
}

void test_array_write_detects_null_array(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_write(NULL, 0, 0, color));
}

void test_array_write_detects_null_vmt(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    array_t array = {
        .vmt = NULL,
    };
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_write(&array, 0, 0, color));
}

void test_array_write_detects_unimplemented(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    static const struct array_methods vmt = {
        .write = NULL,
        .write_all = _test_array_write_all,
        .read = _test_array_read,
        .show = _test_array_show,
    };
    array_t array = {
        .vmt = &vmt,
    };
    TEST_ASSERT_EQUAL(ERROR_NOENT, array_write(&array, 0, 0, color));
}

void test_array_write_calls_write_all_function(void) {
    static const struct write_all_params {
        color_t color;
        err_t err;
    } write_all_params[] = {
        { .color = COLOR_RGB_INIT(0., 0., 0.), .err = ERROR_NONE },
        { .color = COLOR_HSV_INIT(1., 0.5, 0.2), .err = ERROR_COMM },
        { .color = COLOR_HSL_INIT(0.2, 0.3, 0.75), .err = ERROR_HW },
    };

    for (size_t i = 0; i < ARRAY_ELEMENTS(write_all_params); i++) {
        struct write_all_params const * p = &write_all_params[i];
        _test_array.color = p->color;
        _test_array.to_return = p->err;

        _test_array.was_called = false;

        TEST_ASSERT_EQUAL(p->err, array_write_all(_array, p->color));
        TEST_ASSERT_TRUE(_test_array.was_called);
    }
}

void test_array_write_all_detects_null_array(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_write_all(NULL, color));
}

void test_array_write_all_detects_null_vmt(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    array_t array = {
        .vmt = NULL,
    };
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_write_all(&array, color));
}

void test_array_write_all_detects_unimplemented(void) {
    color_t color = COLOR_RGB_INIT(0., 0., 0.);
    static const struct array_methods vmt = {
        .write = _test_array_write,
        .write_all = NULL,
        .read = _test_array_read,
        .show = _test_array_show,
    };
    array_t array = {
        .vmt = &vmt,
    };
    TEST_ASSERT_EQUAL(ERROR_NOENT, array_write_all(&array, color));
}

void test_array_read_calls_read_function(void) {
    static const struct read_params {
        size_t alpha;
        size_t beta;
        color_t color;
        err_t err;
    } read_params[] = {
        {
            .alpha = 0,
            .beta = 0,
            .color = COLOR_RGB_INIT(0., 0., 0.),
            .err = ERROR_NONE,
        },
        {
            .alpha = 3,
            .beta = 5,
            .color = COLOR_HSL_INIT(0.5, 0.2, 0.9),
            .err = ERROR_COMM,
        },
        {
            .alpha = 1,
            .beta = 2,
            .color = COLOR_HSV_INIT(1.0, 1.0, 1.0),
            .err = ERROR_PARAM,
        },
    };

    for (size_t i = 0; i < ARRAY_ELEMENTS(read_params); i++) {
        struct read_params const * p = &read_params[i];

        _test_array.alpha = p->alpha;
        _test_array.beta = p->beta;
        _test_array.color = p->color;
        _test_array.to_return = p->err;

        _test_array.was_called = false;

        color_t read;

        TEST_ASSERT_EQUAL(
            p->err,
            array_read(_array, p->alpha, p->beta, &read)
        );
        TEST_ASSERT_TRUE(_test_array.was_called);
        TEST_ASSERT_EQUAL_color_t(p->color, read);
    }
}

void test_array_read_detects_null_array(void) {
    color_t color;
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_read(NULL, 0, 0, &color));
}

void test_array_read_detects_null_vmt(void) {
    color_t color;
    array_t array = {
        .vmt = NULL,
    };
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_read(&array, 0, 0, &color));
}

void test_array_read_detects_unimplemented(void) {
    color_t color;
    static const struct array_methods vmt = {
        .write = _test_array_write,
        .write_all = _test_array_write_all,
        .read = NULL,
        .show = _test_array_show,
    };
    array_t array = {
        .vmt = &vmt,
    };
    TEST_ASSERT_EQUAL(ERROR_NOENT, array_read(&array, 0, 0, &color));
}

void test_array_show_calls_show_function(void) {
    static const err_t errs[] = {
        ERROR_NONE,
        ERROR_COMM,
        ERROR_PARAM,
    };

    for (size_t i = 0; i < ARRAY_ELEMENTS(errs); i++) {
        _test_array.to_return = errs[i];

        _test_array.was_called = false;

        TEST_ASSERT_EQUAL(errs[i], array_show(_array));
        TEST_ASSERT_TRUE(_test_array.was_called);
    }
}

void test_array_show_detects_null_array(void) {
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_show(NULL));
}

void test_array_show_detects_null_vmt(void) {
    array_t array = {
        .vmt = NULL,
    };
    TEST_ASSERT_EQUAL(ERROR_PARAM, array_show(&array));
}

void test_array_show_detects_unimplemented(void) {
    static const struct array_methods vmt = {
        .write = _test_array_write,
        .write_all = _test_array_write_all,
        .read = _test_array_read,
        .show = NULL,
    };
    array_t array = {
        .vmt = &vmt,
    };
    TEST_ASSERT_EQUAL(ERROR_NOENT, array_show(&array));
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

err_t _test_array_write(
    array_t * array,
    size_t alpha,
    size_t beta,
    color_t color
) {
    TEST_ASSERT_EQUAL_PTR(&_test_array, array);

    test_array_t * tarray = (test_array_t *) array;

    TEST_ASSERT_FALSE(tarray->was_called);
    tarray->was_called = true;

    TEST_ASSERT_EQUAL_UINT32(tarray->alpha, alpha);
    TEST_ASSERT_EQUAL_UINT32(tarray->beta, beta);
    TEST_ASSERT_EQUAL_color_t(tarray->color, color);

    return tarray->to_return;
}

err_t _test_array_write_all(array_t * array, color_t color) {
    TEST_ASSERT_EQUAL_PTR(&_test_array, array);

    test_array_t * tarray = (test_array_t *) array;

    TEST_ASSERT_FALSE(tarray->was_called);
    tarray->was_called = true;

    TEST_ASSERT_EQUAL_color_t(tarray->color, color);

    return tarray->to_return;
}

err_t _test_array_read(
    array_t const * array,
    size_t alpha,
    size_t beta,
    color_t * color
) {
    TEST_ASSERT_EQUAL_PTR(&_test_array, array);

    test_array_t * tarray = (test_array_t *) array;

    TEST_ASSERT_FALSE(tarray->was_called);
    tarray->was_called = true;

    TEST_ASSERT_EQUAL(tarray->alpha, alpha);
    TEST_ASSERT_EQUAL(tarray->beta, beta);

    *color = tarray->color;

    return tarray->to_return;
}

err_t _test_array_show(array_t const * array) {
    TEST_ASSERT_EQUAL_PTR(&_test_array, array);

    test_array_t * tarray = (test_array_t *) array;

    TEST_ASSERT_FALSE(tarray->was_called);
    tarray->was_called = true;

    return tarray->to_return;
}

/// @} defgroup ARRAY_TEST
/// @} addtogroup ARRAY
