#include <hidef.h>  
#include "derivative.h" 
#include "lcd.h"
#define lcd_RWUp DDRH =0; PORTK |=2;
#define lcd_RWDown PORTK &= (~2); DDRH =0xFF; 
#define lcd_EUp PORTK |=1;
#define lcd_EDown PORTK &=(~1);
#define lcd_RSUp PORTK |=4;
#define lcd_RSDown PORTK &=(~4);
//#define lcd_MicroDelay {char __x=1; while(--__x);}

void lcd_Ins(unsigned char val)
{
    lcd_Busy();
    lcd_RWDown;
    lcd_RSDown;
    PTH = val;
    lcd_EUp;
    lcd_EDown;
}
void lcd_Busy (void)
{
    unsigned char inVal =0;
    lcd_RSDown;
    lcd_RWDown;

    do
    {
        lcd_EUp;
        lcd_MicroDelay;
        inVal = PTH;
        lcd_EDown;
    } while (inVal&0x80);
    
}
void lcd_Data (unsigned char val)
{
   lcd_Busy();
    lcd_RSUp; // Set RS high for data
    lcd_RWDown; // Set RW low for write
    PTH = val;
    lcd_EUp;
    lcd_EDown;
}
void lcd_Init(void)
{
    int i;
    // Set Port H as output
    DDRH = 0xFF;

    // Set control lines to initial state
    PORTK &= ~(0b111); // RS, RW, and E low
    DDRK |= 0b111; // RS, RW, and E as output

    // Wait for LCD to power up
    Delay(50);
    
    // Send function control byte multiple times
    for ( i = 0; i < 3; i++) {
        // Function set: 8-bit data, 2-line display, 5x8 font
        lcd_Ins(0b00111000);
        Delay(1); // Delay after each command
    }

    // Display control: Display ON, Cursor OFF, Blink OFF
    lcd_Ins(0b00001110);
    Delay(1);

    // Clear display
    lcd_Ins(0b00000001);
    Delay(2); // Longer delay after clear command

    // Entry mode set: Increment cursor, no display shift
    lcd_Ins(0b00000110);
    Delay(1);
}


void lcd_Ctrl(unsigned char cCommand) {
    while (lcd_BusyReturns() != 0) {
        // Wait for LCD to be not busy
    }
    PTH = cCommand;
    PORTK |= 0b00000001;
    PORTK &= 0b11111000;
}

unsigned char lcd_BusyReturns(void) {
    unsigned char cBusy;
    DDRH = 0b00000000;
    PORTK |= 0b00000011;
    PORTK &= 0b11111000;
    cBusy = PTH & 0b10000000; // Assuming busy flag is at bit 7
    return cBusy;
}

void lcd_Addr(unsigned char addr) {
    addr |= 0b10000000; // Set the DB7 bit for address mode
    lcd_Ctrl(addr);
}

void lcd_AddrXY(unsigned char ix, unsigned char iy) {
    if (ix > 1 || iy > 19) {
        lcd_Addr(0);
    } else {
        unsigned char addr;
        if (ix == 0) {
            addr = iy; // First row is 0-19
        } else {
            addr = iy + 64; // Second row is 64 - 83
        }
        lcd_Addr(addr);
    }
}
void lcd_String(char const *straddr) {
    while (*straddr != '\0') { // Loop until the null terminator is reached
        lcd_Data(*straddr++); // Write each character to the LCD and move to the next character
    }
}

void lcd_StringXY(unsigned char ix, unsigned char iy, char const *const straddr) {
    // Set the cursor position
    lcd_AddrXY(ix, iy);
    // Write the string to the LCD starting from the specified position
    lcd_String(straddr);
}


//////////////////WORKS KIND OF I THNK SO???????????////////////////////////
// void lcd_Addr(unsigned char addr)
// {
//     // Set RS low for command mode
//     lcd_RSDown;
//     // Set RW low for write mode
//     lcd_RWDown;
//     // Set the address on the data bus
//     PTH = addr;
//     // Strobe the enable pin
//     lcd_EUp;
//     lcd_EDown;
// }

// void lcd_AddrXY(unsigned char ix, unsigned char iy)
// {
//     // Calculate the DDRAM address based on the given x and y coordinates
//     unsigned char addr = (iy == 0) ? (0x80 + ix) : (0xC0 + ix);
//     // Set the DDRAM address
//     lcd_Addr(addr);
// }

// void lcd_String(char const *straddr)
// {
//     // Set RS high for data mode
//     lcd_RSUp;
//     // Set RW low for write mode
//     lcd_RWDown;
//     // Write each character of the string to the LCD
//     while (*straddr != '\0')
//     {
//         // Write the current character to the data bus
//         PTH = *straddr;
//         // Strobe the enable pin
//         lcd_EUp;
//         lcd_EDown;
//         // Move to the next character in the string
//         straddr++;
//     }
// }

// void lcd_StringXY(unsigned char ix, unsigned char iy, char const *const straddr)
// {
//     // Set the cursor position
//     lcd_AddrXY(ix, iy);
//     // Write the string to the LCD
//     lcd_String(straddr);
// }























/////////////////OLD NOTESSSS DO NOT WORK/////////////////////
// void lcd_String (char const * straddr)
// {
//     while (*straddr !=0) {      //wach for null terminator
//         lcd_Data(*straddr++); //send next charcter
//     }
// }
// void lcd_Ctrl(unsigned char cCommand)
// {
//     while(lcd_BusyReturns()!=0)
//     {
//         PTH = cCommand;
//         PORTK |= 0b00000001;
//         PORTK &= 0b11111000;
//     }
// }
// unsigned char lcd_BusyReturns(void)
// {
//     unsigned char cBusy;
//     DDRH = 0b00000000;
//     PORTK |= 0b00000011;
//     PORTK &= 0b11111000;
//     cBusy = PTH & 0b10000000;
//     return cBusy;
// }
// void lcd_Addr (unsigned char addr)
// {
//     addr |= 0b10000000;
//     lcd_Ctrl(addr);
// }

// void lcd_AddrXY (unsigned char ix, unsigned char iy)
// {
//     if(ix>3||iy>19)
//     {
//         lcd_Addr(0);
//     }
//     else{
//         switch(ix)
//         {
//             case 0:
//                 lcd_Addr(iy); //first row is 0-19
//                 break;
//             case 1:
//                 lcd_Addr(iy+64); //second row is 64 - 83
//                 break;
//             case 2:
//                 lcd_Addr(iy +20); //third row
//                 break;
//         }
//     }
// }