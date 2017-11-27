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
/*------------LCD--------------------*/
#include "../xlcd/xlcd.h"
/*---------KEYPAD-----------------------*/
#include<string.h>
#include<capture.h>
/*-----------HEARTRATE---------------------*/
#include<timers.h>
#include<capture.h>
/*-----------SPEAKER-----------------------*/
#include <pwm.h> 
/*--------TEMPERATURE------------------*/
#include "../one_wire/ow.h"


/*---------CONFIGURATION BITS--------*/
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF


/*---------GLOBAL VARIABLE DECLARATION-------*/
/*-------------KEYPAD-------------*/
int keypress;                       //Holds what key was pressed
char displaystuff[20];              //Hold message to be displayed

/*----------HEART RATE MONITOR------*/
int timeroverflow=0;
int heartrate_final=0;
/*---------TEMPERATURE------------------*/
unsigned char MSB=0;
unsigned char LSB=0;
unsigned char stopped = 0;
float temp_fract=0;
unsigned char sign=0;
unsigned int temp_int = 0,temp_fract_val=0;



/*-------------FUNCTIONS DECLARATION-----*/
/*----------------LCD---------------------*/
void LCD_init(void);
void LCD_home(void);             //Home LCD screen


/*--------------KEYPAD-------------------*/
void KeyPad_init(void);          //Configure Keypad
void KeyPad_read(void);          //Read value from keypad

/*------------HEARTRATE MONITOR---------*/
void HeartRate(void);           //Heart rate routinr
void HeartRate_init(void);           //Configure heartrate modules
void HeartRate_startup(void);        //welcome screen
void HeartRate_countdown(void);        //Display countdown
void HeartRate_process(void);           //read value and process
void HeartRate_display(void);           //Display heart rate
void HeartRate_ROM(void);               //Store HeartRate to ROM

/*-------------SPEAKER------------------*/
void Speaker_low(void);
void Speaker_high(void);

/*------------GLUCOSE------------------*/
void Glucose(void);
void Glucose_ROM(void);

/*-----------HEART RATE VARIABLITY----*/
void HRV(void);
void HRV_init(void);
void HRV_ROM(void);

/*-----------TEMPERATURE------------*/
void Temperature(void);
void Temp_home(void);
void Temp_init_PORTC(void);
void Temp_convert (void);
void Temp_read_Command (void);
void Temp_format (void);
void Temp_get_frac(void);
void Temp_get_int(void);
void Temp_display(void);
void Temp_ROM(void);

/*-----------FLASH ROM----------------*/
void Flash_home(void);

/*--------------ISR------------------*/
void low_isr(void);
void high_ISR(void);



/*------------PRIORITY CONFIGUATION--------------*/
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
void high_ISR(void){
    //INTCONbits.GIE = 0;
    
    if(INTCONbits.TMR0IF==1){
        T0CONbits.TMR0ON=0;                           // Disable Timer0
        T1CONbits.TMR1ON=0;                           // Disables Timer1
        INTCONbits.TMR0IF=0;
        CloseTimer0();                   //Disable timer0
        CloseTimer1();                   //Disable timer1
        timeroverflow=1;
        return;
    }
    //INTCON3bits.INT1IE = 1;
    //INTCONbits.GIE = 1;
    return;
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
        //INTCON3bits.INT1IE=0;            // Disable future key presses
        LATAbits.LATA1=!LATAbits.LATA1;
        KeyPad_read();
        Delay1TCY();
        //LATBbits.LATB2=!LATBbits.LATB2;
        
        INTCON3bits.INT1F=0;            // Reset interrupt flag
        
        //case

    }
}

/*-----------------MAIN------------*/

void main(void)
{
    
    LCD_init();
    Delay1TCY();
    KeyPad_init();
    Delay1TCY();
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0=1 ;
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1=1 ;
    
//    Speaker_high();
//    Delay1TCY();
//    Speaker_low();
    
    LCD_home();
    Delay1TCY();
    
}
    
    
   
    

 



