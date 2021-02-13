#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Shift an array of bytes by "shift" bits
// Negative "shift" shifts to the left, positive to the right

void shift_bits_vec_c(void* loc, size_t num, int shift){

  if(num == 0 || shift == 0){
    return;
  }

  size_t shiftAbs = (size_t) abs(shift);

  if(shift < 0){
    shift_bits_left_vec_compr_int(loc, num, shiftAbs);
  }
  else{
    shift_bits_right_vec_compr_int(loc, num, shiftAbs);
  }

  return;
}
