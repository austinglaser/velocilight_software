/**@file    audio.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Audio Interface
 */

#ifndef AUDIO_H
#define AUDIO_H

/**@defgroup AUDIO Audio
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES ------------------------------------------------- */

/* Supporting modules */

/* Third-party headers */

/* Standard headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ---------------------------------------------------- */
/* --- PUBLIC DATATYPES ---------------------------------------------------- */
/* --- PUBLIC MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

/** Initialize the audio capture subsystem */
void audio_init(void);

/** Get the latest n available samples
 *
 * @p n must be less than the configured audio buffer size
 */
void audio_get(uint16_t * samples, size_t n);

/** @} defgroup AUDIO */

#endif /* ifndef AUDIO_H */
