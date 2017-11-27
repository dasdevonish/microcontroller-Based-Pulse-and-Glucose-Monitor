/* 
 * File:   Source.c
 * Author: SirDan
 *
 * Created on November 7, 2017, 6:05 PM
 */

/*--------STANDARD LIBRARY FILES--------*/
#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <delays.h>

/*---------CONFIGURATION BITS--------*/
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


/*---------GLOBAL VARIABLE DECLARATION-------*/


/*-------------FUNCTIONS DECLARATION-----*/
void initKeyPad(void);

/*--------------ISR------------------*/
void low_isr(void);
void high_ISR(void);



/*------------PRIORITY CONFIGUATION--------------*/
///*****************Low priority interrupt vector **************************/
//#pragma code low_vector=0x18
//void interrupt_at_low_vector(void)
//{
//  _asm GOTO low_isr _endasm
//}
//
//#pragma code
///*****************Low priority ISR **************************/
//
//#pragma interruptlow low_isr
//void low_isr (void)
//{
//    if (INTCON3bits.INT1IF==1)           // If key press triggers interrupt
//    {
//        
//        LATBbits.LATB2=0;
//        INTCON3bits.INT1F=0;            // Reset interrupt flag
//
//    }
//}

/*****************High priority interrupt vector **************************/

#pragma code high_vector = 0x08
 void high_interrupt_vector(void){
     _asm 
     GOTO high_ISR
     _endasm
 }
#pragma code 

/*****************High priority ISR **************************/
#pragma interrupt high_ISR
void high_ISR(void)
{ //check if the interrupt is caused by the pin RB0
     if(INTCONbits.INT0F == 1) //Checks Receive Interrupt Flag bit
      {
         int flash_count=0;
        //Do your interrupt code, flash RB5 5 times
         for (flash_count = 0;flash_count <5; flash_count++) {
         LATBbits.LATB5 = 1;
          //for (int count=0; count<20; count++) __delay_ms(15); //Generate 300ms delay
         Delay10KTCYx(100L);
         LATBbits.LATB5 = 0;
         //for (int count=0; count<20; count++) __delay_ms(15); //Generate 300ms delay
         Delay10KTCYx(100L);
       }
      
        INTCONbits.INT0F = 0;  // Clear Interrupt Flag
      }
   }


void main(void) {
    TRISB = 0x0F;         //Set PORTC as Output
  //  TRISBbits.RB0=1;   //Set PORTB Bit 0 as Input pin.
   // OSCCON=0x76;       //Configure OSCON Register to use
                       //internal oscillator (8MHz). Please check datasheet

    INTCONbits.INT0E = 1;    //enable Interrupt 0 (RB0 as interrupt)
    INTCON2bits.INTEDG0 = 1; //cause interrupt at rising edge
    INTCONbits.INT0F = 0;    //clear interrupt flag
        INTCONbits.GIEH= 1;             //Enable High Global Interrupts

     //ei();     // This is like flipping the master switch to enable interrupt

     //flag   = 0;      // Flag Variable initialization

    while (1)
    {
        //PORTBbits.RB4=1;
      LATBbits.LATB4 = 1;   //Switch ON B4
      //for (int count=0; count<20; count++) __delay_ms(50); //Generate 1 sec delay
      Delay10KTCYx(100L);
      LATBbits.LATB4 = 0;  //Switch OFF B4
      //for (int count=0; count<20; count++) __delay_ms(50); //Generate 1 sec delay
      Delay10KTCYx(100L);
      
    }
}



