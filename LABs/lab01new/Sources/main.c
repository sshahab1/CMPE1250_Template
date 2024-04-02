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
// #include "sci.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
typedef enum
{
  AND,
  OR
} Operation;

char operand1[5];
char operand2[5];
Operation operation;
int x;
int y;
// unsigned int operandA = 0x1234;
// unsigned int operandB = 0xABCD;
// Operation op = AND;
unsigned char character;
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
  // SCI0BD = 32;
  // SCI0CR2 = 0b00001100;

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    // displaying name and description
    sci0_txStr("\x1b[1;1H Saamia Shahab");

    sci0_txStr("\x1b[2;1H Simple Binary Calculator");
    // Draw initial state
    DrawState(0x1234, 0xABCD, operation);

    if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
    {
      character = SCI0DRL;
      if (character == '&')
      {
        operation = AND;
        DrawState(0x1234, 0xABCD, operation);
      }
      else if (character == '|')
      {
        operation = OR;
        DrawState(0x1234, 0xABCD, operation);
      }

    }
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
