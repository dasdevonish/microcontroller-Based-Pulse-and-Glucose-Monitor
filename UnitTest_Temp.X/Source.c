/* 
 * File:   Source.c
 * Author: SirDan
 *
 * Created on November 7, 2017, 6:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <delays.h>
#include "../one_wire/ow.h"
#include "../xlcd/xlcd.h"
#include    <timers.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

unsigned char MSB=0;
unsigned char LSB=0;
unsigned char stopped = 0;
float temp_fract=0;

unsigned char sign=0;
unsigned int temp_int = 0,temp_fract_val=0;

void configPORTC()
{
    TRISCbits.TRISC0=0;         //Configure PORT that controls transistor base
    PORTCbits.RC0=0;
}

void convertTemp ()
{
    ow_reset();                 //Reset
    ow_write_byte(0xCC);            //Skip ROM
    PORTCbits.RC0=1;
    ow_write_byte(0x44);            //Convert T 
    Delay10KTCYx(100L);              //Wait one second
    PORTCbits.RC0=0;    
}

void readCommandTemp ()
{
    ow_reset();                 //Reset
    ow_write_byte(0xCC);            //Skip ROM
    ow_write_byte(0xBE);            //Set up read command
    LSB = ow_read_byte();
    MSB = ow_read_byte();
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

void get_frac(){
    unsigned char fract,temp_val,i=0,x=1;
    fract = LSB & 0x0F;             //Clear all bits except the fractional part.
    while(i<4){
        temp_val = fract % 10;          //Obtain the right most digit
        temp_fract = (temp_val * (0.0625*x))+ temp_fract; //Binary -> Decimal Conversion
        x=x*2;
        fract = fract/10;               //Truncate last digit in order to convert the next digit in the coming cycle.
        i++;
    }   
    temp_fract_val = temp_fract*1000;
    temp_fract_val = temp_fract_val/100;
}

void get_int(){
    unsigned char i=0,temp=0,int_temp=0,x=1;
    //sign = MSB & 0x80;          //Obtain Sign
    //temp = LSB & 0xF0;          //Clear lower nibble of LSB
    temp = LSB >>4;             //Shift bit7:bit4 down 4 places to the right.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp, therefore int_temp = temp
    //temp = MSB & 0x07;          //Clear all bits of MSB except least significant 3 bits.
    temp = MSB << 4;            //Shift least significant 3 bits(bit10:bit8) up 4 places to the left to prepare for bitwise OR to combine bit11:bit8 and bit7:bit4.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp,therefor int_temp = temp
    if(sign>0){                    //Check if number is negative
       int_temp = int_temp ^ 0x7F; //Toggle bits if negative
    }
    temp_int = int_temp;
}

void formatTemp ()
{
    get_frac();
    get_int();
}

void displayTemp(){
    char disp_val[70];
    if(sign>0){
        sprintf(disp_val,"Temp:-%d.%d",temp_int,temp_fract_val);
    }else{
        sprintf(disp_val,"Temp:%d.%dC",temp_int,temp_fract_val);
    }
    
    //TRISBbits.TRISB1 = 0;  //Configure PORTB pin 1 as an output
    while(BusyXLCD());
    WriteCmdXLCD(0b00000001); // display clear
    while( BusyXLCD() );
    SetDDRamAddr( 0x00 );
    putsXLCD( disp_val );  
    
    //PORTBbits.RB1 = !PORTBbits.RB1;
    Delay10KTCYx(100L); 
}

/* Write LCD delay functions */
// functions required for XLCD
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

void main(void)
{
        
    initLCD();
    
    configPORTC();
    convertTemp();
    readCommandTemp();
    formatTemp();
    displayTemp();
    temp_int = 0;
    temp_fract_val = 0.0;
    
    
    //TRISBbits.TRISB1 = 0;
    //PORTBbits.RB1=1;
     
    while(1)
    {
        //PORTBbits.RB1 = !PORTBbits.RB1;
        //Delay10KTCYx(100L);
    }
   
}
    