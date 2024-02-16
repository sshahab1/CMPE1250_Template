/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia Shahab
// Details:       A more detailed explanation of the program is entered here
// Date:          Feb 16 2024
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
int Switches(void);
void REDLED(void);
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

    /// delay function red led functon nested
    REDLED();
    //  SWL_ON(SWL_RED);
    //  DelayFunction();
    //  SWL_OFF(SWL_RED);
    //  DelayFunction();

    //    int pressed = Switches();

    // if(pressed == 3)
    // {
    //   SWL_ON(SWL_ALL);

    // }
    //    if(pressed == 2)
    //    {
    //     SWL_ON(SWL_GREEN);
    //     SWL_OFF(SWL_YELLOW);
    //     SWL_OFF(SWL_RED);
    //    }
    //    if(pressed == 1)
    //    {
    //     SWL_ON(SWL_RED);
    //     SWL_OFF(SWL_GREEN);
    //     SWL_OFF(SWL_YELLOW);
    //    }
    //    if(pressed == 0){
    //     SWL_ON(SWL_YELLOW);
    //     SWL_OFF(SWL_GREEN);
    //     SWL_OFF(SWL_RED);
    //    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int Switches(void)
{
  int i = 0;
  if (SWL_Pushed(SWL_LEFT) > 0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_RIGHT) > 0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_UP) > 0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_DOWN) > 0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_CTR) > 0)
  {
    i++;
  }

  return i;
}
int Helper(void)
{

  int i = 0;

  if (SWL_Pushed(SWL_RED) > 0) // if any switches on
  {
    i++;
  }
  if (SWL_Pushed(SWL_YELLOW) > 0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_GREEN) > 0)
  {
    i++;
  }

  return i;
}

void DelayFunction(void)
{
  for (j = 0; j < ; j++)
  {
  }
}

void REDLED(void)
{
  SWL_ON(SWL_RED);
  DelayFunction();
  SWL_OFF(SWL_RED);
  DelayFunction();
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
