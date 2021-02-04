#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "vec_compr.h"
#include "vec_compr_int.h"

// Uninitialize vector by freeing associated allocation

void uninit_vec_compr(Vec_Compr *vec){

  free(vec->init);

  return;
}
