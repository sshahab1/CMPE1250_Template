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
  Clock_Set20MHZ();
  SCI0BD=130;
  SCI0R2_TE=1;
  SCI0R2_RE=1;

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    Delay(50);
    SWL_TOG(SWL_RED); //run here o see if its running at 10 Hz on red pin
    unsigned char random = rand() % 26 + 'A';
    printf("Random Char:", random);

//sci0_read(unsigned char *pData) if charcter recieved


    if(Vowels(random)){
      SWL_ON(SWL_GREEN);
      SWL_OFF(SWL_YELLOW);
    }
    else{
      SWL_ON(SWL_YELLOW);
      SWL_OFF(SWL_GREEN);
    }

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
