#include "framebuffer.h"
#include "framebuffer_utils.h"

#include "util.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

FB_DECLARE() = {{0,},};

void framebuffer_migrate_in(uint32_t *values);
void framebuffer_migrate_out(uint32_t *values);
void framebuffer_migrate_out_decay(uint32_t *values);
void framebuffer_migrate_out_fast(uint32_t *values);
void framebuffer_migrate_out_fast_decay(uint32_t *values);

framebuffer_mode_s framebuffer_modes[FB_MODE_MAX] = {
    [FB_MODE_IN] = {
        .name = "Ripple In",
        .insert_values = framebuffer_migrate_in
    },
    [FB_MODE_OUT] = {
        .name = "Ripple Out",
        .insert_values = framebuffer_migrate_out
    },
    [FB_MODE_OUT_DECAY] = {
        .name = "Ripple Out (decay)",
        .insert_values = framebuffer_migrate_out_decay
    },
    [FB_MODE_OUT_FAST] = {
        .name = "Ripple Out (fast)",
        .insert_values = framebuffer_migrate_out_fast
    },
    [FB_MODE_OUT_FAST_DECAY] = {
        .name = "Ripple Out (fast, decay)",
        .insert_values = framebuffer_migrate_out_fast_decay
    },
};

static inline void framebuffer_init_offset_tables(void);
static inline void framebuffer_clear(void);

/** Initialize all framebuffer lookup tables/arrays
 *
 */
void framebuffer_init(void)
{
    framebuffer_init_offset_tables();
    framebuffer_clear();
}

/** Return an approximation of the array's power dissipation
 *
 * This approximation should be about linear.
 */
uint32_t framebuffer_power(void)
{
    uint8_t const * frame_bytes = (uint8_t *) frame_buffer;

    uint32_t power = 0;
    for (uint32_t i = 0; i < sizeof(frame_buffer); i++) {
        power += frame_bytes[i];
    }

    uint32_t offset = FB_STRIP_LEN * FB_STRIP_NUM * 0xFF;
    if (power > offset) {
        power -= offset;
    } else {
        power = 0;
    }

    return power;
}

static inline void framebuffer_decay_by(uint32_t * led, uint8_t decay);

/* Incrementally decreases the brightness across the entire array
 *
 * This universally reduces the brightness on all LEDs. It does not preserve
 * colors while doing this -- all color channels are dimmed evenly.
 * Furthermore, this is not a reversible operation (currently). It's intended
 * for use as a soft cap on overall power dissipation, to avoid either entering
 * a brownout state or shutting off the entire array.
 */
void framebuffer_backoff(void)
{
    uint32_t * frame_leds = (uint32_t *) frame_buffer;
    for (uint32_t i = 0; i < sizeof(frame_buffer)/4; i++) {
        framebuffer_decay_by(&frame_leds[i], 5);
    }
}

static inline void framebuffer_migrate_out_strips(bool decay);
static inline void framebuffer_migrate_out_values(uint32_t *values);

/** insert a new logical row at the center and shift
 *  to the edges of the led array
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_migrate_out(uint32_t *values)
{
    framebuffer_migrate_out_strips(false);
    framebuffer_migrate_out_values(values);
}

/** Insert a new logical row at the center, and shift it outwards
 *
 * Decays the colors towards black at a fixed rate.
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_migrate_out_decay(uint32_t *values)
{
    framebuffer_migrate_out_strips(true);
    framebuffer_migrate_out_values(values);
}

/** insert a new logical row at the center and shift
 *  to the edges of the led array
 *
 * Shifts outward at double the rate of @ref framebuffer_migrate_out
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_migrate_out_fast(uint32_t *values)
{
    for (uint32_t i = 0; i < FB_FAST_SPEEDUP; i++) {
        framebuffer_migrate_out_strips(false);
        framebuffer_migrate_out_values(values);
    }
}

/** insert a new logical row at the center and shift
 *  to the edges of the led array
 *
 * Shifts outward at double the rate of @ref framebuffer_migrate_out
 *
 * Decays the colors towards black at a fixed rate.
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_migrate_out_fast_decay(uint32_t *values)
{
    for (uint32_t i = 0; i < FB_FAST_SPEEDUP; i++) {
        framebuffer_migrate_out_strips(true);
        framebuffer_migrate_out_values(values);
    }
}

static inline void framebuffer_migrate_in_strips(void);
static inline void framebuffer_migrate_in_values(uint32_t *values);

/** Insert a new logical row at the rim and shift
 *  to the center of the led array
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_migrate_in(uint32_t *values)
{
    framebuffer_migrate_in_strips();
    framebuffer_migrate_in_values(values);
}

#if 0
static inline void framebuffer_spiral_out_strips(void);

/** Insert a new logical row at the center 
 *  and spiral to the rim of the led array
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_spiral_out(uint32_t *values)
{
    framebuffer_spiral_out_strips();
    framebuffer_migrate_out_values(values);
}

/** Insert a new logical row at the center 
 *  and spiral to the rim of the led array
 *
 * @param[in] values:   uint32_t array of color values
 */
