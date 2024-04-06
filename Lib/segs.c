#include <hidef.h>
#include "derivative.h"
#include "segs.h"

///////local helpers///////
#define Segs_WLATCH PORTA &= (~0x01); PORTA |=0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;

void Segs_Init (void)
{
    PORTA |=0x03; //port pins high
    DDRA |=0x03; //direction of port pinns as outputs
    DDRB = 0xff; //direction of the port pins as outputs
    Segs_Clear();
}
void Segs_Normal (unsigned char Addr, unsigned char Value, Segs_DPOption dp)
{
    Addr &= 0x07;
    Addr |= 0b01011000;

    if(dp)
    {
        Value &=(~0x80);
    }
    else
    {
        Value |= 0x80;
    }
    PORTB=Addr;
    Segs_MH
    Segs_WLATCH
    PORTB=Value;
    Segs_ML
    Segs_WLATCH

}
 void Segs_Custom (unsigned char Addr, unsigned char Value)
{
    Addr &= 0x07;
    Addr |= 0b01001000;

    // if(dp)
    // {
    //     Value &=(~0x80);
    // }
    // else
    // {
    //     Value |= 0x80;
    // }

    //PORTB does both hold and transfer the value 
    PORTB=Addr;
    Segs_MH
    //like a micro wave open put foof in then close it 
    Segs_WLATCH //open the ting so stuff can go 
    PORTB=Value;
    Segs_ML
    Segs_WLATCH //lacting - close it 



}
void Segs_Clear(void)
{
    for(unsigned int i=0; i<8;i++)
    {
        Segs_Custom(i, 0b10000000);
    }
}
// void Segs_8H (unsigned char, unsigned char)
// {

// }
/*




*/