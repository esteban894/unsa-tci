#ifndef TAD_STRING_H
#define TAD_STRING_H
#define TAMSTR 100

typedef struct NodoStr
{
  char character;
  struct NodoStr *sig;
} NodoStr;

typedef NodoStr *Str;

Str createStr();
Str load();
Str load2(const char *);
void print(Str);
Str concat(Str, Str);
Str beforeToken(Str, char);
Str load3(); // load from file
int compareStr(Str s1, Str s2);

#endif