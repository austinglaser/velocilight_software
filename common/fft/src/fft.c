
#include "fft.h"
#include <arm_math.h>
#include <arm_const_structs.h>

#include <stdbool.h>

static arm_rfft_instance_q15 real_q15;
//static arm_rfft_instance_q31 real_q31;

#if FFT_SAMPLE_SIZE == 4096
    #include "hamming_q15_len4096.h"
    static q15_t const * hamming_q15 = hamming_q15_len4096;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len4096;
#elif FFT_SAMPLE_SIZE == 2048
    #include "hamming_q15_len2048.h"
    static q15_t const * hamming_q15 = hamming_q15_len2048;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len2048;
#elif FFT_SAMPLE_SIZE == 1024
    #include "hamming_q15_len1024.h"
    static q15_t const * hamming_q15 = hamming_q15_len1024;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len1024;
#elif FFT_SAMPLE_SIZE == 512
    #include "hamming_q15_len512.h"
    static q15_t const * hamming_q15 = hamming_q15_len512;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len512;
#elif FFT_SAMPLE_SIZE == 256
    #include "hamming_q15_len256.h"
    static q15_t const * hamming_q15 = hamming_q15_len256;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len256;
#elif FFT_SAMPLE_SIZE == 128
    #include "hamming_q15_len128.h"
    static q15_t const * hamming_q15 = hamming_q15_len128;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len128;
#elif FFT_SAMPLE_SIZE == 64
    #include "hamming_q15_len64.h"
    static q15_t const * hamming_q15 = hamming_q15_len64;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len64;
#elif FFT_SAMPLE_SIZE == 32
    #include "hamming_q15_len32.h"
    static q15_t const * hamming_q15 = hamming_q15_len32;
    static arm_cfft_instance_f32 const * cfft_f32 = &arm_cfft_sR_f32_len32;
#else
    #error   Unsupported FFT size!
#endif

/** initialize fft structs
 *
 */
void fft_init(void)
{
    arm_rfft_init_q15(&real_q15, FFT_SAMPLE_SIZE, 0, 1);
}

/** apply a Hamming window to 16 bit audio sample
 *
 * @param[in] audio:   int16_t array of sample values
 */
static inline void fft_apply_hamming_16(q15_t *audio)
{
    static q15_t audio_deoffset[FFT_SAMPLE_SIZE];

    q15_t audio_offset;
    arm_mean_q15(audio, FFT_SAMPLE_SIZE, &audio_offset);
    arm_offset_q15(audio, -audio_offset, audio_deoffset, FFT_SAMPLE_SIZE);

    arm_mult_q15(audio_deoffset,
                 (q15_t *)hamming_q15,
                 audio,
                 FFT_SAMPLE_SIZE);
}

/** apply a Hamming window to 32 bit audio sample
 *
 * @param[in] audio:   int32_t array of sample values
 */
/*
static inline void fft_apply_hamming_32(int32_t *audio)
{
    uint32_t i;
    for (i = 0; i < FFT_SAMPLE_SIZE; i++)
    {
        audio[i] = ((q31_t)audio[i] * hamming[i]) >> 31;
    }
}
*/

/** execute a 16 bit fft and compute magnitude
 *
 * @param[in] audio_in:       int16_t array of audio data
 * @param[in] fft_mag_out:    uint16_t array of fft magnitudes
 */
void fft_execute_16(uint16_t *audio_in, float32_t * fft_mag_out)
{
    q15_t * audio_in_q = (q15_t *) audio_in;

    fft_apply_hamming_16(audio_in_q);

    static float32_t fft_buf[FFT_SAMPLE_SIZE*2];

    for (size_t i = 0; i < FFT_SAMPLE_SIZE; i++) {
        fft_buf[i*2]     = (float32_t) audio_in_q[i];
        fft_buf[i*2 + 1] = 0.0;
    }

    arm_cfft_f32(cfft_f32, fft_buf, false, true);
    arm_cmplx_mag_f32(fft_buf, fft_mag_out, FFT_SAMPLE_SIZE/2);
}

/** execute a 32 bit fft and compute magnitude
 *
 * @param[in] audio_in:       int32_t array of audio data
 * @param[in] fft_mag_out:    uint32_t array of fft magnitudes
 */
/*
void fft_execute_32(int32_t *audio_in, uint32_t *fft_mag_out)
{
    static uint32_t fft_buf[FFT_SAMPLE_SIZE * 2];

    fft_apply_hamming_32(audio_in);

    arm_rfft_q31(&real_q31, (q31_t *)audio_in, (q31_t *)fft_buf);

    arm_cmplx_mag_q31((q31_t *)fft_buf, (q31_t *)fft_mag_out, FFT_SAMPLE_SIZE);
}
*/
