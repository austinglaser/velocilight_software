#ifndef MUSIC_UTILS_H
#define MUSIC_UTILS_H

#define FFT_MAX_INDEX   FFT_SAMPLE_LEN / 2
#define FFT_MAX_HZ      FFT_SAMELE_HZ  / 2
#define FFT_HZ_AT(idx)  (idx * FFT_SAMPLE_HZ / FFT_SAMPLE_LEN)
#define OCTAVES_MAX     9
#define NOTES_MIN       12
#define NOTES_MAX       24

static uint32_t bound_map[OCTAVES_MAX][NOTES_MAX] = {{0,},};
static uint32_t tone_strip_map_chromatic[OCTAVES_MAX][NOTES_MAX] = {{0,},};
static uint32_t tone_strip_map_fifths[OCTAVES_MAX][NOTES_MAX] = {{0,},};
static uint32_t tone_strip_map_monotonic[OCTAVES_MAX][NOTES_MAX] = {{0,},};

/** return the sector (0 <= x < 12) of the octave and note in chromatic circle
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint8_t get_sector_chromatic(uint32_t note)
{
  return (note - 12);
}

/** return the strip index (0 <= x < 12) of the octave and note in chromatic circle
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint8_t get_strip_chromatic(uint32_t octave, uint32_t note)
{
  return ((get_sector_chromatic(note) * 6) + (octave % 6));
}

/** return the sector (0 <= x < 12) of the octave and note in the circle of fifths
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint8_t get_sector_fifths(uint32_t note)
{
  return (((note - 12) * 7) % 12);
}

/** return the strip index (0 <= x < 12) of the octave and note in circle of fifths
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint8_t get_strip_fifths( uint32_t octave, uint32_t note)
{
  return ((get_sector_fifths(note) * 6) + (octave % 6));
}

/** return the sector (0 <= x < 12) of the octave and note in monotonic circle
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint8_t get_strip_monotonic( uint32_t octave, uint32_t note)
{
  return (((octave * 12) + (note - 12)) % 72);
}

/** return the next upper bound of fft bin for the given octave and note
 *
 * @param[in] octave: octave
 * @param[in] note:   note
 */
static inline uint32_t get_next_bound(uint32_t octave, uint32_t note, uint32_t fft_len)
{
  uint32_t calc = ((note + 1 ) << octave);
  return  ((calc < fft_len) ? calc : fft_len);
}



#endif // MUSIC_UTILS
