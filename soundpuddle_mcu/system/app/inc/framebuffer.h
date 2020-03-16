/**@file    framebuffer.h
 * @author  Ryan Bennett <nomad.ry@gmail.com>
 * @brief   LED framebuffer for setting, shifting, and interpolating led values
 */

#ifndef SOUNDPUDDLE_FRAMEBUFFER_H
#define SOUNDPUDDLE_FRAMEBUFFER_H

#include <stdint.h>

typedef struct framebuffer_mode {
  char const * name;
  void (*insert_values)(uint32_t * values);
} framebuffer_mode_s, * framebuffer_mode_t;

enum FB_MODES {
  FB_MODE_IN,
  FB_MODE_OUT,
  FB_MODE_OUT_DECAY,
  FB_MODE_OUT_FAST,
  FB_MODE_OUT_FAST_DECAY,
  //FB_MODE_SPIRAL_IN,
  //FB_MODE_SPIRAL_OUT,
  FB_MODE_MAX
};

extern framebuffer_mode_s framebuffer_modes[FB_MODE_MAX];

#define FB_STRIP_LEN              40
#define FB_SECTOR_NUM             12
#define FB_STRIPS_PER_SECTOR      6
#define FB_STRIP_NUM              (FB_SECTOR_NUM * FB_STRIPS_PER_SECTOR)

/** How many times faster a _FAST mode goes than its regular counterpart */
#define FB_FAST_SPEEDUP           3

/** How many outward steps between led brightness reductions in _DECAY modes
 *
 * Must be >= 1.
 *
 * A value of 2 gives the fastest decay, and higher values decay more slowly.
 * Even values will give more consistent spatial decay between the circleboard
 * and the strips.
 */
#define FB_DECAY_RATE             16

/** Number of LEDs to average when inserting new values
 *
 * Higher values result in a slower-changing but smoother visualization.
 *
 * A value of 0 is acceptable and simply disables averaging
 */
#define FB_AVERAGE_WINDOW         0

#define FB_STRIP_BUFFER_SIZE (FB_STRIP_LEN + 23)

#define FB_STRIP_CONTINUOUS

#ifdef FB_STRIP_CONTINUOUS

# define FB_DECLARE() uint32_t __attribute__((section(".ram0"))) frame_buffer[FB_STRIP_NUM][FB_STRIP_BUFFER_SIZE]
# define FB_INDEX(strip, led) frame_buffer[strip][led]

#else

# define FB_DECLARE() uint32_t __attribute__((section(".ram0"))) frame_buffer[FB_STRIP_BUFFER_SIZE][FB_STRIP_NUM]
# define FB_INDEX(strip, led) frame_buffer[led][strip]

#endif

extern FB_DECLARE();

void framebuffer_init(void);

uint32_t framebuffer_power(void);

void framebuffer_backoff(void);

#endif
