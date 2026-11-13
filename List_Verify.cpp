#include <stdio.h>
#include "Error_Codes.h"
#define ADD_ERR(c, i, m) \
        do { Add_Error(errs, err_count, c, i, m); } while(0)

void Add_Error( Error * errs, int * err_count, enum Error_Code code, int idx, const char * err_message )
{
    errs[*err_count].code = code;
    errs[*err_count].idx = idx;
    errs[*err_count].err_message = err_message;
    (*err_count)++;
}

int List_Verify( List * list, Error * errs )
{
    int err_count = 0;

    if( !list || !list->deita || !list->next || !list->pref )
    {
        fprintf( stderr, "NULL ptr" );
        return 0;
    }

    if( list->deita[0] != POISON )
        Add_Error(errs, &err_count, ERR_HEAD, 0, " deita[0] != POISON " );

    Check_Capacity( list, errs, &err_count );

    Check_Next_Prev( list, errs, &err_count );

    Check_Size( list, errs, &err_count );

    return err_count;
}

void Check_Capacity( List * list, Error * errs, int * err_count )
{
    for( int i = 0; i < list->capacity; i++ )
    {
        int nx = list->next[i], pr = list->pref[i];
        if( nx < 0 || nx >= list->capacity || pr < 0 || pr >= list->capacity )
        {
            int free_ok = ( i != 0 && nx == -1 && pr == -1 );
            if( !free_ok )
                ADD_ERR( ERR_CAPACITY, i, " index out of range " );
        }
    }
}

void Check_Next_Prev( List * list, Error * errs, int * err_count )
{
    for( int i = 1; i < list->capacity; i++ )
    {
        if( list->next[i] == -1 && list->pref[i] == -1 )
            continue;

        if( list->next[i] < 0 || list->next[i] >= list->capacity ||
            list->pref[i] < 0 || list->pref[i] >= list->capacity )
            continue;

        if( list->next[list->pref[i]] != i )
            ADD_ERR( ERR_PREV, i, " next[pref[i]] != i " );

        if( list->pref[list->next[i]] != i )
            ADD_ERR( ERR_NEXT, i, " pref[next[i]] != i " );
    }
}

void Check_Size( List * list, Error * errs, int * err_count )
{
    int used = 0;
    for( int i = 1; i < list->capacity; i++ )
        if( list->next[i] != -1 ) used++;
    if( used != list->size )
        ADD_ERR( ERR_SIZE, used, " size mismatch " );
}
