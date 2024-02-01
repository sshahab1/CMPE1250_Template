/********************************************************************/
// HC12 Program:  ICA 04 using ossciliscope and waveform to measure 
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:       A more detailed explanation of the program is entered here               
// Date:          Jan 29
// Revision History :
//  created ica04 
//worked on part 1 and 2 


/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
void RED (int b0n);

/********************************************************************/
// Global Variables
/********************************************************************/
uint16_t uiMainLoopCount = 0;
unsigned int i = 0;
unsigned long j = 0;
/********************************************************************/
// Constants
/********************************************************************/
#define RED_LED 0b10001111
#define Yellow_LED 0b01000000
#define Green_LED 0b00100000
/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
  PT1AD1 &=0x1F;
  
  DDR1AD1 = 0xE0;


/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
{
    PT1AD1 ^= RED_LED;
    for(j=0;i<500000;j++)
    {
        
    }
  //++uiMainLoopCount;
  //RED(uiMainLoopCount<0x1000);
}            
}

/********************************************************************/
// Functions
/********************************************************************/
void RED(int b0n)
{
  if(b0n)
  {
    PT1AD1 |= (1<<7);
  }
  else{
    PT1AD1 &= 0x7F;
  }
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
