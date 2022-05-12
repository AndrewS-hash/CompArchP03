
/*---------------------------------------------------------------------------*\
 Factorial   : Simple factorial program
 Composed By : Sim, Mong Tee
 Dated		 : 23rd March 2022
 Copyright   : (C) 2022, Mong
 ==============================================================================
 History
 =======

 Author     Date        Description
 ------ ---------- ------------------------------------------------------------
  Mong      03232022    Initial 
  Schmidt   04012022    Added 2^P
 
\*---------------------------------------------------------------------------*/

#include <stdint.h>
#include "stdlib.h"
#define printf R_printf 

//-----------------------------------------------------------------------------
// function prototype
//-----------------------------------------------------------------------------
uint32_t 	Iterative_Factorial     (uint32_t  num);
uint32_t 	RFactorial_Value        (uint32_t  num);
uint32_t    Iterative_Power         (uint32_t  num);
uint32_t    RPower_Value            (uint32_t  num);

//-----------------------------------------------------------------------------
// Performs a math operation num! in an iterative method
//-----------------------------------------------------------------------------
uint32_t Iterative_Factorial(uint32_t num)
{
    uint32_t x;
    uint32_t retVal = 1;
    for (x = num; x > 1; x--)
    {
        retVal *= x;
    }

    return retVal;
}

//-----------------------------------------------------------------------------
// Performs a math operation num! in a recursive method pass by value
//-----------------------------------------------------------------------------
uint32_t RFactorial_Value(uint32_t num)
{
    if (num > 1)
	{
		return num * RFactorial_Value(num - 1);
	}
	
	return 1;
}

//-----------------------------------------------------------------------------
// Performs a math operation 2^num in a iterative method
//-----------------------------------------------------------------------------
uint32_t    Iterative_Power(uint32_t  num)
{
    uint32_t x;
    uint32_t retVal = 2;
    for (x = num; x > 1; x--)
    {
        retVal *= 2;
    }

    return retVal;;
}

//-----------------------------------------------------------------------------
// Performs a math operation 2^num in a recursive method pass by value
//-----------------------------------------------------------------------------
uint32_t    RPower_Value(uint32_t  num)
{
    if (num > 1)
    {
        return 2 * RPower_Value(num - 1);
    }

    return 2;
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------
int main()
{
    uint32_t fVal   = 0;
    uint32_t num    = 0;

    // Iterative Method
    //
    fVal    = 0;
    num     = 6;
    fVal = Iterative_Factorial(num);
    printf("Iterative Factorial of %d! = %d\n", num, fVal);

    // Pass by value
    //
    fVal    = 0;
    num     = 6;
    fVal = RFactorial_Value(num);
    printf("Recursive Factorial of %d! = %d\n", num, fVal);

    fVal = 0;
    num = 6;
    fVal = Iterative_Power(num);
    printf("Iterative Power of 2^%d = %d\n", num, fVal);

    fVal = 0;
    num = 6;
    fVal = RPower_Value(num);
    printf("Recursive Power of 2^%d = %d\n", num, fVal);

    return 0;
}
