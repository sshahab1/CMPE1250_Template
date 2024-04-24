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
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  char name[20] = "Saamia Shahab";
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

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    //lcd_Data('Q'); --works
    SWL_ON(SWL_RED);
    
    //lcd_AddrXY(2,5);
    //lcd_String("Saamia");

    //lcd_StringXY(2,5, "Saamia");
    lcd_StringXY(0,2, "This is spam!");

  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
