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
    else {
        return "not a defined error";
    }
}