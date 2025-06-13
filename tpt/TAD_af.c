#include "TAD_af.h"
#include "TAD_tree.h"
#include <stdio.h>
#include <stdlib.h>

Af createAf()
{
  Af af = (Af)malloc(sizeof(AfStruct));
  if (af == NULL)
  {
    printf("Error: No se pudo asignar memoria para el automata\n");
    return NULL;
  }

  af->Q = NULL;
  af->Sigma = NULL;
  af->delta = NULL;
  af->q0 = NULL;
  af->F = NULL;
  return af;
}

void destroyAf(Af *af)
{
  if (af == NULL || *af == NULL)
  {
    return;
  }

  if ((*af)->Q != NULL)
  {
    destroyTData(&((*af)->Q));
  }
  if ((*af)->Sigma != NULL)
  {
    destroyTData(&((*af)->Sigma));
  }
  if ((*af)->delta != NULL)
  {
    destroyTData(&((*af)->delta));
  }
  if ((*af)->q0 != NULL)
  {
    destroyTData(&((*af)->q0));
  }
  if ((*af)->F != NULL)
  {
    destroyTData(&((*af)->F));
  }
  free(*af);
  *af = NULL;
}

int setStates(Af af, Set states)
{
  if (af == NULL || states == NULL)
    return 0;
  af->Q = createNodeSet(states);
  return (af->Q != NULL) ? 1 : 0;
}

int setAlphabet(Af af, Set alphabet)
{
  if (af == NULL || alphabet == NULL)
    return 0;
  af->Sigma = createNodeSet(alphabet);
  return (af->Sigma != NULL) ? 1 : 0;
}

int setInitialState(Af af, Str initialState)
{
  if (af == NULL || initialState == NULL)
    return 0;

  if (af->Q != NULL && !belongsToStates(af, initialState))
  {
    printf("Error: El estado inicial no pertenece al conjunto de estados\n");
    return 0;
  }

  af->q0 = createNodeStr(initialState);
  return (af->q0 != NULL) ? 1 : 0;
}

int setFinalStates(Af af, Set finalStates)
{
  if (af == NULL || finalStates == NULL)
    return 0;

  af->F = createNodeSet(finalStates);
  return (af->F != NULL) ? 1 : 0;
}

tData createTransition(Str fromState, Str symbol, Str toState)
{
  Set transitionSet = createSet();
  if (transitionSet == NULL)
    return NULL;

  appendSet(&transitionSet, fromState);
  appendSet(&transitionSet, symbol);
  appendSet(&transitionSet, toState);

  return createNodeSet(transitionSet);
}

int addTransition(Af af, Str fromState, Str symbol, Str toState)
{
  if (af == NULL || fromState == NULL || symbol == NULL || toState == NULL)
    return 0;

  if (af->Q != NULL && (!belongsToStates(af, fromState) ||
                        !belongsToStates(af, toState)))
  {
    printf("Error: Los estados deben pertenecer al conjunto Q\n");
    return 0;
  }

  if (af->Sigma != NULL && !belongsToAlphabet(af, symbol))
  {
    printf("Error: El simbolo debe pertenecer al alfabeto\n");
    return 0;
  }

  tData transition = createTransition(fromState, symbol, toState);
  if (transition == NULL)
    return 0;

  if (af->delta == NULL)
  {
    List newList = createList();
    af->delta = createNodeList(newList);
    if (af->delta == NULL)
      return 0;
  }

  appendNodeList(&(af->delta), transition);
  return 1;
}

int belongsToStates(Af af, Str state)
{
  if (af == NULL || af->Q == NULL || state == NULL)
    return 0;

  tData current = af->Q;
  while (current != NULL)
  {
    if (current->data != NULL && current->data->nodeType == STR)
    {
      if (compareStr(current->data->string, state) == 1)
      {
        return 1;
      }
    }
    current = current->next;
  }
  return 0;
}

int belongsToAlphabet(Af af, Str symbol)
{
  if (af == NULL || af->Sigma == NULL || symbol == NULL)
    return 0;

  tData current = af->Sigma;
  while (current != NULL)
  {
    if (current->data != NULL && current->data->nodeType == STR)
    {
      if (compareStr(current->data->string, symbol) == 1)
      {
        return 1;
      }
    }
    current = current->next;
  }
  return 0;
}

