#include "TAD_string.h"
#include <stdlib.h>
#include <stdio.h>

str create()
{
  str nuevo = (str)malloc(sizeof(str));
  if (nuevo == NULL)
  {
    printf("Error en la asignacion de memoria para el nuevo nodo.");
    return NULL;
  }
  nuevo->character = '\0';
  nuevo->sig = NULL;
  return nuevo;
}

str load()
{
  str head = NULL;
  str tail = NULL;
  char c;
  printf("Ingrese una cadena: ");
  while ((c = getchar()) != '\n')
  {
    str nuevo = create();
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

str load2(const char *input)
{
  str head = NULL;
  str tail = NULL;
  int i;
  for (i = 0; input[i] != '\0'; i++)
  {
    str nuevo = create();
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

void print(str s)
{
  if (s == NULL)
  {
    printf("La cadena esta vacia.");
    return;
  }
  str actual = s;
  while (actual != NULL)
  {
    printf("%c", actual->character);
    actual = actual->sig;
  }
  // printf("\n");
}

str concat(str s1, str s2)
{
  if (s1 == NULL)
    return s2;
  if (s2 == NULL)
    return s1;

  str head = NULL;
  str tail = NULL;

  str actual = s1;
  while (actual != NULL)
  {
    str nuevo = create();
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
    str nuevo = create();
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

str beforeToken(str s, char token)
{
  if (s == NULL)
    return NULL;

  str head = NULL;
  str tail = NULL;

  str actual = s;
  while (actual != NULL && actual->character != token)
  {
    str nuevo = create();
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

str load3(); // cargar un string en base a un archivo .txt o .csv

int compareStr(str s1, str s2)
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