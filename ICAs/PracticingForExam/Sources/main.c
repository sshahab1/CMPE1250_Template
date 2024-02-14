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
#define ring
/********************************************************************/
// Local Prototypes
/********************************************************************/
     int Helper(void);
     void DelayFunction(void);
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
    #ifdef ring
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
    #endif

////////////////LEFTTTTT SWITCHHHH///////////////////////
    if(SWL_Pushed(SWL_LEFT))
    {
    DelayFunction();
    
    SWL_ON(SWL_GREEN);

      DelayFunction();

    SWL_OFF(SWL_GREEN);
    SWL_ON(SWL_YELLOW);
    
    DelayFunction();

    SWL_OFF(SWL_YELLOW);
    SWL_ON(SWL_RED);

    DelayFunction();

    SWL_OFF(SWL_RED);
    }

  if(SWL_Pushed(SWL_DOWN)>0)
  {
    // if(SWL_OFF(SWL_YELLOW))
    // {
      SWL_ON(SWL_YELLOW);
    //}
  
  }
  else{
      SWL_TOG(SWL_YELLOW);
  }
  DelayFunction();


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

void DelayFunction(void)
{
   for(j=0;j<40000;j++)
  {
        
  }

}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
