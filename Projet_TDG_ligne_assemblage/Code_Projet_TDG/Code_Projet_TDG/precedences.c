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

// Structure pour représenter le graphe de précédence
typedef struct Graph {
    int numOperations;
    Node* adjList[MAX_OPERATIONS];
    int inDegree[MAX_OPERATIONS];
    int isSpecified[MAX_OPERATIONS];
} Graph;

// Fonction pour lire les opérations depuis le fichier
int readOperations(Operation *operations, FILE *file) {
    int numOperations = 0;
    while (fscanf(file, "%d %lf", &(operations[numOperations].operationNumber), &(operations[numOperations].executionTime)) == 2) {
        ++numOperations;
    }
    return numOperations;
}

// Fonction pour initialiser le graphe
Graph* initializeGraph(int numOperations) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numOperations = numOperations;

    for (int i = 0; i < numOperations; ++i) {
        graph->adjList[i] = NULL;
        graph->inDegree[i] = 0;
        graph->isSpecified[i] = 0;
    }

    return graph;
}

// Fonction pour ajouter une arête au graphe
void addEdge(Graph* graph, int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operation = to;
    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;

    // Met à jour le degré entrant de la destination
    graph->inDegree[to]++;
    // Marque les opérations comme spécifiées
    graph->isSpecified[from] = 1;
    graph->isSpecified[to] = 1;
}

int main() {
    FILE* filePrecedences = fopen("precedences.txt", "r");
    FILE* fileOperations = fopen("operations.txt", "r");
    if (filePrecedences == NULL || fileOperations == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lire les opérations depuis le fichier
    Operation operations[MAX_OPERATIONS];
    int numOperations = readOperations(operations, fileOperations);

    // Initialiser le nombre total d'opérations avec le maximum
    int maxNumOperations = numOperations;

    int from, to;

    // Lecture du nombre total d'opérations à partir du fichier de précédences
    while (fscanf(filePrecedences, "%d %d", &from, &to) == 2) {
        if (from > maxNumOperations) {
            maxNumOperations = from;
        }
        if (to > maxNumOperations) {
            maxNumOperations = to;
        }
    }

    // Initialisation du graphe
    Graph* graph = initializeGraph(maxNumOperations);
    
    return 0;
}
