/**@file    project_info.h
 * @author  Austin Glaser <austin@boulderes.com>
 * @brief   Project Information Interface
 */

#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H

/**@defgroup PROJECT_INFO Project Information
 * @{
 *
 * @brief
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */
/* --- PUBLIC DATATYPES ----------------------------------------------------- */

/** Structure encoding current repository state */
typedef struct {
    uint8_t git_hash[20];       /**< The git hash of the current HEAD */
    uint64_t build_timestamp;   /**< Unix time when the binary was compiled */
    bool repo_dirty;            /**< Whether the repository has uncommited
                                     changes */
    bool stable_version;        /**< Whether the repository is at a stable
                                     (tagged) commit */
    uint16_t client_id;         /**< BES internal client ID */
    uint16_t project_id;        /**< BES internal project ID */
    uint16_t version_major;     /**< Major firmware version. Invalid if
                                     stable_version is false */
    uint8_t version_minor;      /**< Minor firmware version. Invalid if
                                     stable_version is false */
    uint8_t version_patch;      /**< Patch firmware version. Invalid if
                                     stable_version is false */
} project_info_t;

/* --- PUBLIC MACROS -------------------------------------------------------- */
/* --- PUBLIC VARIABLES ----------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/** @} defgroup PROJECT_INFO */

#endif /* ifndef PROJECT_INFO_H */
