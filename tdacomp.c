#include <pthread.h>

#define COLUMN_POOL_PAGE_SIZE 10
#define ROW_POOL_PAGE_SIZE 10

#define COMPLETE_CANCELLATION 1
#define LARGER 1
#define LESS_THAN_OR_EQUAL 0

typedef struct{
	col colInit;
}
mat;

typedef struct{
	col* colNext;
	row rowInit;
	simp* simp;
	pthread_mutex_t mutex;
}
col;

typedef struct{
	row* rowNext;
	simp* simp;
}
row;

typedef struct{
	simp* simpNext;
	int indexArray;
}
simp;

typedef struct{
	col* colInit;
	col* colFinal;
	void* allocInit;
	int sizeCurrent;
	int sizeTotal;
	pthread_mutex_t_mutex;
}
col_pool_shared;

typedef struct{
	col* colInit;
	col* colFinal;
	col* colReturnInit;
	col* colReturnFinal;
	int sizeCurrent;
	int sizeTotal;
	col_pool_shared* poolShared;
}
col_pool_thread;

typedef struct{
	row* rowInit;
	row* rowFinal;
	void* allocInit;
	int sizeCurrent;
	int sizeTotal;
	pthread_mutex_t mutex;
}
row_pool_shared;

typedef struct{
	row* rowInit;
	row* rowReturnInit;
	row* rowFinal;
	row* rowReturnFinal;
	int sizeCurrent;
	int sizeTotal;
	row_pool_shared* poolShared;
}
row_pool_thread;

typedef struct{
	simp* simpInit;
	void* allocInit;
	int sizeTotal;
	int sizeArray;
	pthread_mutex_t mutex;
}
simp_pool_shared;

static void
allocate_more_columns_to_shared_pool(col_pool_shared* columnPoolShared, int numberOfColumnsToAllocate){

	void** allocation = (void**) malloc(sizeof(void*) + numberOfColumnsToAllocate * sizeof(col));
	col* columnInitial = (col*) allocation + sizeof(void*);
	col* columnCurrent = columnInitial;
	col* columnNext;

	*allocation = columnPoolShared->allocInit;
	columnPoolShared->allocInit = (void*) allocation;

	for(int columnCounter = 1; columnCounter < numberOfColumnsToAllocate; columnCounter++){

		columnNext = columnCurrent + sizeof(col);
		columnCurrent->colNext = columnNext;
		columnCurrent = columnNext;
	}

	columnCurrent->colNext = NULL;

	if(columnPoolShared->sizeCurrent == 0){

		columnPoolShared->colInit = columnInitial;
	} else {

		columnPoolShared->colFinal->colNext = columnInitial;
	}

	columnPoolShared->colFinal = columnCurrent;

	columnPoolShared->sizeTotal += numberOfColumnsToAllocate;
	columnPoolShared->sizeCurrent += numberOfColumnsToAllocate;

	return;
}

static void
allocate_more_rows_to_shared_pool(row_pool_shared* rowPoolShared, int numberOfRowsToAllocate){

	void** allocation = (void**) malloc(sizeof(void*) + numberOfRowsToAllocate * sizeof(row));
	row* rowInitial = (row*) allocation + sizeof(void*);
	row* rowCurrent = rowInitial;
	row* rowNext;

	*allocation = rowPoolShared->allocInit;
	rowPoolShared->allocInit = (void*) allocation;

	for(int rowCounter = 1; rowCounter < numberOfRowsToAllocate; rowCounter++){

		rowNext = rowCurrent + sizeof(row);
		rowCurrent->rowNext = rowNext;
		rowCurrent = rowNext;
	}

	rowCurrent->rowNext = NULL;

	if(rowPoolShared->sizeCurrent == 0){

		rowPoolShared->rowInit = rowInitial;
	} else {

		rowPoolShared->rowFinal->rowNext = rowInitial;
	}

	rowPoolShared->rowFinal = rowCurrent;

	rowPoolShared->sizeTotal += numberOfRowsToAllocate;
	rowPoolShared->sizeCurrent += numberOfRowsToAllocate;

	return;
}