void printAf(Af af, int showElement)
{
  if (af == NULL)
  {
    printf("Automata vacio\n");
    return;
  }

  printf(" \n=== AUTOMATA FINITO ===\n");

  switch (showElement)
  {
  case 1:
    printf("Estados (Q): ");
    if (af->Q != NULL)
    {
      printStruct(af->Q);
    }
    else
    {
      printf("No definido");
    }
    printf("\n");
    break;
  case 2:
    printf("Alfabeto (Sigma): ");
    if (af->Sigma != NULL)
    {
      printStruct(af->Sigma);
    }
    else
    {
      printf("No definido");
    }
    printf("\n");
    break;
  case 3:
    printf("\nTransiciones (delta):\n");
    printTransitions(af);
    break;
  case 4:
    printf("\nEstado inicial (q0): ");
    if (af->q0 != NULL)
    {
      printStruct(af->q0);
    }
    else
    {
      printf("No definido");
    }
    printf("\n");
    break;
  case 5:
    printf("\nEstados finales (F): ");
    if (af->F != NULL)
    {
      printStruct(af->F);
    }
    else
    {
      printf("No definido");
    }
    printf("\n");
    break;

  default:
    printf("Estados (Q): ");
    if (af->Q != NULL)
    {
      printStruct(af->Q);
    }
    else
    {
      printf("No definido");
    }

    printf("\nAlfabeto (Sigma): ");
    if (af->Sigma != NULL)
    {
      printStruct(af->Sigma);
    }
    else
    {
      printf("No definido");
    }

    printf("\nEstado inicial (q0): ");
    if (af->q0 != NULL)
    {
      printStruct(af->q0);
    }
    else
    {
      printf("No definido");
    }

    printf("\nEstados finales (F): ");
    if (af->F != NULL)
    {
      printStruct(af->F);
    }
    else
    {
      printf("No definido");
    }

    printf("\nTransiciones (delta):\n");
    printTransitions(af);
    break;
  }
}

void printTransitions(Af af)
{
  if (af == NULL || af->delta == NULL)
  {
    printf("  No hay transiciones definidas\n");
    return;
  }

  tData deltaList = af->delta;
  int transitionNum = 1;

  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == SET)
    {
      printf("  %d. ", transitionNum++);
      printStruct(deltaList->data);
      printf("\n");
    }
    deltaList = deltaList->next;
  }
}

void skipWhitespace(Str str, int *position)
{
  if (str == NULL || position == NULL)
    return;

  Str current = str;
  for (int i = 0; i < *position && current != NULL; i++)
  {
    current = current->sig;
  }

  while (current != NULL && (current->character == ' ' || current->character == '\t' || current->character == '\n'))
  {
    (*position)++;
    current = current->sig;
  }
}

Str parseString(Str str, int *position)
{
  if (str == NULL || position == NULL)
    return NULL;

  skipWhitespace(str, position);

  Str current = str;
  for (int i = 0; i < *position && current != NULL; i++)
  {
    current = current->sig;
  }

  if (current == NULL)
    return NULL;

  Str result = createStr();
  Str resultTail = NULL;

  while (current != NULL && current->character != ',' && current->character != ']' &&
         current->character != '}' && current->character != ' ')
  {
    Str newNode = createStr();
    if (newNode == NULL)
      return NULL;

    newNode->character = current->character;
    newNode->sig = NULL;

    if (result->character == '\0')
    {
      result->character = current->character;
      resultTail = result;
    }
    else
    {
      resultTail->sig = newNode;
      resultTail = newNode;
    }

    (*position)++;
    current = current->sig;
  }

  return (result->character != '\0') ? result : NULL;
}

