/**@file    array.c
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Array Source
 *
 * @addtogroup ARRAY
 * @{
 *
 * @defgroup ARRAY_PRIVATE Array Private Members
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------ */

/* This module */
#include "array.h"
#include "arrayconf.h"

/* Supporting modules */
#include "ensure.h"
#include "framebuffer.h"
#include "util.h"

/* Third-party headers */
#include "hal.h"

/* Standard headers */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PRIVATE DATATYPES --------------------------------------------------- */

/** A set of LEDs all driven by one FPGA */
typedef struct {
    array_config_t const * config;
} array_t;

/* --- PRIVATE MACROS ------------------------------------------------------ */

/** Number of start frames per strip
 *
 * Should almost always be 1
 */
#define ARRAY_START_NUM     1

/** Number of stop frames per strip
 *
 * Should be equal to the ceil(N_LEDS / 64)
 */
#define ARRAY_STOP_NUM      4

/** Number of unused LEDs at the end of a string
 *
 * These are LEDS that should be logically driven (to be off), but that the
 * framebuffer isn't aware of.
 */
#define ARRAY_UNUSED_NUM    64

/* --- PRIVATE FUNCTION PROTOTYPES ----------------------------------------- */

static void _array_send_pair(void const * buf0, void const * buf1, size_t n);

/** Callback for the end of an SPI frame
 *
 * Signals a semaphore each time it is called. Ignores the spi driver pointer.
 */
static void _spi_frame_done(SPIDriver * spip);

/* --- PRIVATE CONSTANTS --------------------------------------------------- */

/** Word signalling the start of an LED frame */
#define START_FRAME         0x00000000

/** Word signalling the stop of an LED frame
 *
 * @note    The actual value here doesn't matter (though this matches the
 *          datasheet); instead, what matters is the extra clock cycles
 */
#define STOP_FRAME          0x00000000

/** Configuration for LED SPI interface */
static const SPIConfig _array_spi_config = {
    .end_cb = _spi_frame_done,
    .cr1    = SPI_CR1_BR_0 | SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA,
    .cr2    = 0,
};

static const uint32_t _starts[ARRAY_START_NUM]
                = { [0 ... ARRAY_START_NUM - 1] = START_FRAME };

static const uint32_t _stops[ARRAY_STOP_NUM]
                = { [0 ... ARRAY_STOP_NUM - 1]  = STOP_FRAME };

static const uint32_t _black[FB_STRIP_LEN + ARRAY_UNUSED_NUM]
                = { [0 ... FB_STRIP_LEN - 1]  = 0x000000FF };

static const array_config_t array_config = {
    .spi0         = &SPID1,
    .spi1         = &SPID4,

    .spi0_mosi    = PAL_LINE(GPIOA, SPI0_MOSI_PIN),
    .spi0_mosi_af = SPI0_MOSI_AF,
    .spi0_sck     = PAL_LINE(GPIOA, SPI0_SCK_PIN),
    .spi0_sck_af  = SPI0_SCK_AF,

    .spi1_mosi    = PAL_LINE(GPIOE, SPI1_MOSI_PIN),
    .spi1_mosi_af = SPI1_MOSI_AF,
    .spi1_sck     = PAL_LINE(GPIOE, SPI1_SCK_PIN),
    .spi1_sck_af  = SPI1_SCK_AF,

    .b0_b2_act = PAL_LINE(GPIOG, B0_B2_ACT),
    .b1_b3_act = PAL_LINE(GPIOD, B1_B3_ACT),
    .strip_act = {
        [0]  = PAL_LINE(GPIOD, STRIP_ACT_0),
        [1]  = PAL_LINE(GPIOD, STRIP_ACT_1),
        [2]  = PAL_LINE(GPIOE, STRIP_ACT_2),
        [3]  = PAL_LINE(GPIOD, STRIP_ACT_3),
        [4]  = PAL_LINE(GPIOE, STRIP_ACT_4),
        [5]  = PAL_LINE(GPIOE, STRIP_ACT_5),
        [6]  = PAL_LINE(GPIOE, STRIP_ACT_6),
        [7]  = PAL_LINE(GPIOE, STRIP_ACT_7),
        [8]  = PAL_LINE(GPIOD, STRIP_ACT_8),
        [9]  = PAL_LINE(GPIOD, STRIP_ACT_9),
        [10] = PAL_LINE(GPIOD, STRIP_ACT_10),
        [11] = PAL_LINE(GPIOD, STRIP_ACT_11),
        [12] = PAL_LINE(GPIOD, STRIP_ACT_12),
        [13] = PAL_LINE(GPIOF, STRIP_ACT_13),
        [14] = PAL_LINE(GPIOF, STRIP_ACT_14),
        [15] = PAL_LINE(GPIOF, STRIP_ACT_15),
        [16] = PAL_LINE(GPIOF, STRIP_ACT_16),
        [17] = PAL_LINE(GPIOF, STRIP_ACT_17),
    },
    .frame_buffer = frame_buffer,
};

