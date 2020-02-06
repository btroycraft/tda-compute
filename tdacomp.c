#include <pthread.h>

#define COLUMN_POOL_PAGE_SIZE 10
#define ROW_POOL_PAGE_SIZE 10

typedef struct{
	col colInit;
}
mat;

typedef struct{
	col* colNext;
	row rowInit;
	simplex* simplex;
	pthread_mutex_t mutex;
}
col;

typedef struct{
	row* rowNext;
	simplex* simplex;
}
row;

void
incorporate_column_into_matrix(col* columnToIncorporate, mat* boundaryMatrix,
	col* columnPoolInitial, col* columnPoolMarginInitial, int* columnPoolMarginSize, int* numberOfColumnPoolPagesToRequest,
	row* rowPoolInitial, row* rowPoolMarginInitial, int* rowPoolMarginSize, int* numberOfRowPoolPagesToRequest){
	
	// This function takes a column an existing column in list form and places the column into an existing boundary matrix
	// Insertion and reduction are performed based on a sorting criterion
	// Every column less than the working column is used to reduce the working column
	// After reduction, the working column is added into the matrix and used to reduce the remaining columns
	
	col* columnPrevious, columnCurrent, columnNext;
	
	// Initializes the active columns and acquires necessary mutexes
	
	columnPrevious = &(boundaryMatrix->colInit);
	pthread_mutex_lock(columnPrevious->mutex);
	columnCurrent = columnPrevious->colNext;
	
	if(columnCurrent == NULL){
		
		// If initial column hasn't been created yet, just add the working column to the matrix
		
		columnPrevious->colNext = columnToIncorporate;
		pthread_mutex_unlock(columnPrevious->mutex);
		
		// Return nodes to shared pool
		
		return_column_pool(columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize);
		return_row_pool(rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize);
		
		return;
	}
	
	pthread_mutex_lock(columnCurrent->mutex);
	columnNext = columnCurrent->colNext;
	
	if(columnNext != NULL){
		
		pthread_mutex_lock(columnNext->mutex);
	}
	
	while(columnCurrent != NULL && compareSimplexParameters(columnToIncorporate->simplex, columnCurrent->simplex) >= 0){
		
		// Reduce the working column against the matrix columns until simplex parameter is lesser
		
		columnNext = columnCurrent->colNext;
		if(columnNext != NULL){
			
			pthread_mutex_lock(columnNext->mutex);
		}
		
		if(reduce_column_against_column(columnToIncorporate, columnCurrent,
			rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize, numberOfRowPoolPagesToRequest) == 1){
			
			// If the working column is completely canceled, remove
			
			remove_column(columnToIncorporate, NULL, columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize);
			
			// Return nodes to shared pool
			
			return_column_pool(columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize);
			return_row_pool(rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize);
			
			return 0;
		}
		
		pthread_mutex_unlock(columnPrevious->mutex);
		
		columnPrevious = columnCurrent;
		columnCurrent = columnNext;
	}
	
	// Add working column into the matrix at its proper parameter level
	
	columnPrevious->colNext = columnToIncorporate;
	columnToIncorporate->colNext = columnCurrent;
	
	pthread_mutex_init(columnToIncorporate->mutex);
	pthread_mutex_lock(columnToIncorporate->mutex);
	
	pthread_mutex_unlock(columnPrevious->mutex);
	
	columnPrevious = columnToIncorporate;
	
	columnToIncorporate = copy_column(columnToIncorporate,
		columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize, numberOfColumnPoolPagesToRequest,
		rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize, numberOfRowPoolPagesToRequest);
	
	while(columnCurrent != NULL){
		
		// Reduce the succeeding matrix columns using the working column
		
		columnNext = columnCurrent->colNext;
		if(columnNext != NULL){
			
			pthread_mutex_lock(columnNext->mutex);
		}
		
		if(reduce_column_against_column(columnCurrent, columnToIncorporate,
			rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize, numberOfRowPoolPagesToRequest) == 1){
			
			// If the current column is completely canceled, remove and keep previous column the same
			
			pthread_mutex_unlock(columnCurrent->mutex);
			pthread_mutex_destroy(columnCurrent->mutex);
			
			remove_column(columnCurrent, columnPrevious, columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize);
		} else {
			
			// Else move the previous column up one
			
			pthread_mutex_unlock(columnPrevious->mutex);
			
			columnPrevious = columnCurrent;
		}
		
		columnCurrent = columnNext;
	}
	
	// Remove the temporary working column
	
	remove_column(columnToIncorporate, NULL,
		columnPoolInitial, columnPoolMarginInitial, columnPoolMarginSize,
		rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize);
	
	return;
}	

static void
remove_column(col* columnToRemove, col* columnPrevious,
	col* columnPoolInitial, col* columnPoolMarginInitial, int* columnPoolMarginSize,
	row* rowPoolInitial, row* rowPoolMarginInitial, int* rowPoolMarginSize){
	
	row* rowPrevious = &(columnToRemove->rowInit);
	
	while(rowPrevious->rowNext != NULL){
		
		remove_row(rowPrevious->rowNext, rowPrevious, rowPoolInitial, rowPoolMarginInitial, rowPoolMarginSize);
	}
	
	return;
}

static void
reduce_column_against_column(){	
	
	return;
}

static void
reduce_column_against_column(){	
	
	return;
}

void
bdry_add_pivot_col_to_col(bdry_col* colPivot, bdry_col* col, int lengthIndices){	
	
	bdry_row* rowArrayPivot = colPivot->rowNext;
	bdry_row** rowList = &(col->rowNext);
	int iter = 0;
	
	if(rowArrayPivot == NULL){
		return;
	}
	
	while(*rowList != NULL){
		
		if(bdry_compareIndices(rowArrayPivot[iter], (*rowList)->indices, lengthIndices)){
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
bdry_add_pivot_row_to_row(bdry_col* colPivot, bdry_col* col, int* indicesPivot, int lengthIndices){
	
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
bdry_compare_indices(int indices1[], int indices2[], int lengthIndices){
	
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
bdry_extract_pivot_indices(bdry_col* col, bdry_pivot** pivot, int lengthIndices){
	
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
convert_nonpivot_indices(bdry_col* col, bdry_pivot* pivot, int lengthIndices){
	
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
col_space_basis(bdry_mat* mat){
	
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