#include <music.h>
#include <music_utils.h>

#include <arm_math.h>

void music_map_chromatic(uint32_t * strips, uint16_t * fft);
void music_map_fifths(uint32_t * strips, uint16_t * fft);
void music_map_monotonic(uint32_t * strips, uint16_t * fft);

const music_map_mode_s music_map_modes[MUSIC_MODE_MAX] = {
  [MUSIC_MODE_CHROMATIC] = {
    .name = "Chromatic",
    .accumulate_fft = music_map_chromatic
  },
  [MUSIC_MODE_MONOTONIC] = {
    .name = "Monotonic",
    .accumulate_fft = music_map_monotonic
  },
  [MUSIC_MODE_FIFTHS] = {
    .name = "Circle o Fifths",
    .accumulate_fft = music_map_fifths
  }
};

/** accumulate logarithmic ranges of fft magnitudes 
 *  accorting to provided strip_map
 *
 * @param[in] strips:          the target buffer of led strips to map to  
 * @param[in] tone_strip_map:  mapping of note/octave pairs to strips (chromatic, monotonic, COF)
 * @param[in] fft:             fft magnitudes
 * @param[in] fft_len:         fft length
 */
static inline void accumulate_ranges(uint32_t * strips, uint32_t tone_strip_map[OCTAVES_MAX][NOTES_MAX], const uint16_t * fft)
{
  uint32_t octave;
  uint32_t note;
  uint32_t next_bound = 0;
  uint32_t i = 0;
  for (octave = 0; octave < OCTAVES_MAX; octave++){
    for (note = NOTES_MIN; note < NOTES_MAX; note++){
      uint32_t * strip = strips + tone_strip_map[octave][note];
      i = next_bound;
      next_bound = bound_map[octave][note];
      q15_t acc;
      uint32_t index;
      if (next_bound >= FFT_USABLE_LEN) next_bound = FFT_USABLE_LEN;
      arm_max_q15 ((q15_t *)&(fft[i]), next_bound - i, &acc, &index);
      strip[0] = acc;

    }
  }
}

/** accumulate logarithmic ranges of fft magnitudes 
 *  accorting to chromatic circle (1 octave per time around circle)
 *
 * @param[in] strips:          the target buffer of led strips to map to  
 * @param[in] fft:             fft magnitudes
 * @param[in] fft_len:         fft length
 */
void music_map_chromatic(uint32_t * strips, uint16_t * fft)
{
  accumulate_ranges(strips, tone_strip_map_chromatic, fft);
}

/** accumulate logarithmic ranges of fft magnitudes 
 *  accorting to circle of fifths
 *
 * @param[in] strips:          the target buffer of led strips to map to  
 * @param[in] fft:             fft magnitudes
 * @param[in] fft_len:         fft length
 */
void music_map_fifths(uint32_t * strips, uint16_t * fft)
{
  accumulate_ranges(strips, tone_strip_map_fifths, fft);
}

/** accumulate logarithmic ranges of fft magnitudes 
 *  accorting to chromatic circle (1 note == one strip incriment)
 *
 * @param[in] strips:          the target buffer of led strips to map to  
 * @param[in] fft:             fft magnitudes
 * @param[in] fft_len:         fft length
 */
void music_map_monotonic(uint32_t * strips, uint16_t * fft)
{
  accumulate_ranges(strips, tone_strip_map_monotonic, fft);
}

/** accumulate logarithmic ranges of fft magnitudes 
 *  accorting to chromatic circle (1 octave per time around circle)
 *
 * @param[in] strips:          the target buffer of led strips to map to  
 * @param[in] fft:             fft magnitudes
 * @param[in] fft_len:         fft length
 */
void music_map_initialize(void)
{
  uint8_t octave;
  uint8_t note;
  for (octave = 0; octave < OCTAVES_MAX; octave++){
    for (note = NOTES_MIN; note < NOTES_MAX; note++){
      tone_strip_map_chromatic[octave][note] = get_strip_chromatic(octave, note);
      tone_strip_map_fifths[octave][note] = get_strip_fifths(octave,note);
      tone_strip_map_monotonic[octave][note] = get_strip_monotonic(octave,note);
      bound_map[octave][note] = get_next_bound(octave, note, FFT_SAMPLE_LEN);
    }
  }
}
