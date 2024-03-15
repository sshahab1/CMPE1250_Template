#include <hidef.h>
#include "derivative.h"
#include "sci.h"

void sci0_Init(void)
{
    SCI0BD = 130; // math: 20E6 / (9600*16)
}
int sci0_read(unsigned char *pData)
{
    //  if(SCI0SR1_RDRF)
    // {
    // //pData = SCI0DRL;
    //   return 1;
    // }
    // else{
    //     return 0;
    // }

    if (SCI0SR1 & SCI0SR1_RDRF_MASK) // Check if a character has been received
    {
        pData = SCI0DRL;
        return 1;
    }
    return 0;
}
void sci0_txByte(unsigned char data)
{
    if (SCI0SR1_TDRE)
    {
        SCI0DRL = data;
    }
}