#ifndef TAD_AF_H
#define TAD_AF_H

#include "TAD_tree.h"
#include "TAD_string.h"
#include "TAD_set.h"
#include "TAD_list.h"

// Estructura del autómata finito
typedef struct
{
  tData Q;     // Conjunto de estados (SET de strings)
  tData Sigma; // Alfabeto (SET de strings)
  tData delta; // Función de transición (LIST de SETs de 3 elementos: {estado_origen, símbolo, estado_destino})
  tData q0;    // Estado inicial (STR)
  tData F;     // Conjunto de estados de aceptación (SET de strings)
} AfStruct;

typedef AfStruct *Af;

// Funciones principales
Af createAf();
void destroyAf(Af *af);

// Funciones para construir el autómata
int setStates(Af af, Set states);
int setAlphabet(Af af, Set alphabet);
int setInitialState(Af af, Str initialState);
int setFinalStates(Af af, Set finalStates);
int addTransition(Af af, Str fromState, Str symbol, Str toState);
tData createTransition(Str fromState, Str symbol, Str toState);

// Funciones de validación
int belongsToStates(Af af, Str state);
int belongsToAlphabet(Af af, Str symbol);

// Funciones de aceptacion de cadenas
int isAcceptingState(Af af, Str state);
Str processString(Af af, Str input);
int acceptsString(Af af, Str input);
tData getTransition(Af af, Str currentState, Str symbol);

// Funciones de visualización
void printAf(Af af, int showElement);
void printTransitions(Af af);

// Funciones de parsing
Af parseAfFromString(Str afStr);
tData parseComponent(Str str, int *position);
tData parseSet(Str str, int *position);
tData parseList(Str str, int *position);
Str parseString(Str str, int *position);
void skipWhitespace(Str str, int *position);

// Funciones para determinismo
int isDeterministic(Af af);
int hasEpsilonTransitions(Af af);
int hasMultipleTransitions(Af af, Str state, Str symbol);
int countTransitions(Af af, Str state, Str symbol);
void printDeterminismAnalysis(Af af);

// Funciones interactivas
Af createAfFromConsole();
Set readSet(const char *componentName);
Str readStr(const char *componentName, Set validStates);
int readTransition(Str input, Str *origen, Str *simbolo, Str *destino);
void showFormatExamples();

#endif