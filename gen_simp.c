#include "simplex_vector.h"
#include "integer_vector.h"

#define SIMPLEX_GENERATION_SUCCESS true

typedef Simplicial_Complex {
  
} Simplicial_Complex

static bool
generate_simplicial_complex_recursively(double (*)(int *, int, void *), int, double, Simplex_Vector *, Simplex *, Integer_Vector *, Integer_Vector *)

generate_simplicial_complex(const double (*filtrationFunction)(int *, int, void *), const int maximumSimplexDimension, const double maximumFiltrationParameter, int largestVertex)
{
  
  const Simplex_Vector *simplicialComplex = (Simplex_Vector *) malloc((maximumSimplexDimension+1) * sizeof(Simplex_Vector));
  const Integer_Vector *vertexCandidates = (Integer_Vector *) malloc((maximumSimplexDimension+1) * sizeof(Integer_Vector));
  const Simplex *simplexCandidate = (Simplex *) malloc(sizeof(Simplex) + maximumSimplexDimension * sizeof(int));
  
  for(int i = 0; i <= maximumSimplexDimension; i++){
    
    simplicialComplex[i].simplexDimension = i;
    initialize_simplex_vector(&simplicialComplex[i]);
    initialize_integer_vector(&vertexCandidates[i]);
  }
  
  for(int i = 0; i <= largestVertex; i++){
    
    simplexCandidate->initialVertex = i;
    simplexCandidate->filtrationParameter = (*filtrationFunction)(&simplexCandidate->initialVertex, simplexDimension, filtrationFunctionParameters);
    
    if(simplexCandidate->filtrationParameter <= maximumParameterLevel){
        if(append_simplex_to_vector(simplexCandidate, simplicialComplex) == VECTOR_ALLOCATION_FAILURE){
          return VECTOR_ALLOCATION_FAILURE;
        }
        if(append_integer_to_vector(j, vertexCandidates) == VECTOR_ALLOCATION_FAILURE)){
          return VECTOR_ALLOCATION_FAILURE;
        }
      }
  }
  
  if(generate_simplicial_complex_recursively(filtrationFunction, maximumSimplexDimension, maximumFiltrationParameter, simplicialComplex+1, simplexCandidate, vertexCandidates, vertexCandidates+1) == VECTOR_ALLOCATION_FAILURE){
    return VECTOR_ALLOCATION_FAILURE;
  }
  
  return SIMPLEX_GENERATION_SUCCESS;
}

static bool
generate_simplicial_complex_recursively(const double (*filtrationFunction)(int *, int, void *), const int maximumSimplexDimension, const double maximumFiltrationParameter, const Simplex_Vector *destinationSimplexVector, const Simplex *simplexCandidate, const Integer_Vector *currentVertexCandidates, const Integer_Vector *newVertexCandidates)
{
  
  int *workingVertex = (int *) ((Simplex *) simplexCandidate + 1) + (destinationSimplexVector->simplexDimension - 1);
  
  newVertexCandidates->currentSize = 0;
  
  for(int i = 0; i < currentVertexCandidates->currentSize-1; i++){
    
    *workingVertex = currentVertexCandidates->initialVertex[i];
    workingVertex++;
    
    for(int j = i+1; j < currentVertexCandidates->currentSize; j++){
      
      *workingVertex = currentVertexCandidates->initialVertex[j];
      
      simplexCandidate->filtrationParameter = (*filtrationFunction)(&simplexCandidate->initialVertex, destinationSimplexVector->simplexDimension, filtrationFunctionParameters);
      if(simplexCandidate->filtrationParameter <= maximumParameterLevel){
        if(append_simplex_to_vector(simplexCandidate, destinationSimplexVector) == VECTOR_ALLOCATION_FAILURE){
          return VECTOR_ALLOCATION_FAILURE;
        }
        if(append_integer_to_vector(j, newVertexCandidates) == VECTOR_ALLOCATION_FAILURE)){
          return VECTOR_ALLOCATION_FAILURE;
        }
      }
    }
    
    if(simplexDimension < maximumSimplexDimension){
      if(generate_simplicial_complex_recursively(filtrationFunction, maximumSimplexDimension, maximumFiltrationParameter, destinationSimplexVector+1, simplexCandidate, newVertexCandidates, newVertexCandidates+1) == VECTOR_ALLOCATION_FAILURE){
        return VECTOR_ALLOCATION_FAILURE;
      }
    }
    
    workingVertex--;
  }
  
  return SIMPLEX_GENERATION_SUCCESS;
}