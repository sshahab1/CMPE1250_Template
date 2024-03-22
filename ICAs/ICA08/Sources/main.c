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
unsigned char ch;
unsigned char character;
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
  sci0_Init();
  Clock_Set20MHZ();
  // SCI0BD=130;

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    Delay(50);
    SWL_TOG(SWL_RED); // run here o see if its running at 10 Hz on red pin

    ch = rand() % 26 + 'A';

    if (SCI0SR1_TDRE)
    {
      SCI0DRL = ch;
    }
    // sci0_read(unsigned char *pData) if charcter recieved

    // if(Vowels(ch)){
    //   SWL_ON(SWL_GREEN);
    //   SWL_OFF(SWL_YELLOW);
    // }
    // else{
    //   SWL_ON(SWL_YELLOW);
    //   SWL_OFF(SWL_GREEN);
    // }

    // character = SCI0DRL;
    // char * keych = &character;

    // SCI0DRL - READS FROM KEYBOEARD
    
  //  if(SCI0SR1_RDRF)
//      {
//         pData = SCI0DRL;
//      
//     }

    
    if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
    {
      // sci0_read(&character);
      // &keych = SCI0DRL;
     
        character=SCI0DRL;
        
        if (Vowels(character))
        {
          SWL_ON(SWL_GREEN);
          SWL_OFF(SWL_YELLOW);
        }
        else
        {
          SWL_ON(SWL_YELLOW);
          SWL_OFF(SWL_GREEN);
        }
      
    }
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
