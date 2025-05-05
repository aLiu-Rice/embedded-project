#include <msp430.h>
#include "System.h"
#include "intrinsics.h"


void main(){
// Initializing

    // setup code (Runs when processor resets)
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    Init_ADC();
    Init_RGB();
    /*Init_RGB();
    Init_ADC();
    Init_MainValve();
    Init_PilotValve();
    Init_IgnitionLED();*/
 
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    


    /*while(1)
    {
       //while(!CallForHeat()); // while CallForHeat not active, Line just waits for CallForHeat to be active (polling)
       Set_Ignitor();
       Set_Pilot();
       WaitTime_2sec();  
       Check_Flame();

       //while((CallForHeat()) || (Check_Flame()) || (Read_BoilerTemp() < Threshold));
       while(1) {

        CFH = CallForHeat();
        C_F = Check_Flame();

        if (!CallForHeat()) {
            break;
        }
        if (!Check_Flame()) {
            Flame_Extinguished = 1;
            break;
        }
       }

       TurnoffMainValve();
       TurnoffPilotValve();
       TurnoffIgnitor();

       __bis_SR_register(CPUOFF);

    }*/

    while (1)   {
        if (Read_POT() < Read_Thermistor())  {
            Set_RGBLED(255, 0, 0);
        }
        else {
            Set_RGBLED(0, 0, 255);
        }
        //__delay_cycles(100000);
    }
}
