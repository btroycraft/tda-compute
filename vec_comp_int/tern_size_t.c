#include <stdint.h>
#include <stdbool.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

inline size_t tern_size_t_vec_compr_int(bool cond, size_t v1, size_t v2){

  return ((size_t) cond)*v1 + ((size_t) !cond)*v2;
}
