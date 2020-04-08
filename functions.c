typedef struct{
	bdry_col* colNext;
	int lengthIndices;
}
bdry_mat;

typedef struct{
	bdry_col* colNext;
	bdry_row* rowNext;
	int lengthCol;
	int* indices;
}
bdry_col;

typedef struct{
	bdry_row* rowNext;
	int* indices;
}
bdry_row;

typedef struct{
		bdry_pivot* pivotNext;
		int* indices;
		int* indicesPivot;
}
bdry_pivot;



bdry_mat*
bdry_createMat(bdry_mat* mat){
	
	return (bdry_mat*) memcpy(malloc(sizeof(bdry_mat)), mat, sizeof(bdry_mat));
}

bdry_col*
bdry_createCol(bdry_col* col){
	
	return (bdry_col*) memcpy(malloc(sizeof(bdry_col)), col, sizeof(bdry_col));
}

bdry_row*
bdry_createRow(bdry_row* row){
	
	return (bdry_row*) memcpy(malloc(sizeof(bdry_row)), row, sizeof(bdry_row));
}

bdry_pivot*
bdry_createPivot(bdry_pivot* pivot){
	
	return memcpy(malloc(sizeof(bdry_pivot)), pivot, sizeof(bdry_pivot));
}
	
int*
bdry_createIndices(int* indices, int lengthIndices){
	
	return memcpy(malloc(lengthIndices*sizeof(int)), &indices, sizeof(lengthIndices*sizeof(int)));
}

void
bdry_deleteMat(bdry_mat* mat){
	
	free(mat);
	
	return;
}

bdry_col*
bdry_deleteCol(bdry_col* col){
	
	bdry_col* colNext = col->colNext;
	
	free(col);
	
	return colNext;
}

bdry_row*
bdry_deleteRow(bdry_row* row){
	
	bdry_row* rowNext = row->rowNext;
	
	free(row);
	
	return rowNext;
}

bdry_pivot*
bdry_deletePivot(bdry_pivot* pivot){
	
	bdry_pivot* pivotNext = pivot->pivotNext;
	
	free(pivot);
	
	return pivotNext;
}

void
bdry_deleteIndices(int* indices){
	
	//	This function deletes the integer array located at the provided address.
	
	free(indices);
	
	return;
}



void
bdry_convertRowListToArray(bdry_col* col){

	bdry_row* rowList = col->rowNext;
	int** rowArray = (int**) malloc(col->lengthCol*sizeof(int*));
	int iter = 0;
	
	while(rowList != NULL){
		
		rowArray[iter] = rowList->indices;
		
		rowList = bdry_deleteRow(rowList);
		++iter;
	}
	
	return;
}

void
bdry_addPivotColToCol(bdry_col* colPivot, bdry_col* col, int lengthIndices){	
	
	bdry_row* rowArrayPivot = colPivot->rowNext;
	bdry_row** rowList = &(col->rowNext);
	int iter = 0;
	
	if(rowArrayPivot == NULL){
		return;
	}
	
	while(*rowList != NULL){
		
		switch(bdry_compareIndices(rowArrayPivot[iter], (*rowList)->indices, lengthIndices)){
			case -1:
				return;
			case 0:
				goto LOOP_EXIT;
			case 1:
				rowList = &((rowList*)->rowNext);
				break;
		}
	}
	LOOP_EXIT:
	
	while(*rowList != NULL && iter < colPivot->lengthCol){

		switch(bdry_compareIndices(rowArrayPivot[iter], (*rowList)->indices, lengthIndices)){
			case -1:
				*rowList = bdry_createRow(&(bdry_row){.rowNext = *rowList, .indices = rowArrayPivot[iter]});
				rowList = &((*rowList)->rowNext);
				++iter;
				++(col->lengthCol);
				break;
			case 0:
				if((*rowList)->indices != rowArrayPivot[iter]){
					bdry_deleteIndices((*rowList)->indices);
				}
				*rowList = bdry_deleteRow(*rowList);
				++iter;
				--(col->lengthCol);
				break;
			case 1:
				rowList = &((rowList*)->rowNext);
				break;
		}
	}

	while(iter < colPivot->lengthCol){
		*rowList = bdry_createRow(&(bdry_row){.rowNext = *rowList, .indices = rowArrayPivot[iter]});
		rowList = &((*rowList)->rowNext);
		++iter;
	}
	
	return;
}

void
bdry_addPivotRowToRow(bdry_col* colPivot, bdry_col* col, int* indicesPivot, int lengthIndices){
	
	bdry_row* rowArrayPivot = colPivot->rowNext;
	bdry_row** rowList = &(col->rowNext);
	int iter = 0;
	
	while(*rowList != NULL){
		
		switch(bdry_compareIndices(indicesPivot, (*rowList)->indices, lengthIndices)){
			case -1:
				return;
			case 0:
				goto LOOP_EXIT;
			case 1:
				rowList = &((*rowList)->rowNext);
				break;
		}
	}
	return;
	
	LOOP_EXIT:
	
	rowList = &(col->rowNext);
	
	while(*rowList != NULL && iter < colPivot->lengthCol){
		
		switch(bdry_compareIndices(rowArrayPivot[iter], (*rowList)->indices, lengthIndices)){
			case -1:
				*rowList = bdry_createRow(&(bdry_row){.rowNext = *rowList, .indices = rowPivot[iter]});
				++(col->lengthCol);
				++iter;
				break;
			case 0:
				if((*rowList)->indices != rowArrayPivot[iter]){
					bdry_deleteIndices((*rowList)->indices);
				}
				*rowList = bdry_deleteRow(*rowList);
				--(col->lengthCol);
				++iter;
				break;
			case 1:
				rowList = &((*rowList)->rowNext);
				break;
		}
	}
	
	while(iter < colPivot->lengthCol){
		*rowList = bdry_createRow(&(bdry_row){.rowNext = NULL, .indices = rowArrayPivot[iter]});
		rowList = &((*rowList)->rowNext);
		++iter;
	}
	
	return;
}

