#include "TAD_lista.h"
#include "TAD_string.h"
#include <stdlib.h>
#include <stdio.h>

list createList()
{
  list nuevo = (list)malloc(sizeof(list));
  if (nuevo == NULL)
  {
    printf("Error en la asignación de memoria para el nuevo nodo de la lista.");
    return NULL;
  }

  nuevo->string = NULL;
  nuevo->sig = NULL;
  return nuevo;
}

void show(list lista)
{
  if (lista == NULL)
  {
    // Si la lista está vacía
    printf("Lista vacía.\n");
    return;
  }

  list aux = lista;

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

void append(list *lista, str s)
{
  if (*lista == NULL)
  {
    *lista = createList();
    if (*lista == NULL)
    {
      printf("Error en la asignación de memoria para el nuevo nodo de la lista.");
      return;
    }
    (*lista)->string = s;
    (*lista)->sig = NULL;
    return;
  }
  list actual = *lista;
  while (actual->sig != NULL)
  {
    actual = actual->sig;
  }
  list nuevo = createList();
  if (nuevo == NULL)
  {
    return;
  }
  nuevo->string = s;
  nuevo->sig = NULL;
  actual->sig = nuevo;
}

str toStr(list lista) // ["hola", " mundo"] => "hola mundo"
{
  str result = create();
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

list strToList(str string) // "hola" => ["h", "o", "l", "a"]
{
  list lista = NULL;
  if (string != NULL)
  {
    while (string != NULL)
    {
      str aux = create();
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