/*----------------LCD---------------------*/
/*-----------DELAY FUNCTIONS-------------*/
void DelayFor18TCY(void)        //18 instruction cycle delay
{
    Nop(); Nop(); Nop(); Nop();     //18 instruction cycle
    Nop(); Nop(); Nop(); Nop(); 
    Nop(); Nop(); Nop(); Nop(); 
    Nop(); Nop(); Nop(); Nop();
    Nop(); Nop();
    return;
}

void DelayPORXLCD(void)         // 15 ms delay
{
    Delay1KTCYx(15L);           //15,000 instruction cycles
    return;
}

void DelayXLCD(void)            // 5 ms delay
{
    Delay1KTCYx(5L);            //5,000 instruction cycles
    return;
}

/*------------Configure LCD-------------*/
void LCD_init()
{
    TRISD = 0x00;
    PORTD = 0x00;
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD());
    WriteCmdXLCD(DON & CURSOR_OFF & BLINK_ON); // Turn display off, Enable display with no cursor,Enable display with unblinking cursor
    while(BusyXLCD());
    WriteCmdXLCD( SHIFT_CUR_RIGHT & SHIFT_DISP_LEFT  ); //Cursor shifts to the right, Display shifts to the left, 
    //while(BusyXLCD());
    //WriteCmdXLCD(ENTRY_CURSOR_INC & ENTRY_DISPLAY_NO_SHIFT); /* Sets the cursor move direction to increment, Sets the display to not shift*/
    while(BusyXLCD());
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    return;
  
 }
/*-----------Home Screen Message--------*/
void LCD_home(void)
{
    while(1)
    {       
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        while(BusyXLCD());
        putrsXLCD("Welcome to Group G's");
        while(BusyXLCD());
        SetDDRamAddr(0x14);         //Set cursor to second line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("HeartRate Monitor");
        Delay10KTCYx(200L);              //Wait two second
        LATAbits.LATA0 = !LATAbits.LATA0;//-- toggle PORTB pin 2
        
        
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        while(BusyXLCD());
        putrsXLCD("A to take Heart Rate");
        while(BusyXLCD());
        SetDDRamAddr(0x40);         //Set cursor to second line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("B to take Glucose");
        while(BusyXLCD());              // Wait if LCD busy
        SetDDRamAddr(0x14);         //Set cursor to third line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        while(BusyXLCD());
        putrsXLCD("C to take HRV");
        while(BusyXLCD());
        SetDDRamAddr(0x54);         //Set cursor to forth line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("D to take Temp");     
        Delay10KTCYx(200L);              //Wait two second
        Delay10KTCYx(100L);              //Wait one second
        LATAbits.LATA0 = !LATAbits.LATA0;//-- toggle PORTB pin 2

        
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        while(BusyXLCD());
        putrsXLCD("Press any number");
        while(BusyXLCD());
        SetDDRamAddr(0x40);         //Set cursor to second line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("to access stored");
        while(BusyXLCD());              // Wait if LCD busy
        SetDDRamAddr(0x14);         //Set cursor to third line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        while(BusyXLCD());
        putrsXLCD("data");     
        Delay10KTCYx(200L);              //Wait two second
        //Delay10KTCYx(100L);              //Wait one second
        LATAbits.LATA0 = !LATAbits.LATA0;//-- toggle PORTB pin 2
    }  
    
}


/*-----------------------------------*/
/*---------KEYPAD FUNCTIONS-------*/
void KeyPad_init()
{
    
    TRISBbits.RB1 = 1;              //RB1 is an input
    TRISCbits.RC4 = 1;              //RB4 is an input
    TRISCbits.RC5 = 1;              //RB5 is an input
    TRISCbits.RC6 = 1;              //RB6 is an input
    TRISCbits.RC7 = 1;              //RB7 is an input
    
    INTCON2bits.INTEDG1= 1;         //External Interrupt 1 Edge Select bit (rising)
    
    INTCON3bits.INT1IP=0;           //External Interrupt 1 Priority bit (low)
    INTCON3bits.INT1IE = 1 ;         //Enables the INT1 external interrupt  
    INTCON3bits.INT1IF = 0;           // Clear external INT1 interrupt
    RCONbits.IPEN = 1;              //Enable Priority Level Interrupts
    INTCONbits.GIEH= 1;             //Enable High Global Interrupts
    INTCONbits.GIEL= 1;             //Enable Low Global Interrupts
    
    return;
}

