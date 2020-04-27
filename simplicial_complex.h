#ifndef SIMPLICIAL_COMPLEX_H_
#define SIMPLICIAL_COMPLEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

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
  unsigned int dim;
  Simp_Vec init;
};
Simp_Comp;

Simplicial_Complex *generate_simplicial_complex(double (*const)(int *, int, void *), void *const, const int, const int, const double);
#endif
