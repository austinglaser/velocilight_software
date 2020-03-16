/**@file    color.c
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   Floating-point color library implementation
 *
 * @addtogroup COLOR
 * @{
 */

/* --- PRIVATE DEPENDENCIES-------------------------------------------------- */

#include "color.h"

#include "stdint.h"
#include <math.h>

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */
/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */

/** Evaluate the maximum of three floating-point values
 *
 * @param[in] v1:       The first value to evaluate
 * @param[in] v2:       The second value to evaluate
 * @param[in] v3:       The third value to evaluate
 * @return              The max of v1, v2, and v3
 */
#define FMAX3(v1, v2, v3)   fmax(fmax((v1), (v2)), (v3))

/** Evaluate the minimum of three floating-point values
 *
 * @param[in] v1:       The first value to evaluate
 * @param[in] v2:       The second value to evaluate
 * @param[in] v3:       The third value to evaluate
 * @return              The min of v1, v2, and v3
 */
#define FMIN3(v1, v2, v3)   fmin(fmin((v1), (v2)), (v3))

/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */

/** Convert color from rgb to hsv
 *
 * Based on <http://www.rapidtables.com/convert/color/rgb-to-hsv.htm>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_rgb_to_hsv(color_t * color);

/** Convert color from rgb to hsl
 *
 * Based on <http://www.rapidtables.com/convert/color/rgb-to-hsl.htm>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_rgb_to_hsl(color_t * color);

/** Convert color from hsv to rgb
 *
 * Based on <http://www.rapidtables.com/convert/color/hsv-to-rgb.htm>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_hsv_to_rgb(color_t * color);

/** Convert color from hsv to hsl
 *
 * Based on <http://ariya.blogspot.com/2008/07/converting-between-hsl-and-hsv.html>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_hsv_to_hsl(color_t * color);

/** Convert color from hsl to rgb
 *
 * Based on <http://www.rapidtables.com/convert/color/hsl-to-rgb.htm>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_hsl_to_rgb(color_t * color);

/** Convert color from hsl to hsv
 *
 * Based on <http://ariya.blogspot.com/2008/07/converting-between-hsl-and-hsv.html>
 *
 * @note    Ignores color's current type
 *
 * @param[in,out] color:    The color to convert
 */
static void _color_convert_hsl_to_hsv(color_t * color);

/** Get the hue value from a color of type @ref COLOR_TYPE_RGB
 *
 * @param[in] color:    The RGB color
 * @param[in] cmax:     The max of r, g, and b
 * @param[in] cmin:     The min of r, g, and b
 *
 * @return              The hue for an equivalent HSV or HSL color
 */
static float _color_get_h_from_rgb(color_t const * color, float cmax, float cmin);

/** Get RGB from the helper values c, x, and m
 *
 * c, x, and m are calculated from the hsv or hsl color. See @ref
 * _color_hsv_to_rgb() and @ref_color_hsl_to_rgb() for the calculations for
 * each color type.
 *
 * @param[in] h:        The input color's hue
 * @param[in] c:        C helper value
 * @param[in] x:        X helper value
 * @param[in] m:        M helper value
 * @param[out] r:       The computed red value
 * @param[out] g:       The computed green value
 * @param[out] b:       The computed blue value
 */
static void _color_get_rgb_from_hcxm(float h,
                                     float c,
                                     float x,
                                     float m,
                                     float *r,
                                     float *g,
                                     float *b);

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