static void
allocate_more_simplices_to_shared_pool(simp_pool_shared* simplexPoolShared, int numberOfSimplicesToAllocate, int sizeIndexArray){

	void** allocation = (void**) malloc(sizeof(void*) + numberOfSimplicesToAllocate * (sizeof(simp*) + sizeIndexArray * sizeof(int)));
	simp* simplexInitial = (simp*) allocation + sizeof(void*);
	simp* simplexCurrent = simplexInitial;
	simp* simplexNext;

	*allocation = simplexPoolShared->allocInit;
	simplexPoolShared->allocInit = (void*) allocation;

	for(int simplexCounter = 0; simplexCounter < numberOfSimplicesToAllocate; simplexCounter++){

		simplexNext = simplexCurrent + sizeof(simp*) + sizeIndexArray * sizeof(int);
		simplexCurrent->simpNext = simplexNext;
		simplexCurrent = simplexNext;
	}

	simplexCurrent->simpNext = NULL;
	simplexPoolShared->simpInit = simplexInitial;

	simplexPoolShared->sizeTotal += numberOfSimplicesToAllocate;

	return;
}

static void
get_more_columns_from_shared_pool(col_pool_thread* columnPoolThread, col_pool_shared* columnPoolShared, int numberOfColumnsToGet){

	col* columnPointer;

	pthread_mutex_lock(columnPoolShared->mutex);

	if(columnPoolShared->sizeCurrent < numberOfColumnsToGet){

		allocate_more_columns_to_shared_pool(columnPoolShared, columnPoolShared->sizeTotal);
	}

	columnPointer = columnPoolShared->colInit;
	columnPoolThread->colInit = columnPointer;

	for(int columnCounter = 1; columnCounter < numberOfColumnsToGet; columnCounter++){

		columnPointer = columnPointer->colNext;
	}

	columnPoolThread->colFinal = columnPointer;
	columnPointer = columnPointer->colNext;

	columnPoolShared->colInit = columnPointer;

	pthread_mutex_unlock(columnPoolShared->mutex);

	columnPoolThread->sizeCurrent = numberOfColumnsToGet;
	columnPoolThread->sizeTotal += numberOfColumnsToGet;

	return;
}

static void
get_more_rows_from_shared_pool(row_pool_thread* rowPoolThread, row_pool_shared* rowPoolShared, int numberOfRowsToGet){

	row* rowPointer;

	pthread_mutex_lock(rowPoolShared->mutex);

	if(rowPoolShared->sizeCurrent < numberOfRowsToGet){

		allocate_more_rows_to_shared_pool(rowPoolShared, rowPoolShared->sizeTotal);
	}

	rowPointer = rowPoolShared->rowInit;
	rowPoolThread->rowInit = rowPointer;

	for(int rowCounter = 1; rowCounter < numberOfRowsToGet; rowCounter++){

		rowPointer = rowPointer->rowNext;
	}

	rowPoolThread->rowFinal = rowPointer;
	rowPointer = rowPointer->rowNext;

	rowPoolShared->rowInit = rowPointer;

	pthread_mutex_unlock(rowPoolShared->mutex);

	rowPoolThread->sizeCurrent = numberOfRowsToGet;
	rowPoolThread->sizeTotal += numberOfRowsToGet;

	return;
}

static void
get_simplex_from_shared_pool(simp_pool_shared* simplexPoolShared){

	simp* simplexPointer;

	if(simplexPoolShared->simpInit == NULL){

		allocate_more_simplices_to_shared_pool(simplexPoolShared, simplexPoolShared->sizeTotal, simplexPoolShared->sizeArray);
	}

	simplexPointer = simplexPoolShared->simpInit;
	simplexPoolShared->simpInit = simplexPointer->simpNext;

	return simplexPointer;
}

static col*
get_column_from_thread_pool(col_pool_thread* columnPoolThread){

	// Gets a new column node from the thread pool. If necessary, gets more
	// column nodes from the shared pool. Requires a	destination pointer to hold
	// the location of the new node, along with a pointer to the thread pool

	col* columnPointer;

	if(columnPoolThread->sizeCurrent == 0){

		get_more_columns_from_shared_pool(columnPoolThread, columnPoolThread->poolShared, columnPoolThread->sizeTotal);
	}

	if(columnPoolThread->sizeCurrent > columnPoolThread->sizeTotal){

		columnPointer = columnPoolThread->colReturnInit;
		columnPoolThread->colReturnInit = columnPointer->colReturnNext;
	} else {

		columnPointer = columnPoolThread->colInit;
		columnPoolThread->colInit = columnPointer->colNext;
	}

	columnPoolThread->sizeCurrent--;

	return columnPointer;
}

