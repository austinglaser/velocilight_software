#ifndef ARDUINO_HSV_H
#define ARDUINO_HSV_H

#include <stdint.h>

#define RGB_CONTROL_BYTE 0xFF // TODO
typedef struct sp_hsv {
  uint8_t h;
  uint8_t s;
  uint8_t v;
} sp_hsv_s, * sp_hsv_t;

typedef struct sp_rgb {
  uint8_t control;
  uint8_t b;
  uint8_t g;
  uint8_t r;
} sp_rgb_s, * sp_rgb_t;

typedef union sp_rgb_u_ {
  uint32_t packed;
  sp_rgb_s unpacked;
} sp_rgb_u, * sp_rgb_u_t;

void setLedColorHSV(sp_hsv_t hsv, sp_rgb_t rgb);

#endif
