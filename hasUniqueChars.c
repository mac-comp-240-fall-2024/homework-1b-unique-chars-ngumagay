/*
 * hasUniqueChars.c
 *
 * Two helper functions that support UniqueChars function as well as the UniqueChars function.
 *
 * Author: Nathan Gumagay
 */

#include <stdio.h>   // fprintf, printf
#include <stdlib.h>  // exit() defined here
#include <string.h>  // useful string operations
#include <ctype.h>   //useful character operations
#include <stdbool.h> // to define a boolean type and true, false
                     // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"

/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text)
{

  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
}

/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char *inputStr)
{
  char nextChar;
  int i;

  for (i = 0; i < strlen(inputStr); i++)
  {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31) || (nextChar == 127))
    {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}

/*
 * The function takes in a pointer to a char which is a string, then checking each character of the string to
 * see if the string has all it's characters unique.
 * Error conditions: Duplicates, as well as \0,\t,\n all push the function to exit, as well as others in the ascii table that cannot be checked.
 */
bool hasUniqueChars(char *inputStr)
{

  checkInvalid(inputStr);

  int i;

  unsigned long checkBitsA_z = 0;      // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp = 0; // for checking ! though @

  char nextChar;

  unsigned long mask = 0;

  for (i = 0; i < strlen(inputStr); i++)
  {
    nextChar = inputStr[i];
    if (nextChar > 64)
    {
      mask = 1L << nextChar;
      if (checkBitsA_z & mask)
      {
        return false;
      }
      checkBitsA_z |= mask;
    }
    else
    {
      if (nextChar >= 33 && nextChar <= 64)
      {
        mask = 1L << nextChar;
        if (checkBitsexcl_amp & mask)
        {
          return false;
        }
        checkBitsexcl_amp |= mask;
      }
    }
  }

  // if through all the characters, then no duplicates found
  return true;
}