/*-----------READ KEY PRESS-------------*/
void KeyPad_read()
{
    int keypad_val=0;
    keypad_val=0xF0&PORTC;
    keypad_val=keypad_val>>4;
    
    if(keypad_val==0x00)               //1 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x01)           //2 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x02)           //3 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x03)           //A was pressed
    {
        HeartRate();
    }
    else if(keypad_val==0x04)           //4 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x05)           //5 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x06)           //6 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x07)           //B was pressed
    {
        Glucose();
    }
    else if(keypad_val==0x08)           //7 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x09)           //8 was pressed
    {
        Flash_home();    
    }
    else if(keypad_val==0x0A)           //9 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x0B)           //C was pressed
    {
        HRV();
    }
    else if(keypad_val==0x0C)           //* was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x0D)           //0 was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x0E)           //# was pressed
    {
        Flash_home();
    }
    else if(keypad_val==0x0F)           //D was pressed
    {
        Temperature();
    }    
   
}


/*-----------------------------------*/
/*---------HEART RATE MONITOR-------*/

void HeartRate()
{
    HeartRate_init();
    Delay1TCY();
    HeartRate_startup();
    Delay1TCY();
    HeartRate_countdown();
    Delay1TCY();
    if (timeroverflow==0)
    {
       Delay1TCY(); 
    }
    timeroverflow=0;
    HeartRate_process();
    Delay1TCY();
    HeartRate_display();
    Delay1TCY();
    HeartRate_ROM();
    Delay1TCY();
    
    return;
}

void HeartRate_init()
{
    /*Configure Timer 1 counter mode*/
    CloseTimer1();                 //Disable timer1   
    T1CONbits.RD16=1;           // Enables register Read/Write of Timer1 in one 16-bit operation
    T1CONbits.TMR1CS=1;         //Timer1 increments on every rising edge of the external clock
    T1CONbits.T1CKPS1=0;          // 1:1 Prescale value
    T1CONbits.T1CKPS0=0;
    T1CONbits.T1OSCEN=0;            //Timer1 Oscillator is shut-off
    T1CONbits.T1SYNC=1;         //Do not synchronize external clock input
    WriteTimer1(0);                 //Write 0 into the timer 1
  
    //T1CONbits.TMR1ON=1            //Enables Timer1   
//    OpenTimer1( TIMER_INT_OFF &      //Interrupt disabled
//            T1_8BIT_RW &            //16-bit mode
//            T1_SOURCE_EXT &         //External clock source (I/O pin)
//            T1_PS_1_1 &             //1:1 prescale
//            T1_OSC1EN_OFF &         //Disable Timer1 oscillator
//            T1_SYNC_EXT_OFF );       //Don?t sync external clock input
    
    
    /*Configure Timer 0 timer mode*/
    CloseTimer0();                   //Disable timer0
    T0CONbits.T08BIT=0;               //Timer0 is configured as a 16-bit timer/counter
    T0CONbits.T0CS=1; // Transition on T0CKI pin
    T0CONbits.T0SE=0;     //Increment on low-to-high transition on T0CKI pin
    T0CONbits.PSA=0;// Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
    T0CONbits.T0PS2=1;            //Timer0 Prescaler Select bits
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS0=1;         //1:256 prescale value
    WriteTimer0(6941);                 //Write 6941 into the timer 0
    
    /*Configure Interrupts*/
    INTCON2bits.TMR0IP=1;                     // TMR0 Overflow Interrupt High Priority 
    INTCONbits.TMR0IF=0;                     //TImer0 interrupt flag clear
    INTCONbits.TMR0IE=1;        //Enables the TMR0 overflow interrupt    
    
    return;  
}

void HeartRate_startup()
{
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Place finger between");
            
    while(BusyXLCD());
    SetDDRamAddr(0x40);         //Set cursor to second line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    putrsXLCD("heart rate sensors");
    Delay10KTCYx(200L);              //Wait two second

    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x14);         //Set cursor to third line
    while(BusyXLCD());
    Delay1KTCYx(110);       //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Starting in ");

    while(BusyXLCD());
    SetDDRamAddr(0x54);         //Set cursor to forth line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    putrsXLCD("3...");     
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("2..");     
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("1");     
    Delay10KTCYx(100L);              //Wait one second
    
    return;    
}

