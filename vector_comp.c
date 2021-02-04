#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "vector_comp.h"

static const SIZE_MAX_DOUBLE = size_max_double();

bool expand_cap_vec_c(Vec_C *vec, const size_t num){

  // Expand vector capacity to occomodate at least "num" new entries

  const size_t width = vec->width;
  const size_t next = vec->next;
  const size_t off = vec->off;

  if(num == 0 || width == 0){
    return false;
  }

  size_t req;
  {
    // Get required allocation size and check for possible size_t overflows

    const size_t q = num / CHAR_WIDTH;
    const size_t r = num - CHAR_WIDTH*q;

    req = next;

    {
      if(q > SIZE_MAX / width){
        return true;
      }

      const size_t temp = width*q;
      if(req > SIZE_MAX - temp){
        return true;
      }

      req += temp;
    }

    {
      const size_t temp = (width*r + off + (CHAR_WIDTH-1));
      if(req > SIZE_MAX - temp){
        return true;
      }

      req += temp;
    }
  }

  if(expand_alloc_vec_c(vec, req)){
    return true;
  }

  return false;
}

void shift_left_vec_c(void *loc, size_t num, int shift){

  // Shift an array of bytes to the left by "shift" bits
  // Leading bits are removed, with trailing 0s added

  const size_t shiftAbs = (const size_t) abs(shift);
  const size_t shiftAbsTrunc = shiftAbs / CHAR_WIDTH < num ? shiftAbs : CHAR_WIDTH*num;

  size_t startIn = 0;
  size_t startOut = 0;

  size_t endIn = num;
  size_t endOut = num;

  if(shift < 0){

    size_t startIn = shiftAbs / CHAR_WIDTH;
    size_t
    size_t off1 = shiftAbs - CHAR_WIDTH*startIn;
    size_t off2 = CHAR_WIDTH - off1;

    for(size_t ind = )



  }
  else{

    shift = shift / CHAR_WIDTH < num ? shift : CHAR_WIDTH*num;

    shiftByte = shift / CHAR_WIDTH;
    shiftBit = shift - CHAR_WIDTH*shiftByte;
  }



  return false;
}

bool change_width_vec_c(Vec_C *vec, size_t width){

  size_t widthOut = width;
  size_t widthIn = vec->width;
  size_t next = vec->next;
  size_t off = vec->off;

  if((next == 0 && off == 0) || width == widthOld){
    return false;
  }

  if(widthOut > widthIn){

    size_t req;
    {
      // Get required allocation size and check for possible size_t overflows

      size_t q = next / widthIn;
      size_t r = next - widthIn*q;

      {
        if(q > SIZE_MAX / widthOut){
          return true;
        }

        req = widthOut*q;
      }

      {
        size_t temp = (widthOut*((CHAR_WIDTH*r + off) / widthIn) + (CHAR_WIDTH-1)) / CHAR_WIDTH;
        if(req > SIZE_MAX - temp){
          return true;
        }

        req += temp;
      }
    }

    if(expand_alloc_vec_c(vec, req)){
      return true;
    }
  }

  if(widthIn < widthOut){

    size_t sizeTrans = (widthOut + 2*(CHAR_WIDTH-1)) / CHAR_WIDTH;

    unsigned char *trans1 = (unsigned char*) alloca(sizeTrans);




  }
  size_t sizeTrans = widthIn

  size_t offIn = 0;
  size_t offOut = 0;
  char *workIn = vec->init;
  char *workOut = init;

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
