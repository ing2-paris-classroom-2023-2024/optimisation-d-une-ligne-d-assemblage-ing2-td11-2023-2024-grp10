//
// Created by lolas on 03/12/2023.
//

#include "tempsxprecedences.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 100

// Structure pour repr�senter une op�ration avec son temps d'ex�cution
typedef struct {
    int operationNumber;
    double executionTime;
} Operation;

// Structure pour repr�senter un n�ud du graphe
typedef struct Node {
    int operation;
    struct Node* next;
} Node;

// Structure pour repr�senter le graphe de pr�c�dence
typedef struct Graph {
    int numOperations;
    Node* adjList[MAX_OPERATIONS];
    int inDegree[MAX_OPERATIONS];
    int isSpecified[MAX_OPERATIONS];
} Graph;

// Fonction pour lire les op�rations depuis le fichier
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

// Fonction pour ajouter une ar�te au graphe
void addEdge(Graph* graph, int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operation = to;
    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;

    // Met � jour le degr� entrant de la destination
    graph->inDegree[to]++;
    // Marque les op�rations comme sp�cifi�es
    graph->isSpecified[from] = 1;
    graph->isSpecified[to] = 1;
}

// Fonction pour effectuer le tri topologique du graphe
int* topologicalSort(Graph* graph) {
    int* order = (int*)malloc(graph->numOperations * sizeof(int));
    int* visited = (int*)malloc(graph->numOperations * sizeof(int));

    for (int i = 0; i < graph->numOperations; ++i) {
        visited[i] = 0;
    }

    int index = 0;

    // Ajoute les op�rations sans pr�c�dents et sp�cifi�es dans l'ordre
    for (int i = 0; i < graph->numOperations; ++i) {
        if (graph->inDegree[i] == 0 && graph->isSpecified[i]) {
            order[index++] = i;
            visited[i] = 1;  // Marque les op�rations sans pr�c�dents comme visit�es
        }
    }

    // Parcours le graphe pour le tri topologique
    for (int i = 0; i < graph->numOperations; ++i) {
        int currentOperation = order[i];
        Node* currentNode = graph->adjList[currentOperation];

        while (currentNode != NULL) {
            int nextOperation = currentNode->operation;
            graph->inDegree[nextOperation]--;

            if (graph->inDegree[nextOperation] == 0 && !visited[nextOperation]) {
                order[index++] = nextOperation;
                visited[nextOperation] = 1;
            }

            currentNode = currentNode->next;
        }
    }

    // Affichage de l'ordre d'execution des op�rations
    printf("Ordre d'execution des operations :\n");
    for (int i = 0; i < index; ++i) {
        printf("%d ", order[i] + 1);  // Ajoute 1 pour afficher les op�rations � partir de 1 au lieu de 0
    }
    printf("\n");
    free(order);
    free(visited);
    return order;
}

// Fonction pour afficher le graphe de pr�c�dence
void printGraph(Graph* graph) {
    printf("Graphe de precedence :\n");
    for (int i = 0; i < graph->numOperations; ++i) {
        if (graph->isSpecified[i] && graph->adjList[i] != NULL) {
            printf("%d -> ", i + 1);  // Ajoute 1 pour afficher les op�rations � partir de 1 au lieu de 0

            Node* currentNode = graph->adjList[i];
            while (currentNode != NULL) {
                printf("%d", currentNode->operation + 1);  // Ajoute 1 pour afficher les op�rations � partir de 1
                if (currentNode->next != NULL) {
                    printf(", ");
                }
                currentNode = currentNode->next;
            }

            printf("\n");
        }
    }
}
float liretempscycle(const char* nomfichier) {
    FILE * fichier = fopen(nomfichier, "r");
    // on declare un pointeur pour ouvrir le fichier
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier TEMPS CYCLES ");
        exit(1);
    }
    // blindage


    float tempscycle;
    if (fscanf(fichier, "%f", &tempscycle) != 1) {
        // on lis le fichier
        printf("Erreur lecture du TEMPS DE CYCLE");
        exit(1);
    }

    fclose(fichier);
    return tempscycle;
}
void creerStations(Operation *operations, int* order, int size, float tempsCycle) {
    int stationNumber = 1;
    float tempsTotalStation = 0.0;

    printf("Station %d:\n", stationNumber);
    for (int i = 0; i < size; i++) {
        // Trouver l'index de l'opération dans le tableau des opérations
        int opIndex = -1;
        for (int j = 0; j < size; j++) {
            if (operations[j].operationNumber == order[i] ) { // +1 car l'ordre est basé sur un index 0
                opIndex = j;
                break;
            }
        }

        if (opIndex == -1) {
            // Si l'opération n'est pas trouvée, continuer avec la suivante
            continue;
        }

        // Vérifier si l'opération actuelle peut être ajoutée à la station actuelle
        if (tempsTotalStation + operations[opIndex].executionTime > tempsCycle) {
            // Si l'ajout de cette opération dépasse le temps de cycle, passer à la prochaine station
            printf("    Temps total de la Station %d: %.2f\n", stationNumber, tempsTotalStation);
            stationNumber++;
            tempsTotalStation = 0.0;
            printf("\nStation %d:\n", stationNumber);
        }

        // Ajouter l'opération à la station actuelle
        printf("    Operation %d: Temps d'execution = %.2f\n", operations[opIndex].operationNumber, operations[opIndex].executionTime);
        tempsTotalStation += operations[opIndex].executionTime;
    }

    // Afficher le temps total pour la dernière station
    printf("    Temps total de la Station %d: %.2f\n", stationNumber, tempsTotalStation);
}


int main() {
    FILE* filePrecedences = fopen("../precedences.txt", "r");
    FILE* fileOperations = fopen("../operations.txt", "r");
    if (filePrecedences == NULL || fileOperations == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lire les op�rations depuis le fichier
    Operation operations[MAX_OPERATIONS];
    int numOperations = readOperations(operations, fileOperations);

    // Initialiser le nombre total d'op�rations avec le maximum
    int maxNumOperations = numOperations;

    int from, to;

    // Lecture du nombre total d'op�rations � partir du fichier de pr�c�dences
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

    // Ajout des ar�tes de pr�c�dence au graphe
    fseek(filePrecedences, 0, SEEK_SET);  // R�initialise la position du curseur dans le fichier
    while (fscanf(filePrecedences, "%d %d", &from, &to) == 2) {
        addEdge(graph, from - 1, to - 1);  // Soustrait 1 car les indices commencent � partir de 0
    }

    // Fermeture du fichier
    fclose(filePrecedences);

    // Fermeture du fichier
    fclose(fileOperations);

    // Affichage du graphe de pr�c�dence
    printGraph(graph);

    // Tri topologique et affichage de l'ordre d'ex�cution
    int * order =topologicalSort(graph);

    // Afficher les op�rations pour v�rification
    printf("\n\nOperations lues depuis le fichier :\n\n");
    for (int i = 0; i < numOperations; ++i) {
        printf("Operation %d : Temps d'execution %.2lf\n", operations[i].operationNumber, operations[i].executionTime);
    }
    printf("\n");
    float tempsCycle = liretempscycle("../temps_cycle.txt");

    if (numOperations > 0) {
        creerStations(operations, order, numOperations, tempsCycle);
    }
    free(order);
    // Lib�ration de la m�moire
    for (int i = 0; i < graph->numOperations; ++i) {
        Node* currentNode = graph->adjList[i];
        while (currentNode != NULL) {
            Node* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
    }
    free(graph);

    return 0;
}
