#include <hidef.h>
#include "derivative.h"
#include "sci.h"

void sci0_Init(void){
     SCI0BD = 32; 
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