static row*
get_row_from_thread_pool(row_pool_thread* rowPoolThread){

	// Gets a new row node from the thread pool. If necessary, gets more row nodes from the shared pool. Requires a	destination pointer to hold the location of the new node, along with a pointer to the thread pool

	row* rowPointer;

	if(rowPoolThread->sizeCurrent == 0){

		get_more_rows_from_shared_pool(rowPoolThread, rowPoolThread->poolShared, rowPoolThread->sizeTotal);
	}

	if(rowPoolThread->sizeCurrent > rowPoolThread->sizeTotal){

		rowPointer = rowPoolThread->rowReturnInit;
		rowPoolThread->rowReturnInit = rowPointer->rowReturnNext;
	} else {

		rowPointer = rowPoolThread->rowInit;
		rowPoolThread->rowInit = rowPointer->rowNext;
	}

	rowPoolThread->sizeCurrent--;

	return rowPointer;
}

static void
return_column_to_thread_pool(col* columnToReturn, col_pool_thread* columnPoolThread){

	// Returns a given column node to the thread pool. Requires a pointer to the returned column and thread pool

	if(columnPoolThread->sizeCurrent < columnPoolThread->sizeTotal){

		columnToReturn->colNext = columnPoolThread->colInit;
		columnPoolThread->colInit = columnToReturn;

		if(columnPoolThread->sizeCurrent == 0){

			columnPoolThread->colFinal = columnToReturn;
		}
	} else {

		columnToReturn->colNext = columnPoolThread->colReturnInit;
		columnPoolThread->colReturnInit = columnToReturn;

		if(columnPoolThread->sizeCurrent == columnPoolThread->sizeTotal){

			columnPoolThread->colReturnFinal = columnToReturn;
		}
	}

	columnPoolThread->sizeCurrent++;

	return;
}

static void
return_row_to_thread_pool(row* rowToReturn, row_pool_thread* rowPoolThread){

	// Returns a given row node to the thread pool. Requires a pointer to the returned row and thread pool

	if(rowPoolThread->sizeCurrent < rowPoolThread->sizeTotal){

		rowToReturn->rowNext = rowPoolThread->rowInit;
		rowPoolThread->rowInit = rowToReturn;

		if(rowPoolThread->sizeCurrent == 0){

			rowPoolThread->rowFinal = rowToReturn;
		}
	} else {

		rowToReturn->rowNext = rowPoolThread->rowReturnInit;
		rowPoolThread->rowReturnInit = rowToReturn;

		if(rowPoolThread->sizeCurrent == rowPoolThread->sizeTotal){

			rowPoolThread->rowReturnFinal = rowToReturn;
		}
	}

	rowPoolThread->sizeCurrent++;

	return;
}

static void
return_columns_to_shared_pool(col_pool_thread* columnPoolThread, columnPoolShared* columnPoolShared){

	pthread_mutex_lock(columnPoolShared->mutex);

	if(columnPoolShared->sizeCurrent == 0){

		columnPoolShared->colInit = columnPoolThread->colReturnInit;
	} else {

		columnPoolShared->colFinal->colNext = columnPoolThread->colReturnInit;
	}

	columnPoolShared->colFinal = columnPoolThread->colReturnFinal;

	columnPoolShared->sizeCurrent += columnPoolThread->sizeCurrent - columnPoolThread->sizeTotal;

	pthread_mutex_unlock(columnPoolShared->mutex);

	columnPoolThread->sizeCurrent = columnPoolThread->sizeTotal;

	return;
}

static void
return_rows_to_shared_pool(row_pool_thread* rowPoolThread, rowPoolShared* rowPoolShared){

	pthread_mutex_lock(rowPoolShared->mutex);

	if(rowPoolShared->sizeCurrent == 0){

		rowPoolShared->rowInit = rowPoolThread->rowReturnInit;
	} else {

		rowPoolShared->rowFinal->rowNext = rowPoolThread->rowReturnInit;
	}

	rowPoolShared->rowFinal = rowPoolThread->rowReturnFinal;

	rowPoolShared->sizeCurrent += rowPoolThread->sizeCurrent - rowPoolThread->sizeTotal;

	pthread_mutex_unlock(rowPoolShared->mutex);

	rowPoolThread->sizeCurrent = rowPoolThread->sizeTotal;

	return;
}

