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
  SCI0BD=130;
  SCI0R2_TE=1;      
  SCI0R2_RE=1;

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    if(SCI0SR1_TDRE)
    {
      SCI0DRL = 'A';
    }
    if(SCI0SR1_RDRF)
    {
      ch = toupper(char)SCI0DRL
      SWL_ON(SWL_RED);
    }
   
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
