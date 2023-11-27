#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter une paire d'opérations interdites
typedef struct {
    int op1;
    int op2;
} Exclusion;

// Structure pour représenter le graphe orienté sans cycle (acyclique)
typedef struct {
    int numVertices; // Nombre total d'opérations
    int numExclusions; // Nombre de paires d'opérations interdites
    Exclusion exclusions[MAX_OPERATIONS]; // Tableau de paires d'opérations interdites
    int **exclusionMatrix; // Matrice d'adjacence pour les contraintes d'exclusion
} Graph;

// Structure pour représenter une opération avec son temps d'exécution
typedef struct {
    int operationNumber;
    double executionTime;
} Operation;

int main()
{
    // Charger les données du fichier exclusions.txt
    FILE *file = fopen("exclusions.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier exclusions.txt");
        return EXIT_FAILURE;
    }

    // Initialiser le graphe et les contraintes
    Graph graph;
    initializeGraph(&graph, MAX_OPERATIONS);

    // Lire les exclusions depuis le fichier et les ajouter au graphe
    int op1, op2;
    while (fscanf(file, "%d %d", &op1, &op2) == 2) {
        addExclusion(&graph, op1, op2);
    }

    // Fermer le fichier
    fclose(file);

    // Charger les données du fichier operations.txt
    file = fopen("operations.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier operations.txt");
        return EXIT_FAILURE;
    }
     // Lire les opérations depuis le fichier
    Operation operations[MAX_OPERATIONS];
    int numOperations = readOperations(operations, file);

    // Fermer le fichier
    fclose(file);
    return 0;
}
  
