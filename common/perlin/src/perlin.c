/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Perlin Implementation
///
/// @addtogroup PERLIN
/// @{
///
/// @defgroup PERLIN_PRIVATE Private Members
/// @{

// --- PRIVATE DEPENDENCIES ------------------------------------------------ //

// This module
#include "perlin.h"

// Supporting modules
#include "ensure.h"

// Third-party headers

// Standard headers
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// --- PRIVATE CONSTANTS --------------------------------------------------- //

/// Reference engine.
///
/// Source: https://mrl.nyu.edu/~perlin/noise.
static const perlin_t _PERLIN_REFERENCE = {
    .p = {
        151, 160, 137, 91,  90,  15,  131, 13,
        201, 95,  96,  53,  194, 233, 7,   225,
        140, 36,  103, 30,  69,  142, 8,   99,
        37,  240, 21,  10,  23,  190, 6,   148,
        247, 120, 234, 75,  0,   26,  197, 62,
        94,  252, 219, 203, 117, 35,  11,  32,
        57,  177, 33,  88,  237, 149, 56,  87,
        174, 20,  125, 136, 171, 168, 68,  175,
        74,  165, 71,  134, 139, 48,  27,  166,
        77,  146, 158, 231, 83,  111, 229, 122,
        60,  211, 133, 230, 220, 105, 92,  41,
        55,  46,  245, 40,  244, 102, 143, 54,
        65,  25,  63,  161, 1,   216, 80,  73,
        209, 76,  132, 187, 208, 89,  18,  169,
        200, 196, 135, 130, 116, 188, 159, 86,
        164, 100, 109, 198, 173, 186, 3,   64,
        52,  217, 226, 250, 124, 123, 5,   202,
        38,  147, 118, 126, 255, 82,  85,  212,
        207, 206, 59,  227, 47,  16,  58,  17,
        182, 189, 28,  42,  223, 183, 170, 213,
        119, 248, 152, 2,   44,  154, 163, 70,
        221, 153, 101, 155, 167, 43,  172, 9,
        129, 22,  39,  253, 19,  98,  108, 110,
        79,  113, 224, 232, 178, 185, 112, 104,
        218, 246, 97,  228, 251, 34,  242, 193,
        238, 210, 144, 12,  191, 179, 162, 241,
        81,  51,  145, 235, 249, 14,  239, 107,
        49,  192, 214, 31,  181, 199, 106, 157,
        184, 84,  204, 176, 115, 121, 50,  45,
        127, 4,   150, 254, 138, 236, 205, 93,
        222, 114, 67,  29,  24,  72,  243, 141,
        128, 195, 78,  66,  215, 61,  156, 180,
    }
};

// --- PRIVATE DATATYPES --------------------------------------------------- //
// --- PRIVATE MACROS ------------------------------------------------------ //
// --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- //

/// Shuffle an array of length @p len in-place
///
/// @param[in,out] array        Data to be shuffled. Must contain @p len
///                             elements.
/// @param[in] len              Elements in @p array
static void _perlin_shuffle(uint8_t * array, size_t len);

/// Fade a value between 0.0 and 1.0, inclusive.
///
/// Implements the function `6t^5 - 15t^4 + 10t^3`, as described in [Perlin's
/// improved noise paper](https://mrl.nyu.edu/~perlin/paper445.pdf). This has
/// the important advantage of a zero second-derivative at both 0 and 1.
///
/// Source: https://mrl.nyu.edu/~perlin/noise/
///
/// @param[in] t        Value to fade, in the range [0.0, 1.0]
static float _perlin_fade(float t);

/// Linearly interpolate betweein @p a and @p b.
///
/// @param[in] t        Interpolation fraction, in the range [0.0, 1.0]
/// @param[in] a        Value to use when @p t == 0
/// @param[in] b        Value to use when @p t == 1
static float _perlin_lerp(float t, float a, float b);

/// Compute the dot-product of (@p x, @p y, @p z) with a unit vector.
///
/// Selects the appropriate unit vector from the following list:
///
///     [
///         (1,1,0), (-1,1,0), (1,-1,0), (-1,-1,0),
///         (1,0,1), (-1,0,1), (1,0,-1), (-1,0,-1),
///         (0,1,1), (0,-1,1), (0,1,-1), (0,-1,-1),
///         (1,1,0), (-1,1,0), (0,-1,1), (0,-1,-1),
///     ]
///
/// based on the lowest-order 4 bits of @p hash.
///
/// @param[in] hash     Used to select unit vector
/// @param[in] x        X coordinate
/// @param[in] y        Y coordinate
/// @param[in] z        Z coordinate
static float _perlin_grad(uint8_t hash, float x, float y, float z);

// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PRIVATE VARIABLES --------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

