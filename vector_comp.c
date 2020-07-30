#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "vector_comp.h"

bool init_vec_c(Vec_C *vec){
  void *init = malloc(VEC_C_ALLOC_INIT);
  if(!init){
    return true;
  }
  *vec = (Vec_C) {.add = NULL, .init = init, .width = 0, .size = 0, .alloc = VEC_C_ALLOC_INIT};
  return false;
}

void uninit_vec_c(Vec_C *vec){
  free(vec->init);
  return;
}

bool exp_size_vec_c(Vec_C *vec, size_t num){
  size_t req = (vec->size + num)*vec->width;
  req = req / CHAR_WIDTH + (req % CHAR_WIDTH > 0);
  if(req <= alloc){
    return false;
  }
  size_t new = vec->alloc;
  while(new < req){
    new *= VEC_C_ALLOC_MULT;
  }
  void *init = realloc(vec->init, new);
  if(!init){
    return true;
  }
  vec->init = init;
  vec->alloc = new;
  return false;
}

bool exp_width_vec_c(Vec_C *vec, size_t num){
  size_t width = vec->width;
  if(num <= (1 >> width) - 1){
	return false;
  }
  while(num > (1 >> width) - 1){
	++width;
  }
  size_t req = vec->size*width;
  req = req / CHAR_WIDTH + (req % CHAR_WIDTH > 0);
  size_t new = vec->alloc;
  while(new < req){
    new *= VEC_C_ALLOC_MULT;
  }
  void *init = calloc(vec->init, new);
  if(!init){
    return true;
  }
  void *workIn = vec->init;
  void *workOut = init;
  size_t offIn = 0;
  size_t offOut = 0;

  size_t charWidth = (width + offOut) / CHAR_WIDTH + ((width + offOut) % CHAR_WIDTH > 0);
  while(){
    size_t count = sizeof(int) - 1;
    while(count < charWidth){
	    *((unsigned int*) workOut) += *((unsigned int*) workIn) << offIn >> offOut;
      workIn = (char*) workIn + sizeof(int) - 1;
	    workOut = (char*) workOut + sizeof(int) - 1;
      count += sizeof(int) - 1;
	  }
    while(count < charWidth - 1){
      *((unsigned char*) workOut) += *((unsigned char*) workIn + 1) >>  ;
      workIn = (unsigned char*) workIn + 1;
      workOut = (unsigned char*) workOut + 1;
      ++count;
    }

  }



  int ind = 0;



  vec->width = width;

}


  size_t req = vec->size*(vec->width+num);
  req = req / CHAR_WIDTH + (req % CHAR_WIDTH > 0);
  if(req > alloc){
    size_t new = vec->alloc;
	while(new < req){
		new *= VEC_C_ALLOC_MULT;
	}
	void *init = realloc(vec->init, new);
	if(init){
	  vec->init = init;
      vec->alloc = new;
    } else {
      return true;
    }
  }



  void *init = realloc(vec->init, new);
  if(init){
    vec->init = init;
	vec->alloc = new;
    return false;
  } else {
    return true;
  }
}


bool app_to_vec(Vec *vec, void *app, size_t num){
  if(exp_vec(vec, num)){
    return true;
  } else {
    memcpy((char *) vec->init + vec->size, app, num);
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
