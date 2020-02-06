#include "btop.h"
#include "btop_p.h"

typedef struct{
	int vertex;
	VertexNode* nextNode;
} VertexNode;

typedef struct{
	int vertexA, vertexB;
	double parameter;
} Edge;

typedef struct{
	int* vertices;
	double parameter;
	SimplexNode* nextNode;
} SimplexNode;

typedef struct{
	int* vertices;
	double parameter;
} Simplex;


struct{Simplex*; size_t}
constructRipsSimplices(const double* pairwiseDistances, const size_t size, const double maxParameter, const int dimension){
	
	VertexNode* vertexArray = malloc(size*sizeof(VertexNode*));
	VertexNode* iterArray = malloc((dimension-1)*sizeof(VertexNode*));
	VertexNode* sharedList;
	VertexNode* node;
	size_t simplexSize;
	size_listSize = 0;
	size_t edgeArraySize = size*(size-1)/2;
	Edge* edgeArray = malloc(edgeArraySize*sizeof(Edge));
	int* simplex = malloc((dimension+1)*sizeof(int));
	SimplexNode* simplexList = NULL;
	void* simplexLocation;
	
	int iterA, iterB, iterC, vertexA, vertexB;
	
	for(iterA = 0; iterA < size; ++iterA){
		vertexArray[iterA] = NULL;
	}
	
	for(iterA = 0; iterA < size-1; ++iterA){
		for(iterB = iterA+1; iterB < size; ++iterB){
			iterC = iterA+iterB*(iterB+1)/2;
			edges[iterC]->distance = pairwiseDistances[iterC]/2;
			edges[iterC]->vertexA = iterA;
			edges[iterC]->vertexB = iterB;
		}
	}
	
	qsort(edgeArray, edgeArraySize, sizeof(Edge), &compareEdges);
	
	iterA = 0;
	while(edgeArray[iterA]->parameter <= maxParameter && iterA < edgeArraySize){
		vertexArray[edgeArray[iterA]->vertexA] = createVertexNode(edges[iterA]->vertexB, vertexArray[edgeArray[iterA]->vertexA]);
		vertexArray[edgeArray[iterA]->vertexB] = createVertexNode(edges[iterA]->vertexA, vertexArray[edgeArray[iterA]->vertexB]);
		++iterA;
	}
	
	--iterA;
	while(iterA >= 0){
		
		vertexA = edgeArray[iterA]->vertexA;
		vertexB = edgeArray[iterA]->vertexB;
		vertexArray[vertexA] = deleteVertexNode(vertexArray[vertexA]);
		vertexArray[vertexB] = deleteVertexNode(vertexArray[vertexB]);
		simplex[0] = vertexA;
		simplex[1] = vertexB;
		
		sharedList = getSharedVertices(vertexArray[vertexA], vertexArray[vertexB]);
		
		if(selectFirstVertices(sharedList, iterArray, dimension-1) == 1){
			do{
				for(iterB = 0; iterB < dimension-1; ++iterB){
					simplex[iterB+2] = iterArray[iterB]->vertex;
				}
				if(isSimplexInRips(&simplex[2], dimension-1, pairwiseDistances, maxParameter)){
					simplexList = createSimplexNode(edgeArray[iterA]->parameter, simplexList, simplex, dimension+1);
					++listSize;
				}
			} while(nextCombination(iterArray, dimension-1) == 1);
			
			while(sharedList != NULL){
				sharedList = deleteVertexNode(sharedList);
			}
		}
		--iterA;
	}
	
	for(iterA = 0; iterA < size; ++iterA){
		node = vertexArray[iterA];
		while(node != NULL){
			node = deleteVertexNode(node);
		}
	}
	
	free(edgeArray);
	free(vertexArray);
	free(simplex);
	free(iterArray);
	
	simplexSize = sizeof(Simplex)+(dimension+1)*sizeof(int);
	simplexArray = malloc(listSize*simplexSize);
	simplexLocation = &simplexArray[listSize+1];
	for(iterA = 0; iterA < listSize; ++iterA){
		simplexArray[iterA]->vertices = simplexLocation;
		simplexArrat[iterA]->parameter = simplexList->parameter;
		memcpy(simplexLocation, simplexList->vertices, (dimension+1)*sizeof(int));
		simplexLocation += (dimension+1)*sizeof(int));
	}
	
	qsort(simplexArray, listSize, sizeof(Simplex), &compareSimplices);
	
	return {simplexArray, listSize};
}