tData parseSet(Str str, int *position)
{
  if (str == NULL || position == NULL)
    return NULL;

  skipWhitespace(str, position);

  Str current = str;
  for (int i = 0; i < *position && current != NULL; i++)
  {
    current = current->sig;
  }

  if (current == NULL || current->character != '{')
    return NULL;

  (*position)++;

  Set resultSet = createSet();
  int first = 1;

  while (1)
  {
    skipWhitespace(str, position);

    current = str;
    for (int i = 0; i < *position && current != NULL; i++)
    {
      current = current->sig;
    }

    if (current == NULL)
      break;

    if (current->character == '}')
    {
      (*position)++;
      break;
    }

    if (!first && current->character == ',')
    {
      (*position)++;
      skipWhitespace(str, position);
    }
    first = 0;

    if (current->character == '{')
    {
      tData nestedSet = parseSet(str, position);
      if (nestedSet != NULL && nestedSet->nodeType == SET)
      {
        Set traditionalSet = createSet();
        tData current_nested = nestedSet;

        while (current_nested != NULL)
        {
          if (current_nested->data != NULL && current_nested->data->nodeType == STR)
          {
            appendSet(&traditionalSet, current_nested->data->string);
          }
          current_nested = current_nested->next;
        }

        Str setStr = toStrSet(traditionalSet);
        appendSet(&resultSet, setStr);

        destroySet(&traditionalSet);
      }
    }
    else
    {
      Str element = parseString(str, position);
      if (element != NULL)
      {
        appendSet(&resultSet, element);
      }
    }
  }

  return createNodeSet(resultSet);
}

tData parseList(Str str, int *position)
{
  if (str == NULL || position == NULL)
    return NULL;

  skipWhitespace(str, position);

  Str current = str;
  for (int i = 0; i < *position && current != NULL; i++)
  {
    current = current->sig;
  }

  if (current == NULL || current->character != '[')
    return NULL;

  (*position)++;

  List resultList = createList();
  tData listNode = createNodeList(resultList);
  int first = 1;

  while (1)
  {
    skipWhitespace(str, position);

    current = str;
    for (int i = 0; i < *position && current != NULL; i++)
    {
      current = current->sig;
    }

    if (current == NULL)
      break;

    if (current->character == ']')
    {
      (*position)++;
      break;
    }

    if (!first && current->character == ',')
    {
      (*position)++;
      skipWhitespace(str, position);
    }
    first = 0;

    tData component = parseComponent(str, position);
    if (component != NULL)
    {
      appendNodeList(&listNode, component);
    }
  }

  return listNode;
}

tData parseComponent(Str str, int *position)
{
  if (str == NULL || position == NULL)
    return NULL;

  skipWhitespace(str, position);

  Str current = str;
  for (int i = 0; i < *position && current != NULL; i++)
  {
    current = current->sig;
  }

  if (current == NULL)
    return NULL;

  if (current->character == '{')
  {
    return parseSet(str, position);
  }
  else if (current->character == '[')
  {
    return parseList(str, position);
  }
  else
  {
    Str simpleStr = parseString(str, position);
    return (simpleStr != NULL) ? createNodeStr(simpleStr) : NULL;
  }
}

Af parseAfFromString(Str afStr)
{
  if (afStr == NULL)
    return NULL;

  Af af = createAf();
  if (af == NULL)
    return NULL;

  int position = 0;

  skipWhitespace(afStr, &position);

  Str current = afStr;
  for (int i = 0; i < position && current != NULL; i++)
  {
    current = current->sig;
  }

  if (current == NULL || current->character != '[')
  {
    destroyAf(&af);
    return NULL;
  }

  position++;

  tData components[5];
  for (int i = 0; i < 5; i++)
  {
    components[i] = parseComponent(afStr, &position);
    if (components[i] == NULL)
    {
      destroyAf(&af);
      return NULL;
    }

    if (i < 4)
    {
      skipWhitespace(afStr, &position);
      current = afStr;
      for (int j = 0; j < position && current != NULL; j++)
      {
        current = current->sig;
      }
      if (current != NULL && current->character == ',')
      {
        position++;
      }
    }
  }

  af->Q = components[0];
  af->Sigma = components[1];
  af->delta = components[2];
  af->q0 = components[3];
  af->F = components[4];

  return af;
}

Set readSet(const char *componentName)
{
  printf("DEFINIR %s\n", componentName);

  while (1)
  {
    printf("Ingresa %s en formato {elemento1,elemento2,...}: ", componentName);
    Str input = load();

    if (input == NULL)
    {
      printf("Error al leer la entrada. Intenta de nuevo.\n");
      continue;
    }

    int position = 0;
    tData parsedSet = parseSet(input, &position);

    if (parsedSet == NULL || parsedSet->nodeType != SET)
    {
      printf("Formato para conjunto invalido.\n");
      continue;
    }

    Set resultSet = createSet();
    tData current = parsedSet;

    while (current != NULL)
    {
      if (current->data != NULL && current->data->nodeType == STR)
      {
        appendSet(&resultSet, current->data->string);
      }
      current = current->next;
    }

    return resultSet;
  }
}

