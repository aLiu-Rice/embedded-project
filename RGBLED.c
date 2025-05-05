#include <msp430.h>

void Init_RGB(){

    P6DIR |= BIT0 | BIT1 | BIT2;                     // P6.0, P6.1, P6.2 output
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);                 // P6.0, P6.1, P6.2 options select
    P6SEL0 |= BIT0 | BIT1 | BIT2;
    

    TB3CCR0 = 1024-1;                         // PWM Period
    TB3CCTL3 = OUTMOD_3;    // RED LED P6.0   // CCR1 reset/set
    TB3CCR3 = 750;                            // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_3;    // GREEN LED P6.1 // CCR2 reset/set
    TB3CCR2 = 500;                            // CCR2 PWM duty cycle
    TB3CCTL1 = OUTMOD_3;    // BLUE LED P6.2  // CCR3 set/reset
    TB3CCR1 = 250;                            // CCR3 PWM Duty Cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}


void Set_RGBLED(char RED, char GREEN, char BLUE) {
    TB3CCR3 = BLUE << 2;         // RED * 4 to scale to range of 1024
    TB3CCR2 = GREEN << 2;
    TB3CCR1 = RED << 2;
}
