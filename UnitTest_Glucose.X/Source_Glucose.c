/* 
 * File:   Source.c
 * Author: SirDan
 *
 * Created on November 14, 2017, 3:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <delays.h>
#include "../one_wire/ow.h"
#include "../xlcd/xlcd.h"
#include    <timers.h>

#include <adc.h>
#include <delays.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

//**************Declare Global Varaibles**************************************
unsigned int ADCResult=0;
float voltage;
//int voltage;
unsigned char Buffer[9];
float concen;


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

void initADC ()
{
     // configure A/D convertor
    OpenADC( ADC_FOSC_2 & ADC_RIGHT_JUST & ADC_8ANA_0REF,
    ADC_CH0 & ADC_INT_OFF );
    Delay10TCYx( 5 ); // Delay for 50TCY
}

void welcomemessage()
{
    putrsXLCD("ADC");             //Display "Hello World"
    SetDDRamAddr(0x40);            //shift cursor to beginning of second line
    putrsXLCD("Display Voltage");      //Display "LCD display"
     //for (int x=0; x<=20;x++)  // 1 second delay
    Delay10KTCYx(100L);
    WriteCmdXLCD(0x01);       //Clear Screen 
    
}

void runADC()
{
    while(1)
    {
        ADCResult =0;
        //---sample and convert----

        ConvertADC();                   //Start conversion
        while(BusyADC());              //Wait here until conversion is finished
        ADCResult = ReadADC();          //Read the convented data
        voltage = (ADCResult*5.0)/1023; // convert the converted data into voltage
                                        //we devide by 1024 because its a 10-bit converted data
        
        //concen=(voltage-c)/m          //(y-c)/m
        
        //voltage = 4;

        //sprintf(Buffer, "Voltage= %d", voltage );    // Convert voltage to string

        //1.68 V
        putrsXLCD("Voltage= ");         //Display "Voltage" on the screen
        sprintf(Buffer, "%.3g", voltage );    // Convert voltage to string
        putsXLCD(Buffer);              //Display the Voltage on the screen
        putrsXLCD("   ");           // Clear after comma
        WriteCmdXLCD(0x02);             //Home position on LCD
    } 
}

void main(void)
{
    OSCCON=0x76;                   //Configure to use 8MHz internal oscillator.
    initLCD();                    //Call the Initialize LCD display function
    initADC();                   //Call the Initialize ADC function
    
    welcomemessage();           //Display welcome message
    runADC();                   //Run ADC functions
    
 
 }
//
//unsigned char MSB=0;
//unsigned char LSB=0;
//unsigned char stopped = 0;
//float temp_fract=0;
//
//unsigned char sign=0;
//unsigned int temp_int = 0,temp_fract_val=0;
//
//void configPORTC()
//{
//    TRISCbits.TRISC0=0;         //Configure PORT that controls transistor base
//    PORTCbits.RC0=0;
//}
//
//void blinkLED ()
//{
//    TRISC=0x00;
//    PORTC=0x00;
//    
//     TRISCbits.TRISC0=0;
//     for(;;)
//     {
//         PORTCbits.RC0=!PORTCbits.RC0;
//         Delay10KTCYx(100L);              //Wait one second
//     }
//}
//
//void convertTemp ()
//{
//    ow_reset();                 //Reset
//    ow_write_byte(0xCC);            //Skip ROM
//    PORTCbits.RC0=1;
//    ow_write_byte(0x44);            //Convert T 
//    Delay10KTCYx(100L);              //Wait one second
//    PORTCbits.RC0=0;    
//}
//
//void readCommandTemp ()
//{
//    ow_reset();                 //Reset
//    ow_write_byte(0xCC);            //Skip ROM
//    ow_write_byte(0xBE);            //Set up read command
//    LSB = ow_read_byte();
//    MSB = ow_read_byte();
//}
//
//void initLCD()
//{
//    OpenXLCD(FOUR_BIT & LINES_5X7);
//    while(BusyXLCD());
//    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_OFF); // display on
//    while(BusyXLCD());
//    WriteCmdXLCD(0b00000001); // display clear
//    while(BusyXLCD());
//    WriteCmdXLCD(ENTRY_CURSOR_INC & ENTRY_DISPLAY_NO_SHIFT); // entrymode
////    while( BusyXLCD() );
////    WriteCmdXLCD( SHIFT_DISP_LEFT );
//}
//
//void get_frac(){
//    unsigned char fract,temp_val,i=0,x=1;
//    fract = LSB & 0x0F;             //Clear all bits except the fractional part.
//    while(i<4){
//        temp_val = fract % 10;          //Obtain the right most digit
//        temp_fract = (temp_val * (0.0625*x))+ temp_fract; //Binary -> Decimal Conversion
//        x=x*2;
//        fract = fract/10;               //Truncate last digit in order to convert the next digit in the coming cycle.
//        i++;
//    }   
//    temp_fract_val = temp_fract*1000;
//    temp_fract_val = temp_fract_val/100;
//}
//
//void get_int(){
//    unsigned char i=0,temp=0,int_temp=0,x=1;
//    //sign = MSB & 0x80;          //Obtain Sign
//    //temp = LSB & 0xF0;          //Clear lower nibble of LSB
//    temp = LSB >>4;             //Shift bit7:bit4 down 4 places to the right.
//    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp, therefore int_temp = temp
//    //temp = MSB & 0x07;          //Clear all bits of MSB except least significant 3 bits.
//    temp = MSB << 4;            //Shift least significant 3 bits(bit10:bit8) up 4 places to the left to prepare for bitwise OR to combine bit11:bit8 and bit7:bit4.
//    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp,therefor int_temp = temp
//    if(sign>0){                    //Check if number is negative
//       int_temp = int_temp ^ 0x7F; //Toggle bits if negative
//    }
//    temp_int = int_temp;
//}
//
//void formatTemp ()
//{
//    get_frac();
//    get_int();
//}
//
//void displayTemp(){
//    char disp_val[70];
//    if(sign>0){
//        sprintf(disp_val,"Temp:-%d.%d",temp_int,temp_fract_val);
//    }else{
//        sprintf(disp_val,"Temp:%d.%dC",temp_int,temp_fract_val);
//    }
//    
//    TRISBbits.TRISB1 = 0;  //Configure PORTB pin 1 as an output
//    while(BusyXLCD());
//    WriteCmdXLCD(0b00000001); // display clear
//    while( BusyXLCD() );
//    SetDDRamAddr( 0x00 );
//    putsXLCD( disp_val );  
//    
//    PORTBbits.RB1 = !PORTBbits.RB1;
//    Delay10KTCYx(100L); 
//}
//
///* Write LCD delay functions */
//// functions required for XLCD
//void DelayFor18TCY(void)        //18 instruction cycle delay
//{
//    Delay10TCYx(2L);            //20 instruction cycle
//}
//
//void DelayPORXLCD(void)         // 15 ms delay
//{
//    Delay1KTCYx(15L);           //15,000 instruction cycles
//}
//
//void DelayXLCD(void)            // 5 ms delay
//{
//    Delay1KTCYx(5L);            //5,000 instruction cycles
//}
//
//void main(void)
//{
//        
//    initLCD();
//    
//    configPORTC();
//    convertTemp();
//    readCommandTemp();
//    formatTemp();
//    displayTemp();
//    temp_int = 0;
//    temp_fract_val = 0.0;
//    
//    
//    while(1)
//    {
//        PORTBbits.RB1 = !PORTBbits.RB1;
//        Delay10KTCYx(100L);
//    }
//   
//}

