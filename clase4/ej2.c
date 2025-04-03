#include <stdio.h>
#include <stdlib.h>

union Dato
{
  int num;
  char letra;
};

struct Nodo
{
  union Dato dato;
  int esEntero;
  struct Nodo *sig;
};

// hacer funcion en comun para hacer el malloc

struct Nodo *crearNodoEntero(int valor)
{
  struct Nodo *nuevo = NULL;
  // malloc...
  nuevo->dato.num = valor;
  nuevo->esEntero = 1;
  nuevo->sig = NULL;
  return nuevo;
}

struct Nodo *crearNodoChar(char valor)
{
  struct Nodo *nuevo = NULL;
  // malloc...
  nuevo->dato.letra = valor;
  nuevo->esEntero = 0;
  nuevo->sig = NULL;
  return nuevo;
}

int main()
{
  return 0;
}