#include "TAD_string.h"
#include <stdlib.h>
#include <stdio.h>

Str createStr()
{
  Str nuevo = (Str)malloc(sizeof(Str));
  if (nuevo == NULL)
  {
    printf("Error en la asignación de memoria para el nuevo nodo.");
    return NULL;
  }
  nuevo->character = '\0';
  nuevo->sig = NULL;
  return nuevo;
}

Str load()
{
  Str head = NULL;
  Str tail = NULL;
  char c;
  printf("Ingrese una cadena: ");
  while ((c = getchar()) != '\n')
  {
    Str nuevo = create();
    if (nuevo == NULL)
    {
      return NULL;
    }
    nuevo->character = c;
    if (head == NULL)
    {
      head = nuevo;
      tail = nuevo;
    }
    else
    {
      tail->sig = nuevo;
      tail = nuevo;
    }
  }
  return head;
}

Str load2(const char *input)
{
  Str head = NULL;
  Str tail = NULL;
  int i;
  for (i = 0; input[i] != '\0'; i++)
  {
    Str nuevo = create();
    if (nuevo == NULL)
    {
      return NULL;
    }
    nuevo->character = input[i];
    nuevo->sig = NULL;
    if (head == NULL)
    {
      head = nuevo;
      tail = nuevo;
    }
    else
    {
      tail->sig = nuevo;
      tail = nuevo;
    }
  }
  return head;
}

void print(Str s)
{
  if (s == NULL)
  {
    printf("La cadena esta vacia.");
    return;
  }
  Str actual = s;
  while (actual != NULL)
  {
    printf("%c", actual->character);
    actual = actual->sig;
  }
  // printf("\n");
}

Str concat(Str s1, Str s2)
{
  if (s1 == NULL)
    return s2;
  if (s2 == NULL)
    return s1;

  Str head = NULL;
  Str tail = NULL;

  Str actual = s1;
  while (actual != NULL)
  {
    Str nuevo = create();
    if (nuevo == NULL)
    {
      return NULL;
    }
    nuevo->character = actual->character;
    nuevo->sig = NULL;

    if (head == NULL)
    {
      head = nuevo;
      tail = nuevo;
    }
    else
    {
      tail->sig = nuevo;
      tail = nuevo;
    }

    actual = actual->sig;
  }

  actual = s2;
  while (actual != NULL)
  {
    Str nuevo = create();
    if (nuevo == NULL)
    {
      return NULL;
    }
    nuevo->character = actual->character;
    nuevo->sig = NULL;

    if (tail == NULL)
    {
      head = nuevo;
      tail = nuevo;
    }
    else
    {
      tail->sig = nuevo;
      tail = nuevo;
    }

    actual = actual->sig;
  }

  return head;
}

Str beforeToken(Str s, char token)
{
  if (s == NULL)
    return NULL;

  Str head = NULL;
  Str tail = NULL;

  Str actual = s;
  while (actual != NULL && actual->character != token)
  {
    Str nuevo = create();
    if (nuevo == NULL)
    {
      return NULL;
    }
    nuevo->character = actual->character;
    nuevo->sig = NULL;
    if (head == NULL)
    {
      head = nuevo;
      tail = nuevo;
    }
    else
    {
      tail->sig = nuevo;
      tail = nuevo;
    }
    actual = actual->sig;
  }
  return head;
}

Str load3(); // cargar un string en base a un archivo .txt o .csv