/* 
 * File:   Source.c
 * Author: SirDan
 *
 * Created on November 15, 2017, 12:54 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <delays.h>
#include "../one_wire/ow.h"
#include "../xlcd/xlcd.h"
#include    <timers.h>
#include<string.h>
#include<capture.h>


#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


int keypress;
char displaystuff[20];


void low_isr(void);

void displayLCD()
{
    //TRISBbits.TRISB1 = 0;  //Configure PORTB pin 1 as an output
    while(BusyXLCD());
    WriteCmdXLCD(0b00000001); // display clear
    while( BusyXLCD() );
    SetDDRamAddr( 0x00 );
    putsXLCD( displaystuff );  
    INTCON3bits.INT1IE=1;  
    
    //PORTBbits.RB1 = !PORTBbits.RB1;
    Delay10KTCYx(100L); 
    
    
}

void dummy1()
{
    sprintf(displaystuff,"1");
    displayLCD();
}
//void dummy2()
//{
//    displaystuff="2";
//    displayLCD();
//}
//void dummy3()
//{
//    displaystuff="3";
//    displayLCD();
//}
//void dummy4()
//{
//    displaystuff="4";
//    displayLCD();
//}
//void dummy5()
//{
//    displaystuff="5";
//    displayLCD();
//}
//void dummy6()
//{
//    displaystuff="6";
//    displayLCD();
//}
//void dummy7()
//{
//    displaystuff="7";
//    displayLCD();
//}
//void dummy8()
//{
//    displaystuff="8";
//    displayLCD();
//}
//void dummy9()
//{
//    displaystuff="9";
//    displayLCD();
//}
//void dummy0()
//{
//    displaystuff="0";
//    displayLCD();
//}
//void dummyA()
//{
//    displaystuff="A";
//    displayLCD();
//}
//void dummyB()
//{
//    displaystuff="B";
//    displayLCD();
//}
//void dummyC()
//{
//    displaystuff="C";
//    displayLCD();
//}
//void dummyD()
//{
//    displaystuff="D";
//    displayLCD();
//}
//void dummystar()
//{
//    displaystuff="*";
//    displayLCD();
//}
//void dummypound()
//{
//    displaystuff="#";
//    displayLCD();
//}


void readkey()
{
    keypress = PORTA & 0x0F;
    
    //if (keypress == 0x00)
    //{
        dummy1();
    //}
//    else if (keypress == 0x03)
//    {
//        dummy2();
//    }
//    else if (keypress == 0x02)
//    {
//        dummy3();
//    }
//    else if (keypress == 0x04)
//    {
//        dummy4();
//    }
//    else if (keypress == 0x07)
//    {
//        dummy5();
//    }
//    else if (keypress == 0x06)
//    {
//        dummy6();
//    }
//    else if (keypress == 0x08)
//    {
//        dummy7();
//    } 
//    else if (keypress == 0x0B)
//    {
//        dummy8();
//    }
//    else if (keypress == 0x0A)
//    {
//        dummy9();
//    }  
//    else if (keypress == 0x0F)
//    {
//        dummy0();
//    } 
//    else if (keypress == 0x01)
//    {
//        dummyA();
//    }
//    else if (keypress == 0x05)
//    {
//        dummyB();
//    }
//    else if (keypress == 0x09)
//    {
//        dummyC();
//    }
//    else if (keypress == 0x0D)
//    {
//        dummyD();
//    }
//    else if (keypress == 0x0C)
//    {
//        dummystar();
//    }
//    else if (keypress == 0x0E)
//    {
//        dummypound();
//    }
}

/*****************Low priority interrupt vector **************************/
#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
  _asm GOTO low_isr _endasm
}

#pragma code
/*****************Low priority ISR **************************/

#pragma interruptlow low_isr
void low_isr (void)
{
    if (INTCON3bits.INT1IF==1)           // If key press triggers interrupt
    {
        INTCON3bits.INT1IE=0;            // Disable future key presses
        INTCON3bits.INT1IF=0;            // Reset interrupt flag
        readkey();    
    }
}

void configkeyinter()
{
    INTCON3bits.INT1F = 0;           // Clear external INT1 interrupt
    RCONbits.IPEN = 1;              //Enable Priority Level Interrupts
    INTCONbits.GIEH= 1;             //Enable Global Interrupts
    INTCONbits.PEIE= 1;             //Enables all low priority peripheral interrupts
    INTCON3bits.INT1E = 1 ;         // Enables the INT1 external 
    INTCON2bits.INTEDG1 = 1;        //Interrupt on rising edge
    INTCON3bits.INT1IP=0;           //Make External interrupt low priority
    
}

void configPORT()
{
    TRISBbits.RB1 = 1;              //RB1 is an input
    TRISAbits.RA0 = 1;              //RA0 is an input
    TRISAbits.RA1 = 1;              //RA1 is an input
    TRISAbits.RA2 = 1;              //RA2 is an input
    TRISAbits.RA3 = 1;              //RA3 is an input
    
}

void initLCD()
{
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD());
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF); // display on
    while(BusyXLCD());
    WriteCmdXLCD(0b00000001); // display clear
    while(BusyXLCD());
    WriteCmdXLCD(ENTRY_CURSOR_INC & ENTRY_DISPLAY_NO_SHIFT); // entrymode
//    while( BusyXLCD() );
//    WriteCmdXLCD( SHIFT_DISP_LEFT );
}

void DelayFor18TCY(void)        //18 instruction cycle delay
{
    Delay10TCYx(2L);            //20 instruction cycle
}
void DelayPORXLCD(void)         // 15 ms delay
{
    Delay1KTCYx(15L);           //15,000 instruction cycles
}
void DelayXLCD(void)            // 5 ms delay
{
    Delay1KTCYx(5L);            //5,000 instruction cycles
}


void main()
{
    configkeyinter();
    configPORT();
    
    initLCD();
    
    while(1){
    displayLCD();
    };
    
}