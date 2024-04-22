/********************************************************************/
// HC12 Program:  Lab01 - Labs
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:      Lab s a calculator for the binary
// Date:          April 17
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
#include "segs.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
unsigned int DecimalToBCD(unsigned int decimal);
void DisplayBCD(unsigned int bcd);
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter = 0;
// unsigned int loopCount = 0;
unsigned int i = 0;
// unsigned int currentStateUp=0;
// unsigned int currentStateDown=0;
unsigned int oldStateUp = 0;
unsigned int oldStateDown = 0;

unsigned int pressedUp = 0;
unsigned int pressedDown = 0;
int array[20];
unsigned int loopCount = 0;

unsigned int value = 0;
unsigned int digit_position = 0; 
 unsigned int hexValue =0;
//unsigned int multiplier=0; 
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  int count = 0;
  int j;
  
  // Initialize the processor, device, and peripherals
  // main entry point
  _DISABLE_COP();
  EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();
  RTI_Init();
  sci0_Init();
  Clock_Set20MHZ();
  Segs_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
      DisplayBCD(value);
      //Segs_16DDP(value,1);
        //check if the left button is pressed to change the current digit position
        if (SWL_Pushed(SWL_LEFT)) {
            digit_position = (digit_position + 1) % 4; //cycle through the four digit positions
            
        }
        
         if (SWL_Pushed(SWL_RIGHT)) {
            digit_position = (digit_position - 1) % 4; //cycle through the four digit positions
              //Segs_Custom(digit_position, 0b00000000);
        }
        //Segs_Custom(digit_position, 0b00000000);
        //check if the up button is pressed to increment the digit at the current position
        if (SWL_Pushed(SWL_UP)) {
            unsigned int multiplier = 1;
            //calculate the multiplier to isolate the current digit position
            for (i = 0; i < digit_position; i++) {
                multiplier *= 10;
            }
            //increment the digit at the current position
            value += multiplier;
            if (value > 9999) {
                value = 0; //wrap around if the value exceeds 9999
            }
        }
      //Segs_Normal(digit_position, value, Segs_DP_ON);
      //hexValue = DecimalToBCD(value);
      Segs_16H(value, 1);
      //hexValue = DecimalToBCD(value);
      //Segs_Normal(digit_position, value, Segs_DP_ON);
      // Delay for debouncing and to adjust the refresh rate
      Delay(100);
    // Delay(100);
    // Segs_16DDP(count, i);
    // {
    //   if (SWL_Pushed(SWL_UP))
    //   {
    //     if (++count > 9)
    //     {
    //       count = 0;
    //     }

    //     // for( j = 0; j < 4;j++)
    //     // {
    //     //     array[j]=count;
    //     // }
    //     // oldStateUp = curStateUp;
    //   }
    // }
    // if (SWL_Pushed(SWL_RIGHT))
    // {
    //   if (loopCount % 4 == 0)
    //   {

    //     if (i < 4)
    //     {
    //       Segs_ClearDigit(i - 1);
    //       Segs_Custom(i, 0b00000000);
    //       i++;
    //     }
    //     else
    //     {
    //       Segs_ClearLine(Segs_LineTop);
    //       i = 0;
    //     }
    //   }
    // }

  }
}
/********************************************************************/
// Functions
/********************************************************************/
unsigned int DecimalToBCD(unsigned int decimal) {
    unsigned int bcd = 0;
    unsigned int remainder, i = 1;

    while (decimal != 0) {
        remainder = decimal % 10;
        bcd += remainder * i;
        decimal /= 10;
        i *= 16;
    }

    return bcd;
}
void DisplayBCD(unsigned int bcd) {
    Segs_16DDP(bcd, 0);
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
