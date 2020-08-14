#include "Matrix.h"
#include "ErrorCode.h"

#include<stdint.h>
#include <stdio.h>

ErrorCode initialize_matrix(const PMatrix matrix, const uint32_t height,
                            const uint32_t width) {
    uint32_t i = 0;
    uint32_t j = 0;
    ErrorCode result = ERROR_SUCCESS;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            result = matrix_setValue(matrix, i, j, i*j);
            if (!error_isSuccess(result)) {
                fprintf(stderr, "Error matrix_setValue: %s\n",
                        error_getErrorMessage(result));
                return result;
            }
        }
    }

    return ERROR_SUCCESS;
}

int main() {
    PMatrix x = NULL;
    PMatrix y = NULL;
    PMatrix xMultY = NULL;
    uint32_t height;
    uint32_t width;
    double value;
    matrix_create(&x,3,2);
    matrix_create(&y,2,3);
    if (x == NULL || y == NULL) {
        printf("Error in matrix_create\n");
        printf("Make sure u are doing\n *matrix = pm\n and not\n matrix = &pm\nwhen pm is the matrix u are creating in the function\n");
        return 0;
    }
    initialize_matrix(x,3,2);
    initialize_matrix(y,2,3);
    ErrorCode c = matrix_multiplyMatrices(&xMultY,y,x);
    if (!error_isSuccess(c)) {
        printf("\nProbably didn't make adjustments for multiplying matrices with sizes 3x2 and 2x3 for example\n");
        return 0;
    }
    matrix_getHeight(xMultY,&height);
    matrix_getWidth(xMultY,&width);
    if(height != 2 || width != 2){
        printf("Error in getHeight or getWidth\n");
        return 0;
    }
    matrix_getValue(xMultY,1,1,&value);
    double error = 0.0000001;
    if (!(value - 5 < error || 5 - value < error)) {
        printf("Error in multiplication definition in multiplyMatrices\n");
        return 0;
    }
    matrix_multiplyWithScalar(xMultY,2);
    matrix_getValue(xMultY,1,1,&value);
    if (!(value - 10 < error || 10 - value < error)) {
        printf("Error in multiplication with scalar\n");
        return 0;
    }
    PMatrix a = NULL;
    PMatrix b = NULL;
    PMatrix aPb =NULL;
    matrix_create(&a,2,2);
    matrix_create(&b,2,2);
    initialize_matrix(a,2,2);
    initialize_matrix(b,2,2);
    ErrorCode e = matrix_add(&aPb,a,b);
    if (!error_isSuccess(e)) {
        printf("\nError in matrix_add, adding two matrices sized 2x2 should be fine\n");
        return 0;
    }
    matrix_getValue(aPb,1,1,&value);
    if (!(value - 2 < error || 2 - value < error)) {
        printf("Error in matrix_add, adding wasn't correct");
        return 0;
    }
    printf("SUCCESS!!\n");
    matrix_destroy(x);
    matrix_destroy(y);
    matrix_destroy(xMultY);
    return 0;
}