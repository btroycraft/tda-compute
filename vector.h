#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define VEC_SIZE_INIT 32
#define VEC_SIZE_MULT 2

typedef struct Vec{
  void *add;
  void *init;
  size_t size;
  size_t alloc;
} Vec;

bool init_vec(Vec*);
void uninit_vec(Vec*);
bool exp_vec(Vec*, size_t);
bool app_to_vec(Vec*, void*, size_t);

#endif
