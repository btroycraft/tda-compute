#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <assert.h>

#define VEC_ALLOC_FAIL true
#define VEC_ALLOC_SUCC false

#define DECLARE_VEC_TYPE(NAME, ITEM_TYPE, SIZE_TYPE )\
  typedef struct NAME##_Vec{\
    SIZE_TYPE size;\
    SIZE_TYPE cap;\
    SIZE_TYPE alloc;\
    ITEM_TYPE *init;\
  } NAME##_Vec;

#define DECLARE_INIT_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE, INIT_SIZE )\
  bool init_##NAME##_vec(NAME##_Vec *const vec){\
    const ITEM_TYPE *const init = malloc(INIT_SIZE);\
    vec->init = (ITEM_TYPE *) init;\
    assert(init != NULL);\
    if(init == NULL){\
      vec->cap = 0;\
      return VEC_ALLOC_FAIL;\
    } else {\
      vec->alloc = INIT_SIZE;\
      vec->cap = ((SIZE_TYPE) INIT_SIZE) / ((SIZE_TYPE) sizeof(ITEM_TYPE));\
      return !VEC_ALLOC_FAIL;\
    }\
  }

#define DECLARE_EXP_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE, INIT_SIZE, MULT )\
  bool exp_##NAME##_vec(NAME##_Vec *const vec, const SIZE_TYPE num){\
    if(vec->cap == 0){\
      if(init_##NAME##_vec(vec) == VEC_ALLOC_FAIL){\
        return VEC_ALLOC_FAIL;\
      }\
    }\
    const SIZE_TYPE req = vec->size + num;\
    if(req < vec->cap){\
      return !VEC_ALLOC_FAIL;\
    }\
    SIZE_TYPE new = vec->cap;\
    while(new < req){\
      new = (SIZE_TYPE) (MULT * new);\
    }\
    const ITEM_TYPE *const init = realloc(vec->init, new * sizeof(ITEM_TYPE));\
    assert(init != NULL);\
    if(init == NULL){\
      return VEC_ALLOC_FAIL;\
    } else {\
      vec->init = (ITEM_TYPE *) init;\
      vec->cap = new;\
      vec->alloc = new * sizeof(ITEM_TYPE);\
      return !VEC_ALLOC_FAIL;\
    }\
  }

#define DECLARE_APP_TO_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE )\
  bool app_##NAME##_to_vec(const ITEM_TYPE *const app, NAME##_Vec *const vec, const SIZE_TYPE num){\
    if(exp_##NAME##_vec(vec, num) == VEC_ALLOC_FAIL){\
      return VEC_ALLOC_FAIL;\
    } else {\
      ITEM_TYPE *const work = vec->init + vec->size;\
      memcpy(work, app, num * sizeof(ITEM_TYPE));\
      vec->size += num;\
      return !VEC_ALLOC_FAIL;\
    }\
  }
 
#define DECLARE_FREE_VEC_FUN( NAME, ITEM_TYPE )\
  void free_##NAME##_vec(NAME##_Vec *const vec){\
    free(vec->init);\
    *vec = (NAME##_Vec) {.size = 0, .cap = 0, .alloc = 0, .init = NULL};\
  }

#define DECLARE_VEC_TYPE_AND_FUNCS( NAME, ITEM_TYPE, SIZE_TYPE, INIT_SIZE, MULT )\
  DECLARE_VEC_TYPE( NAME, ITEM_TYPE, SIZE_TYPE )\
  DECLARE_INIT_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE, INIT_SIZE )\
  DECLARE_EXP_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE, INIT_SIZE, MULT )\
  DECLARE_APP_TO_VEC_FUNC( NAME, ITEM_TYPE, SIZE_TYPE )\
  DECLARE_FREE_VEC_FUN( NAME, ITEM_TYPE )

#endif
