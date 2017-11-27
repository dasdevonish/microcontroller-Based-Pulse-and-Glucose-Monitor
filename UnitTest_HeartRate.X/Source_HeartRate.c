#include<p18f452.h>
#include<delays.h>
#include"xlcd.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<timers.h>
#include<capture.h>
#include<string.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000UL

void init_timer(void);
void high_isr(void);
void init_lcd(void);
void display_bpm(int);

int x = 0,heart_beat=0,bpm_obt=0,ris_edg=0,value_obtained=0;
/*****************High priority interrupt vector **************************/
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
  _asm GOTO high_isr _endasm
}

#pragma code
/*****************High priority ISR **************************/

#pragma interrupt high_isr
void high_isr (void)
{
	if (INTCONbits.TMR0IF==1){  // Interrupt Check   
        x++;
        PORTBbits.RB7 = !PORTBbits.RB7;
        if(x==10){
            CloseTimer1();
            CloseTimer0();
            bpm_obt = 1;
        //display(x);
        
        INTCONbits.TMR0IF = 0;
        //WriteTimer0(34304);
        }else{
            INTCONbits.TMR0IF = 0;
            WriteTimer0(34304);
        }
    }
    
    if (INTCONbits.INT0F==1 ) {
        // ((value_obtained==0)){
            ris_edg++;
            value_obtained = 1;
            INTCONbits.INT0F = 0;
        //}
           //INTCONbits.INT0F = 0;
    }
    
    
}

void main(){
    
    int bpm_val = 0;
    INTCONbits.GIEH= 1;         
    INTCONbits.TMR0IE = 1;          //Enable Timer0 Interrupt
    INTCONbits.TMR0IF = 0;          //Clear Timer0 Interrupt Flag
    INTCONbits.INT0E = 1 ;         // Enables the INT0 external interrupt
    INTCONbits.INT0F = 0;          //The INT0 external interrupt occurred (must be cleared in software)          
    INTCON2bits.TMR0IP = 1;          //Timer0 High Priority
    //INTCON2bits.RBIP = 1;           // interrupt on change high priority 
    INTCON2bits.INTEDG0 = 1;        //Interrupt on rising edge
    RCONbits.IPEN = 1;              //Enable Priority Levels
    TRISBbits.RB7 = 0;
    TRISBbits.RB0 = 1;
    PORTBbits.RB7 = 0;
    
    init_timer();
    init_lcd();
    WriteTimer0(34304);
              
    while(1){
        if(bpm_obt==0){
            //heart_beat = ReadTimer1();
            
            heart_beat = ris_edg; 
            //Delay1KTCYx(0xC8);
            display_bpm(heart_beat);
            
            
            
        }else{
            CloseTimer1();
            CloseTimer0();
            bpm_val = bpm();
            //display_bpm(bpm_val);
        }
       //if(value_obtained==1){
       //    Delay1KTCYx(300);
       //    value_obtained=0;
       //} 
        
    }
    
}

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


void init_timer(){
    //OpenCapture1(C1_EVERY_RISE_EDGE & CAPTURE_INT_OFF);
    //OpenTimer3(TIMER_INT_OFF & T3_SOURCE_INT);
    OpenTimer0(TIMER_INT_ON & T0_SOURCE_INT & T0_PS_1_128 & T0_16BIT );
    OpenTimer1(TIMER_INT_OFF & T1_SOURCE_EXT);

   

}

void display_bpm(int x){
    char y[80];
    //itoa(x,y);
    //PORTBbits.RB7 = !PORTBbits.RB7;
    sprintf(y, "%d bpm",x);
    while( BusyXLCD() );
    SetDDRamAddr( 0x00 );
    putrsXLCD("Heart Rate: ");
    while( BusyXLCD() );
    SetDDRamAddr( 0x40 );
    putsXLCD( y );
    //putrsXLCD(" bpm");
    Delay1KTCYx(0x64);
   // WriteCmdXLCD(0b00000001);
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

int bpm(){
    int r_val;
    r_val = heart_beat*6;
    return r_val;
    }   
