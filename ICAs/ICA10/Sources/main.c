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

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{

  int centerBtnPushed;
  int  animatedcaret;
  int i = 0;
  char caret[100];
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
    Segs_8H(7, '4');
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
      Segs_16H(0xFFFF - i, 0);
      Segs_16H(i, 1);
      i++;
    }
  if(centerBtnPushed)
  {
     animatedcaret=(animatedcaret+1) % 6;
     Segs_Custom(animatedcaret, 0b10000000|caret[animatedcaret]);
     

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
