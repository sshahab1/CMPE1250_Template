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

Operation currentOperation = AND;

unsigned char key;
unsigned char character;
char arrayofstr[20];
char escSeq[20];

int iXEditPos = 0;             // X position (0-3)
int iYEditPos = 0;             // Y position (0-1)
unsigned int operand[2] = {0}; // 2 operands
/********************************************************************/
// Local Prototypes
// /********************************************************************/
void sci0_GotoXY(int iCol, int iRow);
void sci0_txStrXY(int Col, int Row, char const *straddr);
void sci0_ShowBinAnd(unsigned int num1, unsigned int num2);
void updateOperand(char key);

int hexCharToDecimal(char hex);
// Function to convert a hexadecimal string to its decimal equivalent
unsigned int hexToDecimal(const char *hexString);
// Function to convert a hexadecimal string to its binary equivalent
unsigned int hexToBinary(const char *hexString);
void sci0_ShowBinOr(unsigned int num1, unsigned int num2);

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
  char hexbuffer1[20];
  char hexbuffer2[20];
   char hexArray1[] = {'1', 'B', 'C', 'D'};
  char hexArray2[] = {'2', 'A', '3', 'C'};
 
  int i;
  char storeChar[20];
 
  //  main entry point
  char str[20];
  char vowels;
  ////newwww////
  // char character;
  // char hexOperandA[5] = "A2B4"; // Placeholder for operand A
  // char hexOperandB[5] = "0000"; // Placeholder for operand B
  int opA;
  int opB;
  unsigned int decimalA;
  unsigned int decimalB;
  unsigned int binaryA;
  unsigned int binaryB;
  unsigned int result;
  unsigned int result2;
  int sci0_current_x_position = 5;
  int sci0_current_y_position = 14;
  int currentOperand = 0; // Variable to store the index of the currently edited operand

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

    /********************************************************************/

    /////////////////////////////////////////WORKS GET RID OF THE RECIEVE//////////////////////////////
    sci0_txStrXY(1, 1, "Saamia Shahab");
    sci0_txStrXY(2, 1, "Simple Binary Calculator");

    sci0_txStrXY(5, 5, "OP A:");
    sci0_txStrXY(5, 12, "0x");
    //sci0_GotoXY(5,15);
   // sci0_txStr(hexArray1);
    sci0_txStrXY(5, 14, "1BCD" );
   sci0_txStrXY(5, 22, "(");


    result = HexArrayToUInt16(hexArray1);

    sprintf(hexbuffer1, "\x1b[5;22H %05d", result);

    sci0_txStr(hexbuffer1);

    sci0_txStrXY(5, 28, ")");

    sci0_txStrXY(6, 5, "OP B:");
    sci0_txStrXY(6, 12, "0x");
    
    sci0_txStrXY(6, 14, "2A3C");
    //  sci0_GotoXY(5,15);
    // sci0_txStr(hexArray2);
    sci0_txStrXY(6, 22, "(");
    result2 = HexArrayToUInt16(hexArray2);
    sprintf(hexbuffer2, "\x1b[6;22H %05d", result2);
    sci0_txStr(hexbuffer2);

    sci0_txStrXY(6, 28, ")");

    sci0_txStrXY(9, 10, "&");

    sci0_txStrXY(8, 12, " ");
    // sci0_ShowBin16(4660);
    sci0_ShowBin16(result);
    sci0_txStrXY(9, 12, " ");
    // sci0_ShowBin16(43981);
    sci0_ShowBin16(result2);
    sci0_txStrXY(10, 12, "-----------------");
    sci0_txStrXY(11, 12, " ");
    // sci0_ShowBinAnd(result, result2);
    sci0_ShowBinOr(result, result2);

// while(1){



//     for (i = 0; i < 4; ++i)
//     {
      
//        sci0_GotoXY(5+i, 16);
//       //check if a character has been received
//       if (SCI0SR1 & SCI0SR1_RDRF_MASK)
//       {

//         //a character has been received, read it from SCI0DRL
//         character = SCI0DRL;

//         //process the received key
//         if ((character >= '0' && character <= '9') || (character >= 'a' && character <= 'f') || (character >= 'A' && character <= 'F'))
//         {
//           //update the corresponding position in the hex array
      
//           hexTest[i] = character;
//         }
//       }
      
     
//     }

  
  //   //convert the hex array to a 16-bit value and display it
  //   result = HexArrayToUInt16(hexTest);
  //   //eet cursor position to display the result
  //  //sci0_GotoXY(5, 21);
  //  sprintf(hexop1, "\x1b[5;30H %05d", result);
  //   sci0_txStr(hexop1);

  //     sci0_GotoXY(5, 16);
  //   sci0_txByte(hexTest);

   












   
    //   sci0_GotoXY(14 + iXEditPos, 5 + iYEditPos);

    //   // for (int i = 0; i < 20; i++)
    //   // {
    //   //   str[i] = key;
    //   // }
    //   // sci0_txStrXY(20, 20, str);
    // }

    //////////////////////////////////WORKS THE TEMPELATE WORKS JUST GET RID OF THE RECIEVE////////////////////////////
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
void sci0_ShowBinAnd(unsigned int num1, unsigned int num2)
{
  unsigned int result = num1 & num2; // Perform bitwise AND operation
  sci0_ShowBin16(result);
}
void sci0_ShowBinOr(unsigned int num1, unsigned int num2)
{
  unsigned int result = num1 | num2; // Perform bitwise OR operation
  sci0_ShowBin16(result);
}

int hexCharToDecimal(char hex)
{
  if (hex >= '0' && hex <= '9')
  {
    return hex - '0';
  }
  else if (hex >= 'a' && hex <= 'f')
  {
    return hex - 'a' + 10;
  }
  else if (hex >= 'A' && hex <= 'F')
  {
    return hex - 'A' + 10;
  }
  else
  {
    return -1; // Invalid character
  }
}

// Function to convert a hexadecimal string to its decimal equivalent
unsigned int hexToDecimal(const char *hexString)
{
  unsigned int result = 0;
  while (*hexString)
  {
    result = result * 16 + hexCharToDecimal(*hexString);
    hexString++;
  }
  return result;
}

// Function to convert a hexadecimal string to its binary equivalent
unsigned int hexToBinary(const char *hexString)
{
  unsigned int result = 0;
  while (*hexString)
  {
    result = result << 4;
    result |= hexCharToDecimal(*hexString);
    hexString++;
  }
  return result;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
