#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Vec{ 
  size_t alloc;
  void *init;
  void *next;
} Vec;
 
bool init_vec(Vec *const);
bool exp_vec(Vec *const, const size_t);
bool res_vec(Vec *const, const size_t);
bool app_to_vec(const void *const app, Vec *const, const size_t);
void free_vec(Vec *const);

#endif