#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simplex_vector.h"

bool resize_simplex_vector(Simplex_Vector *);


bool initialize_simplex_vector(const Simplex_Vector *simplexVectorToInitialize)
{
  
  const Simplex *initialSimplex = (Simplex *) malloc(SIMPLEX_VECTOR_INITIAL_CAPACITY * (sizeof(Simplex) + simplexVectorToInitialize->simplexDimension * sizeof(int)));
  
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
  
  return VECTOR_INITIALIZATION_SUCCESS;
}

bool append_simplex_to_vector(const Simplex *simplexToAppend, const Simplex_Vector *destinationSimplexVector)
{
  
  if(destinationSimplexVector->currentSize == destinationSimplexVector->currentCapacity){
    if(resize_simplex_vector(destinationSimplexVector) == VECTOR_ALLOCATION_FAILURE){
      return VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  const Simplex *simplexDestination = (Simplex *) ((int *) destinationSimplexVector->initialSimplex + destinationSimplexVector->currentSize*destinationSimplexVector->simplexDimension) + destinationSimplexVector->currentSize;
  
  memcpy(simplexDestination, simplexToAppend, sizeof(Simplex) + destinationSimplexVector->simplexDimension * sizeof(int));
  
  simplexVector->currentSize++;
  
  return VECTOR_APPEND_SUCCESS;
}

void free_simplex_vector(const Simplex_Vector *simplexVectorToFree)
{
  
  free(simplexVectorToFree->initialSimplex);
  simplexVectorToFree->initialSimplex = NULL;
}


static bool resize_simplex_vector(const Simplex_Vector *simplexVectorToResize)
{
  
  const int newCapacity = (int) (SIMPLEX_VECTOR_RESIZE_FACTOR * simplexVectorToResize->currentCapacity);
  
  const Simplex *initialSimplex = realloc(simplexVectorToResize->initialSimplex, newCapacity * (sizeof(Simplex) + simplexVectorToResize->simplexDimension * sizeof(int)));
  
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
  
  return VECTOR_RESIZE_SUCCESS;
}