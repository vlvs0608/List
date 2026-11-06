#ifndef LIST_INIT_H
#define LIST_INIT_H
#define POISON 666
#define START_LEN 64

typedef struct
{
    int * deita;
    int * next;
    int * pref;
}List;

void Create_List( List * list );
void Push_Value( List * list, int value, int position );
void Change_Next_Pref( List * list, int position, int real_index );
int Find_Free( List * list );
void Print_List( List * list );
void Remove_Value( List * list, int position );
void Destroy_List( List * list );


#endif
