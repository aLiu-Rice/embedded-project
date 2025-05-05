#include <msp430.h>

// Thermistor, Thermocouple, POT
// Thermocouple --> P1.3 (A3)
// Thermistor --> P1.4 (A4)
// POT --> P1.5 (A5)

volatile char ADCFinished = 0;
volatile unsigned int ADC_Result = 0;
unsigned int FLAME_THRESHOLD = 1000;  // Adjust based on flame signal ADC value


unsigned int Read_Thermistor() {
    unsigned int TempValue;    // any name, change later
    TempValue = Read_ADC(4);
    unsigned int Set_Temp;
    Set_Temp = Read_ADC(5);
    return TempValue;
    return (TempValue > Set_Temp) ? 1:0;    // Over temp by 1
}

void Init_Opamp() {
    P1SEL0 |= BIT1 + BIT3;             // Select P1.1 P1.2 P1.3 OA function
    P1SEL1 |= BIT1 + BIT3;             // Select P1.1 P1.2 P1.3 OA function

    SAC0OA = NMUXEN + PMUXEN + PSEL_0 + NSEL_1;//Select positive and negative pin input
    SAC0OA |= OAPM;                           // Select low speed and low power mode
    SAC0PGA = GAIN0 + GAIN2 + MSEL_2;         // Set Non-inverting PGA mode with Gain=17
    SAC0OA |= SACEN + OAEN;                   // Enable SAC and OA

    __bis_SR_register(LPM3_bits);             // Enter LPM3
}

unsigned int Read_Thermocouple() {
    unsigned int Check_Flame;
    Check_Flame = Read_ADC(3);
    return Check_Flame;
    return (Check_Flame > FLAME_THRESHOLD) ? 1:0;   // When Flame Present = 1
}

unsigned int Read_POT() {
    return Read_ADC(5);
}

void Init_ADC() {
    // Configure ADC pins
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    // Configure ADC // ADC Example 12_01
    ADCCTL0 |= ADCSHT_2 | ADCON;
    ADCCTL1 |= ADCSHP;
    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;
    ADCIE |= ADCIE0;
}

unsigned int Read_ADC(char Channel) {

    ADCCTL0 &= ~ADCENC;              // Disable ADC before changing channel
    ADCMCTL0 &= ~ADCINCH_15;         // Clear previous channel selection

    switch (Channel) {
        case 3:
            ADCMCTL0 |= ADCINCH_3;
        break;
        case 4:
            ADCMCTL0 |= ADCINCH_4;
        break;
        case 5:
            ADCMCTL0 |= ADCINCH_5;
        break;
        default:
            ADCMCTL0 |= ADCINCH_3;  // Any channel that you feel is important to default to(for now thermocouple)
        break;

    }

    ADCCTL0 |= ADCENC | ADCSC;
    while (ADCFinished != 1);
    return ADC_Result;
}


// ADC interrupt service routine
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADC_Result = ADCMEM0;
            ADCFinished = 1;
            break;
        default:
            break;
    }
}