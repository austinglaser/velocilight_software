#include <soundpuddle.h>

#include <array.h>
#include <audio.h>
#include <fft.h>
#include <led_colors.h>
#include <string.h>
#include <util.h>

uint16_t audio_sample_buffer[FFT_SAMPLE_LEN] __attribute__((aligned(0x1000))) = {0,};
uint16_t fft_mag_buffer[FFT_SAMPLE_LEN] __attribute__((aligned(0x1000))) = {0,};
uint32_t strip_buffer[FB_STRIP_NUM] __attribute__((aligned(0x1000))) = {0,};

void clear_16(uint16_t * array, size_t len)
{
  size_t i = 0;
  for (; i < len; i++) array[i] = 0;
}

void clear_32(uint32_t * array, size_t len)
{
  size_t i = 0;
  for (; i < len; i++) array[i] = 0;
}

static inline void soundpuddle_process_sample(uint16_t * audio, soundpuddle_mode_t mode)
{
  memset(strip_buffer,0,sizeof(audio));
  memset(strip_buffer,0, sizeof(strip_buffer));
  memset(fft_mag_buffer,0, sizeof(fft_mag_buffer));
  fft_execute_16(audio, fft_mag_buffer);
  mode->music_map_mode->accumulate_fft(strip_buffer, fft_mag_buffer);
  led_colors_map(strip_buffer);
  mode->framebuffer_mode->insert_values(strip_buffer);
}

void soundpuddle_run(soundpuddle_mode_t mode)
{
  audio_get(audio_sample_buffer, ARRAY_ELEMENTS(audio_sample_buffer));
  soundpuddle_process_sample(audio_sample_buffer, mode);
  array_write();
}
