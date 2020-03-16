#ifndef MUSICMAP_H
#define MUSICMAP_H

#include <stdint.h>
#include <fft.h>

#define FFT_SAMPLE_HZ   27439
#define FFT_SAMPLE_LEN  FFT_SAMPLE_SIZE
#define FFT_ACTIVE_LEN (FFT_SAMPLE_LEN * 2)
#define FFT_USABLE_LEN ((FFT_SAMPLE_LEN / 2) - 1)

typedef struct music_map_mode {
  char name[16];
  void (*accumulate_fft)(uint32_t * strips, uint16_t * fft);
} music_map_mode_s, * music_map_mode_t;

enum {
  MUSIC_MODE_CHROMATIC = 0,
  MUSIC_MODE_MONOTONIC,
  MUSIC_MODE_FIFTHS,
  MUSIC_MODE_MAX
};

extern const music_map_mode_s music_map_modes[MUSIC_MODE_MAX];

void music_map_initialize(void);

#endif // MUSICMAP_H
