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

// char operand1[5];
// char operand2[5];
Operation operation = AND;


char operand1[5] = 0x1234;
char operand2[5] = 0xABCD;
// Operation op = AND;
unsigned char character;

char A = 0x1234;
char B = 0xABCD;

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
unsigned int result;
char arrayop1[5];
char arrayop2[5];
unsigned int x;
unsigned int y;
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

   // displaying name and description
    // sci0_txStr("\x1b[1;1H Saamia Shahab");

    // sci0_txStr("\x1b[2;1H Simple Binary Calculator");

    // sci0_txStr("OP A: ");
    // sci0_txStr(" OP B: ");
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
 

    // // sci0_txByte(operand1);
    // // sci0_txStr(" ( ");
    // x=HexArrayToUInt16(&operand1);
    // sprintf(arrayop1, " HEXNUM1 %d ", x);
    // sci0_txStr(arrayop1);
    // // sci0_txStr(" ) ");

 
    // // sci0_txByte(operand2);
    // // sci0_txStr(" ( ");
    // y=HexArrayToUInt16(&operand2);
    // sprintf(arrayop2, " HEXNUM2 %d ", y);
    //  sci0_txStr(arrayop2);
    // sci0_txStr(" ) ");

    sci0_txStr("Binary OP A: ");
    sci0_ShowBin16(04660);
  

    sci0_txStr("Binary OP B: ");
    sci0_ShowBin16(43981);

   

    // if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
    // {
    //   character = SCI0DRL;
    //   if (character == '&')
    //   {
    //     operation = AND;
    //     //DrawState(0x1234, 0xABCD, operation);
    //   }
    //   else if (character == '|')
    //   {
    //     operation = OR;
    //    // DrawState(0x1234, 0xABCD, operation);
    //   }

    // }

    // if (operation == AND)
    // {
    //   result = HexArrayToUInt16(operand1) & HexArrayToUInt16(operand2);
    //   sci0_txStr("Result (AND): ");
    // }
    // else
    // {
    //   result = HexArrayToUInt16(operand1) | HexArrayToUInt16(operand2);
    //   sci0_txStr("Result (OR): ");
    // }

    // Draw the result in binary
    //sci0_ShowBin16(result);


  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
