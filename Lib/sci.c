#include <hidef.h>
#include "derivative.h"
#include "sci.h"





void sci0_Init(void){
    // SCI0BD = 130; // math: 20E6 / (9600*16) //9600
     //SCI0BD = 65; // for 19200
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
