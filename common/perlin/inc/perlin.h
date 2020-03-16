/// @file
/// @author  Austin Glaser <austin@boulderes.com>
/// @brief   Perlin Interface

#ifndef PERLIN_H
#define PERLIN_H

/// @defgroup PERLIN Perlin
/// @{
///
/// @brief

// --- PUBLIC DEPENDENCIES ------------------------------------------------- //

// Supporting modules

// Third-party headers

// Standard headers
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// --- PUBLIC CONSTANTS ---------------------------------------------------- //
// --- PUBLIC DATATYPES ---------------------------------------------------- //

/// Perlin state.
typedef struct {
    /// Permutation vector.
    uint8_t p[512];
} perlin_t;

// --- PUBLIC MACROS ------------------------------------------------------- //
// --- PUBLIC VARIABLES ---------------------------------------------------- //
// --- PUBLIC FUNCTIONS ---------------------------------------------------- //

/// Initialize a perlin engine.
///
/// Only needs to be called once per perlin usage.
///
/// Triggers an `ensure()` failure if @p perlin is NULL.
///
/// @param[out] perlin      Engine to be initialized. Must be non-NULL
/// @param[in] seed         Determines pseudorandom behavior.
void perlin_init(perlin_t * perlin, uint32_t seed);

/// Get the reference noise engine.
///
/// Always returns a reference to the same object.
///
/// @return     Reference perlin engine.
perlin_t const * perlin_reference(void);

/// Compute a noise value for a given point (@p x, @p y, @p z).
///
/// @param[in] perlin       Initialized engine
/// @param[in] x            X coordinate
/// @param[in] y            Y coordinate
/// @param[in] z            Z coordinate
///
/// @return     Noise magnitude for the point (x, y, z)
float perlin_noise(perlin_t const * perlin, float x, float y, float z);

/// Compute several @p octaves of noise at (@p x, @p y, @p z).
///
/// @param[in] perlin       Initialized engine
/// @param[in] x            X coordinate
/// @param[in] y            Y coordinate
/// @param[in] z            Z coordinate
/// @param[in] base_freq    Additional coordinate space scale factor.
/// @param[in] octaves      Number of noise octaves to consider. Must be >= 1.
///                         When 1, this function is identical to @ref
///                         perlin_noise
/// @param[in] persistence  Reduction factor for each octave. Must be in the
///                         range (0.0, 1.0].
///
///                         A value of 1.0 lends equal strength to each octave.
///                         Smaller values reduce that strength.
float perlin_noise_octaves(
    perlin_t const * perlin,
    float x,
    float y,
    float z,
    float base_freq,
    uint32_t octaves,
    float persistence
);

/// @} defgroup PERLIN

#endif // ifndef PERLIN_H
