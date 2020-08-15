ErrorCode.c:

* bool error_isSuccess(ErrorCode code) :
return !code because if the ErroCode is success it will be 0 (=false) so we need to return !0 =1 (=true).
   
* const char* error_getErrorMessage(ErrorCode code) :
   find the kind of error and return a nice message to describe it

* typedef struct Matrix {}Matrix :
create the struct matrix that contians 3 fiels: height of the matrix (uint32_t), width of the matrix (uint32_t) 
and the data of the matrix (double**).

* ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) :
check if all the args we got are good (right height and width(>0)).
try to allocate a struct matrix at the heep. if it faild return the right error and free all the memory we already allocate.
upate all the fields if the allocate succeeded and try to allocate an array for the rows.
if it faild return the right error and free all the memory we already allocate.
if it succeeded try to allocate the actual rows.
if it faild return the right error and free all the memory we already allocate.

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) :
check if the source matrix is good matrix(not null).
try to initial result with create matrix.
if it failed return the right error.
else copy every boot of the source matrix to result matrix.

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value ) :
check if the matrix is not null.
check if the indexes are existing in this matrix.
check if value is not null.
if one of those checks failed return the right error.
else copy the value in those indexes in the matrix to "*value"

void matrix_destroy(PMatrix matrix) :
check if the matrix is not null.
free first the roes of the matrix, than free the rows array, than the matrix struct.

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) :
  check if matix and result are not null.
  put the matrix width in result*
}
ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) :
  check if matix and result are not null.
  put the matrix height in result*
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value) :
    check if the marix is not null, and if the atgs indexes are matches to the matrix.
    put the value of the boot in those indexs at value*.

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) :
check if the lhs and rhs are actual matrix and not null and check if they are at the same size.
try to allocate an intial matrix to result*.
if one of those failed return the right errorCode.
put the same of every matching boot in lhs and rhs and put it at the match boot in result.e.

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) :
check if the lhs and rhs are actual matrix and not null and check if the lhs rows number quals to rhs collumns number.
try to allocate an intial matrix to result*.
if one of those failed return the right errorCode.

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) :
check if the matrix is not null.
multiple every boot at the matrix with the scalar. 

added a friend test to the library at main.c
