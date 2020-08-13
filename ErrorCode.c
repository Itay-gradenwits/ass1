#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return !code;
}

const char* error_getErrorMessage(ErrorCode code) {
    if(code == ERROR_SUCCESS) {
        return "success";
    }
    else {
        return "not a defined error";
    }
}