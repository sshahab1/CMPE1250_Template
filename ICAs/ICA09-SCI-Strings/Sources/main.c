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
unsigned char ch;
unsigned int i;
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
    char output[30]; // Output buffer
    Delay(250);

    for (i = 0; i < 20; i++)
    {
      ch = (rand() % 5) + 'a';

      if (SWL_Pushed(SWL_CTR)) // if the button is pushed, transmit uppercase vowels
        ch = toupper(ch);

      // transmit only if the character is a vowel
      if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
      {
        if (SCI0SR1_TDRE)
        {
          SCI0DRL = ch;
          SWL_ON(SWL_RED);
        }
      }
        output[i] = ch; //store transmitted character in output buffer
    }
    Delay(250);
  }
}
  /********************************************************************/
  // Functions
  /********************************************************************/
  int Vowels(unsigned char ch)
  {
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  /********************************************************************/
  // Interrupt Service Routines
  /********************************************************************/
