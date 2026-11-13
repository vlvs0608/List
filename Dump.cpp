#include <stdio.h>
#include <stdlib.h>
#include "List_Init.h"
#include "Dump.h"
#include "Error_Codes.h"

void Dump_List( List * list, const char * dot_name )
{
    FILE * dot = File_Open( dot_name );

    int used[START_LEN] = {};
    int used_idx = Find_Used_Elems( list, used );

    fprintf( dot,
        "digraph List {\n"
        "   rankdir=LR;\n"
        "   node [shape=Mrecord, fontsize=14];\n"
        "   edge [fontsize=11, color=blue];\n\n" );

    Print_Used_Nodes( list, dot, used, used_idx );
    Print_Next( list, dot, used, used_idx );
    Print_Prev( list, dot, used, used_idx );

    //#ifdef LIST_DEBUG
    Error errs[32] = {};
    int err_count = List_Verify( list, errs );

    Print_Verify( list, dot, errs, err_count );
    //#endif

    fprintf( dot, "}\n" );

    fclose( dot );
}

void Print_Used_Nodes( List * list, FILE * dot, int * used, int used_idx )
{
    for( int i = 0; i < used_idx; i++ )
    {
        int elem = used[i];

        fprintf( dot,
            "    node_%d [label=\"{ idx=%d | { next=%d | pref=%d } | deita=%d }\"];\n",
            elem, elem,
            list->next[elem],
            list->pref[elem],
            list->deita[elem] );
    }
}

void Print_Next( List * list, FILE * dot, int * used, int used_idx )
{
    for( int i = 0; i < used_idx; i++ )
    {
        int from = used[i];
        int to = list->next[from];

        fprintf( dot,
            "   node_%d -> node_%d "
            "[penwidth=2, label=\"n[%d]\"];\n", from, to, i );
    }
}

void Print_Prev( List * list, FILE * dot, int * used, int used_idx )
{
    for( int i = 0; i < used_idx; i++ )
    {
        int from = used[i];
        int to = list->pref[from];

        fprintf( dot,
            "   node_%d -> node_%d "
            "[style=dashed, penwidth=2, label=\"p[%d]\"];\n", from, to, i );
    }
}

void Dump_List_Png( List * list, const char * dot_name, const char * png_name )
{
    Dump_List( list, dot_name );

    char cmd[1024];
    snprintf( cmd, sizeof( cmd ), "dot -Tpng \"%s\" -o \"%s\"", dot_name, png_name );

    if( system( cmd ) != 0 )
        fprintf( stderr, "Error of create PNG" );
}

void Print_Verify( List * list, FILE * dot, Error * errs, int err_count )
{
    fprintf( dot,
        "   subgraph cluster_errors {\n"
        "       label=\"Verificator\"; style=dashed; color=\"#FF1744\"; bgcolor=white\n"
        "       fontcolor=red; fontsize=14;\n"  );

    if( err_count == 0 )
    {
        fprintf( dot,
            "       err_ok[label=\"Errors not founded\", shape=plaintext,\n"
            "               fontcolor=red; fontsize=14];\n" );
    }

    else
    {
        for( int i = 0; i < err_count; i++ )
            fprintf( dot,
                "          err_%d [label=\"[%d] %s\", shape=plaintext,\n"
                "                   fontcolor=\"FF1744\", fontsize=9];\n",
                i, errs[i].idx, errs[i].err_message );

        for( int i = 1; i < err_count; i++ )
            fprintf(  dot, "      err_%d -> err_%d [style=invis];\n", i-1, i );
    }
    fprintf( dot, "   }\n" );
}

FILE * File_Open( const char * filename)
{
    if( filename == NULL)
    {
        printf("Такого файла не существует");
        return NULL;
    }
    FILE * file_ptr = fopen( filename , "w");

    if( file_ptr == NULL)
    {
        printf("Ошибка чтения файла");
        return NULL;
    }

    return file_ptr;
}
