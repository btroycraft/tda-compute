#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h>

#include "simplex_vector.h"
#include "integer_vector.h"
#include "simplicial_complex.h"

#ifndef SIMP_INCL
#define SIMP_INCL true
#endif

static bool generate_simplicial_complex_recursively(bool (*const)(int *, int, void *), void *const, const int, const double, Simplex_Vector *const, Simplex *const, const Integer_Vector *const, Integer_Vector *const);


Simp_Comp *gen_simp_comp(bool (const *const simp_func)(Simp *const, const unsigned int, va_list), const Vert maxVert, const unsigned int maxDim, const unsigned int numThreads, ...){
  
  va_list args;
  va_start(args, maxDim);
  
  pthread_t threads[numThreads];
  Simp_Vec simpThread[numThreads];
  
  bool flag = !ALLOC_FAIL;
  
  Simp_Comp *const comp = (Simp_Comp *) malloc(sizeof(Simp_Comp) + maxDim * sizeof(Simp_Vec));
  if(comp == NULL){
    return ALLOC_FAIL;
  }
  
  if(flag != ALLOC_FAIL){
    Simp_Vec *work = simpThread;
    for(unsigned int i = 0; i < threads, ++i){
      if(init_simp_vec(work) == ALLOC_FAIL){
        flag = ALLOC_FAIL;
        break;
      }
      ++work;
    }
  }
  
  if(flag != ALLOC_FAIL){
    Simp_Vec *work = &comp->init;
    for(unsigned int i = 0; i <= maxDim; ++i){
      
      work->dim = i;
      if(init_simp_vec(work) == ALLOC_FAIL){
        flag = ALLOC_FAIL;
        break;
      }
      ++work;
    }
  }
  
  {
  Simp simpTemp;
    for(Simp simpTemp = (Simp) {.init = 0}; simpTemp.init <= maxVert; ++simpTemp.init){
      
      if((*simp_func)(&simpTemp, 0, args) == SIMP_INCL){
        if(app_simp_to_vec(&simpTemp, simpComp->init, 1) == ALLOC_FAIL){
          flag = ALLOC_FAIL;
          break;
        }
      }
    }
  }
  
  if(simplicialComplexGenerationFlag != VECTOR_ALLOCATION_FAILURE){
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

generate_simplicial_complex_thread(bool (const *const simplex_function)(Simplex *const, const unsigned int, va_list)){
  
}

bool label_simplicial_complex_by_rank(Simplex_Vector *simplicialComplex){

  bool simplicialComplexRankFlag = SIMPLICIAL_COMPLEX_LABELLING_SUCCESS;
  
  for(int i = 0; i < simplicialComplex->maximumSimplexDimension; ++i){
    
    
    
  }
  
  int* simplexRanks = (int*) malloc();
  
}

bool rank_simplex_set_recursively(simplexSetToRank, ){
  
  const int length = upper - lower;
  Simplex *
  
  if(upper - lower < 17){
    for(int i = 0; i < length; ++i){
      for(int j = i; j > 0 && )
    }
  }
  
}

generate

generate_uniformly_distributed_random_permutation(int permutationLength){
  
  int *const permutation = (int *) malloc(permutationLength*sizeof(int));
  
  int divisor, remainder;
  
  int random
  for(int i = permutationLength; i > 1; ){
    int 
  }
  
 
return  
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
