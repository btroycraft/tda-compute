#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

DECLARE_VEC_TYPE_AND_FUNCS(uint, unsigned int, unsigned int, 4, 2)

int main(void){

  uint_Vec vec;
  init_uint_vec(&vec);
  
  unsigned int arry[30];

  for(int i = 0; i< 30; i++){
    arry[i] = i;
  }
  
  app_uint_to_vec(arry, &vec, 30);
  
  
  for(int i = 0; i< 30; i++){
    printf("%d", vec.init[i]);
  }
  printf("\n");
  
  free_uint_vec(&vec);
  
  return 0;
}
