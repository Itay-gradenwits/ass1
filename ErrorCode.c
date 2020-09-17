#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return !code;
}
const char* error_getErrorMessage(ErrorCode code) {
    if(code == ERROR_SUCCESS) {
        return "success";
    }
    if (code == ERROR_MEMORY_ALLOCATION_FAIL) {
        return "memory ellocation fail";   
    }
    if (code == ERROR_BAD_MATRIX_SIZES) {
        return "the sizes of the matrix are not good for this method";
    }
    if (code == ERROR_NULL_POINTER) {
        return "the pointer provided is null";
    }
    else {
        return "not a defined error";
    }
}