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
  List transitionList = createList();
  if (transitionList == NULL)
    return NULL;

  append(&transitionList, fromState);
  append(&transitionList, symbol);
  append(&transitionList, toState);

  return createNodeList(transitionList);
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
    if (deltaList->data != NULL && deltaList->data->nodeType == LIST)
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

  (*position)++; // Saltar el '['

  // Crear el nodo principal de la lista
  tData listHead = (tData)malloc(sizeof(struct dataType));
  if (listHead == NULL)
    return NULL;

  listHead->nodeType = LIST;
  listHead->data = NULL;
  listHead->next = NULL;

  tData listTail = NULL;
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
      (*position)++; // Saltar el ']'
      break;
    }

    // Si no es el primer elemento, esperamos una coma
    if (!first && current->character == ',')
    {
      (*position)++; // Saltar la coma
      skipWhitespace(str, position);
    }
    first = 0;

    tData component = parseComponent(str, position);
    if (component != NULL)
    {
      tData newListNode = (tData)malloc(sizeof(struct dataType));
      if (newListNode == NULL)
        return NULL;

      newListNode->nodeType = LIST;
      newListNode->data = component;
      newListNode->next = NULL;

      if (listHead->data == NULL)
      {
        listHead->data = component;
        listTail = listHead;
      }
      else
      {
        listTail->next = newListNode;
        listTail = newListNode;
      }
    }
  }

  return listHead;
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

  (*position)++; // Saltar el '{'

  tData setHead = (tData)malloc(sizeof(struct dataType));
  if (setHead == NULL)
    return NULL;

  setHead->nodeType = SET;
  setHead->data = NULL;
  setHead->next = NULL;

  tData setTail = NULL;
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
      (*position)++; // Saltar el '}'
      break;
    }

    if (!first && current->character == ',')
    {
      (*position)++; // Saltar la coma
      skipWhitespace(str, position);
    }
    first = 0;

    tData component = parseComponent(str, position);
    if (component != NULL)
    {
      tData newSetNode = (tData)malloc(sizeof(struct dataType));
      if (newSetNode == NULL)
        return NULL;

      newSetNode->nodeType = SET;
      newSetNode->data = component;
      newSetNode->next = NULL;

      if (setHead->data == NULL)
      {
        setHead->data = component;
        setTail = setHead;
      }
      else
      {
        setTail->next = newSetNode;
        setTail = newSetNode;
      }
    }
  }

  return setHead;
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
  if (result == NULL)
    return NULL;

  Str resultTail = result;
  int hasContent = 0;

  while (current != NULL &&
         current->character != ',' &&
         current->character != ']' &&
         current->character != '}' &&
         current->character != ' ' &&
         current->character != '\t' &&
         current->character != '\n')
  {
    if (!hasContent)
    {
      result->character = current->character;
      hasContent = 1;
    }
    else
    {
      Str newNode = createStr();
      if (newNode == NULL)
        return NULL;

      newNode->character = current->character;
      newNode->sig = NULL;
      resultTail->sig = newNode;
      resultTail = newNode;
    }

    (*position)++;
    current = current->sig;
  }

  return hasContent ? result : NULL;
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
    printf("Transicion #%d (o 'fin'): ", transitionCount + 1);

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
      printf("Formato invalido. Usa: origen,simbolo,destino\n");
      continue;
    }

    if (!belongsTo(states, origen))
    {
      printf("Estado origen no valido: \"");
      print(origen);
      printf("\"\n");
      printf("Estados disponibles: ");
      showSet(states);
      printf("\n");
      continue;
    }

    if (!belongsTo(alphabet, simbolo))
    {
      printf("Simbolo no valido: \"");
      print(simbolo);
      printf("\"\n");
      printf("Alfabeto disponible: ");
      showSet(alphabet);
      printf("\n");
      continue;
    }

    if (!belongsTo(states, destino))
    {
      printf("Estado destino no valido: \"");
      print(destino);
      printf("\"\n");
      printf("Estados disponibles: ");
      showSet(states);
      printf("\n");
      continue;
    }

    if (addTransition(af, origen, simbolo, destino))
    {
      printf("Transicion agregada: ");
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
      printf("Error interno al agregar la transicion\n");
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

  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == LIST)
    {
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      if (index >= 2 && elements[1] != NULL && elements[1]->nodeType == STR)
      {
        Str symbol = elements[1]->string;

        if (symbol == NULL ||
            symbol->character == '\0' ||                 // Cadena vacia
            compareStr(symbol, load2("epsilon")) == 1 || // Palabra "epsilon"
            compareStr(symbol, load2("")) == 1)          // Cadena explicitamente vacia
        {
          return 1;
        }
      }
    }
    deltaList = deltaList->next;
  }

  return 0;
}

