#ifndef SIMPLICIAL_COMPLEX_H_
#define SIMPLICIAL_COMPLEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "vector.h"
#include "simp.h"

#ifndef MAIN_MEMORY_SIZE
#define MAIN_MEMORY_SIZE 4
#endif
#ifndef L3_CACHE_SIZE
#define L3_CACHE_SIZE
#endif
#ifndef L2_CACHE_SIZE
#define L2_CACHE_SIZE 4
#endif
#ifndef L1_CACHE_SIZE
#define L1_CACHE_SIZE 4
#endif

typedef Simp_Comp struct{
  size_t dim;
  Simp_Vec init;
};
Simp_Comp;

typedef Simp

#define DECLARE_SIMP_COMP_TYPE_AND_FUNCS()\
  \
  typedef COMP_TYPE struct{\
  DIM_TYPE dim;\
  SIMP_VEC_TYPE init;\
};\
Simp_Comp;

COMP_TYPE *gen_simp_comp(double (*const)(int *, int, void *), void *const, const int, const int, const double);
#endif