int
bdry_compareIndices(int indices1[], int indices2[], int lengthIndices){
	
	// This function compares two arrays of indices lexicographically. lengthIndices is the length
	// of each integer array. Arrays must be of comparable size. Output is -1 if the first
	// input is ordered first lexicographically, 0 if the two are the same, and 1 if the second
	// array is first.
	
	int iter;
	
	for(iter = 0; iter < lengthIndices; ++iter){
		if(indices1[iter] < indices2[iter]){
			return -1;
		}
		if indices1[iter] > indices2[iter]){
			return 1;
		}
	}
	
	return 0;
}

int*
bdry_extractPivotIndices(bdry_col* col, bdry_pivot** pivot, int lengthIndices){
	
	bdry_row** row = &(col->rowNext);
	
	if(*pivot == NULL){
		*pivot = bdry_createPivot(&(bdry_pivot){.pivotNext = NULL, .indices = (*row)->indices, .indicesPivot = col->indices});
		*row = bdry_deleteRow(*row);
		--(col->lengthCol);
		return (*pivot)->indices;
	}
	
	while(*row != NULL && *pivot != NULL){
		
		switch(bdry_compareIndices((*row)->indices, (*pivot)->indices, lengthIndices)){
			case -1:
				*pivot = bdry_createPivot(&(bdry_pivot){.pivotNext = (*pivot)->pivotNext, .indices = (*row)->indices, .indicesPivot = col->indices});
				*row = bdry_deleteRow(*row);
				return (*pivot)->indices;
			case 0:
				pivot = &((*pivot)->pivotNext);
				row = &((row*)->rowNext);
				break;
			case 1:
				pivot = &((*pivot)->rowNext);
				break;
		}
	}
	
	return NULL;
}

void
bdry_convertNonPivotIndices(bdry_col* col, bdry_pivot* pivot, int lengthIndices){
	
	bdry_row** row = &(col->rowNext);
	
	while(*row != NULL){
		
		switch(bdry_compareIndices(pivot->indices, (*row)->indices, lengthIndices)){
			case -1:
				pivot = pivot->pivotNext;
				break;
			case 0:
				(*row)->indices = pivot->indicesPivot;
				pivot = pivot->pivotNext;
				row = &((*row)->rowNext);
				break;
		}
	}
	
	*row = bdry_createRow(&(bdry_row){.rowNext = NULL, .indices = col->indices});
	
	return;
}



void
bdry_colSpaceBasis(bdry_mat* mat){
	
	bdry_col* colPivot = mat->colNext;
	bdry_col** col;
	
	while(colPivot != NULL){
		bdry_convertRowListToArray(colPivot);
		col = &(colPivot->colNext);
		while(*col != NULL){
			bdry_addPivotColToCol(colPivot, *col, mat->lengthIndices);
			if((*col)->rowNext == NULL){
				*col = bdry_deleteCol(*col);
			}
		}
		colPivot = colPivot->nextCol;
	}
	
	return;
}

void
bdry_nullSpaceBasis(bdry_mat* mat){
	
	bdry_pivot* pivot = NULL;
	
	bdry_col** colPivot = &(mat->colNext);
	bdry_col* col;
	int* indicesPivot;
	
	while(*colPivot != NULL){
		
			indicesPivot = bdry_extractPivotIndices(*colPivot, &pivot, mat->lengthIndices);
			
			if(indicesPivot == NULL){
				
				bdry_convertNonPivotIndices(*colPivot, pivot, mat->lengthIndices);
				*colPivot = (*colPivot)->colNext;
				
			} else {
				
				bdry_convertRowListToArray(*colPivot);
				col = (*colPivot)->colNext;
				
				while(col != NULL){
					bdry_addPivotRowToRow(*colPivot, col, indicesPivot, mat->lengthIndices);
					col = col->colNext;
				}
				
				free((*colPivot)->rowNext);
				*colPivot = bdry_deleteCol(*colPivot);
			}
	}
	
	return;
}


bdry_getRipsSimplices(float[] matPairwise, int nrow, int dim, float parameterMax){
	
	int[] indices = (int*) malloc(dim*sizeof(int));
	int[] candidates = (int*) malloc(nrow*sizeof(int));
	int iter = 0;
	
bdry_isSimplexInRips(float[] matPairwise, int nrow, int[] indices, int lengthIndices, float parameterMax){
	
	int iter1, iter2;
	
	for(iter1 = 0; iter1 < lengthIndices-1; ++iter1){
		for(iter2 = iter1+1; iter2 < lengthIndices; ++iter2){
			if(matPairwise[indices[iter1]*nrow+indices[iter2]] > parameterMax)
		}
	}
}
	
	
	
	
	
	
	
}