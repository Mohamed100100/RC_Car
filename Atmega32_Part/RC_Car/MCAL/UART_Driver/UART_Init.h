#ifndef UART_INIT_H_
#define UART_INIT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* UART Configuration Enums */
#define    UART_PARITY_DISABLED 0
  #define  UART_PARITY_EVEN 2
 #define   UART_PARITY_ODD 3
#define    UART_STOP_BIT_1  0
#define   UART_STOP_BIT_2   1

#define   UART_DATA_5_BITS  0
#define   UART_DATA_6_BITS  1
#define   UART_DATA_7_BITS  2
#define   UART_DATA_8_BITS  3
#define   UART_DATA_9_BITS  7

 #define   UART_MODE_ASYNCHRONOUS  0
#define   UART_MODE_SYNCHRONOUS  1

#define    UART_INT_DISABLED 0
 #define   UART_INT_RX_ENABLED 1
 #define   UART_INT_TX_ENABLED 2
 #define   UART_INT_BOTH_ENABLED 3

typedef enum {
    UART_OK = 0,
    UART_ERROR = 1,
    UART_TIMEOUT = 2,
    UART_PARITY_ERROR = 3,
    UART_FRAME_ERROR = 4,
    UART_OVERRUN_ERROR = 5
} UART_Status_t;

/* Function Prototypes */

/**
 * @brief Initialize UART with default configuration
 * @return UART_Status_t - Status of initialization
 */
UART_Status_t UART_vidInit(void);

/**
 * @brief Initialize UART with custom baud rate
 * @param Copy_u32BaudRate - Desired baud rate
 * @return UART_Status_t - Status of initialization
 */
UART_Status_t UART_voidInitWithBaudRate(u32 Copy_u32BaudRate);

/**
 * @brief Send a single character via UART
 * @param Copy_u8Data - Character to send
 * @return UART_Status_t - Status of transmission
 */
UART_Status_t UART_u8SendChar(u8 Copy_u8Data);

/**
 * @brief Send a string via UART
 * @param Copy_pu8String - Pointer to string to send
 * @return UART_Status_t - Status of transmission
 */
UART_Status_t UART_u8SendString(const u8* Copy_pu8String);

/**
 * @brief Send a string with specified length via UART
 * @param Copy_pu8String - Pointer to string to send
 * @param Copy_u16Length - Length of string
 * @return UART_Status_t - Status of transmission
 */
UART_Status_t UART_u8SendStringWithLength(const u8* Copy_pu8String, u16 Copy_u16Length);

/**
 * @brief Send integer as string via UART
 * @param Copy_s32Number - Integer to send
 * @return UART_Status_t - Status of transmission
 */
UART_Status_t UART_u8SendNumber(s32 Copy_s32Number);

/**
 * @brief Receive a single character via UART (blocking)
 * @param Copy_pu8Data - Pointer to store received character
 * @return UART_Status_t - Status of reception
 */
UART_Status_t UART_u8ReceiveChar(u8* Copy_pu8Data);

/**
 * @brief Receive a string via UART until newline (blocking)
 * @param Copy_pu8String - Pointer to buffer to store received string
 * @param Copy_u16MaxLength - Maximum length of buffer
 * @return UART_Status_t - Status of reception
 */
UART_Status_t UART_u8ReceiveString(u8* Copy_pu8String, u16 Copy_u16MaxLength);

/**
 * @brief Receive a single character via UART (non-blocking)
 * @param Copy_pu8Data - Pointer to store received character
 * @return UART_Status_t - Status of reception
 */
UART_Status_t UART_u8ReceiveCharNonBlocking(u8* Copy_pu8Data);


/**
 * @brief Check if data is available to read
 * @return u8 - 1 if data available, 0 otherwise
 */
u8 UART_u8DataAvailable(void);

/**
 * @brief Check if transmitter is ready to send data
 * @return u8 - 1 if ready, 0 otherwise
 */
u8 UART_u8TransmitterReady(void);

/**
 * @brief Set callback function for RX interrupt
 * @param Copy_pvCallBack - Pointer to callback function
 */
void UART_voidSetRxCallback(void (*Copy_pvCallBack)(u8));

/**
 * @brief Set callback function for TX interrupt
 * @param Copy_pvCallBack - Pointer to callback function
 */
void UART_voidSetTxCallback(void (*Copy_pvCallBack)(void));

/**
 * @brief Enable/Disable UART interrupts
 * @param Copy_u8InterruptMode - Interrupt mode to set
 */
void UART_voidSetInterruptMode(u8 Copy_u8InterruptMode);

/**
 * @brief Flush UART buffers
 */
void UART_voidFlush(void);

#endif /* UART_INIT_H_ */
