/*
 * TIMER_Confg.h
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#ifndef TIMER1_CONFG_H_
#define TIMER1_CONFG_H_



/************** You Will Put The Clock Select Of Timer1 (CLK = 1/F_CPU)*/
/**************** You have 8 Choices ***********************************/
/**************** (1) NO_CLK_OFF         *******************************/
/*****************(2) CLK_NO_PRESCALER   *******************************/
/**************** (3) CLK_8_PRESCALER    *******************************/
/**************** (4) CLK_64_PRESCALER   *******************************/
/**************** (5) CLK_256_PRESCALER  *******************************/
/**************** (6) CLK_1024_PRESCALER *******************************/
/**************** (7) EXT_CLK_F_EDGE     *******************************/
/**************** (8) EXT_CLK_R_EDGE     *******************************/
/***********************************************************************/
#define CLOCK_SELECT	CLK_64_PRESCALER
/***********************************************************************/


/***********************************************************************/
/**************** You Will Put The Modes Of Timer1 (Channel A) *********/
/**************** You have 16 Choices ***********************************/
/*
|----| |--------------------------------|------|
|Mode| |  Mode of Operation(channel A)	| TOP  |
|----| |--------------------------------|------|
| 01 | |Normal 						    |0xFFFF|
| 02 | |PWM, Phase Correct, 8-bit 	    |0x00FF|
| 03 | |PWM, Phase Correct, 9-bit 	    |0x01FF|
| 04 | |PWM, Phase Correct, 10-bit 	    |0x03FF|
| 05 | |CTC 						    |OCR1A |
| 06 | |FastPWM, 8-bit 			     	|0x00FF|
| 07 | |FastPWM, 9-bit 			     	|0x01FF|
| 08 | |FastPWM, 10-bit 			    |0x03FF|
| 09 | |PWM,Phase and Frequency Correct |ICR1  |
| 10 | |PWM,Phase and Frequency Correct |OCR1A |
| 11 | |PWM,Phase Correct 				|ICR1  |
| 12 | |PWM,Phase Correct 				|OCR1A |
| 13 | |CTC 							|ICR1  |
| 14 | |Fast PWM 						|ICR1  |
| 15 | |Fast PWM 						|OCR1A |
|----| |--------------------------------|------|
*/
/**************** (1)  MODE_01 *****************************************/
/*****************(2)  MODE_02 *****************************************/
/**************** (3)  MODE_03 *****************************************/
/**************** (4)  MODE_04 *****************************************/
/**************** (5)  MODE_05 *****************************************/
/**************** (6)  MODE_06 *****************************************/
/**************** (7)  MODE_07 *****************************************/
/**************** (8)  MODE_08 *****************************************/
/**************** (9)  MODE_09 *****************************************/
/**************** (10) MODE_10 *****************************************/
/**************** (11) MODE_11 *****************************************/
/**************** (12) MODE_12 *****************************************/
/**************** (13) MODE_13 *****************************************/
/**************** (14) MODE_14 *****************************************/
/**************** (15) MODE_15 *****************************************/
/***********************************************************************/
#define TIMER1_MODE		MODE_14
/***********************************************************************/


/* If You Choose MODE_01 (Normal Mode)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_OverFlowMode(u16 u16InitVal);
*  Don't Forget That It Has The Top Equal 0xFFFF (Handle Your Calculations)
*  You May Need To Enable Any Interrupt You Can Do This By Using The Helper Functions(Look At Init File)
*/

/* If You Choose MODE_02 (PWM, Phase Correct, 8-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  Don't Forget That It Has The Top Equal 0xFF (Handle Your Calculations)
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  Don't Forget That (Top(0xFF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*/

/* If You Choose MODE_03 (PWM, Phase Correct, 9-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  Don't Forget That It Has The Top Equal 0x1FF (Handle Your Calculations)
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  Don't Forget That (Top(0x1FF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*/

/* If You Choose MODE_04 (PWM, Phase Correct, 10-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  Don't Forget That It Has The Top Equal 0x3FF (Handle Your Calculations)
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  Don't Forget That (Top(0x3FF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*/

