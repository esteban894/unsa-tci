#include "TAD_af.h"
#include <stdio.h>
#include <stdlib.h>

int options();
void menu(Af *af);

int main()
{
  // Str automatonStr = load2("[{q0,q1},{0,1},[{q0,0,q1},{q0,1,q0},{q1,0,q0},{q1,1,q1}],q0,{q0}]");

  // Parsear
  // Af automaton = parseAfFromString(automatonStr);
  Af af = createAf();

  if (af == NULL)
  {
    printf("Error al crear el automata.\n");
    return 1;
  }

  menu(&af);

  destroyAf(&af);
  return 0;
}

int options()
{
  int option;
  printf("\nOpciones:\n");
  printf("1. Crear automata desde cadena hardcodeada\n");
  printf("2. Crear automata desde consola\n");
  printf("3. Mostrar partes de la 5-upla del automata\n");
  printf("4. Determinar si el automata es determinista o no determinista\n");
  printf("5. Determinar si el af acepta una cadena hardcodeada\n");
  printf("6. Determinar si el af acepta una cadena ingresada por consola\n");
  printf("7. Crear caso de prueba para un AFD que acepte cadenas sobre 0,1 con cantidad impar de 0's\n");
  printf("0. Salir\n");
  printf("Selecciona una opcion: ");
  scanf("%d", &option);
  return option;
}

void menu(Af *af)
{
  int op = options();
  switch (op)
  {
  case 1:
    *af = parseAfFromString(load2("[{q0,q1},{0,1},[{q0,0,q1},{q0,1,q0},{q1,0,q0},{q1,1,q1}],q0,{q0}]"));
    if (*af == NULL)
    {
      printf("\nError al crear el automata desde la cadena.\n");
    }
    else
    {
      printf("\nAutomata creado exitosamente desde la cadena.\n");
    }
    menu(af);
    break;
  case 2:
    *af = createAfFromConsole();
    if (*af == NULL)
    {
      printf("\nError al crear el automata desde la consola.\n");
    }
    else
    {
      printf("\nAutomata creado exitosamente desde la consola.\n");
    }
    menu(af);
    break;
  case 3:
    int opt = 0;
    printf("\nQue parte de la 5-upla del automata quieres mostrar?\n");
    printf("1. Conjunto de estados (Q)\n");
    printf("2. Alfabeto (Sigma)\n");
    printf("3. Funcion de transicion (delta)\n");
    printf("4. Estado inicial (q0)\n");
    printf("5. Conjunto de estados de aceptacion (F)\n");
    printf("0. Mostrar todo\n");
    printf("Selecciona una opcion: ");
    scanf("%d", &opt);
    printAf(*af, opt);
    menu(af);
    break;
  case 4:
    if (*af != NULL)
    {
      printAf(*af, 0);
      if (isDeterministic(*af))
      {
        printf("\nEl automata es determinista.\n");
      }
      else
      {
        printf("\nEl automata no es determinista.\n");
      }
    }
    menu(af);
    break;
  case 5:
    if (*af != NULL)
    {
      Str input = load2("001010");
      if (acceptsString(*af, input))
      {
        printf("\nEl automata acepta la cadena ");
        print(input);
        printf("'.\n");
      }
      else
      {
        printf("\nEl automata no acepta la cadena ");
        print(input);
        printf("'.\n");
      }
    }
    menu(af);
    break;
  case 6:
    if (*af != NULL)
    {
      printf("\nIngresa una cadena para verificar si el automata la acepta: ");
      fflush(stdin);
      Str input = load();
      if (acceptsString(*af, input))
      {
        printf("\nEl automata acepta la cadena ");
        print(input);
        printf("'.\n");
      }
      else
      {
        printf("\nEl automata no acepta la cadena ");
        print(input);
        printf("'.\n");
      }
    }
    menu(af);
    break;
  case 7:
    printf("\nCreando caso de prueba para un AFD que acepte cadenas sobre 0,1 con cantidad impar de 0's...\n");
    Af afd = parseAfFromString(load2("[{q_par,q_impar},{0,1},[{q_par,0,q_impar},{q_par,1,q_par},{q_impar,0,q_par},{q_impar,1,q_impar}],q_par,{q_impar}]"));
    if (afd == NULL)
    {
      printf("\nError al crear el AFD.\n");
    }
    else
    {
      printf("\nAFD creado exitosamente.\n");
      printAf(afd, 0);
      fflush(stdin);
      Str testString = load();
      if (acceptsString(afd, testString))
      {
        printf("\nEl AFD acepta la cadena ");
        print(testString);
        printf("'.\n");
      }
      else
      {
        printf("\nEl AFD no acepta la cadena ");
        print(testString);
        printf("'.\n");
      }
      destroyAf(&afd);
    }
    menu(af);
    break;
  case 0:
    printf("\nSaliendo del programa.\n");
    break;
  default:
    printf("\nOpcion invalida. Por favor, selecciona una opcion valida.\n");
    menu(af);
    break;
  }
}