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
unsigned int i;
/********************************************************************/
// Local Prototypes
/********************************************************************/

char GenerateVowels();
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
    // char str[21]; // Array to hold 20 characters plus '\0'
    // int i;
    
    // // Generate 20 random vowels and store them in str
    // for (i = 0; i < 20; i++)
    // {
    //   char vowels = GenerateVowels();
    //   if (SWL_Pushed(SWL_CTR))
    //   {
    //     vowels = toupper(vowels);
    //   }
    //   SWL_ON(SWL_RED);
    //   str[i] = vowels;
    // }
    // str[20] = '\0'; // Null-terminate the string
  
    // // Transmit the string
    // sci0_txStr(str);
    // // SWL_OFF(SWL_RED);
    // Delay(250);

///////PART B //////////////////////////////////////////////////////////
char str[25]; // Array to hold 20 characters plus '\0' and space for sum
    int i;
    int sum = 0;

    // Generate 20 random vowels and store them in str
    for (i = 0; i < 20; i++) {
        char vowel = GenerateVowels();
        str[i] = vowel;
        sum += (int)vowel; // Add ASCII value to sum
    }
    
    // Append sum as a four-digit padded number with leading zeroes
    sprintf(str + 20, " %04d ", sum);

    // Transmit the string
    sci0_txStr(str);




    //   string randomVowels[]; // Output buffer

    //   Delay(250);
    //   string outputString;

    //   ch = (rand() % 26) + 'a';

    //   for (size_t i = 0; i < 20; i++)
    //   {
    //     if (less than 20)
    //     {
    //       if ('A E I O U')

    //         output[i] = ch;
    //     }
    //   }

    //   char vowels[5] =
    //       {
    //           'A', 'E', 'I', 'O', 'U'};
    //   ch = (rand() % 5) + vowels;

    //   for (i = 0; i < 20; i++)
    //   {
    //     sprintf(ch, "iterate # %d",i);
    //     sci0_txStr (&ch);
    //   }

    //   for (i = 0; i < 20; i++)
    //   {
    //     ch = (rand() % 26) + 'a';

    //     if (SWL_Pushed(SWL_CTR)) // if the button is pushed, transmit uppercase vowels
    //       ch = toupper(ch);

    //     // transmit only if the character is a vowel
    //     if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
    //     {
    //       if (SCI0SR1_TDRE)
    //       {
    //         SCI0DRL = ch;
    //         SWL_ON(SWL_RED);
    //       }
    //     }
    //     output[i] = ch; // store transmitted character in output buffer
    //   }
    //   Delay(250);
    // }
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
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
