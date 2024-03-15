#include <hidef.h>  
#include "derivative.h" 
#include "sci.h"

int GetRandom (int iLow, int iHighEx)
{
    return iLow + rand() % (iHighEx - iLow);
}