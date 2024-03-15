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
int Switches(void);
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
  Clock_Set20MHZ();

  // Clock_Set24MHZ();
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

    int pushed = Switches();
    if (SWL_Pushed(SWL_RIGHT))
    {
      SWL_OFF(SWL_RED);
      SWL_ON(SWL_GREEN);
    }
    else
    {

      SWL_OFF(SWL_GREEN);

      if (pushed == 0 || pushed > 1)
      {
        Delay(10);
        SWL_TOG(SWL_RED);
      }
      if (SWL_Pushed(SWL_UP) > 0)
      {
        Delay(8);
        SWL_TOG(SWL_RED);
      }
      if (SWL_Pushed(SWL_DOWN) > 0)
      {
        Delay(12);
        SWL_TOG(SWL_RED);
      }

      // tier 2

      if (SWL_Pushed(SWL_LEFT) > 0)
      {
       
        SWL_ON(SWL_RED);
        Delay(1);
        SWL_OFF(SWL_RED);
        Delay(9);
      }
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int Switches(void) // creating a funtion that counts up
{
  int i = 0;
  if (SWL_Pushed(SWL_LEFT) > 0) // if left is pressed count ++
  {
    i++;
  }
  if (SWL_Pushed(SWL_RIGHT) > 0) // if right is pressed count ++
  {
    i++;
  }
  if (SWL_Pushed(SWL_UP) > 0) // if up is pressed count ++
  {
    i++;
  }
  if (SWL_Pushed(SWL_DOWN) > 0) // if down is pressed count ++
  {
    i++;
  }
  if (SWL_Pushed(SWL_CTR) > 0) // if center is pressed count ++
  {
    i++;
  }

  return i; // return the value of i
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
