#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Shift an array of bytes to the left by "shift" bits
// Expected shift values at most CHAR_BIT*sizeof(uint_fast32_t)

inline void shift_bits_left_vec_compr_int(void* loc, size_t num, size_t shift){

  uint_fast32_t *ptrWord = (uint_fast32_t *) loc;
  unsigned char *ptrByteLast = (unsigned char *) loc + num - sizeof(uint_fast32_t);

  uint_fast32_t *ptrWord;
  {
    size_t shiftComp = CHAR_BIT*sizeof(uint_fast32_t) - shift;
    for(ptrWord = (uint_fast32_t *) loc; (unsigned char *) ptrWord < ptrByteLast, ++ptrWord){
      *ptrWord = (*ptrWord << shift) + (*(ptrWord+1) >> shiftComp);
    }
  uint_fast32_t lastWord;
  {
    lastWord = 0;

    unsigned char *ptrIn, *ptrOut;
    for(ptr = ; ind )

  } = 0;


  // Perform the shift

  if(shiftWords*sizeof(uint_fast8_t) + shiftBytes < num){

    {
    for(size_t ind = 0; ind < )
      ((unsigned char*) loc)[ind] =
    }
    shift

    for(size_t ind = 0;)

    for(size_t ind = 0; ind < num - shiftBytes - 1; ++ind){

      ((unsigned char*) loc)[ind] = (((unsigned char*) loc)[ind + shiftBytes] << shiftBits) + (((unsigned char*) loc)[ind + shiftBytes + 1] >> shiftBitsComp);
    }

    ((unsigned char*) loc)[num - shiftBytes - 1] = ((unsigned char*) loc)[num-1] << shiftBits;
  }

  if(shiftBytes > 0){
    memset((unsigned char*) loc + num - shiftBytes, 0, shiftBytes);
  }

  return;
}
