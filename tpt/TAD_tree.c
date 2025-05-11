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

void printStruct(tData node)
{
  if (node == NULL)
    return;

  switch (node->nodeType)
  {
  case STR:
    // Si es un string, simplemente lo imprimimos
    print(node->string);
    break;

  case LIST:
    // Si es una lista, recorremos sus elementos
    tData current = node;
    printf("[");
    while (current != NULL)
    {
      printStruct(current->data); // Recursivamente procesamos cada elemento
      if (current->next != NULL)
        printf(", ");
      current = current->next;
    }
    printf("]");
    break;

  case SET:
    // Si es un conjunto, recorremos sus elementos
    tData currentSet = node;
    printf("{");
    while (currentSet != NULL)
    {
      printStruct(currentSet->data); // Recursivamente procesamos cada elemento
      if (currentSet->next != NULL)
        printf(", ");
      currentSet = currentSet->next;
    }
    printf("}");
    break;
  }
}

tData concatNodeStr(tData s1, tData s2)
{
  // Si ambos son NULL, retornar NULL
  if (s1 == NULL && s2 == NULL)
    return NULL;

  // Si s1 es NULL y s2 no es NULL
  if (s1 == NULL)
    return (s2->nodeType == STR) ? s2 : NULL;

  // Si s2 es NULL y s1 no es NULL
  if (s2 == NULL)
    return (s1->nodeType == STR) ? s1 : NULL;

  // Si ninguno es NULL, verificar que ambos sean STR
  if (s1->nodeType == STR && s2->nodeType == STR)
  {
    tData result = createNodeStr(concat(s1->string, s2->string));
    return result;
  }

  return NULL;
}

tData beforeTokenNodeStr(tData s, char token)
{
  // Si el nodo es NULL o no es de tipo STR, retornar NULL
  if (s == NULL || s->nodeType != STR)
    return NULL;

  // Crear un nuevo nodo con la subcadena antes del token
  tData result = createNodeStr(beforeToken(s->string, token));
  return result;
}

int compareNodeStr(tData s1, tData s2)
{
  // Si alguno es NULL o no es de tipo STR, retornar 0 (no iguales)
  if (s1 == NULL || s2 == NULL || s1->nodeType != STR || s2->nodeType != STR)
    return 0;

  // Usar la función compareStr existente para comparar los strings
  return compareStr(s1->string, s2->string);
}

void appendNodeList(tData *list, tData node) // [1, 2, [3, 4]]
{
  // Si la lista está vacía, crear un nuevo nodo de tipo LIST
  if (*list == NULL)
  {
    List newList = createList();
    *list = createNodeList(newList);
    if (*list == NULL)
      return;
    (*list)->data = node;
    (*list)->next = NULL;
    return;
  }

  // Validar que el nodo actual sea de tipo LIST
  if ((*list)->nodeType != LIST)
    return;

  // Recorrer hasta el final de la lista
  tData aux = *list;
  while (aux->next != NULL)
  {
    // Validar que todos los nodos en el recorrido sean de tipo LIST
    if (aux->next->nodeType != LIST)
      return;
    aux = aux->next;
  }

  // Crear un nuevo nodo de tipo LIST para el elemento a agregar
  List newList = createList();
  tData newNode = createNodeList(newList);
  if (newNode == NULL)
    return;

  // Asignar el nodo a agregar como data del nuevo nodo LIST
  newNode->data = node;
  newNode->next = NULL;

  // Conectar el nuevo nodo al final de la lista
  aux->next = newNode;
}

// [{q0,q1},{0,1},[{q0,0,q1},{q0,1,q0},{q1,0,q0},{q1,1,q1}],q0,{q0}]
// =>
// "{q0,q1},{0,1},[{q0,0,q1},{q0,1,q0},{q1,0,q0},{q1,1,q1}],q0,{q0}"

tData toNodeStr(tData node) // [hola, ' ', mundo, [1,2,3]] => "hola mundo"
{
  if (node == NULL || (node->nodeType != LIST && node->nodeType != SET))
    return NULL;

  Str result = createStr();
  tData aux = node;

  while (aux != NULL)
  {
    if (aux->data == NULL)
      return NULL;

    // Si el elemento es un string, lo concatenamos directamente
    if (aux->data->nodeType == STR)
    {
      result = concat(result, aux->data->string);
    }
    // Si el elemento es una lista o conjunto, lo convertimos recursivamente
    else if (aux->data->nodeType == LIST || aux->data->nodeType == SET)
    {
      tData nestedStr = toNodeStr(aux->data);
      if (nestedStr == NULL)
        return NULL;
      result = concat(result, nestedStr->string);
    }
    // Si es de otro tipo, retornamos NULL
    else
    {
      return NULL;
    }

    aux = aux->next;
  }

  return createNodeStr(result);
}

tData listToNodeStr(tData list) // ["hola", " ", "mundo"] => "hola mundo"
{
  if (list == NULL || list->nodeType != LIST)
    return NULL;

  Str result = createStr();
  tData aux = list;

  while (aux != NULL)
  {
    // Verificar que el elemento sea de tipo STR
    if (aux->data == NULL || aux->data->nodeType != STR)
      return NULL;

    // Concatenar el string
    result = concat(result, aux->data->string);
    aux = aux->next;
  }

  return createNodeStr(result);
}