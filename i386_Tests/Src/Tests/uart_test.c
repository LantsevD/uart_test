/**
  ******************************************************************************
  * @file   uart_test.c
  * @author Dmitry Lantsev
  * @version V0.0.1
  * @date    30-05-2021
  * @brief   UART unit tests module
  * @note    This file is part of the uart_test repo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT Lantsev </center></h2>
  ******************************************************************************
  */

#include "uart.h"
#include "uart_test.h"
#include <string.h>
#include <stdio.h>

/* Test functions */
static MunitResult uart_test_transmition(const MunitParameter params[], void *data);
static MunitResult uart_print_result(const MunitParameter params[], void *data);

/* Test task macro */

#define TEST_TASK_TX_BLOCK_SIZE     128
#define TEST_TASK_UART_BUFFER_SIZE  TEST_TASK_TX_BLOCK_SIZE * 2
#define TEST_TASK_UART1_BAUDRATE    9600
#define TEST_TASK_UART2_BAUDRATE    115200

/* Global objects */

UART_Control_t uart1 = {
  .state = IDLE,
  .baud  = 0, /* by default will not work */
  .parity = NONE,
  .stop_bits = ONE_STOP,
  .tx_buf = { NULL, 0 , 0, 0},
  .rx_buf = { NULL, 0 , 0, 0},
  .tx_callback = NULL,
  .rx_callback = NULL,
};

UART_Control_t uart2 = {
  .state = IDLE,
  .baud  = 0, /* by default will not work */
  .parity = NONE,
  .stop_bits = ONE_STOP,
  .tx_buf = { NULL, 0 , 0, 0},
  .rx_buf = { NULL, 0 , 0, 0},
  .tx_callback = NULL,
  .rx_callback = NULL,
};

uint8_t uart_buffer[TEST_TASK_UART_BUFFER_SIZE];

uint8_t init_data_array[] = {
 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x3D, 0x53, 0x41, 0x49, 0x54, 0x4F, 0x20, 0x46, 0x47,
 0x34, 0x30, 0x7C, 0x68, 0x77, 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x35, 0x46, 0x2E, 0x33, 0x7C, 0x73, 0x77,
 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x67, 0x69, 0x6E,
 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x3D, 0x53, 0x41, 0x49, 0x54, 0x4F, 0x20, 0x46, 0x47,
 0x34, 0x30, 0x7C, 0x68, 0x77, 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x35, 0x46, 0x2E, 0x33, 0x7C, 0x73, 0x77,
 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x67, 0x69, 0x6E,
 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x3D, 0x53, 0x41, 0x49, 0x54, 0x4F, 0x20, 0x46, 0x47,
 0x34, 0x30, 0x7C, 0x68, 0x77, 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x35, 0x46, 0x2E, 0x33, 0x7C, 0x73, 0x77,
 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x67, 0x69, 0x6E,
 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x3D, 0x53, 0x41, 0x49, 0x54, 0x4F, 0x20, 0x46, 0x47,
 0x34, 0x30, 0x7C, 0x68, 0x77, 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x35, 0x46, 0x2E, 0x33, 0x7C, 0x73, 0x77,
 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x67, 0x69, 0x6E,
 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x3D, 0x53, 0x41, 0x49, 0x54, 0x4F, 0x20, 0x46, 0x47,
 0x34, 0x30, 0x7C, 0x68, 0x77, 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x35, 0x46, 0x2E, 0x33, 0x7C, 0x73, 0x77,
 0x5F, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x67, 0x69, 0x6E,
 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30
};

uint8_t final_data_array[sizeof(init_data_array)];///< Result of the test must be same with init_data_array, only last block not be the same

/* Imitation of Interrupts handler */

uint8_t uart1_data_reg; /* Imitation of data registers */

/**
 * @brief USART1_IRQHandler - look like irq of mcu
 */
void USART1_IRQHandler(void)
{
    extern UART_Control_t uart1;

    /* Below only for receive byte interrupt */
    if(uart1.state == RX)
    {
        RING_Push(&uart1.rx_buf, uart1_data_reg);

        if(RING_GetBytesAvailable(&uart1.rx_buf) == uart1.rx_buf.size)
        {
             uart1.state = IDLE;

             /* Also disable RX_IRQ here */
             if(uart1.rx_callback != NULL){
                uart1.rx_callback();
             }
        }     
    }
}

/**
 * @brief USART2_IRQHandler - look like irq of mcu
 */
void USART2_IRQHandler(void)
{
    extern UART_Control_t uart2;

    /* Below only for transmite byte interrupt */
    if(uart2.state == TX)
    {
        static uint32_t tx_ind = 0;
        final_data_array[tx_ind++] = RING_Pop(&uart2.tx_buf);

        if(RING_GetBytesAvailable(&uart2.tx_buf) == uart2.tx_buf.size)
        {
             uart2.state = IDLE;

             /* Also disable TX_IRQ here */
             if(uart2.rx_callback != NULL){
                uart2.tx_callback();
             }
        }
    }
}

/**
 * @brief TEST_ReceiveCallback - use it in order to start transmition,
 * we have already block with 128 bytes
 * @param unit
 */
