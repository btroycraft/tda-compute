#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vertex_vector.h"

static bool resize_vertex_vector(Vertex_Vector *const);


bool initialize_vertex_vector(Vertex_Vector *const vertexVectorToInitialize)
{
  
  const Vertex *const initialVertex = (Vertex *) malloc(VERTEX_VECTOR_INITIAL_CAPACITY * sizeof(Vertex));
  
  vertexVectorToInitialize->initialVertex = initialVertex;
  vertexVectorToInitialize->currentSize = 0;
  
  if(initialVertex == NULL){
    #ifdef VERTEX_VECTOR_DEBUG_ON
      printf("Vertex vector allocation failure.\n");
    #endif
    
    vertexVectorToInitialize->currentCapacity = 0;
    
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  vertexVectorToInitialize->currentCapacity = VERTEX_VECTOR_INITIAL_CAPACITY;
  
  return !VECTOR_ALLOCATION_FAILURE;
}

bool append_vertex_to_vector(const int vertexToAppend, Vertex_Vector *const destinationVertexVector)
{
  
  if(destinationVertexVector->currentSize == destinationVertexVector->currentCapacity){
    if(resize_vertex_vector(destinationVertexVector) == VECTOR_ALLOCATION_FAILURE){
      return VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  destinationVertexVector->initialVertex[destinationVertexVector->currentSize] = vertexToAppend;
  ++destinationVertexVector->currentSize;
  
  return !VECTOR_ALLOCATION_FAILURE;
}

void free_vertex_vector(Vertex_Vector *const vertexVectorToFree)
{
  
  free(vertexVectorToFree->initialVertex);
  vertexVectorToFree->initialVertex = NULL;
}


static bool resize_vertex_vector(Vertex_Vector *const vertexVectorToResize)
{
  
  const unsigned int newCapacity = (const unsigned int) (VERTEX_VECTOR_RESIZE_FACTOR * vertexVectorToResize->currentCapacity);
  
  const Vertex *const initialVertex = (const Vertex *const) realloc(vertexVectorToResize->initialVertex, newCapacity * sizeof(Vertex));
  
  #ifdef VERTEX_VECTOR_DEBUG_ON
    printf("Vertex vector resized from %d to %d.\n", vertexVectorToResize->currentCapacity, newCapacity);
    if(initialVertex == NULL){
      printf("Vertex vector reallocation failure.\n");
    }
  #endif
  
  if(initialVertex == NULL){
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  vertexVectorToResize->initialVertex = initialVertex;
  vertexVectorToResize->currentCapacity = newCapacity;
  
  return !VECTOR_ALLOCATION_FAILURE;
}
