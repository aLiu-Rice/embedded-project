#include <msp430.h>

void Init_Opamp();
void Init_ADC();
unsigned int Read_ADC(char Channel);
unsigned int Read_Thermistor();      // Returns 1 if over-temp
unsigned int Read_Thermocouple();    // Returns 1 if flame present
unsigned int Read_POT();             // Returns ADC setpoint

extern volatile char ADCFinished;
extern volatile unsigned int ADC_Result;
