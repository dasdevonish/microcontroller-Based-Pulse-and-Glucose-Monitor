#include <p18f452.h>
#include <delays.h>
#include "xlcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "Header Files/ow.h"



#pragma config WDT = OFF //Disable watchdog timer
#pragma config LVP = OFF //Disable low voltage programming

#define _XTAL_FREQ 4000000UL


 


    unsigned char ms_byte=0,ls_byte=0,sign=0;
    float temp_fract=0;
    unsigned int temp_int = 0,temp_fract_val=0;

void DelayFor18TCY(void){
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop();
    Nop();
}

void DelayPORXLCD(void){  //Delay 15ms
    Delay1KTCYx(0x96);
}

void DelayXLCD(void){   //Delay 5ms
    Delay1KTCYx(0x05);
}

void init_lcd(){
    OpenXLCD( FOUR_BIT & LINES_5X7 );
    while( BusyXLCD() );
    WriteCmdXLCD( FOUR_BIT & LINES_5X7 );
    while( BusyXLCD() );
    //WriteCmdXLCD( BLINK_ON );
    while( BusyXLCD() );
    WriteCmdXLCD( SHIFT_DISP_LEFT );
}

    

void get_frac(){
    unsigned char fract,temp_val,i=0,x=1;
    fract = ls_byte & 0x0F;             //Clear all bits except the fractional part.
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
    //sign = ms_byte & 0x80;          //Obtain Sign
    //temp = ls_byte & 0xF0;          //Clear lower nibble of ls_byte
    temp = ls_byte >>4;             //Shift bit7:bit4 down 4 places to the right.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp, therefore int_temp = temp
    //temp = ms_byte & 0x07;          //Clear all bits of ms_byte except least significant 3 bits.
    temp = ms_byte << 4;            //Shift least significant 3 bits(bit10:bit8) up 4 places to the left to prepare for bitwise OR to combine bit11:bit8 and bit7:bit4.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp,therefor int_temp = temp
    if(sign>0){                    //Check if number is negative
       int_temp = int_temp ^ 0x7F; //Toggle bits if negative
    }
    temp_int = int_temp;
}

void display(){
   
    char disp_val[70];
    if(sign>0){
        sprintf(disp_val,"Temp:-%d.%d",temp_int,temp_fract_val);
    }else{
        sprintf(disp_val,"Temp:%d.%dC",temp_int,temp_fract_val);
    }
    while( BusyXLCD() );
    SetDDRamAddr( 0x00 );
    putsXLCD( disp_val );  
}

void main(){
    
    int x;
    TRISBbits.RB6 = 0;          //Strong Pullup Output for MOSFET/Transistor
    PORTBbits.RB6 = 0;          //Initially Low
    init_lcd();
    
  
    while(1){
        ow_reset();
        ow_write_byte(0xCC);    //Skip ROM
        ow_write_byte(0x44);    //Convert T Command
        PORTBbits.RB6=1;        //Turn ON Strong Pull-up
         for( x = 1; x<=8;x++){ //800ms (750ms is recommended conversion time))
           Delay1KTCYx(100);
        }
        PORTBbits.RB6=0;        //Turn-off Strong Pull-up4
        ow_reset();
        ow_write_byte(0xCC);
        ow_write_byte(0xBE);    //Read Scratchpad
        ls_byte = ow_read_byte();
        ms_byte = ow_read_byte();
        get_frac();
        get_int();
        display();
        temp_int = 0;
        temp_fract_val = 0.0;
    }
    
    
}