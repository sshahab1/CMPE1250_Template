/********************************************************************/
// HC12 Program:  ICA09-SCI-Strings
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Saamia
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
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
unsigned char ch;
// unsigned int i;
// unsigned int sum;

/********************************************************************/
// Local Prototypes
/********************************************************************/

char GenerateVowels();
char GenerateVowelsUPPER();
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
  char display[80];
  char str[21]; // array to hold 20 characters plus '\0'
  char array[21];
  int i;
  int sum = 0;

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

    ///////PART A //////////////////////////////////////////////////////////////////

    // generate 20 random vowels and store them in str
    for (i = 0; i < 20; i++)
    {
      char vowels = GenerateVowels();
      if (SWL_Pushed(SWL_CTR) > 0)
      {
        vowels = toupper(vowels);
      }
      SWL_ON(SWL_RED);
      str[i] = vowels;
      
      sum += (int)vowels;
    } 
    str[20] = '\0'; // null-terminate the string
    
    sci0_txStr("\x1b[32m \x1b[1;5H Saamia Shahab"); //green
    
    sci0_txStr("\x1b[35m \x1b[6;1H  vowels: ");

    sprintf( "\x1b[35m \x1b[6;1H vowels:", str); //Magenta
 
    sci0_txStr(str);

    sprintf(array, "\x1b[31m \x1b[7;1H  ASCII: %d ", sum); //red

    //transmit the string
    sci0_txStr(array);
    
    //sci0_txStr("\x1b[35m Hello World !! ");

    sum=0;

    //sci0_txStr(display);

    // SWL_OFF(SWL_RED);
   Delay(250);

  }
}
/********************************************************************/
// Functions
/********************************************************************/
char GenerateVowels()
{
  char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
  return vowels[rand() % 5];
}

char GenerateVowelsUPPER()
{
  char vowels[5] = {'A', 'E', 'I', 'O', 'U'};
  return vowels[rand() % 5];
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
