#ifndef SIMPLICIAL_COMPLEX_H_
#define SIMPLICIAL_COMPLEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simplex_vector.h"
#include "integer_vector.h"

#ifndef SIMPLEX_GENERATION_SUCCESS
#define SIMPLEX_GENERATION_SUCCESS true
#endif


Simplex_Vector *generate_simplicial_complex(const double (*filtrationFunction)(int *, int, void *), const void *filtrationFunctionParameters, const int largestVertex, const int maximumSimplexDimension, const double maximumFiltrationParameter);
#endif