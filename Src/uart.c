/**
  ******************************************************************************
  * @file   uart.c
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

#include "uart.h"
#include <stddef.h>

/* API functions */

/**
 * @brief UART_Init - configure hardware uart module with params from UART_Control_t struct
 * @param unit
 * @return true - OK, false - error
 */
bool UART_Init(UART_Control_t* unit)
{
    unit->state = IDLE;

    if(unit == NULL || unit->baud == 0){
        return false;
    }

    /* Here shall be hardware functions for init uart
     *  by baudrate and etc */

    return true;
}

/**
 * @brief UART_SetBaudRate sets baud rate
 * @param unit
 * @param baud - baud rate of uart
 * @return true - OK, false - ERROR
 */
bool UART_SetBaudRate(UART_Control_t* unit, uint32_t baud)
{
    if(unit == NULL || baud > UART_HARDWARE_MAX_BAUDRATE){
        return false;
    }

    unit->baud = baud;

    return true;
}

/**
 * @brief UART_SetParity sets parity
 * @param unit
 * @param parity
 * @return true - OK, false - ERROR
 */
bool UART_SetParity(UART_Control_t* unit, UART_Parity_t parity)
{
    if(unit == NULL){
        return false;
    }

    unit->parity = parity;

    return true;
}

/**
 * @brief UART_SetStopBits sets stop bits
 * @param unit
 * @param stop_bits
 * @return true - OK, false - ERROR
 */
bool UART_SetStopBits(UART_Control_t* unit, UART_StopBits_t stop_bits)
{
    if(unit == NULL){
        return false;
    }

    unit->stop_bits = stop_bits;

    return true;
}

bool UART_Transmit_IT(UART_Control_t* unit, uint8_t* buf, uint16_t lenght)
{
    if(buf == NULL){
        return false;
    }

    RING_Init(&unit->tx_buf, buf, lenght);
    unit->tx_buf.ind_in = lenght;

    unit->state = TX;

    /* Enable IRQ handlers for TX here */

    return true;
}

/**
 * @brief UART_Receive_IT
 * @param unit
 * @param buf -
 * @param lenght
 * @return
 */
bool UART_Receive_IT(UART_Control_t* unit, uint8_t* buf, uint16_t lenght)
{
    if(buf == NULL){
        return false;
    }

    RING_Init(&unit->rx_buf, buf, lenght);

    unit->state = RX;
    /* Enable IRQ handlers for RX here */

    return true;
}

/**
 * @brief UART_SetTxCpltCallback - function sets user callback, will be called after transmit will be completed
 * @param unit
 * @return true - OK, false - error
 */
bool UART_SetTxCpltCallback(UART_Control_t* unit, void (*tx_callback)(void))
{
    if(tx_callback == NULL)
    {
        return false;
    }

    unit->tx_callback = tx_callback;

    return true;
}

/**
 * @brief UART_SetRxCpltCallback - function sets user callback, will be called after receive will be completed
 * @param unit
 * @return true - OK, false -ERROR
 */
bool UART_SetRxCpltCallback(UART_Control_t* unit, void (*rx_callback)(void))
{
    if(rx_callback == NULL){
        return false;
    }

    unit->rx_callback = rx_callback;

    return true;
}
