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
    if (CRGFLG_RTIF) // RTI period over?
    {
        CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
        //SWL_TOG (SWL_RED); 
    }
}