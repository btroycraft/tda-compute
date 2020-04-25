#ifndef SIMPLICIAL_COMPLEX_H_
#define SIMPLICIAL_COMPLEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simplex_vector.h"
#include "integer_vector.h"

#ifndef SIMPLEX_GENERATION_SUCCESS
#define SIMPLEX_GENERATION_SUCCESS false
#endif

#define BUILD_FUNCTION_GENERATE_SIMPLICIAL_COMPLEX(FILTRATION_FUNCTION, )\
\
Simplicial_Complex *generate_simplicial_complex_using_FILTRATION_FUNCTION(){\



typedef Simplicial_Complex struct{
  Simplex_Vector *initialSimplexSet;
  int maximumSimplexDimension;
};
Simplicial_Complex;

Simplicial_Complex *generate_simplicial_complex(double (*const)(int *, int, void *), void *const, const int, const int, const double);
#endif
