/**
  ******************************************************************************
  * @file   ring_buf.h
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

#ifndef _RING_BUF
#define _RING_BUF

#include <stdint.h>
#include <stdbool.h>

/// Ring buffer struct
typedef struct
{
    uint8_t  *buf; ///< pointer to ring buffer
    volatile uint16_t ind_in; ///< index of head of ring
    volatile uint16_t ind_out; ///< index of tail of ring
    uint16_t size; ///< size of ring buffer
} RING_buffer_t;

/* Public API for module RING */

void     RING_Push(RING_buffer_t* unit, uint8_t symbol);
uint8_t  RING_Pop(RING_buffer_t *unit);
uint16_t RING_GetBytesAvailable(RING_buffer_t *unit);
void     RING_Clear(RING_buffer_t *unit);
bool     RING_Init(RING_buffer_t *unit, uint8_t *buf, uint16_t size);

#endif /* RING_BUF */
