#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "integer_vector.h"

static bool resize_integer_vector(Integer_Vector *const);


bool initialize_integer_vector(Integer_Vector *const integerVectorToInitialize)
{
  
  const int *const initialInteger = (int *) malloc(INTEGER_VECTOR_INITIAL_CAPACITY * sizeof(int));
  
  integerVectorToInitialize->initialInteger = initialInteger;
  integerVectorToInitialize->currentSize = 0;
  
  if(initialInteger == NULL){
    #ifdef INTEGER_VECTOR_DEBUG_ON
      printf("Integer vector allocation failure.\n");
    #endif
    
    integerVectorToInitialize->currentCapacity = 0;
    
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  integerVectorToInitialize->currentCapacity = INTEGER_VECTOR_INITIAL_CAPACITY;
  
  return VECTOR_INITIALIZATION_SUCCESS;
}

bool append_integer_to_vector(const int integerToAppend, Integer_Vector *const destinationIntegerVector)
{
  
  if(destinationIntegerVector->currentSize == destinationIntegerVector->currentCapacity){
    if(resize_integer_vector(destinationIntegerVector) == VECTOR_ALLOCATION_FAILURE){
      return VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  destinationIntegerVector->initialInteger[destinationIntegerVector->currentSize] = integerToAppend;
  ++destinationIntegerVector->currentSize;
  
  return VECTOR_APPEND_SUCCESS;
}

void free_integer_vector(Integer_Vector *const integerVectorToFree)
{
  
  free(integerVectorToFree->initialInteger);
  integerVectorToFree->initialInteger = NULL;
}


static bool resize_integer_vector(Integer_Vector *const integerVectorToResize)
{
  
  const int newCapacity = (const int) (INTEGER_VECTOR_RESIZE_FACTOR * integerVectorToResize->currentCapacity);
  
  const int *const initialInteger = (const int *const) realloc(integerVectorToResize->initialInteger, newCapacity * sizeof(int));
  
  #ifdef INTEGER_VECTOR_DEBUG_ON
    printf("Integer vector resized from %d to %d.\n", integerVectorToResize->currentCapacity, newCapacity);
    if(initialInteger == NULL){
      printf("Integer vector reallocation failure.\n");
    }
  #endif
  
  if(initialInteger == NULL){
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  integerVectorToResize->initialInteger = initialInteger;
  integerVectorToResize->currentCapacity = newCapacity;
  
  return VECTOR_RESIZE_SUCCESS;
}
