#ifndef BTOP_P_H
#define BTOP_P_H

typedef struct{
	int label;
	void* labels;
	size_t size;
	HeaderNode* nextNode;
}
HeaderNode;

typedef struct{
	int label;
	LabelNode* nextNode;
}
LabelNode;

static inline
HeaderNode*
createHeaderNode(const int label, const void* labels, const size_t size, const HeaderNode* nextNode){
	
	HeaderNode* node = malloc(sizeof(HeaderNode));
	node->label = label;
	node->labels = labels;
	node->size = size;
	node->nextNode = nextNode;
	
	return node;
}

static inline
LabelNode*
createLabelNode(const int label, const LabelNode* nextNode){
	
	LabelNode* node = malloc(sizeof(LabelNode));
	node->label = label;
	node->nextNode = nextNode;
	
	return node;
}

static inline
HeaderNode*
deleteHeaderNode(const HeaderNode* node){
	
	HeaderNode* nextNode = node->nextNode;
	
	free(node);
	
	return nextNode;
}

static inline
LabelNode*
deleteLabelNode(const LabelNode* node){
	
	LabelNode* nextNode = node->nextNode;
	
	free(node);
	
	return nextNode;
}

static inline
void
convertLabelListToArray(const HeaderNode* headerNode){

	int* array = malloc(headerNode->size*sizeof(int));
	LabelNode* node;
	int offset;
	
	offset = 0;
	node = headerNode->labels;
	while(node != NULL){

		array[offset] = node->label;
		node = deleteLabelNode(node);
		++offset;
	}
	
	headerNode->labels = array;
	
	return;
}

static inline
void
addLabelArrayToList(const HeaderNode* headerNodeA, const HeaderNode* headerNodeB){
	
	int* array = headerNodeA->labels;
	LabelNode** node = &headerNodeB->labels;
	
	int offset;
	size_t arraySize = headerNodeA->size;
	size_t listSize = headerNodeB->size;
	
	offset = 0;
	while(offset < arraySize && *node != NULL){

		switch(array[offset] > node->label - array[offset] < node->label){
			case -1:
				*node = createLabelNode(array[offset], *node);
				labelNode = &(*node)->nextNode;
				++offset;
				++listSize;
				break;
			case 0:
				*node = deleteLabelNode(*node);
				++offset;
				--listSize;
				break;
			case 1:
				node = &(*node)->nextNode;
				break;
		}
	}

	while(offset < arraySize){
		*node = createLabelNode(array[offset], NULL);
		node = &(*node)->nextNode;
		++offset;
		++listSize;
	}
	
	headerNodeB->size = listSize;
	
	return;
}

static inline
int
containsLabel(const HeaderNode* headerNode, const int label){
	
	LabelNode* node = headerNode->labels;
	
	while(node != NULL){
		if(node->label == label){
			return 1;
		}
		node = node->nextNode;
	}
	return 0;
}

#endif