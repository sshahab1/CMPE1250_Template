#include <hidef.h>  
#include "derivative.h" 
#include "clock.h"

void Clock_Set8MHZ(void)
{
    
    CLKSEL_PSTP = 1; 
    PLLCTL = 0; //monitor enable

    

}

void Clock_Set20MHZ(void)
{
    SYNR = 4;
    REFDV = 3;

    CLKSEL_PSTP = 1; 
    PLLCTL = 0b11111111; //monitor enable

    while (!CRGFLG_LOCK); //must wait for lock
    CLKSEL_PLLSEL = 1; //now that we are locked, use PLLCLK/2 for bus (20MHz)

}


void Clock_Set24MHZ(void)
{
    SYNR = 8;
    REFDV = 5;

    CLKSEL_PSTP = 1; 
    PLLCTL = 0b11111111; //monitor enable

    while (!CRGFLG_LOCK); //must wait for lock
    CLKSEL_PLLSEL = 1; //now that we are locked, use PLLCLK/2 for bus (20MHz)

}

void Clock_Set40MHZ(void)
{
    SYNR = 4;
    REFDV = 1;

    CLKSEL_PSTP = 1; 
    PLLCTL = 0b11111111; //monitor enable

    while (!CRGFLG_LOCK); //must wait for lock
    CLKSEL_PLLSEL = 1; //now that we are locked, use PLLCLK/2 for bus (20MHz)

}

