#include <msp430.h>

int Set_Ignition; // Determine if the ignitor is on or off with 1 or 0

void Init_IgnitionLED() {

    //WDTCTL = WDTPW | WDTHOLD;

    P2OUT &= ~BIT0;
    P2DIR |= BIT0;

    P2DIR &= ~Set_Ignition;

    //PM5CTL0 &= ~LOCKLPM5;
}

void Set_IgnitionLED() {
        if (Set_Ignition == 1) 
        {
            P2OUT |= BIT0;
        }
        else
            P2OUT &= ~BIT0;
    }
