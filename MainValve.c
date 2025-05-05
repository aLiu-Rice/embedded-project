#include <msp430.h>

void Init_MainValve() {

    TB2CCR0 = 20000; // 20 ms period (50 Hz) for servo control
    P5DIR |= BIT0;   // P5.0 as output
    P5SEL0 |= BIT0;  // Select timer function for P5.0
    P5SEL1 &= ~BIT0; // Ensure P5SEL1 is 0 for P5.0
    TB2CCTL1 = OUTMOD_7; // CCR1 reset/set mode
    TB2CCR1 = 1500;      // 1.5 ms pulse width (neutral position)
    TB2CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // to clear
}

void Set_MainValve(unsigned int Position) {
    TB2CCR1 = Position;
}
