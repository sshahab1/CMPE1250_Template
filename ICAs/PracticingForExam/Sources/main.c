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
unsigned long j = 0;
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
    if(SWL_Pushed(SWL_CTR))
    {
    for(j=0;j<40000;j++)
    {
        
    }

      SWL_ON(SWL_RED);
      for(j=0;j<40000;j++)
    {
        
    }
    SWL_OFF(SWL_RED);
    SWL_ON(SWL_YELLOW);
    for(j=0;j<40000;j++)
    {
        
    }
    SWL_OFF(SWL_YELLOW);
    SWL_ON(SWL_GREEN);
    for(j=0;j<40000;j++)
    {
        
    }
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
