/**
  ******************************************************************************
  * @file   ring_buf.c
  * @author Dmitry Lantsev
  * @version V0.0.1
  * @date    30-05-2021
  * @brief   Simple ring buffer module
  * @note    This file is part of the uart_test repo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT Lantsev </center></h2>
  ******************************************************************************
  */

#include "ring_buf.h"
#include <stddef.h>

/**
 * @brief RING_Push - add byte into ring buffer
 * @param unit
 * @param symbol
 */
void RING_Push(RING_buffer_t* unit, uint8_t symbol)
{
    if (unit->ind_in >= unit->size) {
        unit->ind_in = 0;
    }

    unit->buf[unit->ind_in++] = symbol;
}

/**
 * @brief  RING_Pop - get byte from ring buffer
 * @param  unit
 * @return Byte value from ring buffer
 */
uint8_t RING_Pop(RING_buffer_t *unit)
{
    uint8_t retval = unit->buf[unit->ind_out++];

    if (unit->ind_out >= unit->size) {
        unit->ind_out = 0;
    }

    return retval;
}

/**
 * @brief RING_GetBytesAvailable - return number of bytes available in ring buffer
 * @param unit
 * @return number of bytes available in ring buffer
 */
uint16_t RING_GetBytesAvailable(RING_buffer_t *unit)
{
    uint16_t retval = 0;

    if (unit->ind_in < unit->ind_out){
        retval = unit->size + unit->ind_in - unit->ind_out;
    }
    else  {
        retval = unit->ind_in - unit->ind_out;
    }

    return retval;
}

/**
 * @brief RING_Clear - flush ring buffer
 * @param unit
 */
void RING_Clear(RING_buffer_t *unit)
{
    unit->ind_in = 0;
    unit->ind_out = 0;
}

/**
 * @brief RING_Init - bind buffer and its size with ring buffer struct, also flush buffer
 * @param unit
 * @param buf  - set pointer to ring buffer
 * @param size - set size of ring buffer
 * @return true - OK, false - ERROR
 */
bool RING_Init(RING_buffer_t *unit, uint8_t *buf, uint16_t size)
{
    if(unit == NULL || buf == NULL){
        return false;
    }

    unit->size = size;
    unit->buf = buf;
    RING_Clear(unit);

    return true;
}
