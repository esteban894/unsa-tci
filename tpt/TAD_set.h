#ifndef TAD_SET_H
#define TAD_SET_H
#include "TAD_string.h"

typedef struct NodoSet
{
  str string;
  struct NodoSet *sig;
} NodoSet;

typedef NodoSet *Set;

Set createSet();
void appendSet(Set *, str);
Set toSet(str, char);
Set unionSet(Set, Set);
Set intersectionSet(Set, Set);
Set diferenceSet(Set, Set);
void showSet(Set);
int cardinal(Set);
int belongsTo(Set, str);
int includedIn(Set, Set);
void destroySet(Set *);
void removeSetNode(Set *head, Set target);
#endif