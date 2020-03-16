#ifndef SOUNDPUDDLE_H
#define SOUNDPUDDLE_H

#include <framebuffer.h>
#include <music.h>

typedef struct soundpuddle_mode {
  framebuffer_mode_s const * framebuffer_mode;
  music_map_mode_s const * music_map_mode;
} soundpuddle_mode_s, * soundpuddle_mode_t;

extern uint16_t fft_mag_buffer[FFT_SAMPLE_LEN];
extern uint32_t strip_buffer[FB_STRIP_NUM];

void soundpuddle_run(soundpuddle_mode_t mode);
#endif // SOUNDPUDDLE_H
