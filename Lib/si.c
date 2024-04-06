#include <hidef.h>
#include "derivative.h"
#include "si.h"

void sci0_Init(void)
{
    SCI0BD = 130;
    SCI0CR2 = 0b00001100;
}
void sci0_txByte(unsigned char data)
{
    while (!SCI0SR1_TDRE)
        ; // Blocking
    // if(SCI0SR1_TDRE) // non blocking
    SCI0DRL = data;
}
void sci0_txStr(char const *straddr)
{
    for (; *straddr; ++straddr)
        sci0_txByte(*straddr);
}

// void positioning (int row, int col)
// {
//     sprintf("\x1b[%d;%dH", row, col); //red

// }

////LAB01////////////////////////////////
// return 1 if RDRF set, otherwise return 0
int sci0_Peek(void)
{
    if (SCI0SR1_RDRF) // SCI0SR1_RDRF
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// use an escape sequence to place the cursor at the specified position
// this is the \x1B[y;xH form with formatted argument replacement (sprintf)
// void sci0_GotoXY(int iCol, int iRow)
// {
//     sprintf("\x1b[%d;%dH", iCol, iRow);
// }
// use sci0_GotoXY and sci0_txStr to place the string
// void sci0_txStrXY(int iCol, int iRow, char const *straddr) ////need help with this
// {
//     sci0_GotoXY(iCol, iRow);
//     sprintf(straddr, "\x1b[%d;%dH", iRow, iCol);
//     sci0_txStr(straddr);
// }
// use an escape sequence to clear the terminal
void sci0_ClearScreen(void)
{
    sci0_txStr("\x1b[2J");
}
void sci0_ShowBin16(unsigned int iVal)
{

    char myString[20];
    int i;
    int remainder;
    int result;
    while (iVal > 0)
    {
        int remainder = iVal % 2;
        iVal /= 2;
        result = remainder.ToString() + result;
    }

    sprintf(myString, "%d", result);
    sci0_txStr(myString);
    // while (iVal > 0)
    // {
    //     for (i = 0; i < 20; i++)
    //     {
    //         remainder = iVal % 2;
    //         iVal /= 2;
    //         //myString[i] = remainder + myString[i];
    //         result = remainder + result;
    //         myString[i]=result.ToString();
    //     }
    // }
    // sprintf(myString, "The value = %d", iVal);
}
// int ToDigitVal(char digit)
// {
//     if (digit >= '0' && digit <= '9')
//     {
//         // converting '0'-'9' to numerical value (48-57 in ASCII)
//         return digit - '0';
//     }
//     else if (digit >= 'a' && digit <= 'f')
//     {
//         // converting 'a'-'f' to numerical value (97-102 in ASCII)
//         return digit - 'a' + 10;
//     }
//     else if (digit >= 'A' && digit <= 'F')
//     {
//         // converting 'A'-'F' to numerical value (65-70 in ASCII)
//         return digit - 'A' + 10;
//     }
//     else
//     {
//         // invalid character so returning 0
//         return 0;
//     }
// }
// unsigned int HexArrayToUInt16(char *pArray)
// {
//     unsigned int result = 0;
//     int i;
//     for (i = 0; i < 4; i++)
//     {
//         // multipling the current result by 16 and add the value of the current digit
//         result = (result << 4) + ToDigitVal(pArray[i]);
//     }
//     return result;

//     // char hexArray[5] = "1A2F"; //example array representing hexadecimal value 0x1A2F
//     //     unsigned int value = HexArrayToUInt16(hexArray);
//     //     printf("Numerical value of hex array: %u\n", value);
//     //     return 0;
// }

// void DrawState(unsigned int iOPA, unsigned int iOPB, Operation op)
// { //////////////fix this for performance

//     sci0_ClearScreen();
//     // sci0_txStrXY(5, 5, "OP A: %d", &iOPA); // hex
//     // sci0_txStrXY(5, 6, "OP B: %d", &iOPB); // hex

//     char hexArray[20];
//     char hexArrayB[20];

//     sprintf(hexArray, " %d ", iOPA);
//     sci0_txStr(hexArray);

//     sprintf(hexArrayB, " %d ", iOPB);
//     sci0_txStr(hexArrayB)

//         sci0_ShowBin16(iOPA);        // binary
//     sci0_txStrXY(11, 8, "%d", iOPA); // 0111000

//     sci0_ShowBin16(iOPB);                   // binary
//     sci0_txStrXY(11, 9, "OP B: %d", &iOPB); // 010101011

//     sci0_txStrXY(9, 9, "%d", &op);

//     sci0_txStr(11, 10, "--------------------------");
//     unsigned int result = 0;
//     if (op == AND)
//     {
//         result = iOPA & iOPB;
//         sci0_txStrXY(11, 11, "RESULT: ");
//     }
//     else
//     {
//         result = iOPA | iOPB;
//         sci0_txStrXY(11, 11, "RESULT: ");
//     }
//     sci0_ShowBin16(result); //
// // }

// void DrawState(unsigned int iOPA, unsigned int iOPB, Operation op) {
//     sci0_ClearScreen();

//     // Display operand A in hexadecimal
//      char hexArrayA[6];
//     sprintf(hexArrayA, "OP A: %0d", iOPA);
//     sci0_txStrXY(5, 5, hexArrayA);

//     // Display operand B in hexadecimal
//      char hexArrayB[6];
//     sprintf(hexArrayB, "OP B: %d", iOPB);
//     sci0_txStrXY(5, 6, hexArrayB);

//     // Display binary representation of operand A
//     sci0_txStrXY(5, 8, "Binary OP A: ");
//     sci0_ShowBin16(iOPA);

//     // Display binary representation of operand B
//     sci0_txStrXY(5, 9, "Binary OP B: ");
//     sci0_ShowBin16(iOPB);

//     // Draw a line
//     sci0_txStrXY(5, 10, "--------------------------");

//     // Calculate and display the result
//     unsigned int result = (op == AND) ? (iOPA & iOPB) : (iOPA | iOPB);
//     sci0_txStrXY(5, 11, "RESULT: ");
//     sci0_ShowBin16(result);
// }
///////////////////////////////////////////////////////////////
// void SCI0_BSend (unsigned char data)
// {
// 	// transmit buffer empty?
// 	while (!(UCSR0A & (1<<UDRE0)))
// 	;

// 	// transmit complete must be cleared before send in polling mode
// 	if (UCSR0A & (1<<TXC0))
// 	UCSR0A = (1<<TXC0);

// 	// free to send data
// 	UDR0 = data;
// }
// void SCI0_TxString (char * buff)
// {
//   while (*buff)
//   {
//     SCI0_BSend(*buff);
//     ++buff;
//   }
// }
// void SCI0_Tx16H (unsigned int uiVal, int tl)
// {
// 	char buff[7] = {0};
// 	(void)sprintf(buff, "0x%4.4X", uiVal);
// 	SCI0_TxString (buff);

// 	if (tl)
// 		SCI0_TxString ("\r\n");
// }
