#ifndef SIMPLEX_VECTOR_H_
#define SIMPLEX_VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIMPLEX_VECTOR_DEBUG_ON

#ifndef SIMPLEX_VECTOR_INITIAL_CAPACITY
#define SIMPLEX_VECTOR_INITIAL_CAPACITY 4
#endif

#ifndef SIMPLEX_VECTOR_RESIZE_FACTOR
#define SIMPLEX_VECTOR_RESIZE_FACTOR 2
#endif

#ifndef VECTOR_ALLOCATION_FAILURE
#define VECTOR_ALLOCATION_FAILURE true
#endif

#ifndef VECTOR_RESIZE_SUCCESS
#define VECTOR_RESIZE_SUCCESS false
#endif

#ifndef VECTOR_INITIALIZATION_SUCCESS
#define VECTOR_INITIALIZATION_SUCCESS false
#endif

#ifndef VECTOR_APPEND_SUCCESS
#define VECTOR_APPEND_SUCCESS false
#endif


typedef struct Simplex{
  int rankLabel;
  double filtrationParameter;
  int initialVertex;
}
Simplex;

typedef struct Simplex_Vector{
  Simplex *initialSimplex;
  int simplexDimension;
  int currentSize;
  int currentCapacity;
}
Simplex_Vector;

bool initialize_simplex_vector(Simplex_Vector *const);
bool append_simplex_to_vector(const Simplex *const, Simplex_Vector *const);
void free_simplex_vector(Simplex_Vector *const);

#endif
