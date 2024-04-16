/********************************************************************/
// HC12 Program:  Lab01 - Labs
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:      Lab s a calculator for the binary
// Date:          April 1
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
#include "segs.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter = 0;
unsigned int loopCount = 0;
unsigned int i = 4;
// unsigned int currentStateUp=0;
// unsigned int currentStateDown=0;
unsigned int oldStateUp= 0;
unsigned int oldStateDown= 0;

unsigned int pressedUp = 0;
unsigned int pressedDown = 0;

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{

  // Initialize the processor, device, and peripherals
  // main entry point
  _DISABLE_COP();
  EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();
  RTI_Init();
  sci0_Init();
  Clock_Set20MHZ();
  Segs_Init();

  // while(1)
  // {
  //     Segs_Custom(4, 0b00000000);
  //     Delay(200);
  //     Segs_Custom(5, 0b00000000);
  //     Delay(200);
  //     Segs_Custom(6, 0b00000000);
  //     Delay(200);
  //     Segs_Custom(7, 0b00000000);
  //     Delay(200);
  //     Segs_Custom(7, 0b10000000);
  //     Segs_Custom(6, 0b10000000);
  //     Segs_Custom(5, 0b10000000);
  //     Segs_Custom(4, 0b10000000);
  //     Delay(200);

  // }
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {

    SWL_TOG(SWL_RED);

    // Delay(1000);
    // Segs_16H(i, 1);
    // SWL_TOG(SWL_GREEN);
    // i++;

    // if (SWL_Pushed(SWL_CTR))
    // {
    //   counter = 0;
    //   Segs_16D(0, 0);
    // }
    if (loopCount % 4 == 0)
    {

      if (i < 8)
      {
        Segs_Custom(i, 0b00000000);
        i++;
      }
      else
      {
        Segs_ClearLine(Segs_LineBottom);
        i = 4;
      }
    }
    if (loopCount == 20)
    {

      int currentStateUp = SWL_Pushed(SWL_UP);
      int currentStateDown = SWL_Pushed(SWL_DOWN);
      if ((currentStateUp != oldStateUp) & currentStateUp)
      {
        pressedUp = 1;
        pressedDown = 0;
      }
      if ((currentStateDown != oldStateDown) & currentStateDown)
      {
        pressedUp = 0;
        pressedDown = 1;
      }
      if (pressedUp > 0)
      {
        Segs_16H(counter++, Segs_LineTop);
      }
      else if (pressedDown > 0)
      {
        Segs_16D(counter++, Segs_LineTop);
      }

      oldStateDown = currentStateDown;
      oldStateUp = currentStateUp;
      
      SWL_TOG(SWL_GREEN);
      loopCount = 0;
    }

    Delay(50);
    loopCount++;
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
