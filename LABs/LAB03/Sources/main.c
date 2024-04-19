/********************************************************************/
// HC12 Program:  Lab01 - Labs
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:      Lab s a calculator for the binary
// Date:          April 17
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
#define MAX_DIGITS 4

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter = 0;
// unsigned int loopCount = 0;
unsigned int i = 0;
// unsigned int currentStateUp=0;
// unsigned int currentStateDown=0;
unsigned int oldStateUp = 0;
unsigned int oldStateDown = 0;

unsigned int pressedUp = 0;
unsigned int pressedDown = 0;
int array[20];
unsigned int counts[MAX_DIGITS] = {0}; // Array to store counts for each digit
unsigned int loopCount = 0; 
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
 // int count = 0;
  int j;
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

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    Delay(100);

    // Segs_Normal(4, '3', Segs_DP_ON);

    //  if(count<10)
    //  {
    //     if(SWL_Pushed(SWL_UP))
    //     {
    //       Segs_16D(count, Segs_LineTop);
    //       //Segs_16DDecimal(i,  Segs_LineTop, Segs_DP_ON);
    //       count++;
    //     }

    //  }
/////////////////////////////////////////////////////////WORKS KINDOF
    // Segs_16DDP(count, i);
    // {
    //   if (SWL_Pushed(SWL_UP))
    //   {
    //       if (++count > 9)
    //       {
    //         count = 0;
    //       }

    //       for( j = 0; j < 4;j++)
    //       {
    //           array[j]=count;
    //       }
    //     //oldStateUp = curStateUp;
    //   }
    // }
    //  if (SWL_Pushed(SWL_RIGHT))
    // {
    //   if (loopCount % 4 == 0)
    //   {
        
    //     if (i < 4)
    //     {
    //        Segs_ClearDigit(i-1);
    //       Segs_Custom(i, 0b00000000);
    //       i++;
    //     }
    //     else
    //     {
    //       Segs_ClearLine(Segs_LineTop);
    //       i = 0;
    //     }
    //   }
    // }

    ///////////////////////////////////////////////////////////////////////////
    // Simulated SWL_Pushed calls
        // int SWL_Pushed(SWL_UP)= 0; // Simulated condition
        // int SWL_Pushed(SWL_RIGHT) = 0; // Simulated condition

        // if (SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_RIGHT)) {
            if (SWL_Pushed(SWL_UP)) {
                // Increase count at the current digit and wrap around if necessary
                counts[i % MAX_DIGITS] = (counts[i % MAX_DIGITS] + 1) % 10;
            }

            if (SWL_Pushed(SWL_RIGHT)) {
                if (loopCount % 4 == 0) {
                    if (i < MAX_DIGITS) {
                        Segs_ClearDigit(i - 1);
                        Segs_Custom(i, 0b00000000);
                        i++;
                    } else {
                        Segs_ClearLine(Segs_LineTop);
                        i = 0;
                    }
                }

                // Update display with the counts array
                for (j = 0; j < MAX_DIGITS; j++) {
                    Segs_16DDP(counts[j], j);
                }
            }
        
   // Segs_16DDP(count, 0);
    //   if (SWL_Pushed(SWL_UP))
    //   {
    //     if (++count > 9)
    //     {
    //       count = 0;
    //     }
    //   }
    // if (SWL_Pushed(SWL_RIGHT))
    // {

    //   if (loopCount % 4 == 0)
    //   {
    //     if (i < 4)
    //     {
    //       Segs_Normal(i, count, Segs_DP_ON);
    //       //   count++;
    //       //   // Segs_Custom(i, 0b00000000);
    //       i++;
    //     }
    //     else{
    //       i=0;
    //     }
    //   }
    // }

   
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
