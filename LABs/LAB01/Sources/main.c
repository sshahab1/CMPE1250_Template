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
char arrayofstr[20];
char escSeq[20];
unsigned char character;
/********************************************************************/
// Local Prototypes
// /********************************************************************/
void sci0_GotoXY(int iCol, int iRow);
void sci0_txStrXY(int Col, int Row, char const *straddr);

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

  char arrayop1[20];
  char hexop1[20];
  char hexArray[] = {'A', 'B', 'C', 'D'};
  int i;
  char storeChar[20];
  unsigned int result;
  // main entry point
  char str[20];
  char vowels;

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

  // sci0_txStr("OP A: ");
  // sci0_txStr(" OP B: ");
  // sci0_txStr("\x1b[1;1H Saamia Shahab");
  // sci0_txStr("\x1b[2;1H Simple Binary Calculator");
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {

    sci0_txStrXY(1, 1, "Saamia Shahab");
    sci0_txStrXY(2, 1, "Simple Binary Calculator");

    sci0_txStrXY(5, 5, "OP A:");
    sci0_txStrXY(5, 12, "0x");
    sci0_txStrXY(5, 14, "1234");
    sci0_txStrXY(5, 20, "(");
    sci0_txStrXY(5, 21, "04660");
    sci0_txStrXY(5, 26, ")");

    
      if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
      {
        
          character = SCI0DRL;
          sci0_GotoXY(5, 14);
      }
  

    sci0_txStrXY(6, 5, "OP B:");
    sci0_txStrXY(6, 12, "0x");
    sci0_txStrXY(6, 14, "ABCD");
    sci0_txStrXY(6, 20, "(");
    sci0_txStrXY(6, 21, "43981");
    sci0_txStrXY(6, 26, ")");

    sci0_txStrXY(9, 10, "&");

   
    sci0_txStrXY(8, 12, " ");
       sci0_ShowBin16(43981);
    sci0_txStrXY(9, 12, "01110000011100000");
    sci0_txStrXY(10, 12, "-----------------");
    sci0_txStrXY(11, 12, "01110000011100000");




for(i=0;i<10;i++){
  storeChar[i]=character;
}
    sci0_txStrXY(20, 20, storeChar);

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

    // sci0_txStr("\x1b[1;1H cool ");

    // sci0_txStrXY(5, 5, "My Name is Saamia");

    //  char str[20];
    //  sprintf(str, "\x1b[%d;%dH ", 5, 5);
    // sci0_txStr(str);

    ///////////////////////////WORKS/////////////////////////////////

    // show decimal to binary
    //  sci0_ShowBin16(43981);

    // sci0_txStr("  \x1b[6;1H ");

    // sprintf(arrayop1, " HEXNUM: %d ",  ToDigitVal('A'));
    // sci0_txStr(arrayop1);

    // hex to decimal
    //      result = HexArrayToUInt16(hexArray);

    // sprintf(hexop1,"\x1b[6;1H %05d", result);

    // sci0_txStr(hexop1);

    ////////////////////////////////////////////////////////////////

    /////////////////////////////////

    // sci0_txStr("Binary OP B: ");
    // sci0_ShowBin16(43981);

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
    // sci0_ShowBin16(result);
  }
}
/********************************************************************/
// Functions
/********************************************************************/

void sci0_GotoXY(int x, int y)
{
  sprintf(arrayofstr, "\x1b[%d;%dH", x, y);
  sci0_txStr(arrayofstr);
}
void sci0_txStrXY(int Col, int Row, char const *straddr) ////need help with this
{
  sci0_GotoXY(Col, Row);
  // sprintf(straddr, "\x1b[%d;%dH", Col, Row);
  sci0_txStr(straddr);
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
