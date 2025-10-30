#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/* UART Configuration Options */

/* Baud Rate Configuration 
 * Available Options:
 * 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
 */
#define UART_BAUD_RATE          115200

/* Parity Configuration 
 * Options:
 * UART_PARITY_DISABLED
 * UART_PARITY_EVEN
 * UART_PARITY_ODD
 */
#define UART_PARITY_MODE        UART_PARITY_DISABLED

/* Stop Bits Configuration 
 * Options:
 * UART_STOP_BIT_1
 * UART_STOP_BIT_2
 */
#define UART_STOP_BITS          UART_STOP_BIT_1

/* Data Bits Configuration 
 * Options:
 * UART_DATA_5_BITS
 * UART_DATA_6_BITS
 * UART_DATA_7_BITS
 * UART_DATA_8_BITS
 * UART_DATA_9_BITS
 */
#define UART_DATA_BITS          UART_DATA_8_BITS

/* UART Mode Configuration 
 * Options:
 * UART_MODE_ASYNCHRONOUS
 * UART_MODE_SYNCHRONOUS
 */
#define UART_MODE               UART_MODE_ASYNCHRONOUS

/* Interrupt Configuration 
 * Options:
 * UART_INT_DISABLED
 * UART_INT_RX_ENABLED
 * UART_INT_TX_ENABLED
 * UART_INT_BOTH_ENABLED
 */
#define UART_INTERRUPT_MODE     UART_INT_RX_ENABLED




#endif /* UART_CONFIG_H_ */
