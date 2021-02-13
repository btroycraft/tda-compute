#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Expand vector capacity to occomodate at least "num" new entries

inline uint_fast32_t extract_val_vec_compr(uint_fast32_t *loc, size_t off, size_t width){

  uint_fast32_t v1 = *loc >> off;
  uint_fast32_t v2 = *(loc + 1) << (CHAR_BIT*sizeof(uint_fast32_t) - off);

  return (v1 | v2) & ~(~((uint_fast32_t) 0) << width);
}