/* If You Choose MODE_05 (CTC)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_CTCMode(u16 u8InitVal , u16 u16CompareValue,u8 u8CTCMode,u8 u8Channel);
*  When You Want To Choose u8CTCMode -->> Write TIMER1_CTC_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A
*  Don't Forget That Top is OCR1A << After that It Count From zero Again
*  So If You Want To Choose Make OCR1B To Fire Its Interrupt And Use Its Pin
*  You Should Set The Value Of OCR1B By Helper Function (Before Call The Above Function)
*/

/* If You Choose MODE_06 (FastPWM, 8-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);
*  When You Want To Choose u8PWMMode -->> Write TIMER1_PWM_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  Don't Forget That (Top(0xFF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*/

/* If You Choose MODE_07 (FastPWM, 9-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);
*  When You Want To Choose u8PWMMode -->> Write TIMER1_PWM_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  Don't Forget That (Top(0x1FF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*/


/* If You Choose MODE_08 (FastPWM, 10-bit)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);
*  When You Want To Choose u8PWMMode -->> Write TIMER1_PWM_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  Don't Forget That (Top(0x3FF) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*/

/* If You Choose MODE_09 (PWM,Phase and Frequency Correct)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  Don't Forget That It Has The Top Equal (ICR1) (Handle Your Calculations)
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  You Should Call This Function To Set The Value Of ICR1 (Before you call the above)
*  void TIMER1_vidSetInputCaptureReg(u16 u16InputCapture);
*  Don't Forget That (Top(ICR1) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*/


/* If You Choose MODE_10 (PWM,Phase and Frequency Correct)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  Don't Forget That It Has The Top Equal (OCR1A) (Handle Your Calculations)
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  You Should Call This Function To Set The Value Of OCR1A (Before you call the above)
*  void TIMER1_vidSetComparReg_ChannelA(u16 u16CompareValue);
*  Don't Forget That (Top(OCR1A) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*/


/* If You Choose MODE_11 (PWM, Phase Correct)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  You Should Call This Function To Set The Value Of ICR1 (Before you call the above)
*  void TIMER1_vidSetInputCaptureReg(u16 u16InputCapture);
*  Don't Forget That (Top(ICR1) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*/

/* If You Choose MODE_12 (PWM, Phase Correct)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);
*  When You Want To Choose u8PhsCrrectMode -->> Write TIMER1_PHASECORRECT_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  You Should Call This Function To Set The Value Of OCR1A (Before you call the above)
*  void TIMER1_vidSetComparReg_ChannelA(u16 u16CompareValue);
*  Don't Forget That (Top(OCR1A) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*/

/* If You Choose MODE_13 (CTC)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_CTCMode(u16 u8InitVal , u16 u16CompareValue,u8 u8CTCMode,u8 u8Channel);
*  When You Want To Choose u8CTCMode -->> Write TIMER1_CTC_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At ICR1
*  Don't Forget That Top is ICR1 << After that It Count From zero Again
*  So If You Want To Choose Make OCR1B To Fire Its Interrupt And Use Its Pin
*  You Should Set The Value Of OCR1B By Helper Function (Before Call The Above Function)
*/

/* If You Choose MODE_14 (FastPWM)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);
*  When You Want To Choose u8PWMMode -->> Write TIMER1_PWM_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  Don't Forget That (Top(ICR1) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*  You Should Call This Function To Set The Value Of ICR1 (Before you call the above)
*  void TIMER1_vidSetInputCaptureReg(u16 u16InputCapture);
*/

/* If You Choose MODE_15 (FastPWM)
*  This is The Functions Which You Can Use It
*  void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);
*  When You Want To Choose u8PWMMode -->> Write TIMER1_PWM_ <<-- And Choose
*  When You Want To Choose u8Channel -->> Write TIMER1_CHANNEL_ <<-- And Choose
*  Don't Forget That Compared Value Will Be Located At OCR1A Or OCR1B (According your choice)
*  Don't Forget That (Top(OCR1A) > u16CompareValue) <<< Must
*  NOTE >>> if You Want To Make The A&B Call This Function Twice
*  If You Want To Open Any Interrupt During Counting You Can Use The Helper Functions
*  You Should Call This Function To Set The Value Of OCR1A (Before you call the above)
*  void TIMER1_vidSetComparReg_ChannelA(u16 u16CompareValue);
*/

/*************************/
/*This Part For Explain*/
/*************************/
/*Tick Time  = 1/(F_CPU/PreScaller)
 * OverFlow Time = Tick Time * Top (256)*/




#endif /* TIMER1_CONFG_H_ */
