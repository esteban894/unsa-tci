#include "TAD_tree.h"
#include <stdio.h>
#include <stdlib.h>

tData createNodeStr(Str string)
{
  tData node = (tData)malloc(sizeof(struct dataType));
  if (node == NULL)
    return NULL;

  node->nodeType = STR;
  node->string = string;
  return node;
}

tData createNodeSet(Set set)
{
  if (set == NULL)
    return NULL;

  tData head = NULL;
  tData tail = NULL;
  Set current = set;

  // Recorrer el Set y crear nodos tData para cada elemento
  while (current != NULL && current->string != NULL)
  {
    tData newNode = (tData)malloc(sizeof(struct dataType));
    if (newNode == NULL)
      return NULL;

    newNode->nodeType = SET;
    newNode->data = createNodeStr(current->string);
    newNode->next = NULL;

    if (head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }

    current = current->sig;
  }

  return head;
}

tData createNodeList(List list)
{
  if (list == NULL)
  {
    // Crear un nodo LIST vacío
    tData node = (tData)malloc(sizeof(struct dataType));
    if (node == NULL)
      return NULL;

    node->nodeType = LIST;
    node->data = NULL;
    node->next = NULL;
    return node;
  }

  tData head = NULL;
  tData tail = NULL;
  List current = list;

  // Recorrer la List y crear nodos tData para cada elemento
  while (current != NULL && current->string != NULL)
  {
    tData newNode = (tData)malloc(sizeof(struct dataType));
    if (newNode == NULL)
      return NULL;

    newNode->nodeType = LIST;
    newNode->data = createNodeStr(current->string);
    newNode->next = NULL;

    if (head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }

    current = current->sig;
  }

  // Si no hay elementos, crear nodo vacío
  if (head == NULL)
  {
    head = (tData)malloc(sizeof(struct dataType));
    if (head == NULL)
      return NULL;
    head->nodeType = LIST;
    head->data = NULL;
    head->next = NULL;
  }

  return head;
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
    printf("[");
    tData current = node;
    int first = 1;
    while (current != NULL)
    {
      if (!first)
        printf(", ");
      printStruct(current->data); // Recursivamente procesamos cada elemento
      current = current->next;
      first = 0;
    }
    printf("]");
    break;

  case SET:
    // Si es un conjunto, recorremos sus elementos
    printf("{");
    tData currentSet = node;
    int firstSet = 1;
    while (currentSet != NULL)
    {
      if (!firstSet)
        printf(", ");
      printStruct(currentSet->data); // Recursivamente procesamos cada elemento
      currentSet = currentSet->next;
      firstSet = 0;
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

void appendNodeList(tData *list, tData node)
{
  if (node == NULL)
    return;

  // Si la lista está vacía, crear el primer nodo
  if (*list == NULL)
  {
    tData newNode = (tData)malloc(sizeof(struct dataType));
    if (newNode == NULL)
      return;

    newNode->nodeType = LIST;
    newNode->data = node;
    newNode->next = NULL;
    *list = newNode;
    return;
  }

  // Validar que el nodo actual sea de tipo LIST
  if ((*list)->nodeType != LIST)
    return;

  // Recorrer hasta el final de la lista
  tData aux = *list;
  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  // Crear un nuevo nodo de tipo LIST para el elemento a agregar
  tData newNode = (tData)malloc(sizeof(struct dataType));
  if (newNode == NULL)
    return;

  // Asignar el nodo a agregar como data del nuevo nodo LIST
  newNode->nodeType = LIST;
  newNode->data = node;
  newNode->next = NULL;

  // Conectar el nuevo nodo al final de la lista
  aux->next = newNode;
}

tData toNodeStr(tData node)
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

    aux = aux->next;
  }

  return createNodeStr(result);
}

tData listToNodeStr(tData list)
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

void destroyTData(tData *node)
{
  if (node == NULL || *node == NULL)
    return;

  tData current = *node;

  switch (current->nodeType)
  {
  case STR:
    // Para nodos STR, liberar la cadena y el nodo
    if (current->string != NULL)
    {
      // Liberar la cadena carácter por carácter
      Str strCurrent = current->string;
      while (strCurrent != NULL)
      {
        Str temp = strCurrent;
        strCurrent = strCurrent->sig;
        free(temp);
      }
    }
    free(current);
    break;

  case SET:
  case LIST:
    // Para nodos SET y LIST, liberar recursivamente los elementos
    while (current != NULL)
    {
      tData temp = current;
      current = current->next;

      // Liberar recursivamente el contenido (data)
      if (temp->data != NULL)
      {
        destroyTData(&(temp->data));
      }

      free(temp);
    }
    break;

  default:
    // Tipo desconocido, solo liberar el nodo
    free(current);
    break;
  }

  *node = NULL;
}
