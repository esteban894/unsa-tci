#include "TAD_set.h"

int main()
{
  str cadena1 = load2("a");
  str cadena2 = load2("");
  set conjunto1 = toSet(cadena1, ',');
  set conjunto2 = toSet(cadena2, ',');
  set conjunto3 = unionSet(conjunto1, conjunto2);
  showSet(conjunto3);
  return 0;
}
