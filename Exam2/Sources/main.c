/********************************************************************/
// HC12 Program: Exam2
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:       
// Date:         April  2024
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

// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
unsigned char character;
unsigned char ch;
// unsigned int i;
// unsigned int sum;
unsigned int count;
/********************************************************************/
// Local Prototypes
/********************************************************************/


/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
int i;
 char str[79];
 char array[50];

  // Any main local variables must be declared here

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


  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {

    Delay(10);
     SWL_TOG(SWL_RED);

  for(i=0;i<79;i++)
  {
    char dot = '.';
    str[i] = dot;
   
   

   if(SWL_Pushed(SWL_UP))
  {
    char exclamation = '!';
    str[i]= exclamation;
  }
  if(SWL_Pushed(SWL_DOWN))
  {
     char question = '?';
    str[i]= question;
  }
  if(SWL_Pushed(SWL_CTR))
  {
     char dot = '.';
    str[i] = dot;
  }
    count++;
   SWL_TOG(SWL_GREEN);

 

  }


    //sci0_txByte('.');

  str[79] = '\0'; 
 
 if (SCI0SR1 & SCI0SR1_RDRF_MASK) // check if a character has been received
    {
        ch=SCI0DRL;
        if(ch=='R'||ch=='r')
        {
             sprintf(array, "\x1b[1;1H \x1b[31m Count: %05d ", count);
        }
         else if(ch=='G'||ch=='g')
        {
             sprintf(array, "\x1b[1;1H \x1b[32m Count: %05d ", count);
        }
         else if(ch=='B'||ch=='b')
        {
             sprintf(array, "\x1b[1;1H \x1b[34m Count: %05d ", count);
        }

    }

    
 //sprintf(array, "\x1b[1;1H Count: %05d ", count);
 sci0_txStr(array);

  sci0_txStr("\x1b[3;1H     ");

 sci0_txStr(str);
     
  }
}
/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
