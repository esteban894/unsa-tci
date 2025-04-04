#include "TAD_lista.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  str s = load();
  str s2 = load();
  str s3 = load();

  list lista = createList();

  append(&lista, s);
  append(&lista, s2);
  append(&lista, s3);
  show(lista);

  return 0;
}