static const uint32_t _strip_order[ARRAY_STRIP_NUM/2] = {
    0,  35,
    1,  34,
    2,  33,
    3,  32,
    4,  31,
    5,  30,
    6,  29,
    7,  28,
    8,  27,
    9,  26,
    10, 25,
    11, 24,
    12, 23,
    13, 22,
    14, 21,
    15, 20,
    16, 19,
    17, 18,
};

/* --- PUBLIC VARIABLES ---------------------------------------------------- */
/* --- PRIVATE VARIABLES --------------------------------------------------- */

/** Logical handle for the entire array */
static array_t array;

/** Semaphore signalled when an SPI channel has completed its write */
static SEMAPHORE_DECL(_spi_frame_done_sem, 0);

/* --- PUBLIC FUNCTIONS ---------------------------------------------------- */

void array_init(void)
{   
    array.config = &array_config;

    /* Configure mux lines */
    palSetLineMode(array.config->b0_b2_act, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->b0_b2_act);
    palSetLineMode(array.config->b1_b3_act, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->b1_b3_act);

    for (uint32_t strip = 0; strip < ARRAY_STRIP_NUM/4; strip++) {
        palSetLineMode(array.config->strip_act[strip], PAL_MODE_OUTPUT_PUSHPULL);
        palClearLine(array.config->strip_act[strip]);
    }

    /* Clear all latched lines */
    palSetLineMode(array.config->spi0_mosi, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->spi0_mosi);
    palSetLineMode(array.config->spi0_sck, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->spi0_mosi);
    palSetLineMode(array.config->spi1_mosi, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->spi1_mosi);
    palSetLineMode(array.config->spi1_sck, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->spi1_mosi);

    palSetLine(array.config->b0_b2_act);
    palSetLine(array.config->b1_b3_act);
    for (uint32_t strip = 0; strip < ARRAY_STRIP_NUM/4; strip++) {
        palSetLine(array.config->strip_act[strip]);
    }

    chThdSleepMicroseconds(1);

    palClearLine(array.config->b0_b2_act);
    palClearLine(array.config->b1_b3_act);
    for (uint32_t strip = 0; strip < ARRAY_STRIP_NUM/4; strip++) {
        palClearLine(array.config->strip_act[strip]);
    }

    /* Configure SPI busses */
    spiStart(array.config->spi0, &_array_spi_config);
    spiStart(array.config->spi1, &_array_spi_config);
    palSetLineMode(array.config->spi0_mosi,
                   PAL_MODE_ALTERNATE(array.config->spi0_mosi_af));
    palSetLineMode(array.config->spi0_sck,
                   PAL_MODE_ALTERNATE(array.config->spi0_sck_af));
    palSetLineMode(array.config->spi1_mosi,
                   PAL_MODE_ALTERNATE(array.config->spi1_mosi_af));
    palSetLineMode(array.config->spi1_sck,
                   PAL_MODE_ALTERNATE(array.config->spi1_sck_af));
}

