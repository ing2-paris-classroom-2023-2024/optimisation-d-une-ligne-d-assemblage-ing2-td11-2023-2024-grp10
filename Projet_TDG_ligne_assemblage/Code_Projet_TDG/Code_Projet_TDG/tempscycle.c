//
// Created by lolas on 26/11/2023.
//
//
#include "tempscycle.h"


// sous programme pour lire dans le ficher le temps de cycle
float liretempscycle(const char* nomfichier) {
    f* fichier = fopen(nomfichier, "r");
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