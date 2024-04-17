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
unsigned char caret[] =
    {
        0b11000000, // a
        0b10100000, // b
        0b10010000, // c
        0b10000001, // d
        0b10001000, // e
        0b10000010  // f
};
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{

  int centerBtnPushed = 0;
  int animatedcaret = 0;
  int i = 0;
  // int caret[24];
  int loopCount = 0;
  int caretPosn = 0;
  int caretMovedTotal = 0;

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

  // Segs_Clear();
  Segs_8H(7, 0b11100100);
  Segs_Custom(1, 0b01001010);
  Segs_Custom(2, 0b11110000);
  Segs_Custom(5, 0b10001011);
  Segs_Custom(6, 0b10110001);
  Segs_Normal(4, '3', Segs_DP_OFF);

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {

 
   Delay(100);

    if (SWL_Pushed(SWL_CTR))
    {
      centerBtnPushed = 1;
      Segs_16H(0xFFFF - i, Segs_LineBottom);
      Segs_16H(i, Segs_LineTop);
      i++;
    }
    if (centerBtnPushed)
    {
      animatedcaret = (animatedcaret + 1) % 6;
      Segs_Custom(caretPosn, caret[animatedcaret]);
      if (SWL_Pushed(SWL_RIGHT))
      {
        loopCount++;
        if (loopCount >= 10)
        {
          Segs_ClearLine(Segs_LineTop);
          caretPosn = (caretPosn + 1) % 4;
          caretMovedTotal++;

          loopCount = 0;
        }
      }

    else if (SWL_Pushed(SWL_LEFT))
      {

        loopCount++;
        if(loopCount >= 10)
        {
          Segs_ClearLine(Segs_LineTop);
          caretPosn--;
          caretPosn = (caretPosn % 4 + 4) % 4;
          caretMovedTotal++;

          loopCount = 0;
        }
      }


     //Segs_16H(caretMovedTotal, Segs_LineBottom); //display the count

    }
    // Segs_8H(7, 0xF,  Segs_DP_OFF );
    //  Segs_Normal(3,12, Segs_DP_ON);
    //  Segs_Normal(6, 0x0F, Segs_DP_OFF);
    //  Segs_Custom(4, 0b10100101);
    //  Segs_Custom(6, 0b00000000);
    //  Segs_Custom(3, 0b11100110);
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
