#ifndef DUMP_H
#define DUMP_H
#include "List_Init.h"
#include "Error_Codes.h"

void Dump_List( List * list, const char * dot_name );
void Print_Used_Nodes( List * list, FILE * dot, int * used , int used_idx);
void Print_Next( List * list, FILE * dot, int * used, int used_idx );
void Print_Prev( List * list, FILE * dot, int * used, int used_idx );
void Dump_List_Png( List * list, const char * dot_name, const char * png_name );
void Print_Verify( List * list, FILE * dot, Error * errs, int err_count );
FILE * File_Open( const char * filename);

#endif
