//
// Created by Malick on 03/12/2023.
//

#include "cell.h"

t_d_cell * createEmptyCell(int val,int levelNb){
    t_d_cell * newCell = malloc(sizeof(t_d_cell));
    newCell->max_level = levelNb;
    newCell->value = val;
    newCell->next = malloc(levelNb * sizeof (t_d_cell*));
    for(int i = 0; i < levelNb;i++){
        newCell->next[i] = NULL;
    }
    return newCell;
}