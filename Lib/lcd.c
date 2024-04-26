
// macros only apply to this .c library
#include <hidef.h>
#include "derivative.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "rti.h" // for the delays during initialization
// note the LCD is read write

// PORT H : used to send and receive data
// PORT K : used for LCD control signals

/*
Port K uses three pins for control signals:
• 0 -> E (E for enable, NOTE: ACTIVE HIGH, weird, this signal must be low when idle)
• 1 -> R/*W (Reading from LCD == 1, Writing to LCD == 0)
• 2 -> A (Address, AKA RS, determines if data is a command or display data)
*/
// #define PORTH = PTH;
// set r/w to high for INPUTS

//  the character location in the display, also known as DDRAM)

#define lcd_RWUp \
    DDRH = 0;    \
    PORTK |= 2;

// set r/w to low for OUTPUTS
#define lcd_RWDown \
    DDRH = 0XFF;   \
    PORTK &= (~2);

#define lcd_EUp PORTK |= 1;
#define lcd_EDown PORTK &= (~1);
#define lcd_RSUp PORTK |= 4;
#define lcd_RSDown PORTK &= (~4);

// #define lcd_MicroDelay \
//     {                  \
//         char __x = 1;  \
//         while (--__x)  \
//             ;          \
//     }

void lcd_Init(void)
{
    // Clear Port H to then set it as WRITE using the last 3 bits
    // Set PORTH to a known condition to further init other functions
    PTH = 0b00000000;

    // Set the last 3 bits of port H as WRITE
    DDRH = 0b11111111;

    // We want to prevent the chip being addressed immediately, so
    // we set RS (register select, low for Control high for data), R/W (High for read, Low for write) and EN(to enable the chip) to low
    PORTK &= 0b11111000;
    // We are only using 3 of the 8 bits in PORTK, so we can just OR
    // the 3 bits we need with '1' to make them OUTPUTS
    DDRK |= 0b00000111;

    // we need a delay for to make sure the power supply reaches 4.5V to power up the LCD
    Delay(50);

    // Send a function control byte 4 times  in a row

    // Attempt #1, start strobing control lines

    PTH = 0b00111000;
    // 0b00(function_commands)(data_8bit)(lines)(font)(don'tcare)(don'tcare)

    PORTK |= 0b0000001; // write a CONTROL byte

    PORTK &= 0b11111000; // resting state
    // 0b11111(RS, low for control)(RW, low for write)(EN, low for disables)
    Delay(10); // do double the delaye required just to be safe

    // Attempt #2 - strobe the control lines again, then wait

    PORTK |= 0b00000001; // now only the enable is high to write the control
    PORTK &= 0b11111000; // this is the previous resting state, with enable low

    Delay(1); // we need a 100 us delay but to be safe lets do 1 ms (1000ms)

    // Attempt #3 - for this strobing we don't need a delay
    // BUT the micro is faster than the LCD so we should put one just in case

    PORTK |= 0b0000001;  // enable is high to write a control
    PORTK &= 0b11111000; // once again, return to resting state

    Delay(1); // the notes used 100us we will use 1000us

    // ATTEMPT # 4
    // now we use use the LCD_Busy to do it again
    lcd_Ins(0b00111000); // same as what we did above, but we make it busy
    lcd_Ins(0b00001110); // displays the controls
    // 0b0000(Display control commands)(Display high for ON)(Cursor, high for ON)(Blink, low for OFF)
    lcd_Ins(0b00000001); // Clear the display

    lcd_Ins(0b00000110); // controlling the modes
    // 0b00000(entry mode commands)(increment to the left)(no display shift)
}

// same as LCD_Ctrl in long coursepack

/// @brief this method is responsible for sending 8 bit
/// control bytes to the register, once the 'Busy' flag is cleared,
/// using the using RS HIGH for control, R/W LOW for WRITE, and Enable strobed HIGH then LOW.
/// @param cCommand
void lcd_Ins(unsigned char cCommand)
{
    while (lcd_Busy() != 0)
    {
        // do nothing, wait for it to complete
    }

    PTH = cCommand;
    PORTK |= 0b00000001; // RS low, RW low, EN high to write the control
    PORTK &= 0b11111000; // resting state

    // lcd_RWDown     // WRITING
    //     lcd_RSDown // COMMAND

    //         PTH = val; // present data on port

    // lcd_EUp
    //     lcd_EDown // latch
}

