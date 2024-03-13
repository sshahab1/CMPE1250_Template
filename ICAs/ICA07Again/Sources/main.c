/********************************************************************/
// HC12 Program:  ICA07
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "rti.h"
#include "clock.h"
// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
unsigned long i = 0;
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
   EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
   SWL_Init();
   RTI_Init();
  //  Clock_Set20MHZ();
 
  //Clock_Set24MHZ();
//   RTICTL = 0b10010111;
 

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    // if (CRGFLG_RTIF) //check if the RTI period over?
    // {
    //     CRGFLG = CRGFLG_RTIF_MASK; //clears the flag 
    //     SWL_TOG(SWL_RED); //toggles red led
    // }

///tier 1
    SWL_TOG(SWL_RED);
    RTI_Delay_ms(10); 
     
     if(SWL_Pushed(SWL_UP)>0) 
     {
        RTI_Delay_ms(8);
        SWL_TOG(SWL_RED);
         
        
     }
     if(SWL_Pushed(SWL_DOWN)>0)
     { 
        RTI_Delay_ms(12);
        SWL_TOG(SWL_RED);
      
          

     }

//tier 2

// if(SWL_Pushed(SWL_LEFT))
// {
  
//     SWL_ON(SWL_RED);
//     RTI_Delay_ms(1);
//     SWL_OFF(SWL_RED);
//     RTI_Delay_ms(9);
// }

// //tier 3

// if(SWL_Pushed(SWL_RIGHT))
// {
//    SWL_OFF(SWL_RED);
//    SWL_ON(SWL_GREEN);
// }







  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
