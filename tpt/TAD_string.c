#include "TAD_string.h"
#include <stdlib.h>
#include <stdio.h>

Str createStr()
{
  Str nuevo = (Str)malloc(sizeof(NodoStr));
  if (nuevo == NULL)
  {
    printf("Error en la asignacion de memoria para el nuevo nodo.");
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
    Str nuevo = createStr();
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
    Str nuevo = createStr();
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
    Str nuevo = createStr();
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
    Str nuevo = createStr();
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
    Str nuevo = createStr();
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

int compareStr(Str s1, Str s2)
{
  // Recorremos ambas listas mientras no sean NULL
  while (s1 != NULL && s2 != NULL)
  {
    // Comparamos los caracteres de ambas cadenas
    if (s1->character != s2->character)
    {
      return 0; // Si hay una diferencia, las cadenas no son iguales
    }
    // Avanzamos al siguiente nodo en ambas listas
    s1 = s1->sig;
    s2 = s2->sig;
  }

  // Si ambas listas llegaron al final, son iguales
  // Si una es NULL y la otra no, no son iguales
  return (s1 == NULL && s2 == NULL) ? 1 : 0;
}

Str copyString(Str original)
{
  if (original == NULL)
    return NULL;

  Str newStr = createStr();
  if (newStr == NULL)
    return NULL;

  Str current = original;
  Str newCurrent = newStr;
  int first = 1;

  while (current != NULL)
  {
    if (first)
    {
      newCurrent->character = current->character;
      first = 0;
    }
    else
    {
      Str newNode = createStr();
      if (newNode == NULL)
        return NULL;

      newNode->character = current->character;
      newNode->sig = NULL;
      newCurrent->sig = newNode;
      newCurrent = newNode;
    }
    current = current->sig;
  }

  return newStr;
}