void HeartRate_countdown()
{
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Leave finger for");
    while(BusyXLCD());
    SetDDRamAddr(0x40);         //Set cursor to second line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    
    T0CONbits.TMR0ON=1;                           // Enables Timer0
    T1CONbits.TMR1ON=1;                           // Enables Timer1
    
    putrsXLCD("15 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("14 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("13 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("12 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("11 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("10 ");
    Delay10KTCYx(100L);              //Wait one second
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x14);         //Set cursor to third line
    putrsXLCD("09 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("08 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("07 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("06 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("05 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("04 ");
    Delay10KTCYx(100L);              //Wait one second
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x54);         //Set cursor to forth line
    putrsXLCD("03 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("02 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("01 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("00 ");
    
    return; 
}

void HeartRate_process()
{
    int heartrate_val=0;
    
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Processing...");
    
    heartrate_val= ReadTimer1();
    heartrate_final=4*heartrate_val;
    
    //Call storage routine
    
    return;  
}

void HeartRate_display()
{
    char heartrate_out[10];
    sprintf(heartrate_out,"%i bpm",heartrate_final);
    
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Your heart rate is");

    while(BusyXLCD());
    SetDDRamAddr(0x40);         //Set cursor to second line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    putsXLCD(heartrate_out);
    
    if (heartrate_final>100)
    {
        while(BusyXLCD());
        SetDDRamAddr(0x14);         //Set cursor to third line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("Rate is TOO HIGH!!!");
        Speaker_high();
        return;
    }
    else if (heartrate_final<60)
    {
        while(BusyXLCD());
        SetDDRamAddr(0x14);         //Set cursor to third line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("Rate is TOO LOW!!!");
        Speaker_low();
        return;
    }
    else
    {
        while(BusyXLCD());
        SetDDRamAddr(0x14);         //Set cursor to third line
        while(BusyXLCD());
        Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
        putrsXLCD("Rate is good");
        Delay10KTCYx(200L);              //Wait two second
        Delay10KTCYx(200L);              //Wait two second
        Delay10KTCYx(100L);              //Wait one second
        return;
    }
    return;
}

void HeartRate_ROM()
{
    
    
    return;
}

/*---------SPEAKER-----------------*/
/*--------TOO LOW------------------*/
void Speaker_low()
{   
    int i=0;
    //Configure Timer2
    OpenTimer2( TIMER_INT_OFF &         //Interrupt off
            T2_PS_1_16 &                    //Prescalar 1:16
            T2_POST_1_1 );                  //PostScalar :1
    
    //PR2=0x8D;                            //Set the PWM period by writing to the PR2 register(141)
    SetDCPWM1(284);                        //Set 284 as duty cycle value;
    TRISCbits.TRISC2=0;                 // Make the CCP1 pin an output
    
    for(i=0;i<6;i++)
    {
        OpenPWM1(0x8D);                 //141 ---> for frequency of 440 (A4)
        Delay10KTCYx(30L);              //Wait 300 milli second
        ClosePWM1();
        Delay10KTCYx(30L);              //Wait 300 milli second
    }
    return;
  
}

void Speaker_high()
{   
    int i=0;
    //Configure Timer2
    OpenTimer2( TIMER_INT_OFF &         //Interrupt off
            T2_PS_1_16 &                    //Prescalar 1:16
            T2_POST_1_1 );                  //PostScalar :1
    
    //PR2=0x8D;                            //Set the PWM period by writing to the PR2 register(141)
    SetDCPWM1(284);                        //Set 284 as duty cycle value;
    TRISCbits.TRISC2=0;                 // Make the CCP1 pin an output
    
    for(i=0;i<6;i++)
    {
        OpenPWM1(0x58);                 //88 ---> for frequency of 700 (F5)
        Delay10KTCYx(10L);              //Wait 100 milli second
        ClosePWM1();               
        Delay10KTCYx(10L);              //Wait 100 milli second
        OpenPWM1(0x58);                 
        Delay10KTCYx(10L);              //Wait 100 milli second
        ClosePWM1();
        Delay10KTCYx(30L);              //Wait 300 milli second
    }
    return;
  
}

void Flash_home()
{
    return;
}

/*------------GLUCOSE------------------*/
void Glucose()
{
   
    Glucose_ROM();
    Delay1TCY();
    
    return;
}

void Glucose_ROM()
{
    
    return;
}


/*-----------HEART RATE VARIABLITY----*/
void HRV()
{
    HRV_init();
    Delay1TCY();
    HRV_startup();
    Delay1TCY();
    HRV_ROM();
    Delay1TCY();
    return;    
    
}

void HRV_init()
{
    CloseTimer3();                 //Disable timer1   
    T3CONbits.RD16=1;           // Enables register Read/Write of Timer1 in one 16-bit operation
    T3CONbits.T3CCP2=1;         //Timer3 is the clock source for compare/capture CCP modules
    T3CONbits.T3CCP1=1;
    T3CONbits.T3CKPS1=0;          // 1:1 Prescale value
    T3CONbits.T3CKPS0=0;
    T3CONbits.T3SYNC=1;         //Do not synchronize external clock input
    T3CONbits.TMR3CS=0;         // Internal clock (FOSC/4)
    WriteTimer3(0);                 //Write 0 into the timer 1
    
    /*Configure Interrupts*/
    PIE2.TMR3IE=0;                          //Disables the TMR3 overflow interrupt 
    PIR2.TMR3IF=0;                         //TMR3 register overflow low
    IPR1.CCP1IP=1;                          //CCP1 Interrupt Priority bit
    
   
    
  
}

void HRV_startup()
{
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Place finger between");
            
    while(BusyXLCD());
    SetDDRamAddr(0x40);         //Set cursor to second line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    putrsXLCD("heart rate sensors");
    Delay10KTCYx(200L);              //Wait two second

    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x14);         //Set cursor to third line
    while(BusyXLCD());
    Delay1KTCYx(110);       //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Starting in ");

    while(BusyXLCD());
    SetDDRamAddr(0x54);         //Set cursor to forth line
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    putrsXLCD("3...");     
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("2..");     
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("1");     
    Delay10KTCYx(100L);              //Wait one second
    
    return;    
}

void HeartRate_countdown()
{
    int oldreg=0;
    int newreg=0;
    int diff1=0;
    int diff2=0;
    int diffdiff=0;
    
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Leave finger...");
    while(BusyXLCD());
//    SetDDRamAddr(0x40);         //Set cursor to second line
//    while(BusyXLCD());
//    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    

    OpenCapture1(C1_EVERY_RISE_EDGE & CAPTURE_INT_OFF); //Interrupt on every rise edge
    T3CONbits.TMR3ON=1;             // Enables Timer3 
 
    while(!PIR1bits.CCP1IF);
    oldreg = ReadCapture1();
    
    while(!PIR1bits.CCP1IF);
    newreg = ReadCapture1();
    diff1=newreg-oldreg;
    oldreg=newreg;
    
    while(!PIR1bits.CCP1IF);
    newreg = ReadCapture1();
    diff2=newreg-oldreg;
    oldreg=newreg;
    if(diff2>diff1)
    {
        diffdiff=diff2-diff1;
    }
    else
    {
        diffdiff=diff1-diff2;      
    }
    if (diffdiff>50ms)
    
    while(!PIR1bits.CCP1IF);
    newreg = ReadCapture1();
    diff1=newreg-oldreg;
    oldreg=newreg;
    
    
    
    
    
    
    
    putrsXLCD("15 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("14 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("13 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("12 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("11 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("10 ");
    Delay10KTCYx(100L);              //Wait one second
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x14);         //Set cursor to third line
    putrsXLCD("09 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("08 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("07 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("06 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("05 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("04 ");
    Delay10KTCYx(100L);              //Wait one second
    while(BusyXLCD());              // Wait if LCD busy
    SetDDRamAddr(0x54);         //Set cursor to forth line
    putrsXLCD("03 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("02 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("01 ");
    Delay10KTCYx(100L);              //Wait one second
    putrsXLCD("00 ");
    
    return; 
}


void HRV_ROM()
{
    
    
    return;
}

/*-----------TEMPERATURE------------*/
void Temperature()
{
    Temp_home();
    Delay1TCY();
    Temp_init_PORTC();
    Delay1TCY();
    Temp_convert();
    Delay1TCY();
    Temp_read_Command();
    Delay1TCY();
    Temp_format();
    Delay1TCY();
    Temp_display();
    Delay1TCY();
    temp_int = 0;
    temp_fract_val = 0.0;
    
    
    return;
    
}

void Temp_home()
{
        char heartrate_out[10];
    sprintf(heartrate_out,"%i bpm",heartrate_final);
    
    while(BusyXLCD());              // Wait if LCD busy
    WriteCmdXLCD(0x01); // Clears all display and returns the cursor to the home position (Address 0).
    while(BusyXLCD());
    Delay1KTCYx(110); //Give time for LCD to refresh, writing to it too quickly causes flicker issues
    while(BusyXLCD());
    putrsXLCD("Getting Temperature");
    
    return;
}

void Temp_init_PORTC()
{
    TRISCbits.TRISC1=0;         //Configure PORT that controls transistor base
    PORTCbits.RC1=0;
}

void Temp_convert ()
{
    ow_reset();                 //Reset
    ow_write_byte(0xCC);            //Skip ROM
    PORTCbits.RC1=1;
    ow_write_byte(0x44);            //Convert T 
    Delay10KTCYx(100L);              //Wait one second
    PORTCbits.RC1=0;    
    
    return;
}

void Temp_read_Command ()
{
    ow_reset();                 //Reset
    ow_write_byte(0xCC);            //Skip ROM
    ow_write_byte(0xBE);            //Set up read command
    LSB = ow_read_byte();
    MSB = ow_read_byte();
    
    return;
}

void Temp_format ()
{
    Temp_get_frac();
    Delay1TCY();
    Temp_get_int();
    Delay1TCY();
    
    return;
}

void Temp_get_frac()
{
    unsigned char fract,temp_val,i=0,x=1;
    fract = LSB & 0x0F;             //Clear all bits except the fractional part.
    while(i<4)
    {
        temp_val = fract % 10;          //Obtain the right most digit
        temp_fract = (temp_val * (0.0625*x))+ temp_fract; //Binary -> Decimal Conversion
        x=x*2;
        fract = fract/10;               //Truncate last digit in order to convert the next digit in the coming cycle.
        i++;
    }   
    temp_fract_val = temp_fract*1000;
    temp_fract_val = temp_fract_val/100;
}

void Temp_get_int()
{
    unsigned char i=0,temp=0,int_temp=0,x=1;
    //sign = MSB & 0x80;          //Obtain Sign
    //temp = LSB & 0xF0;          //Clear lower nibble of LSB
    temp = LSB >>4;             //Shift bit7:bit4 down 4 places to the right.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp, therefore int_temp = temp
    //temp = MSB & 0x07;          //Clear all bits of MSB except least significant 3 bits.
    temp = MSB << 4;            //Shift least significant 3 bits(bit10:bit8) up 4 places to the left to prepare for bitwise OR to combine bit11:bit8 and bit7:bit4.
    int_temp = temp | int_temp;     //Bitwise OR temp with int_temp,therefor int_temp = temp
    if(sign>0)
    {                    //Check if number is negative
       int_temp = int_temp ^ 0x7F; //Toggle bits if negative
    }
    temp_int = int_temp;
    
    return;
}

void Temp_display()
{
    char disp_val[70];
    if(sign>0)
    {
        sprintf(disp_val,"Temp:-%d.%d",temp_int,temp_fract_val);
    }
    else
    {
        sprintf(disp_val,"Temp:%d.%dC",temp_int,temp_fract_val);
    }
    
    //TRISBbits.TRISB1 = 0;  //Configure PORTB pin 1 as an output
    while(BusyXLCD());
    WriteCmdXLCD(0b00000001); // display clear
    while( BusyXLCD() );
    SetDDRamAddr( 0x00 );
    putsXLCD( disp_val );  
    
    Delay10KTCYx(200L);         //Wait two second
    Delay10KTCYx(100L);         //Wait one second

    return;
}













