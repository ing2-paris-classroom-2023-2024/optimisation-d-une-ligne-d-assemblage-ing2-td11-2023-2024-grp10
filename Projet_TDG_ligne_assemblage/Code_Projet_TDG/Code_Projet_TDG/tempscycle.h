//
// Created by lolas on 26/11/2023.
//
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD11_2023_2024_GRP10_TEMPSCYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD11_2023_2024_GRP10_TEMPSCYCLE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int operationNumber;
    double executionTime;
} Operation;

float liretempscycle(const char* nomfichier);
int lireoperations(const char *fileName, Operation *operations, int maxSize);
void creerStations(Operation *operations, int size, float tempsCycle);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TD11_2023_2024_GRP10_TEMPSCYCLE_H
