struct bdry_mat{

	bdry_col *nextCol;
	int numIndices;
}

struct bdry_col{

	bdry_col *nextCol;
	bdry_row *nextRow;
	float parameter;
}

struct bdry_row{

	bdry_row *nextRow;
	int *indices;
}

bdry_col* bdry_createCol(bdry_col *nextCol, bdry_row *nextRow, float parameter){
	
	//	This function creates a new column node in the boundary matrix copying the
	//	column address supplied as input. The address for the new node is returned. The
	//	pointer to the initial row node for the column is set according to input, as is the
	//	associated parameter value.
	
	bdry_col *newCol = (bdry_col*) malloc(sizeof(bdry_col));
	newCol->nextCol = nextCol;
	
	newCol->nextRow = nextRow;
	newCol->parameter = parameter;
	
	return newCol;
}

int bdry_deleteCol(bdry_col *col){
	
	//	This function deletes the column node at the provided address. The
	//	return value is the address of the next column originally referenced
	//	by the deleted node. 
	
	bdry_col *nextCol = col->nextCol;
	
	free(col);
	
	return nextCol;
}

bdry_row* bdry_createRow(bdry_row *nextRow, int *indices){
	
	//	This function creates a new row node in the boundary matrix copying the row
	//	address supplied as input. The address for the new node is returned. The pointer
	//	to the array of indices is initially set according to the input.
	
	bdry_row *newRow = (bdry_row*) malloc(sizeof(bdry_row));
	newRow->nextRow = nextRow;
	
	newRow->indices = indices;
	
	return newRow;
}

int bdry_deleteRow(bdry_row *row){
	
	//	This function deletes the row node at the provided address. The return
	//	value is the address for the next node contained in the deleted node.
	
	bdry_row *nextRow = row->nextRow;
	
	free(row);
	
	return nextRow;
}

int* bdry_createIndices(int numIndices){
	
	//	This function allocates an integer array according to the input length and
	//	returns the address to the initial array value.
	
	return (int*) malloc(numIndices*sizeof(int));
}

int bdry_deleteIndices(int *indices){
	
	//	This function deletes the integer array located at the provided address.
	
	free(indices);
	
	return 1;
}

int bdry_addColToCol(bdry_col *col, bdry_col *colToAdd, int numIndices){	
	
	//	This function performs addition mod 2 between the two provided columns
	//	and replaces the column located at the first address provided. numIndices
	//	is the length of the simplices referenced by each node in the column.
	
	bdry_row **row = &(col->nextRow);
	bdry_row *rowToAdd = colToAdd->nextRow;
	
	while(*row != NULL && rowToAdd != NULL){

		switch(bdry_compareIndices(rowToAdd->indices, (*row)->indices, numIndices)){
			case -1:
				*row = bdry_createRow(*row, rowToAdd->indices);
				row = &((row*)->nextRow);
				rowToAdd = rowToAdd->nextRow;
				break;
			case 0:
				bdry_deleteIndices((*row)->indices);
				*row = bdry_deleteRow(*row);
				rowToAdd = rowToAdd->nextRow;
				break;
			case 1:
				rowToAdd = rowToAdd->nextRow;
				break;
		}
	}

	if(rowToAdd == NULL){
		return 1;
	} else if(*row == NULL){
		while(rowToAdd != NULL){
			*row = bdry_createRow(NULL, rowToAdd->indices);
			rowToAdd = rowToAdd->nextRow;
		}	
	}
}

int bdry_compareIndices(int indices1[], int indices2[], int numIndices){
{
	
	// This function compares two arrays of indices lexographically. numIndices is the length
	// of each integer array. Arrays must be of comparable size. Output is -1 if the first
	// input is ordered first lexographically, 0 if the two are the same, and 1 if the second
	// array is first.
	
	int i;
	
	for(i = 0; i < numIndices; ++i){
		if(indices1[i] < indices2[i]){
			return -1;
		} else if(indices1[i] > indices2[i]){
			return 1;
		}
	}
	
	return 0;
}