static inline
VertexNode*
createVertexNode(int vertex, VertexNode* nextNode){
	
	VertexNode* node = malloc(sizeof(VertexNode));
	
	node->vertex = vertex;
	node->nextNode = nextNode;
	
	return node;
}

static inline
VertexNode*
deleteVertexNode(const VertexNode* node){
	
	VertexNode* nextNode = node->nextNode;
	
	free(node);
	
	return nextNode;
}

static inline
VertexNode*
getSharedVertices(const VertexNode* listA, const VertexNode* listB){
	
	VertexNode* sharedList = NULL;
	VertexNode* nodeA, nodeB;
	
	nodeaA = listA;
	while(nodeA != NULL){
			nodeB = listB;
			while(nodeB != NULL){
				if(nodeA->vertex == nodeB->vertex){
					listC = createVertexNode(nodeA->vertex, listC);
				}
				nodeB = nodeB->nextNode;
			}
			nodeA = nodeA->nextNode;
	}
	
	return sharedList;
}

static inline
SimplexNode*
createSimplexNode(const double parameter, const SimplexNode* nextNode, const int* simplex, const size_t size){
	SimplexNode* node = malloc(sizeof(SimplexNode)+size*sizeof(int));
	node->parameter = parameter;
	node->nextNode = nextNode;
	node->vertices = memcpy(node+1, simplex, size*sizeof(int));
	qsort(node+1, size, sizeof(int), &compareVertices);
	
	return node;
}

static inline
SimplexNode*
deleteSimplexNode(SimplexNode* node){
	
	SimplexNode* nextNode = node->nextNode;
	
	free(node);
	
	return nextNode;
}

int
compareEdges(Edge* edgeA, Edge* edgeB){
	
	return edgeA->parameter > edgeB->parameter - edgeA->parameter < edgeB->parameter;
}

int
compareVertices(int* vertexA, int* vertexB){
	
	return *vertexA > *vertexB - *vertexA < *vertexB;
}

int
compareSimplices(Simplex* simplexA, Simplex* simplexB){
	
	offset = 0;
	
	switch(simplexA->parameter > simplexB->parameter - simplexA->parameter < simplexB->parameter){
		
		case -1:
			return -1;
		case 0:
			while(1){
				switch(simplexA->vertices[offset] > simplexB->vertices[offset] - simplexA->vertices[offset] < simplexB->vertices[offset]){
					
					case -1:
						return -1;
					case 0:
						++offset
						break;
					case 1:
						return 1;
				}
			}
		case 1:
			return 1;
	}
}

static inline
int
selectFirstVertices(VertexNode* node, const VertexNode* array, const size_t size){
	
	int offset;
	
	offset = 0;
	while(offset < size);
		if(node == NULL){
			return 0;
		} else {
			array = node;
			node = node->nextNode;
			++offset;
		}
	}
	
	return 1;
}

static inline
int
nextCombination(VertexNode* array, const size_t size){
	
	int offset;
	
	if(array[size-1]->nextNode != NULL){
		array[size-1] = array[size-1]->nextNode;
		return 1;
	}
	offset = size-2;
	while(offset >= 0){
		if(array[offset]->nextNode == array[offset+1]){
			--offset;
		} else {
			array[offset] = array[offset]->nextNode;
			++offset;
			while(offset < size){
				array[offset] = array[offset-1]->nextNode;
				++offset;
			}
			return 1;
		}
	}
	
	return 0;
}

static inline
int
isSimplexInRips(const int* simplex, const size_t size, const double* pairwiseDistances, const double maxParameter){
	
	int iterA, iterB, min, max;
	
	for(iterA = 0; iterA < size-1; ++iterA){
		for(iterB = iterA+1; iterB < size; ++iterB){
			if(simplex[iterA] < simplex[iterB]){
				min = simplex[iterA];
				max = simplex[iterB];
			} else {
				min = simplex[iterB];
				max = simplex[iterA];
			}
			if(pairwiseDistances[min+max*(max-1)/2]/2 > maxParameter){
				return 0;
			}
		}
	}
	
	return 1;
}
