#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "simplex_vector.h"

static bool resize_simplex_vector(Simplex_Vector *const);


bool initialize_simplex_vector(Simplex_Vector *const simplexVectorToInitialize)
{
  
  const Simplex *const initialSimplex = (Simplex *) malloc(SIMPLEX_VECTOR_INITIAL_CAPACITY * (sizeof(Simplex) + simplexVectorToInitialize->simplexDimension * sizeof(Vertex)));
  
  simplexVectorToInitialize->initialSimplex = initialSimplex;
  simplexVectorToInitialize->currentSize = 0;
  
  if(initialSimplex == NULL){
    #ifdef SIMPLEX_VECTOR_DEBUG_ON
      printf("Simplex vector allocation failure.\n");
    #endif
    
    simplexVectorToInitialize->currentCapacity = 0;
    
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  simplexVectorToInitialize->currentCapacity = SIMPLEX_VECTOR_INITIAL_CAPACITY;
  
  return !VECTOR_ALLOCATION_FAILURE;
}

bool append_simplex_to_vector(const Simplex *const simplexToAppend, Simplex_Vector *const destinationSimplexVector)
{
  
  if(destinationSimplexVector->currentSize >= destinationSimplexVector->currentCapacity){
    if(resize_simplex_vector(destinationSimplexVector) == VECTOR_ALLOCATION_FAILURE){
      return VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  Simplex *const workingSimplex = (Simplex *) ((Vertex *) workingSimplex + destinationSimplexVector->currentSize*destinationSimplexVector->simplexDimension) + destinationSimplexVector->currentSize;
  
  memcpy(workingSimplex, simplexToAppend, sizeof(Simplex) + destinationSimplexVector->simplexDimension * sizeof(int));
  
  ++destinationSimplexVector->currentSize;
  
  return !VECTOR_ALLOCATION_FAILURE;
}

void free_simplex_vector(Simplex_Vector *const simplexVectorToFree)
{
  
  free(simplexVectorToFree->initialSimplex);
  simplexVectorToFree->initialSimplex = NULL;
}


static bool resize_simplex_vector(Simplex_Vector *const simplexVectorToResize)
{
  
  const int newCapacity = (int) (SIMPLEX_VECTOR_RESIZE_FACTOR * simplexVectorToResize->currentCapacity);
  
  const Simplex *const initialSimplex = realloc(simplexVectorToResize->initialSimplex, newCapacity * (sizeof(Simplex) + simplexVectorToResize->simplexDimension * sizeof(int)));
  
  #ifdef SIMPLEX_VECTOR_DEBUG_ON
    printf("Simplex vector resized from %d to %d.\n", simplexVectorToResize->currentCapacity, newCapacity);
    if(initialSimplex == NULL){
      printf("Simplex vector reallocation failure.\n");
    }
  #endif
  
  if(initialSimplex == NULL){
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  simplexVectorToResize->initialSimplex = initialSimplex;
  simplexVectorToResize->currentCapacity = newCapacity;
  
  return !VECTOR_ALLOCATION_FAILURE;
}
