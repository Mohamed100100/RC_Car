/*
 * ICU_Prog.c
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO_Driver/DIO_Int.h"
#include "../../MCAL/TIMER0_Driver/TIMER0_Init.h"

#include "ICU_Init.h"
#include "ICU_Config.h"

/* Global Variables */
static volatile u8 g_u8ICUState = ICU_STATE_IDLE;
static volatile u32 g_u32StartTime = 0;
static volatile u32 g_u32EndTime = 0;
static volatile u32 g_u32OverflowCount = 0;
static volatile u8 g_u8EdgeCount = 0;

/* Private Function Prototypes */
static void ICU_voidExtIntCallback(void);
static void ICU_voidTimer0OverflowCallback(void);
static u32 ICU_u32GetCurrentTime(void);

u8 ICU_u8Init(void)
{
    /* Initialize Timer0 in normal mode */
    TIMER0_vidInit();

    /* Set Timer0 overflow callback */
    Timer0_OF_Call_Back = ICU_voidTimer0OverflowCallback;

    /* Configure external interrupt */
    #if ICU_EXT_INT_NUM == 0
        EXT_INT0_Call_Back = ICU_voidExtIntCallback;
    #elif ICU_EXT_INT_NUM == 1
        EXT_INT1_Call_Back = ICU_voidExtIntCallback;
    #elif ICU_EXT_INT_NUM == 2
        EXT_INT2_Call_Back = ICU_voidExtIntCallback;
    #endif

    /* Initialize state */
    g_u8ICUState = ICU_STATE_IDLE;
    g_u32StartTime = 0;
    g_u32EndTime = 0;
    g_u32OverflowCount = 0;
    g_u8EdgeCount = 0;

    return ICU_OK;
}

u8 ICU_u8StartMeasurement(void)
{
    /* Check if already measuring */
    if (g_u8ICUState == ICU_STATE_MEASURING)
    {
        return ICU_BUSY;
    }

    /* Stop any previous timer */
    TIMER0_vidStopTimer();

    /* Reset variables */
    g_u32StartTime = 0;
    g_u32EndTime = 0;
    g_u32OverflowCount = 0;
    g_u8EdgeCount = 0;

    /* Clear timer counter */
    TIMER0_vidSetInitReg(0);

    /* Start Timer0 with overflow interrupt */
    TIMER0_vidStartTimer_OverFlowMode(0);

    /* Enable external interrupt */
    DIO_vidEnableIntrupt(ICU_EXT_INT_NUM, ICU_EDGE_MODE);

    /* Set state to measuring */
    g_u8ICUState = ICU_STATE_MEASURING;

    return ICU_OK;
}

void ICU_voidReset(void)
{
    /* Stop measurement */
    TIMER0_vidStopTimer();

    /* Disable external interrupt */
    DIO_vidDisableExtInt(ICU_EXT_INT_NUM);

    /* Reset all variables */
    g_u32StartTime = 0;
    g_u32EndTime = 0;
    g_u32OverflowCount = 0;
    g_u8EdgeCount = 0;
    g_u8ICUState = ICU_STATE_IDLE;
}

u8 ICU_u8StopMeasurement(void)
{
    /* Stop Timer0 */
    TIMER0_vidStopTimer();

    /* Disable external interrupt */
    DIO_vidDisableExtInt(ICU_EXT_INT_NUM);

    /* Set state to idle */
    g_u8ICUState = ICU_STATE_IDLE;

    return ICU_OK;
}

u8 ICU_u8GetMeasuredTime(u32* Copy_pu32Time)
{
    if (Copy_pu32Time == NULL)
    {
        return ICU_ERROR;
    }

    if (g_u8ICUState != ICU_STATE_COMPLETE)
    {
        return ICU_ERROR;
    }

    /* Calculate total time in Timer0 counts */
    *Copy_pu32Time = g_u32EndTime - g_u32StartTime;

    return ICU_OK;
}

u8 ICU_u8GetMeasuredTimeUs(u32* Copy_pu32TimeUs)
{
    u32 Local_u32TimeCounts;
    u8 Local_u8Status;

    if (Copy_pu32TimeUs == NULL)
    {
        return ICU_ERROR;
    }

    /* Get measured time in counts */
    Local_u8Status = ICU_u8GetMeasuredTime(&Local_u32TimeCounts);
    if (Local_u8Status != ICU_OK)
    {
        return Local_u8Status;
    }

    /* Convert to microseconds based on Timer0 configuration */
    /* Timer0 with 8 prescaler: 16MHz/8 = 2MHz, 1 count = 0.5us */
    *Copy_pu32TimeUs = (Local_u32TimeCounts * 1) / 2;  /* 0.5us per count */

    return ICU_OK;
}

u8 ICU_u8IsMeasurementComplete(void)
{
    return (g_u8ICUState == ICU_STATE_COMPLETE) ? 1 : 0;
}

u8 ICU_u8GetState(void)
{
    return g_u8ICUState;
}



/* Private Functions */

static void ICU_voidExtIntCallback(void)
{
    if (g_u8ICUState == ICU_STATE_MEASURING)
    {
        if (g_u8EdgeCount == 0)
        {
            /* First edge - start measurement */
            g_u32StartTime = ICU_u32GetCurrentTime();
            g_u8EdgeCount = 1;
        }
        else
        {
            /* Second edge - complete measurement */
            g_u32EndTime = ICU_u32GetCurrentTime();
            g_u8ICUState = ICU_STATE_COMPLETE;

            /* Stop timer and interrupt */
            TIMER0_vidStopTimer();
            DIO_vidDisableExtInt(ICU_EXT_INT_NUM);
        }
    }
}

static void ICU_voidTimer0OverflowCallback(void)
{
    g_u32OverflowCount++;

    /* Check for timeout */
    if (g_u32OverflowCount > ICU_MAX_OVERFLOWS)
    {
        /* Timeout - reset measurement */
        ICU_voidReset();
    }
}

static u32 ICU_u32GetCurrentTime(void)
{
    /* Return current time as (overflows * 256) + current timer value */
    return (g_u32OverflowCount * 256) + TIMER0_vidGetCounterReg();
}