void perlin_init(perlin_t * perlin, uint32_t seed) {
    ensure(perlin != NULL);

    srand(seed);

    for (size_t i = 0; i < sizeof(perlin->p) / 2; i++) {
        perlin->p[i] = i;
    }

    _perlin_shuffle(perlin->p, sizeof(perlin->p) / 2);

    for (size_t i = 0; i < sizeof(perlin->p) / 2; i++) {
        perlin->p[i + sizeof(perlin->p)/2] = perlin->p[i];
    }
}

perlin_t const * perlin_reference(void) {
    return &_PERLIN_REFERENCE;
}

float perlin_noise(perlin_t const * perlin, float x, float y, float z) {
    float floor_x = floorf(x);
    float floor_y = floorf(y);
    float floor_z = floorf(z);

    uint8_t bound_x = (uint8_t) floor_x;
    uint8_t bound_y = (uint8_t) floor_y;
    uint8_t bound_z = (uint8_t) floor_z;

    x -= floor_x;
    y -= floor_y;
    z -= floor_z;

    float u = _perlin_fade(x);
    float v = _perlin_fade(y);
    float w = _perlin_fade(z);

    uint8_t a = perlin->p[bound_x] + bound_y;
    uint8_t aa = perlin->p[a] + bound_z;
    uint8_t ab = perlin->p[a + 1] + bound_z;

    uint8_t b = perlin->p[bound_x + 1] + bound_y;
    uint8_t ba = perlin->p[b] + bound_z;
    uint8_t bb = perlin->p[b + 1] + bound_z;

    float grad_ruo = _perlin_grad(perlin->p[aa],     x,     y,     z);
    float grad_luo = _perlin_grad(perlin->p[ba],     x - 1, y,     z);
    float grad_rdo = _perlin_grad(perlin->p[ab],     x,     y - 1, z);
    float grad_ldo = _perlin_grad(perlin->p[bb],     x - 1, y - 1, z);
    float grad_rui = _perlin_grad(perlin->p[aa + 1], x,     y,     z - 1);
    float grad_lui = _perlin_grad(perlin->p[ba + 1], x - 1, y,     z - 1);
    float grad_rdi = _perlin_grad(perlin->p[ab + 1], x,     y - 1, z - 1);
    float grad_ldi = _perlin_grad(perlin->p[bb + 1], x - 1, y - 1, z - 1);

    float lerp_uo = _perlin_lerp(u, grad_ruo, grad_luo);
    float lerp_do = _perlin_lerp(u, grad_rdo, grad_ldo);
    float lerp_ui = _perlin_lerp(u, grad_rui, grad_lui);
    float lerp_di = _perlin_lerp(u, grad_rdi, grad_ldi);

    float lerp_o = _perlin_lerp(v, lerp_uo, lerp_do);
    float lerp_i = _perlin_lerp(v, lerp_ui, lerp_di);

    float noise = _perlin_lerp(w, lerp_o, lerp_i);

    // Sometimes (presumably due to rounding error), the noise may fall outside
    // the [0.0, 1.0] range. This simplisticly clips it back to that range.
    if (noise < 0.0) {
        noise = 0.0;
    }

    if (noise > 1.0) {
        noise = 1.0;
    }

    return noise;
}

float perlin_noise_octaves(
    perlin_t const * perlin,
    float x,
    float y,
    float z,
    float base_freq,
    uint32_t octaves,
    float persistence
) {
    // Borrowed from http://flafla2.github.io/2014/08/09/perlinnoise.html
    float total = 0.0;
    float frequency = 1.0;
    float amplitude = 1.0;
    float max_value = 0.0;

    for (uint32_t i = 0; i < octaves; i++) {
        total += perlin_noise(
            perlin,
            x * base_freq * frequency,
            y * base_freq * frequency,
            z * base_freq * frequency
        ) * amplitude;

        max_value += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }

    return total / max_value;
}

// --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- //

static void _perlin_shuffle(uint8_t * array, size_t len) {
    for (size_t i = 0; i < len; i++) {
            size_t j = i + rand() / (RAND_MAX / (len - i) + 1);
            uint8_t temp = array[j];
            array[j] = array[i];
            array[i] = temp;
    }
}

static float _perlin_fade(float t) {
    return t * t * t * (t * (t * 6 - 15.) + 10.);
}

static float _perlin_lerp(float t, float a, float b) {
    return a + t * (b - a);
}

static float _perlin_grad(uint8_t hash, float x, float y, float z) {
    switch (hash & 0xF) {

    case 0x0: return  x + y;
    case 0x1: return -x + y;
    case 0x2: return  x - y;
    case 0x3: return -x - y;
    case 0x4: return  x + z;
    case 0x5: return -x + z;
    case 0x6: return  x - z;
    case 0x7: return -x - z;
    case 0x8: return  y + z;
    case 0x9: return -y + z;
    case 0xA: return  y - z;
    case 0xB: return -y - z;
    case 0xC: return  y + x;
    case 0xD: return -y + z;
    case 0xE: return  y - x;
    case 0xF: return -y - z;

    default: return 0; // never happens

    }
}

/// @} defgroup PERLIN_PRIVATE
/// @} addtogroup PERLIN
