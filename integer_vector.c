#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "integer_vector.h"

bool resize_integer_vector(Integer_Vector *);


bool initialize_integer_vector(const Integer_Vector *integerVectorToInitialize)
{
  
  const int *initialInteger = (int *) malloc(INTEGER_VECTOR_INITIAL_CAPACITY * sizeof(int));
  
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

bool append_integer_to_vector(const int integerToAppend, const Integer_Vector *destinationIntegerVector)
{
  
  if(destinationIntegerVector->currentSize == destinationIntegerVector->currentCapacity){
    if(resize_integer_vector(destinationIntegerVector) == VECTOR_ALLOCATION_FAILURE){
      return VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  destinationIntegerVector->initialInteger[destinationIntegerVector->currentSize] = integerToAppend;
  destinationIntegerVector->currentSize++;
  
  return VECTOR_APPEND_SUCCESS;
}

void free_integer_vector(const Integer_Vector *integerVectorToFree)
{
  
  free(integerVectorToFree->initialInteger);
  integerVectorToFree->initialInteger = NULL;
}


static bool resize_integer_vector(const Integer_Vector *integerVectorToResize)
{
  
  const int newCapacity = (int) (INTEGER_VECTOR_RESIZE_FACTOR * integerVectorToResize->currentCapacity);
  
  const int *initialInteger = (int *) realloc(integerVectorToResize->initialInteger, newCapacity * sizeof(int));
  
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