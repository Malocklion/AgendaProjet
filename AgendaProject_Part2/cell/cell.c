//
// Created by Malick on 03/12/2023.
//

#include "cell.h"

//Fonction de creation d'une cellule
t_d_cell * createEmptyCell(int val,int levelNb){
    t_d_cell * newCell = malloc(sizeof(t_d_cell));

    //Verification de l'allocation dynamique
    if(NULL == newCell){
        printf("Allocation echoue");
        exit(EXIT_FAILURE);
    }

    newCell->nbLevels = levelNb;
    newCell->value = val;

    newCell->next = malloc(levelNb * sizeof (t_d_cell*));

    //Verification de l'allocation dynamique
    if(NULL == newCell->next){
        printf("Allocation echoue");
        exit(EXIT_FAILURE);
    }

    //Initialisation a NULL
    for(int i = 0; i < levelNb;i++){
        newCell->next[i] = NULL;
    }
    return newCell;
}