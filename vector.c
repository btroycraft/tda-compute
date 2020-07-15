#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vector.h"

bool init_vec(Vec *vec){
  void *init = malloc(VEC_SIZE_INIT);
  if(init){
    *vec = (Vec) {.add = NULL, .init = NULL, .size = 0, .alloc = 0};
    return false;
  }
  else{
    *vec = (Vec) {.add = NULL, .init = NULL, .size = 0, .alloc = VEC_SIZE_INIT};
    return true;
  }
}

void uninit_vec(Vec *vec){
  if(!vec->init){
    free(vec->init);
  }
  *vec = (Vec) {.add = NULL, .init = NULL, .size = 0, .alloc=0};
}

bool exp_vec(Vec *vec, size_t num){

  if(vec->alloc - vec->size >= num){
    return false;
  }
  if(!vec->alloc){
    if(init_vec(vec)){
      return false;
    }
  }
  if(SIZE_MAX - vec->alloc < num){
    return true;
  }

  size_t req = vec->size + num;
  size_t allocMultInt = (size_t) VEC_SIZE_MULT;
  double allocMultFrac = VEC_SIZE_MULT - allocMultInt;

  size_t new = vec->alloc;
  while(new < req){
    if(SIZE_MAX / new <= allocMultInt){
      new *= allocMultInt;
      if((size_t) (new*allocMultFrac) <= SIZE_MAX-new){
        new += (size_t) (new*allocMultFrac);
      } else {
        new = SIZE_MAX;
      }
    } else {
      new = SIZE_MAX;
    }
  }

  void *init = realloc(vec->init, new);
  if(init){
    *vec = (Vec) {.add = NULL, .init = init, .size = vec->size, .alloc = new};
    return false;
  } else {
    return true;
  }
}

bool app_to_vec(Vec *vec, void *app, size_t num){
  if(exp_vec(vec, num)){
    return true;
  } else {
    memcpy(&((char *) vec->init)[vec->size], app, num);
    vec->size += num;
    return false;
  }
}

bool app_to_paired_vecs_t(Vec *vec1, void* app1, void* num1, Vec *vec2, void* app2, void* num2, mutexShared, mutexThreads, threadID, numThreads){

  size_t size1 <- vec1->size;
  size_t size2 <- vec2->size;

  pthread_mutex_lock(mutexShared);
  pthread_mutex_lock(&mutexThreads[threadID]);

  bool expand = vec1->alloc - vec1->size < num1 || vec2->alloc - vec2->size < num2;

  if(expand){
    for(uint_fast8_t threadIndex = 0; threadIndex < numThreads; ++threadIndex){
      if(threadIndex != threadID){
        pthread_mutex_lock(&mutexThreads[threadIndex]);
      }
    }
  }

  if(exp_vec(vec1, num1)){
    flag = true;
  }
  if(exp_vec(vec2, num2)){
    flag = true;
  }

  pthread_mutex_unlock(mutexShared);

  if(expand){
    for(uint_fast8_t threadIndex = 0; threadIndex < numThreads; ++threadIndex){
      if(threadIndex != threadID){
        pthread_mutex_unlock(&mutexThreads[threadIndex]);
      }
    }
  }

  memcpy(&((char *) vec1)[size1], app1, num1);
  memcpy(&((char *) vec2)[size2], app2, num2);

  pthread_mutex_unlock(&mutexThreads[threadID]);

  return(flag);
}
