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


Simplex_Vector *generate_simplicial_complex(double (* )(int *, int, void *), void *, int, int, double);
#endif