#ifndef TAD_LISTA_H
#define TAD_LISTA_H
#include "TAD_string.h"

typedef struct NodoLis
{
  str string;
  struct NodoLis *sig;
} NodoLis;

typedef NodoLis *list;

list createList();
void show(list);
void append(list *, str);
list strToList(str);

#endif