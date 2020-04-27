#ifndef VERTEX_VECTOR_H_
#define VERTEX_VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VERTEX_VECTOR_DEBUG_ON

#ifndef VERTEX_VECTOR_INITIAL_CAPACITY
#define VERTEX_VECTOR_INITIAL_CAPACITY 4
#endif

#ifndef VERTEX_VECTOR_RESIZE_FACTOR
#define VERTEX_VECTOR_RESIZE_FACTOR 2
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

typedef unsigned int Vertex;

typedef struct Vertex_Vector{
  unsigned int currentSize;
  unsigned int currentCapacity;
  Vertex *initialVertex;
}
Vertex_Vector;

bool initialize_vertex_vector(Vertex_Vector *const);
bool append_vertex_to_vector(const Vertex, Vertex_Vector *const);
void free_vertex_vector(Vertex_Vector *const);

#endif
