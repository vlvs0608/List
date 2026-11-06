#include <TXlib.h>
#include <stdio.h>

#include "List_Init.h"


int main( void )
{
    List list = {};
    Create_List( &list );

    Push_Value( &list, 35, 1 );
    Push_Value( &list, 77, 2 );
    Push_Value( &list, 88, 1 );
    Push_Value( &list, 99, 3 );

    Print_List( &list );

    Remove_Value( &list, 2 );

    putchar( '\n' );

    Print_List( &list );

    Destroy_List( &list );

    return 0;
}