unsigned char lcd_Busy(void)
{
    unsigned char cBusy;

    DDRH = 0b00000000; // data bus as inputs for read

    PORTK |= 0b00000011; // enable and RW high

    PORTK &= 0b11111000; // resting state

    cBusy = PTH & 0b10000000; // the 'Busy' flag is the MSB of the PTH register, so set it to high,AKA active

    DDRH = 0b11111111; // data bus is returned to the outputs to prepare for the next write

    return cBusy;
}

// THIS IS JUST lcd_DATA, write ONE CHARACTER to the LCD
void lcd_Char(unsigned char cDisplay)
{
    while (lcd_Busy() != 0)
    {
        // do nothing, wait for it to complete
    }

    PTH = cDisplay;
    PORTK |= 0b00000101; // set the RS to high
    PORTK &= 0b11111000;
}

void lcd_String(char const *straddr)
{
    while (*straddr != 0) // while the string to transmit is NOT null
    {
        lcd_Char(*straddr++); // send in the next character
    }
    // else, we reached the end
}

void lcd_Addr(unsigned char addr)
{
    addr |= 0b10000000; // the raw address converted to a control byte
    lcd_Ins(addr);      // send that converted address to the LCD to display, the 0b1  MSB allows the board to read data from the DDRAM
}

void lcd_Pos(unsigned char cRow, unsigned char cCol)
{
    if (cRow > LCD_WIDTH || cRow < 0 || cCol > LCD_ROW3 || cCol < 0) // out of the bounds of the LCD display
    {
        lcd_Addr(0); // display invalid inputs at the home location 0,0
    }
    else
    {
        switch (cRow)
        {
        case 0: // first row is col 0 to 19
            lcd_Addr(cCol);
            break;
        case 1: // second row is col r2 version of 0 to 19 so 64 to 83
            lcd_Addr(cCol + LCD_ROW1);
            break;
        case 2: // the third row is 20 - 39
            lcd_Addr(cCol + LCD_ROW2);

            break;
        case 3: // row 4 84 to 103
            lcd_Addr(cCol + LCD_ROW3);
            break;
        }
    }
}
void lcd_StringXY(unsigned char ix, unsigned char iy, char const *const straddr)
{

    while (lcd_Busy() != 0)
    {
        // do nothing, wait for it to complete
    }

    lcd_Pos(ix, iy);
    lcd_String(straddr);
}
void lcd_DispControl(unsigned char curon, unsigned char blinkon)
{
    // 0b00001DCB
    // D - diplay
    // C - cursor
    // B - blink

    while (lcd_Busy() != 0)
    {
        // wait for flag to clear
    }

    if (curon && blinkon) // underscore on, bar blinking
        lcd_Ins(0b00001111);
    else if (curon && !blinkon) // underscore on, no bar blinking, no bar
        lcd_Ins(0b00001110);
    else if (!curon && blinkon) // cursor off, bar on, and bar blinking
        lcd_Ins(0b00001101);
    else // nothing on
        lcd_Ins(0b00001100);
}
void lcd_CharGen8(char *cDefs)
{
    unsigned char cLine;

    lcd_Ins(0b01000000); // start of ascii (0)

    for (cLine = 0; cLine < 64; cLine++)
    {
        /* code */
        lcd_Char(*cDefs++);
    }

    lcd_Ins(0b10000000); // back to DDRAM, the home location
}
void lcd_Clear(void)
{
    while (lcd_Busy() != 0) // since this is a stand alone method we need to wait for the busy flag to clear
    {
        // do nothing, wait for the register to be empty
    }

    lcd_Ins(0b00000001);
}
void lcd_Home(void)
{
    while (lcd_Busy() != 0)
    {
        // do nothing, wait for the register to be empty
    }
    lcd_Pos(0, 0);
}

void lcd_ShiftL(char option) // option is always 1
{

    lcd_Ins(0b00010000 | option);
}

void lcd_ShiftR(char option)
{
    lcd_Ins(0b00011000 | option);
}


// #include <hidef.h>  
// #include "derivative.h" 
// #include "lcd.h"
// #define lcd_RWUp DDRH =0; PORTK |=2;
// #define lcd_RWDown PORTK &= (~2); DDRH =0xFF; 
// #define lcd_EUp PORTK |=1;
// #define lcd_EDown PORTK &=(~1);
// #define lcd_RSUp PORTK |=4;
// #define lcd_RSDown PORTK &=(~4);
// //#define lcd_MicroDelay {char __x=1; while(--__x);}

