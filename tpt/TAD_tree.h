#ifndef TAD_TREE_H
#define TAD_TREE_H
#include "TAD_string.h"
#include "TAD_set.h"
#include "TAD_list.h"
#include <stdlib.h>

#define STR 1
#define SET 2
#define LIST 3

struct dataType
{
  int nodeType; // STR SET LIST
  union
  {
    Str string;
    struct
    {
      struct dataType *data;
      struct dataType *next;
    };
  };
};

typedef struct dataType *tData;

tData createNodeStr(Str);
tData createNodeSet(Set);
tData createNodeList(List);
void printStruct(tData structure);
tData concatNodeStr(tData s1, tData s2);
tData beforeTokenNodeStr(tData s, char token);
int compareNodeStr(tData s1, tData s2);
void appendNodeList(tData *list, tData node);
tData toNodeStr(tData list);
void destroyTData(tData *node);

#endif