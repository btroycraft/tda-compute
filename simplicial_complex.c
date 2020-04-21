#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simplex_vector.h"
#include "integer_vector.h"
#include "simplicial_complex.h"

static bool generate_simplicial_complex_recursively(double (*const)(int *, int, void *), void *const, const int, const double, Simplex_Vector *const, Simplex *const, const Integer_Vector *const, Integer_Vector *const);


Simplex_Vector *generate_simplicial_complex(double (*const filtrationFunction)(int *, int, void *), void *const filtrationFunctionParameters, const int largestVertex, const int maximumSimplexDimension, const double maximumFiltrationParameter)
{
  
  Simplex_Vector *const simplicialComplex = (Simplex_Vector *) malloc((maximumSimplexDimension+1) * sizeof(Simplex_Vector));
  Integer_Vector *const vertexCandidates = (Integer_Vector *) malloc((maximumSimplexDimension+1) * sizeof(Integer_Vector));
  Simplex *const simplexCandidate = (Simplex *) malloc(sizeof(Simplex) + maximumSimplexDimension * sizeof(int));
  
  bool simplicialComplexGenerationFlag = SIMPLICIAL_COMPLEX_GENERATION_SUCCESS;
  
  for(int i = 0; i <= maximumSimplexDimension; ++i){
    
    simplicialComplex[i].simplexDimension = i;
    initialize_simplex_vector(&simplicialComplex[i]);
    initialize_integer_vector(&vertexCandidates[i]);
  }
  
  for(int i = 0; i <= largestVertex; ++i){
    
    simplexCandidate->initialVertex = i;
    simplexCandidate->filtrationParameter = (*filtrationFunction)(&simplexCandidate->initialVertex, simplicialComplex->simplexDimension, filtrationFunctionParameters);
    
    if(simplexCandidate->filtrationParameter <= maximumFiltrationParameter){
        if(append_simplex_to_vector(simplexCandidate, simplicialComplex) == VECTOR_ALLOCATION_FAILURE){
          simplicialComplexGenerationFlag = VECTOR_ALLOCATION_FAILURE;
          break;
        }
        if(append_integer_to_vector(i, vertexCandidates) == VECTOR_ALLOCATION_FAILURE){
          simplicialComplexGenerationFlag = VECTOR_ALLOCATION_FAILURE;
          break;
        }
      }
  }
  
  if(simplicialComplexGenerationFlag == SIMPLICIAL_COMPLEX_GENERATION_SUCCESS){
    if(generate_simplicial_complex_recursively(filtrationFunction, filtrationFunctionParameters, maximumSimplexDimension, maximumFiltrationParameter, simplicialComplex+1, simplexCandidate, vertexCandidates, vertexCandidates+1) == VECTOR_ALLOCATION_FAILURE){
      simplicialComplexGenerationFlag = VECTOR_ALLOCATION_FAILURE;
    }
  }
  
  for(int i = 0; i <= maximumSimplexDimension; ++i){
    
    free_integer_vector(&vertexCandidates[i]);
  }
  
  free(simplexCandidate);
  free(vertexCandidates);
  
  switch(simplicialComplexGenerationFlag){
    case VECTOR_ALLOCATION_FAILURE:
      return NULL;
    case SIMPLEX_GENERATION_SUCCESS:
      return simplicialComplex;
  }
}

bool rank_simplicial_complex(Simplex_Vector *simplicialComplex){

  bool simplicialComplexRankFlag = SIMPLICIAL_COMPLEX_RANKING_SUCCESS;
  
  int simplicialComplexTotalSize = 0;
  for(int i = 0; i < simplicialComplex->maximumSimplexDimension;
  
  int* simplexRanks = (int*) malloc()
  
}



static bool generate_simplicial_complex_recursively(double (*const filtrationFunction)(int *, int, void *), void *const filtrationFunctionParameters, const int maximumSimplexDimension, const double maximumFiltrationParameter, Simplex_Vector *const destinationSimplexVector, Simplex *const simplexCandidate, const Integer_Vector *const currentVertexCandidates, Integer_Vector *const newVertexCandidates)
{
  
  int *workingVertex = &simplexCandidate->initialVertex + destinationSimplexVector->simplexDimension - 1;

  for(int i = 0; i < currentVertexCandidates->currentSize-1; ++i){
    
    newVertexCandidates->currentSize = 0;
    
    *workingVertex = currentVertexCandidates->initialInteger[i];
    ++workingVertex;
    
    for(int j = i+1; j < currentVertexCandidates->currentSize; ++j){
      
      *workingVertex = currentVertexCandidates->initialInteger[j];

      simplexCandidate->filtrationParameter = (*filtrationFunction)(&simplexCandidate->initialVertex, destinationSimplexVector->simplexDimension, filtrationFunctionParameters);
      if(simplexCandidate->filtrationParameter <= maximumFiltrationParameter){
        if(append_simplex_to_vector(simplexCandidate, destinationSimplexVector) == VECTOR_ALLOCATION_FAILURE){
          return VECTOR_ALLOCATION_FAILURE;
        }
        if(append_integer_to_vector(*workingVertex, newVertexCandidates) == VECTOR_ALLOCATION_FAILURE){
          return VECTOR_ALLOCATION_FAILURE;
        }
      }
    }
    
    if(destinationSimplexVector->simplexDimension < maximumSimplexDimension){
      if(generate_simplicial_complex_recursively(filtrationFunction, filtrationFunctionParameters, maximumSimplexDimension, maximumFiltrationParameter, destinationSimplexVector+1, simplexCandidate, newVertexCandidates, newVertexCandidates+1) == VECTOR_ALLOCATION_FAILURE){
        return VECTOR_ALLOCATION_FAILURE;
      }
    }
    
    --workingVertex;
  }
  
  return SIMPLEX_GENERATION_SUCCESS;
}