void TEST_ReceiveCallback(void)
{    
    if(RING_GetBytesAvailable(&uart1.rx_buf) == TEST_TASK_TX_BLOCK_SIZE)
    {
        UART_Transmit_IT(&uart2, uart1.rx_buf.buf, TEST_TASK_TX_BLOCK_SIZE);

        if(uart1.rx_buf.buf == uart_buffer){
            UART_Receive_IT(&uart1, uart_buffer + TEST_TASK_TX_BLOCK_SIZE, TEST_TASK_TX_BLOCK_SIZE);
        }
        else  {
            UART_Receive_IT(&uart1, uart_buffer, TEST_TASK_TX_BLOCK_SIZE);
        }
    }
}

/**
 * @brief test_task_logic - main funtional of test task is here
 */
static void TEST_TaskLogic(void)
{
    UART_SetBaudRate(&uart1, TEST_TASK_UART1_BAUDRATE);
    UART_Init(&uart1);

    UART_SetBaudRate(&uart2, TEST_TASK_UART2_BAUDRATE);
    UART_Init(&uart2);

    UART_SetRxCpltCallback(&uart1, TEST_ReceiveCallback);
    UART_Receive_IT(&uart1, uart_buffer, TEST_TASK_TX_BLOCK_SIZE);
}


/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest uart_test_suite_tests[] = {

    /* test run for 16 bit values */
    { /* The name is just a unique human-readable way to identify the
      * test. You can use it to run a specific test if you want, but
      * usually it's mostly decorative. */
      (char *)"test uart receive and transmition functions",
      /* You probably won't be surprised to learn that the tests are
      * functions. */
      uart_test_transmition,
      /* If you want, you can supply a function to set up a fixture.  If
      * you supply NULL, the user_data parameter from munit_suite_main
      * will be used directly.  If, however, you provide a callback
      * here the user_data parameter will be passed to this callback,
      * and the return value from this callback will be passed to the
      * test function.
      *
      * For our example we don't really need a fixture, but lets
      * provide one anyways. */
      NULL,
      /* If you passed a callback for the fixture setup function, you
      * may want to pass a corresponding callback here to reverse the
      * operation. */
      NULL,
      /* Finally, there is a bitmask for options you can pass here.  You
      * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
      * defaults. */
      MUNIT_TEST_OPTION_NONE,
      NULL },
    {
         (char *)"print results of uart test",
         uart_print_result,
         NULL,
         NULL,
         MUNIT_TEST_OPTION_NONE,
         NULL,
    },
    
    //**********************************************************
    {
        /* finalizer */
        (char *)"uart no more tests",
        NULL,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },

};

MunitSuite uart_test_suite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"uart_test/",
    /* The first parameter is the array of test suites. */
    uart_test_suite_tests,
    /* In addition to containing test cases, suites can contain other
     * test suites.  This isn't necessary in this example, but it can be
     * a great help to projects with lots of tests by making it easier
     * to spread the tests across many files.  This is where you would
     * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
     * running multiple iterations of the tests.  This is usually only
     * interesting if you make use of the PRNG to randomize your tests
     * cases a bit, or if you are doing performance testing and want to
     * average multiple runs.  0 is an alias for 1. */
    1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE
};

/**
 * @brief uart_test_transmition fucntion imitates uart routine
 * @param params
 * @param data
 * @return
 */
static MunitResult uart_test_transmition(const MunitParameter params[] __attribute__((unused)), void *data __attribute__((unused)))
{
    TEST_TaskLogic(); /* Init uarts */

    /* Imitate IRQ handlers and uart work, it is not part of the mcu routine */
    for(uint32_t ind = 0; ind < sizeof(init_data_array) -
                          sizeof(init_data_array)%TEST_TASK_TX_BLOCK_SIZE; ind++)
    {
        uart1_data_reg = init_data_array[ind];
        USART1_IRQHandler();

        USART2_IRQHandler();   
    }

    if(memcmp(init_data_array, final_data_array, sizeof(init_data_array) - TEST_TASK_TX_BLOCK_SIZE*2) == 0)
    {
        return MUNIT_OK;
    }
    else
    {
       return MUNIT_FAIL;
    }
}

/**
 * @brief uart_print_result prints initial data for test and result after module work
 * @param params
 * @param data
 * @return
 */
static MunitResult uart_print_result(const MunitParameter params[] __attribute__((unused)), void *data __attribute__((unused)))
{
    printf("\r\n");

    printf("\r\nInit data:\r\n");
    for(uint32_t ind = 0; ind < sizeof(init_data_array) -
                          sizeof(init_data_array)%TEST_TASK_TX_BLOCK_SIZE; ind++)
    {
       if(ind % 16 == 0){
           printf("\r\n");
       }
       printf("%c", init_data_array[ind]);
    }
    printf("\r\n");

    printf("\r\nAfter uart module:\r\n");
    for(uint32_t ind = 0; ind < sizeof(init_data_array) -
                          sizeof(init_data_array)%TEST_TASK_TX_BLOCK_SIZE; ind++)
    {
       if(ind % 16 == 0){
          printf("\r\n");
       }
       printf("%c", init_data_array[ind]);
    }

    printf("\r\n");

    return MUNIT_OK;
}
