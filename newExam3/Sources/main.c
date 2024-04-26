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
#include "segs.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter = 0;
unsigned int loopCount = 0;
unsigned int i = 4;
// unsigned int currentStateUp=0;
// unsigned int currentStateDown=0;
unsigned int oldStateUp= 0;
unsigned int oldStateDown= 0;
unsigned char character;
unsigned int pressedUp = 0;
unsigned int pressedDown = 0;

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
 char display[80];
  char str[21]; // array to hold 20 characters plus '\0'
  char array[21];
  int i=4;
  int j;
  int random =0;
  int sum = 0;
  int me = 5667;
  char storeChar[31];
  char demostr[80];                    // char buffer to hold the string

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
  lcd_Init();
  sci0_txStr("\x1b[32m \x1b[1;1H Saamia Shahab"); // green
  //lcd_StringXY( 2, 2, "Saamia Shahab");
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
      Delay(200);
    //   Segs_ClearLine(Segs_LineTop);
    //   Segs_ClearLine(Segs_LineBottom);
    //  SWL_OFF(SWL_GREEN);
   
      random = rand() % 9999 + 0000;
      //random = 5467;
      Segs_16D(random, 0);
    //    SWL_ON(SWL_GREEN);
      if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
    {
          character = SCI0DRL;

          sum += character;
          j+=character;
        
          if(i<8)
          {
            storeChar[i] = character;
            if(i==8)
            {
              Segs_ClearLine(Segs_LineBottom);
            }
            Segs_Normal(i, character, Segs_DP_OFF);
            i++;
          }
        
        if(random == character)
        {
          SWL_ON(SWL_GREEN);
          SWL_OFF(SWL_RED);
        }
        else{
          SWL_ON(SWL_RED);
           SWL_OFF(SWL_GREEN);
        }
  

    }
    
          
    
  
   // lcd_StringXY(2,1, storeChar);
    //sci0_txStr("\x1b[3;3H ");
    sci0_txByte(character);

 

if(SWL_Pushed(SWL_RIGHT))
{
    lcd_ShiftL(1);
   lcd_StringXY( 1, 2, "Shahab");
   
}
if(SWL_Pushed(SWL_LEFT))
{
    lcd_ShiftL(1);
   lcd_StringXY( 1, 2, "Shahab");
   
}
if(SWL_Pushed(SWL_CTR))
{
  lcd_Home();
}

    //Segs_16D(sum, 0);
    //Segs_16H(sum, 1);

  
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