// void lcd_Ins(unsigned char val)
// {
//     lcd_Busy();
//     lcd_RWDown;
//     lcd_RSDown;
//     PTH = val;
//     lcd_EUp;
//     lcd_EDown;
// }
// void lcd_Busy (void)
// {
//     unsigned char inVal =0;
//     lcd_RSDown;
//     lcd_RWDown;

//     do
//     {
//         lcd_EUp;
//         lcd_MicroDelay;
//         inVal = PTH;
//         lcd_EDown;
//     } while (inVal&0x80);
    
// }
// void lcd_Data (unsigned char val)
// {
//    lcd_Busy();
// //    PTH = val;
// //    PORTK_PK1 = 0;
// //    PORTK_PK2 = 1;

// //    lcd_Latch;
//     lcd_RSUp; // Set RS high for data
//     lcd_RWDown; // Set RW low for write
//     PTH = val;
//     lcd_EUp;
//     lcd_EDown;
// }
// void lcd_Init(void)
// {
//     int i;
//     // Set Port H as output
//     DDRH = 0xFF;

//     // Set control lines to initial state
//     PORTK &= ~(0b111); // RS, RW, and E low
//     DDRK |= 0b111; // RS, RW, and E as output

//     // Wait for LCD to power up
//     Delay(50);
    
//     // Send function control byte multiple times
//     for ( i = 0; i < 3; i++) {
//         // Function set: 8-bit data, 2-line display, 5x8 font
//         lcd_Ins(0b00111000);
//         Delay(1); // Delay after each command
//     }

//     // Display control: Display ON, Cursor OFF, Blink OFF
//     lcd_Ins(0b00001110);
//     Delay(1);

//     // Clear display
//     lcd_Ins(0b00000001);
//     Delay(2); // Longer delay after clear command

//     // Entry mode set: Increment cursor, no display shift
//     lcd_Ins(0b00000110);
//     Delay(1);
// }


// void lcd_Ctrl(unsigned char cCommand) {
//     while (lcd_BusyReturns() != 0) {
//         // Wait for LCD to be not busy
//     }
//     PTH = cCommand;
//     PORTK |= 0b00000001;
//     PORTK &= 0b11111000;
// }

// unsigned char lcd_BusyReturns(void) {
//     unsigned char cBusy;
//     DDRH = 0b00000000;
//     PORTK |= 0b00000011;
//     PORTK &= 0b11111000;
//     cBusy = PTH & 0b10000000; // Assuming busy flag is at bit 7
//     return cBusy;
// }

// void lcd_Addr(unsigned char addr) {
//     lcd_Ins(0x80 | addr);
//     // addr |= 0b10000000; // Set the DB7 bit for address mode
//     // lcd_Ctrl(addr);
// }

// void lcd_AddrXY(unsigned char ix, unsigned char iy) {

//     unsigned char Y;
//     unsigned char Z;
//     switch(iy)
//     {
//         case 0:
//             Y = LCD_ROW0; 
//             break;
//         case 1:
//             Y = LCD_ROW1;
//             break;
//         case 2:
//             Y = LCD_ROW2;
//             break;
//         case 3:
//             Y = LCD_ROW3;
//             break;
//     }
//     Z = Y + ix;
//     lcd_Ins(0x80 | Z);

// }
// void lcd_String(char const *straddr) {
//     int i=0;                                                                              
//     while (straddr[i] != '\0') { // Loop until the null terminator is reached
//         lcd_Data(straddr[i]); // Write each character to the LCD and move to the next character
//         i++;
//     }
// }

// void lcd_StringXY(unsigned char ix, unsigned char iy, char const *const straddr) {
//     // Set the cursor position
//     lcd_AddrXY(ix, iy);
//     // Write the string to the LCD starting from the specified position
//     lcd_String(straddr);
// }
// void lcdSmartString(char const * straddr, unsigned int delay)
// {
//       int i=0;
                                                                                       
//     while (straddr[i] != '\0') { // Loop until the null terminator is reached
//         lcd_Data(straddr[i]); // Write each character to the LCD and move to the next character
//         i++;
//     }
//     Delay(20);
// }