void framebuffer_spiral_out_fast(uint32_t *values)
{
    framebuffer_spiral_out_strips();
    framebuffer_migrate_out_values(values);
    framebuffer_spiral_out_strips();
    framebuffer_migrate_out_values(values);
}
#endif

/** Initialize all the offset tables we use in framebuffer managment
 *  at a given strip position
 *
 * @param[in] strip:   strip index (0 <= strip < 72)
 */
static inline void initialize_offset_tables_at_strip_index(uint16_t strip)
{
    strip_position_offsets[strip] = strip_position_offset(strip);
    unshift_offsets[strip] = strip_position_offset(strip);
    push_offsets[strip] = push_offset(strip);
    circleboard_strip_boundaries[strip] = circleboard_strip_boundary(strip);
    migrate_out_tick_boundaries[strip] = migrate_out_tick_boundary(strip);
    migrate_out_norm_boundaries[strip] = migrate_out_norm_boundary(strip);
}

/** Initialize all the offset tables we use in framebuffer managment
 */
static inline void framebuffer_init_offset_tables(void)
{
    for (uint16_t i = 0; i < FB_STRIP_NUM; i++)
    {
        initialize_offset_tables_at_strip_index(i);
    }
}

/** Fill the framebuffer with off LEDs
 */
static inline void framebuffer_clear(void)
{
    for (uint32_t strip = 0; strip < FB_STRIP_NUM; strip++) {
        for (uint32_t led = 0; led < FB_STRIP_BUFFER_SIZE; led++) {
            FB_INDEX(strip, led) = LED_OFF;
        }
    }
}

/** set a single value in the framebuffer to desired logical position
 * 
 * @param[in] strip:              strip index (0 <= strip < 72)
 * @param[in] logical_position:   logical radial position (0 === center)
 * @param[in] value:              value to set
 */
static inline void framebuffer_set_value(uint8_t strip, uint16_t logical_position, uint32_t value)
{
    FB_INDEX( strip, adjust_position(strip, logical_position) ) = value;
}

/** set a single value in the framebuffer to logical zero position
 * 
 * @param[in] strip:              strip index (0 <= strip < 72)
 * @param[in] value:              value to unshift
 */
static inline void framebuffer_unshift_value(uint8_t strip, uint32_t value)
{
    uint32_t unshift_offset = unshift_offsets[strip];

#if FB_AVERAGE_WINDOW > 0
    uint8_t * value_bytes = (uint8_t *) &value;
    uint32_t acc_r = value_bytes[3];
    uint32_t acc_g = value_bytes[2];
    uint32_t acc_b = value_bytes[1];

    for (uint32_t i = 0; i < FB_AVERAGE_WINDOW; i++) {
        uint32_t led_index = (unshift_offset + i) % FB_STRIP_BUFFER_SIZE;
        uint8_t const * led_bytes = (uint8_t *) &(FB_INDEX(strip, led_index));
        acc_r += led_bytes[3];
        acc_g += led_bytes[2];
        acc_b += led_bytes[1];
    }

    acc_r /= FB_AVERAGE_WINDOW + 1;
    acc_g /= FB_AVERAGE_WINDOW + 1;
    acc_b /= FB_AVERAGE_WINDOW + 1;

    value_bytes[3] = acc_r;
    value_bytes[2] = acc_g;
    value_bytes[1] = acc_b;
#endif

    FB_INDEX(strip, unshift_offset) = value;
}