Str readStr(const char *componentName, Set validStates)
{
  printf("DEFINIR %s\n", componentName);

  if (validStates != NULL)
  {
    printf("Estados validos: ");
    showSet(validStates);
    printf("\n");
  }

  while (1)
  {
    printf("Ingresa %s: ", componentName);
    Str input = load();

    if (input == NULL)
    {
      printf("Error al leer la entrada. Intenta de nuevo.\n");
      continue;
    }

    if (validStates != NULL && !belongsTo(validStates, input))
    {
      printf("El estado '");
      print(input);
      printf("' no pertenece al conjunto de estados validos.\n");
      printf("\n\n");
      continue;
    }

    return input;
  }
}

int readTransition(Str input, Str *origen, Str *simbolo, Str *destino)
{
  if (input == NULL)
    return 0;

  *origen = NULL;
  *simbolo = NULL;
  *destino = NULL;

  Str parts[3];
  for (int i = 0; i < 3; i++)
  {
    parts[i] = createStr();
  }

  int currentPart = 0;
  Str current = input;
  Str partTail[3] = {NULL, NULL, NULL};

  while (current != NULL && currentPart < 3)
  {
    if (current->character == ',')
    {
      currentPart++;
      current = current->sig;
      continue;
    }

    if (parts[currentPart]->character == '\0')
    {
      parts[currentPart]->character = current->character;
      partTail[currentPart] = parts[currentPart];
    }
    else
    {
      Str newNode = createStr();
      newNode->character = current->character;
      newNode->sig = NULL;
      partTail[currentPart]->sig = newNode;
      partTail[currentPart] = newNode;
    }

    current = current->sig;
  }

  if (currentPart != 2)
  {
    return 0;
  }

  for (int i = 0; i < 3; i++)
  {
    if (parts[i]->character == '\0')
    {
      return 0;
    }
  }

  *origen = parts[0];
  *simbolo = parts[1];
  *destino = parts[2];

  return 1;
}

Af createAfFromConsole()
{
  printf("\nConstruye un automata usando el siguiente formato.\n");
  showFormatExamples();
  printf("Estructura: M = (Q, Sigma, delta, q0, F)\n");

  Af af = createAf();
  if (af == NULL)
  {
    printf("Error: No se pudo crear el automata.\n");
    return NULL;
  }

  Set states = readSet("CONJUNTO DE ESTADOS (Q)");

  if (states == NULL || states->string == NULL)
  {
    printf("Error: Debes definir al menos un estado.\n");
    destroyAf(&af);
    return NULL;
  }

  setStates(af, states);

  Set alphabet = readSet("ALFABETO (Sigma)");

  if (alphabet == NULL || alphabet->string == NULL)
  {
    printf("Error: Debes definir al menos un simbolo.\n");
    destroyAf(&af);
    return NULL;
  }

  setAlphabet(af, alphabet);

  Str initialState = readStr("ESTADO INICIAL (q0)", states);

  setInitialState(af, initialState);

  Set finalStates = readSet("ESTADOS FINALES (F)");

  Set temp = finalStates;
  while (temp != NULL && temp->string != NULL)
  {
    if (!belongsTo(states, temp->string))
    {
      printf("Error: El estado final '");
      print(temp->string);
      printf("' no pertenece a Q.\n");
      destroyAf(&af);
      return NULL;
    }
    temp = temp->sig;
  }

  setFinalStates(af, finalStates);

  printf("DEFINIR TRANSICIONES (delta)\n");
  printf("=====================================\n");
  printf("Ingresa las transiciones una por una:\n");
  printf("Formato: origen,simbolo,destino\n");
  printf("Escribe 'fin' para terminar.\n\n");

  int transitionCount = 0;
  while (1)
  {
    printf("Transición #%d (o 'fin'): ", transitionCount + 1);

    Str input = load();
    if (input == NULL)
    {
      printf("Error al leer entrada. Intenta de nuevo.\n");
      continue;
    }

    if (compareStr(input, load2("fin")) == 1)
    {
      break;
    }

    Str origen, simbolo, destino;
    if (!readTransition(input, &origen, &simbolo, &destino))
    {
      printf("Formato inválido. Usa: origen,simbolo,destino\n");
      continue;
    }

    if (!belongsTo(states, origen))
    {
      printf("Estado origen no válido: \"");
      print(origen);
      printf("\"\n");
      printf("Estados disponibles: ");
      showSet(states);
      printf("\n");
      continue;
    }

    if (!belongsTo(alphabet, simbolo))
    {
      printf("Símbolo no válido: \"");
      print(simbolo);
      printf("\"\n");
      printf("Alfabeto disponible: ");
      showSet(alphabet);
      printf("\n");
      continue;
    }

    if (!belongsTo(states, destino))
    {
      printf("Estado destino no válido: \"");
      print(destino);
      printf("\"\n");
      printf("Estados disponibles: ");
      showSet(states);
      printf("\n");
      continue;
    }

    if (addTransition(af, origen, simbolo, destino))
    {
      printf("Transición agregada: ");
      print(origen);
      printf(", ");
      print(simbolo);
      printf("-> ");
      print(destino);
      printf("\n");
      transitionCount++;
    }
    else
    {
      printf("Error interno al agregar la transición\n");
    }

    printf("\n");
  }

  printf("\nAUTOMATA CREADO EXITOSAMENTE!\n");

  return af;
}

