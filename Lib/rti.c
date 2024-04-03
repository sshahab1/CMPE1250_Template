#include <hidef.h>  
#include "derivative.h" 
#include "rti.h"

void RTI_Init(void)
{
    RTICTL = 0b10010111;
}


 
// void RTI_Delay_ms(unsigned long ms)
// {
//     unsigned int i =0; ///0
//       RTICTL = 0;

//    //CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RT
//     if (CRGFLG_RTIF) // Stop the RTI 
//     {
//         CRGFLG = ~CRGFLG_RTIF_MASK; //Stop the RTI 
        
//     }
   
//     while(i<ms)
//     {
//         if (CRGFLG_RTIF) // RTI period over?
//         {
//             CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
//             i++;
//         }
       
//     } 
    
//      CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RT

// }

void Delay(unsigned int ms)
{
    
    RTICTL = 0;

    RTICTL = 0b10010111;

   
    CRGFLG = CRGFLG_RTIF_MASK; 
    while(ms>0)
    {
        if (CRGFLG_RTIF) // RTI period over?
        {
            CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
            ms--;
        }
       
    }
    RTICTL = 0;
     
}