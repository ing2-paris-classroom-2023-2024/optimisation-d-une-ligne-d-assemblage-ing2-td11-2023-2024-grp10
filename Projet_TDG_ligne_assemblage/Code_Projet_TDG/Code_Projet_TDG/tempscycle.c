//
// Created by lolas on 26/11/2023.
//
//tzsr Test ,
#include "tempscycle.h"

float liretempscycle(const char* nomfichier) {
    f* fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier TEMPS CYCLES ");
        exit(1);
    }


    float tempscycle;
    if (fscanf(fichier, "%f", &tempscycle) != 1) {
        printf("Erreur lecture du TEMPS DE CYCLE");
        exit(1);
    }

    fclose(fichier);
    return tempscycle;
}