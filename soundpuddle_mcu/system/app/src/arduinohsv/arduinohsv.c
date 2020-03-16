// modified for soundpuddle by Ryan Bennett
#include <arduinohsv.h>

void setLedColorHSV(sp_hsv_t hsv, sp_rgb_t rgb) {
  // this is the algorithm to convert from RGB to HSV
  uint8_t h = hsv->h;
  uint8_t s = hsv->s;
  uint8_t v = hsv->v;

  h = (h * 192) / 256;  // 0..191
  unsigned int i = h / 32;   // We want a value of 0 thru 5
  unsigned int f = (h % 32) * 8;   // 'fractional' part of 'i' 0..248 in jumps

  unsigned int sInv = 255 - s;  // 0 -> 0xff, 0xff -> 0
  unsigned int fInv = 255 - f;  // 0 -> 0xff, 0xff -> 0
  uint8_t pv = v * sInv / 256;  // pv will be in range 0 - 255
  uint8_t qv = v * (256 - s * f / 256) / 256;
  uint8_t tv = v * (256 - s * fInv / 256) / 256;

  switch (i) {
  case 0:
    rgb->r = v;
    rgb->g = tv;
    rgb->b = pv;
    break;
  case 1:
    rgb->r = qv;
    rgb->g = v;
    rgb->b = pv;
    break;
  case 2:
    rgb->r = pv;
    rgb->g = v;
    rgb->b = tv;
    break;
  case 3:
    rgb->r = pv;
    rgb->g = qv;
    rgb->b = v;
    break;
  case 4:
    rgb->r = tv;
    rgb->g = pv;
    rgb->b = v;
    break;
  case 5:
    rgb->r = v;
    rgb->g = pv;
    rgb->b = qv;
    break;
  }
}