/** set a single value in the framebuffer to FB_LOGICAL_MAX position
 * 
 * @param[in] strip:              strip index (0 <= strip < 72)
 * @param[in] value:              value to push
 */
static inline void framebuffer_push_value(uint8_t strip, uint32_t value)
{
    FB_INDEX( strip, push_offsets[strip] ) = value;
}

/** Move all values at constant velocity from the exterior to the interior
 */
static inline void framebuffer_migrate_in_strips(void)
{
    for (uint16_t strip = 0; strip < FB_MIGRATE_IN_STRIP_INCR_END; strip++)
    {
        uint16_t led;

        for (led = FB_MIGRATE_IN_LED_INCR_CB_START; led < FB_MIGRATE_IN_LED_INCR_CB_END(strip); led++)
        {
            FB_INDEX(strip, led) = FB_INDEX(strip, led + 1) = FB_INDEX(strip, led + 2);
        }

        for (led = FB_MIGRATE_IN_LED_INCR_ST_START(strip); led < FB_MIGRATE_IN_LED_INCR_ST_END; led++)
        {
            FB_INDEX(strip, led) = FB_INDEX(strip, led + 1);
        }
    }
}

/** push an array of values into the framebuffer logical rim
 */
static inline void framebuffer_migrate_in_values(uint32_t *values)
{
    for (uint16_t i = 0; i < FB_STRIP_NUM; i++)
    {
        framebuffer_push_value(i, values[i]);
    }
}

static inline void framebuffer_decay_by(uint32_t * led, uint8_t decay)
{
    uint8_t * led_bytes = (uint8_t *) led;

    /* Byte 0 is the control byte; that shouldn't change */
    for (uint32_t i = 1; i < 4; i++) {
        if (led_bytes[i] > decay) {
            led_bytes[i] -= decay;
        } else {
            led_bytes[i] = 0;
        }
    }
}

/** Move all values at constant velocity from the center to the rim
 */
static inline void framebuffer_migrate_out_strips(bool decay)
{
    static uint8_t tick = 0;

    tick = ~tick;
    for (uint16_t strip = FB_MIGRATE_OUT_STRIP_INCR_START; strip < FB_MIGRATE_OUT_STRIP_INCR_END; strip++)
    {
        uint16_t led;

        if (tick)
            for (led = FB_MIGRATE_OUT_LED_TICK_DECR_CB_START(strip); led > FB_MIGRATE_OUT_LED_TICK_DECR_CB_END(strip); led--)
            {
                uint32_t prev_led = FB_INDEX(strip, led -1);
                if (decay && (led % (FB_DECAY_RATE/2) == 0)) {
                    framebuffer_decay_by(&prev_led, 1);
                }
                FB_INDEX(strip, led) = prev_led;
            }

        for (led = FB_MIGRATE_OUT_LED_DECR_CB_START(strip); led > FB_MIGRATE_OUT_LED_DECR_CB_END; led--)
        {
            uint32_t prev_led = FB_INDEX(strip, led -1);
            if (decay && (led % FB_DECAY_RATE == 0)) {
                framebuffer_decay_by(&prev_led, 1);
            }
            FB_INDEX(strip, led) = prev_led;
        }

        FB_INDEX( strip, 0 ) = FB_INDEX( strip, FB_STRIP_BUFFER_SIZE - 1 );

        for (led = FB_MIGRATE_OUT_LED_DECR_ST_START; led > FB_MIGRATE_OUT_LED_DECR_ST_END(strip); led--)
        {
            uint32_t prev_led = FB_INDEX(strip, led -1);
            if (decay && (led % FB_DECAY_RATE == 0)) {
                framebuffer_decay_by(&prev_led, 1);
            }
            FB_INDEX(strip, led) = prev_led;
        }
    }
}

/** push an array of values into the framebuffer logical center
 */
static inline void framebuffer_migrate_out_values(uint32_t *values)
{
    for (uint16_t strip = 0; strip < FB_STRIP_NUM; strip++)
    {
        framebuffer_unshift_value(strip, values[strip]);
    }
}