// Funciones para analizar si un automata es determinista
int isDeterministic(Af af)
{
  if (af == NULL)
    return 0;

  if (hasEpsilonTransitions(af))
  {
    return 0;
  }

  if (af->Q == NULL || af->Sigma == NULL)
    return 0;

  tData stateNode = af->Q;
  while (stateNode != NULL)
  {
    if (stateNode->data != NULL && stateNode->data->nodeType == STR)
    {
      Str currentState = stateNode->data->string;

      tData symbolNode = af->Sigma;
      while (symbolNode != NULL)
      {
        if (symbolNode->data != NULL && symbolNode->data->nodeType == STR)
        {
          Str currentSymbol = symbolNode->data->string;

          if (hasMultipleTransitions(af, currentState, currentSymbol))
          {
            return 0;
          }
        }
        symbolNode = symbolNode->next;
      }
    }
    stateNode = stateNode->next;
  }

  return 1;
}

int hasEpsilonTransitions(Af af)
{
  if (af == NULL || af->delta == NULL)
    return 0;

  // Recorrer todas las transiciones del automata
  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == SET)
    {

      // Cada transicion es un conjunto: {estado_origen, simbolo, estado_destino}
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      // Extraer los 3 elementos de la transicion
      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      // Verificar el simbolo (elemento en posicion 1)
      if (index >= 2 && elements[1] != NULL && elements[1]->nodeType == STR)
      {
        Str symbol = elements[1]->string;

        // Verificar si es una transicion epsilon
        if (symbol == NULL ||
            symbol->character == '\0' ||                 // Cadena vacia
            compareStr(symbol, load2("epsilon")) == 1 || // Palabra "epsilon"
            compareStr(symbol, load2("")) == 1)          // Cadena explicitamente vacia
        {
          return 1; // Si tiene transiciones epsilon
        }
      }
    }
    deltaList = deltaList->next;
  }

  return 0; // NO tiene transiciones epsilon
}

int countTransitions(Af af, Str state, Str symbol)
{
  if (af == NULL || af->delta == NULL ||
      state == NULL || symbol == NULL)
  {
    return 0;
  }

  int count = 0;

  // Recorrer todas las transiciones del automata
  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == SET)
    {

      // Cada transicion: {estado_origen, simbolo, estado_destino}
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      // Extraer los 3 elementos de la transicion
      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      // Verificar si esta transicion coincide con el par (estado, simbolo) buscado
      if (index == 3 && elements[0] != NULL && elements[1] != NULL)
      {
        if (elements[0]->nodeType == STR && elements[1]->nodeType == STR)
        {
          // Comparar estado origen y simbolo
          if (compareStr(elements[0]->string, state) == 1 &&
              compareStr(elements[1]->string, symbol) == 1)
          {
            count++; // Encontramos una transicion que coincide
          }
        }
      }
    }
    deltaList = deltaList->next;
  }

  return count;
}

