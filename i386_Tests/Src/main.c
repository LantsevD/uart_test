/**
  ******************************************************************************
  * @file    main.c
  * @author  Dmitry Lantsev
  * @version V0.0.1
  * @date    30-05-2021
  * @brief   Test target main.c file for high level uart module correct work check.
  * @note    This file is part of the uart_test repo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT Lantsev </center></h2>
  ******************************************************************************
  */

#include "munit.h"
#include "uart.h"
#include "uart_test.h"

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    int result = 0;

    /* Run tests for uart module */
    result = munit_suite_main(&uart_test_suite, (void*) "µnit", argc, argv);

    return result;
}
