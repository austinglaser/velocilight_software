/**
 * @file    main.c
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   Application Entry Point
 *
 * @defgroup MAIN Main
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

// Standard
#include <stdint.h>
#include <stdbool.h>

// Chibios
#include "ch.h"
#include "hal.h"

/* --- PRIVATE DATATYPES ---------------------------------------------------- */
/* --- PRIVATE FUNCTION PROTOTYPES ------------------------------------------ */
/* --- PRIVATE MACROS ------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PRIVATE VARIABLES ---------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/**
 * @brief   Application entry point
 */
int main(void) {

    // Chibios init
    halInit();
    chSysInit();

    // Driver init

    // Application init

    // Main loop
    while (true) {
        palToggleLine(LINE_STATUS_LED);
        chThdSleepMilliseconds(500);
    }
}

/* --- PRIVATE FUNCTION DEFINITIONS ----------------------------------------- */

/** @} defgroup MAIN */
