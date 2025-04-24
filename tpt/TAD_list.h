#ifndef TAD_LIST_H
#define TAD_LIST_H
#include "TAD_string.h"

typedef struct NodoLis
{
  Str string;
  struct NodoLis *sig;
} NodoLis;

typedef NodoLis *List;

List createList();
void show(List);
void append(List *, Str);
Str toStr(List);
List strToList(str);

#endif