#include <stdio.h>
#include <stdlib.h>
#include "TAD_set.h"
#include "TAD_string.h"

set createSet()
{
  set nuevo = (set)malloc(sizeof(NodoSet));
  if (nuevo == NULL)
  {
    printf("Error en la asignacion de memoria para el nuevo nodo del conjunto.");
    return NULL;
  }
  nuevo->string = NULL;
  nuevo->sig = NULL;
  return nuevo;
}

void appendSet(set *conjunto, str cadena)
{
  if (*conjunto == NULL || (*conjunto)->string == NULL)
  {
    *conjunto = createSet();
    if (*conjunto == NULL)
      return;
    (*conjunto)->string = cadena;
    (*conjunto)->sig = NULL;
    return;
  }

  set aux = *conjunto;
  while (aux->sig != NULL)
    aux = aux->sig;
  set nuevo = createSet();
  if (nuevo == NULL)
    return;
  nuevo->string = cadena;
  nuevo->sig = NULL;
  aux->sig = nuevo;
}

// 000,001,010,011

set toSet(str cadena, char token)
{ // toSet(string, ',')
  set conjunto = NULL;

  str aux = cadena;

  if (aux != NULL)
  {
    appendSet(&conjunto, beforeToken(aux, token));
    while (aux != NULL)
    {
      if (aux->character == token)
      {
        aux = aux->sig;
        if (aux != NULL)
        {
          str stringToken = beforeToken(aux, token);
          set temp = conjunto;
          int found = 0;
          while (temp != NULL)
          {
            if (compareStr(temp->string, stringToken) == 1)
            {
              found = 1;
              break;
            }
            temp = temp->sig;
          }
          if (!found)
          {
            appendSet(&conjunto, stringToken);
          }
        }
      }
      else
      {
        aux = aux->sig;
      }
    }
  }
  else
    conjunto = createSet();
  return conjunto;
}

set unionSet(set conjunto1, set conjunto2)
{
  set nuevo = NULL;
  set aux = conjunto1;
  while (aux != NULL)
  {
    appendSet(&nuevo, aux->string);
    aux = aux->sig;
  }
  aux = conjunto2;
  while (aux != NULL && aux->string != NULL)
  {
    set temp = nuevo;
    int found = 0;
    while (temp != NULL)
    {
      if (compareStr(temp->string, aux->string) == 1)
      {
        found = 1;
        break;
      }
      temp = temp->sig;
    }
    if (!found)
    {
      appendSet(&nuevo, aux->string);
    }
    aux = aux->sig;
  }
  return nuevo;
}
set intersectionSet(set conjunto1, set conjunto2)
{
  set nuevo = NULL;
  set aux1 = conjunto1;
  set aux2 = conjunto2;
  while (aux1 != NULL && aux2 != NULL)
  {
    if (compareStr(aux1->string, aux2->string) == 1)
    {
      appendSet(&nuevo, aux1->string);
    }
    aux1 = aux1->sig;
    aux2 = aux2->sig;
  }
  return nuevo;
}

set diferenceSet(set conjunto1, set conjunto2)
{
  set nuevo = NULL;
  set aux1 = conjunto1;
  set aux2 = conjunto2;
  while (aux1 != NULL)
  {
    int found = 0;
    set temp = aux2;
    while (temp != NULL)
    {
      if (compareStr(aux1->string, temp->string) == 1)
      {
        found = 1;
        break;
      }
      temp = temp->sig;
    }
    if (!found)
    {
      appendSet(&nuevo, aux1->string);
    }
    aux1 = aux1->sig;
  }
  return nuevo;
}

void showSet(set conjunto)
{
  if (conjunto == NULL)
  {
    printf("{}\n");
    return;
  }

  set aux = conjunto;

  printf("{");
  while (aux != NULL)
  {
    if (aux->string != NULL)
    {
      // print(aux->string);
      str aux2 = aux->string;
      while (aux2 != NULL)
      {
        printf("%c", aux2->character);
        aux2 = aux2->sig;
      }
    }
    else
    {
      print(aux->string);
    }
    if (aux->sig != NULL)
    {
      printf(", ");
    }
    aux = aux->sig;
  }
  printf("}\n");
}

int cardinal(set conjunto)
{
  int count = 0;
  set aux = conjunto;
  while (aux != NULL)
  {
    count++;
    aux = aux->sig;
  }
  return count;
}

int belongsTo(set conjunto, str cadena)
{
  set aux = conjunto;
  while (aux != NULL)
  {
    if (compareStr(aux->string, cadena) == 1)
    {
      return 1;
    }
    aux = aux->sig;
  }
  return 0;
}

int includedIn(set conjunto1, set conjunto2) // que conjunto2 este contenido en conjunto1
{
  set aux1 = conjunto1;
  set aux2 = conjunto2;
  while (aux2 != NULL)
  {
    if (!belongsTo(aux1, aux2->string))
    {
      return 0;
    }
    aux2 = aux2->sig;
  }
  return 1;
}

void destroySet(set *conjunto)
{
  set aux = *conjunto;
  while (aux != NULL)
  {
    set temp = aux;
    aux = aux->sig;
    free(temp->string);
    free(temp);
  }
  *conjunto = NULL;
}

void removeSetNode(set *head, set target)
{
  if (*head == NULL || target == NULL)
    return;

  if (*head == target)
  {
    *head = target->sig;
  }
  else
  {
    set aux = *head;
    while (aux->sig != NULL && aux->sig != target)
    {
      aux = aux->sig;
    }
    if (aux->sig == target)
    {
      aux->sig = target->sig;
    }
  }

  target->sig = NULL;
  destroySet(&target);
}