#include <stdint.h>
#include <led_colors.h>
#include <soundpuddle.h>

sp_rgb_u led_colors_hsv_table[256] = {{0,},};

uint8_t scale_shift_16[16] = {
  8, 7,
  7, 6,
  6, 5,
  5, 4,
  4, 3,
  3, 2,
  2, 1,
  1, 0 //  adjust bottom to intentionally cut off low values
};

uint8_t scale_shift_32[32] = {
  24, 23, 22, 21,
  21, 20, 19, 18,
  18, 17, 16, 15,
  15, 14, 13, 12,
  12, 11, 10, 9,
  9, 8, 7, 6,
  6, 5, 4, 3,
  3, 2, 1, 0 // adjust bottom to intentionally cut off low values
};

static inline uint32_t value_scale_down_16(uint32_t mag)
{
  return (mag >> (scale_shift_16[ __builtin_clz( mag ) ] ));
}

void led_colors_init(void)
{
  uint16_t i;
  led_colors_hsv_table[0].unpacked.control = RGB_CONTROL_BYTE;
  sp_hsv_s hsv = {
    .h = 0,
    .s = 255,
    .v = 5
  };
  for (i = 1; i < 256; i++) {
    led_colors_hsv_table[i].unpacked.control = RGB_CONTROL_BYTE;
    hsv.h = i;
    setLedColorHSV(&hsv, &(led_colors_hsv_table[i].unpacked));
  }
}

void led_colors_map(uint32_t * strips)
{
  uint8_t i = 0;
  for (; i < FB_STRIP_NUM; i++) {
    uint8_t _i = (uint8_t) value_scale_down_16(strips[i]);
    strips[i] = led_colors_hsv_table[_i].packed;
  }
}

