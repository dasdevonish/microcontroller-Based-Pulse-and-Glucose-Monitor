/* 
 * File:   Speaker_Test.c
 * Author: SirDan
 *
 * Created on November 7, 2017, 11:56 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <delays.h>
//#include "PWM.h"


void main(void)
{
    unsigned char   dc ;

    TRISC = 0 ;                     // set PORTC as output
    PORTC = 0 ;                     // clear PORTC

    /*
     * configure CCP module as 4000 Hz PWM output
     */
    PR2 = 0b01111100 ;
    T2CON = 0b00000101 ;
    CCP1CON = 0b00001100 ;
    CCP2CON = 0b00111100 ;

    for(;;)                         // forever
    {
    /*
     * PWM resolution is 10 bits
     * don't use last 2 less significant bits CCPxCON,
     * so only CCPRxL have to be touched to change duty cycle
     */
        for(dc = 0 ; dc < 128 ; dc++){
            CCPR1L = dc ;
            CCPR2L = 128 - dc ;
            //Delay_ms(10) ;
            Delay1TCY();
        }
        for(dc = 127 ; dc > 0 ; dc--){
            CCPR1L = dc ;
            CCPR2L = 128 - dc ;
            //Delay_ms(10) ;
            Delay1TCY();
        }
    }
}
