#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Shift an array of bytes to the right by "shift" bits
// Expected "shift" is no more than CHAR_BIT

inline void shift_bits_right_vec_compr_int(void* loc, size_t num, size_t shift){

  size_t shiftComp = CHAR_BIT - shift;

  for(size_t ind = num-1; ind > 0; --ind){

    ((unsigned char*) loc)[ind] = (((unsigned char*) loc)[ind] >> shift) + (((unsigned char*) loc)[ind-1] << shiftComp);
  }

  ((unsigned char*) loc)[0] >>= shift;

  return;
}
