//RTI Module Library
//File: rti.h (header file)
//Processor: MC9S12XDP512
//Crystal: 16 MHz
//by Saamia Shahab
//March 2024



//This has to be declared as a global variable in rti.c
extern volatile unsigned long rtiMasterCount;

/// @brief Enables RTI Moule
/// @param  
void RTI_Init(void);

/// @brief Enables RTI Module with callback to be used in main
/// @param function 
/*
We will implemente this function later once we cover 
function pointers
*/
//void RTI_InitCallback(void(*function)(void));

/// @brief Blocking delay to be used  once the RTI MOdule is enabled
/// @param timeout 
void RTI_Delay_ms(unsigned int ms);

void Delay(unsigned long ms);