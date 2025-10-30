/*
 * ICU_Config.h
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */

#ifndef ICU_CONFIG_H_
#define ICU_CONFIG_H_

/* ICU Configuration using Timer0 and External Interrupt */

/* External Interrupt Selection for ICU
 * Options:
 * 0 - Use INT0 (PD2)
 * 1 - Use INT1 (PD3)
 * 2 - Use INT2 (PB2)
 */
#define ICU_EXT_INT_NUM         0

/* Timer0 Configuration for ICU timing */
#define ICU_TIMER0_PRESCALER    CLK_8_PRESCALER   /* Use 8 prescaler for good resolution */

/* Edge Detection Mode
 * Options:
 * DIO_INT_R_EDGE    - Rising Edge
 * DIO_INT_F_EDGE    - Falling Edge
 * DIO_INT_R_F_EDGE  - Both Edges
 */
#define ICU_EDGE_MODE           DIO_INT_R_F_EDGE

/* Maximum measurement time in Timer0 overflows */
#define ICU_MAX_OVERFLOWS       100

#endif /* ICU_CONFIG_H_ */
