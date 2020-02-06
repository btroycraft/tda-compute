#include "btop_p.h"

void
reduce_image_basis(HeaderNode* pivotHeaderNode){
	
	HeaderNode** headerNode;
	
	while(pivotHeaderNode != NULL){
		convertLabelsListToArray(pivotHeaderNode);
		headerNode = &pivotHeaderNode->nextNode;
		while(*headerNode != NULL){
			
			if(containsLabel(*headerNode, pivotHeaderNode->labels[0])){
				
				addLabelArrayToList(pivotHeaderNode, *headerNode);
			
				if((*headerNode)->size == 0){
					*headerNode = deleteHeaderNode(*headerNode);
				}
			}
		}
		pivotHeaderNode = pivotHeaderNode->nextNode;
	}
	
	return;
}