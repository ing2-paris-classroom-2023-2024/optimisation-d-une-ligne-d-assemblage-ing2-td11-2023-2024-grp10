//
// Created by lolas on 26/11/2023.
//
//
#include "tempscycle.h"



// Structure qui permet de représenter une opération avec son temps d'exécution

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

int lireoperations(const char *fileName, Operation *operations, int maxSize) {
    FILE *file;
    //variable pour compter le nb d'operations
    int count = 0;

    //on ouvre le fichier en mode lecture
    file = fopen(fileName, "r");
    if (file == NULL) {
        //blindage
        printf("Erreur en ouvrant le fichier");
        exit(1);
    }

    while (fscanf(file, "%d %lf", &operations[count].operationNumber, &operations[count].executionTime) == 2) {
        count++;
        if (count >= maxSize) {
            printf("Limite de capacité du tableau atteinte.\n");
            break;
        }
    }

    fclose(file);
    return count;
}
/*
// pour verifier le graph avec l'affichage
void printOperations(const Operation *operations, int size) {
    for (int i = 0; i < size; i++) {
        printf("Operation %d: Temps d'execution = %.2f\n", operations[i].operationNumber, operations[i].executionTime);
    }
}*/

// fonction pour creer et afficher les stations
void creerStations(Operation *operations, int size, float tempsCycle) {
    // on initialise la première station a 1
    int stationNumber = 1;
    float tempsTotal = 0.0;
    float tempsTotalStation = 0.0;

    printf("Station %d:\n", stationNumber);
    for (int i = 0; i < size; i++) {
        // on verrifie si le temps de la station depasse le temps de cycle
        if (tempsTotal + operations[i].executionTime > tempsCycle) {
            printf("    Temps total de la Station %d: %.2f\n", stationNumber, tempsTotalStation);
            stationNumber++;
            tempsTotal = 0.0f;
            tempsTotalStation = 0.0f;
            printf("\nStation %d:\n", stationNumber);
        }
        printf("    Operation %d: Temps d'execution = %.2f\n", operations[i].operationNumber, operations[i].executionTime);
        tempsTotal += operations[i].executionTime;
        tempsTotalStation += operations[i].executionTime;
    }
    printf("    Temps total de la Station %d: %.2f\n", stationNumber, tempsTotalStation);
}


int main() {
    // on initialise notre tab de structures
    Operation operations[100];
    // on recup dans les fichiers le temps de cycles et les operations avec leur temps d'execution
    float tempsCycle = liretempscycle("../temps_cycle.txt");
    int size = lireoperations("../operations.txt", operations, 100);


    if (size > 0) {
        // on applique le code pour creer les station
        creerStations(operations, size, tempsCycle);
    }

    return 0;
}