int hasMultipleTransitions(Af af, Str state, Str symbol)
{
  return countTransitions(af, state, symbol) > 1;
}

void printDeterminismAnalysis(Af af)
{
  if (af == NULL)
  {
    printf("Error: Automata nulo - no se puede analizar\n");
    return;
  }

  printf("======ANALISIS DE DETERMINISMO=======\n");

  // PASO 1: Determinar si es determinista
  int deterministic = isDeterministic(af);
  printf("\nRESULTADO: ");
  if (deterministic)
  {
    printf("AUTOMATA FINITO DETERMINISTA (AFD)\n");
  }
  else
  {
    printf("AUTOMATA FINITO NO DETERMINISTA (AFND)\n");
  }
}

// Funciones para determinar aceptacion de cadenas

tData getTransition(Af af, Str currentState, Str symbol)
{
  if (af == NULL || af->delta == NULL ||
      currentState == NULL || symbol == NULL)
    return NULL;

  // Recorrer la lista de transiciones
  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == SET)
    {
      // Cada transicion es un conjunto de 3 elementos
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      // Extraer los 3 elementos de la transicion
      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      // Verificar si coincide con el estado actual y simbolo
      if (index == 3 && elements[0] != NULL && elements[1] != NULL && elements[2] != NULL)
      {
        if (compareStr(elements[0]->string, currentState) == 1 &&
            compareStr(elements[1]->string, symbol) == 1)
        {
          return elements[2]; // Retornar el estado destino
        }
      }
    }
    deltaList = deltaList->next;
  }

  return NULL; // No se encontro transicion
}

int isAcceptingState(Af af, Str state)
{
  if (af == NULL || af->F == NULL || state == NULL)
    return 0;

  // Recorrer el conjunto F y verificar si el estado es de aceptacion
  tData current = af->F;
  while (current != NULL)
  {
    if (current->data != NULL && current->data->nodeType == STR)
    {
      if (compareStr(current->data->string, state) == 1)
      {
        return 1;
      }
    }
    current = current->next;
  }
  return 0;
}

int acceptsString(Af af, Str input)
{
  if (af == NULL || af->q0 == NULL)
    return 0;

  Str currentStateStr = processString(af, input);
  if (currentStateStr == NULL)
    return 0;

  int result = isAcceptingState(af, currentStateStr);
  return result;
}

Str processString(Af af, Str input)
{
  if (af == NULL || af->q0 == NULL)
    return NULL;

  // Comenzar desde el estado inicial
  Str currentState = af->q0->string;
  Str inputAux = input;

  // Procesar cada simbolo de entrada
  while (inputAux != NULL)
  {
    // Crear un string de un solo caracter para el simbolo actual
    Str symbol = createStr();
    symbol->character = inputAux->character;
    symbol->sig = NULL;

    // Buscar la transicion correspondiente
    tData nextStateNode = getTransition(af, currentState, symbol);
    if (nextStateNode == NULL || nextStateNode->nodeType != STR)
    {
      // No hay transicion valida
      return NULL;
    }

    currentState = nextStateNode->string;
    inputAux = inputAux->sig;
  }

  return currentState;
}

void showFormatExamples()
{
  printf("\n EJEMPLOS DE FORMATO:\n");
  printf("==================================\n");
  printf("* Conjunto: {q0,q1,q2} o {0,1,a,b}\n");
  printf("* Lista: [{q0,0,q1},{q1,1,q2}] \n");
  printf("* String simple: q0 o estado_inicial\n");
  printf("* Conjunto vacio: {}\n");
  printf("* Lista vacia: []\n\n");
}

/*
afnd2afd(Af af):
  sea A = (Q, Sigma, delta, q0, F)
  q0b = {a0}
  Qb={q0b}
  mientras exista P em Qb | deltab(P, a) = null para cualquier a en Sigma:
    para cada a en SIgma:
      deltab(P, a) = UNION r en P => delta(r, a)
      Qb = Qb Union {deltab(P, a)}

  Fb = {}

  para cada R en Qb:
    si R Intersec F != vacío
      Fb = Fb Union {R}

  return [Qb, Sigma, deltab, q0b, Fb]

*/