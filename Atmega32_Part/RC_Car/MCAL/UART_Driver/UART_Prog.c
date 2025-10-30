#include "UART_Confg.h"
#include "UART_Init.h"
#include "UART_Priv.h"


/* Global Variables */
static void (*UART_pvRxCallback)(u8) = NULL;
static void (*UART_pvTxCallback)(void) = NULL;

/* Private Function Prototypes */
static u16 UART_u16CalculateBaudRate(u32 Copy_u32BaudRate);
static UART_Status_t UART_u8CheckErrors(void);

/* Function Implementations */

UART_Status_t UART_vidInit(void)
{
    return UART_voidInitWithBaudRate(UART_BAUD_RATE);
}

UART_Status_t UART_voidInitWithBaudRate(u32 Copy_u32BaudRate)
{
    u16 Local_u16BaudRateValue;
    u8 Local_u8TempUCSRC = 0;
    
    /* Calculate baud rate value */
    Local_u16BaudRateValue = UART_u16CalculateBaudRate(Copy_u32BaudRate);
    
    /* Set baud rate */
    UBRRH_REG = (u8)(Local_u16BaudRateValue >> 8);
    UBRRL_REG = (u8)Local_u16BaudRateValue;
    
    /* Configure UCSRC register */
    Local_u8TempUCSRC |= (1 << 7); // URSEL bit to select UCSRC
    
    /* Set UART mode */
    #if UART_MODE == UART_MODE_SYNCHRONOUS
        Local_u8TempUCSRC |= (1 << 6); // UMSEL bit
    #endif
    
    /* Set parity mode */
    #if UART_PARITY_MODE == UART_PARITY_EVEN
        Local_u8TempUCSRC |= (2 << 4); // UPM1:0 = 10
    #elif UART_PARITY_MODE == UART_PARITY_ODD
        Local_u8TempUCSRC |= (3 << 4); // UPM1:0 = 11
    #endif
    
    /* Set stop bits */
    #if UART_STOP_BITS == UART_STOP_BIT_2
        Local_u8TempUCSRC |= (1 << 3); // USBS bit
    #endif
    
    /* Set data bits */
    #if UART_DATA_BITS == UART_DATA_5_BITS
        // UCSZ2:0 = 000 (default)
    #elif UART_DATA_BITS == UART_DATA_6_BITS
        Local_u8TempUCSRC |= (1 << 1); // UCSZ1:0 = 01
    #elif UART_DATA_BITS == UART_DATA_7_BITS
        Local_u8TempUCSRC |= (2 << 1); // UCSZ1:0 = 10
    #elif UART_DATA_BITS == UART_DATA_8_BITS
        Local_u8TempUCSRC |= (3 << 1); // UCSZ1:0 = 11
    #elif UART_DATA_BITS == UART_DATA_9_BITS
        Local_u8TempUCSRC |= (3 << 1); // UCSZ1:0 = 11
        UCSRB_REG |= (1 << 2);         // UCSZ2 = 1
    #endif
    
    /* Write to UCSRC */
    UCSRC_REG = Local_u8TempUCSRC;
    
    /* Enable transmitter and receiver */
    UCSRB_REG |= (1 << 3) | (1 << 4); // RXEN and TXEN
    
    /* Configure interrupts */
    #if UART_INTERRUPT_MODE == UART_INT_RX_ENABLED
        UCSRB_REG |= (1 << 7); // RXCIE
    #elif UART_INTERRUPT_MODE == UART_INT_TX_ENABLED
        UCSRB_REG |= (1 << 6); // TXCIE
    #elif UART_INTERRUPT_MODE == UART_INT_BOTH_ENABLED
        UCSRB_REG |= (1 << 7) | (1 << 6); // RXCIE and TXCIE
    #endif
    
    return UART_OK;
}

UART_Status_t UART_u8SendChar(u8 Copy_u8Data)
{
    /* Wait for transmit buffer to be empty */
    while (!(UCSRA_REG & (1 << 5)));

    /* Send data */
    UDR_REG = Copy_u8Data;
    
    return UART_OK;
}
UART_Status_t UART_u8SendNumber(s32 Copy_s32Number)
{
    u8 Local_u8NumberString[12]; // Enough for 32-bit signed integer
    u8 Local_u8Index = 0;
    u8 Local_u8IsNegative = 0;
    s32 Local_s32TempNumber = Copy_s32Number;

    /* Handle negative numbers */
    if (Copy_s32Number < 0)
    {
        Local_u8IsNegative = 1;
        Local_s32TempNumber = -Copy_s32Number;
    }

    /* Handle zero case */
    if (Local_s32TempNumber == 0)
    {
        return UART_u8SendChar('0');
    }

    /* Convert number to string */
    while (Local_s32TempNumber > 0)
    {
        Local_u8NumberString[Local_u8Index] = (Local_s32TempNumber % 10) + '0';
        Local_s32TempNumber /= 10;
        Local_u8Index++;
    }

    /* Add negative sign if needed */
    if (Local_u8IsNegative)
    {
        Local_u8NumberString[Local_u8Index] = '-';
        Local_u8Index++;
    }

    /* Send string in reverse order */
    for (u8 i = Local_u8Index; i > 0; i--)
    {
        UART_Status_t Local_Status = UART_u8SendChar(Local_u8NumberString[i - 1]);
        if (Local_Status != UART_OK)
        {
            return Local_Status;
        }
    }

    return UART_OK;
}



UART_Status_t UART_u8SendString(const u8* Copy_pu8String)
{
    UART_Status_t Local_Status;
    
    if (Copy_pu8String == NULL)
    {
        return UART_ERROR;
    }
    
    while (*Copy_pu8String != '\0')
    {
        Local_Status = UART_u8SendChar(*Copy_pu8String);
        if (Local_Status != UART_OK)
        {
            return Local_Status;
        }
        Copy_pu8String++;
    }
    
    return UART_OK;
}

