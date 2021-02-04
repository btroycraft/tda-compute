#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Shift an array of bytes to the left by "shift" bits
// Any "shift" equal to num*CHAR_BIT or greater will zero the array

inline void shift_bits_left_vec_compr_int(void* loc, size_t num, size_t shift){

  // Break shift into byte and bit parts

  size_t shiftBytes = shift / CHAR_BIT;
  size_t shiftBits = shift - CHAR_BIT*shiftBytes;
  size_t shiftBitsComp = CHAR_BIT - shiftBits;

  size_t end = tern_size_t_vec_compr_int(shiftBytes < num, num - shiftBytes - 1, 0);

  // Perform the shift

  for(size_t ind = 0; ind < end; ++ind){

    ((unsigned char*) loc)[ind] = (((unsigned char*) loc)[ind] << shiftBits) + (((unsigned char*) loc)[ind+1] >> shiftBitsComp);
  }

  if(shiftBytes < num){
    ((unsigned char*) loc)[end] = ((unsigned char*) loc)[num] << shiftBits;
    memset((unsigned char*) loc + end, 0, shiftBytes);
  }
  else{

  }

  return;
}
