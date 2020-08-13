#include "Matrix.h"
#include <stdint.h>
 struct Matrix {
    int ** data;
    uint32_t height;
    uint32_t width;
};

void matrix_destroy(PMatrix matrix) {
    for (uint32_t i = 0; i< matrix->width; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix->width);
    free(matrix->height);
}
