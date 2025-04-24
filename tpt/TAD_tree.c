#include "TAD_tree.h"
#include <stdlib.h>

tData createNodeStr(Str string)
{
  tData node = NULL;
  node = (tData)malloc(sizeof(struct dataType));
  node->nodeType = STR;
  node->string = string;
  return node;
}

tData createNodeSet(Set set)
{
  tData node = NULL;
  node = (tData)malloc(sizeof(struct dataType));
  node->nodeType = SET;
  tData nodeString = createNodeStr(set->string);
  node->data = nodeString;
  node->next = NULL;
  return node;
}

tData createNodeList(List list)
{
  tData node = NULL;
  node = (tData)malloc(sizeof(struct dataType));
  node->nodeType = LIST;
  tData nodeString = createNodeStr(list->string);
  node->data = nodeString;
  node->next = NULL;
  return node;
}
