/*
 * File:   main.c
 * Author: gwiley
 *
 * Hardware: StarUSB/PIC18F2550
 * Clock: 8.0Mhz ext, 48.0Mhz PLL
 * Compiler: 
 *
 * porta is output
 * portb is input b/c it has internal pullup resistors
 * RC6-TX (connect to pin 2 on FTDI) UART 1200 baud
 * RC7-RX (connect to pin 3 on FTDI)
 * Delay10TCYx(15) = 600us

 */

#include <p18cxxx.h>
#include <p18f2550.h>
#include <delays.h>
#include <stdio.h>
#include <usart.h>

#pragma config PLLDIV   = 1
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 1
#pragma config FOSC     = INTOSCIO_EC
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = OFF
#pragma config BORV     = 3
#pragma config VREGEN   = OFF       //USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = OFF
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
#pragma config STVREN   = OFF
#pragma config CCP2MX   = ON
#pragma config LVP      = ON
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
#pragma config CPB      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
#pragma config EBTRB    = OFF

#define RCE_MAXMSGLEN   40           // longest string to print to uart

//---------------------------------------- main
void main(void)  {
    char led = 0;
    char resstr[40];
    int  adres;
	int  ctr;

    //-------------------- chip setup

    CMCON = 0X0E;
    PORTA = 0xFF;
    TRISA = 0xFF;
    PORTB = 0x00;
    TRISB = 0xFF;
    TRISC = 0xFF;

    INTCONbits.GIE = 0;

    //-------------------- serial IO setup

    OpenUSART (USART_TX_INT_OFF &
        USART_RX_INT_OFF &
        USART_ASYNCH_MODE &
        USART_EIGHT_BIT &
        USART_CONT_RX &
        USART_BRGH_HIGH, 51); //1200 BAUD (51)
    BAUDCONbits.TXCKP=0;
    BAUDCONbits.RXDTP=0;

    sprintf(resstr, "otpad: start\n");
    putsUSART(resstr);

    do {
		// Delay10KTCYx(1);             // give it time to recover

        sprintf(resstr, "waiting...\n");
        putsUSART(resstr);

		// make RB5 an input
		TRISB = TRISB | 32;

		// start counting
		// wait for capacitor to charge (we will see 1 on RB5)
		ctr = 0;
		while(LATB & 32 == 0)
		{
			ctr++;
		}
		TRISB = TRISB & 223;
		LATB = LATB | 32;
		// counter is our random #
        sprintf(resstr, "%d\n", ctr);
        putsUSART(resstr);

//        Delay10KTCYx(15);        // about 0.5 seconds
    } while(1);

    return;
} /* main */