UART_Status_t UART_u8SendStringWithLength(const u8* Copy_pu8String, u16 Copy_u16Length)
{
    UART_Status_t Local_Status;
    u16 Local_u16Counter;
    
    if (Copy_pu8String == NULL)
    {
        return UART_ERROR;
    }
    
    for (Local_u16Counter = 0; Local_u16Counter < Copy_u16Length; Local_u16Counter++)
    {
        Local_Status = UART_u8SendChar(Copy_pu8String[Local_u16Counter]);
        if (Local_Status != UART_OK)
        {
            return Local_Status;
        }
    }
    
    return UART_OK;
}

UART_Status_t UART_u8ReceiveChar(u8* Copy_pu8Data)
{
    UART_Status_t Local_Status;
    
    if (Copy_pu8Data == NULL)
    {
        return UART_ERROR;
    }
    
    /* Wait for data to be received */
    while (!(UCSRA_REG & (1 << 7)));

    
    /* Check for errors */
    Local_Status = UART_u8CheckErrors();
    if (Local_Status != UART_OK)
    {
        return Local_Status;
    }
    
    /* Read data */
    *Copy_pu8Data = UDR_REG;
    
    return UART_OK;
}

UART_Status_t UART_u8ReceiveString(u8* Copy_pu8String, u16 Copy_u16MaxLength)
{
    UART_Status_t Local_Status;
    u8 Local_u8ReceivedChar;
    u16 Local_u16Counter = 0;
    
    if (Copy_pu8String == NULL || Copy_u16MaxLength == 0)
    {
        return UART_ERROR;
    }
    
    while (Local_u16Counter < (Copy_u16MaxLength - 1))
    {
        Local_Status = UART_u8ReceiveChar(&Local_u8ReceivedChar);
        if (Local_Status != UART_OK)
        {
            return Local_Status;
        }
        
        if (Local_u8ReceivedChar == '\r' || Local_u8ReceivedChar == '\n')
        {
            break;
        }
        
        Copy_pu8String[Local_u16Counter] = Local_u8ReceivedChar;
        Local_u16Counter++;
    }
    
    /* Null terminate the string */
    Copy_pu8String[Local_u16Counter] = '\0';
    
    return UART_OK;
}

UART_Status_t UART_u8ReceiveCharNonBlocking(u8* Copy_pu8Data)
{
    UART_Status_t Local_Status;
    
    if (Copy_pu8Data == NULL)
    {
        return UART_ERROR;
    }
    
    /* Check if data is available */
    if (!(UCSRA_REG & (1 << 7)))
    {
        return UART_TIMEOUT; // No data available
    }
    
    /* Check for errors */
    Local_Status = UART_u8CheckErrors();
    if (Local_Status != UART_OK)
    {
        return Local_Status;
    }
    
    /* Read data */
    *Copy_pu8Data = UDR_REG;
    
    return UART_OK;
}


u8 UART_u8DataAvailable(void)
{
    return (UCSRA_REG & (1 << 7)) ? 1 : 0;
}

u8 UART_u8TransmitterReady(void)
{
    return (UCSRA_REG & (1 << 5)) ? 1 : 0;
}

void UART_voidSetRxCallback(void (*Copy_pvCallBack)(u8))
{
    UART_pvRxCallback = Copy_pvCallBack;
}

void UART_voidSetTxCallback(void (*Copy_pvCallBack)(void))
{
    UART_pvTxCallback = Copy_pvCallBack;
}

void UART_voidSetInterruptMode(u8 Copy_u8InterruptMode)
{
    /* Clear interrupt enable bits */
    UCSRB_REG &= ~((1 << 7) | (1 << 6));
    
    switch (Copy_u8InterruptMode)
    {
        case UART_INT_RX_ENABLED:
            UCSRB_REG |= (1 << 7); // RXCIE
            break;
        case UART_INT_TX_ENABLED:
            UCSRB_REG |= (1 << 6); // TXCIE
            break;
        case UART_INT_BOTH_ENABLED:
            UCSRB_REG |= (1 << 7) | (1 << 6); // RXCIE and TXCIE
            break;
        default:
            break;
    }
}

void UART_voidFlush(void)
{
    u8 Local_u8Dummy;
    
    /* Clear any pending received data */
    while (UCSRA_REG & (1 << 7))
    {
        Local_u8Dummy = UDR_REG;
    }
    
    /* Wait for any transmission to complete */
    while (!(UCSRA_REG & (1 << 6)));
}

/* Private Functions */

static u16 UART_u16CalculateBaudRate(u32 Copy_u32BaudRate)
{
    return (u16)((F_CPU / (16UL * Copy_u32BaudRate)) - 1);
}

static UART_Status_t UART_u8CheckErrors(void)
{
    u8 Local_u8Status = UCSRA_REG;
    
    if (Local_u8Status & (1 << 4)) // Frame Error
    {
        return UART_FRAME_ERROR;
    }
    
    if (Local_u8Status & (1 << 3)) // Data Overrun
    {
        return UART_OVERRUN_ERROR;
    }
    
    if (Local_u8Status & (1 << 2)) // Parity Error
    {
        return UART_PARITY_ERROR;
    }
    
    return UART_OK;
}

/* Interrupt Service Routines */

/* RX Complete Interrupt */
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
    u8 Local_u8ReceivedData = UDR_REG;
    
    if (UART_pvRxCallback != NULL)
    {
        UART_pvRxCallback(Local_u8ReceivedData);
    }
}

/* TX Complete Interrupt */
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
    if (UART_pvTxCallback != NULL)
    {
        UART_pvTxCallback();
    }
}
