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
    
    return 0;
}
  
