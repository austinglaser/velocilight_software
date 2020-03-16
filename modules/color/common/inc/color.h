/**@file    color.h
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   Floating-point color library interface
 */

#ifndef COLOR_H_
#define COLOR_H_

/**@defgroup COLOR Color Manipulation
 * @{
 *
 * Library for manipulation of colors
 *
 * Provides data types and functions for storing and manipulating color representations
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */
/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/** The different color encodings which are available */
typedef enum {
    COLOR_TYPE_RGB      = 0x00,     /**< Color represented by red, green, and blue levels */
    COLOR_TYPE_HSV,                 /**< Color represented by hue, saturation, anc value */
    COLOR_TYPE_HSL,                 /**< Color represented by hue, saturation, and luminance */
    MAX_COLOR_TYPE,                 /**< Total number of implemented color types */
    COLOR_TYPE_INVALID              /**< Invalid color type */
} color_type_t;

/** Return values from color operations */
typedef enum {
    COLOR_SUCCESS       = 0x00,     /**< Color manipulation was successful */
    COLOR_ERR_TYPE,                 /**< A color has invalid @see color_type_t "type" */
    COLOR_ERR_LEVEL,                /**< A color field has an invalid value */
    MAX_COLOR_ERR,                  /**< Total number of color errors */
    COLOR_ERR_INVALID               /**< Invalid color error */
} color_err_t;

/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure encoding a color
 *
 * @note    All channels are stored as floating point values, in the range [0.0, 1.0]
 */
typedef struct {
    color_type_t type;          /**< The current color encoding type */
    union {
        float r;                /**< RGB red [0.0, 1.0] */
        float h;                /**< HSL/HSV hue [0.0, 1.0] */
    };
    union {
        float g;                /**< RGB green [0.0, 1.0] */
        float s;                /**< HSL/HSV saturation [0.0, 1.0] */
    };
    union {
        float b;                /**< RGB blue [0.0, 1.0] */
        float v;                /**< HSV value [0.0, 1.0] */
        float l;                /**< HSL lightness [0.0, 1.0] */
    };
} color_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */

/** Initialize a variable of type @ref color_type_t to be RGB
 *
 * @param[in] r_level:      Level for the red channel [0.0, 1.0]
 * @param[in] g_level:      Level for the green channel [0.0, 1.0]
 * @param[in] b_level:      Level for the blue channel [0.0, 1.0]
 *
 * @return  An appropriate initializer
 */
#define COLOR_RGB_INIT(r_level, g_level, b_level)   {                           \
                                                        .type = COLOR_TYPE_RGB, \
                                                        .r = (r_level),         \
                                                        .g = (g_level),         \
                                                        .b = (b_level),         \
                                                    }

/** Initialize a variable of type @ref color_type_t to be HSV
 *
 * @param[in] h_level:      Level for the hue channel [0.0, 1.0]
 * @param[in] s_level:      Level for the saturation channel [0.0, 1.0]
 * @param[in] v_level:      Level for the value channel [0.0, 1.0]
 *
 * @return  An appropriate initializer
 */
#define COLOR_HSV_INIT(h_level, s_level, v_level)   {                           \
                                                        .type = COLOR_TYPE_HSV, \
                                                        .h = (h_level),         \
                                                        .s = (s_level),         \
                                                        .v = (v_level),         \
                                                    }

/** Initialize a variable of type @ref color_type_t to be HSL
 *
 * @param[in] h_level:      Level for the hue channel [0.0, 1.0]
 * @param[in] s_level:      Level for the saturation channel [0.0, 1.0]
 * @param[in] l_level:      Level for the lightness channel [0.0, 1.0]
 *
 * @return  An appropriate initializer
 */
#define COLOR_HSL_INIT(h_level, s_level, l_level)   {                           \
                                                        .type = COLOR_TYPE_HSL, \
                                                        .h = (h_level),         \
                                                        .s = (s_level),         \
                                                        .l = (l_level),         \
                                                    }

/** Gets a three-character string to represent the color's type
 *
 * @param[in] color:        Color to examine
 *
 * @return          An appropriate type string, or "???" if the type is invalid
 */
#define COLOR_TYPE_STR(color)   (                                              \
                                    ((color).type == COLOR_TYPE_RGB) ? "rgb" : \
                                    ((color).type == COLOR_TYPE_HSV) ? "hsv" : \
                                    ((color).type == COLOR_TYPE_HSL) ? "hsl" : \
                                    "???"                                      \
                                )

/** A printf format specifier for printing a color
 *
 * Should be used similar to the following:
 *
 *     printf("color x: " PRIcolor_t ", color y: " PRIcolor_t "\n",
 *            PRIVARcolor_t(x),
 *            PRIVARcolor_t(y));
 *
 * @see PRIVARcolor_t
 */
#define PRIcolor_t              "[%s]%c:%f,%c:%f,%c:%f"

/** Expose @p color's fields for @ref PRIcolor_t
 *
 * @param[in] color:    The color to be printed
 *
 * @see PRIcolor_t
 */
#define PRIVARcolor_t(color)    COLOR_TYPE_STR(color),    \
                                COLOR_TYPE_STR(color)[0], \
                                (color).r,                \
                                COLOR_TYPE_STR(color)[1], \
                                (color).g,                \
                                COLOR_TYPE_STR(color)[2], \
                                (color).b

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** Convert @p color from its current type to @p conver_to
 *
 * Infers the current color type from the input parameter
 *
 * @param[in,out] color:    Pointer to color to be converted
 * @param[in] convert_to:   The type to change color to
 *
 * @retval COLOR_SUCCESS:   The conversion was successful
 * @retval COLOR_ERR_TYPE:  The input or conversion type was invalid
 * @retval COLOR_ERR_LEVEL: One or more of the levels in color is invalid
 */
color_err_t color_convert(color_t* color, color_type_t convert_to);

/** @} defgroup COLOR */

#endif //ifndef COLOR_H_
