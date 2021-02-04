#include <stdint.h>
#include <stdbool.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

inline const size_t tern_size_t_(const bool cond, const size_t v1, const size_t v2){

  return ((size_t) cond)*v1 + ((size_t) !cond)*v2;
}
