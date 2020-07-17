#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <limits.h>
#include <math.h>

#include "simplex_vector.h"
#include "integer_vector.h"
#include "simplicial_complex.h"

typedef Simp_Comp struct{
  uint_fast8_t maxDim;
  size_t vertWidth;
  Vec* simpVec;
  Vec* parVec;
  Vec* labVec;
};
Simp_Comp;

gen_simp_comp(int maxVert, int maxDim, bool (*inclFunc)(int*, size_t, *float, void*)){

  Simp_Comp *comp = malloc(sizeof(Simp_Comp) + 3*(maxDim+1)*sizeof(Vec) + (maxDim+1)*sizeof(size_t));
  Vec *simpVec = (char *) comp + sizeof(Simp_Comp);
  Vec *parVec = (char *) comp + sizeof(Simp_Comp) + (maxDim+1)*sizeof(Vec);
  Vec *labVec = (char *) comp + sizeof(Simp_Comp) + 2*(maxDim+1)*sizeof(Vec);

  comp = (Simp_Comp) {.maxDim = maxDim, .vertWidth = 1, .simpVec = simpVec, .parVec = parVec, .labVec = labVec};
  while(maxVert << comp.vertWidth*CHAR_BIT){
    ++comp.vertWidth;
  }

  Vec vertCand[maxDim];

  for(uint_fast8_t dim = 0; dim < maxDim){
    init_vec(&simpVec[dim]);
    init_vec(&parVec[dim]);
    init_vec(&labVec[dim]);
    init_vec(&vertCand[dim]);
  }
  init_vec(&simpVec[maxDim]);
  init_vec(&parVec[maxDim]);
  init_vec(&labVec[maxDim]);

  float par;

  for(uintmax_t vert = 0; vert <= maxVert; ++vert){
    if((*inclFunc)(&vert, 0, &par, inclFuncArgs)){
      app_to_vec(&simpVec[0], &vert, sizeof(uintmax_t));
      app_to_vec(&parVec[0], &par, sizeof(float));
      app_to_vec(&vertCand[0], &vert, sizeof(uintmax_t));
    }
  }

  uintmax_t simp[maxDim+1];
  size_t candInd1[maxDim];
  size_t candInd2[maxDim];

  uint_fast8_6 dim = 1;
  candInd1[0] = 0;
  candInd2[0] = sizeof(uintmax_t);
  simp[0] = ((uintmax_t *) vertCand[0].init)[0];

  while(dim > 0){

    simp[dim] = ((uintmax_t *) vertCand[dim-1].init)[candInd2[dim-1]];
    if((*inclFunc)(&simp, dim, &par, inclFuncArgs)){
      app_to_vec(&simpVec[dim], &simp, (dim+1)*sizeof(uintmax_t));
      app_to_vec(&parVec[dim], &par, sizeof(float));
      if(dim < maxDim){
        app_to_vec(&vertCand[dim], &simp[dim], sizeof(uintmax_t));
      }
    }

    if(candInd2[dim-1] < vertCand[dim-1].size){
      candInd2[dim-1] += sizeof(uintmax_t);
    }
    else{
      if(vertCand[dim].size > 1 & dim < maxDim){
        candInd1[dim] = 0;
        candInd2[dim] = sizeof(uintmax_t);
        simp[dim] = ((uintmax_t *) vertCand[dim]->init)[0];
        ++dim;
      }
      else {
        while(dim > 0){
          if(candInd2[dim-1] < vertCand[dim-1].size - 1){
            candInd2[dim-1] += sizeof(uintmax_t);
          }
          else{
            --dim;
          }
        }
      }
    }
  }

  return comp;
}
