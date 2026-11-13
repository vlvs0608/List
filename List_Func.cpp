#include <stdio.h>
#include <stdlib.h>
#include "List_Init.h"
#include "Error_Codes.h"

void Create_List( List * list )
{
    list->capacity = START_LEN;
    list->size     = 0;

    list->deita = ( int * )calloc( START_LEN, sizeof( int ) );

    list->next = (int * )calloc( START_LEN, sizeof(int) );

    list->pref = (int * )calloc( START_LEN, sizeof(int) );

    if( list->deita == NULL || list->next == NULL || list->pref == NULL )
    {
        fprintf( stderr, "Ошибка инициализации массива " );
        return;
    }

    list->deita[0] = POISON;
    list->next[0] = 0;
    list->pref[0] = 0;

    for( int i = 1; i < list->capacity; i++ )
    {
        list->pref[i] = -1;
        list->next[i] = -1;
    }

}

void Push_Value( List * list, int value, int position )
{
    int n = Find_Free( list );

    list->deita[n] = value;

    Change_Next_Pref( list, position, n );

    list->size++;
}

void Change_Next_Pref( List * list, int position, int real_index )
{
    int n = 0;
    for( int i = 1; i < position; i++)
        n = list->next[n];

    int t = list->next[n];
    list->next[n] = real_index;
    list->pref[real_index] = n;
    list->next[real_index] = t;
    list->pref[t]= real_index;
}

int Find_Free( List * list )
{
    for( int i = 1; i < list->capacity; i++ )
        if( list->next[i] == -1 )
            return i;
}

void Print_List( List * list )
{
    int i = 0;
    do
    {
        printf( "%d; ", list->deita[list->next[i]] );
        i = list->next[i];
    } while ( list->next[i] != 0 );
}

void Remove_Value( List * list, int position )
{
    int n = 0;
    for( int i = 0; i < position; i++ )
        n = list->next[n];

    int t = list->next[n];
    int p = list->pref[n];
    list->next[p] = t;
    list->pref[t] = p;

    list->deita[n] = 0;
    list->next[n] = -1;
    list->pref[n] = -1;

    list->size--;
}

void Destroy_List( List * list )
{
    free( list->deita );
    free( list->next );
    free( list->pref);
}

int Find_Used_Elems( List * list, int * used )
{
    int used_idx = 0;
    int used_elem = 0;
    do
    {
        used[used_idx] = used_elem;
        used_idx++;
        used_elem = list->next[used_elem];
    } while( used_elem != 0 && used_idx < START_LEN );

    return used_idx;
}
