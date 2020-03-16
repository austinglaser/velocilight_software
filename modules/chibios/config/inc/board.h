/**
 * @file    board.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Board Interface
 */

#ifndef BOARD_H
#define BOARD_H

/**@defgroup BOARD Board
 * @{ 
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

#define LED_R_PORT      GPIOA
#define LED_R_PIN       1
#define LED_G_PORT      GPIOB
#define LED_G_PIN       2
#define LED_B_PORT      GPIOC
#define LED_B_PIN       3

/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup BOARD */

#endif /* ifndef BOARD_H */
