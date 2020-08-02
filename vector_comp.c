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

bool exp_alloc_vec_c(Vec_C *vec, size_t num){
	
	size_t req = (vec->size + num - 1) * vec->width / CHAR_WIDTH + sizeof(unsigned int);
	if(req <= vec->alloc){
		return false;
	}
	
	size_t reqExp = vec->alloc;
	while(reqExp < req){
		reqExp *= VEC_C_ALLOC_MULT;
	}
	
	void *init = realloc(vec->init, reqExp);
	if(!init){
		return true;
	}
	
	vec->init = init;
	vec->alloc = reqExp;
	
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
	
	size_t req = (vec->size - 1) * width / CHAR_WIDTH + sizeof(unsigned int);
	size_t reqExp = vec->alloc;
	while(reqExp < req){
		reqExp *= VEC_C_ALLOC_MULT;
	}
	
	void *init = malloc(reqExp);
	if(!init){
		return true;
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