int countTransitions(Af af, Str state, Str symbol)
{
  if (af == NULL || af->delta == NULL ||
      state == NULL || symbol == NULL)
  {
    return 0;
  }

  int count = 0;

  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == LIST)
    {
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      if (index == 3 && elements[0] != NULL && elements[1] != NULL)
      {
        if (elements[0]->nodeType == STR && elements[1]->nodeType == STR)
        {
          if (compareStr(elements[0]->string, state) == 1 &&
              compareStr(elements[1]->string, symbol) == 1)
          {
            count++;
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

  tData deltaList = af->delta;
  while (deltaList != NULL)
  {
    if (deltaList->data != NULL && deltaList->data->nodeType == LIST)
    {
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      if (index == 3 && elements[0] != NULL && elements[1] != NULL && elements[2] != NULL)
      {
        if (elements[0]->nodeType == STR && elements[1]->nodeType == STR && elements[2]->nodeType == STR)
        {
          if (compareStr(elements[0]->string, currentState) == 1 &&
              compareStr(elements[1]->string, symbol) == 1)
          {
            return elements[2];
          }
        }
      }
    }
    deltaList = deltaList->next;
  }
  printf("No se encontro transicion\n");
  return NULL;
}

int acceptsString(Af af, Str input)
{
  if (af == NULL || af->q0 == NULL)
    return 0;

  Set currentStateSet = processString(af, input);

  if (currentStateSet == NULL)
  {
    printf("Error: processString retorno NULL\n");
    return 0;
  }

  printf("Estados finales alcanzados: ");
  showSet(currentStateSet);

  Set aux = currentStateSet;
  int result = 0;
  while (aux != NULL && aux->string != NULL)
  {
    if (isAcceptingState(af, aux->string))
    {
      result = 1;
      break;
    }
    aux = aux->sig;
  }
  return result;
}

Set getAllTransitions(Af af, Str currentState, Str symbol)
{
  if (af == NULL || af->delta == NULL || currentState == NULL || symbol == NULL)
  {
    printf("ERROR: Parametros nulos en getAllTransitions\n");
    return NULL;
  }

  Set resultStates = createSet();
  if (resultStates == NULL)
  {
    printf("Error: No se pudo crear resultStates\n");
    return NULL;
  }

  tData deltaList = af->delta;
  int transitionCount = 0;

  while (deltaList != NULL)
  {
    transitionCount++;

    if (deltaList->data != NULL && deltaList->data->nodeType == LIST)
    {
      tData transition = deltaList->data;
      tData elements[3] = {NULL, NULL, NULL};
      int index = 0;

      tData current = transition;
      while (current != NULL && index < 3)
      {
        elements[index] = current->data;
        current = current->next;
        index++;
      }

      if (index == 3 && elements[0] != NULL && elements[1] != NULL && elements[2] != NULL)
      {
        if (elements[0]->nodeType == STR && elements[1]->nodeType == STR && elements[2]->nodeType == STR)
        {
          if (compareStr(elements[0]->string, currentState) == 1 &&
              compareStr(elements[1]->string, symbol) == 1)
          {
            appendSet(&resultStates, elements[2]->string);
          }
        }
      }
    }
    deltaList = deltaList->next;
  }

  return resultStates;
}

Set processNextSymbol(Af af, Set currentStates, Str symbol)
{
  if (af == NULL || currentStates == NULL || symbol == NULL)
  {
    printf("Error: Parametros nulos en processNextSymbol\n");
    return NULL;
  }

  Set nextStates = createSet();
  if (nextStates == NULL)
  {
    printf("Error: No se pudo crear nextStates\n");
    return NULL;
  }

  Set currentStateNode = currentStates;
  while (currentStateNode != NULL && currentStateNode->string != NULL)
  {
    Set transitionStates = getAllTransitions(af, currentStateNode->string, symbol);

    if (transitionStates != NULL)
    {
      Set transNode = transitionStates;
      while (transNode != NULL && transNode->string != NULL)
      {
        appendSet(&nextStates, transNode->string);
        transNode = transNode->sig;
      }

      transitionStates = NULL;
    }

    currentStateNode = currentStateNode->sig;
  }

  return nextStates;
}

Set processString(Af af, Str input)
{
  if (af == NULL || af->q0 == NULL)
  {
    printf("Error: Automata nulo o sin estado inicial\n");
    return NULL;
  }

  if (input == NULL)
  {
    Set initialStates = createSet();
    if (initialStates == NULL)
    {
      printf("Error: No se pudo crear el conjunto de estados\n");
      return NULL;
    }
    appendSet(&initialStates, af->q0->string);
    return initialStates;
  }

  if (isDeterministic(af))
  {
    Str currentState = af->q0->string;
    Str inputAux = input;

    // Procesar cada simbolo de entrada
    while (inputAux != NULL)
    {
      Str symbol = createStr();
      if (symbol == NULL)
      {
        printf("Error: No se pudo crear simbolo\n");
        return NULL;
      }
      symbol->character = inputAux->character;
      symbol->sig = NULL;

      tData nextStateNode = getTransition(af, currentState, symbol);
      if (nextStateNode == NULL || nextStateNode->nodeType != STR)
      {
        printf("No se encontro transicion para simbolo '%c' desde estado ", inputAux->character);
        print(currentState);
        printf("\n");
        return NULL;
      }

      currentState = nextStateNode->string;
      inputAux = inputAux->sig;
    }

    Set currentStates = createSet();
    if (currentStates == NULL)
    {
      printf("Error: No se pudo crear el conjunto de estados\n");
      return NULL;
    }
    appendSet(&currentStates, currentState);

    return currentStates;
  }
  else
  {
    Set currentStates = createSet();
    if (currentStates == NULL)
    {
      printf("Error: No se pudo crear conjunto inicial de estados\n");
      return NULL;
    }
    appendSet(&currentStates, af->q0->string);

    Str inputAux = input;
    while (inputAux != NULL)
    {
      Str symbol = createStr();
      if (symbol == NULL)
      {
        printf("Error: No se pudo crear simbolo\n");
        return NULL;
      }
      symbol->character = inputAux->character;
      symbol->sig = NULL;

      Set nextStates = processNextSymbol(af, currentStates, symbol);

      if (nextStates == NULL || nextStates->string == NULL)
      {
        printf("No hay transiciones posibles - cadena rechazada\n");
        if (nextStates != NULL)
        {
          nextStates = NULL;
        }
        return NULL;
      }

      currentStates = nextStates;
      inputAux = inputAux->sig;
    }

    return currentStates;
  }
}

int isAcceptingState(Af af, Str state)
{
  if (af == NULL || af->F == NULL || state == NULL)
    return 0;

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

StateSetList createStateSet(Set states, Str name)
{
  StateSetList newStateSet = (StateSetList)malloc(sizeof(StateSet));
  if (newStateSet == NULL)
    return NULL;

  newStateSet->states = states;
  newStateSet->stateName = name;
  newStateSet->next = NULL;
  return newStateSet;
}

StateSetList findStateSet(StateSetList list, Set targetStates)
{
  StateSetList current = list;
  while (current != NULL)
  {
    if (setsAreEqual(current->states, targetStates))
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

int hasUnprocessedStates(StateSetList Qb, StateSetList processed, Af af)
{
  StateSetList current = Qb;
  while (current != NULL)
  {
    StateSetList found = findStateSet(processed, current->states);
    if (found == NULL)
    {
      tData alphabetNode = af->Sigma;
      while (alphabetNode != NULL)
      {
        if (alphabetNode->data != NULL && alphabetNode->data->nodeType == STR)
        {
          Set targetStates = getUnionOfTransitions(af, current->states, alphabetNode->data->string);
          if (targetStates != NULL && targetStates->string != NULL)
          {
            return 1;
          }
        }
        alphabetNode = alphabetNode->next;
      }
    }
    current = current->next;
  }
  return 0;
}

Set getUnionOfTransitions(Af af, Set stateSet, Str symbol)
{
  if (af == NULL || stateSet == NULL || symbol == NULL)
    return NULL;

  Set result = createSet();
  if (result == NULL)
    return NULL;

  Set currentState = stateSet;
  while (currentState != NULL && currentState->string != NULL)
  {
    Set transitions = getAllTransitions(af, currentState->string, symbol);
    if (transitions != NULL)
    {
      Set transNode = transitions;
      while (transNode != NULL && transNode->string != NULL)
      {
        appendSet(&result, transNode->string);
        transNode = transNode->sig;
      }
    }
    currentState = currentState->sig;
  }

  return (result->string != NULL) ? result : NULL;
}

void addStateSetIfNotExists(StateSetList *list, Set states)
{
  if (states == NULL || states->string == NULL)
    return;

  if (findStateSet(*list, states) != NULL)
    return;

  Str name = toStrSet(states);
  StateSetList newStateSet = createStateSet(states, name);
  if (newStateSet == NULL)
    return;

  if (*list == NULL)
  {
    *list = newStateSet;
  }
  else
  {
    StateSetList current = *list;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newStateSet;
  }
}

Af afnd2afd(Af afnd)
{
  if (afnd == NULL)
  {
    printf("Error: AFND es NULL\n");
    return NULL;
  }

  if (isDeterministic(afnd))
  {
    printf("El automata ya es determinista\n");
    return afnd;
  }

  printf("\n=== CONVIRTIENDO AFND A AFD ===\n");

  // Paso 1: Inicializacion
  // q0b = {q0}
  Set q0b = createSet();
  if (afnd->q0 != NULL && afnd->q0->nodeType == STR)
  {
    appendSet(&q0b, afnd->q0->string);
  }

  // Qb = {q0b}
  StateSetList Qb = NULL;
  addStateSetIfNotExists(&Qb, q0b);

  StateSetList processed = NULL;

  // Paso 2: Construccion de estados y transiciones
  StateSetList currentStateSet = Qb;
  while (currentStateSet != NULL)
  {
    if (findStateSet(processed, currentStateSet->states) == NULL)
    {
      addStateSetIfNotExists(&processed, currentStateSet->states);

      // Para cada símbolo del alfabeto
      tData alphabetNode = afnd->Sigma;
      while (alphabetNode != NULL)
      {
        if (alphabetNode->data != NULL && alphabetNode->data->nodeType == STR)
        {
          // deltab(P, a) = UNION r en P => delta(r, a)
          Set targetStates = getUnionOfTransitions(afnd, currentStateSet->states, alphabetNode->data->string);

          if (targetStates != NULL && targetStates->string != NULL)
          {
            // Qb = Qb Union {deltab(P, a)}
            addStateSetIfNotExists(&Qb, targetStates);
          }
        }
        alphabetNode = alphabetNode->next;
      }
    }
    currentStateSet = currentStateSet->next;
  }

  // Paso 3: Crear el AFD resultante
  Af afd = createAf();
  if (afd == NULL)
  {
    printf("Error: No se pudo crear el AFD\n");
    return NULL;
  }

  // Crear conjunto de estados Qb
  Set afdStates = createSet();
  StateSetList current = Qb;
  while (current != NULL)
  {
    appendSet(&afdStates, current->stateName);
    current = current->next;
  }
  setStates(afd, afdStates);

  // Crear conjunto de simbolos Sigma
  Set afdAlphabet = createSet();
  tData alphaNode = afnd->Sigma;
  while (alphaNode != NULL)
  {
    if (alphaNode->data != NULL && alphaNode->data->nodeType == STR)
    {
      appendSet(&afdAlphabet, alphaNode->data->string);
    }
    alphaNode = alphaNode->next;
  }
  setAlphabet(afd, afdAlphabet);

  // Estado inicial del AFD
  Str afdInitialState = toStrSet(q0b);
  setInitialState(afd, afdInitialState);

  // Paso 4: Crear transiciones del AFD
  current = Qb;
  while (current != NULL)
  {
    tData alphabetNode = afnd->Sigma;
    while (alphabetNode != NULL)
    {
      if (alphabetNode->data != NULL && alphabetNode->data->nodeType == STR)
      {
        Set targetStates = getUnionOfTransitions(afnd, current->states, alphabetNode->data->string);
        if (targetStates != NULL && targetStates->string != NULL)
        {
          Str targetStateName = toStrSet(targetStates);
          addTransition(afd, current->stateName, alphabetNode->data->string, targetStateName);
        }
      }
      alphabetNode = alphabetNode->next;
    }
    current = current->next;
  }

  // Paso 5: Crear estados finales Fb
  Set originalFinalStates = getOriginalFinalStates(afnd);
  if (originalFinalStates == NULL)
  {
    printf("Error: No se pudieron obtener estados finales originales\n");
    destroyAf(&afd);
    return NULL;
  }

  Set afdFinalStates = createSet();
  if (afdFinalStates == NULL)
  {
    printf("ERROR: No se pudo crear conjunto de estados finales AFD\n");
    destroyAf(&afd);
    return NULL;
  }

  current = Qb;
  while (current != NULL)
  {
    if (containsFinalState(current->states, originalFinalStates))
    {
      appendSet(&afdFinalStates, current->stateName);
    }
    current = current->next;
  }

  setFinalStates(afd, afdFinalStates);

  printf("\n=== AFD RESULTANTE ===\n");
  printAf(afd, 0);

  return afd;
}

int containsFinalState(Set stateSet, Set finalStates)
{
  if (stateSet == NULL || finalStates == NULL)
  {
    return 0;
  }

  Set currentState = stateSet;
  while (currentState != NULL && currentState->string != NULL)
  {
    Set currentFinal = finalStates;
    while (currentFinal != NULL && currentFinal->string != NULL)
    {
      if (compareStr(currentState->string, currentFinal->string) == 1)
      {
        return 1;
      }
      currentFinal = currentFinal->sig;
    }
    currentState = currentState->sig;
  }

  return 0;
}

Set getOriginalFinalStates(Af afnd)
{
  if (afnd == NULL || afnd->F == NULL)
  {
    printf("Error: AFND o F es NULL\n");
    return NULL;
  }

  Set finalStates = createSet();
  if (finalStates == NULL)
  {
    printf("Error: No se pudo crear conjunto de estados finales\n");
    return NULL;
  }

  tData current = afnd->F;
  while (current != NULL)
  {
    if (current->data != NULL && current->data->nodeType == STR)
    {
      appendSet(&finalStates, current->data->string);
    }
    current = current->next;
  }

  return finalStates;
}

void destroyStateSetList(StateSetList *list)
{
  StateSetList current = *list;
  while (current != NULL)
  {
    StateSetList temp = current;
    current = current->next;
    if (temp->states != NULL)
    {
      destroySet(&(temp->states));
    }
    free(temp);
  }
  *list = NULL;
}
