#ifndef BTOP_H
#define BTOP_H

#include "btop_p.h"

/*struct btop_MatData;
struct btop_MatPW;*/
struct BoundaryOperator;

/*typedef struct {
	unsigned int size;
	unsigned int dimension;
	double* dataArray;
}
btop_MatData;

typedef struct{
	unsigned int size;
	double* dataArray;
}
btop_MatPW; */

typedef struct{
	int dimension;
	HeaderNode* labels;
}
BoundaryOperator;

#endif