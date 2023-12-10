//
// Created by Malick on 03/12/2023.
//

#ifndef AGENDAPROJECT_PART2_LIST_H
#define AGENDAPROJECT_PART2_LIST_H

#include "../cell/cell.h"
#include "math.h"


typedef struct s_d_list
{
    int max_levels;
    t_d_cell ** heads;
} t_d_list;

t_d_list * createEmptyList(int);

void addCellToListHead( t_d_list * , t_d_cell * );

int isValInLvl0(t_d_list, int);

int isValInList(t_d_list, int);

t_d_list * createLevelList(int);


#endif //AGENDAPROJECT_PART2_LIST_H
