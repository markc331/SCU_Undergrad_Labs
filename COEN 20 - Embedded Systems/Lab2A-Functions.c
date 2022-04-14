#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "library.h"
#include "graphics.h"

int32_t Bits2Signed(int8_t bits[8])
{
    int32_t x = 0;  // integer we will return to main
    if(bits[7] ==1)
        x -= pow(2, 7); //makes number negative if 7th bit is 1, since signed
    for(int i = 0; i <=6; i++) // transverse entire array
    {
        if(bits[i] == 1 )// checks if bit value = 1
            x += pow(2, i); // adds 2^i to total number
    }

    return x; //returns x to main fuction
}

uint32_t Bits2Unsigned(int8_t bits[8])
{
    uint32_t x = 0;
    for(int i = 0; i <= 7; i++) // transverses entire array
    {
        if(bits[i] == 1) //checks if bit value = 1
        {
            x+= pow(2, i); // adds 2^i to the total number
        }
    }
    return x;
}

void Increment(int8_t bits[8])
{
    for(int i = 0; i <= 7; i++)
    {
        if(bits[i] == 0) // checks if bit is 0
        {
            bits[i] = 1; //makes 0 to 1
            break; // breaks at first instance of 0 because 0+1 = 1 with no carry over
        }
        bits[i] = 0; // makes every 1 a 0 since 1+1 = 2, no way to represent 2 so we do 2%2 = 0
    }
}

void Unsigned2Bits(uint32_t n, int8_t bits[8])
{
    for(int i = 0; i <= 7; i++)
    {
        bits[i] = n%2; //  sees if number has a remained of 1 or not
        n = n/2; // divides by 2
    }
}
