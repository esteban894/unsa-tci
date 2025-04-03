#ifndef TAD_STRING_H
#define TAD_STRING_H
#define TAMSTR 100

typedef struct NodoStr
{
  char character;
  struct NodoStr *sig;
} NodoStr;

typedef NodoStr *str;

str create();
str load();
str load2(const char *);
void print(str);
str concat(str, str);
str beforeToken(str, char);
str load3(); // nose

#endif