#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

const size_t tern_(const bool cond, const size_t v1, const size_t v2){

  return ((size_t) cond)*v1 + ((size_t) !cond)*v2;
}

int main(void){

  float  val1 = 2*SIZE_MAX;
  const int x = 5 < 6 ? (int) val1 : 1274;

  printf("%d", x);

  return 1;
}
