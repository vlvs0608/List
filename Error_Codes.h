#ifndef ERROR_CODES_H
#define ERROR_CODES_H
#include "List_Init.h"

enum Error_Code
{
    ERR_OK,
    ERR_HEAD,
    ERR_NO_CLOSURE,
    ERR_CYCLE,
    ERR_NEXT,
    ERR_PREV,
    ERR_CAPACITY,
    ERR_SIZE,
    ERR_COUNT
};

typedef struct
{
    enum Error_Code code;
    int idx;
    const char * err_message;
}Error;

void Add_Error( Error * errs, int * err_count, enum Error_Code code, int idx, const char * err_message );
int List_Verify( List * list, Error * errs );
int Node_Error( Error * errs, int err_count, int idx );
void Check_Capacity( List * list, Error * errs, int * err_count );
void Check_Next_Prev( List * list, Error * errs, int * err_count );
void Check_Size( List * list, Error * errs, int * err_count );

#endif
