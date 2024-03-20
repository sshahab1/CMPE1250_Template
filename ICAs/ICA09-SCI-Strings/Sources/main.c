/********************************************************************/
// HC12 Program:  ICA09-SCI-Strings
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
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

Vowels(unsigned char ch);
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
  sci0_Init();
  Clock_Set20MHZ();
  

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
int Vowels(unsigned char ch)
{
  if(ch == 'A'||ch == 'E'||ch == 'I'||ch == 'O'||ch == 'U')
  {
    return 1;
  }
  else{
    return 0;
  }
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
