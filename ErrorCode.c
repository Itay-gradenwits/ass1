#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return !code;
}

const char* error_getErrorMessage(ErrorCode code) {
    if(code == ERROR_SUCCESS) {
        return "success";
    }
    else if (code == ERROR_MEMORY_ELLOCATION_FAIL) {
        return "memory ellocation fail";   
    }
    else if (code == ERROR_BAD_MATRIX_SIZES) {
        return "the sizes of the matrix are not good for this method";
    }
    else {
        return "not a defined error";
    }
}