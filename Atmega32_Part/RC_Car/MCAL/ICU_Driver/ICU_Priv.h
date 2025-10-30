///*
// * ICU_Priv.h
// *
// *  Created on: Oct 17, 2025
// *      Author: Eng.Gemy
// */
//
//#ifndef ICU_PRIV_H_
//#define ICU_PRIV_H_
//
///* External Interrupt Registers */
//#define MCUCR_REG       (*(volatile u8*)0x55)  /* MCU Control Register */
//#define MCUCSR_REG      (*(volatile u8*)0x54)  /* MCU Control and Status Register */
//#define GICR_REG        (*(volatile u8*)0x5B)  /* General Interrupt Control Register */
//#define GIFR_REG        (*(volatile u8*)0x5A)  /* General Interrupt Flag Register */
//
///* Timer0 Registers */
//#define TCCR0_REG       (*(volatile u8*)0x53)  /* Timer/Counter0 Control Register */
//#define TCNT0_REG       (*(volatile u8*)0x52)  /* Timer/Counter0 Register */
//#define TIMSK_REG       (*(volatile u8*)0x59)  /* Timer/Counter Interrupt Mask Register */
//#define TIFR_REG        (*(volatile u8*)0x58)  /* Timer/Counter Interrupt Flag Register */
//
///* Port D Register (for INT0/INT1 pins) */
//#define PORTD_REG       (*(volatile u8*)0x32)
//#define DDRD_REG        (*(volatile u8*)0x31)
//#define PIND_REG        (*(volatile u8*)0x30)
//
///* Global Interrupt Enable Register */
//#define SREG_REG        (*(volatile u8*)0x5F)
//
///* External Interrupt Bit Definitions */
//#define INT0_BIT        6  /* INT0 Enable bit in GICR */
//#define INT1_BIT        7  /* INT1 Enable bit in GICR */
//#define INTF0_BIT       6  /* INT0 Flag bit in GIFR */
//#define INTF1_BIT       7  /* INT1 Flag bit in GIFR */
//
///* Interrupt Sense Control Bits */
//#define ISC00_BIT       0  /* INT0 Sense Control bit 0 */
//#define ISC01_BIT       1  /* INT0 Sense Control bit 1 */
//#define ISC10_BIT       2  /* INT1 Sense Control bit 0 */
//#define ISC11_BIT       3  /* INT1 Sense Control bit 1 */
//
///* Timer0 Control Bits */
//#define CS00_BIT        0  /* Clock Select bit 0 */
//#define CS01_BIT        1  /* Clock Select bit 1 */
//#define CS02_BIT        2  /* Clock Select bit 2 */
//#define TOIE0_BIT       0  /* Timer0 Overflow Interrupt Enable */
//#define TOV0_BIT        0  /* Timer0 Overflow Flag */
//
///* Interrupt Pin Definitions */
//#define ICU_INT0_PIN    2  /* PD2 - INT0 pin */
//#define ICU_INT1_PIN    3  /* PD3 - INT1 pin */
//
///* Timer0 Prescaler Options */
//#define ICU_TIMER_STOP          0x00
//#define ICU_TIMER_PRESCALER_1   0x01
//#define ICU_TIMER_PRESCALER_8   0x02
//#define ICU_TIMER_PRESCALER_64  0x03
//#define ICU_TIMER_PRESCALER_256 0x04
//#define ICU_TIMER_PRESCALER_1024 0x05
//
///* ICU State Macros */
//#define ICU_STATE_IDLE          0
//#define ICU_STATE_MEASURING     1
//#define ICU_STATE_COMPLETE      2
//
///* Status Macros */
//#define ICU_OK                  0x00
//#define ICU_ERROR               0x01
//#define ICU_TIMEOUT             0x02
//#define ICU_BUSY                0x03
//#define ICU_INVALID_PARAMETER   0x04
//
///* Timeout Values */
//#define ICU_TIMEOUT_COUNT       65000
//
//#endif /* ICU_PRIV_H_ */
