#ifndef INTEGER_VECTOR_H_
#define INTEGER_VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INTEGER_VECTOR_DEBUG_ON

#ifndef INTEGER_VECTOR_INITIAL_CAPACITY
#define INTEGER_VECTOR_INITIAL_CAPACITY 4
#endif

#ifndef INTEGER_VECTOR_RESIZE_FACTOR
#define INTEGER_VECTOR_RESIZE_FACTOR 2
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

typedef struct Integer_Vector{
  int *initialInteger;
  int currentSize;
  int currentCapacity;
}
Integer_Vector;

bool initialize_integer_vector(Integer_Vector *const);
bool append_integer_to_vector(const int, Integer_Vector *const);
void free_integer_vector(Integer_Vector *const);

#endif