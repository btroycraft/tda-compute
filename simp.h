#ifndef SIMP_H_
#define SIMP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vector.h"

#define DECLARE_SIMP_TYPES_AND_FUNCS( LAB, SIMP_TYPE, LAB_TYPE, PAR_TYPE, VERT_TYPE, VEC_TYPE, DIM_TYPE, INIT_ALLOC_SIZE, ALLOC_MULT )\
  \
  typedef struct SIMP_TYPE{\
    LAB_TYPE lab;\
    PAR_TYPE par;\
    VERT_TYPE init;\
  } SIMP_TYPE;\
  \
  typedef struct VEC_TYPE{\
    DIM_TYPE dim;\
    size_t width;\
    size_t size;\
    size_t cap;\
    size_t alloc;\
    SIMP_TYPE *init;\
  } VEC_TYPE;\
  \
  inline bool init_simp_vec##LAB(VEC_TYPE *const vec, DIM_TYPE dim){\
    const SIMP_TYPE *const init = malloc(INIT_ALLOC_SIZE);\
    if(init){\
      *vec = (VEC_TYPE) {.dim = dim, .size = 0, .cap = 0, .alloc = 0, .init = NULL};\
      return 0;\
    else{\
      *vec = (VEC_TYPE) {.dim = dim, .size = 0, .cap = INIT_ALLOC_SIZE/((dim+1) * sizeof(ITEM_TYPE)), .alloc = INIT_ALLOC_SIZE, .init = init};\
      return 1;\
    }\
  }\
  \
  inline bool exp_simp_vec##LAB(VEC_TYPE *const vec, const size_t num){\
    if(vec->cap - vec->size >= num){\
      return 0;\
    }\
    if(!vec->alloc){\
      if(init_simp_vec##LAB(vec), vec->dim){\
        return 1;\
      }\
    }\
    if(SIZE_MAX / (sizeof(SIMP_TYPE) + vec->dim * sizeof(VERT_TYPE)) - vec->size < num){\
      return 1;\
    }\
    const size_t req = (vec->size + num)*(sizeof(SIMP_TYPE) + vec->dim*sizeof(VERT_TYPE));\
    const size_t allocMultInt = (size_t) ALLOC_MULT;\
    const float allocMultFrac = ALLOC_MULT - allocMultInt;\
    size_t new = vec->alloc;\
    while(new < req){\
      if(SIZE_MAX / new <= allocMultInt){\
        new *= allocMultInt;\
        if((size_t) (new*allocMultFrac) <= SIZE_MAX-new){\
          new += (size_t) (new*allocMultFrac);\
        } else {\
          new = SIZE_MAX;\
        }\
      } else {\
        new = SIZE_MAX;\
      }\
    }\
    const SIMP_TYPE *const init = realloc(vec->init, new);\
    if(init){\
      vec->cap = new/(sizeof(SIMP_TYPE) + vec->dim*sizeof(VERT_TYPE));\
      vec->alloc = new;\
      vec->init = init;\
      return 0;\
    } else {\
      return 1;\
    }\
  }\
  \
  inline bool app_to_simp_vec##LAB(const SIMP_TYPE *const app, VEC_TYPE *const vec, const size_t num){\
    if(exp_simp_vec##LAB(vec, num)){\
      return 1;\
    } else {\
      memcpy((VERT_TYPE *) (vec->init + vec->size) + vec->size * vec->dim, app, num * (sizeof(SIMP_TYPE) + vec->dim*sizeof(VERT_TYPE)));\
      vec->size += num;\
      return 0;\
    }\
  }\
  \
  inline void free_simp_vec##LAB(VEC_TYPE *const vec){\
    free(vec->init);\
    vec->size = 0;\
    vec->cap = 0;\
    vec->alloc = 0;\
    vec->init = NULL;\
  }\
  \
  inline void upd_simp_vec_dim##LAB(VEC_TYPE *const vec, DIM_TYPE dim){\
    vec->dim = dim;\
    vec->cap = (vec->alloc) / (sizeof(SIMP_TYPE) + (dim-1)*sizeof(VERT_TYPE));\
  }
  
#endif
