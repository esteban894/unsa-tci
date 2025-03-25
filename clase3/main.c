/* Crear un TAD que modele una lista enlazada de str (otra lista enlazada)

list createList();
void show(list);
void append(list*, str);
str toStr(list);
list strToList(str);

  Considerar incluir el TAD string
*/
#include "TAD_string.h"
#include "TAD_lista.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
  list lista = NULL;

  str s1 = load();

  lista = strToList(s1);
  show(lista);
  return 0;
}