void array_write(void)
{
    /*
     * The SPI driver uses DMA, which doesn't play nice with caching -- it's
     * another master on the memory bus, so memory coherency rears its ugly head.
     *
     * One solution to this problem would be to put the framebuffer in
     * non-cacheable RAM, but that entails a significant performance hit. By
     * manually flushing the cache to memory before writing a frame, we enforce
     * coherency while still possibly reaping performance benefits from the
     * cache during the frame manipulation cycle.
     */
    SCB_CleanInvalidateDCache();

    static bool tick;

    tick = !tick;

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(_strip_order)/2; i++) {
        uint32_t strip          = _strip_order[i*2 + tick];
        uint32_t quadrant_strip = strip % (ARRAY_STRIP_NUM/4);

        ensure(strip < ARRAY_STRIP_NUM/2);

        if (strip < ARRAY_STRIP_NUM/4) {
            palSetLine(array.config->b0_b2_act);
        } else {
            palSetLine(array.config->b1_b3_act);
        }


        palSetLine(array.config->strip_act[quadrant_strip]);

        _array_send_pair(_starts, _starts, sizeof(_starts));
        _array_send_pair(array.config->frame_buffer[strip],
                         array.config->frame_buffer[strip + ARRAY_STRIP_NUM/2],
                         FB_STRIP_LEN*sizeof(uint32_t));
        _array_send_pair(_black, _black, ARRAY_UNUSED_NUM*sizeof(uint32_t));
        _array_send_pair(_stops, _stops, sizeof(_stops));

        palSetLineMode(array.config->spi0_mosi, PAL_MODE_OUTPUT_PUSHPULL);
        palSetLineMode(array.config->spi1_mosi, PAL_MODE_OUTPUT_PUSHPULL);
        palClearLine(array.config->spi0_mosi);
        palClearLine(array.config->spi1_mosi);

        osalThreadSleepMicroseconds(1);

        palClearLine(array.config->strip_act[quadrant_strip]);
        palClearLine(array.config->b0_b2_act);
        palClearLine(array.config->b1_b3_act);

        osalThreadSleepMicroseconds(1);

        palSetLineMode(array.config->spi0_mosi,
                       PAL_MODE_ALTERNATE(array.config->spi0_mosi_af));
        palSetLineMode(array.config->spi1_mosi,
                       PAL_MODE_ALTERNATE(array.config->spi1_mosi_af));
    }

#if SINGLE_STEP
    /* Wait for button press and release */
    while (palReadLine(LINE_ENCODER_SW) == PAL_LOW);
#endif
    while (palReadLine(LINE_ENCODER_SW) == PAL_HIGH);
}

void array_clear(void)
{
    palSetLine(array.config->b0_b2_act);
    palSetLine(array.config->b1_b3_act);
    for (uint32_t i = 0; i < ARRAY_ELEMENTS(array.config->strip_act); i++) {
        palSetLine(array.config->strip_act[i]);
    }

    _array_send_pair(_starts, _starts, sizeof(_starts));
    _array_send_pair(_black,  _black,  sizeof(_black));
    _array_send_pair(_stops,  _stops,  sizeof(_stops));

    palSetLineMode(array.config->spi0_mosi, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(array.config->spi1_mosi, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(array.config->spi0_mosi);
    palClearLine(array.config->spi1_mosi);

    osalThreadSleepMicroseconds(1);

    palSetLineMode(array.config->spi0_mosi, PAL_MODE_ALTERNATE(array.config->spi0_mosi_af));
    palSetLineMode(array.config->spi1_mosi, PAL_MODE_ALTERNATE(array.config->spi1_mosi_af));

    for (uint32_t i = 0; i < ARRAY_ELEMENTS(array.config->strip_act); i++) {
        palClearLine(array.config->strip_act[i]);
    }
    palClearLine(array.config->b0_b2_act);
    palClearLine(array.config->b1_b3_act);
}

/* --- PRIVATE FUNCTION DEFINITIONS ---------------------------------------- */

static void _array_send_pair(void const * buf0, void const * buf1, size_t n)
{
    spiStartSend(array.config->spi0, n, buf0);
    spiStartSend(array.config->spi1, n, buf1);

    chSemWait(&_spi_frame_done_sem);
    chSemWait(&_spi_frame_done_sem);
}

static void _spi_frame_done(SPIDriver * spip)
{
    UNUSED_PARAMETER(spip);

    osalSysLockFromISR();
    chSemSignalI(&_spi_frame_done_sem);
    osalSysUnlockFromISR();
}

/** @} defgroup ARRAY_PRIVATE */
/** @} addtogroup ARRAY */