static int
compare_indices_lexicographically(int* arrayIndexFirst, int* arrayIndexSecond, int sizeIndexArray){

	for(int counter = 0; counter < sizeIndexArray; counter++){

		if(arrayIndexFirst[counter] < arrayIndexSecond[counter]){

			return -1;
		}
		if(arrayIndexFirst[counter] > arrayIndexSecond[counter]){

			return 1;
		}
	}

	return 0;
}

static void
reduce_column_against_column(col* columnToReduce, col* columnToReduceAgainst, row_pool_thread* rowPoolThread){

	return;
}

void
incorporate_column_into_matrix(col* columnToIncorporate, mat* boundaryMatrix, col_pool_thread* columnPoolThread, row_pool_thread* rowPoolThread){

	// This function takes an existing column in list form and places the column into an existing boundary matrix. Insertion and reduction are performed based on a sorting criterion. Every column less than the working column is used to reduce the working column. After reduction, the working column is added into the matrix and used to reduce the remaining columns

	col* columnPrevious, columnCurrent;

	// Initializes the active columns and acquires necessary mutexes

	columnPrevious = &(boundaryMatrix->colInit);
	pthread_mutex_lock(columnPrevious->mutex);
	columnCurrent = columnPrevious->colNext;

	while(columnCurrent != NULL){

		// Reduce the working column against the existing matrix columns until column parameter of the working parameter is lesser than the matrix column or the end of the matrix is reached

		if(compareSimplices(columnToIncorporate->simplex, columnCurrent->simplex == LESS_THAN){

			break;
		}

		// Lock mutex for current column

		pthread_mutex_lock(columnCurrent->mutex);

		reduce_column_against_column(columnToIncorporate, columnCurrent, rowPool);

		if(columnToIncorporate->rowInit->rowNext == NULL){

			// If the working column is completely canceled, release mutexes and return working column to thread pool

			pthread_mutex_unlock(columnPrevious->mutex);
			pthread_mutex_unlock(columnCurrent->mutex);

			return_column_to_thread_pool(columnToIncorporate, columnPoolThread);

			return;
		}

		pthread_mutex_unlock(columnPrevious->mutex);

		columnPrevious = columnCurrent;
		columnCurrent = columnCurrent->colNext;
	}

	// Add working column into the matrix at current location. Every preceding column is lesser or equal, and every subsequent column is greater

	columnPrevious->colNext = columnToIncorporate;
	columnToIncorporate->colNext = columnCurrent;

	// Inititialize and lock the mutex for the new column

	pthread_mutex_init(columnToIncorporate->mutex);
	pthread_mutex_lock(columnToIncorporate->mutex);

	// Release mutex on previous column

	pthread_mutex_unlock(columnPrevious->mutex);

	// Make a new copy of the working column so other threads can have access

	columnPrevious = columnToIncorporate;

	columnToIncorporate = copy_column(columnPrevious, columnPoolThread, rowPoolThread);

	while(columnCurrent != NULL){

		pthread_mutex_lock(columnCurrent->mutex);

		// Reduce the succeeding matrix columns using the working column

		reduce_column_against_column(columnCurrent, columnToIncorporate, rowPoolThread, columnPoolThread);

		if(columnCurrent->rowInit->rowNext == NULL){

			// If the current column is completely canceled, remove and keep previous column the same

			columnPrevious->colNext = columnCurrent->colNext;

			pthread_mutex_unlock(columnCurrent->mutex);
			pthread_mutex_destroy(columnCurrent->mutex);

			return_column_to_thread_pool(columnCurrent, columnPoolThread);

			columnCurrent = columnPrevious->colNext;
		} else {

			// Else move the previous column up one

			pthread_mutex_unlock(columnPrevious->mutex);

			columnPrevious = columnCurrent;
		}
	}

	// Return surplus nodes to the thread pool

	return_columns_to_shared_pool(columnPoolThread, columnPoolThread->poolShared);
	return_rows_to_shared_pool(rowPoolThread, rowPoolThread->poolShared);

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
