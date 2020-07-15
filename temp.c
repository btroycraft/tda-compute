#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

DECLARE_VEC_TYPE_AND_FUNCS(uint, unsigned int, size_t, 1000, 2)

int main(void){
  return 0;  
}

bool afunc(uint_Vec *vec, unsigned int *const init){
  if(init == NULL){
    *vec = (uint_Vec) {.size=0, .cap=0, .alloc=0, .init=NULL};
    return 1;
  } else {
    *vec = (uint_Vec) {.size=0, .cap=1000/sizeof(unsigned int), .alloc=1000, .init = init}; 
    return 0;
  }
}
