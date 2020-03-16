#ifndef FFT_H
#define FFT_H

#include <stdint.h>
#include <arm_math.h>

#ifndef FFT_SAMPLE_SIZE
#define FFT_SAMPLE_SIZE 4096
#endif

typedef struct dsp_mode {
  char name[16];
  void (*execute_fft)(uint16_t * audio_in, float32_t * fft_mag_out);
} dsp_mode_s, * dsp_mode_t;

enum {
  DSP_MODE_16 = 0,
  //DSP_MODE_32,
  DSP_MODE_MAX
};

void fft_execute_16(uint16_t * audio_in, float32_t * fft_mag_out);
//void fft_execute_32(uint16_t *audio_in, uint32_t *fft_mag_out);
void fft_init(void);

#endif // FFT_H
