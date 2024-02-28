/////////////////////////////////////////////////////////////////////////////
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Saamia Shahab
// Details:       Configures PLL to bring bus to other rates
// Date:          *unknown*
// Revision History :
//  Dec 07 2020 - Modified Documentation
//  May 12 2021 - Added 24MHz function, for CMPE1250, CMPE2250
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Library Prototypes
/////////////////////////////////////////////////////////////////////////////

// bring the bus clock to 20MHz
void PLL_To20MHz (void);
// bring the bus clock to 24MHz
void PLL_To24MHz (void);

// bring the bus clock to 40MHz
void PLL_To40MHz (void);