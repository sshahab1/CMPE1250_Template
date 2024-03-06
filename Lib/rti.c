#include <hidef.h>  
#include "derivative.h" 
#include "rti.h"

void RTI_Init(void)
{
    RTICTL = 0b10010111;
}

void RTI_InitCallback(void(*function)(void))
{

}

void RTI_Delay_ms(unsigned int ms)
{
    RTICTL=0; //stop the RTI, shouldn’t be running

    if (CRGFLG_RTIF) // RTI period over?
    {
        CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
        
    }
    RTICTL = 0b10010111; //1ms 16*10^3 o 16MHz / 16000 = 1000Hz, or 1ms.
    unsigned int delay = ms * RTICTL;
    if (CRGFLG_RTIF) // RTI period over?
    {
        CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
        
    }
    
    RTICTL=0; 
}