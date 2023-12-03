#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100

// Structure pour représenter une opération avec son temps d'exécution
typedef struct {
    int operationNumber;
    double executionTime;
} Operation;

// Structure pour représenter un nœud du graphe
typedef struct Node {
    int operation;
    struct Node* next;
} Node;
