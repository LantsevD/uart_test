/**
  ******************************************************************************
  * @file   uart.h
  * @author Dmitry Lantsev
  * @version V0.0.1
  * @date    30-05-2021
  * @brief   UART module
  * @note    This file is part of the uart_test repo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT Lantsev </center></h2>
  ******************************************************************************
  */

#ifndef _UART
#define _UART

#include "ring_buf.h"
#include <stdint.h>
#include <stdbool.h>

#define UART_HARDWARE_MAX_BAUDRATE 1000000

/// UART module state
typedef enum
{
    IDLE = 0,
    RX,
    TX,
    TX_RX,
}UART_State_t;

/// UART parity control modes
typedef enum
{
    NONE = 0,
    ODD,
    EVEN,
    MARK,
    SPACE,
}UART_Parity_t;

/// UART stop bits modes
typedef enum
{
    ONE_STOP = 0,
    ONE_HALF_STOP,
    TWO_STOP,
}UART_StopBits_t;

/// UART control structure
typedef struct
{
    volatile UART_State_t state;    ///< State of uart module
    uint32_t        baud;           ///< UART baud rate speed
    UART_Parity_t   parity;         ///< UART module parity
    UART_StopBits_t stop_bits;      ///< UART module stop bits
    RING_buffer_t   tx_buf;         ///< Transmit ring buffer
    RING_buffer_t   rx_buf;         ///< Receive  ring buffer
    void (*tx_callback)(void);      ///< User callback, calls after transmition is over. Calls in Interrupt be carefull!
    void (*rx_callback)(void);      ///< User callback, calls after receive is over. Calls in Interrupt be carefull!
}UART_Control_t;

/* Public API for UART module */

bool UART_Init(UART_Control_t* unit);
bool UART_SetBaudRate(UART_Control_t* unit, uint32_t baud);
bool UART_SetParity(UART_Control_t* unit, UART_Parity_t parity);
bool UART_SetStopBits(UART_Control_t* unit, UART_StopBits_t stop_bits);
bool UART_Transmit_IT(UART_Control_t* unit, uint8_t* buf, uint16_t lenght);
bool UART_Receive_IT(UART_Control_t* unit, uint8_t* buf, uint16_t lenght);
bool UART_SetTxCpltCallback(UART_Control_t* unit, void (*tx_callback)(void));
bool UART_SetRxCpltCallback(UART_Control_t* unit, void (*rx_callback)(void));

#endif
