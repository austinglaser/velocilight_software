#ifndef SOUNDPUDDLE_FRAMEBUFFER_UTILS_H
#define SOUNDPUDDLE_FRAMEBUFFER_UTILS_H

const uint16_t sector_strip_offsets[FB_STRIPS_PER_SECTOR];
uint16_t strip_position_offsets[FB_STRIP_NUM];


#define FB_LOGICAL_MAX FB_STRIP_LEN
#define FB_LOGICAL_MIN 0

#define FB_LED_CIRCLEBOARD_LOGICAL_MAX 39

#define FB_LED_CIRCLEBOARD_INCR_START FB_LOGICAL_MIN
#define FB_LED_CIRCLEBOARD_INCR_END   FB_LED_CIRCLEBOARD_LOGICAL_MAX
#define FB_LED_CIRCLEBOARD_DECR_START FB_LED_CIRCLEBOARD_LOGICAL_MAX
#define FB_LED_CIRCLEBOARD_DECR_END   FB_LOGICAL_MIN

#define FB_LED_STRIP_DECR_START FB_LOGICAL_MAX
#define FB_LED_STRIP_DECR_END   FB_LOGICAL_MIN
#define FB_LED_STRIP_INCR_START FB_LOGICAL_MIN
#define FB_LED_STRIP_INCR_END   FB_LOGICAL_MAX

#define FB_LED_IDX_SAFE_UPPERBOUND FB_LOGICAL_MAX - 1
#define FB_LED_IDX_SAFE_LOWERBOUND FB_LED_CIRCLEBOARD_INCR_END

#define FB_STRIP_INCR_START FB_LED_CIRCLEBOARD_INCR_END
#define FB_STRIP_INCR_END   FB_LOGICAL_MAX

#define LED_CONTROL_BYTE    0x000000FF

#define LED_OFF             LED_CONTROL_BYTE

#define BIT_SHIFT_R 0
#define BIT_SHIFT_B 16
#define BIT_SHIFT_G 8

#define BYTE_SHIFT_R(val) (val << BIT_SHIFT_R)
#define BYTE_SHIFT_G(val) (val << BIT_SHIFT_G)
#define BYTE_SHIFT_B(val) (val << BIT_SHIFT_B)

#define FB_TRANSFORM_STRIP_INCR_START 0
#define FB_CIRCLEBOARD_STRIP_BOUNDARY(strip) circleboard_strip_boundaries[strip]
#define FB_MIGRATE_OUT_TICK_BOUNDARY(strip)  migrate_out_tick_boundaries[strip]
#define FB_MIGRATE_OUT_NORM_BOUNDARY(strip)  migrate_out_norm_boundaries[strip]

#define FB_MIGRATE_IN_STRIP_INCR_START   FB_TRANSFORM_STRIP_INCR_START
#define FB_MIGRATE_IN_STRIP_INCR_END     FB_STRIP_NUM
#define FB_MIGRATE_IN_LED_INCR_CB_START  FB_TRANSFORM_STRIP_INCR_START
#define FB_MIGRATE_IN_LED_INCR_CB_END(strip) FB_CIRCLEBOARD_STRIP_BOUNDARY(strip)
#define FB_MIGRATE_IN_LED_INCR_ST_START  FB_MIGRATE_IN_LED_INCR_CB_END
#define FB_MIGRATE_IN_LED_INCR_ST_END    FB_STRIP_BUFFER_SIZE

#define FB_MIGRATE_OUT_STRIP_INCR_START   FB_TRANSFORM_STRIP_INCR_START
#define FB_MIGRATE_OUT_STRIP_INCR_END     FB_STRIP_NUM
#define FB_MIGRATE_OUT_LED_TICK_DECR_CB_START(strip) FB_MIGRATE_OUT_TICK_BOUNDARY(strip)
#define FB_MIGRATE_OUT_LED_TICK_DECR_CB_END(strip) FB_CIRCLEBOARD_STRIP_BOUNDARY(strip)
#define FB_MIGRATE_OUT_LED_DECR_CB_START(strip)  FB_CIRCLEBOARD_STRIP_BOUNDARY(strip)
#define FB_MIGRATE_OUT_LED_DECR_CB_END           FB_TRANSFORM_STRIP_INCR_START
#define FB_MIGRATE_OUT_LED_DECR_ST_START         FB_STRIP_BUFFER_SIZE - 1
#define FB_MIGRATE_OUT_LED_DECR_ST_END(strip)    FB_MIGRATE_OUT_NORM_BOUNDARY(strip)

const uint16_t sector_strip_offsets[FB_STRIPS_PER_SECTOR] = {
    0,                // Unused, zero index is variable
    12, 12, 4, 12, 12 // can we compute this in a more general fashion? my guess is no...
};

uint16_t strip_position_offsets[FB_STRIP_NUM] = {
    0,
};
static uint16_t unshift_offsets[FB_STRIP_NUM] = {
    0,
};
static uint16_t push_offsets[FB_STRIP_NUM] = {
    0,
};
static uint16_t circleboard_strip_boundaries[FB_STRIP_NUM] = {
    0,
};
static uint16_t migrate_out_tick_boundaries[FB_STRIP_NUM] = {
    0,
};
static uint16_t migrate_out_norm_boundaries[FB_STRIP_NUM] = {
    0,
};
static inline uint8_t strip_to_sector(uint8_t strip)
{
  return (strip / FB_STRIPS_PER_SECTOR);
}

static inline uint8_t strip_to_sector_strip(uint8_t strip)
{
  return (strip % FB_STRIPS_PER_SECTOR);
}

static inline uint8_t sector_strip0_offset(uint8_t sector)
{
  return ((sector > 0) ? ((sector % 3) > 0) ? 2 : 1 : 0);
}

static inline uint8_t sector_strip_offset(uint8_t sector, uint8_t sector_strip)
{
  return ((sector_strip > 0) ? sector_strip_offsets[sector_strip] : sector_strip0_offset(sector));
}

static inline uint8_t strip_offset(uint8_t strip)
{
  return sector_strip_offset(strip_to_sector(strip), strip_to_sector_strip(strip));
}

static inline uint16_t circleboard_strip_boundary(uint8_t strip)
{
  return (FB_LED_CIRCLEBOARD_LOGICAL_MAX - strip_offset(strip));
}

static inline uint16_t migrate_out_tick_boundary(uint8_t strip)
{
  return (FB_STRIP_LEN + 11 - strip_offset(strip));
}

static inline uint16_t migrate_out_norm_boundary(uint8_t strip)
{
  return (FB_STRIP_BUFFER_SIZE - 1 - strip_offset(strip));
}

static inline uint16_t adjust_position(uint8_t strip, uint16_t logical_position)
{
  return ((logical_position + strip_position_offsets[strip]) % (FB_LOGICAL_MAX));
}

static inline uint16_t push_offset(uint8_t strip)
{
  return (FB_STRIP_BUFFER_SIZE - strip_offset(strip));
}

static inline uint16_t strip_position_offset(uint8_t strip)
{
  return (FB_STRIP_BUFFER_SIZE - 1 - strip_offset(strip));
}

#endif