color_err_t color_convert(color_t* color, color_type_t convert_to)
{
    if (color->type >= MAX_COLOR_TYPE || convert_to >= MAX_COLOR_TYPE) {
        return COLOR_ERR_TYPE;
    }

    if (!(0.0 <= color->r && color->r <= 1.0 &&
          0.0 <= color->g && color->g <= 1.0 &&
          0.0 <= color->b && color->b <= 1.0)) {
        return COLOR_ERR_LEVEL;
    }

    if (color->type == convert_to) {
        return COLOR_SUCCESS;
    }

    if (color->type == COLOR_TYPE_RGB) {
        if (convert_to == COLOR_TYPE_HSV) {
            _color_convert_rgb_to_hsv(color);
        } else if (convert_to == COLOR_TYPE_HSL) {
            _color_convert_rgb_to_hsl(color);
        }
    } else if (color->type == COLOR_TYPE_HSV) {
        if (convert_to == COLOR_TYPE_RGB) {
            _color_convert_hsv_to_rgb(color);
        } else if (convert_to == COLOR_TYPE_HSL) {
            _color_convert_hsv_to_hsl(color);
        }
    } else if (color->type == COLOR_TYPE_HSL) {
        if (convert_to == COLOR_TYPE_RGB) {
            _color_convert_hsl_to_rgb(color);
        } else if (convert_to == COLOR_TYPE_HSV) {
            _color_convert_hsl_to_hsv(color);
        }
    }

    return COLOR_SUCCESS;
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

static void _color_convert_rgb_to_hsv(color_t* color)
{
    float r = color->r;
    float g = color->g;
    float b = color->b;

    float cmax = FMAX3(r, g, b);
    float cmin = FMIN3(r, g, b);
    float delta = cmax - cmin;

    float h = _color_get_h_from_rgb(color, cmax, cmin);

    float s = 0.0;
    if (cmax <= 0.0001) {
        s = 0.0;
    } else {
        s = delta / cmax;
    }

    float v = cmax;

    color->type = COLOR_TYPE_HSV;
    color->h    = h;
    color->s    = s;
    color->v    = v;
}

static void _color_convert_rgb_to_hsl(color_t* color)
{
    float r = color->r;
    float g = color->g;
    float b = color->b;

    float cmax = FMAX3(r, g, b);
    float cmin = FMIN3(r, g, b);
    float delta = cmax - cmin;

    float h = _color_get_h_from_rgb(color, cmax, cmin);

    float l = (cmax + cmin)/2;

    float s = 0.0;
    if (delta <= 0.0001) {
        s = 0.0;
    } else {
        s = delta/(1.0f - fabsf(2 * l - 1));
    }

    color->type = COLOR_TYPE_HSL;
    color->h    = h;
    color->s    = s;
    color->l    = l;
}

static void _color_convert_hsv_to_rgb(color_t* color)
{
    float h = color->h;
    float s = color->s;
    float v = color->v;

    float c = v * s;
    float x = c * (1 - fabsf(fmodf(h * 6.0, 2.0) - 1));
    float m = v - c;

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    _color_get_rgb_from_hcxm(h, c, x, m, &r, &g, &b);

    color->type = COLOR_TYPE_RGB;
    color->r    = r;
    color->g    = g;
    color->b    = b;
}

static void _color_convert_hsv_to_hsl(color_t* color)
{
    float h_hsv = color->h;
    float s_hsv = color->s;
    float v_hsv = color->v;

    float h_hsl = h_hsv;
    float s_hsl = s_hsv * v_hsv;
    float l_hsl = (2.0 - s_hsv) * v_hsv;

    if (l_hsl <= 0.0001 || l_hsl >= 1.9999) {
        s_hsl = 0.0;
    }
    else {
        s_hsl /= (l_hsl <= 1.0) ? l_hsl : (2.0 - l_hsl);
    }
    l_hsl /= 2.0;

    color->type = COLOR_TYPE_HSL;
    color->h    = h_hsl;
    color->s    = s_hsl;
    color->l    = l_hsl;
}

static void _color_convert_hsl_to_rgb(color_t* color)
{
    float h = color->h;
    float s = color->s;
    float l = color->l;

    float c = (1.0 - fabsf(2.0 * l - 1)) * s;
    float x = c * (1.0 - fabsf(fmodf(h * 6.0, 2.0) - 1.0));
    float m = l - c / 2.0;

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    _color_get_rgb_from_hcxm(h, c, x, m, &r, &g, &b);

    color->type = COLOR_TYPE_RGB;
    color->r    = r;
    color->g    = g;
    color->b    = b;
}

static void _color_convert_hsl_to_hsv(color_t* color)
{
    float h_hsl = color->h;
    float s_hsl = color->s;
    float l_hsl = color->l;

    l_hsl *= 2.0;
    s_hsl *= (l_hsl <= 1.0) ? l_hsl : (2.0 - l_hsl);
    float h_hsv = h_hsl;
    float s_hsv = 0.0;
    if (l_hsl + s_hsl <= 0.0001) {
        s_hsv = 0.0;
    } else {
        s_hsv = (2.0 * s_hsl) / (l_hsl + s_hsl);
    }
    float v_hsv = (l_hsl + s_hsl) / 2.0;

    color->type = COLOR_TYPE_HSV;
    color->h    = h_hsv;
    color->s    = s_hsv;
    color->v    = v_hsv;
}

static float _color_get_h_from_rgb(color_t const * color, float cmax, float cmin)
{
    float r = color->r;
    float g = color->g;
    float b = color->b;

    float delta = cmax - cmin;

    float h = 0.0;
    if (delta <= 0.0001)
    {
        h = 0.0;
    } else {
        if (r >= cmax) {
            h = fmodf(((g - b)/delta), 6.0)/6.0;
        } else if (g >= cmax) {
            h = (((b - r)/delta) + 2.0)/6.0;
        } else if (b >= cmax) {
            h = (((r - g)/delta) + 4.0)/6.0;
        }
    }
    if (h < 0.0) {
        h = 1.0 + h;
    }

    return h;
}

static void _color_get_rgb_from_hcxm(float h,
                                     float c,
                                     float x,
                                     float m,
                                     float *r,
                                     float *g,
                                     float *b)
{
    uint32_t sextant = floorf(h * 6.0);

    switch (sextant) {
    case 0:
    case 6:
        *r = c + m;
        *g = x + m;
        *b = m;
        break;

    case 1:
        *r = x + m;
        *g = c + m;
        *b = m;
        break;

    case 2:
        *r = m;
        *g = c + m;
        *b = x + m;
        break;

    case 3:
        *r = m;
        *g = x + m;
        *b = c + m;
        break;

    case 4:
        *r = x + m;
        *g = m;
        *b = c + m;
        break;

    case 5:
        *r = c + m;
        *g = m;
        *b = x + m;
        break;
    } /* switch (sextant) */
}

/** @} addtogroup COLOR */
