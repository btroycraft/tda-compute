#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#include "simplex_vector.h"
#include "integer_vector.h"
#include "simplicial_complex.h"

double test_func(const int *, const int, const void *);


int main(void)
{
  
  Simplex_Vector *simplicialComplex = generate_simplicial_complex(&test_func, NULL, 5, 3, 0);
  if(simplicialComplex == NULL){
    return 1;
  }
  Simplex *workingSimplex;
  
  for(int i = 0; i <= 3; i++){
    workingSimplex = simplicialComplex[i].initialSimplex;
    for(int j = 0; j < simplicialComplex->currentCapacity; j++){
      for(int k = 0; k <= simplicialComplex[i].simplexDimension; k++){
        printf("%d", (&workingSimplex->initialVertex)[k]);
      }
      printf("\n");
      workingSimplex = (Simplex *) ((int *) (workingSimplex + 1) + simplicialComplex[i].simplexDimension);
    }
    printf("\n********\n\n");
  }
  
  free(simplicialComplex);
  
  return 0;
}


double test_func(const int *simplex, const int simplexDimension, const void *filtrationFunctionParameters){
  
  for(int i = 0; i <= simplexDimension; i++){
    switch(simplex[i]){
      
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        return DBL_MAX;
    }
  }
  
  return 0;
}