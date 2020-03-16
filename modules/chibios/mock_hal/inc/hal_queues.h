/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_queues.h
 * @brief   I/O Queues macros and structures.
 *
 * @addtogroup HAL_QUEUES
 * @{
 */

#ifdef MOCK_HAL
#include "ch.h"
#include "hal.h"
#endif

#ifndef _HAL_QUEUES_H_
#define _HAL_QUEUES_H_

/* The ChibiOS/RT kernel provides the following definitions by itself, this
   check is performed in order to avoid conflicts. */
#if !defined(_CHIBIOS_RT_) || (CH_CFG_USE_QUEUES == FALSE) ||               \
    defined(__DOXYGEN__)

/**
 * @name    Queue functions returned status value
 * @{
 */
#define Q_OK            MSG_OK      /**< @brief Operation successful.       */
#define Q_TIMEOUT       MSG_TIMEOUT /**< @brief Timeout condition.          */
#define Q_RESET         MSG_RESET   /**< @brief Queue has been reset.       */
#define Q_EMPTY         (msg_t)-3   /**< @brief Queue empty.                */
#define Q_FULL          (msg_t)-4   /**< @brief Queue full,                 */
/** @} */

/**
 * @brief   Type of a generic I/O queue structure.
 */
typedef struct io_queue io_queue_t;

/**
 * @brief   Queue notification callback type.
 *
 * @param[in] qp        the queue pointer
 */
typedef void (*qnotify_t)(io_queue_t *qp);

/**
 * @brief   Generic I/O queue structure.
 * @details This structure represents a generic Input or Output asymmetrical
 *          queue. The queue is asymmetrical because one end is meant to be
 *          accessed from a thread context, and thus can be blocking, the other
 *          end is accessible from interrupt handlers or from within a kernel
 *          lock zone and is non-blocking.
 */
struct io_queue {
  threads_queue_t       q_waiting;  /**< @brief Queue of waiting threads.   */
  volatile size_t       q_counter;  /**< @brief Resources counter.          */
  uint8_t               *q_buffer;  /**< @brief Pointer to the queue buffer.*/
  uint8_t               *q_top;     /**< @brief Pointer to the first
                                         location after the buffer.         */
  uint8_t               *q_wrptr;   /**< @brief Write pointer.              */
  uint8_t               *q_rdptr;   /**< @brief Read pointer.               */
  qnotify_t             q_notify;   /**< @brief Data notification callback. */
  void                  *q_link;    /**< @brief Application defined field.  */
};

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Returns the queue's buffer size.
 *
 * @param[in] qp        pointer to a @p io_queue_t structure
 * @return              The buffer size.
 *
 * @xclass
 */
#define qSizeX(qp)                                                          \
  /*lint -save -e9033 [10.8] The cast is safe.*/                            \
  ((size_t)((qp)->q_top - (qp)->q_buffer))                                  \
  /*lint -restore*/

/**
 * @brief   Queue space.
 * @details Returns the used space if used on an input queue or the empty
 *          space if used on an output queue.
 *
 * @param[in] qp        pointer to a @p io_queue_t structure
 * @return              The buffer space.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define qSpaceI(qp) ((qp)->q_counter)
#else
size_t qSpaceI(io_queue_t *qp);
#endif

/**
 * @brief   Returns the queue application-defined link.
 * @note    This function can be called in any context.
 *
 * @param[in] qp        pointer to a @p io_queue_t structure
 * @return              The application-defined link.
 *
 * @special
 */
#ifndef MOCK_HAL
#define qGetLink(qp) ((qp)->q_link)
#else
void *qGetLink(io_queue_t * qp);
#endif
/** @} */

/**
 * @extends io_queue_t
 *
 * @brief   Type of an input queue structure.
 * @details This structure represents a generic asymmetrical input queue.
 *          Writing to the queue is non-blocking and can be performed from
 *          interrupt handlers or from within a kernel lock zone.
 *          Reading the queue can be a blocking operation and is supposed to
 *          be performed by a system thread.
 */
typedef io_queue_t input_queue_t;

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Returns the filled space into an input queue.
 *
 * @param[in] iqp       pointer to an @p input_queue_t structure
 * @return              The number of full bytes in the queue.
 * @retval 0            if the queue is empty.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define iqGetFullI(iqp) qSpaceI(iqp)
#else
size_t iqGetFullI(input_queue_t *iqp);
#endif

/**
 * @brief   Returns the empty space into an input queue.
 *
 * @param[in] iqp       pointer to an @p input_queue_t structure
 * @return              The number of empty bytes in the queue.
 * @retval 0            if the queue is full.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define iqGetEmptyI(iqp) (qSizeX(iqp) - qSpaceI(iqp))
#else
size_t iqGetEmptyI(input_queue_t *iqp);
#endif

/**
 * @brief   Evaluates to @p true if the specified input queue is empty.
 *
 * @param[in] iqp       pointer to an @p input_queue_t structure
 * @return              The queue status.
 * @retval false        if the queue is not empty.
 * @retval true         if the queue is empty.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define iqIsEmptyI(iqp) ((bool)(qSpaceI(iqp) == 0U))
#else
bool iqIsEmptyI(input_queue_t *iqp);
#endif

/**
 * @brief   Evaluates to @p true if the specified input queue is full.
 *
 * @param[in] iqp       pointer to an @p input_queue_t structure
 * @return              The queue status.
 * @retval false        if the queue is not full.
 * @retval true         if the queue is full.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define iqIsFullI(iqp)                                                      \
  /*lint -save -e9007 [13.5] No side effects, a pointer is passed.*/        \
  ((bool)(((iqp)->q_wrptr == (iqp)->q_rdptr) && ((iqp)->q_counter != 0U)))  \
  /*lint -restore*/
#else
bool iqIsFullI(input_queue_t *iqp);
#endif

/**
 * @brief   Input queue read.
 * @details This function reads a byte value from an input queue. If the queue
 *          is empty then the calling thread is suspended until a byte arrives
 *          in the queue.
 *
 * @param[in] iqp       pointer to an @p input_queue_t structure
 * @return              A byte value from the queue.
 * @retval Q_RESET      if the queue has been reset.
 *
 * @api
 */
#ifndef MOCK_HAL
#define iqGet(iqp) iqGetTimeout(iqp, TIME_INFINITE)
#else
msg_t iqGet(input_queue_t *iqp);
#endif
/** @} */

/**
 * @extends io_queue_t
 *
 * @brief   Type of an output queue structure.
 * @details This structure represents a generic asymmetrical output queue.
 *          Reading from the queue is non-blocking and can be performed from
 *          interrupt handlers or from within a kernel lock zone.
 *          Writing the queue can be a blocking operation and is supposed to
 *          be performed by a system thread.
 */
typedef io_queue_t output_queue_t;

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Returns the filled space into an output queue.
 *
 * @param[in] oqp       pointer to an @p output_queue_t structure
 * @return              The number of full bytes in the queue.
 * @retval 0            if the queue is empty.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define oqGetFullI(oqp) (qSizeX(oqp) - qSpaceI(oqp))
#else
size_t oqGetFullI(output_queue_t *oqp);
#endif

/**
 * @brief   Returns the empty space into an output queue.
 *
 * @param[in] oqp       pointer to an @p output_queue_t structure
 * @return              The number of empty bytes in the queue.
 * @retval 0            if the queue is full.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define oqGetEmptyI(oqp) qSpaceI(oqp)
#else
size_t oqGetEmptyI(output_queue_t *oqp);
#endif

/**
 * @brief   Evaluates to @p true if the specified output queue is empty.
 *
 * @param[in] oqp       pointer to an @p output_queue_t structure
 * @return              The queue status.
 * @retval false        if the queue is not empty.
 * @retval true         if the queue is empty.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define oqIsEmptyI(oqp)                                                     \
  /*lint -save -e9007 [13.5] No side effects, a pointer is passed.*/        \
  ((bool)(((oqp)->q_wrptr == (oqp)->q_rdptr) && ((oqp)->q_counter != 0U)))  \
  /*lint -restore*/
#else
bool oqIsEmptyI(output_queue_t *oqp);
#endif

/**
 * @brief   Evaluates to @p true if the specified output queue is full.
 *
 * @param[in] oqp       pointer to an @p output_queue_t structure
 * @return              The queue status.
 * @retval false        if the queue is not full.
 * @retval true         if the queue is full.
 *
 * @iclass
 */
#ifndef MOCK_HAL
#define oqIsFullI(oqp) ((bool)(qSpaceI(oqp) == 0U))
#else
bool oqIsFullI(output_queue_t *oqp);
#endif

/**
 * @brief   Output queue write.
 * @details This function writes a byte value to an output queue. If the queue
 *          is full then the calling thread is suspended until there is space
 *          in the queue.
 *
 * @param[in] oqp       pointer to an @p output_queue_t structure
 * @param[in] b         the byte value to be written in the queue
 * @return              The operation status.
 * @retval Q_OK         if the operation succeeded.
 * @retval Q_RESET      if the queue has been reset.
 *
 * @api
 */
#ifndef MOCK_HAL
#define oqPut(oqp, b) oqPutTimeout(oqp, b, TIME_INFINITE)
#else
msg_t oqPut(output_queue_t *oqp, uint8_t b);
#endif
 /** @} */

#ifdef __cplusplus
extern "C" {
#endif
  void iqObjectInit(input_queue_t *iqp, uint8_t *bp, size_t size,
                    qnotify_t infy, void *link);
  void iqResetI(input_queue_t *iqp);
  msg_t iqPutI(input_queue_t *iqp, uint8_t b);
  msg_t iqGetTimeout(input_queue_t *iqp, systime_t timeout);
  size_t iqReadTimeout(input_queue_t *iqp, uint8_t *bp,
                       size_t n, systime_t timeout);

  void oqObjectInit(output_queue_t *oqp, uint8_t *bp, size_t size,
                    qnotify_t onfy, void *link);
  void oqResetI(output_queue_t *oqp);
  msg_t oqPutTimeout(output_queue_t *oqp, uint8_t b, systime_t timeout);
  msg_t oqGetI(output_queue_t *oqp);
  size_t oqWriteTimeout(output_queue_t *oqp, const uint8_t *bp,
                        size_t n, systime_t timeout);
#ifdef __cplusplus
}
#endif

#else /* defined(_CHIBIOS_RT_) && CH_CFG_USE_QUEUES */

/* If ChibiOS is being used and its own queues subsystem is activated then
   this module will use the ChibiOS queues code.*/
#define qSizeX(qp)                          chQSizeX(qp)
#define qSpaceI(qp)                         chQSpaceI(qp)
#define qGetLink(qp)                        chQGetLinkX(qp)
#define iqGetFullI(iqp)                     chIQGetFullI(iqp)
#define iqGetEmptyI(iqp)                    chIQGetEmptyI(iqp)
#define iqIsEmptyI(iqp)                     chIQIsEmptyI(iqp)
#define iqIsFullI(iqp)                      chIQIsFullI(iqp)
#define iqGet(iqp)                          chIQGet(iqp)
#define oqGetFullI(oqp)                     chOQGetFullI(oqp)
#define oqGetEmptyI(oqp)                    chOQGetEmptyI(oqp)
#define oqIsEmptyI(oqp)                     chOQIsEmptyI(oqp)
#define oqIsFullI(oqp)                      chOQIsFullI(oqp)
#define oqPut(oqp, b)                       chOQPut(oqp, b)
#define iqObjectInit(iqp, bp, size, infy, link)                             \
  chIQObjectInit(iqp, bp, size, infy, link)
#define iqResetI(iqp)                       chIQResetI(iqp)
#define iqPutI(iqp, b)                      chIQPutI(iqp, b)
#define iqGetTimeout(iqp, time)             chIQGetTimeout(iqp, time)
#define iqReadTimeout(iqp, bp, n, time)     chIQReadTimeout(iqp, bp, n, time)
#define oqObjectInit(oqp, bp, size, onfy, link)                             \
  chOQObjectInit(oqp, bp, size, onfy, link)
#define oqResetI(oqp)                       chOQResetI(oqp)
#define oqPutTimeout(oqp, b, time)          chOQPutTimeout(oqp, b, time)
#define oqGetI(oqp)                         chOQGetI(oqp)
#define oqWriteTimeout(oqp, bp, n, time)    chOQWriteTimeout(oqp, bp, n, time)

#endif /* defined(_CHIBIOS_RT_) || (CH_CFG_USE_QUEUES == FALSE) */

#endif /* _HAL_QUEUES_H_ */

/** @} */
