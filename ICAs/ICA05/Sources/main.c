/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
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
// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
     int Helper(void);
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
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    /// Tier 1
    // if(SWL_Pushed(SWL_LEFT))
    // {
    //   SWL_ON(SWL_RED);
    // }
    // else{
    //   SWL_OFF(SWL_RED);
    // }

    // if(SWL_Pushed(SWL_CTR))
    // {
    //   SWL_ON(SWL_YELLOW);
    // }
    // else{
    //   SWL_OFF(SWL_YELLOW);
    // }

    // if(SWL_Pushed(SWL_RIGHT))
    // {
    //    SWL_ON(SWL_GREEN);
    // }
    // else{
    //    SWL_OFF(SWL_GREEN);
    // }

    // Tier 2
    //  if(SWL_Pushed(SWL_LEFT))
    //  {
    //    SWL_ON(SWL_RED);
    //  }
    //  if(SWL_Pushed(SWL_CTR))
    //   {
    //      SWL_ON(SWL_YELLOW);
    //   }
    //   if(SWL_Pushed(SWL_RIGHT))
    //   {
    //      SWL_ON(SWL_GREEN);
    //   }
    //   if(SWL_Pushed(SWL_DOWN))
    //   {
    //    SWL_OFF(SWL_RED);
    //    SWL_OFF(SWL_YELLOW);
    //    SWL_OFF(SWL_GREEN);
    //   }
    //   if(SWL_Pushed(SWL_UP))
    //   {
    //       SWL_OFF(SWL_RED);
    //      SWL_OFF(SWL_YELLOW);
    //      SWL_OFF(SWL_GREEN);
    //   }

    // Tier 3

    int count = Helper();
    if (SWL_Pushed(SWL_LEFT))
    {
      if(count<2){
        SWL_ON(SWL_RED);
      }
    }
    if (SWL_Pushed(SWL_CTR) )
    {
      if(count<2){
        SWL_ON(SWL_YELLOW);
      }
    }
    if (SWL_Pushed(SWL_RIGHT))
    {
      if(count<2){
        SWL_ON(SWL_GREEN);
      }
    }
   



    if (SWL_Pushed(SWL_DOWN))
    {
      SWL_OFF(SWL_RED);
      SWL_OFF(SWL_YELLOW);
      SWL_OFF(SWL_GREEN);
    }
    if (SWL_Pushed(SWL_UP))
    {
      SWL_OFF(SWL_RED);
      SWL_OFF(SWL_YELLOW);
      SWL_OFF(SWL_GREEN);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int Helper(void)
{

  int i = 0;

  if (SWL_Pushed(SWL_RED)>0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_YELLOW)>0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_GREEN)>0)
  {
    i++;
  }
  
  return i;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
