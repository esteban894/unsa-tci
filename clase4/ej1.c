#include <stdio.h>

union Dato
{
  int i;
  float f;
  char c;
};

int main()
{
  union Dato valor;

  valor.i = 190;
  printf("%d\n", valor.i);

  valor.f = 3.14;
  printf("%f\n", valor.f); // sobrescribe el valor anterior

  valor.c = 'a';
  printf("%c\n", valor.c); // vuelve a sobrescribir

  return 0;
}