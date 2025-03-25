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

int main()
{
  list lista = NULL;

  str s1 = load2("hola");
  str s2 = load2(" ");
  str s3 = load2("mundo");
  append(&lista, s1);
  append(&lista, s2);
  append(&lista, s3);
  show(lista);
  return 0;
}
