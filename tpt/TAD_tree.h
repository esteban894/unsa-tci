#ifndef TAD_TREE_H
#define TAD_TREE_H
#include "TAD_string.h"

#define STR 1
#define SET 2
#define LIST 3

struct dataType
{
  int nodeType; // STR SET LIST
  union
  {
    str string;
    struct
    {
      struct dataType *data;
      struct dataType *next;
    };
  };
};

typedef struct dataType *tData;

#endif