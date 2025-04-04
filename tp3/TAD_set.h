#ifndef TAD_SET_H
#define TAD_SET_H
#include "TAD_string.h"

typedef struct NodoSet
{
  str string;
  struct NodoSet *sig;
} NodoSet;

typedef NodoSet *set;

set createSet();
void appendSet(set *, str);
set toSet(str, char);
set unionSet(set, set);
set intersectionSet(set, set);
set diferenceSet(set, set);
void showSet(set);
#endif