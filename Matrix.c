#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <stdint.h>

typedef struct Matrix {
    //an array of double arrays that represent a collumns array.
    double ** data;
    //the height of the matrix.
    uint32_t height;
    //the width of the matrix.
    uint32_t width;
}Matrix;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    
    //we cannot create a matrix with less than 1 row or collumn.
    if (height <= 0 || width <= 0) {
        return ERROR_BAD_MATRIX_SIZES;
    }

    //try to allocate a memory for the matrix.
    *matrix = malloc(sizeof(Matrix));

    //if it fails return a matching error.
    if (*matrix == NULL) {
        return ERROR_MEMORY_ELLOCATION_FAIL;
    }

    //if it succeed initial the fields of the matrix:
    (*matrix)->height = height;
    (*matrix)->width = width;
    
    //try to allocate the collumns array.
    (*matrix)->data = malloc(width * sizeof(double*));

    //if it failed free the matrix and return the matching Error.
    if ((*matrix)->data == NULL) {
        free(*matrix);
        return ERROR_MEMORY_ELLOCATION_FAIL;
    }
    
    //try the allocate the collumns of the matrix and initial them to 0.
    for(uint32_t i = 0; i < width; i ++) {
        (*matrix)->data[i] = calloc(height, sizeof(double));
        //if one of the allocate did not succeeded we need to free all the memory of the matrix we already got.
        if((*matrix)->data[i] == NULL) {
            //free all the collumns we succeeded to allocate.
            for(uint32_t j = 0; j < i; j++) {
                free((*matrix)->data[j]);
            }
            //free the array of the collumns.
            free((*matrix)->data);
            //free the matrix
            free(*(matrix));
            //return the matching error.
            return ERROR_MEMORY_ELLOCATION_FAIL;
        }
    }
    //if the allocations and initials succeeded.
     return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    //if the source matrix is null we can not copy it.
    if(source == NULL) {
        return ERROR_NULL_POINTER;
    }
    //initial the result matrix and save the output error.
    ErrorCode initialError = matrix_create(result, source->height, source->width);
    //if the saved error is ERROR_BAD_MATRIX_SIZES return it too.
    if (initialError == ERROR_BAD_MATRIX_SIZES) {
        return ERROR_BAD_MATRIX_SIZES;
    }
     //if the saved error is ERROR_MEMORY_ELLOCATION_FAIL return it too.
    if (initialError == ERROR_MEMORY_ELLOCATION_FAIL) {
        return ERROR_MEMORY_ELLOCATION_FAIL;
    }
    //if it is ERROR_SUCCESS copy all the values from the source matrix to the result matrix and return ERROR_SUCCESS.
    for(uint32_t i =0; i < source->height; i++) {
        for(uint32_t j =0; j< source->width; j++) {
            matrix_setValue(result, i, j, source->data[i][j]);
        }
    }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    //if the matrix is the null we cant destroy it.
    if(matrix == NULL) {
        return;
    }
    //free all the data collumns of the matrix.
    for (uint32_t i = 0; i< matrix->width; i++) {
        free(matrix->data[i]);
    }
    //free the array of collumns.
    free(matrix->data);
    //free the matrix.
    free(matrix);
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    //if the matrix pointer is null return the matching ERROR.
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if not, put the height of the matrix at result* and return ERROR_SUCCESS.
    *result = matrix->height;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    //if the matrix pointer is null return the matching ERROR.
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if not, put the width of the matrix at result* and return ERROR_SUCCESS.
    *result = matrix->width;
    return ERROR_SUCCESS;;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value) {
    //if the provided matrix pointer is null return the mathcing ERROR.
    if (matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if the provided indexes are not matching to the matrix return the matching ERROR.
    if (colIndex < 0 || colIndex >= matrix->width  || rowIndex < 0 || rowIndex >= matrix->height ) {
        return ERORR_BAD_INDEXES;
    }
    //if we can change the data(we didnt return any other error) change the boot in the matrix that matches to the indexes, to be value
    // and return ERROR_SUCCESS. 
    matrix->data[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value ){
     //if the provided matrix pointer is null return the mathcing ERROR.
    if (matrix == NULL || value == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if the provided indexes are not matching to the matrix return the matching ERROR.
    if (colIndex < 0 || colIndex >= matrix->width  || rowIndex < 0 || rowIndex >= matrix->height ) {
        return ERORR_BAD_INDEXES;
    }
    //if we can get the data(we didnt return any other error) change value to be the boot in the matrix that matches to the indexes,
    // and return ERROR_SUCCESS. 
    *value =  matrix->data[rowIndex][colIndex];
     return ERROR_SUCCESS;     
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    //if the provided matrix pointer is null return the mathcing ERROR.
    if (lhs == NULL || rhs == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if the 2 matrixs are not at the same sizes.
    if (lhs->height != rhs->height || lhs->width != rhs->width) {
        return ERROR_BAD_MATRIX_SIZES;
    }

    //try to inital a new matrix to result and save the output ERROR.
    ErrorCode InitialError = matrix_create(result, lhs->height, lhs->width);
    //if the initial fails because of a bad sizes of the 2 matrix return the matching error.
    if(InitialError == ERROR_BAD_MATRIX_SIZES) {
        return ERROR_BAD_MATRIX_SIZES;
    }
     //if the initial fails because of a memory ellocation fail return the matching error.
    if(InitialError == ERROR_MEMORY_ELLOCATION_FAIL) {
        return ERROR_MEMORY_ELLOCATION_FAIL;
    }
    //if the inital succeeded(there cannot be other ERRORS from this function ) build the new matrix in a way that every boot in
    //the result matrix is a sum of the 2 matching boot int the lhs and rhs matrixs.
    for(uint32_t colIdx; colIdx < lhs->width; colIdx++) {
        for(uint32_t rowIdx; rowIdx< lhs->height; rowIdx++) {
            matrix_setValue(*result, rowIdx, colIdx, lhs->data[rowIdx][colIdx] + rhs->data[rowIdx][colIdx]);
        }
    }
}
