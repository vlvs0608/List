#include <TXlib.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_DEBUG

#include "List_Init.h"
#include "Dump.h"
#include "Error_Codes.h"


int main( const int argc, const char * argv[] )
{
    List list = {};
    Create_List( &list );

    Push_Value( &list, 35, 1 );
    Push_Value( &list, 77, 2 );
    Push_Value( &list, 88, 1 );
    Push_Value( &list, 99, 3 );

    Print_List( &list );

    Dump_List_Png( &list, argv[1], argv[2] );

    Remove_Value( &list, 2 );

    putchar( '\n' );

    Print_List( &list );

    Destroy_List( &list );

    return 0;
}
