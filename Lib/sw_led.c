#include <hidef.h>  
#include "derivative.h" 
#include "sw_led.h"

void SWL_Init (void){
    PT1AD1 &= 0x1F;
    DDR1AD1 = 0xE0;
    ATD1DIEN1 |= 0x1F;
}

void SWL_ON (SWL_LEDColour led){
    PT1AD1 | = (unsigned char)led;
}
void SWL_OFF (SWL_LEDColour led){
    PT1AD1 &= ~(unsigned char)led;
}
void SWL_OFF (SWL_LEDColour led){
    PT1AD1 ^= (unsigned char)led;
}

int SWL_Pushed (SWL_SwitchPos pos){
    return PT1AD1 & pos;
}
