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
  lcd_Init();
  lcd_StringXY( 2, 2, "Saamia Shahab");
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
      
  
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
