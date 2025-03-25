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

// void show(list lista)
// {
//   if (lista == NULL)
//   {
//     printf("Lista vacía.\n");
//     return;
//   }
//   list aux = lista;

//   printf("[ ");
//   while (aux != NULL)
//   {
//     if (aux->sig != NULL)
//     {
//       print(aux->string);
//     }
//     else
//     {
//       printf("(nodo vacio)");
//     }
//     if (aux->sig != NULL)
//     {
//       printf(", ");
//     }
//     aux = aux->sig;
//   }

//   printf(" ]\n");
// }

void show(list lista)
{
  if (lista == NULL)
  {
    // Si la lista está vacía
    printf("Lista vacía.\n");
    return;
  }

  list aux = lista;

  printf("[ ");
  while (aux != NULL)
  {
    if (aux->string != NULL)
    {
      print(aux->string); // Imprime la cadena asociada al nodo
    }
    else
    {
      printf("(nodo vacío)"); // Manejo de nodos sin cadena
    }

    if (aux->sig != NULL)
    {
      printf(", ");
    }
    aux = aux->sig;
  }
  printf(" ]\n");
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

str toStr(list);

list strToList(str);