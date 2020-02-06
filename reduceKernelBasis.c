#include "btop_p.h"

typedef struct{
	int labelA, labelB;
	LabelLinkNode* nextNode;
}
LabelLinkNode;

void
reduceKernelBasis(HeaderNode** headerList){

	HeaderNode* headerNode;
	HeaderNode** pivotHeaderNode;
	LabelLinkNode* pivotList;
	int pivotLabel;
	
	pivotHeaderNode = headerList;
	while(*pivotHeaderNode != NULL){
		
			pivotLabel = extractPivotLabel(*pivotHeaderNode, &pivotList);
			
			if(pivotLabel < 0){
				
				convertLabels(*pivotHeaderNode, pivotList);
				pivotHeaderNode = &(*pivotHeaderNode)->nextNode;
				
			} else {
				
				convertLabelListToArray(*pivotHeaderNode);
				headerNode = (*pivotHeaderNode)->nodeNext;
				
				while(headerNode != NULL){
					
					if(containsLabel(headerNode, pivotLabel)){
						addLabelArrayToList(*pivotHeaderNode, headerNode);
					}
				}
				
				if(*headerList == *pivotHeaderNode){
					*headerList = (*pivotHeaderNode)->nextNode;
				}
				*pivotHeaderNode = deleteHeaderNode(*pivotHeaderNode);
			}
	}
	
	return;
}

static inline
LabelLinkNode*
createLabelLinkNode(const int labelA, const int labelB, const LabelLinkNode* nextNode){
	
	LabelLinkNode* node = malloc(sizeof(LabelLinkNode));
	node->labelA = labelA;
	node->labelB = labelB;
	node->nextNode = nextNode;
	return node;
}

static inline
LabelLinkNode*
deleteLabelLinkNode(const LabelLinkNode* node){
	
	LabelLinkNode* nextNode = node->nextNode;
	
	free(node);
	
	return nextNode;
}

static inline
int
extractPivotLabel(const HeaderNode* headerNode, LabelLinkNode** linkNode){
	
	LabelNode** node = &headerNode->labels;
	
	while(*node != NULL && *linkNode != NULL){
		
		switch(node->label > linkNode->labelA - node->label < linkNode->labelA){
			case -1:
				*linkNode = createLabelLinkNode((*node)->label, headerNode->label, (*linkNode)->nextNode);
				*node = deleteLabelNode(*node);
				return (*linkNode)->labelA;
			case 0:
				linkNode = &(*linkNode)->nextNode;
				node = &(*node)->nextNode;
				break;
			case 1:
				linkNode = &(*linkNode)->nextNode;
				break;
		}
	}
	
	if(*node != NULL && *linkNode == NULL){
		*linkNode = createLabelLinkNode((*node)->label, headerNode->label, NULL);
		*node = deleteLabelNode(*node);
		--headerNode->size;
		return (*linkNode)->labelA;
	}
	
	return -1;
}

static inline
void
convertLabels(const HeaderNode* headerNode, LabelLinkNode* linkNode){
	
	LabelNode** node = &headerNode->labels;
	
	while(*node != NULL){
		
		switch(linkNode->labelA > (*node)->label - linkNode->labelA < (*node)->label){
			case -1:
				linkNode = linkNode->nextNode;
				break;
			case 0:
				(*node)->label = linkNode->labelB;
				linkNode = linkNode->nextNode;
				node = &(*node)->nextNode;
				break;
		}
	}
	
	*node = createLabelNode(headerNode->label, NULL);
	
	return;
}