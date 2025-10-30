#ifndef UART_PRIV_H_
#define UART_PRIV_H_

/* This Register has The Data of The Trans Or Rec*
 * *******************************************************/
#define UDR_REG		(*(volatile u8*)0x2C)
/******************************************************************/

/* This Register Control and Status Register (Flags)
 * ****************************************************************
* Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
* RXC 		TXC 	UDRE 	FE 		DOR 	PE 		U2X 	MPCM
******************************************************************
* RXC    >> USART Receive Complete Flag
* TXC    >> USART Transmit Complete Flag
* UDRE   >> USART Data Register Empty Flag
* FE     >> Frame Error Flag
* DOR    >> Data OverRun Flag
* PE     >> Parity Error Flag
* U2X    >> Double the USART Transmission Speed
* MPCM   >> Multi-processor Communication Mode
* ****************************************************************/
#define UCSRA_REG		(*(volatile u8*)0x2B)
/******************************************************************/


/* This Register Control and Status Register (INTR)
 * ****************************************************************
* Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
* RXCIE 	TXCIE 	UDRIE 	RXEN 	TXEN 	UCSZ2 	RXB8 	TXB8
*******************************************************************
* RXCIE   >> RX Complete Interrupt Enable
* TXCIE   >> TX Complete Interrupt Enable
* UDRIE   >> USART Data Register Empty Interrupt Enable
* RXEN    >> Receiver Enable
* TXEN    >> Transmitter Enable
* UCSZ2   >> Character Size
* RXB8    >> Receive Data Bit 8
* TXB8    >> Transmit Data Bit 8
* ****************************************************************/
#define UCSRB_REG		(*(volatile u8*)0x2A)
/******************************************************************/

/* This Register Control and Status Register
 * ****************************************************************
* Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
* URSEL 	UMSEL 	UPM1 	UPM0 	USBS 	UCSZ1 	UCSZ0 	UCPOL
*******************************************************************
* URSEL  	 	>> Register Select
* UMSEL 	 	>> USART Mode Select(Asynchronous OR Synchronous )
* UPM1,UPM0  	>> Parity Mode
* USBS  	 	>> Stop Bit Select (1 , 2 Bit)
* UCSZ1,UCSZ0	>> Character Size
* UCPOL 	 	>> Clock Polarity
* ****************************************************************/
#define UCSRC_REG		(*(volatile u8*)0x40)
/******************************************************************/

/* This Register Control and Status Register
* ****************************************************************
* Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
* URSEL 	UMSEL 	UPM1 	UPM0 	USBS 	UCSZ1 	UCSZ0 	UCPOL
*******************************************************************
* URSEL  	 	>> Register Select
* UMSEL 	 	>> USART Mode Select(Asynchronous OR Synchronous )
* UPM1,UPM0  	>> Parity Mode
* USBS  	 	>> Stop Bit Select (1 , 2 Bit)
* UCSZ1,UCSZ0	>> Character Size
* UCPOL 	 	>> Clock Polarity
* ****************************************************************/
#define UCSRC_REG		(*(volatile u8*)0x40)
/******************************************************************/


/* This Register Has High Value Of BoudRate REG
* ****************************************************************
* Bit7		Bit3	Bit2	Bit1	Bit0
* URSEL 	UBRR[11:8]
*******************************************************************
* URSEL  	 	>> Register Select
* UBRR[11:8]	>> USART Baud Rate Register High
* ****************************************************************/
#define UBRRH_REG		(*(volatile u8*)0x40)
/******************************************************************/


/* This Register Has Low Value Of BoudRate REG
* ****************************************************************
* UBRR[7:0]		>> USART Baud Rate Register Low
* ****************************************************************/
#define UBRRL_REG		(*(volatile u8*)0x29)
/******************************************************************/

/* This Register Has The Enable Of All Interrupts
 * Bit7
 * I		*/
#define  SR_REG 	 (*(volatile u8*)0x5F)
/***************************************************/

#endif /* UART_PRIV_H_ */
