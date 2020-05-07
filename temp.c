#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

DECLARE_VEC_TYPE_AND_FUNCS(uint, unsigned int, unsigned int, 4, 1000)

int main(void){

  uint_Vec vec;
  init_uint_vec(&vec);
  
  const int n = 250;

  unsigned int arry[n];

  for(int i = 0; i< n; i++){
    arry[i] = i;
  }
  
  app_uint_to_vec(arry, &vec, n);
  
  
  for(int i = 0; i< n; i++){
    printf("%d ", vec.init[i]);
  }
  printf("\n");
  
  free_uint_vec(&vec);
  
  return 0;
}
