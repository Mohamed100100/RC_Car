/*
 * DIO_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: vmk9p-'
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_Priv.h"
#include "DIO_Int.h"




void DIO_vidSetPinDir(u8 u8PortId , u8 u8PinId , u8 u8PinDir)
{
	if ((u8PortId <= DIO_PORTD)&&(u8PinId <= DIO_PIN7))
	{
		if(u8PinDir == DIO_OUTPUT)
		{
			switch(u8PortId)
			{
			case (DIO_PORTA) : SET_BIT(DDRA_REG , u8PinId); break;
			case (DIO_PORTB) : SET_BIT(DDRB_REG , u8PinId); break;
			case (DIO_PORTC) : SET_BIT(DDRC_REG , u8PinId); break;
			case (DIO_PORTD) : SET_BIT(DDRD_REG , u8PinId); break;
			}
		}
		else if(u8PinDir == DIO_INPUT)
		{
			switch(u8PortId)
			{
			case (DIO_PORTA) : CLR_BIT(DDRA_REG , u8PinId); break;
			case (DIO_PORTB) : CLR_BIT(DDRB_REG , u8PinId); break;
			case (DIO_PORTC) : CLR_BIT(DDRC_REG , u8PinId); break;
			case (DIO_PORTD) : CLR_BIT(DDRD_REG , u8PinId); break;
			}
		}
		else{/* wrong Pin Direction */}
	}
	else{/* wrong PortId OR PinId  */}
}

void DIO_vidSetPinVal(u8 u8PortId , u8 u8PinId , u8 u8PinVal){
	if ((u8PortId <= DIO_PORTD)&&(u8PinId <= DIO_PIN7))
	{
		if(u8PinVal == DIO_HIGH)
		{
			switch(u8PortId)
			{
			case (DIO_PORTA) : SET_BIT(PORTA_REG , u8PinId); break;
			case (DIO_PORTB) : SET_BIT(PORTB_REG , u8PinId); break;
			case (DIO_PORTC) : SET_BIT(PORTC_REG , u8PinId); break;
			case (DIO_PORTD) : SET_BIT(PORTD_REG , u8PinId); break;
			}
		}
		else if(u8PinVal == DIO_INPUT)
		{
			switch(u8PortId)
			{
			case (DIO_PORTA) : CLR_BIT(PORTA_REG , u8PinId); break;
			case (DIO_PORTB) : CLR_BIT(PORTB_REG , u8PinId); break;
			case (DIO_PORTC) : CLR_BIT(PORTC_REG , u8PinId); break;
			case (DIO_PORTD) : CLR_BIT(PORTD_REG , u8PinId); break;
			}
		}
		else{/* wrong Pin Value */}

	}
	else{/* wrong PortId OR PinId  */}

}

void DIO_vidTogglePinVal(u8 u8PortId , u8 u8PinId)
{
	if ((u8PortId <= DIO_PORTD)&&(u8PinId <= DIO_PIN7))
	{
		switch(u8PortId)
		{
		case (DIO_PORTA) : TOG_BIT(PORTA_REG , u8PinId); break;
		case (DIO_PORTB) : TOG_BIT(PORTB_REG , u8PinId); break;
		case (DIO_PORTC) : TOG_BIT(PORTC_REG , u8PinId); break;
		case (DIO_PORTD) : TOG_BIT(PORTD_REG , u8PinId); break;
		}
	}
	else{/* wrong PortId OR PinId  */}
}

/*Warning you can't use this function except you are sure that the pin is input*/
void DIO_vidEnablePullUpRes(u8 u8PortId , u8 u8PinId)
{
	{
		if ((u8PortId <= DIO_PORTD)&&(u8PinId <= DIO_PIN7))
		{
			switch(u8PortId)
			{
			case (DIO_PORTA) : SET_BIT(PORTA_REG , u8PinId); break;
			case (DIO_PORTB) : SET_BIT(PORTB_REG , u8PinId); break;
			case (DIO_PORTC) : SET_BIT(PORTC_REG , u8PinId); break;
			case (DIO_PORTD) : SET_BIT(PORTD_REG , u8PinId); break;
			}
		}
		else{/* wrong PortId OR PinId  */}
	}
}

/*this function will return only 0x01 OR 0x00*/
u8 DIO_u8GetPinVal(u8 u8PortId , u8 u8PinId)
{
	u8 u8Result;
	if ((u8PortId <= DIO_PORTD)&&(u8PinId <= DIO_PIN7))
	{
		switch(u8PortId)
		{
		case (DIO_PORTA) : u8Result = GET_BIT(PINA_REG , u8PinId); break;
		case (DIO_PORTB) : u8Result = GET_BIT(PINB_REG , u8PinId); break;
		case (DIO_PORTC) : u8Result = GET_BIT(PINC_REG , u8PinId); break;
		case (DIO_PORTD) : u8Result = GET_BIT(PIND_REG , u8PinId); break;
		}
	}
	else
	{/* wrong PortId OR PinId  */
		u8Result = DIO_UNDEFINED_VALUE;
	}
	return u8Result;
}


