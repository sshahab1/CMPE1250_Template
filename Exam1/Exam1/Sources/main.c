/********************************************************************/
// HC12 Program:  The exam part a is turning on all leds then 
//toggling red using delay then turn on green 
//if two switches pressed otherwise turn on yellow if green is off
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia Shahab
// Details:       Exam 1
// Date:          Feb 16 2024
// Revision History : 
/*working on part a
working on part b fixed part b
working on part c 

*/

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
//#define ring
/********************************************************************/
// Local Prototypes
/********************************************************************/
void DelayFunctionRED_ON(void);
void DelayFunctionRED_OFF(void);
int Switches(void);
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long j = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  { 


     //PART A
    #ifdef ring
     SWL_ON(SWL_RED);
     SWL_ON(SWL_GREEN);
     SWL_ON(SWL_YELLOW);
    #endif

  
      //PART B
    
      SWL_OFF(SWL_RED);
      DelayFunctionRED_OFF();
      SWL_ON(SWL_RED);
      DelayFunctionRED_ON();


      //PART C
      int count = Switches();
      
      if(count == 2) //if any 2 switches are pressed
      {
        SWL_ON(SWL_GREEN); //turn on green led and off all other leds
        SWL_OFF(SWL_YELLOW);
      }
      else{ //otherwise turn on yellow if green is  not on
        SWL_ON(SWL_YELLOW);
        SWL_OFF(SWL_GREEN);
      }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int Switches(void) //creating a funtion that counts up 
{
  int i = 0;
  if (SWL_Pushed(SWL_LEFT) > 0) //if left is pressed count ++ 
  {
    i++;
  }
  if (SWL_Pushed(SWL_RIGHT) > 0)  //if right is pressed count ++ 
  {
    i++;
  }
  if (SWL_Pushed(SWL_UP) > 0)  //if up is pressed count ++ 
  {
    i++;
  }
  if (SWL_Pushed(SWL_DOWN) > 0)  //if down is pressed count ++ 
  {
    i++;
  }
  if (SWL_Pushed(SWL_CTR) > 0)  //if center is pressed count ++ 
  {
    i++;
  }

  return i; //return the value of i 
}
//using a delay function for on led
void DelayFunctionRED_ON(void)
{
  //calculated the numbers using ratio 
  for(j=0;j<2556;j++) //delay of 15ms
      {

      }
}
//using a delay function for on led
void DelayFunctionRED_OFF(void)
{
  for(j=0;j<852;j++) //delay of 5ms
      {

      }
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
