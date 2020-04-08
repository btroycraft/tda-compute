#include <stdio.h>
#include <stdlib.h>

int main(void){

  double data[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
       printf("%f ", data[i+3*j]);
    }
    printf("\n");
  }

  return 0;
}

int count_ind(const int dim, const double par, const double (*funcPar)(void*, int, size_t, void*), const void *funcParArgs, const void *data, const size_t sizeData, const int lengthData){

  int totalPairs;
  char *pairs[2];
  int *rowSizes = (int*) malloc(2 * lengthData * sizeof(int));

  totalPairs = 0;
  for(int i = 0; i < lengthData-1; i++){
    pairs[1] = (char*) data + i*sizeData;
    rowSizes[2*i] = totalPairs;
    for(int j = i+1; j < lengthData; j++){
      pairs[2] = (char*) data + j*sizeData;
      if(funcPar(pairs, 2, sizeData, funcParArgs) <= par){
        totalPairs++;
      }
    }
    rowSizes[2*i+1] = lengthTotal - rowSizes[2*i];
  }

  int *pairsConn = (int*) malloc(totalPairs * sizeof(int));

  totalPairs = 0;
  for(int i = 0; i < lengthData-1; i++){
    pairs[1] = (char*) data + i*sizeData;
    for(int j = i+1; j < lengthData; j++){
      pairs[2] = (char*) data + j*sizeData;
      if(funcPar(pairs, 2, sizeData, funcParArgs) <= par){
        pairsConn[totalPairs] = j;
        totalPairs++;
      }
    }
  }

  return 0;
}

double func(double *data, size_t size_data, int *ind, int indLength){

  int dimData = (int) (size_data / sizeof(double));


}

int increment(int *array, int length, int max){

  if(*array == max-length){
    return 1;
  }

  if(length == 1){
    (*array)++;
  } else if(increment(array+1, length-1, max)){
    (*array)++;
    for(int i = 1; i < length; i++){
      array[i] = *array + i;
    }
  }

  return 0;
}
