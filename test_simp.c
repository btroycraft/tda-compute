#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#include "simplex_vector.h"
#include "integer_vector.h"
#include "simplicial_complex.h"

double test_func(int *, int, void *);


int main(void)
{
  
  int dim = 8;
  int maxVert = 20;

  Simplex_Vector *simplicialComplex = generate_simplicial_complex(&test_func, NULL, maxVert, dim, 0);
  if(simplicialComplex == NULL){
    return 1;
  }
  
  for(int i = 0; i <= dim; i++){
    free_simplex_vector(&simplicialComplex[i]);
  }
  free(simplicialComplex);
  
  return 0;
}


double test_func(int *initialVertex, int simplexDimension, void *filtrationFunctionParameters){
  
  return 0;
  
  for(int i = 0; i <= simplexDimension; i++){
    switch(initialVertex[i]){
      
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
