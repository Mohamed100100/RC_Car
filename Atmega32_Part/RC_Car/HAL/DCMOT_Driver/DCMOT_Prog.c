/*
 * DCMOT_Prog.c
 *
 *  Created on: ١٧‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO_Driver/DIO_Int.h"

#include "DCMOT_Init.h"
#include "DCMOT_Confg.h"

void DCMOT_1_vidInit(void)
{
	DIO_vidSetPinDir(DC_MOT_1_PORT_S1, DC_MOT_1_PIN_S1, DIO_OUTPUT);
	DIO_vidSetPinDir(DC_MOT_1_PORT_S2, DC_MOT_1_PIN_S2, DIO_OUTPUT);

	DIO_vidSetPinVal(DC_MOT_1_PORT_S1, DC_MOT_1_PIN_S1, DIO_LOW);
	DIO_vidSetPinVal(DC_MOT_1_PORT_S2, DC_MOT_1_PIN_S2, DIO_LOW);
}

void DCMOT_2_vidInit(void)
{
	DIO_vidSetPinDir(DC_MOT_2_PORT_S1, DC_MOT_2_PIN_S1, DIO_OUTPUT);
	DIO_vidSetPinDir(DC_MOT_2_PORT_S2, DC_MOT_2_PIN_S2, DIO_OUTPUT);

	DIO_vidSetPinVal(DC_MOT_2_PORT_S1, DC_MOT_2_PIN_S1, DIO_LOW);
	DIO_vidSetPinVal(DC_MOT_2_PORT_S2, DC_MOT_2_PIN_S2, DIO_LOW);
}

void DCMOT_1_vidRotCW(void)
{
	DCMOT_1_vidStop();
	DIO_vidSetPinVal(DC_MOT_1_PORT_S1, DC_MOT_1_PIN_S1, DIO_HIGH);
}

void DCMOT_2_vidRotCW(void)
{
	DCMOT_2_vidStop();
	DIO_vidSetPinVal(DC_MOT_2_PORT_S1, DC_MOT_2_PIN_S1, DIO_HIGH);
}

void DCMOT_1_vidRotCCW(void)
{
	DCMOT_1_vidStop();
	DIO_vidSetPinVal(DC_MOT_1_PORT_S2, DC_MOT_1_PIN_S2, DIO_HIGH);
}

void DCMOT_2_vidRotCCW(void)
{
	DCMOT_2_vidStop();
	DIO_vidSetPinVal(DC_MOT_2_PORT_S2, DC_MOT_2_PIN_S2, DIO_HIGH);
}


void DCMOT_1_vidStop(void)
{
	DIO_vidSetPinVal(DC_MOT_1_PORT_S1, DC_MOT_1_PIN_S1, DIO_LOW);
	DIO_vidSetPinVal(DC_MOT_1_PORT_S2, DC_MOT_1_PIN_S2, DIO_LOW);
}

void DCMOT_2_vidStop(void)
{
	DIO_vidSetPinVal(DC_MOT_2_PORT_S1, DC_MOT_2_PIN_S1, DIO_LOW);
	DIO_vidSetPinVal(DC_MOT_2_PORT_S2, DC_MOT_2_PIN_S2, DIO_LOW);
}
