#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "simp.h"

bool init_int_vec(Int_Vec *const vec){
  
  const int *const init = (int *) malloc(INT_VEC_INIT_SIZE);
  
  vec->init = init;
  
  assert(init != NULL);
  
  if(init == NULL){
    vec->cap = 0;
    return VEC_ALLOC_FAIL;
  } else {
    vec->cap = ((unsigned int) INT_VEC_INIT_SIZE) / sizeof(int);
    return !VEC_ALLOC_FAIL;
  }
}
bool init_uint_vec(UInt_Vec *const vec){
  
  const unsigned int *const init = (unsigned int *) malloc(UINT_VEC_INIT_SIZE);
  
  vec->init = init;
  
  assert(init != NULL);
  
  if(init == NULL){
    vec->cap = 0;
    return VEC_ALLOC_FAIL;
  } else {
    vec->cap = ((unsigned int) UINT_VEC_INIT_SIZE) / sizeof(unsigned int);
    return !VEC_ALLOC_FAIL;
  }
}
bool init_vert_vec(Vert_Vec *const vec){
  
  const Vert *const init = (Vert *) malloc(VERT_VEC_INIT_SIZE);
  
  vec->init = init;
  
  assert(init != NULL);
  
  if(init == NULL){
    vec->cap = 0;
    return VEC_ALLOC_FAIL;
  } else {
    vec->cap = ((unsigned int) VERT_VEC_INIT_SIZE) / sizeof(Vert);
    return !VEC_ALLOC_FAIL;
  }
}
bool init_simp_vec(Simp_Vec *const vec){
  
  const Simp *const init = (Simp *) malloc(SIMP_VEC_INIT_SIZE);
  
  vec->init = init;
  
  assert(init != NULL);
  
  if(init == NULL){
    vec->cap = 0;
    return VEC_ALLOC_FAIL;
  } else {
    vec->cap = ((unsigned int) SIMP_VEC_INIT_SIZE) / sizeof(Simp);
    return !VEC_ALLOC_FAIL;
  }
}

bool exp_int_vec(Int_Vec *const vec, const unsigned int num){
  
  if(vec->cap == 0){
    if(init_int_vec(vec) == VEC_ALLOC_FAIL){
      return VEC_ALLOC_FAIL;
    }
  }
  
  const unsigned int req = vec->size + num;
  if(req < vec->cap){
    return !VEC_ALLOC_FAIL;
  }
  
  unsigned int new = vec->cap;
  while(new < req){
    new = (unsigned int) (INT_VEC_MULT * new);
  }
  
  const int *const init = (int *) realloc(vec->init, new * sizeof(int));
  
  assert(init != NULL);
  
  if(init == NULL){
    return VEC_ALLOC_FAIL;
  } else {
    vec->init = init;
    vec->cap = new;
    vec->alloc = new * sizeof(int);
    return !VEC_ALLOC_FAIL;
  }
}
bool exp_uint_vec(UInt_Vec *const vec, const unsigned int num){
  
  if(vec->cap == 0){
    if(init_uint_vec(vec) == VEC_ALLOC_FAIL){
      return VEC_ALLOC_FAIL;
    }
  }
  
  const unsigned int req = vec->size + num;
  if(req < vec->cap){
    return !VEC_ALLOC_FAIL;
  }
  
  unsigned int new = vec->cap;
  while(new < req){
    new = (unsigned int) (UINT_VEC_MULT * new);
  }
  
  const unsigned int *const init = (unsigned int *) realloc(vec->init, new * sizeof(unsigned int));
  
  assert(init != NULL);
  
  if(init == NULL){
    return VEC_ALLOC_FAIL;
  } else {
    vec->init = init;
    vec->cap = new;
    vec->alloc = new * sizeof(unsigned int);
    return !VEC_ALLOC_FAIL;
  }
}
bool exp_vert_vec(Vert_Vec *const vec, const unsigned int num){
  
  if(vec->cap == 0){
    if(init_vert_vec(vec) == VEC_ALLOC_FAIL){
      return VEC_ALLOC_FAIL;
    }
  }
  
  const unsigned int req = vec->size + num;
  if(req < vec->cap){
    return !VEC_ALLOC_FAIL;
  }
  
  unsigned int new = vec->cap;
  while(new < req){
    new = (unsigned int) (VERT_VEC_MULT * new);
  }
  
  const Vert *const init = (Vert *) realloc(vec->init, new * sizeof(Vert));
  
  assert(init != NULL);
  
  if(init == NULL){
    return VEC_ALLOC_FAIL;
  } else {
    vec->init = init;
    vec->cap = new;
    vec->alloc = new * sizeof(Vert);
    return !VEC_ALLOC_FAIL;
  }
}
bool exp_simp_vec(Simp_Vec *const vec, const unsigned int num){
  
  if(vec->cap == 0){
    if(init_simp_vec(vec) == VEC_ALLOC_FAIL){
      return VEC_ALLOC_FAIL;
    }
  }
  
  const unsigned int req = vec->size + num;
  if(req < vec->cap){
    return !VEC_ALLOC_FAIL;
  }
  
  unsigned int new = vec->cap;
  while(new < req){
    new = (unsigned int) (SIMP_VEC_MULT * new);
  }
  
  const Simp *const init = (Simp *) realloc(vec->init, new * (sizeof(Simp) + vec->dim * sizeof(Vert)));
  
  assert(init != NULL);
  
  if(init == NULL){
    return VEC_ALLOC_FAIL;
  } else {
    vec->init = init;
    vec->cap = new;
    vec->alloc = new * (sizeof(Simp) + vec->dim * sizeof(Vert));
    return !VEC_ALLOC_FAIL;
  }
}

bool app_int_to_vec(const int *const app, Int_Vec *const vec, const unsigned int num){
  
  if(exp_int_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    int *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(int));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_uint_to_vec(const unsigned int *const app, UInt_Vec *const vec, const unsigned int num){
  
  if(exp_uint_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    unsigned int *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(unsigned int));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_vert_to_vec(const Vert *const app, Vert_Vec *const vec, const unsigned int num){
  
  if(exp_vert_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    Vert *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(Vert));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_simp_to_vec(const Simp *const app, Simp_Vec *const vec, const unsigned int num){
  
  if(exp_simp_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    Simp *const work = (Simp *) ((Vert *) vec->init + vec->size * vec->dim) + vec->size;
    memcpy(work, app, num * (sizeof(Simp) + vec->dim * sizeof(Vert)));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}

void free_int_vec(Int_Vec *const vec){
  
  free(vec->init);
  *vec = (Int_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_uint_vec(UInt_Vec *const vec){
  
  free(vec->init);
  *vec = (UInt_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_vert_vec(Vert_Vec *const vec){
  
  free(vec->init);
  *vec = (Vert_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_simp_vec(Simp_Vec *const vec){
  
  free(vec->init);
  *vec = (Simp_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}

void upd_simp_vec_dim(Simp_Vec *const vec){
  
  vec->size = 0;
  vec->cap = vec->alloc / (sizeof(Simp) + vec->dim * sizeof(Vert));
}
