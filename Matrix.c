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
    //free all the data collumns of the matrix.
    for (uint32_t i = 0; i< matrix->width; i++) {
        free(matrix->data[i]);
    }
    //free the array of collumns.
    free(matrix->data);
    //free the matrix.
    free(matrix);
}


