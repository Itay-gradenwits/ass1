#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <stdint.h>

typedef struct Matrix {
    double ** data;
    uint32_t height;
    uint32_t width;
}Matrix;


ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    
    if(height < 0 || width < 0) {
        return ERROR_BAD_MATRIX_SIZES;
    }

    *matrix = malloc(sizeof(Matrix));
    if(*matrix == NULL) {
        return ERROR_MEMORY_ELLOCATION_FAIL;
    }
    (*matrix)->height = height;
    (*matrix)->width = width;

    for(uint32_t i = 0; i < width; i ++) {
        (*matrix)->data[i] = calloc(height, sizeof(double));
        if((*matrix)->data[i] == NULL) {
            for(uint32_t j = 0; j < i; j++) {
                free((*matrix)->data[j]);
            }
            free((*matrix)->data);
            free(*(matrix));
            return ERROR_MEMORY_ELLOCATION_FAIL;
        }
    }
}

void matrix_destroy(PMatrix matrix) {
    for (uint32_t i = 0; i< matrix->width; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}