u8 DIO_u8GetPortVal(u8 u8PortId )
{
	u8 u8Result;
	switch(u8PortId)
	{
	case (DIO_PORTA) : u8Result = PINA_REG ; break;
	case (DIO_PORTB) : u8Result = PINB_REG ; break;
	case (DIO_PORTC) : u8Result = PINC_REG ; break;
	case (DIO_PORTD) : u8Result = PIND_REG ; break;
	default :/* wrong PortId  */
		u8Result = DIO_UNDEFINED_VALUE;break;
	}

	return u8Result;
}

void DIO_vidSetPortDir(u8 u8PortId , u8 u8PortDir)
{
	switch(u8PortId)
	{
	case (DIO_PORTA) : DDRA_REG = u8PortDir; break;
	case (DIO_PORTB) : DDRB_REG = u8PortDir; break;
	case (DIO_PORTC) : DDRC_REG = u8PortDir; break;
	case (DIO_PORTD) : DDRD_REG = u8PortDir; break;
	default :/* wrong PortId OR PinId  */    break;
	}

}

void DIO_vidSetPortVal(u8 u8PortId , u8 u8PortVal)
{
	switch(u8PortId)
	{
	case (DIO_PORTA) : PORTA_REG = u8PortVal; break;
	case (DIO_PORTB) : PORTB_REG = u8PortVal; break;
	case (DIO_PORTC) : PORTC_REG = u8PortVal; break;
	case (DIO_PORTD) : PORTD_REG = u8PortVal; break;
	default :/* wrong PortId OR PinId  */     break;
	}
}


void DIO_vidEnableIntrupt(u8 u8InterNum, u8 u8InterStat)
{
	if((u8InterNum<3)&&(u8InterStat<4))
	{
		/*Enable All Interrupts*/
		SET_BIT(SR_REG,7);

		switch(u8InterNum)
		{
		/*Interrupt 0(INT0)*/
		case 0:
			/*Make The INT0 Pin As Input	&PullUp Res*/
			DIO_vidSetPinDir(DIO_PORTD,DIO_PIN2,DIO_INPUT);
			DIO_vidEnablePullUpRes(DIO_PORTD,DIO_PIN2);

			switch(u8InterStat)
			{
			/*Low Level Interrupt*/
			case 0:	CLR_BIT(MCUCR_REG,1);CLR_BIT(MCUCR_REG,0);break;

			/*Raising Or Falling Edge*/
			case 1:CLR_BIT(MCUCR_REG,1);SET_BIT(MCUCR_REG,0);break;

			/*Falling Edge*/
			case 2:SET_BIT(MCUCR_REG,1);CLR_BIT(MCUCR_REG,0);break;

			/*Raising Edge*/
			case 3:SET_BIT(MCUCR_REG,1);SET_BIT(MCUCR_REG,0);break;
			}

			/*Enable Interrupt 0*/
			SET_BIT(GICR_REG,6);
			break;

			/*Interrupt 1(INT1)*/
			case 1:
				/*Make The INT1 Pin As Input	&PullUp Res*/
				DIO_vidSetPinDir(DIO_PORTD,DIO_PIN3,DIO_INPUT);
				DIO_vidEnablePullUpRes(DIO_PORTD,DIO_PIN3);

				switch(u8InterStat)
				{
				/*Low Level Interrupt*/
				case 0:	CLR_BIT(MCUCR_REG,3);CLR_BIT(MCUCR_REG,2);break;

				/*Raising Or Falling Edge*/
				case 1:CLR_BIT(MCUCR_REG,3);SET_BIT(MCUCR_REG,2);break;

				/*Falling Edge*/
				case 2:SET_BIT(MCUCR_REG,3);CLR_BIT(MCUCR_REG,2);break;

				/*Raising Edge*/
				case 3:SET_BIT(MCUCR_REG,3);SET_BIT(MCUCR_REG,2);break;
				}
				/*Enable Interrupt 1*/
				SET_BIT(GICR_REG,7);
				break;

				/*Interrupt 2(INT2)*/
				case 2:


					switch(u8InterStat)
					{
					/*Falling Edge*/
					case 2:CLR_BIT(MCUCSR_REG,6);

					/*Make The INT2 Pin As Input	&PullUp Res*/
					DIO_vidSetPinDir(DIO_PORTB,DIO_PIN2,DIO_INPUT);
					DIO_vidEnablePullUpRes(DIO_PORTB,DIO_PIN2);

					SET_BIT(GICR_REG,5);
					break;

					/*Raising Edge*/
					case 3:SET_BIT(MCUCSR_REG,6);break;

					/*Make The INT2 Pin As Input	&PullUp Res*/
					DIO_vidSetPinDir(DIO_PORTB,DIO_PIN2,DIO_INPUT);
					DIO_vidEnablePullUpRes(DIO_PORTB,DIO_PIN2);

					/*Enable Interrupt 2*/
					SET_BIT(GICR_REG,5);
					break;
					}
					break;
		}
	}
}


void DIO_vidDisableExtInt(u8 u8InterNum){
	switch(u8InterNum)
	{
	/*Interrupt 0(INT0)*/
	case 0 :CLR_BIT(GICR_REG, u8InterNum);break;
	case 1 :CLR_BIT(GICR_REG, u8InterNum);break;
	}
}



void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXT_INT0_Call_Back != NULL){
		EXT_INT0_Call_Back();
	}

}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXT_INT1_Call_Back != NULL){
		EXT_INT1_Call_Back();
	}

}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXT_INT2_Call_Back != NULL){
		EXT_INT2_Call_Back();
	}

}








