#include "TAD_list.h"
#include "TAD_string.h"
#include <stdlib.h>
#include <stdio.h>

List createList()
{
  List nuevo = (List)malloc(sizeof(List));
  if (nuevo == NULL)
  {
    printf("Error en la asignación de memoria para el nuevo nodo de la lista.");
    return NULL;
  }

  nuevo->string = NULL;
  nuevo->sig = NULL;
  return nuevo;
}

void show(List lista)
{
  if (lista == NULL)
  {
    // Si la lista está vacía
    printf("[]\n");
    return;
  }

  List aux = lista;

  printf("[");
  while (aux != NULL)
  {
    if (aux->string != NULL)
    {
      printf("'");
      print(aux->string);
      printf("'");
    }

    if (aux->sig != NULL)
    {
      printf(", ");
    }
    aux = aux->sig;
  }
  printf("]\n");
}

void append(List *lista, Str s)
{
  if (*lista == NULL || (*lista)->string == NULL)
  {
    *lista = createList();
    if (*lista == NULL)
      return;
    (*lista)->string = s;
    (*lista)->sig = NULL;
    return;
  }
  List actual = *lista;
  while (actual->sig != NULL)
  {
    actual = actual->sig;
  }
  List nuevo = createList();
  if (nuevo == NULL)
  {
    return;
  }
  nuevo->string = s;
  nuevo->sig = NULL;
  actual->sig = nuevo;
}

Str toStr(List lista) // ["hola", " mundo"] => "hola mundo"
{
  Str result = create();
  if (lista != NULL)
  {
    do
    {
      result = concat(result, lista->string);
      lista = lista->sig;
    } while (lista != NULL);
  }
  return result;
}

List strToList(Str string) // "hola" => ["h", "o", "l", "a"]
{
  List lista = NULL;
  if (string != NULL)
  {
    while (string != NULL)
    {
      Str aux = create();
      aux->character = string->character;
      aux->sig = NULL;
      append(&lista, aux);
      string = string->sig;
    }
  }
  else
  {
    lista = createList();
  }
  return lista;
}