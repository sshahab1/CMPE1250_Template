#include <hidef.h>
#include "derivative.h"
#include "sci.h"

void sci0_Init(void)
{
    // SCI0BD = 130; // math: 20E6 / (9600*16) //9600
    // SCI0BD = 65; // for 19200
    SCI0BD = 32; // for 38400 20000000/16/38400  -----lab1 -----
    SCI0CR2 = 0b00001100;
}
// int sci0_read(unsigned char *pData)
//  {
//     if(SCI0SR1_RDRF)
//      {
//         pData = SCI0DRL;
//       return 1;
//     }
//     else{
//           return 0;
//     }
//     // if (SCI0SR1 & SCI0SR1_RDRF_MASK) // Check if a character has been received
//     // {
// //         pData = SCI0DRL;
// //         return 1;
// //     }
// //     return 0;
// // }
//  }

///////////////mine/////////////////////
// void sci0_txByte(unsigned char data)
// {
//     if (SCI0SR1_TDRE)
//     {
//         SCI0DRL = data;
//     }
// }
// void sci0_txStr (char const * straddr)
// {
// for (; *straddr; ++straddr)
// sci0_txByte (*straddr);
// }

// send a byte to SCI0 (blocking)
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
void sci0_GotoXY(int iCol, int iRow)
{
    sprintf("\x1b[%d;%dH", iRow, iCol);
}
// use sci0_GotoXY and sci0_txStr to place the string
void sci0_txStrXY(int iCol, int iRow, char const *straddr) ////need help with this
{
    sci0_GotoXY(iCol, iRow);
    sci0_txStr(straddr);
}
// use an escape sequence to clear the terminal
void sci0_ClearScreen(void)
{
    sprintf("\x1b[2J");
}
void sci0_ShowBin16(unsigned int iVal)
{
    int i;
    for (i = 15; i >= 0; i--)
    {
        // sci0_txByte(iVal & 0x80 ? '1' : '0');
        // iVal <<= 1;

        if (iVal & (1 << i))
        {
            sci0_txByte("1");
        }
        else
        {
            sci0_txByte("0");
        }
    }
    // unsigned int value = 1234; // Example value
    // sprintf("Binary representation of %d is: ", value);
    // sci0_ShowBin16(value);
    // sprintf("\n");
    // return 0;
}
int ToDigitVal(char digit)
{
    if (digit >= '0' && digit <= '9')
    {
        // converting '0'-'9' to numerical value (48-57 in ASCII)
        return digit - '0';
    }
    else if (digit >= 'a' && digit <= 'f')
    {
        // converting 'a'-'f' to numerical value (97-102 in ASCII)
        return digit - 'a' + 10;
    }
    else if (digit >= 'A' && digit <= 'F')
    {
        // converting 'A'-'F' to numerical value (65-70 in ASCII)
        return digit - 'A' + 10;
    }
    else
    {
        // invalid character so returning 0
        return 0;
    }
}
unsigned int HexArrayToUInt16(char *pArray)
{
    unsigned int result = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        // multipling the current result by 16 and add the value of the current digit
        result = (result << 4) + ToDigitVal(pArray[i]);
    }
    return result;

    // char hexArray[5] = "1A2F"; //example array representing hexadecimal value 0x1A2F
    //     unsigned int value = HexArrayToUInt16(hexArray);
    //     printf("Numerical value of hex array: %u\n", value);
    //     return 0;
}
typedef enum
{
    AND,
    OR
} Operation;
void DrawState(unsigned int iOPA, unsigned int iOPB, Operation op)
{ //////////////fix this for performance
    unsigned int i;

    sci0_ClearScreen();
    sci0_txStrXY(5, 5, "OP A: '%04X' (%u)", iOPA,iOPA); // hex
    sci0_txStrXY(5, 6, "OP B: '%04X' (%u)", iOPB,iOPB); // hex

    sci0_ShowBin16(iOPA); //binary 
    sci0_txStrXY(11, 8, "%d", iOPA); // 0111000

     sci0_ShowBin16(iOPB);//binary
    sci0_txStrXY(11, 9, "OP B: %d", iOPB); // 010101011

    sci0_txStrXY(9, 9, "%d", op);
    unsigned int result;
    if (op == AND) {
        result = iOPA & iOPB;
        sci0_txStrXY(11, 11, "RESULT: ");
    } else {
        result = iOPA | iOPB;
       sci0_txStrXY(11, 11, "RESULT: ");
    }
    sci0_ShowBin16(result); //

   
}