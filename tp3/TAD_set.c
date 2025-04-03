#include "TAD_set.h"

set createSet();
void appendSet(set *conjunto, str cadena);
set toSet(str cadena, char token);
set unionSet(set conjunto1, set conjunto2);
set intersectionSet(set conjunto1, set conjunto2);
set diference(set conjunto1, set conjunto2);
void showSet(set conjunto);