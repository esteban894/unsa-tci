#include <stdio.h>
#include <stdlib.h>
#include "TAD_set.h"
#include "TAD_string.h"

Set createSet()
{
  Set nuevo = (Set)malloc(sizeof(NodoSet));
  if (nuevo == NULL)
  {
    printf("Error en la asignación de memoria para el nuevo nodo del conjunto.");
    return NULL;
  }
  nuevo->string = NULL;
  nuevo->sig = NULL;
  return nuevo;
}

void appendSet(Set *conjunto, Str cadena)
{
  if (cadena == NULL || cadena->character == '\0')
    return;

  if (*conjunto == NULL || (*conjunto)->string == NULL)
  {
    *conjunto = createSet();
    if (*conjunto == NULL)
      return;
    (*conjunto)->string = cadena;
    (*conjunto)->sig = NULL;
    return;
  }

  Set aux = *conjunto;
  while (aux->sig != NULL)
    aux = aux->sig;

  Set nuevo = createSet();
  if (nuevo == NULL)
    return;

  nuevo->string = cadena;
  nuevo->sig = NULL;
  aux->sig = nuevo;
}

// 000,001,010,011

Set toSet(Str cadena, char token)
{ // toSet(string, ',')
  Set conjunto = NULL;

  Str aux = cadena;

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
          Str stringToken = beforeToken(aux, token);
          Set temp = conjunto;
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

Set unionSet(Set conjunto1, Set conjunto2)
{
  Set nuevo = NULL;

  Set aux = conjunto1;
  while (aux != NULL)
  {
    if (aux->string != NULL && aux->string->character != '\0')
    {
      appendSet(&nuevo, aux->string);
    }
    aux = aux->sig;
  }

  aux = conjunto2;
  while (aux != NULL && aux->string != NULL)
  {
    if (aux->string->character != '\0')
    {
      Set temp = nuevo;
      int found = 0;

      while (temp != NULL)
      {
        if (temp->string != NULL && compareStr(temp->string, aux->string) == 1)
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
    }
    aux = aux->sig;
  }
  return nuevo;
}

Set intersectionSet(Set conjunto1, Set conjunto2)
{
  Set nuevo = NULL;

  if (conjunto1 == NULL || conjunto2 == NULL)
    return nuevo;

  Set aux1 = conjunto1;
  while (aux1 != NULL && aux1->string != NULL)
  {
    if (aux1->string->character != '\0')
    {
      Set aux2 = conjunto2;
      while (aux2 != NULL && aux2->string != NULL)
      {
        if (aux2->string->character != '\0' &&
            compareStr(aux1->string, aux2->string) == 1)
        {
          appendSet(&nuevo, aux1->string);
          break;
        }
        aux2 = aux2->sig;
      }
    }
    aux1 = aux1->sig;
  }

  return nuevo;
}

Set diferenceSet(Set conjunto1, Set conjunto2)
{
  Set nuevo = NULL;
  Set aux1 = conjunto1;
  Set aux2 = conjunto2;
  while (aux1 != NULL)
  {
    int found = 0;
    Set temp = aux2;
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

void showSet(Set conjunto)
{
  if (conjunto == NULL)
  {
    printf("{}");
    return;
  }

  Set aux = conjunto;
  printf("{");

  int first = 1;
  while (aux != NULL)
  {
    if (aux->string != NULL && aux->string->character != '\0')
    {
      if (!first)
      {
        printf(", ");
      }

      Str aux2 = aux->string;
      while (aux2 != NULL)
      {
        printf("%c", aux2->character);
        aux2 = aux2->sig;
      }

      first = 0;
    }
    aux = aux->sig;
  }

  printf("}");
}

int cardinal(Set conjunto)
{
  int count = 0;
  Set aux = conjunto;
  while (aux != NULL)
  {
    count++;
    aux = aux->sig;
  }
  return count;
}

int belongsTo(Set conjunto, Str cadena)
{
  Set aux = conjunto;
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

int includedIn(Set conjunto1, Set conjunto2) // que conjunto2 este contenido en conjunto1
{
  Set aux1 = conjunto1;
  Set aux2 = conjunto2;
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

void destroySet(Set *conjunto)
{
  Set aux = *conjunto;
  while (aux != NULL)
  {
    Set temp = aux;
    aux = aux->sig;
    free(temp->string);
    free(temp);
  }
  *conjunto = NULL;
}

void removeSetNode(Set *head, Set target)
{
  if (*head == NULL || target == NULL)
    return;

  if (*head == target)
  {
    *head = target->sig;
  }
  else
  {
    Set aux = *head;
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

Str toStrSet(Set set)
{
  Str result = createStr();

  // Agregar '{' al inicio
  Str open = createStr();
  open->character = '{';
  open->sig = NULL;
  result = concat(result, open);

  Set aux = set;
  while (aux != NULL)
  {
    if (aux->string != NULL)
    {
      result = concat(result, aux->string);
    }
    if (aux->sig != NULL)
    {
      // Agregar coma
      Str coma = createStr();
      coma->character = ',';
      coma->sig = NULL;
      result = concat(result, coma);
    }
    aux = aux->sig;
  }

  // Agregar '}' al final
  Str close = createStr();
  close->character = '}';
  close->sig = NULL;
  result = concat(result, close);

  return result;
}