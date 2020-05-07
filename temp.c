#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

DECLARE_VEC_TYPE_AND_FUNCS(int, int, unsigned int, 4, 2)

int main(void){

  int_Vec vec;
  init_int_vec(&vec);

  return 0;
}
