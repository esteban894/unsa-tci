#ifndef TAD_SET_H
#define TAD_SET_H
#include "TAD_string.h"

typedef struct NodoSet
{
  Str string;
  struct NodoSet *sig;
} NodoSet;

typedef NodoSet *Set;

Set createSet();
void appendSet(Set *, Str);
Set toSet(Str, char);
Str toStrSet(Set set);
Set unionSet(Set, Set);
Set intersectionSet(Set, Set);
Set diferenceSet(Set, Set);
void showSet(Set);
int cardinal(Set);
int belongsTo(Set, Str);
int includedIn(Set, Set);
void destroySet(Set *);
void removeSetNode(Set *head, Set target);
int setsAreEqual(Set set1, Set set2);

#endif