#ifndef SIMP_H_
#define SIMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//#define NDEBUG
#include <assert.h>

#ifndef INT_VEC_INIT_SIZE 
#define INT_VEC_INIT_SIZE 4
#endif
#ifndef UINT_VEC_INIT_SIZE 
#define UINT_VEC_INIT_SIZE 4
#endif
#ifndef VERT_VEC_INIT_SIZE 
#define VERT_VEC_INIT_SIZE 4
#endif
#ifndef SIMP_VEC_INIT_SIZE 
#define SIMP_VEC_INIT_SIZE 4
#endif

#ifndef INT_VEC_MULT
#define INT_VEC_MULT 2
#endif
#ifndef UINT_VEC_MULT
#define UINT_VEC_MULT 2
#endif
#ifndef VERT_VEC_MULT
#define VERT_VEC_MULT 2
#endif
#ifndef SIMP_VEC_MULT
#define SIMP_VEC_MULT 2
#endif

#ifndef VEC_ALLOC_FAIL
#define VEC_ALLOC_FAIL true
#endif

typedef unsigned int Vert;
typedef struct Simp{
  double par;
  unsigned int lab;
  Vert init;
} Simp;
typedef struct Int_Vec{
  unsigned int size;
  unsigned int cap;
  unsigned int alloc;
  int *init;
} Int_Vec;
typedef struct UInt_Vec{
  unsigned int size;
  unsigned int cap;
  unsigned int alloc;
  unsigned int *init;
} Int_Vec;
typedef struct Vert_Vec{
  unsigned int size;
  unsigned int cap;
  unsigned int alloc;
  Vert *init;
} Vert_Vec;
typedef struct Simp_Vec{
  unsigned int dim;
  unsigned int size;
  unsigned int cap;
  unsigned int alloc;
  Simp *init;
} Simp_Vec;

bool init_int_vec(Int_Vec *const);
  
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
bool init_uint_vec(UInt_Vec *const);
  
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
bool init_vert_vec(Vert_Vec *const);
  
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
bool init_simp_vec(Simp_Vec *const);
  
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

bool exp_int_vec(Int_Vec *const, const unsigned int);
  
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
bool exp_uint_vec(UInt_Vec *const, const unsigned int);
  
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
bool exp_vert_vec(Vert_Vec *const, const unsigned int);
  
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
bool exp_simp_vec(Simp_Vec *const, const unsigned int);
  
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

bool app_int_to_vec(const int *const, Int_Vec *const, const unsigned int);
  
  if(exp_int_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    int *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(int));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_uint_to_vec(const unsigned int *const, UInt_Vec *const, const unsigned int);
  
  if(exp_uint_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    unsigned int *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(unsigned int));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_vert_to_vec(const Vert *const, Vert_Vec *const, const unsigned int);
  
  if(exp_vert_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    Vert *const work = vec->init + vec->size;
    memcpy(work, app, num * sizeof(Vert));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}
bool app_simp_to_vec(const Simp *const, Simp_Vec *const, const unsigned int);
  
  if(exp_simp_vec(vec, num) == VEC_ALLOC_FAIL){
    return VEC_ALLOC_FAIL;
  } else {
    Simp *const work = (Simp *) ((Vert *) vec->init + vec->size * vec->dim) + vec->size;
    memcpy(work, app, num * (sizeof(Simp) + vec->dim * sizeof(Vert)));
    vec->size += num;
    return !VEC_ALLOC_FAIL;
  }
}

void free_int_vec(Int_Vec *const);
  
  free(vec->init);
  *vec = (Int_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_uint_vec(UInt_Vec *const);
  
  free(vec->init);
  *vec = (UInt_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_vert_vec(Vert_Vec *const);
  
  free(vec->init);
  *vec = (Vert_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};
  
}
void free_simp_vec(Simp_Vec *const);

void upd_simp_vec_dim(Simp_Vec *const);

#endif
