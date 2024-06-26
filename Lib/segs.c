#include <hidef.h>
#include "derivative.h"
#include "segs.h"

///////local helpers///////
#define Segs_WLATCH   \
    PORTA &= (~0x01); \
    PORTA |= 0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;

void Segs_Init(void)
{
    PORTA |= 0x03; // port pins high
    DDRA |= 0x03;  // direction of port pinns as outputs
    DDRB = 0xff;   // direction of the port pins as outputs
    Segs_Clear();
}
void Segs_Normal(unsigned char Addr, unsigned char Value, Segs_DPOption dp)
{
    Addr &= 0x07;
    Addr |= 0b01011000;

    if (dp)
    {
        Value &= ~(0x80);
    }
    else
    {
        Value |= 0x80;
    }
    PORTB = Addr;
    Segs_MH;
    Segs_WLATCH;
    PORTB = Value;
    Segs_ML;
    Segs_WLATCH;
}
void Segs_Custom(unsigned char Addr, unsigned char Value)
{
    Addr &= 0x07;
    Addr |= 0b01111000;

    // if(dp)
    // {
    //     Value &=(~0x80);
    // }
    // else
    // {
    //     Value |= 0x80;
    // }

    // PORTB does both hold and transfer the value
    PORTB = Addr;
    Segs_MH;
    // like a micro wave open put foof in then close it
    Segs_WLATCH; // open the ting so stuff can go
    PORTB = Value;
    Segs_ML;
    Segs_WLATCH; // lacting - close it
}
void Segs_Clear(void)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        Segs_Custom(i, 0b10000000);
    }
}
void Segs_ClearDigit(unsigned char cToClear){
    Segs_Custom(cToClear, 0b10000000);
}
void Segs_ClearLine(Segs_LineOption line)
{
    int i;
    unsigned char startAddr = 0;

    if (line == Segs_LineBottom)
    {
        startAddr = 4; // Start address for the bottom line
    }

    for (i = 0; i < 4; i++)
    {
        Segs_Custom(startAddr + i, 0b10000000); // Clear each segment of the line
    }
}
void Segs_8H(unsigned char Addr, unsigned char Value)
{
    unsigned char hChar, lChar;

    Addr &= 0x7;
    hChar = Value >> 4;
    lChar = Value & 0x0F;

    Segs_Normal(Addr, hChar, Segs_DP_OFF);

    if (Addr < 7)
    {
        Segs_Normal(Addr + 1, lChar, Segs_DP_OFF);
    }
    else
    {
        Segs_Normal(0, lChar, Segs_DP_OFF);
    }
}
void Segs_16H(unsigned int Value, Segs_LineOption line)
{
    unsigned char i;
    unsigned char offset = 0;
    unsigned int cDisplay;

    // if (line == Segs_LineBottom)
    // {
    //     offset = 4;
    // }

    if(line == Segs_LineTop)
    {
        offset=0;
    }
     else  if (line == Segs_LineBottom)
    {
        offset = 4;
    }
    for (i = 0; i < 4; i++)
    {
        cDisplay = (Value >> (unsigned char)((3 - i) * 4)) & 0xF;
        Segs_Normal(i + offset, (unsigned char)cDisplay, Segs_DP_OFF);
    }
}
void Segs_16D(unsigned int input, Segs_LineOption line)
{
    unsigned char index = 0;
    unsigned int Value;


    if(line == Segs_LineTop)
    {
        index=0;
    }
     else  if (line == Segs_LineBottom)
    {
        index = 4;
    }
    if(input < 1000)
    {
        Value = HexToBCD16(input);
        Segs_8H(index, Value>>8);
        Segs_8H(index+2, Value&0xFF);
    }
    else{
        return;
    }
    // for(i = 0;i < 4; i++)
    // {
    //     cDisplay = (Value >> (unsigned char)((3 - i) * 4)) & 0xF;
    //     Segs_Normal(i + offset, (unsigned char)cDisplay, Segs_DP_OFF);
    // }
}
void Segs_16DDecimal(unsigned int input, Segs_LineOption line, Segs_DPOption dp)
{
    unsigned char index = 0;
    unsigned int Value;

    if (dp)
    {
        Value &= ~(0x80);
    }
    else
    {
        Value |= 0x80;
    }
  
    // Segs_MH;
    // Segs_WLATCH;
    // PORTB = Value;
    // Segs_ML;
    // Segs_WLATCH;
    if(line == Segs_LineTop)
    {
        index=0;
    }
     else  if (line == Segs_LineBottom)
    {
        index = 4;
    }
    if(input < 1000)
    {
        Value = HexToBCD16(input);
        Segs_8H(index, Value>>8);
        Segs_8H(index+2, Value&0xFF);
    }
    else{
        return;
    }
    // for(i = 0;i < 4; i++)
    // {
    //     cDisplay = (Value >> (unsigned char)((3 - i) * 4)) & 0xF;
    //     Segs_Normal(i + offset, (unsigned char)cDisplay, Segs_DP_OFF);
    // }
}
unsigned int HexToBCD16(unsigned int input)
{
    unsigned int value = 0;


    value +=(input%10) * 0x1;
    value +=((input/10) % 10) * 0x10;
    value +=((input/100) % 10) * 0x100;
    value +=((input/1000) % 10) * 0x1000;

    return value;

}
void Segs_16DDP(unsigned int input, unsigned int dpLocation){
    unsigned char index = 0;
    unsigned int Value;

    // if (dp)
    // {
    //     index &= ~(0x80);
    // }
    // else
    // {
    //     index |= 0x80;
    //  }
    if (dpLocation % 4 == dpLocation)
    {
        index = dpLocation; // go at location
    }
    else
    {
        index = 0; // start at location 0
    }
    if (input < 10000)
    {

        Value = HexToBCD16(input);

        Segs_8H(index, Value >> 8);
        Segs_8H(index + 2, Value & 0xFF);
    }
    else
    {
        return;
    }
}