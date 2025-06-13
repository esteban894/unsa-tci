#ifndef TAD_LIST_H
#define TAD_LIST_H
#include "TAD_string.h"

typedef struct NodoList
{
  Str string;
  struct NodoList *sig;
} NodoList;

typedef NodoList *List;

List createList();
void show(List);
void append(List *, Str);
Str toStr(List);
List strToList(Str);

#endif