#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "vector_comp.h"

static const SIZE_MAX_DOUBLE = size_max_double();

bool init_vec_c(Vec_C *vec){

  void *init = malloc(ALLOC_INIT_VEC_C);
  if(!init){
    return true;
  }

  *vec = (Vec_C) {.init = init, .width = 0, .size = 0, .alloc = ALLOC_INIT_VEC_C, .add = NULL};

  return false;
}

void uninit_vec_c(Vec_C *vec){

  free(vec->init);

  return;
}

bool exp_alloc_vec_c(Vec_C *vec, size_t num){

  size_t width = vec->width;

  // Check for possible size_t overflow

  if(width > CHAR_WIDTH){

    size_t q = (SIZE_MAX - sizeof(unsigned int)) / width;
    size_t r = (SIZE_MAX - sizeof(unsigned int)) - width*q;

    if(num > CHAR_WIDTH*q + (CHAR_WIDTH*(r+1)-1) / width + 1 - vec->size){
      return true;
    }
  } else{

    if(num > SIZE_MAX - sizeof(unsigned int) + 1 - vec->size){
        return true;
    }
  }

  // Get required number of bytes to store the compressed vector

  size_t req;
  {
    size_t q1 = num / CHAR_WIDTH;
    size_t r1 = num - CHAR_WIDTH*q1;

    size_t v2 = vec->size - 1;
    size_t q2 = v2 / CHAR_WIDTH;
    size_t r2 = v2 - CHAR_WIDTH*q2;

    req = width*(q1+q2) + width*(r1+r2) / CHAR_WIDTH + sizeof(unsigned int);
  }

  if(req > vec->alloc){

    {
      // Expand vector allocation size by multiplication factor until required size is met

      float reqFloat;
      for(reqFloat = vec->alloc; reqFloat < req; reqFloat *= ALLOC_MULT_VEC_C);
      if{reqFloat > req}{
        req = reqFloat < SIZE_MAX ? (float) reqFloat : SIZE_MAX;
      }
    }

    // Reallocate vector using new size

    void *init = realloc(vec->init, reqExp);
    if(!init){
      return true;
    }

    vec->init = init;
    vec->alloc = req;
  }

  return false;
}

bool exp_width_vec_c(Vec_C *vec, size_t width){

  size_t widthOld = vec->width;

  // Check for possible size_t overflow

  if(width > CHAR_WIDTH){

    size_t q = (SIZE_MAX - sizeof(unsigned int)) / width;
    size_t r = (SIZE_MAX - sizeof(unsigned int)) - width*q;

    if(num > CHAR_WIDTH*q + (CHAR_WIDTH*(r+1)-1) / width + 1 - vec->size){
      return true;
    }
  }

  // Get required number of bytes to store the compressed vector

  size_t req;
  {
    size_t q = (vec->size - 1) / CHAR_WIDTH;
    size_t r = (vec->size - 1) - CHAR_WIDTH*q;

    req = width*q + width*r / CHAR_WIDTH + sizeof(unsigned int);
  }

  if(req > vec->alloc){

    {
      // Expand vector allocation size by multiplication factor until required size is met

      float reqFloat;
      for(reqFloat = vec->alloc; reqFloat < req; reqFloat *= ALLOC_MULT_VEC_C);
      if{reqFloat > req}{
        req = reqFloat < SIZE_MAX ? (float) reqFloat : SIZE_MAX;
      }
    }

    // Reallocate vector using new size

    void *init = realloc(vec->init, reqExp);
    if(!init){
      return true;
    }

    vec->init = init;
    vec->alloc = req;
  }

  size_t offIn = 0;
  size_t offOut = 0;
  unsigned int *workIn = vec->init;
  unsigned int *workOut = init;

for(size_t ind = 0; ind < vec->size; ++ind){

*workOut = (*workIn << offIn >> offOut) | (~(~0 >> offOut) & *workOut);

workIn = (char *) workIn + (offIn + vec->width) / CHAR_WIDTH;
workOut = (char *) workOut + (offOut + width) / CHAR_WIDTH;

offIn = (offIn + vec->width) % CHAR_WIDTH;
offOut = (offOut + width) % CHAR_WIDTH;
}

free(vec->init);

vec->init = init;
vec->alloc = reqExp;
vec->width = width;

return false;
}

bool app_to_vec_c(Vec_C *vec, unsigned int *app, size_t num){

if(exp_alloc_vec(vec, num)){
return true;
}

vec->size += num;

size_t off = vec->size * vec->width % CHAR_WIDTH;
unsigned int *work = (char *) vec->init + vec->size * vec->width / CHAR_WIDTH;

for(size_t ind = 0; ind < num; ++ind){

*work = (app[ind] >> off) | (~(~0 >> off) & *work);

work = (char *) work + (off + vec->width) / CHAR_WIDTH;
off = (off + vec->width) % CHAR_WIDTH;
}

return false;
}

unsigned int ext_val_vec_c(Vec_C *vec, size_t ind){

size_t off = ind * vec->width % CHAR_WIDTH;
unsigned int *work = (char *) vec->init + ind * vec->width / CHAR_WIDTH;

return  ~(~0 >> vec->width) & *work << off;
}
