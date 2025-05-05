#include "intrinsics.h"
#include <msp430.h>
int Set_Pilot;

void Init_PilotValve() {

    P2OUT &= ~BIT5;                         // Clear P1.0 output latch for a defined power-on state
    P2DIR |= BIT5;                          // Set P1.0 to output direction

}

void Set_PilotValve() {
    if (Set_Pilot == 1) {
        P2OUT |= BIT5;          // Turn solenoid on
        __delay_cycles(1000);
    }
    else {
        P2OUT &= ~BIT5;         // Turn solenoid off
        __delay_cycles(1000);
    }
}
